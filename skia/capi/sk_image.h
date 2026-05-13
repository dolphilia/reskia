//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_IMAGE_H
#define RAIA_SKIA_SK_IMAGE_H

#include <stddef.h>
#include <stdint.h>
#include "sk_async_read_result.h"
#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_i_rect.h"
#include "../handles/static_sk_i_size.h"
#include "../handles/static_sk_image.h"
#include "../handles/static_sk_image_info.h"
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
typedef int32_t reskia_image_rescale_gamma_t;
typedef int32_t reskia_image_rescale_mode_t;
typedef int32_t reskia_image_yuv_color_space_t;

/**
 * Releases the caller-held reference.
 * Skia: (SkImage *image).
 */
void SkImage_release(reskia_image_t *image);

sk_image_info_t SkImage_imageInfo(reskia_image_t *image); // (SkImage *image) -> sk_image_info_t
int SkImage_width(reskia_image_t *image); // (SkImage *image) -> int
int SkImage_height(reskia_image_t *image); // (SkImage *image) -> int
sk_i_size_t SkImage_dimensions(reskia_image_t *image); // (SkImage *image) -> sk_i_size_t
sk_i_rect_t SkImage_bounds(reskia_image_t *image); // (SkImage *image) -> sk_i_rect_t
reskia_u32_t SkImage_uniqueID(reskia_image_t *image); // (SkImage *image) -> uint32_t
reskia_image_alpha_type_t SkImage_alphaType(reskia_image_t *image); // (SkImage *image) -> SkAlphaType
reskia_image_color_type_t SkImage_colorType(reskia_image_t *image); // (SkImage *image) -> SkColorType
/**
 * Borrowed pointer; caller must not free. NULL image or no color space returns NULL.
 * Skia: (SkImage *image) -> SkColorSpace *.
 */
reskia_color_space_t *SkImage_colorSpace(reskia_image_t *image);
/**
 * retained handle.
 * Caller deletes with static_sk_color_space_delete.
 * NULL image or no color space returns 0.
 * Skia: (SkImage *image) -> sk_color_space_t.
 */
sk_color_space_t SkImage_refColorSpace(reskia_image_t *image);
bool SkImage_isAlphaOnly(reskia_image_t *image); // (SkImage *image) -> bool
bool SkImage_isOpaque(reskia_image_t *image); // (SkImage *image) -> bool
/**
 * image/sampling: non-null.
 * tmx/tmy must be valid SkTileMode values.
 * localMatrix may be NULL.
 * Returns a caller-owned shader handle.
 * Invalid input or factory failure returns 0.
 * Skia: (SkImage *image, SkTileMode tmx, SkTileMode tmy, const SkSamplingOptions *sampling, const SkMatrix *localMatrix) -> sk_shader_t.
 */
sk_shader_t SkImage_makeShader(reskia_image_t *image, reskia_image_tile_mode_t tmx, reskia_image_tile_mode_t tmy, const reskia_sampling_options_t *sampling, const reskia_matrix_t *localMatrix);
/**
 * image/sampling/lm: non-null.
 * tmx/tmy must be valid SkTileMode values.
 * Returns a caller-owned shader handle.
 * Invalid input or factory failure returns 0.
 * Skia: (SkImage *image, SkTileMode tmx, SkTileMode tmy, const SkSamplingOptions *sampling, const SkMatrix *lm) -> sk_shader_t.
 */
sk_shader_t SkImage_makeShaderWithTileModesAndLocalMatrix(reskia_image_t *image, reskia_image_tile_mode_t tmx, reskia_image_tile_mode_t tmy, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm);
/**
 * image/sampling/lm: non-null.
 * Returns a caller-owned shader handle.
 * Invalid input or factory failure returns 0.
 * Skia: (SkImage *image, const SkSamplingOptions *sampling, const SkMatrix *lm) -> sk_shader_t.
 */
sk_shader_t SkImage_makeShaderWithSamplingAndLocalMatrix(reskia_image_t *image, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm);
/**
 * image/sampling: non-null.
 * lm may be NULL.
 * Returns a caller-owned shader handle.
 * Invalid input or factory failure returns 0.
 * Skia: (SkImage *image, const SkSamplingOptions *sampling, const SkMatrix *lm) -> sk_shader_t.
 */
sk_shader_t SkImage_makeShaderWithSampling(reskia_image_t *image, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm);
/**
 * image/sampling: non-null.
 * tmx/tmy must be valid SkTileMode values.
 * localMatrix may be NULL.
 * Returns a caller-owned shader handle.
 * Invalid input or factory failure returns 0.
 * Skia: (SkImage *image, SkTileMode tmx, SkTileMode tmy, const SkSamplingOptions *sampling, const SkMatrix *localMatrix) -> sk_shader_t.
 */
