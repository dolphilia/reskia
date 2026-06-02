//
// Created by dolphilia on 2024/01/13.
//

#ifndef RAIA_SKIA_SK_SURFACES_H
#define RAIA_SKIA_SK_SURFACES_H

#include <stddef.h>

#include "../handles/static_sk_surface.h"

typedef struct reskia_image_info_t reskia_image_info_t;
typedef struct reskia_pixmap_t reskia_pixmap_t;
typedef struct reskia_surface_props_t reskia_surface_props_t;

#ifdef __cplusplus
extern "C" {
#endif

sk_surface_t SkSurfaces_Null(int width, int height); // Returns 0 on creation failure. (int width, int height) -> sk_surface_t
/**
 * imageInfo must be non-NULL. surfaceProps may be NULL.
 * Returns 0 on creation failure.
 * (const SkImageInfo *imageInfo, size_t rowBytes, const SkSurfaceProps *surfaceProps) -> sk_surface_t
 */
sk_surface_t SkSurfaces_Raster(const reskia_image_info_t *imageInfo, size_t rowBytes, const reskia_surface_props_t *surfaceProps);
/**
 * imageInfo must be non-NULL. props may be NULL.
 * Returns 0 on creation failure.
 * (const SkImageInfo *imageInfo, const SkSurfaceProps *props) -> sk_surface_t
 */
sk_surface_t SkSurfaces_RasterWithoutRowBytes(const reskia_image_info_t *imageInfo, const reskia_surface_props_t *props);
/**
 * imageInfo and pixels must be non-NULL. surfaceProps may be NULL.
 * Returns 0 on creation failure.
 * (const SkImageInfo *imageInfo, void *pixels, size_t rowBytes, const SkSurfaceProps *surfaceProps) -> sk_surface_t
 */
sk_surface_t SkSurfaces_WrapPixels(const reskia_image_info_t *imageInfo, void *pixels, size_t rowBytes, const reskia_surface_props_t *surfaceProps);
/**
 * pm must be non-NULL. props may be NULL.
 * Returns 0 on creation failure.
 * (const SkPixmap *pm, const SkSurfaceProps *props) -> sk_surface_t
 */
sk_surface_t SkSurfaces_WrapPixelsWithPixmap(const reskia_pixmap_t *pm, const reskia_surface_props_t *props);
/**
 * imageInfo and pixels must be non-NULL. release proc, context, and surfaceProps may be NULL.
 * Returns 0 on creation failure.
 * (const SkImageInfo *imageInfo, void *pixels, size_t rowBytes, SkSurfaces::PixelsReleaseProc pixelsReleaseProc, void *context, const SkSurfaceProps *surfaceProps) -> sk_surface_t
 */
sk_surface_t SkSurfaces_WrapPixelsWithReleaseProcAndContext(const reskia_image_info_t *imageInfo, void *pixels, size_t rowBytes, void(* pixelsReleaseProc)(void *, void *), void *context, const reskia_surface_props_t *surfaceProps);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_SURFACES_H
