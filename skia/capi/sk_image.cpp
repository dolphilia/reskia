//
// Created by dolphilia on 2024/01/08.
//

#include "sk_image.h"

#include "include/core/SkImage.h"

#include "../handles/static_sk_image.h"
#include "../handles/static_sk_shader.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_i_rect.h"
#include "../handles/static_sk_image_required_properties.h"
#include "../handles/static_sk_i_size.h"

#include "../handles/static_sk_image-internal.h"
#include "../handles/static_sk_image_required_properties-internal.h"
#include "../handles/static_sk_i_rect-internal.h"
#include "../handles/static_sk_i_size-internal.h"
#include "../handles/static_sk_shader-internal.h"
#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_color_space-internal.h"

extern "C" {

void SkImage_release(reskia_image_t *image) {
    reinterpret_cast<SkImage *>(image)->unref();
}

// TODO
// const void * SkImage_imageInfo(void *image) {
//     auto *info = static_cast<SkImageInfo *>(image);
//     return &info->imageInfo();
// }

int SkImage_width(reskia_image_t *image) {
    return reinterpret_cast<SkImage *>(image)->width();
}

int SkImage_height(reskia_image_t *image) {
    return reinterpret_cast<SkImage *>(image)->height();
}

sk_i_size_t SkImage_dimensions(reskia_image_t *image) {
    return static_sk_i_size_make(reinterpret_cast<SkImage *>(image)->dimensions());
}

sk_i_rect_t SkImage_bounds(reskia_image_t *image) {
    return static_sk_i_rect_make(reinterpret_cast<SkImage *>(image)->bounds());
}

reskia_u32_t SkImage_uniqueID(reskia_image_t *image) {
    return reinterpret_cast<SkImage *>(image)->uniqueID();
}

reskia_image_alpha_type_t SkImage_alphaType(reskia_image_t *image) {
    return static_cast<reskia_image_alpha_type_t>(reinterpret_cast<SkImage *>(image)->alphaType());
}

reskia_image_color_type_t SkImage_colorType(reskia_image_t *image) {
    return static_cast<reskia_image_color_type_t>(reinterpret_cast<SkImage *>(image)->colorType());
}

reskia_color_space_t *SkImage_colorSpace(reskia_image_t *image) {
    return reinterpret_cast<reskia_color_space_t *>(reinterpret_cast<SkImage *>(image)->colorSpace());
}

sk_color_space_t SkImage_refColorSpace(reskia_image_t *image) {
    return static_sk_color_space_make(reinterpret_cast<SkImage *>(image)->refColorSpace());
}

bool SkImage_isAlphaOnly(reskia_image_t *image) {
    return reinterpret_cast<SkImage *>(image)->isAlphaOnly();
}

bool SkImage_isOpaque(reskia_image_t *image) {
    return reinterpret_cast<SkImage *>(image)->isOpaque();
}

sk_shader_t SkImage_makeShader(reskia_image_t *image, reskia_image_tile_mode_t tmx, reskia_image_tile_mode_t tmy, const reskia_sampling_options_t *sampling, const reskia_matrix_t *localMatrix) {
    return static_sk_shader_make(reinterpret_cast<SkImage *>(image)->makeShader(static_cast<SkTileMode>(tmx), static_cast<SkTileMode>(tmy), * reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkImage_makeShader_2(reskia_image_t *image, reskia_image_tile_mode_t tmx, reskia_image_tile_mode_t tmy, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm) {
    return static_sk_shader_make(reinterpret_cast<SkImage *>(image)->makeShader(static_cast<SkTileMode>(tmx), static_cast<SkTileMode>(tmy), * reinterpret_cast<const SkSamplingOptions *>(sampling), * reinterpret_cast<const SkMatrix *>(lm)));
}

sk_shader_t SkImage_makeShader_3(reskia_image_t *image, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm) {
    return static_sk_shader_make(reinterpret_cast<SkImage *>(image)->makeShader(* reinterpret_cast<const SkSamplingOptions *>(sampling), * reinterpret_cast<const SkMatrix *>(lm)));
}

sk_shader_t SkImage_makeShader_4(reskia_image_t *image, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm) {
    return static_sk_shader_make(reinterpret_cast<SkImage *>(image)->makeShader(* reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkMatrix *>(lm)));
}

sk_shader_t SkImage_makeRawShader(reskia_image_t *image, reskia_image_tile_mode_t tmx, reskia_image_tile_mode_t tmy, const reskia_sampling_options_t *sampling, const reskia_matrix_t *localMatrix) {
    return static_sk_shader_make(reinterpret_cast<SkImage *>(image)->makeRawShader(static_cast<SkTileMode>(tmx), static_cast<SkTileMode>(tmy), * reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkImage_makeRawShader_2(reskia_image_t *image, reskia_image_tile_mode_t tmx, reskia_image_tile_mode_t tmy, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm) {
    return static_sk_shader_make(reinterpret_cast<SkImage *>(image)->makeRawShader(static_cast<SkTileMode>(tmx), static_cast<SkTileMode>(tmy), * reinterpret_cast<const SkSamplingOptions *>(sampling), * reinterpret_cast<const SkMatrix *>(lm)));
}

sk_shader_t SkImage_makeRawShader_3(reskia_image_t *image, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm) {
    return static_sk_shader_make(reinterpret_cast<SkImage *>(image)->makeRawShader(* reinterpret_cast<const SkSamplingOptions *>(sampling), * reinterpret_cast<const SkMatrix *>(lm)));
}

sk_shader_t SkImage_makeRawShader_4(reskia_image_t *image, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm) {
    return static_sk_shader_make(reinterpret_cast<SkImage *>(image)->makeRawShader(* reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkMatrix *>(lm)));
}

bool SkImage_peekPixels(reskia_image_t *image, reskia_pixmap_t *pixmap) {
    return reinterpret_cast<SkImage *>(image)->peekPixels(reinterpret_cast<SkPixmap *>(pixmap));
}

bool SkImage_isTextureBacked(reskia_image_t *image) {
    return reinterpret_cast<SkImage *>(image)->isTextureBacked();
}

size_t SkImage_textureSize(reskia_image_t *image) {
    return reinterpret_cast<SkImage *>(image)->textureSize();
}

bool SkImage_isValid(reskia_image_t *image, reskia_recording_context_t *context) {
    return reinterpret_cast<SkImage *>(image)->isValid(reinterpret_cast<GrRecordingContext *>(context));
}

bool SkImage_readPixels(reskia_image_t *image, reskia_direct_context_t *context, const reskia_image_info_t *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY, reskia_image_caching_hint_t cachingHint) {
    return reinterpret_cast<SkImage *>(image)->readPixels(reinterpret_cast<GrDirectContext *>(context), * reinterpret_cast<const SkImageInfo *>(dstInfo), dstPixels, dstRowBytes, srcX, srcY, static_cast<SkImage::CachingHint>(cachingHint));
}

bool SkImage_readPixels_2(reskia_image_t *image, reskia_direct_context_t *context, const reskia_pixmap_t *dst, int srcX, int srcY, reskia_image_caching_hint_t cachingHint) {
    return reinterpret_cast<SkImage *>(image)->readPixels(reinterpret_cast<GrDirectContext *>(context), * reinterpret_cast<const SkPixmap *>(dst), srcX, srcY, static_cast<SkImage::CachingHint>(cachingHint));
}

bool SkImage_readPixels_3(reskia_image_t *image, const reskia_image_info_t *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY, reskia_image_caching_hint_t cachingHint) {
    return reinterpret_cast<SkImage *>(image)->readPixels(* reinterpret_cast<const SkImageInfo *>(dstInfo), dstPixels, dstRowBytes, srcX, srcY, static_cast<SkImage::CachingHint>(cachingHint));
}

bool SkImage_readPixels_4(reskia_image_t *image, const reskia_pixmap_t *dst, int srcX, int srcY, reskia_image_caching_hint_t cachingHint) {
    return reinterpret_cast<SkImage *>(image)->readPixels(* reinterpret_cast<const SkPixmap *>(dst), srcX, srcY, static_cast<SkImage::CachingHint>(cachingHint));
}

// TODO
//
// void SkImage_asyncRescaleAndReadPixels(void *image, const void *info, const void *srcRect, int rescaleGamma, int rescaleMode, SkImage::ReadPixelsCallback callback, void * context) {
//     reinterpret_cast<SkImage *>(image)->asyncRescaleAndReadPixels(* reinterpret_cast<const SkImageInfo *>(info), * reinterpret_cast<const SkIRect *>(srcRect), static_cast<SkImage::RescaleGamma>(rescaleGamma), static_cast<SkImage::RescaleMode>(rescaleMode), callback, context);
// }
//
// void SkImage_asyncRescaleAndReadPixelsYUV420(void *image, int yuvColorSpace, sk_color_space_t color_space, const void *srcRect, const void *dstSize, int rescaleGamma, int rescaleMode, SkImage::ReadPixelsCallback callback, void * context) {
//     reinterpret_cast<SkImage *>(image)->asyncRescaleAndReadPixelsYUV420(static_cast<SkYUVColorSpace>(yuvColorSpace), static_sk_color_space_move(color_space), * reinterpret_cast<const SkIRect *>(srcRect), * static_cast<const SkISize *>(dstSize), static_cast<SkImage::RescaleGamma>(rescaleGamma), static_cast<SkImage::RescaleMode>(rescaleMode), callback, context);
// }
//
// void SkImage_asyncRescaleAndReadPixelsYUVA420(void *image, int yuvColorSpace, sk_color_space_t color_space, const void *srcRect, const void *dstSize, int rescaleGamma, int rescaleMode, SkImage::ReadPixelsCallback callback, void * context) {
//     reinterpret_cast<SkImage *>(image)->asyncRescaleAndReadPixelsYUVA420(static_cast<SkYUVColorSpace>(yuvColorSpace), static_sk_color_space_move(color_space), * reinterpret_cast<const SkIRect *>(srcRect), * static_cast<const SkISize *>(dstSize), static_cast<SkImage::RescaleGamma>(rescaleGamma), static_cast<SkImage::RescaleMode>(rescaleMode), callback, context);
// }

bool SkImage_scalePixels(reskia_image_t *image, const reskia_pixmap_t *dst, const reskia_sampling_options_t *sampling, reskia_image_caching_hint_t cachingHint) {
    return reinterpret_cast<SkImage *>(image)->scalePixels(* reinterpret_cast<const SkPixmap *>(dst), * reinterpret_cast<const SkSamplingOptions *>(sampling), static_cast<SkImage::CachingHint>(cachingHint));
}

sk_data_t SkImage_refEncodedData(reskia_image_t *image) {
    return static_sk_data_make(reinterpret_cast<SkImage *>(image)->refEncodedData());
}

sk_image_t SkImage_makeSubset(reskia_image_t *image, reskia_direct_context_t *direct, const reskia_i_rect_t *subset) {
    return static_sk_image_make(reinterpret_cast<SkImage *>(image)->makeSubset(reinterpret_cast<GrDirectContext *>(direct), * reinterpret_cast<const SkIRect *>(subset)));
}

sk_image_t SkImage_makeSubset_2(reskia_image_t *image, reskia_graphite_recorder_t *recorder, const reskia_i_rect_t *subset, sk_image_required_properties_t properties) {
    return static_sk_image_make(reinterpret_cast<SkImage *>(image)->makeSubset(reinterpret_cast<skgpu::graphite::Recorder *>(recorder), * reinterpret_cast<const SkIRect *>(subset), static_sk_image_required_properties_get_entity(properties)));
}

bool SkImage_hasMipmaps(reskia_image_t *image) {
    return reinterpret_cast<SkImage *>(image)->hasMipmaps();
}

bool SkImage_isProtected(reskia_image_t *image) {
    return reinterpret_cast<SkImage *>(image)->isProtected();
}

sk_image_t SkImage_withDefaultMipmaps(reskia_image_t *image) {
    return static_sk_image_make(reinterpret_cast<SkImage *>(image)->withDefaultMipmaps());
}

sk_image_t SkImage_makeNonTextureImage(reskia_image_t *image, reskia_direct_context_t *context) {
    return static_sk_image_make(reinterpret_cast<SkImage *>(image)->makeNonTextureImage(reinterpret_cast<GrDirectContext *>(context)));
}

sk_image_t SkImage_makeRasterImage(reskia_image_t *image, reskia_direct_context_t *context, reskia_image_caching_hint_t cachingHint) {
    return static_sk_image_make(reinterpret_cast<SkImage *>(image)->makeRasterImage(reinterpret_cast<GrDirectContext *>(context), static_cast<SkImage::CachingHint>(cachingHint)));
}

sk_image_t SkImage_makeRasterImage_2(reskia_image_t *image, reskia_image_caching_hint_t cachingHint) {
    return static_sk_image_make(reinterpret_cast<SkImage *>(image)->makeRasterImage(static_cast<SkImage::CachingHint>(cachingHint)));
}

bool SkImage_asLegacyBitmap(reskia_image_t *image, reskia_bitmap_t *bitmap, reskia_image_legacy_bitmap_mode_t legacyBitmapMode) {
    return reinterpret_cast<SkImage *>(image)->asLegacyBitmap(reinterpret_cast<SkBitmap *>(bitmap), static_cast<SkImage::LegacyBitmapMode>(legacyBitmapMode));
}

bool SkImage_isLazyGenerated(reskia_image_t *image) {
    return reinterpret_cast<SkImage *>(image)->isLazyGenerated();
}

sk_image_t SkImage_makeColorSpace(reskia_image_t *image, reskia_direct_context_t *direct, sk_color_space_t color_space) {
    return static_sk_image_make(reinterpret_cast<SkImage *>(image)->makeColorSpace(reinterpret_cast<GrDirectContext *>(direct), static_sk_color_space_get_entity(color_space)));
}

sk_image_t SkImage_makeColorSpace_2(reskia_image_t *image, reskia_graphite_recorder_t *recorder, sk_color_space_t color_space, sk_image_required_properties_t properties) {
    return static_sk_image_make(reinterpret_cast<SkImage *>(image)->makeColorSpace(reinterpret_cast<skgpu::graphite::Recorder *>(recorder), static_sk_color_space_get_entity(color_space), static_sk_image_required_properties_get_entity(properties)));
}

sk_image_t SkImage_makeColorTypeAndColorSpace(reskia_image_t *image, reskia_direct_context_t *direct, reskia_image_color_type_t targetColorType, sk_color_space_t color_space) {
    return static_sk_image_make(reinterpret_cast<SkImage *>(image)->makeColorTypeAndColorSpace(reinterpret_cast<GrDirectContext *>(direct), static_cast<SkColorType>(targetColorType), static_sk_color_space_get_entity(color_space)));
}

sk_image_t SkImage_makeColorTypeAndColorSpace_2(reskia_image_t *image, reskia_graphite_recorder_t *recorder, reskia_image_color_type_t targetColorType, sk_color_space_t color_space, sk_image_required_properties_t properties) {
    return static_sk_image_make(reinterpret_cast<SkImage *>(image)->makeColorTypeAndColorSpace(reinterpret_cast<skgpu::graphite::Recorder *>(recorder), static_cast<SkColorType>(targetColorType), static_sk_color_space_get_entity(color_space), static_sk_image_required_properties_get_entity(properties)));
}

sk_image_t SkImage_reinterpretColorSpace(reskia_image_t *image, sk_color_space_t color_space) {
    return static_sk_image_make(reinterpret_cast<SkImage *>(image)->reinterpretColorSpace(static_sk_color_space_get_entity(color_space)));
}

bool SkImage_unique(reskia_image_t *image) {
    return reinterpret_cast<SkImage *>(image)->unique();
}

void SkImage_ref(reskia_image_t *image) {
    return reinterpret_cast<SkImage *>(image)->ref();
}

void SkImage_unref(reskia_image_t *image) {
    return reinterpret_cast<SkImage *>(image)->unref();
}

}
