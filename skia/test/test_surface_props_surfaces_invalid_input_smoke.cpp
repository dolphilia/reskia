#include "capi/sk_surface_props.h"
#include "capi/sk_surfaces.h"
#include "handles/static_sk_surface.h"
#include "handles/static_sk_surface_props.h"

#include <cstdio>

namespace {
bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[surface-props-surfaces-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}
} // namespace

int main() {
    bool ok = true;

    SkSurfaceProps_delete(nullptr);
    ok &= check(SkSurfaceProps_newCopy(nullptr) == nullptr, "SurfaceProps newCopy null");
    ok &= check(SkSurfaceProps_cloneWithPixelGeometry(nullptr, 0) == 0, "SurfaceProps clone null");
    ok &= check(SkSurfaceProps_flags(nullptr) == 0, "SurfaceProps flags null");
    ok &= check(SkSurfaceProps_pixelGeometry(nullptr) == 0, "SurfaceProps pixelGeometry null");
    ok &= check(!SkSurfaceProps_isUseDeviceIndependentFonts(nullptr), "SurfaceProps use device independent fonts null");
    ok &= check(!SkSurfaceProps_isAlwaysDither(nullptr), "SurfaceProps always dither null");

    reskia_surface_props_t *props = SkSurfaceProps_new();
    ok &= check(props != nullptr, "SurfaceProps new");
    if (props != nullptr) {
        reskia_surface_props_t *copy = SkSurfaceProps_newCopy(props);
        ok &= check(copy != nullptr, "SurfaceProps newCopy valid");
        SkSurfaceProps_delete(copy);

        const sk_surface_props_t clone = SkSurfaceProps_cloneWithPixelGeometry(props, 0);
        ok &= check(clone != 0, "SurfaceProps clone valid");
        if (clone != 0) {
            static_sk_surface_props_delete(clone);
        }
        (void)SkSurfaceProps_flags(props);
        (void)SkSurfaceProps_pixelGeometry(props);
        (void)SkSurfaceProps_isUseDeviceIndependentFonts(props);
        (void)SkSurfaceProps_isAlwaysDither(props);
        SkSurfaceProps_delete(props);
    }

    ok &= check(SkSurfaces_Raster(nullptr, 0, nullptr) == 0, "Raster null imageInfo");
    ok &= check(SkSurfaces_RasterWithoutRowBytes(nullptr, nullptr) == 0, "RasterWithoutRowBytes null imageInfo");
    ok &= check(SkSurfaces_WrapPixels(nullptr, nullptr, 0, nullptr) == 0, "WrapPixels null imageInfo");
    ok &= check(SkSurfaces_WrapPixelsWithPixmap(nullptr, nullptr) == 0, "WrapPixelsWithPixmap null pixmap");
    ok &= check(SkSurfaces_WrapPixelsWithReleaseProcAndContext(nullptr, nullptr, 0, nullptr, nullptr, nullptr) == 0, "WrapPixelsWithReleaseProc null imageInfo");

    const sk_surface_t null_surface = SkSurfaces_Null(1, 1);
    ok &= check(null_surface != 0, "Null surface valid");
    if (null_surface != 0) {
        static_sk_surface_delete(null_surface);
    }

    return ok ? 0 : 1;
}
