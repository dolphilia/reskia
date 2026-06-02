//
// Created by dolphilia on 2024/02/02.
//

#ifndef RAIA_SKIA_SK_ANDROID_CODEC_H
#define RAIA_SKIA_SK_ANDROID_CODEC_H

#include <stddef.h>
#include <stdint.h>

#include "sk_alpha_type.h"
#include "reskia_status.h"
#include "../handles/static_sk_android_codec.h"
#include "../handles/static_sk_codec.h"
#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_i_size.h"
#include "../handles/static_sk_stream.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_android_codec_t reskia_android_codec_t;
typedef struct reskia_android_options_t reskia_android_options_t;
typedef struct reskia_codec_t reskia_codec_t;
typedef struct reskia_gainmap_info_t reskia_gainmap_info_t;
typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_i_size_t reskia_i_size_t;
typedef struct reskia_image_info_t reskia_image_info_t;
typedef struct reskia_png_chunk_reader_t reskia_png_chunk_reader_t;

typedef int32_t reskia_codec_result_code_t;
typedef int32_t reskia_color_type_t;
typedef int32_t reskia_encoded_image_format_t;

/**
 * owned: NULL is no-op.
 * caller が保持する参照を解放する (SkAndroidCodec *androidCodec)
 */
void SkAndroidCodec_delete(reskia_android_codec_t *androidCodec);
/**
 * borrowed: NULL androidCodec returns NULL (SkAndroidCodec *androidCodec) -> const SkImageInfo *
 */
const reskia_image_info_t *SkAndroidCodec_getInfo(reskia_android_codec_t *androidCodec);
/**
 * borrowed: NULL androidCodec returns NULL (SkAndroidCodec *androidCodec) -> const skcms_ICCProfile *
 */
const void *SkAndroidCodec_getICCProfile(reskia_android_codec_t *androidCodec);
/**
 * NULL androidCodec returns -1 (SkAndroidCodec *androidCodec) -> SkEncodedImageFormat
 */
reskia_encoded_image_format_t SkAndroidCodec_getEncodedFormat(reskia_android_codec_t *androidCodec);
/**
 * NULL androidCodec returns -1 (SkAndroidCodec *androidCodec, SkColorType requestedColorType) -> SkColorType
 */
reskia_color_type_t SkAndroidCodec_computeOutputColorType(reskia_android_codec_t *androidCodec, reskia_color_type_t requestedColorType);
/**
 * NULL androidCodec returns -1 (SkAndroidCodec *androidCodec, bool requestedUnpremul) -> SkAlphaType
 */
reskia_alpha_type_t SkAndroidCodec_computeOutputAlphaType(reskia_android_codec_t *androidCodec, bool requestedUnpremul);
/**
 * NULL androidCodec or null result returns handle 0 (SkAndroidCodec *androidCodec, SkColorType outputColorType, sk_color_space_t prefColorSpace) -> sk_color_space_t
 */
sk_color_space_t SkAndroidCodec_computeOutputColorSpace(reskia_android_codec_t *androidCodec, reskia_color_type_t outputColorType, sk_color_space_t prefColorSpace);
/**
 * borrowed: androidCodec/size are non-null.
 * invalid input returns 0 (SkAndroidCodec *androidCodec, SkISize* size) -> int.
 */
int SkAndroidCodec_computeSampleSize(reskia_android_codec_t *androidCodec, reskia_i_size_t *size);
/**
 * NULL androidCodec or sampleSize <= 0 returns handle 0 (SkAndroidCodec *androidCodec, int sampleSize) -> sk_i_size_t
 */
sk_i_size_t SkAndroidCodec_getSampledDimensions(reskia_android_codec_t *androidCodec, int sampleSize);
/**
 * borrowed: androidCodec/desiredSubset are non-null.
 * invalid input returns false (SkAndroidCodec *androidCodec, SkIRect* desiredSubset) -> bool.
 */