sk_shader_t SkImage_makeRawShader(reskia_image_t *image, reskia_image_tile_mode_t tmx, reskia_image_tile_mode_t tmy, const reskia_sampling_options_t *sampling, const reskia_matrix_t *localMatrix);
/**
 * image/sampling/lm: non-null.
 * tmx/tmy must be valid SkTileMode values.
 * Returns a caller-owned shader handle.
 * Invalid input or factory failure returns 0.
 * Skia: (SkImage *image, SkTileMode tmx, SkTileMode tmy, const SkSamplingOptions *sampling, const SkMatrix *lm) -> sk_shader_t.
 */
sk_shader_t SkImage_makeRawShaderWithTileModesAndLocalMatrix(reskia_image_t *image, reskia_image_tile_mode_t tmx, reskia_image_tile_mode_t tmy, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm);
/**
 * image/sampling/lm: non-null.
 * Returns a caller-owned shader handle.
 * Invalid input or factory failure returns 0.
 * Skia: (SkImage *image, const SkSamplingOptions *sampling, const SkMatrix *lm) -> sk_shader_t.
 */
sk_shader_t SkImage_makeRawShaderWithSamplingAndLocalMatrix(reskia_image_t *image, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm);
/**
 * image/sampling: non-null.
 * lm may be NULL.
 * Returns a caller-owned shader handle.
 * Invalid input or factory failure returns 0.
 * Skia: (SkImage *image, const SkSamplingOptions *sampling, const SkMatrix *lm) -> sk_shader_t.
 */
sk_shader_t SkImage_makeRawShaderWithSampling(reskia_image_t *image, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm);
/**
 * pixmap: non-null out param.
 * Returned pixmap borrows image pixels.
 * Invalid input returns false.
 * Skia: (SkImage *image, SkPixmap *pixmap) -> bool.
 */
bool SkImage_peekPixels(reskia_image_t *image, reskia_pixmap_t *pixmap);
/**
 * NULL image returns false.
 * Skia: (SkImage *image) -> bool.
 */
bool SkImage_isTextureBacked(reskia_image_t *image);
/**
 * NULL image returns 0.
 * Skia: (SkImage *image) -> size_t.
 */
size_t SkImage_textureSize(reskia_image_t *image);
/**
 * image: non-null.
 * context may be NULL.
 * NULL image returns false.
 * Skia: (SkImage *image, GrRecordingContext *context) -> bool.
 */
bool SkImage_isValid(reskia_image_t *image, reskia_recording_context_t *context);
/**
 * image/dstInfo/dstPixels: non-null.
 * context may be NULL.
 * dstRowBytes must satisfy dstInfo.validRowBytes.
 * Invalid input returns false.
 * Skia:
 *   (SkImage *image,
 *    GrDirectContext *context,
 *    const SkImageInfo *dstInfo,
 *    void *dstPixels,
 *    size_t dstRowBytes,
 *    int srcX,
 *    int srcY,
 *    SkImage::CachingHint cachingHint) -> bool.
 */
bool SkImage_readPixels(reskia_image_t *image, reskia_direct_context_t *context, const reskia_image_info_t *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY, reskia_image_caching_hint_t cachingHint);
/**
 * image/dst pixmap: non-null.
 * context may be NULL.
 * Invalid input returns false.
 * Skia: (SkImage *image, GrDirectContext *context, const SkPixmap *dst, int srcX, int srcY, SkImage::CachingHint cachingHint) -> bool.
 */
bool SkImage_readPixelsWithContextPixmap(reskia_image_t *image, reskia_direct_context_t *context, const reskia_pixmap_t *dst, int srcX, int srcY, reskia_image_caching_hint_t cachingHint);
/**
 * image/dstInfo/dstPixels: non-null.
 * dstRowBytes must satisfy dstInfo.validRowBytes.
 * Invalid input returns false.
 * Skia:
 *   (SkImage *image,
 *    const SkImageInfo *dstInfo,
 *    void *dstPixels,
 *    size_t dstRowBytes,
 *    int srcX,
 *    int srcY,
 *    SkImage::CachingHint cachingHint) -> bool.
 */
bool SkImage_readPixelsWithImageInfo(reskia_image_t *image, const reskia_image_info_t *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY, reskia_image_caching_hint_t cachingHint);
/**
 * image/dst pixmap: non-null.
 * Invalid input returns false.
 * Skia: (SkImage *image, const SkPixmap *dst, int srcX, int srcY, SkImage::CachingHint cachingHint) -> bool.
 */
bool SkImage_readPixelsWithPixmap(reskia_image_t *image, const reskia_pixmap_t *dst, int srcX, int srcY, reskia_image_caching_hint_t cachingHint);

