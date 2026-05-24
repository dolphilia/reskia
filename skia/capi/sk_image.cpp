//
// Created by dolphilia on 2024/01/08.
//

#include "sk_image.h"
#include "sk_async_read_result-internal.h"

#include <utility>

#include "include/core/SkImage.h"
#include "include/core/SkColorType.h"
#include "include/core/SkImageInfo.h"
#include "include/core/SkTileMode.h"
#if defined(GRAPHITE_TEST_UTILS)
#include "include/gpu/graphite/Recorder.h"
#endif

#include "../handles/static_sk_image.h"
#include "../handles/static_sk_shader.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_i_rect.h"
#include "../handles/static_sk_image_info.h"
#include "../handles/static_sk_image_required_properties.h"
#include "../handles/static_sk_i_size.h"

#include "../handles/static_sk_image-internal.h"
#include "../handles/static_sk_image_required_properties-internal.h"
#include "../handles/static_sk_i_rect-internal.h"
#include "../handles/static_sk_image_info-internal.h"
#include "../handles/static_sk_i_size-internal.h"
#include "../handles/static_sk_shader-internal.h"
#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_color_space-internal.h"

namespace {

sk_image_t make_image_handle(sk_sp<SkImage> image) {
    return image ? static_sk_image_make(std::move(image)) : 0;
}

sk_color_space_t make_color_space_handle(sk_sp<SkColorSpace> color_space) {
    return color_space ? static_sk_color_space_make(std::move(color_space)) : 0;
}

sk_data_t make_data_handle(sk_sp<SkData> data) {
    return data ? static_sk_data_make(std::move(data)) : 0;
}

bool has_i_size_handle(sk_i_size_t size) {
    return size != 0 && static_sk_i_size_get_ptr(size) != nullptr;
}

bool has_optional_color_space_handle(sk_color_space_t color_space) {
    return color_space == 0 || static_sk_color_space_get_ptr(color_space) != nullptr;
}

bool has_required_properties_handle(sk_image_required_properties_t properties) {
    return properties != 0 && static_sk_image_required_properties_get_ptr(properties) != nullptr;
}

bool has_valid_pixels(const reskia_image_info_t *info, const void *pixels, size_t rowBytes) {
    if (info == nullptr || pixels == nullptr) {
        return false;
    }
    return reinterpret_cast<const SkImageInfo *>(info)->validRowBytes(rowBytes);
}

bool valid_tile_mode(reskia_image_tile_mode_t mode) {
    return mode >= 0 && mode <= static_cast<reskia_image_tile_mode_t>(SkTileMode::kLastTileMode);
}

bool valid_caching_hint(reskia_image_caching_hint_t hint) {
    return hint == static_cast<reskia_image_caching_hint_t>(SkImage::kAllow_CachingHint) ||
           hint == static_cast<reskia_image_caching_hint_t>(SkImage::kDisallow_CachingHint);
}

bool valid_color_type(reskia_image_color_type_t colorType) {
    return colorType >= 0 && colorType <= static_cast<reskia_image_color_type_t>(kLastEnum_SkColorType);
}

bool valid_legacy_bitmap_mode(reskia_image_legacy_bitmap_mode_t mode) {
    return mode == static_cast<reskia_image_legacy_bitmap_mode_t>(SkImage::kRO_LegacyBitmapMode);
}

bool valid_rescale_gamma(reskia_image_rescale_gamma_t gamma) {
    return gamma == static_cast<reskia_image_rescale_gamma_t>(SkImage::RescaleGamma::kSrc) ||
           gamma == static_cast<reskia_image_rescale_gamma_t>(SkImage::RescaleGamma::kLinear);
}

bool valid_rescale_mode(reskia_image_rescale_mode_t mode) {
    return mode >= static_cast<reskia_image_rescale_mode_t>(SkImage::RescaleMode::kNearest) &&
           mode <= static_cast<reskia_image_rescale_mode_t>(SkImage::RescaleMode::kRepeatedCubic);
}

bool valid_yuv_color_space(reskia_image_yuv_color_space_t yuvColorSpace) {
    return yuvColorSpace >= 0 &&
           yuvColorSpace <= static_cast<reskia_image_yuv_color_space_t>(kLastEnum_SkYUVColorSpace);
}

}  // namespace

