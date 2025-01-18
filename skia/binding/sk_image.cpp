//
// Created by dolphilia on 2024/01/08.
//

#include "sk_image.h"

#include "include/core/SkImage.h"

#include "../static/static_sk_image.h"
#include "../static/static_sk_shader.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_color_space.h"
#include "../static/static_sk_i_rect.h"
#include "../static/static_sk_image_required_properties.h"
#include "../static/static_sk_i_size.h"

#include "../static/static_sk_image-internal.h"
#include "../static/static_sk_image_required_properties-internal.h"
#include "../static/static_sk_i_rect-internal.h"
#include "../static/static_sk_i_size-internal.h"
#include "../static/static_sk_shader-internal.h"
#include "../static/static_sk_data-internal.h"
#include "../static/static_sk_color_space-internal.h"

extern "C" {

void SkImage_delete(void *image) {
    delete static_cast<SkImage *>(image);
}

// TODO
// const void * SkImage_imageInfo(void *image) {
//     auto *info = static_cast<SkImageInfo *>(image);
//     return &info->imageInfo();
// }

int SkImage_width(void *image) {
    return static_cast<SkImage *>(image)->width();
}

int SkImage_height(void *image) {
    return static_cast<SkImage *>(image)->height();
}

sk_i_size_t SkImage_dimensions(void *image) {
    return static_sk_i_size_make(static_cast<SkImage *>(image)->dimensions());
}

sk_i_rect_t SkImage_bounds(void *image) {
    return static_sk_i_rect_make(static_cast<SkImage *>(image)->bounds());
}

uint32_t SkImage_uniqueID(void *image) {
    return static_cast<SkImage *>(image)->uniqueID();
}

int SkImage_alphaType(void *image) {
    return static_cast<SkImage *>(image)->alphaType();
}

int SkImage_colorType(void *image) {
    return static_cast<SkImage *>(image)->colorType();
}

void * SkImage_colorSpace(void *image) {
    return static_cast<SkImage *>(image)->colorSpace();
}

sk_color_space_t SkImage_refColorSpace(void *image) {
    return static_sk_color_space_make(static_cast<SkImage *>(image)->refColorSpace());
}

bool SkImage_isAlphaOnly(void *image) {
    return static_cast<SkImage *>(image)->isAlphaOnly();
}

bool SkImage_isOpaque(void *image) {
    return static_cast<SkImage *>(image)->isOpaque();
}

sk_shader_t SkImage_makeShader(void *image, int tmx, int tmy, const void *sampling, const void *localMatrix) {
    return static_sk_shader_make(static_cast<SkImage *>(image)->makeShader(static_cast<SkTileMode>(tmx), static_cast<SkTileMode>(tmy), * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkImage_makeShader_2(void *image, int tmx, int tmy, const void *sampling, const void *lm) {
    return static_sk_shader_make(static_cast<SkImage *>(image)->makeShader(static_cast<SkTileMode>(tmx), static_cast<SkTileMode>(tmy), * static_cast<const SkSamplingOptions *>(sampling), * static_cast<const SkMatrix *>(lm)));
}

sk_shader_t SkImage_makeShader_3(void *image, const void *sampling, const void *lm) {
    return static_sk_shader_make(static_cast<SkImage *>(image)->makeShader(* static_cast<const SkSamplingOptions *>(sampling), * static_cast<const SkMatrix *>(lm)));
}

sk_shader_t SkImage_makeShader_4(void *image, const void *sampling, const void *lm) {
    return static_sk_shader_make(static_cast<SkImage *>(image)->makeShader(* static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkMatrix *>(lm)));
}

sk_shader_t SkImage_makeRawShader(void *image, int tmx, int tmy, const void * sampling, const void *localMatrix) {
    return static_sk_shader_make(static_cast<SkImage *>(image)->makeRawShader(static_cast<SkTileMode>(tmx), static_cast<SkTileMode>(tmy), * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkImage_makeRawShader_2(void *image, int tmx, int tmy, const void *sampling, const void *lm) {
    return static_sk_shader_make(static_cast<SkImage *>(image)->makeRawShader(static_cast<SkTileMode>(tmx), static_cast<SkTileMode>(tmy), * static_cast<const SkSamplingOptions *>(sampling), * static_cast<const SkMatrix *>(lm)));
}

sk_shader_t SkImage_makeRawShader_3(void *image, const void *sampling, const void *lm) {
    return static_sk_shader_make(static_cast<SkImage *>(image)->makeRawShader(* static_cast<const SkSamplingOptions *>(sampling), * static_cast<const SkMatrix *>(lm)));
}

sk_shader_t SkImage_makeRawShader_4(void *image, const void *sampling, const void *lm) {
    return static_sk_shader_make(static_cast<SkImage *>(image)->makeRawShader(* static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkMatrix *>(lm)));
}

bool SkImage_peekPixels(void *image, void *pixmap) {
    return static_cast<SkImage *>(image)->peekPixels(static_cast<SkPixmap *>(pixmap));
}

bool SkImage_isTextureBacked(void *image) {
    return static_cast<SkImage *>(image)->isTextureBacked();
}

size_t SkImage_textureSize(void *image) {
    return static_cast<SkImage *>(image)->textureSize();
}

bool SkImage_isValid(void *image, void *context) {
    return static_cast<SkImage *>(image)->isValid(static_cast<GrRecordingContext *>(context));
}

bool SkImage_readPixels(void *image, void *context, const void *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY, int cachingHint) {
    return static_cast<SkImage *>(image)->readPixels(static_cast<GrDirectContext *>(context), * static_cast<const SkImageInfo *>(dstInfo), dstPixels, dstRowBytes, srcX, srcY, static_cast<SkImage::CachingHint>(cachingHint));
}

bool SkImage_readPixels_2(void *image, void *context, const void *dst, int srcX, int srcY, int cachingHint) {
    return static_cast<SkImage *>(image)->readPixels(static_cast<GrDirectContext *>(context), * static_cast<const SkPixmap *>(dst), srcX, srcY, static_cast<SkImage::CachingHint>(cachingHint));
}

bool SkImage_readPixels_3(void *image, const void *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY, int cachingHint) {
    return static_cast<SkImage *>(image)->readPixels(* static_cast<const SkImageInfo *>(dstInfo), dstPixels, dstRowBytes, srcX, srcY, static_cast<SkImage::CachingHint>(cachingHint));
}

bool SkImage_readPixels_4(void *image, const void *dst, int srcX, int srcY, int cachingHint) {
    return static_cast<SkImage *>(image)->readPixels(* static_cast<const SkPixmap *>(dst), srcX, srcY, static_cast<SkImage::CachingHint>(cachingHint));
}

// TODO
//
// void SkImage_asyncRescaleAndReadPixels(void *image, const void *info, const void *srcRect, int rescaleGamma, int rescaleMode, SkImage::ReadPixelsCallback callback, void * context) {
//     static_cast<SkImage *>(image)->asyncRescaleAndReadPixels(* static_cast<const SkImageInfo *>(info), * static_cast<const SkIRect *>(srcRect), static_cast<SkImage::RescaleGamma>(rescaleGamma), static_cast<SkImage::RescaleMode>(rescaleMode), callback, context);
// }
//
// void SkImage_asyncRescaleAndReadPixelsYUV420(void *image, int yuvColorSpace, sk_color_space_t color_space, const void *srcRect, const void *dstSize, int rescaleGamma, int rescaleMode, SkImage::ReadPixelsCallback callback, void * context) {
//     static_cast<SkImage *>(image)->asyncRescaleAndReadPixelsYUV420(static_cast<SkYUVColorSpace>(yuvColorSpace), static_sk_color_space_move(color_space), * static_cast<const SkIRect *>(srcRect), * static_cast<const SkISize *>(dstSize), static_cast<SkImage::RescaleGamma>(rescaleGamma), static_cast<SkImage::RescaleMode>(rescaleMode), callback, context);
// }
//
// void SkImage_asyncRescaleAndReadPixelsYUVA420(void *image, int yuvColorSpace, sk_color_space_t color_space, const void *srcRect, const void *dstSize, int rescaleGamma, int rescaleMode, SkImage::ReadPixelsCallback callback, void * context) {
//     static_cast<SkImage *>(image)->asyncRescaleAndReadPixelsYUVA420(static_cast<SkYUVColorSpace>(yuvColorSpace), static_sk_color_space_move(color_space), * static_cast<const SkIRect *>(srcRect), * static_cast<const SkISize *>(dstSize), static_cast<SkImage::RescaleGamma>(rescaleGamma), static_cast<SkImage::RescaleMode>(rescaleMode), callback, context);
// }

bool SkImage_scalePixels(void *image, const void *dst, const void *sampling, int cachingHint) {
    return static_cast<SkImage *>(image)->scalePixels(* static_cast<const SkPixmap *>(dst), * static_cast<const SkSamplingOptions *>(sampling), static_cast<SkImage::CachingHint>(cachingHint));
}

sk_data_t SkImage_refEncodedData(void *image) {
    return static_sk_data_make(static_cast<SkImage *>(image)->refEncodedData());
}

sk_image_t SkImage_makeSubset(void *image, void *direct, const void *subset) {
    return static_sk_image_make(static_cast<SkImage *>(image)->makeSubset(static_cast<GrDirectContext *>(direct), * static_cast<const SkIRect *>(subset)));
}

sk_image_t SkImage_makeSubset_2(void *image, void *recorder, const void *subset, sk_image_required_properties_t properties) {
    return static_sk_image_make(static_cast<SkImage *>(image)->makeSubset(static_cast<skgpu::graphite::Recorder *>(recorder), * static_cast<const SkIRect *>(subset), static_sk_image_required_properties_get(properties)));
}

bool SkImage_hasMipmaps(void *image) {
    return static_cast<SkImage *>(image)->hasMipmaps();
}

bool SkImage_isProtected(void *image) {
    return static_cast<SkImage *>(image)->isProtected();
}

sk_image_t SkImage_withDefaultMipmaps(void *image) {
    return static_sk_image_make(static_cast<SkImage *>(image)->withDefaultMipmaps());
}

sk_image_t SkImage_makeNonTextureImage(void *image, void *context) {
    return static_sk_image_make(static_cast<SkImage *>(image)->makeNonTextureImage(static_cast<GrDirectContext *>(context)));
}

sk_image_t SkImage_makeRasterImage(void *image, void *context, int cachingHint) {
    return static_sk_image_make(static_cast<SkImage *>(image)->makeRasterImage(static_cast<GrDirectContext *>(context), static_cast<SkImage::CachingHint>(cachingHint)));
}

sk_image_t SkImage_makeRasterImage_2(void *image, int cachingHint) {
    return static_sk_image_make(static_cast<SkImage *>(image)->makeRasterImage(static_cast<SkImage::CachingHint>(cachingHint)));
}

bool SkImage_asLegacyBitmap(void *image, void *bitmap, int legacyBitmapMode) {
    return static_cast<SkImage *>(image)->asLegacyBitmap(static_cast<SkBitmap *>(bitmap), static_cast<SkImage::LegacyBitmapMode>(legacyBitmapMode));
}

bool SkImage_isLazyGenerated(void *image) {
    return static_cast<SkImage *>(image)->isLazyGenerated();
}

sk_image_t SkImage_makeColorSpace(void *image, void *direct, sk_color_space_t color_space) {
    return static_sk_image_make(static_cast<SkImage *>(image)->makeColorSpace(static_cast<GrDirectContext *>(direct), static_sk_color_space_move(color_space)));
}

sk_image_t SkImage_makeColorSpace_2(void *image, void *recorder, sk_color_space_t color_space, sk_image_required_properties_t properties) {
    return static_sk_image_make(static_cast<SkImage *>(image)->makeColorSpace(static_cast<skgpu::graphite::Recorder *>(recorder), static_sk_color_space_move(color_space), static_sk_image_required_properties_get(properties)));
}

sk_image_t SkImage_makeColorTypeAndColorSpace(void *image, void *direct, int targetColorType, sk_color_space_t color_space) {
    return static_sk_image_make(static_cast<SkImage *>(image)->makeColorTypeAndColorSpace(static_cast<GrDirectContext *>(direct), static_cast<SkColorType>(targetColorType), static_sk_color_space_move(color_space)));
}

sk_image_t SkImage_makeColorTypeAndColorSpace_2(void *image, void *recorder, int targetColorType, sk_color_space_t color_space, sk_image_required_properties_t properties) {
    return static_sk_image_make(static_cast<SkImage *>(image)->makeColorTypeAndColorSpace(static_cast<skgpu::graphite::Recorder *>(recorder), static_cast<SkColorType>(targetColorType), static_sk_color_space_move(color_space), static_sk_image_required_properties_get(properties)));
}

sk_image_t SkImage_reinterpretColorSpace(void *image, sk_color_space_t color_space) {
    return static_sk_image_make(static_cast<SkImage *>(image)->reinterpretColorSpace(static_sk_color_space_move(color_space)));
}

bool SkImage_unique(void *image) {
    return static_cast<SkImage *>(image)->unique();
}

void SkImage_ref(void *image) {
    return static_cast<SkImage *>(image)->ref();
}

void SkImage_unref(void *image) {
    return static_cast<SkImage *>(image)->unref();
}

}