/**
 * image/info/srcRect/callback: non-null.
 * context may be NULL.
 * Invalid input calls callback with NULL result when callback is provided.
 * NULL callback is no-op.
 * Skia:
 *   (SkImage *image,
 *    const SkImageInfo *info,
 *    const SkIRect *srcRect,
 *    SkImage::RescaleGamma rescaleGamma,
 *    SkImage::RescaleMode rescaleMode,
 *    reskia_async_read_pixels_callback_t callback,
 *    void *context).
 */
void SkImage_asyncRescaleAndReadPixels(reskia_image_t *image, const reskia_image_info_t *info, const reskia_i_rect_t *srcRect, reskia_image_rescale_gamma_t rescaleGamma, reskia_image_rescale_mode_t rescaleMode, reskia_async_read_pixels_callback_t callback, void *context);
/**
 * image/srcRect/callback: non-null.
 * context may be NULL.
 * dstSize must be a valid handle.
 * Invalid input calls callback with NULL result when callback is provided.
 * NULL callback is no-op.
 * Skia:
 *   (SkImage *image,
 *    SkYUVColorSpace yuvColorSpace,
 *    sk_color_space_t color_space,
 *    const SkIRect *srcRect,
 *    sk_i_size_t dstSize,
 *    SkImage::RescaleGamma rescaleGamma,
 *    SkImage::RescaleMode rescaleMode,
 *    reskia_async_read_pixels_callback_t callback,
 *    void *context).
 */
void SkImage_asyncRescaleAndReadPixelsYUV420(reskia_image_t *image, reskia_image_yuv_color_space_t yuvColorSpace, sk_color_space_t color_space, const reskia_i_rect_t *srcRect, sk_i_size_t dstSize, reskia_image_rescale_gamma_t rescaleGamma, reskia_image_rescale_mode_t rescaleMode, reskia_async_read_pixels_callback_t callback, void *context);
/**
 * image/srcRect/callback: non-null.
 * context may be NULL.
 * dstSize must be a valid handle.
 * Invalid input calls callback with NULL result when callback is provided.
 * Skia:
 *   (SkImage *image,
 *    SkYUVColorSpace yuvColorSpace,
 *    sk_color_space_t color_space,
 *    const SkIRect *srcRect,
 *    sk_i_size_t dstSize,
 *    SkImage::RescaleGamma rescaleGamma,
 *    SkImage::RescaleMode rescaleMode,
 *    reskia_async_read_pixels_callback_t callback,
 *    void *context).
 */
void SkImage_asyncRescaleAndReadPixelsYUVA420(reskia_image_t *image, reskia_image_yuv_color_space_t yuvColorSpace, sk_color_space_t color_space, const reskia_i_rect_t *srcRect, sk_i_size_t dstSize, reskia_image_rescale_gamma_t rescaleGamma, reskia_image_rescale_mode_t rescaleMode, reskia_async_read_pixels_callback_t callback, void *context);
/**
 * image/dst/sampling: non-null.
 * dst must have writable storage.
 * Invalid input returns false.
 * Skia: (SkImage *image, const SkPixmap *dst, const SkSamplingOptions *sampling, SkImage::CachingHint cachingHint) -> bool.
 */
bool SkImage_scalePixels(reskia_image_t *image, const reskia_pixmap_t *dst, const reskia_sampling_options_t *sampling, reskia_image_caching_hint_t cachingHint);
/**
 * Returns a caller-owned retained data handle.
 * Caller deletes with static_sk_data_delete.
 * Returns 0 when image is NULL or no encoded data is available.
 * Skia: (SkImage *image) -> sk_data_t.
 */
sk_data_t SkImage_refEncodedData(reskia_image_t *image);
/**
 * image/subset: non-null.
 * direct may be NULL.
 * Returned handle is caller-owned.
 * Returns 0 on invalid input or factory failure.
 * Skia: (SkImage *image, GrDirectContext *direct, const SkIRect *subset) -> sk_image_t.
 */
sk_image_t SkImage_makeSubset(reskia_image_t *image, reskia_direct_context_t *direct, const reskia_i_rect_t *subset);
/**
 * image/recorder/subset: non-null.
 * Returns 0 on invalid input or factory failure.
 * Skia: (SkImage *image, skgpu::graphite::Recorder *recorder, const SkIRect *subset, sk_image_required_properties_t properties) -> sk_image_t.
 */
sk_image_t SkImage_makeSubsetWithRecorder(reskia_image_t *image, reskia_graphite_recorder_t *recorder, const reskia_i_rect_t *subset, sk_image_required_properties_t properties);
bool SkImage_hasMipmaps(reskia_image_t *image); // (SkImage *image) -> bool
bool SkImage_isProtected(reskia_image_t *image); // (SkImage *image) -> bool
/**
 * image: non-null.
 * Returned handle is caller-owned.
 * Returns 0 on invalid input or factory failure.
 * Skia: (SkImage *image) -> sk_image_t.
 */