extern "C" {

void SkImage_release(reskia_image_t *image) {
    if (image == nullptr) {
        return;
    }
    reinterpret_cast<SkImage *>(image)->unref();
}

sk_image_info_t SkImage_imageInfo(reskia_image_t *image) {
    if (image == nullptr) {
        return 0;
    }
    return static_sk_image_info_make(reinterpret_cast<SkImage *>(image)->imageInfo());
}

int SkImage_width(reskia_image_t *image) {
    if (image == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkImage *>(image)->width();
}

int SkImage_height(reskia_image_t *image) {
    if (image == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkImage *>(image)->height();
}

sk_i_size_t SkImage_dimensions(reskia_image_t *image) {
    if (image == nullptr) {
        return 0;
    }
    return static_sk_i_size_make(reinterpret_cast<SkImage *>(image)->dimensions());
}

sk_i_rect_t SkImage_bounds(reskia_image_t *image) {
    if (image == nullptr) {
        return 0;
    }
    return static_sk_i_rect_make(reinterpret_cast<SkImage *>(image)->bounds());
}

reskia_u32_t SkImage_uniqueID(reskia_image_t *image) {
    if (image == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkImage *>(image)->uniqueID();
}

reskia_image_alpha_type_t SkImage_alphaType(reskia_image_t *image) {
    if (image == nullptr) {
        return 0;
    }
    return static_cast<reskia_image_alpha_type_t>(reinterpret_cast<SkImage *>(image)->alphaType());
}

reskia_image_color_type_t SkImage_colorType(reskia_image_t *image) {
    if (image == nullptr) {
        return 0;
    }
    return static_cast<reskia_image_color_type_t>(reinterpret_cast<SkImage *>(image)->colorType());
}

reskia_color_space_t *SkImage_colorSpace(reskia_image_t *image) {
    if (image == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_color_space_t *>(reinterpret_cast<SkImage *>(image)->colorSpace());
}

sk_color_space_t SkImage_refColorSpace(reskia_image_t *image) {
    if (image == nullptr) {
        return 0;
    }
    return make_color_space_handle(reinterpret_cast<SkImage *>(image)->refColorSpace());
}

bool SkImage_isAlphaOnly(reskia_image_t *image) {
    if (image == nullptr) {
        return false;
    }
    return reinterpret_cast<SkImage *>(image)->isAlphaOnly();
}

bool SkImage_isOpaque(reskia_image_t *image) {
    if (image == nullptr) {
        return false;
    }
    return reinterpret_cast<SkImage *>(image)->isOpaque();
}

sk_shader_t SkImage_makeShader(reskia_image_t *image, reskia_image_tile_mode_t tmx, reskia_image_tile_mode_t tmy, const reskia_sampling_options_t *sampling, const reskia_matrix_t *localMatrix) {
    if (image == nullptr || !valid_tile_mode(tmx) || !valid_tile_mode(tmy) || sampling == nullptr) {
        return 0;
    }
    return static_sk_shader_make(reinterpret_cast<SkImage *>(image)->makeShader(static_cast<SkTileMode>(tmx), static_cast<SkTileMode>(tmy), * reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkImage_makeShaderWithTileModesAndLocalMatrix(reskia_image_t *image, reskia_image_tile_mode_t tmx, reskia_image_tile_mode_t tmy, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm) {
    if (image == nullptr || !valid_tile_mode(tmx) || !valid_tile_mode(tmy) || sampling == nullptr || lm == nullptr) {
        return 0;
    }
    return static_sk_shader_make(reinterpret_cast<SkImage *>(image)->makeShader(static_cast<SkTileMode>(tmx), static_cast<SkTileMode>(tmy), * reinterpret_cast<const SkSamplingOptions *>(sampling), * reinterpret_cast<const SkMatrix *>(lm)));
}

sk_shader_t SkImage_makeShaderWithSamplingAndLocalMatrix(reskia_image_t *image, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm) {
    if (image == nullptr || sampling == nullptr || lm == nullptr) {
        return 0;
    }
    return static_sk_shader_make(reinterpret_cast<SkImage *>(image)->makeShader(* reinterpret_cast<const SkSamplingOptions *>(sampling), * reinterpret_cast<const SkMatrix *>(lm)));
}

sk_shader_t SkImage_makeShaderWithSampling(reskia_image_t *image, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm) {
    if (image == nullptr || sampling == nullptr) {
        return 0;
    }
    return static_sk_shader_make(reinterpret_cast<SkImage *>(image)->makeShader(* reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkMatrix *>(lm)));
}

sk_shader_t SkImage_makeRawShader(reskia_image_t *image, reskia_image_tile_mode_t tmx, reskia_image_tile_mode_t tmy, const reskia_sampling_options_t *sampling, const reskia_matrix_t *localMatrix) {
    if (image == nullptr || !valid_tile_mode(tmx) || !valid_tile_mode(tmy) || sampling == nullptr) {
        return 0;
    }
    return static_sk_shader_make(reinterpret_cast<SkImage *>(image)->makeRawShader(static_cast<SkTileMode>(tmx), static_cast<SkTileMode>(tmy), * reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkImage_makeRawShaderWithTileModesAndLocalMatrix(reskia_image_t *image, reskia_image_tile_mode_t tmx, reskia_image_tile_mode_t tmy, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm) {
    if (image == nullptr || !valid_tile_mode(tmx) || !valid_tile_mode(tmy) || sampling == nullptr || lm == nullptr) {
        return 0;
    }
    return static_sk_shader_make(reinterpret_cast<SkImage *>(image)->makeRawShader(static_cast<SkTileMode>(tmx), static_cast<SkTileMode>(tmy), * reinterpret_cast<const SkSamplingOptions *>(sampling), * reinterpret_cast<const SkMatrix *>(lm)));
}

sk_shader_t SkImage_makeRawShaderWithSamplingAndLocalMatrix(reskia_image_t *image, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm) {
    if (image == nullptr || sampling == nullptr || lm == nullptr) {
        return 0;
    }
    return static_sk_shader_make(reinterpret_cast<SkImage *>(image)->makeRawShader(* reinterpret_cast<const SkSamplingOptions *>(sampling), * reinterpret_cast<const SkMatrix *>(lm)));
}

sk_shader_t SkImage_makeRawShaderWithSampling(reskia_image_t *image, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm) {
    if (image == nullptr || sampling == nullptr) {
        return 0;
    }
    return static_sk_shader_make(reinterpret_cast<SkImage *>(image)->makeRawShader(* reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkMatrix *>(lm)));
}

bool SkImage_peekPixels(reskia_image_t *image, reskia_pixmap_t *pixmap) {
    if (image == nullptr || pixmap == nullptr) {
        return false;
    }
    return reinterpret_cast<SkImage *>(image)->peekPixels(reinterpret_cast<SkPixmap *>(pixmap));
}

bool SkImage_isTextureBacked(reskia_image_t *image) {
    if (image == nullptr) {
        return false;
    }
    return reinterpret_cast<SkImage *>(image)->isTextureBacked();
}

size_t SkImage_textureSize(reskia_image_t *image) {
    if (image == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkImage *>(image)->textureSize();
}

bool SkImage_isValid(reskia_image_t *image, reskia_recording_context_t *context) {
    if (image == nullptr) {
        return false;
    }
    return reinterpret_cast<SkImage *>(image)->isValid(reinterpret_cast<GrRecordingContext *>(context));
}

bool SkImage_readPixels(reskia_image_t *image, reskia_direct_context_t *context, const reskia_image_info_t *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY, reskia_image_caching_hint_t cachingHint) {
    if (image == nullptr || !has_valid_pixels(dstInfo, dstPixels, dstRowBytes) || !valid_caching_hint(cachingHint)) {
        return false;
    }
    return reinterpret_cast<SkImage *>(image)->readPixels(reinterpret_cast<GrDirectContext *>(context), * reinterpret_cast<const SkImageInfo *>(dstInfo), dstPixels, dstRowBytes, srcX, srcY, static_cast<SkImage::CachingHint>(cachingHint));
}

bool SkImage_readPixelsWithContextPixmap(reskia_image_t *image, reskia_direct_context_t *context, const reskia_pixmap_t *dst, int srcX, int srcY, reskia_image_caching_hint_t cachingHint) {
    if (image == nullptr || dst == nullptr || !valid_caching_hint(cachingHint)) {
        return false;
    }
    return reinterpret_cast<SkImage *>(image)->readPixels(reinterpret_cast<GrDirectContext *>(context), * reinterpret_cast<const SkPixmap *>(dst), srcX, srcY, static_cast<SkImage::CachingHint>(cachingHint));
}

bool SkImage_readPixelsGraphite(reskia_image_t *image, reskia_graphite_recorder_t *recorder, const reskia_pixmap_t *dst, int srcX, int srcY) {
#if defined(GRAPHITE_TEST_UTILS)
    if (image == nullptr || recorder == nullptr || dst == nullptr) {
        return false;
    }
    return reinterpret_cast<SkImage *>(image)->readPixelsGraphite(
            reinterpret_cast<skgpu::graphite::Recorder *>(recorder),
            *reinterpret_cast<const SkPixmap *>(dst),
            srcX,
            srcY);
#else
    (void) image;
    (void) recorder;
    (void) dst;
    (void) srcX;
    (void) srcY;
    return false;
#endif
}

bool SkImage_readPixelsWithImageInfo(reskia_image_t *image, const reskia_image_info_t *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY, reskia_image_caching_hint_t cachingHint) {
    if (image == nullptr || !has_valid_pixels(dstInfo, dstPixels, dstRowBytes) || !valid_caching_hint(cachingHint)) {
        return false;
    }
    return reinterpret_cast<SkImage *>(image)->readPixels(* reinterpret_cast<const SkImageInfo *>(dstInfo), dstPixels, dstRowBytes, srcX, srcY, static_cast<SkImage::CachingHint>(cachingHint));
}

bool SkImage_readPixelsWithPixmap(reskia_image_t *image, const reskia_pixmap_t *dst, int srcX, int srcY, reskia_image_caching_hint_t cachingHint) {
    if (image == nullptr || dst == nullptr || !valid_caching_hint(cachingHint)) {
        return false;
    }
    return reinterpret_cast<SkImage *>(image)->readPixels(* reinterpret_cast<const SkPixmap *>(dst), srcX, srcY, static_cast<SkImage::CachingHint>(cachingHint));
}

void SkImage_asyncRescaleAndReadPixels(reskia_image_t *image, const reskia_image_info_t *info, const reskia_i_rect_t *srcRect, reskia_image_rescale_gamma_t rescaleGamma, reskia_image_rescale_mode_t rescaleMode, reskia_async_read_pixels_callback_t callback, void *context) {
    if (!image || !info || !srcRect || !callback || !valid_rescale_gamma(rescaleGamma) || !valid_rescale_mode(rescaleMode)) {
        reskia_async_read_pixels_fail(callback, context);
        return;
    }
    reinterpret_cast<SkImage *>(image)->asyncRescaleAndReadPixels(
            *reinterpret_cast<const SkImageInfo *>(info),
            *reinterpret_cast<const SkIRect *>(srcRect),
            static_cast<SkImage::RescaleGamma>(rescaleGamma),
            static_cast<SkImage::RescaleMode>(rescaleMode),
            reskia_async_read_pixels_bridge,
            reskia_async_read_callback_context_new(callback, context));
}

void SkImage_asyncRescaleAndReadPixelsYUV420(reskia_image_t *image, reskia_image_yuv_color_space_t yuvColorSpace, sk_color_space_t color_space, const reskia_i_rect_t *srcRect, sk_i_size_t dstSize, reskia_image_rescale_gamma_t rescaleGamma, reskia_image_rescale_mode_t rescaleMode, reskia_async_read_pixels_callback_t callback, void *context) {
    if (!image || !srcRect || !has_i_size_handle(dstSize) || !callback || !valid_yuv_color_space(yuvColorSpace) || !valid_rescale_gamma(rescaleGamma) || !valid_rescale_mode(rescaleMode)) {
        reskia_async_read_pixels_fail(callback, context);
        return;
    }
    reinterpret_cast<SkImage *>(image)->asyncRescaleAndReadPixelsYUV420(
            static_cast<SkYUVColorSpace>(yuvColorSpace),
            static_sk_color_space_get_entity(color_space),
            *reinterpret_cast<const SkIRect *>(srcRect),
            static_sk_i_size_get_entity(dstSize),
            static_cast<SkImage::RescaleGamma>(rescaleGamma),
            static_cast<SkImage::RescaleMode>(rescaleMode),
            reskia_async_read_pixels_bridge,
            reskia_async_read_callback_context_new(callback, context));
}

void SkImage_asyncRescaleAndReadPixelsYUVA420(reskia_image_t *image, reskia_image_yuv_color_space_t yuvColorSpace, sk_color_space_t color_space, const reskia_i_rect_t *srcRect, sk_i_size_t dstSize, reskia_image_rescale_gamma_t rescaleGamma, reskia_image_rescale_mode_t rescaleMode, reskia_async_read_pixels_callback_t callback, void *context) {
    if (!image || !srcRect || !has_i_size_handle(dstSize) || !callback || !valid_yuv_color_space(yuvColorSpace) || !valid_rescale_gamma(rescaleGamma) || !valid_rescale_mode(rescaleMode)) {
        reskia_async_read_pixels_fail(callback, context);
        return;
    }
    reinterpret_cast<SkImage *>(image)->asyncRescaleAndReadPixelsYUVA420(
            static_cast<SkYUVColorSpace>(yuvColorSpace),
            static_sk_color_space_get_entity(color_space),
            *reinterpret_cast<const SkIRect *>(srcRect),
            static_sk_i_size_get_entity(dstSize),
            static_cast<SkImage::RescaleGamma>(rescaleGamma),
            static_cast<SkImage::RescaleMode>(rescaleMode),
            reskia_async_read_pixels_bridge,
            reskia_async_read_callback_context_new(callback, context));
}

bool SkImage_scalePixels(reskia_image_t *image, const reskia_pixmap_t *dst, const reskia_sampling_options_t *sampling, reskia_image_caching_hint_t cachingHint) {
    if (image == nullptr || dst == nullptr || sampling == nullptr || !valid_caching_hint(cachingHint)) {
        return false;
    }
    return reinterpret_cast<SkImage *>(image)->scalePixels(* reinterpret_cast<const SkPixmap *>(dst), * reinterpret_cast<const SkSamplingOptions *>(sampling), static_cast<SkImage::CachingHint>(cachingHint));
}

sk_image_t SkImage_makeScaled(reskia_image_t *image, const reskia_image_info_t *info, const reskia_sampling_options_t *sampling) {
    if (image == nullptr || info == nullptr || sampling == nullptr) {
        return 0;
    }
    return make_image_handle(reinterpret_cast<SkImage *>(image)->makeScaled(
            *reinterpret_cast<const SkImageInfo *>(info),
            *reinterpret_cast<const SkSamplingOptions *>(sampling)));
}

sk_image_t SkImage_makeScaledWithRecorder(reskia_image_t *image, reskia_graphite_recorder_t *recorder, const reskia_image_info_t *info, const reskia_sampling_options_t *sampling) {
    if (image == nullptr || info == nullptr || sampling == nullptr) {
        return 0;
    }
    return make_image_handle(reinterpret_cast<SkImage *>(image)->makeScaled(
            reinterpret_cast<skgpu::graphite::Recorder *>(recorder),
            *reinterpret_cast<const SkImageInfo *>(info),
            *reinterpret_cast<const SkSamplingOptions *>(sampling)));
}

sk_data_t SkImage_refEncodedData(reskia_image_t *image) {
    if (image == nullptr) {
        return 0;
    }
    return make_data_handle(reinterpret_cast<SkImage *>(image)->refEncodedData());
}

sk_image_t SkImage_makeSubset(reskia_image_t *image, reskia_direct_context_t *direct, const reskia_i_rect_t *subset) {
    if (image == nullptr || subset == nullptr) {
        return 0;
    }
    return make_image_handle(reinterpret_cast<SkImage *>(image)->makeSubset(reinterpret_cast<GrDirectContext *>(direct), * reinterpret_cast<const SkIRect *>(subset)));
}

sk_image_t SkImage_makeSubsetWithRecorder(reskia_image_t *image, reskia_graphite_recorder_t *recorder, const reskia_i_rect_t *subset, sk_image_required_properties_t properties) {
    if (image == nullptr || recorder == nullptr || subset == nullptr || !has_required_properties_handle(properties)) {
        return 0;
    }
    return make_image_handle(reinterpret_cast<SkImage *>(image)->makeSubset(reinterpret_cast<skgpu::graphite::Recorder *>(recorder), * reinterpret_cast<const SkIRect *>(subset), static_sk_image_required_properties_get_entity(properties)));
}

bool SkImage_hasMipmaps(reskia_image_t *image) {
    if (image == nullptr) {
        return false;
    }
    return reinterpret_cast<SkImage *>(image)->hasMipmaps();
}

bool SkImage_isProtected(reskia_image_t *image) {
    if (image == nullptr) {
        return false;
    }
    return reinterpret_cast<SkImage *>(image)->isProtected();
}

sk_image_t SkImage_withDefaultMipmaps(reskia_image_t *image) {
    if (image == nullptr) {
        return 0;
    }
    return make_image_handle(reinterpret_cast<SkImage *>(image)->withDefaultMipmaps());
}

sk_image_t SkImage_makeNonTextureImage(reskia_image_t *image, reskia_direct_context_t *context) {
    if (image == nullptr) {
        return 0;
    }
    return make_image_handle(reinterpret_cast<SkImage *>(image)->makeNonTextureImage(reinterpret_cast<GrDirectContext *>(context)));
}

sk_image_t SkImage_makeRasterImage(reskia_image_t *image, reskia_direct_context_t *context, reskia_image_caching_hint_t cachingHint) {
    if (image == nullptr || !valid_caching_hint(cachingHint)) {
        return 0;
    }
    return make_image_handle(reinterpret_cast<SkImage *>(image)->makeRasterImage(reinterpret_cast<GrDirectContext *>(context), static_cast<SkImage::CachingHint>(cachingHint)));
}

sk_image_t SkImage_makeRasterImageWithoutContext(reskia_image_t *image, reskia_image_caching_hint_t cachingHint) {
    if (image == nullptr || !valid_caching_hint(cachingHint)) {
        return 0;
    }
    return make_image_handle(reinterpret_cast<SkImage *>(image)->makeRasterImage(static_cast<SkImage::CachingHint>(cachingHint)));
}

bool SkImage_asLegacyBitmap(reskia_image_t *image, reskia_bitmap_t *bitmap, reskia_image_legacy_bitmap_mode_t legacyBitmapMode) {
    if (image == nullptr || bitmap == nullptr || !valid_legacy_bitmap_mode(legacyBitmapMode)) {
        return false;
    }
    return reinterpret_cast<SkImage *>(image)->asLegacyBitmap(reinterpret_cast<SkBitmap *>(bitmap), static_cast<SkImage::LegacyBitmapMode>(legacyBitmapMode));
}

bool SkImage_isLazyGenerated(reskia_image_t *image) {
    if (image == nullptr) {
        return false;
    }
    return reinterpret_cast<SkImage *>(image)->isLazyGenerated();
}

sk_image_t SkImage_makeColorSpace(reskia_image_t *image, reskia_direct_context_t *direct, sk_color_space_t color_space) {
    if (image == nullptr || !has_optional_color_space_handle(color_space)) {
        return 0;
    }
    return make_image_handle(reinterpret_cast<SkImage *>(image)->makeColorSpace(reinterpret_cast<GrDirectContext *>(direct), static_sk_color_space_get_entity(color_space)));
}

sk_image_t SkImage_makeColorSpaceWithRecorder(reskia_image_t *image, reskia_graphite_recorder_t *recorder, sk_color_space_t color_space, sk_image_required_properties_t properties) {
    if (image == nullptr || recorder == nullptr || !has_optional_color_space_handle(color_space) || !has_required_properties_handle(properties)) {
        return 0;
    }
    return make_image_handle(reinterpret_cast<SkImage *>(image)->makeColorSpace(reinterpret_cast<skgpu::graphite::Recorder *>(recorder), static_sk_color_space_get_entity(color_space), static_sk_image_required_properties_get_entity(properties)));
}

sk_image_t SkImage_makeColorTypeAndColorSpace(reskia_image_t *image, reskia_direct_context_t *direct, reskia_image_color_type_t targetColorType, sk_color_space_t color_space) {
    if (image == nullptr || !valid_color_type(targetColorType) || !has_optional_color_space_handle(color_space)) {
        return 0;
    }
    return make_image_handle(reinterpret_cast<SkImage *>(image)->makeColorTypeAndColorSpace(reinterpret_cast<GrDirectContext *>(direct), static_cast<SkColorType>(targetColorType), static_sk_color_space_get_entity(color_space)));
}

sk_image_t SkImage_makeColorTypeAndColorSpaceWithRecorder(reskia_image_t *image, reskia_graphite_recorder_t *recorder, reskia_image_color_type_t targetColorType, sk_color_space_t color_space, sk_image_required_properties_t properties) {
    if (image == nullptr || recorder == nullptr || !valid_color_type(targetColorType) || !has_optional_color_space_handle(color_space) || !has_required_properties_handle(properties)) {
        return 0;
    }
    return make_image_handle(reinterpret_cast<SkImage *>(image)->makeColorTypeAndColorSpace(reinterpret_cast<skgpu::graphite::Recorder *>(recorder), static_cast<SkColorType>(targetColorType), static_sk_color_space_get_entity(color_space), static_sk_image_required_properties_get_entity(properties)));
}

sk_image_t SkImage_reinterpretColorSpace(reskia_image_t *image, sk_color_space_t color_space) {
    if (image == nullptr || !has_optional_color_space_handle(color_space)) {
        return 0;
    }
    return make_image_handle(reinterpret_cast<SkImage *>(image)->reinterpretColorSpace(static_sk_color_space_get_entity(color_space)));
}

bool SkImage_unique(reskia_image_t *image) {
    if (image == nullptr) {
        return false;
    }
    return reinterpret_cast<SkImage *>(image)->unique();
}

void SkImage_ref(reskia_image_t *image) {
    if (image == nullptr) {
        return;
    }
    return reinterpret_cast<SkImage *>(image)->ref();
}

void SkImage_unref(reskia_image_t *image) {
    if (image == nullptr) {
        return;
    }
    return reinterpret_cast<SkImage *>(image)->unref();
}

}
