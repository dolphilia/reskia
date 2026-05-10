//
// Created by dolphilia on 2024/01/08.
//

#include "sk_images.h"

#include <utility>

#include "include/core/SkImage.h"
#include "include/core/SkSurfaceProps.h"

#include "../handles/static_sk_image.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_picture.h"
#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_image_generator.h"
#include "../handles/static_sk_surface_props.h"

#include "../handles/static_sk_image_generator-internal.h"
#include "../handles/static_sk_picture-internal.h"
#include "../handles/static_sk_surface_props-internal.h"
#include "../handles/static_sk_image-internal.h"
#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_color_space-internal.h"

namespace {

sk_image_t make_image_handle(sk_sp<SkImage> image) {
    return image ? static_sk_image_make(std::move(image)) : 0;
}

const SkBitmap *as_bitmap(const reskia_bitmap_t *bitmap) {
    return reinterpret_cast<const SkBitmap *>(bitmap);
}

const SkISize *as_i_size(const reskia_i_size_t *size) {
    return reinterpret_cast<const SkISize *>(size);
}

const SkPixmap *as_pixmap(const reskia_pixmap_t *pixmap) {
    return reinterpret_cast<const SkPixmap *>(pixmap);
}

const SkImageInfo *as_image_info(const reskia_image_info_t *info) {
    return reinterpret_cast<const SkImageInfo *>(info);
}

} // namespace

extern "C" {

sk_image_t SkImages_RasterFromBitmap(const reskia_bitmap_t *bitmap) {
    const SkBitmap *native = as_bitmap(bitmap);
    return native != nullptr ? make_image_handle(SkImages::RasterFromBitmap(*native)) : 0;
}

sk_image_t SkImages_RasterFromCompressedTextureData(sk_data_t data, int width, int height, reskia_images_texture_compression_type_t type) {
    return make_image_handle(SkImages::RasterFromCompressedTextureData(static_sk_data_get_entity(data), width, height, static_cast<SkTextureCompressionType>(type)));
}

sk_image_t SkImages_DeferredFromEncodedData(sk_data_t data) {
    return make_image_handle(SkImages::DeferredFromEncodedData(static_sk_data_get_entity(data)));
}

sk_image_t SkImages_DeferredFromGenerator(sk_image_generator_t image_generator) {
    return make_image_handle(SkImages::DeferredFromGenerator(static_sk_image_generator_take_entity(image_generator)));
}

sk_image_t SkImages_DeferredFromPicture(sk_picture_t picture, const reskia_i_size_t *dimensions, const reskia_matrix_t *matrix, const reskia_paint_t *paint, reskia_images_bit_depth_t bitDepth, sk_color_space_t color_space, sk_surface_props_t props) {
    const SkISize *native_dimensions = as_i_size(dimensions);
    if (native_dimensions == nullptr) {
        return 0;
    }
    return make_image_handle(SkImages::DeferredFromPicture(static_sk_picture_get_entity(picture), *native_dimensions, reinterpret_cast<const SkMatrix *>(matrix), reinterpret_cast<const SkPaint *>(paint), static_cast<SkImages::BitDepth>(bitDepth), static_sk_color_space_get_entity(color_space), static_sk_surface_props_get_entity(props)));
}

sk_image_t SkImages_DeferredFromPictureWithoutProps(sk_picture_t picture, const reskia_i_size_t *dimensions, const reskia_matrix_t *matrix, const reskia_paint_t *paint, reskia_images_bit_depth_t bitDepth, sk_color_space_t color_space) {
    const SkISize *native_dimensions = as_i_size(dimensions);
    if (native_dimensions == nullptr) {
        return 0;
    }
    return make_image_handle(SkImages::DeferredFromPicture(static_sk_picture_get_entity(picture), *native_dimensions, reinterpret_cast<const SkMatrix *>(matrix), reinterpret_cast<const SkPaint *>(paint), static_cast<SkImages::BitDepth>(bitDepth), static_sk_color_space_get_entity(color_space)));
}

sk_image_t SkImages_RasterFromPixmapCopy(const reskia_pixmap_t *pixmap) {
    const SkPixmap *native = as_pixmap(pixmap);
    return native != nullptr ? make_image_handle(SkImages::RasterFromPixmapCopy(*native)) : 0;
}

sk_image_t SkImages_RasterFromPixmap(const reskia_pixmap_t *pixmap, void (*rasterReleaseProc)(const void *, void *), void *releaseContext) {
    const SkPixmap *native = as_pixmap(pixmap);
    return native != nullptr ? make_image_handle(SkImages::RasterFromPixmap(*native, rasterReleaseProc, releaseContext)) : 0;
}

sk_image_t SkImages_RasterFromData(const reskia_image_info_t *info, sk_data_t data, size_t rowBytes) {
    const SkImageInfo *native = as_image_info(info);
    return native != nullptr ? make_image_handle(SkImages::RasterFromData(*native, static_sk_data_get_entity(data), rowBytes)) : 0;
}

reskia_status_t SkImages_MakeWithFilter(sk_image_t image, const reskia_image_filter_t *filter, const reskia_i_rect_t *subset, const reskia_i_rect_t *clip_bounds, reskia_i_rect_t *out_subset, reskia_i_point_t *out_offset, sk_image_t *out_image) {
    if (out_image != nullptr) {
        *out_image = 0;
    }
    if (subset == nullptr || clip_bounds == nullptr || out_subset == nullptr || out_offset == nullptr || out_image == nullptr) {
        return RESKIA_STATUS_INVALID_ARGUMENT;
    }
    sk_sp<SkImage> image_with_filter = SkImages::MakeWithFilter(
        static_sk_image_get_entity(image),
        reinterpret_cast<const SkImageFilter *>(filter),
        *reinterpret_cast<const SkIRect *>(subset),
        *reinterpret_cast<const SkIRect *>(clip_bounds),
        reinterpret_cast<SkIRect *>(out_subset),
        reinterpret_cast<SkIPoint *>(out_offset)
    );
    if (image_with_filter == nullptr) {
        return RESKIA_STATUS_NOT_FOUND;
    }
    *out_image = static_sk_image_make(std::move(image_with_filter));
    return RESKIA_STATUS_OK;
}

}
