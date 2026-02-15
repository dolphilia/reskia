//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_IMAGES_H
#define RAIA_SKIA_SK_IMAGES_H

#include <stddef.h>

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

int SkImages_RasterFromBitmap(const reskia_bitmap_t *bitmap); // (const SkBitmap *bitmap) -> sk_image_t
int SkImages_RasterFromCompressedTextureData(int data, int width, int height, int type); // (sk_data_t data, int width, int height, SkTextureCompressionType type) -> sk_image_t
int SkImages_DeferredFromEncodedData(int data); // (sk_data_t data) -> sk_image_t
int SkImages_DeferredFromGenerator(int image_generator); // (sk_image_generator_t image_generator) -> sk_image_t
int SkImages_DeferredFromPicture(int picture, const reskia_i_size_t *dimensions, const reskia_matrix_t *matrix, const reskia_paint_t *paint, int bitDepth, int color_space, int props); // (sk_picture_t picture, const SkISize *dimensions, const SkMatrix *matrix, const SkPaint *paint, SkImages::BitDepth bitDepth, sk_color_space_t color_space, sk_surface_props_t props) -> sk_image_t
int SkImages_DeferredFromPicture_2(int picture, const reskia_i_size_t *dimensions, const reskia_matrix_t *matrix, const reskia_paint_t *paint, int bitDepth, int color_space); // (sk_picture_t picture, const SkISize *dimensions, const SkMatrix *matrix, const SkPaint *paint, SkImages::BitDepth bitDepth, sk_color_space_t color_space) -> sk_image_t
int SkImages_RasterFromPixmapCopy(const reskia_pixmap_t *pixmap); // (const SkPixmap *pixmap) -> sk_image_t
int SkImages_RasterFromPixmap(const reskia_pixmap_t *pixmap, void (*rasterReleaseProc)(const void *, void *), void *releaseContext); // (const SkPixmap *pixmap, SkImages::RasterReleaseProc rasterReleaseProc, SkImages::ReleaseContext releaseContext) -> sk_image_t
int SkImages_RasterFromData(const reskia_image_info_t *info, int data, size_t rowBytes); // (const SkImageInfo *info, sk_data_t data, size_t rowBytes) -> sk_image_t
int SkImages_MakeWithFilter(int image, const reskia_image_filter_t *filter, const reskia_i_rect_t *subset, const reskia_i_rect_t *clipBounds, reskia_i_rect_t *outSubset, reskia_i_point_t *offset); // (sk_image_t image, const SkImageFilter *filter, const SkIRect *subset, const SkIRect *clipBounds, SkIRect *outSubset, SkIPoint *offset) -> sk_image_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_IMAGES_H
