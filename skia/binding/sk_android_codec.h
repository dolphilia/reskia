//
// Created by dolphilia on 2024/02/02.
//

#ifndef RAIA_SKIA_SK_ANDROID_CODEC_H
#define RAIA_SKIA_SK_ANDROID_CODEC_H

#include <stddef.h>
#include <stdint.h>

#include "sk_alpha_type.h"
#include "reskia_status.h"
#include "../static/static_sk_android_codec.h"
#include "../static/static_sk_codec.h"
#include "../static/static_sk_color_space.h"
#include "../static/static_sk_i_size.h"
#include "../static/static_sk_stream.h"

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

void SkAndroidCodec_delete(reskia_android_codec_t *androidCodec); // owned: caller が保持する参照を解放する (SkAndroidCodec *androidCodec)
const reskia_image_info_t *SkAndroidCodec_getInfo(reskia_android_codec_t *androidCodec); // borrowed: returns borrowed pointer (SkAndroidCodec *androidCodec) -> const SkImageInfo *
const void *SkAndroidCodec_getICCProfile(reskia_android_codec_t *androidCodec); // borrowed: returns borrowed pointer (SkAndroidCodec *androidCodec) -> const skcms_ICCProfile *
reskia_encoded_image_format_t SkAndroidCodec_getEncodedFormat(reskia_android_codec_t *androidCodec); // (SkAndroidCodec *androidCodec) -> SkEncodedImageFormat
reskia_color_type_t SkAndroidCodec_computeOutputColorType(reskia_android_codec_t *androidCodec, reskia_color_type_t requestedColorType); // (SkAndroidCodec *androidCodec, SkColorType requestedColorType) -> SkColorType
reskia_alpha_type_t SkAndroidCodec_computeOutputAlphaType(reskia_android_codec_t *androidCodec, bool requestedUnpremul); // (SkAndroidCodec *androidCodec, bool requestedUnpremul) -> SkAlphaType
sk_color_space_t SkAndroidCodec_computeOutputColorSpace(reskia_android_codec_t *androidCodec, reskia_color_type_t outputColorType, sk_color_space_t prefColorSpace); // (SkAndroidCodec *androidCodec, SkColorType outputColorType, sk_color_space_t prefColorSpace) -> sk_color_space_t
int SkAndroidCodec_computeSampleSize(reskia_android_codec_t *androidCodec, reskia_i_size_t *size); // borrowed: output parameter is in-place mutable (SkAndroidCodec *androidCodec, SkISize* size) -> int
sk_i_size_t SkAndroidCodec_getSampledDimensions(reskia_android_codec_t *androidCodec, int sampleSize); // (SkAndroidCodec *androidCodec, int sampleSize) -> sk_i_size_t
bool SkAndroidCodec_getSupportedSubset(reskia_android_codec_t *androidCodec, reskia_i_rect_t *desiredSubset); // borrowed: desiredSubset is in-place mutable (SkAndroidCodec *androidCodec, SkIRect* desiredSubset) -> bool
sk_i_size_t SkAndroidCodec_getSampledSubsetDimensions(reskia_android_codec_t *androidCodec, int sampleSize, const reskia_i_rect_t *subset); // (SkAndroidCodec *androidCodec, int sampleSize, const SkIRect* subset) -> sk_i_size_t
reskia_codec_result_code_t SkAndroidCodec_getAndroidPixels(reskia_android_codec_t *androidCodec, const reskia_image_info_t *info, void *pixels, size_t rowBytes, const reskia_android_options_t *options); // (SkAndroidCodec *androidCodec, const SkImageInfo* info, void* pixels, size_t rowBytes, const SkAndroidCodec::AndroidOptions* options) -> SkCodec::Result
reskia_codec_result_code_t SkAndroidCodec_getAndroidPixels_2(reskia_android_codec_t *androidCodec, const reskia_image_info_t *info, void *pixels, size_t rowBytes); // (SkAndroidCodec *androidCodec, const SkImageInfo* info, void* pixels, size_t rowBytes) -> SkCodec::Result
reskia_codec_result_code_t SkAndroidCodec_getPixels(reskia_android_codec_t *androidCodec, const reskia_image_info_t *info, void *pixels, size_t rowBytes); // (SkAndroidCodec *androidCodec, const SkImageInfo* info, void* pixels, size_t rowBytes) -> SkCodec::Result
reskia_codec_t *SkAndroidCodec_codec(reskia_android_codec_t *androidCodec); // borrowed: returns borrowed codec pointer (SkAndroidCodec *androidCodec) -> SkCodec *
reskia_status_t SkAndroidCodec_getAndroidGainmap(reskia_android_codec_t *androidCodec, reskia_gainmap_info_t *out_info, sk_stream_t *out_gainmap_image_stream); // out_info/out_gainmap_image_stream: non-null

// static

sk_android_codec_t SkAndroidCodec_MakeFromCodec(sk_codec_t codec); // (sk_codec_t codec) -> sk_android_codec_t
sk_android_codec_t SkAndroidCodec_MakeFromStream(sk_codec_t codec, reskia_png_chunk_reader_t *pngChunkReader); // (sk_codec_t codec, SkPngChunkReader* pngChunkReader) -> sk_android_codec_t
sk_android_codec_t SkAndroidCodec_MakeFromData(sk_codec_t codec, reskia_png_chunk_reader_t *pngChunkReader); // (sk_codec_t codec, SkPngChunkReader* pngChunkReader) -> sk_android_codec_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_ANDROID_CODEC_H
