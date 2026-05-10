//
// Created by dolphilia on 2024/01/13.
//

#include "sk_surfaces.h"

#include "include/core/SkSurface.h"

#include "../handles/static_sk_surface.h"

#include "../handles/static_sk_surface-internal.h"

namespace {

const SkImageInfo *as_image_info(const reskia_image_info_t *image_info) {
    return reinterpret_cast<const SkImageInfo *>(image_info);
}

const SkPixmap *as_pixmap(const reskia_pixmap_t *pixmap) {
    return reinterpret_cast<const SkPixmap *>(pixmap);
}

const SkSurfaceProps *as_surface_props(const reskia_surface_props_t *surface_props) {
    return reinterpret_cast<const SkSurfaceProps *>(surface_props);
}

sk_surface_t make_surface_handle(sk_sp<SkSurface> surface) {
    return surface ? static_sk_surface_make(surface) : 0;
}

} // namespace

extern "C" {

sk_surface_t SkSurfaces_Null(int width, int height) {
    return make_surface_handle(SkSurfaces::Null(width, height));
}

sk_surface_t SkSurfaces_Raster(const reskia_image_info_t *imageInfo, size_t rowBytes, const reskia_surface_props_t *surfaceProps) {
    const SkImageInfo *native_info = as_image_info(imageInfo);
    return native_info != nullptr ? make_surface_handle(SkSurfaces::Raster(*native_info, rowBytes, as_surface_props(surfaceProps))) : 0;
}

sk_surface_t SkSurfaces_RasterWithoutRowBytes(const reskia_image_info_t *imageInfo, const reskia_surface_props_t *props) {
    const SkImageInfo *native_info = as_image_info(imageInfo);
    return native_info != nullptr ? make_surface_handle(SkSurfaces::Raster(*native_info, as_surface_props(props))) : 0;
}

sk_surface_t SkSurfaces_WrapPixels(const reskia_image_info_t *imageInfo, void *pixels, size_t rowBytes, const reskia_surface_props_t *surfaceProps) {
    const SkImageInfo *native_info = as_image_info(imageInfo);
    return native_info != nullptr && pixels != nullptr ? make_surface_handle(SkSurfaces::WrapPixels(*native_info, pixels, rowBytes, as_surface_props(surfaceProps))) : 0;
}

sk_surface_t SkSurfaces_WrapPixelsWithPixmap(const reskia_pixmap_t *pm, const reskia_surface_props_t *props) {
    const SkPixmap *native_pixmap = as_pixmap(pm);
    return native_pixmap != nullptr ? make_surface_handle(SkSurfaces::WrapPixels(*native_pixmap, as_surface_props(props))) : 0;
}

sk_surface_t SkSurfaces_WrapPixelsWithReleaseProcAndContext(const reskia_image_info_t *imageInfo, void *pixels, size_t rowBytes, void(* pixelsReleaseProc)(void *, void *), void *context, const reskia_surface_props_t *surfaceProps) {
    const SkImageInfo *native_info = as_image_info(imageInfo);
    return native_info != nullptr && pixels != nullptr ? make_surface_handle(SkSurfaces::WrapPixels(*native_info, pixels, rowBytes, pixelsReleaseProc, context, as_surface_props(surfaceProps))) : 0;
}

}