bool SkAndroidCodec_getSupportedSubset(reskia_android_codec_t *androidCodec, reskia_i_rect_t *desiredSubset);
/**
 * NULL androidCodec/subset or sampleSize <= 0 returns handle 0 (SkAndroidCodec *androidCodec, int sampleSize, const SkIRect* subset) -> sk_i_size_t
 */
sk_i_size_t SkAndroidCodec_getSampledSubsetDimensions(reskia_android_codec_t *androidCodec, int sampleSize, const reskia_i_rect_t *subset);
/**
 * androidCodec/info/pixels are non-null.
 * invalid input returns SkCodec::kInvalidParameters (SkAndroidCodec *androidCodec, const SkImageInfo* info, void* pixels, size_t rowBytes, const SkAndroidCodec::AndroidOptions* options) -> SkCodec::Result.
 */
reskia_codec_result_code_t SkAndroidCodec_getAndroidPixels(reskia_android_codec_t *androidCodec, const reskia_image_info_t *info, void *pixels, size_t rowBytes, const reskia_android_options_t *options);
/**
 * androidCodec/info/pixels are non-null.
 * invalid input returns SkCodec::kInvalidParameters (SkAndroidCodec *androidCodec, const SkImageInfo* info, void* pixels, size_t rowBytes) -> SkCodec::Result.
 */
reskia_codec_result_code_t SkAndroidCodec_getAndroidPixels_withoutOptions(reskia_android_codec_t *androidCodec, const reskia_image_info_t *info, void *pixels, size_t rowBytes);
/**
 * androidCodec/info/pixels are non-null.
 * invalid input returns SkCodec::kInvalidParameters (SkAndroidCodec *androidCodec, const SkImageInfo* info, void* pixels, size_t rowBytes) -> SkCodec::Result.
 */
reskia_codec_result_code_t SkAndroidCodec_getPixels(reskia_android_codec_t *androidCodec, const reskia_image_info_t *info, void *pixels, size_t rowBytes);
/**
 * borrowed: NULL androidCodec returns NULL (SkAndroidCodec *androidCodec) -> SkCodec *
 */
reskia_codec_t *SkAndroidCodec_codec(reskia_android_codec_t *androidCodec);
/**
 * androidCodec/out_info/out_gainmap_image_stream: non-null.
 * invalid input returns RESKIA_STATUS_INVALID_ARGUMENT.
 */
reskia_status_t SkAndroidCodec_getAndroidGainmap(reskia_android_codec_t *androidCodec, reskia_gainmap_info_t *out_info, sk_stream_t *out_gainmap_image_stream);
/**
 * androidCodec/out_info/out_gainmap_codec: non-null.
 * invalid input returns RESKIA_STATUS_INVALID_ARGUMENT.
 */
reskia_status_t SkAndroidCodec_getGainmapAndroidCodec(reskia_android_codec_t *androidCodec, reskia_gainmap_info_t *out_info, sk_android_codec_t *out_gainmap_codec);

// static

/**
 * codec handle 0 or factory failure returns handle 0 (sk_codec_t codec) -> sk_android_codec_t
 */
sk_android_codec_t SkAndroidCodec_MakeFromCodec(sk_codec_t codec);
/**
 * stream handle 0 or factory failure returns handle 0 (sk_stream_t stream, SkPngChunkReader* pngChunkReader) -> sk_android_codec_t
 */
sk_android_codec_t SkAndroidCodec_MakeFromStream(sk_stream_t stream, reskia_png_chunk_reader_t *pngChunkReader);
/**
 * data handle 0 or factory failure returns handle 0 (sk_data_t data, SkPngChunkReader* pngChunkReader) -> sk_android_codec_t
 */
sk_android_codec_t SkAndroidCodec_MakeFromData(sk_data_t data, reskia_png_chunk_reader_t *pngChunkReader);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_ANDROID_CODEC_H