sk_image_t SkImage_withDefaultMipmaps(reskia_image_t *image);
/**
 * image: non-null.
 * context may be NULL.
 * Returns 0 on invalid input or factory failure.
 * Skia: (SkImage *image, GrDirectContext *context) -> sk_image_t.
 */
sk_image_t SkImage_makeNonTextureImage(reskia_image_t *image, reskia_direct_context_t *context);
/**
 * image: non-null.
 * context may be NULL.
 * Returned handle is caller-owned.
 * Returns 0 on invalid input or factory failure.
 * Skia: (SkImage *image, GrDirectContext *context, SkImage::CachingHint cachingHint) -> sk_image_t.
 */
sk_image_t SkImage_makeRasterImage(reskia_image_t *image, reskia_direct_context_t *context, reskia_image_caching_hint_t cachingHint);
/**
 * image: non-null.
 * Returned handle is caller-owned.
 * Returns 0 on invalid input or factory failure.
 * Skia: (SkImage *image, SkImage::CachingHint cachingHint) -> sk_image_t.
 */
sk_image_t SkImage_makeRasterImageWithoutContext(reskia_image_t *image, reskia_image_caching_hint_t cachingHint);
bool SkImage_asLegacyBitmap(reskia_image_t *image, reskia_bitmap_t *bitmap, reskia_image_legacy_bitmap_mode_t legacyBitmapMode); // (SkImage *image, SkBitmap *bitmap, SkImage::LegacyBitmapMode legacyBitmapMode) -> bool
bool SkImage_isLazyGenerated(reskia_image_t *image); // (SkImage *image) -> bool
/**
 * image: non-null.
 * direct may be NULL.
 * color_space handle 0 is allowed as null color space.
 * Non-zero color_space must be valid.
 * Returns 0 on invalid input or factory failure.
 * Skia: (SkImage *image, GrDirectContext *direct, sk_color_space_t color_space) -> sk_image_t.
 */
sk_image_t SkImage_makeColorSpace(reskia_image_t *image, reskia_direct_context_t *direct, sk_color_space_t color_space);
/**
 * image/recorder: non-null.
 * color_space handle 0 is allowed as null color space.
 * Non-zero color_space must be valid.
 * Returns 0 on invalid input or factory failure.
 * Skia:
 *   (SkImage *image,
 *    skgpu::graphite::Recorder *recorder,
 *    sk_color_space_t color_space,
 *    sk_image_required_properties_t properties) -> sk_image_t.
 */
sk_image_t SkImage_makeColorSpaceWithRecorder(reskia_image_t *image, reskia_graphite_recorder_t *recorder, sk_color_space_t color_space, sk_image_required_properties_t properties);
/**
 * image: non-null.
 * color_space handle 0 is allowed as null color space.
 * Non-zero color_space must be valid.
 * Returns 0 on invalid input or factory failure.
 * Skia: (SkImage *image, GrDirectContext *direct, SkColorType targetColorType, sk_color_space_t color_space) -> sk_image_t.
 */
sk_image_t SkImage_makeColorTypeAndColorSpace(reskia_image_t *image, reskia_direct_context_t *direct, reskia_image_color_type_t targetColorType, sk_color_space_t color_space);
/**
 * image/recorder: non-null.
 * color_space handle 0 is allowed as null color space.
 * Non-zero color_space must be valid.
 * Returns 0 on invalid input or factory failure.
 * Skia:
 *   (SkImage *image,
 *    skgpu::graphite::Recorder *recorder,
 *    SkColorType targetColorType,
 *    sk_color_space_t color_space,
 *    sk_image_required_properties_t properties) -> sk_image_t.
 */
sk_image_t SkImage_makeColorTypeAndColorSpaceWithRecorder(reskia_image_t *image, reskia_graphite_recorder_t *recorder, reskia_image_color_type_t targetColorType, sk_color_space_t color_space, sk_image_required_properties_t properties);
/**
 * image: non-null.
 * color_space handle 0 is allowed as null color space.
 * Non-zero color_space must be valid.
 * Returns 0 on invalid input or factory failure.
 * Skia: (SkImage *image, sk_color_space_t color_space) -> sk_image_t.
 */
sk_image_t SkImage_reinterpretColorSpace(reskia_image_t *image, sk_color_space_t color_space);
bool SkImage_unique(reskia_image_t *image); // (SkImage *image) -> bool
void SkImage_ref(reskia_image_t *image); // Retains image. (SkImage *image)
/**
 * Releases the reference.
 * Skia: (SkImage *image).
 */
void SkImage_unref(reskia_image_t *image);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_IMAGE_H
