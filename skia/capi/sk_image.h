//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_IMAGE_H
#define RAIA_SKIA_SK_IMAGE_H

#include <stddef.h>
#include <stdint.h>
#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_i_rect.h"
#include "../handles/static_sk_i_size.h"
#include "../handles/static_sk_image.h"
#include "../handles/static_sk_image_required_properties.h"
#include "../handles/static_sk_shader.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_image_t reskia_image_t;
typedef struct reskia_bitmap_t reskia_bitmap_t;
typedef struct reskia_color_space_t reskia_color_space_t;
typedef struct reskia_direct_context_t reskia_direct_context_t;
typedef struct reskia_graphite_recorder_t reskia_graphite_recorder_t;
typedef struct reskia_image_info_t reskia_image_info_t;
typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_pixmap_t reskia_pixmap_t;
typedef struct reskia_recording_context_t reskia_recording_context_t;
typedef struct reskia_sampling_options_t reskia_sampling_options_t;
typedef uint32_t reskia_u32_t;
typedef int32_t reskia_image_alpha_type_t;
typedef int32_t reskia_image_color_type_t;
typedef int32_t reskia_image_tile_mode_t;
typedef int32_t reskia_image_caching_hint_t;
typedef int32_t reskia_image_legacy_bitmap_mode_t;

void SkImage_release(reskia_image_t *image); // owned: caller が保持する参照を release する (SkImage *image)

// TODO
// const void *SkImage_imageInfo(void *image); // (SkImage *image) -> const SkImageInfo *
int SkImage_width(reskia_image_t *image); // (SkImage *image) -> int
int SkImage_height(reskia_image_t *image); // (SkImage *image) -> int
sk_i_size_t SkImage_dimensions(reskia_image_t *image); // (SkImage *image) -> sk_i_size_t
sk_i_rect_t SkImage_bounds(reskia_image_t *image); // (SkImage *image) -> sk_i_rect_t
reskia_u32_t SkImage_uniqueID(reskia_image_t *image); // (SkImage *image) -> uint32_t
reskia_image_alpha_type_t SkImage_alphaType(reskia_image_t *image); // (SkImage *image) -> SkAlphaType
reskia_image_color_type_t SkImage_colorType(reskia_image_t *image); // (SkImage *image) -> SkColorType
reskia_color_space_t *SkImage_colorSpace(reskia_image_t *image); // borrowed: 解放不要の借用ポインタ (SkImage *image) -> SkColorSpace *
sk_color_space_t SkImage_refColorSpace(reskia_image_t *image); // (SkImage *image) -> sk_color_space_t
bool SkImage_isAlphaOnly(reskia_image_t *image); // (SkImage *image) -> bool
bool SkImage_isOpaque(reskia_image_t *image); // (SkImage *image) -> bool
sk_shader_t SkImage_makeShader(reskia_image_t *image, reskia_image_tile_mode_t tmx, reskia_image_tile_mode_t tmy, const reskia_sampling_options_t *sampling, const reskia_matrix_t *localMatrix); // (SkImage *image, SkTileMode tmx, SkTileMode tmy, const SkSamplingOptions *sampling, const SkMatrix *localMatrix) -> sk_shader_t
sk_shader_t SkImage_makeShader_2(reskia_image_t *image, reskia_image_tile_mode_t tmx, reskia_image_tile_mode_t tmy, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm); // (SkImage *image, SkTileMode tmx, SkTileMode tmy, const SkSamplingOptions *sampling, const SkMatrix *lm) -> sk_shader_t
sk_shader_t SkImage_makeShader_3(reskia_image_t *image, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm); // (SkImage *image, const SkSamplingOptions *sampling, const SkMatrix *lm) -> sk_shader_t
sk_shader_t SkImage_makeShader_4(reskia_image_t *image, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm); // (SkImage *image, const SkSamplingOptions *sampling, const SkMatrix *lm) -> sk_shader_t
sk_shader_t SkImage_makeRawShader(reskia_image_t *image, reskia_image_tile_mode_t tmx, reskia_image_tile_mode_t tmy, const reskia_sampling_options_t *sampling, const reskia_matrix_t *localMatrix); // (SkImage *image, SkTileMode tmx, SkTileMode tmy, const SkSamplingOptions *sampling, const SkMatrix *localMatrix) -> sk_shader_t
sk_shader_t SkImage_makeRawShader_2(reskia_image_t *image, reskia_image_tile_mode_t tmx, reskia_image_tile_mode_t tmy, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm); // (SkImage *image, SkTileMode tmx, SkTileMode tmy, const SkSamplingOptions *sampling, const SkMatrix *lm) -> sk_shader_t
sk_shader_t SkImage_makeRawShader_3(reskia_image_t *image, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm); // (SkImage *image, const SkSamplingOptions *sampling, const SkMatrix *lm) -> sk_shader_t
sk_shader_t SkImage_makeRawShader_4(reskia_image_t *image, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm); // (SkImage *image, const SkSamplingOptions *sampling, const SkMatrix *lm) -> sk_shader_t
bool SkImage_peekPixels(reskia_image_t *image, reskia_pixmap_t *pixmap); // (SkImage *image, SkPixmap *pixmap) -> bool
bool SkImage_isTextureBacked(reskia_image_t *image); // (SkImage *image) -> bool
size_t SkImage_textureSize(reskia_image_t *image); // (SkImage *image) -> size_t
bool SkImage_isValid(reskia_image_t *image, reskia_recording_context_t *context); // (SkImage *image, GrRecordingContext *context) -> bool
bool SkImage_readPixels(reskia_image_t *image, reskia_direct_context_t *context, const reskia_image_info_t *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY, reskia_image_caching_hint_t cachingHint); // (SkImage *image, GrDirectContext *context, const SkImageInfo *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY, SkImage::CachingHint cachingHint) -> bool
bool SkImage_readPixels_2(reskia_image_t *image, reskia_direct_context_t *context, const reskia_pixmap_t *dst, int srcX, int srcY, reskia_image_caching_hint_t cachingHint); // (SkImage *image, GrDirectContext *context, const SkPixmap *dst, int srcX, int srcY, SkImage::CachingHint cachingHint) -> bool
bool SkImage_readPixels_3(reskia_image_t *image, const reskia_image_info_t *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY, reskia_image_caching_hint_t cachingHint); // (SkImage *image, const SkImageInfo *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY, SkImage::CachingHint cachingHint) -> bool
bool SkImage_readPixels_4(reskia_image_t *image, const reskia_pixmap_t *dst, int srcX, int srcY, reskia_image_caching_hint_t cachingHint); // (SkImage *image, const SkPixmap *dst, int srcX, int srcY, SkImage::CachingHint cachingHint) -> bool

