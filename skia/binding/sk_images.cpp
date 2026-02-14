//
// Created by dolphilia on 2024/01/08.
//

#include "sk_images.h"

#include "include/core/SkImage.h"
#include "include/core/SkSurfaceProps.h"

#include "../static/static_sk_image.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_picture.h"
#include "../static/static_sk_color_space.h"
#include "../static/static_sk_image_generator.h"
#include "../static/static_sk_surface_props.h"

#include "../static/static_sk_image_generator-internal.h"
#include "../static/static_sk_picture-internal.h"
#include "../static/static_sk_surface_props-internal.h"
#include "../static/static_sk_image-internal.h"
#include "../static/static_sk_data-internal.h"
#include "../static/static_sk_color_space-internal.h"

extern "C" {

sk_image_t SkImages_RasterFromBitmap(const void *bitmap) {
    return static_sk_image_make(SkImages::RasterFromBitmap(* static_cast<const SkBitmap *>(bitmap)));
}

sk_image_t SkImages_RasterFromCompressedTextureData(sk_data_t data, int width, int height, int type) {
    return static_sk_image_make(SkImages::RasterFromCompressedTextureData(static_sk_data_get_entity(data), width, height, static_cast<SkTextureCompressionType>(type)));
}

sk_image_t SkImages_DeferredFromEncodedData(sk_data_t data) {
    return static_sk_image_make(SkImages::DeferredFromEncodedData(static_sk_data_get_entity(data)));
}

sk_image_t SkImages_DeferredFromGenerator(sk_image_generator_t image_generator) {
    return static_sk_image_make(SkImages::DeferredFromGenerator(static_sk_image_generator_take_entity(image_generator)));
}

sk_image_t SkImages_DeferredFromPicture(sk_picture_t picture, const void *dimensions, const void *matrix, const void *paint, int bitDepth, sk_color_space_t color_space, sk_surface_props_t props) {
    return static_sk_image_make(SkImages::DeferredFromPicture(static_sk_picture_get_entity(picture), * static_cast<const SkISize *>(dimensions), static_cast<const SkMatrix *>(matrix), static_cast<const SkPaint *>(paint), static_cast<SkImages::BitDepth>(bitDepth), static_sk_color_space_get_entity(color_space), static_sk_surface_props_get_entity(props)));
}

sk_image_t SkImages_DeferredFromPicture_2(sk_picture_t picture, const void *dimensions, const void *matrix, const void *paint, int bitDepth, sk_color_space_t color_space) {
    return static_sk_image_make(SkImages::DeferredFromPicture(static_sk_picture_get_entity(picture), * static_cast<const SkISize *>(dimensions), static_cast<const SkMatrix *>(matrix), static_cast<const SkPaint *>(paint), static_cast<SkImages::BitDepth>(bitDepth), static_sk_color_space_get_entity(color_space)));
}

sk_image_t SkImages_RasterFromPixmapCopy(const void *pixmap) {
    return static_sk_image_make(SkImages::RasterFromPixmapCopy(* static_cast<const SkPixmap *>(pixmap)));
}

sk_image_t SkImages_RasterFromPixmap(const void *pixmap, void (*rasterReleaseProc)(const void *, void *), void * releaseContext) {
    return static_sk_image_make(SkImages::RasterFromPixmap(* static_cast<const SkPixmap *>(pixmap), rasterReleaseProc, releaseContext));
}

sk_image_t SkImages_RasterFromData(const void *info, sk_data_t data, size_t rowBytes) {
    return static_sk_image_make(SkImages::RasterFromData(* static_cast<const SkImageInfo *>(info), static_sk_data_get_entity(data), rowBytes));
}

sk_image_t SkImages_MakeWithFilter(sk_image_t image, const void *filter, const void *subset, const void *clipBounds, void *outSubset, void *offset) {
    return static_sk_image_make(SkImages::MakeWithFilter(static_sk_image_get_entity(image), static_cast<const SkImageFilter *>(filter), * static_cast<const SkIRect *>(subset), * static_cast<const SkIRect *>(clipBounds), static_cast<SkIRect *>(outSubset), static_cast<SkIPoint *>(offset)));
}

}
