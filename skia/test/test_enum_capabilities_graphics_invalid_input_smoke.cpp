#include "capi/sk_alpha_type.h"
#include "capi/sk_blend_mode.h"
#include "capi/sk_capabilities.h"
#include "capi/sk_graphics.h"
#include "handles/static_sk_capabilities.h"
#include "include/core/SkBlendMode.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[enum-capabilities-graphics-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
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

    return ok ? 0 : 1;
}
