//
// Created by dolphilia on 2024/01/08.
//

#include "sk_graphics.h"

#include "include/core/SkGraphics.h"

#include <memory>
#include <mutex>

#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_image_generator-internal.h"

namespace {

struct ImageGeneratorFactoryContext {
    reskia_image_generator_from_encoded_data_factory_t callback = nullptr;
    void *user_data = nullptr;
    reskia_callback_release_proc_t release_proc = nullptr;

    ~ImageGeneratorFactoryContext() {
        if (release_proc != nullptr) {
            release_proc(user_data);
        }
    }
};

std::mutex g_image_generator_factory_mutex;
std::shared_ptr<const ImageGeneratorFactoryContext> g_image_generator_factory_context;

std::unique_ptr<SkImageGenerator> reskia_image_generator_from_encoded_data_factory(sk_sp<const SkData> data) {
    std::shared_ptr<const ImageGeneratorFactoryContext> context;
    {
        std::lock_guard<std::mutex> lock(g_image_generator_factory_mutex);
        context = g_image_generator_factory_context;
    }
    if (!context || context->callback == nullptr) {
        return nullptr;
    }

    const_sk_data_t data_handle = static_const_sk_data_make(std::move(data));
    sk_image_generator_t generator_handle = context->callback(data_handle, context->user_data);
    static_const_sk_data_delete(data_handle);
    return static_sk_image_generator_take_entity(generator_handle);
}

} // namespace

extern "C" {

void SkGraphics_delete(reskia_graphics_t *graphics) {
    delete reinterpret_cast<SkGraphics *>(graphics);
}

// static

void SkGraphics_Init() {
    SkGraphics::Init();
}

size_t SkGraphics_GetFontCacheLimit() {
    return SkGraphics::GetFontCacheLimit();
}

size_t SkGraphics_SetFontCacheLimit(size_t bytes) {
    return SkGraphics::SetFontCacheLimit(bytes);
}

size_t SkGraphics_GetFontCacheUsed() {
    return SkGraphics::GetFontCacheUsed();
}

int SkGraphics_GetFontCacheCountUsed() {
    return SkGraphics::GetFontCacheCountUsed();
}

int SkGraphics_GetFontCacheCountLimit() {
    return SkGraphics::GetFontCacheCountLimit();
}

int SkGraphics_SetFontCacheCountLimit(int count) {
    if (count < 0) {
        return SkGraphics::GetFontCacheCountLimit();
    }
    return SkGraphics::SetFontCacheCountLimit(count);
}

int SkGraphics_GetTypefaceCacheCountLimit() {
    return SkGraphics::GetTypefaceCacheCountLimit();
}

int SkGraphics_SetTypefaceCacheCountLimit(int count) {
    if (count < 0) {
        return SkGraphics::GetTypefaceCacheCountLimit();
    }
    return SkGraphics::SetTypefaceCacheCountLimit(count);
}

void SkGraphics_PurgeFontCache() {
    SkGraphics::PurgeFontCache();
}

void SkGraphics_PurgePinnedFontCache() {
    SkGraphics::PurgePinnedFontCache();
}

size_t SkGraphics_GetResourceCacheTotalBytesUsed() {
    return SkGraphics::GetResourceCacheTotalBytesUsed();
}

size_t SkGraphics_GetResourceCacheTotalByteLimit() {
    return SkGraphics::GetResourceCacheTotalByteLimit();
}

size_t SkGraphics_SetResourceCacheTotalByteLimit(size_t newLimit) {
    return SkGraphics::SetResourceCacheTotalByteLimit(newLimit);
}

void SkGraphics_PurgeResourceCache() {
    SkGraphics::PurgeResourceCache();
}
size_t SkGraphics_GetResourceCacheSingleAllocationByteLimit() {
    return SkGraphics::GetResourceCacheSingleAllocationByteLimit();
}

size_t SkGraphics_SetResourceCacheSingleAllocationByteLimit(size_t newLimit) {
    return SkGraphics::SetResourceCacheSingleAllocationByteLimit(newLimit);
}

void SkGraphics_DumpMemoryStatistics(reskia_trace_memory_dump_t *dump) {
    if (dump == nullptr) {
        return;
    }
    SkGraphics::DumpMemoryStatistics(reinterpret_cast<SkTraceMemoryDump *>(dump));
}

void SkGraphics_PurgeAllCaches() {
    SkGraphics::PurgeAllCaches();
}

bool SkGraphics_SetImageGeneratorFromEncodedDataFactory(
        reskia_image_generator_from_encoded_data_factory_t callback,
        void *user_data,
        reskia_callback_release_proc_t release_proc) {
    if (callback == nullptr) {
        return false;
    }

    auto next_context = std::make_shared<ImageGeneratorFactoryContext>();
    next_context->callback = callback;
    next_context->user_data = user_data;
    next_context->release_proc = release_proc;

    std::shared_ptr<const ImageGeneratorFactoryContext> previous_context;
    {
        std::lock_guard<std::mutex> lock(g_image_generator_factory_mutex);
        previous_context = std::move(g_image_generator_factory_context);
        g_image_generator_factory_context = std::move(next_context);
    }

    SkGraphics::SetImageGeneratorFromEncodedDataFactory(
            reskia_image_generator_from_encoded_data_factory);
    return true;
}

SkGraphics::OpenTypeSVGDecoderFactory SkGraphics_SetOpenTypeSVGDecoderFactory(SkGraphics::OpenTypeSVGDecoderFactory factory) {
    return SkGraphics::SetOpenTypeSVGDecoderFactory(factory);
}

SkGraphics::OpenTypeSVGDecoderFactory SkGraphics_GetOpenTypeSVGDecoderFactory() {
    return SkGraphics::GetOpenTypeSVGDecoderFactory();
}

}
