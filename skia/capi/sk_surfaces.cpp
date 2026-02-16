//
// Created by dolphilia on 2024/01/13.
//

#include "sk_surfaces.h"

#include "include/core/SkSurface.h"

#include "../handles/static_sk_surface.h"

#include "../handles/static_sk_surface-internal.h"

extern "C" {

sk_surface_t SkSurfaces_Null(int width, int height) {
    return static_sk_surface_make(SkSurfaces::Null(width, height));
}

sk_surface_t SkSurfaces_Raster(const reskia_image_info_t *imageInfo, size_t rowBytes, const reskia_surface_props_t *surfaceProps) {
    return static_sk_surface_make(SkSurfaces::Raster(* reinterpret_cast<const SkImageInfo *>(imageInfo), rowBytes, reinterpret_cast<const SkSurfaceProps *>(surfaceProps)));
}

sk_surface_t SkSurfaces_Raster_2(const reskia_image_info_t *imageInfo, const reskia_surface_props_t *props) {
    return static_sk_surface_make(SkSurfaces::Raster(* reinterpret_cast<const SkImageInfo *>(imageInfo), reinterpret_cast<const SkSurfaceProps *>(props)));
}

sk_surface_t SkSurfaces_WrapPixels(const reskia_image_info_t *imageInfo, void *pixels, size_t rowBytes, const reskia_surface_props_t *surfaceProps) {
    return static_sk_surface_make(SkSurfaces::WrapPixels(* reinterpret_cast<const SkImageInfo *>(imageInfo), pixels, rowBytes, reinterpret_cast<const SkSurfaceProps *>(surfaceProps)));
}

sk_surface_t SkSurfaces_WrapPixels_2(const reskia_pixmap_t *pm, const reskia_surface_props_t *props) {
    return static_sk_surface_make(SkSurfaces::WrapPixels(* reinterpret_cast<const SkPixmap *>(pm), reinterpret_cast<const SkSurfaceProps *>(props)));
}

sk_surface_t SkSurfaces_WrapPixels_3(const reskia_image_info_t *imageInfo, void *pixels, size_t rowBytes, void(* pixelsReleaseProc)(void *, void *), void *context, const reskia_surface_props_t *surfaceProps) {
    return static_sk_surface_make(SkSurfaces::WrapPixels(* reinterpret_cast<const SkImageInfo *>(imageInfo), pixels, rowBytes, pixelsReleaseProc, context, reinterpret_cast<const SkSurfaceProps *>(surfaceProps)));
}

}
