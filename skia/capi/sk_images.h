//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_IMAGES_H
#define RAIA_SKIA_SK_IMAGES_H

#include <stddef.h>
#include <stdint.h>

#include "reskia_status.h"
#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_image.h"
#include "../handles/static_sk_image_generator.h"
#include "../handles/static_sk_picture.h"
#include "../handles/static_sk_surface_props.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_bitmap_t reskia_bitmap_t;
typedef struct reskia_i_point_t reskia_i_point_t;
typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_i_size_t reskia_i_size_t;
typedef struct reskia_image_filter_t reskia_image_filter_t;
typedef struct reskia_image_info_t reskia_image_info_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_paint_t reskia_paint_t;
typedef struct reskia_pixmap_t reskia_pixmap_t;
typedef int32_t reskia_images_texture_compression_type_t;
typedef int32_t reskia_images_bit_depth_t;

sk_image_t SkImages_RasterFromBitmap(const reskia_bitmap_t *bitmap); // bitmap must be non-NULL. Returns 0 if creation fails. (const SkBitmap *bitmap) -> sk_image_t
sk_image_t SkImages_RasterFromCompressedTextureData(sk_data_t data, int width, int height, reskia_images_texture_compression_type_t type); // invalid data or creation failure returns 0. (sk_data_t data, int width, int height, SkTextureCompressionType type) -> sk_image_t
sk_image_t SkImages_DeferredFromEncodedData(sk_data_t data); // invalid data or creation failure returns 0. (sk_data_t data) -> sk_image_t
sk_image_t SkImages_DeferredFromGenerator(sk_image_generator_t image_generator); // invalid generator or creation failure returns 0. Consumes the generator handle. (sk_image_generator_t image_generator) -> sk_image_t
/**
 * dimensions must be non-NULL. matrix and paint may be NULL. Invalid picture/props handles are treated as empty. Returns 0 if creation fails. (sk_picture_t picture, const SkISize *dimensions, const SkMatrix *matrix, const SkPaint *paint, SkImages::BitDepth bitDepth, sk_color_space_t color_space, sk_surface_props_t props) -> sk_image_t
 */
sk_image_t SkImages_DeferredFromPicture(sk_picture_t picture, const reskia_i_size_t *dimensions, const reskia_matrix_t *matrix, const reskia_paint_t *paint, reskia_images_bit_depth_t bitDepth, sk_color_space_t color_space, sk_surface_props_t props);
/**
 * dimensions must be non-NULL. matrix and paint may be NULL. Invalid picture or creation failure returns 0. (sk_picture_t picture, const SkISize *dimensions, const SkMatrix *matrix, const SkPaint *paint, SkImages::BitDepth bitDepth, sk_color_space_t color_space) -> sk_image_t
 */
sk_image_t SkImages_DeferredFromPictureWithoutProps(sk_picture_t picture, const reskia_i_size_t *dimensions, const reskia_matrix_t *matrix, const reskia_paint_t *paint, reskia_images_bit_depth_t bitDepth, sk_color_space_t color_space);
sk_image_t SkImages_RasterFromPixmapCopy(const reskia_pixmap_t *pixmap); // pixmap must be non-NULL. Returns 0 if creation fails. (const SkPixmap *pixmap) -> sk_image_t
/**
 * pixmap must be non-NULL. release proc/context may be NULL. Returns 0 if creation fails. (const SkPixmap *pixmap, SkImages::RasterReleaseProc rasterReleaseProc, SkImages::ReleaseContext releaseContext) -> sk_image_t
 */
sk_image_t SkImages_RasterFromPixmap(const reskia_pixmap_t *pixmap, void (*rasterReleaseProc)(const void *, void *), void *releaseContext);
/**
 * info must be non-NULL. Invalid data or creation failure returns 0. (const SkImageInfo *info, sk_data_t data, size_t rowBytes) -> sk_image_t
 */
sk_image_t SkImages_RasterFromData(const reskia_image_info_t *info, sk_data_t data, size_t rowBytes);
/**
 * subset, clip_bounds, out_subset, out_offset, and out_image must be non-NULL. On failure, out_image is set to 0.
 */
reskia_status_t SkImages_MakeWithFilter(sk_image_t image, const reskia_image_filter_t *filter, const reskia_i_rect_t *subset, const reskia_i_rect_t *clip_bounds, reskia_i_rect_t *out_subset, reskia_i_point_t *out_offset, sk_image_t *out_image);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_IMAGES_H
