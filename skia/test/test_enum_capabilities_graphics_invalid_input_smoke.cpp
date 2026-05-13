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
    ok &= check(raster != 0 && static_const_sk_capabilities_get_ptr(raster) != nullptr, "SkCapabilities RasterBackend handle");
    static_const_sk_capabilities_delete(raster);

    SkGraphics_Init();
    const int count_limit = SkGraphics_GetFontCacheCountLimit();
    ok &= check(SkGraphics_SetFontCacheCountLimit(-1) == count_limit, "SkGraphics negative font cache count rejected");
    SkGraphics_DumpMemoryStatistics(nullptr);
    SkGraphics_PurgeFontCache();
    SkGraphics_PurgePinnedFontCache();
    SkGraphics_PurgeResourceCache();
    SkGraphics_PurgeAllCaches();

    return ok ? 0 : 1;
}