// TODO
// void SkImage_asyncRescaleAndReadPixels(void *image, const void *info, const void *srcRect, int rescaleGamma, int rescaleMode, SkImage::ReadPixelsCallback callback, void * context); // (SkImage *image, const SkImageInfo *info, const SkIRect *srcRect, SkImage::RescaleGamma rescaleGamma, SkImage::RescaleMode rescaleMode, SkImage::ReadPixelsCallback callback, SkImage::ReadPixelsContext context)
// void SkImage_asyncRescaleAndReadPixelsYUV420(void *image, int yuvColorSpace, sk_color_space_t color_space, const void *srcRect, const void *dstSize, int rescaleGamma, int rescaleMode, SkImage::ReadPixelsCallback callback, void * context); // (SkImage *image, SkYUVColorSpace yuvColorSpace, sk_color_space_t color_space, const SkIRect *srcRect, const SkISize *dstSize, SkImage::RescaleGamma rescaleGamma, SkImage::RescaleMode rescaleMode, SkImage::ReadPixelsCallback callback, SkImage::ReadPixelsContext context)
// void SkImage_asyncRescaleAndReadPixelsYUVA420(void *image, int yuvColorSpace, sk_color_space_t color_space, const void *srcRect, const void *dstSize, int rescaleGamma, int rescaleMode, SkImage::ReadPixelsCallback callback, void * context); // (SkImage *image, SkYUVColorSpace yuvColorSpace, sk_color_space_t color_space, const SkIRect *srcRect, const SkISize *dstSize, SkImage::RescaleGamma rescaleGamma, SkImage::RescaleMode rescaleMode, SkImage::ReadPixelsCallback callback, SkImage::ReadPixelsContext context)
bool SkImage_scalePixels(reskia_image_t *image, const reskia_pixmap_t *dst, const reskia_sampling_options_t *sampling, reskia_image_caching_hint_t cachingHint); // (SkImage *image, const SkPixmap *dst, const SkSamplingOptions *sampling, SkImage::CachingHint cachingHint) -> bool
sk_data_t SkImage_refEncodedData(reskia_image_t *image); // (SkImage *image) -> sk_data_t
sk_image_t SkImage_makeSubset(reskia_image_t *image, reskia_direct_context_t *direct, const reskia_i_rect_t *subset); // (SkImage *image, GrDirectContext *direct, const SkIRect *subset) -> sk_image_t
sk_image_t SkImage_makeSubset_2(reskia_image_t *image, reskia_graphite_recorder_t *recorder, const reskia_i_rect_t *subset, sk_image_required_properties_t properties); // (SkImage *image, skgpu::graphite::Recorder *recorder, const SkIRect *subset, sk_image_required_properties_t properties) -> sk_image_t
bool SkImage_hasMipmaps(reskia_image_t *image); // (SkImage *image) -> bool
bool SkImage_isProtected(reskia_image_t *image); // (SkImage *image) -> bool
sk_image_t SkImage_withDefaultMipmaps(reskia_image_t *image); // (SkImage *image) -> sk_image_t
sk_image_t SkImage_makeNonTextureImage(reskia_image_t *image, reskia_direct_context_t *context); // (SkImage *image, GrDirectContext *context) -> sk_image_t
sk_image_t SkImage_makeRasterImage(reskia_image_t *image, reskia_direct_context_t *context, reskia_image_caching_hint_t cachingHint); // (SkImage *image, GrDirectContext *context, SkImage::CachingHint cachingHint) -> sk_image_t
sk_image_t SkImage_makeRasterImage_2(reskia_image_t *image, reskia_image_caching_hint_t cachingHint); // (SkImage *image, SkImage::CachingHint cachingHint) -> sk_image_t
bool SkImage_asLegacyBitmap(reskia_image_t *image, reskia_bitmap_t *bitmap, reskia_image_legacy_bitmap_mode_t legacyBitmapMode); // (SkImage *image, SkBitmap *bitmap, SkImage::LegacyBitmapMode legacyBitmapMode) -> bool
bool SkImage_isLazyGenerated(reskia_image_t *image); // (SkImage *image) -> bool
sk_image_t SkImage_makeColorSpace(reskia_image_t *image, reskia_direct_context_t *direct, sk_color_space_t color_space); // (SkImage *image, GrDirectContext *direct, sk_color_space_t color_space) -> sk_image_t
sk_image_t SkImage_makeColorSpace_2(reskia_image_t *image, reskia_graphite_recorder_t *recorder, sk_color_space_t color_space, sk_image_required_properties_t properties); // (SkImage *image, skgpu::graphite::Recorder *recorder, sk_color_space_t color_space, sk_image_required_properties_t properties) -> sk_image_t
sk_image_t SkImage_makeColorTypeAndColorSpace(reskia_image_t *image, reskia_direct_context_t *direct, reskia_image_color_type_t targetColorType, sk_color_space_t color_space); // (SkImage *image, GrDirectContext *direct, SkColorType targetColorType, sk_color_space_t color_space) -> sk_image_t
sk_image_t SkImage_makeColorTypeAndColorSpace_2(reskia_image_t *image, reskia_graphite_recorder_t *recorder, reskia_image_color_type_t targetColorType, sk_color_space_t color_space, sk_image_required_properties_t properties); // (SkImage *image, skgpu::graphite::Recorder *recorder, SkColorType targetColorType, sk_color_space_t color_space, sk_image_required_properties_t properties) -> sk_image_t
sk_image_t SkImage_reinterpretColorSpace(reskia_image_t *image, sk_color_space_t color_space); // (SkImage *image, sk_color_space_t color_space) -> sk_image_t
bool SkImage_unique(reskia_image_t *image); // (SkImage *image) -> bool
void SkImage_ref(reskia_image_t *image); // retained: 参照カウントを増やす (SkImage *image)
void SkImage_unref(reskia_image_t *image); // owned: 参照カウントを減らす (SkImage *image)

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_IMAGE_H
