//
// Created by dolphilia on 2024/01/13.
//

#include "sk_surfaces.h"

#include "include/core/SkSurface.h"

#include "../static/static_sk_surface.h"

#include "../static/static_sk_surface-internal.h"

extern "C" {

sk_surface_t SkSurfaces_Null(int width, int height) {
    return static_sk_surface_make(SkSurfaces::Null(width, height));
}

sk_surface_t SkSurfaces_Raster(const void *imageInfo, size_t rowBytes, const void *surfaceProps) {
    return static_sk_surface_make(SkSurfaces::Raster(* static_cast<const SkImageInfo *>(imageInfo), rowBytes, static_cast<const SkSurfaceProps *>(surfaceProps)));
}

sk_surface_t SkSurfaces_Raster_2(const void *imageInfo, const void *props) {
    return static_sk_surface_make(SkSurfaces::Raster(* static_cast<const SkImageInfo *>(imageInfo), static_cast<const SkSurfaceProps *>(props)));
}

sk_surface_t SkSurfaces_WrapPixels(const void *imageInfo, void *pixels, size_t rowBytes, const void *surfaceProps) {
    return static_sk_surface_make(SkSurfaces::WrapPixels(* static_cast<const SkImageInfo *>(imageInfo), pixels, rowBytes, static_cast<const SkSurfaceProps *>(surfaceProps)));
}

sk_surface_t SkSurfaces_WrapPixels_2(const void *pm, const void *props) {
    return static_sk_surface_make(SkSurfaces::WrapPixels(* static_cast<const SkPixmap *>(pm), static_cast<const SkSurfaceProps *>(props)));
}

sk_surface_t SkSurfaces_WrapPixels_3(const void *imageInfo, void *pixels, size_t rowBytes, void(* pixelsReleaseProc)(void *, void *), void *context, const void *surfaceProps) {
    return static_sk_surface_make(SkSurfaces::WrapPixels(* static_cast<const SkImageInfo *>(imageInfo), pixels, rowBytes, pixelsReleaseProc, context, static_cast<const SkSurfaceProps *>(surfaceProps)));
}

}
