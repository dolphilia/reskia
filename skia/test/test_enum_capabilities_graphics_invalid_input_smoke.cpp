#include "capi/sk_alpha_type.h"
#include "capi/sk_blend_mode.h"
#include "capi/sk_capabilities.h"
#include "capi/sk_data.h"
#include "capi/sk_graphics.h"
#include "capi/sk_images.h"
#include "handles/static_sk_data.h"
#include "handles/static_sk_capabilities.h"
#include "include/core/SkBlendMode.h"

#include <cstdio>

namespace {

struct GraphicsFactoryContext {
    int *callback_count;
    int *release_count;
    const void **last_data_ptr;
};

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[enum-capabilities-graphics-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

sk_image_generator_t null_image_generator_factory(const_sk_data_t encoded_data, void *user_data) {
    auto *context = static_cast<GraphicsFactoryContext *>(user_data);
    if (context != nullptr) {
        if (context->callback_count != nullptr) {
            ++*context->callback_count;
        }
        if (context->last_data_ptr != nullptr) {
            *context->last_data_ptr = static_const_sk_data_get_ptr(encoded_data);
        }
    }
    return 0;
}

void release_graphics_factory_context(void *user_data) {
    auto *context = static_cast<GraphicsFactoryContext *>(user_data);
    if (context != nullptr && context->release_count != nullptr) {
        ++*context->release_count;
    }
}

}  // namespace

int main() {
    bool ok = true;

    ok &= check(!SkAlphaType_SkAlphaTypeIsOpaque(-1), "SkAlphaType invalid low");
    ok &= check(!SkAlphaType_SkAlphaTypeIsOpaque(999999), "SkAlphaType invalid high");
    ok &= check(SkAlphaType_SkAlphaTypeIsOpaque(1), "SkAlphaType opaque valid");

    SkBlendModeCoeff src = SkBlendModeCoeff::kZero;
    SkBlendModeCoeff dst = SkBlendModeCoeff::kZero;
    ok &= check(!SkBlendMode_SkBlendMode_AsCoeff(-1, &src, &dst), "SkBlendMode AsCoeff invalid mode");
    ok &= check(!SkBlendMode_SkBlendMode_AsCoeff(0, nullptr, &dst), "SkBlendMode AsCoeff null src");
    ok &= check(!SkBlendMode_SkBlendMode_AsCoeff(0, &src, nullptr), "SkBlendMode AsCoeff null dst");
    ok &= check(SkBlendMode_SkBlendMode_AsCoeff(0, &src, &dst), "SkBlendMode AsCoeff valid");
    ok &= check(SkBlendMode_SkBlendMode_Name(-1) == nullptr, "SkBlendMode Name invalid");
    ok &= check(SkBlendMode_SkBlendMode_Name(0) != nullptr, "SkBlendMode Name valid");

    SkCapabilities_ref(nullptr);
    SkCapabilities_unref(nullptr);
    SkCapabilities_release(nullptr);
    ok &= check(SkCapabilities_skslVersion(nullptr) == 0, "SkCapabilities skslVersion null");
    ok &= check(!SkCapabilities_unique(nullptr), "SkCapabilities unique null");
    const_sk_capabilities_t raster = SkCapabilities_RasterBackend();
    const void *raster_ptr = static_const_sk_capabilities_get_ptr(raster);
    ok &= check(raster != 0 && raster_ptr != nullptr, "SkCapabilities RasterBackend handle");
    if (raster_ptr != nullptr) {
        void *raster_mut = const_cast<void *>(raster_ptr);
        ok &= check(SkCapabilities_skslVersion(raster_mut) >= 0, "SkCapabilities RasterBackend skslVersion");
        const bool raster_unique = SkCapabilities_unique(raster_mut);
        ok &= check(raster_unique == SkCapabilities_unique(raster_mut), "SkCapabilities RasterBackend unique stable");
        SkCapabilities_ref(raster_mut);
        SkCapabilities_unref(raster_mut);
    }
    static_const_sk_capabilities_delete(raster);

    SkGraphics_Init();
    const int count_limit = SkGraphics_GetFontCacheCountLimit();
    ok &= check(SkGraphics_SetFontCacheCountLimit(-1) == count_limit, "SkGraphics negative font cache count rejected");
    const size_t font_limit = SkGraphics_GetFontCacheLimit();
    ok &= check(SkGraphics_SetFontCacheLimit(font_limit) == font_limit, "SkGraphics font cache byte limit stable set");
    ok &= check(SkGraphics_GetFontCacheLimit() == font_limit, "SkGraphics font cache byte limit restored");
    ok &= check(SkGraphics_SetFontCacheCountLimit(count_limit) == count_limit, "SkGraphics font cache count limit stable set");
    ok &= check(SkGraphics_GetFontCacheCountLimit() == count_limit, "SkGraphics font cache count limit restored");
    ok &= check(SkGraphics_GetFontCacheUsed() <= SkGraphics_GetFontCacheLimit(), "SkGraphics font cache used within limit");
    ok &= check(SkGraphics_GetFontCacheCountUsed() >= 0, "SkGraphics font cache count used non-negative");
    const size_t resource_total_limit = SkGraphics_GetResourceCacheTotalByteLimit();
    ok &= check(SkGraphics_SetResourceCacheTotalByteLimit(resource_total_limit) == resource_total_limit, "SkGraphics resource total limit stable set");
    ok &= check(SkGraphics_GetResourceCacheTotalByteLimit() == resource_total_limit, "SkGraphics resource total limit restored");
    ok &= check(SkGraphics_GetResourceCacheTotalBytesUsed() <= SkGraphics_GetResourceCacheTotalByteLimit(), "SkGraphics resource bytes used within limit");
    const size_t single_allocation_limit = SkGraphics_GetResourceCacheSingleAllocationByteLimit();
    ok &= check(SkGraphics_SetResourceCacheSingleAllocationByteLimit(single_allocation_limit) == single_allocation_limit, "SkGraphics resource single allocation limit stable set");
    ok &= check(SkGraphics_GetResourceCacheSingleAllocationByteLimit() == single_allocation_limit, "SkGraphics resource single allocation limit restored");
    SkGraphics_DumpMemoryStatistics(nullptr);
    SkGraphics_PurgeFontCache();
    SkGraphics_PurgePinnedFontCache();
    SkGraphics_PurgeResourceCache();
    SkGraphics_PurgeAllCaches();

    int first_callback_count = 0;
    int first_release_count = 0;
    const void *first_data_ptr = nullptr;
    GraphicsFactoryContext first_context{&first_callback_count, &first_release_count, &first_data_ptr};
    ok &= check(SkGraphics_SetImageGeneratorFromEncodedDataFactory(
                        null_image_generator_factory,
                        &first_context,
                        release_graphics_factory_context),
                "SkGraphics image generator factory install");
    const uint8_t invalid_encoded[] = {0x52, 0x53, 0x4b, 0x00};
    sk_data_t invalid_data = SkData_MakeWithCopy(invalid_encoded, sizeof(invalid_encoded));
    sk_image_t invalid_image = SkImages_DeferredFromEncodedData(invalid_data);
    ok &= check(invalid_image == 0, "SkGraphics image generator factory null fallback result");
    ok &= check(first_callback_count == 1, "SkGraphics image generator factory callback called");
    ok &= check(first_data_ptr != nullptr, "SkGraphics image generator factory borrowed data");
    ok &= check(first_release_count == 0, "SkGraphics image generator factory retained context before replace");
    static_sk_data_delete(invalid_data);

    int second_callback_count = 0;
    int second_release_count = 0;
    const void *second_data_ptr = nullptr;
    GraphicsFactoryContext second_context{&second_callback_count, &second_release_count, &second_data_ptr};
    ok &= check(SkGraphics_SetImageGeneratorFromEncodedDataFactory(
                        null_image_generator_factory,
                        &second_context,
                        release_graphics_factory_context),
                "SkGraphics image generator factory replace");
    ok &= check(first_release_count == 1, "SkGraphics image generator factory replaced context released once");
    invalid_data = SkData_MakeWithCopy(invalid_encoded, sizeof(invalid_encoded));
    invalid_image = SkImages_DeferredFromEncodedData(invalid_data);
    ok &= check(invalid_image == 0, "SkGraphics image generator factory second null fallback result");
    ok &= check(second_callback_count == 1, "SkGraphics image generator factory replacement callback called");
    ok &= check(second_data_ptr != nullptr, "SkGraphics image generator factory replacement borrowed data");
    ok &= check(second_release_count == 0, "SkGraphics image generator factory replacement retained");
    static_sk_data_delete(invalid_data);

    ok &= check(!SkGraphics_SetImageGeneratorFromEncodedDataFactory(nullptr, nullptr, nullptr),
                "SkGraphics image generator factory rejects null callback");
    ok &= check(second_release_count == 0, "SkGraphics image generator factory null callback does not replace");
    ok &= check(SkGraphics_SetImageGeneratorFromEncodedDataFactory(
                        null_image_generator_factory,
                        nullptr,
                        nullptr),
                "SkGraphics image generator factory final no-op replacement");
    ok &= check(second_release_count == 1, "SkGraphics image generator factory replacement context released once");

    return ok ? 0 : 1;
}
