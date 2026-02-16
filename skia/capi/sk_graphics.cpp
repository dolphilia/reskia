//
// Created by dolphilia on 2024/01/08.
//

#include "sk_graphics.h"

#include "include/core/SkGraphics.h"

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
    return SkGraphics::SetFontCacheCountLimit(count);
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
    SkGraphics::DumpMemoryStatistics(reinterpret_cast<SkTraceMemoryDump *>(dump));
}

void SkGraphics_PurgeAllCaches() {
    SkGraphics::PurgeAllCaches();
}

void * SkGraphics_SetImageGeneratorFromEncodedDataFactory(SkGraphics::ImageGeneratorFromEncodedDataFactory factory) {
    return reinterpret_cast<SkGraphics::ImageGeneratorFromEncodedDataFactory *>(SkGraphics::SetImageGeneratorFromEncodedDataFactory(factory));
}

void * SkGraphics_SetOpenTypeSVGDecoderFactory(SkGraphics::OpenTypeSVGDecoderFactory factory) {
    return reinterpret_cast<SkGraphics::OpenTypeSVGDecoderFactory *>(SkGraphics::SetOpenTypeSVGDecoderFactory(factory));
}

void * SkGraphics_GetOpenTypeSVGDecoderFactory() {
    return reinterpret_cast<SkGraphics::OpenTypeSVGDecoderFactory *>(SkGraphics::GetOpenTypeSVGDecoderFactory());
}

}
