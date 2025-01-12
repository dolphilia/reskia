//
// Created by dolphilia on 2024/02/02.
//

#ifndef RAIA_SKIA_SK_ANDROID_CODEC_H
#define RAIA_SKIA_SK_ANDROID_CODEC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "../static/static_sk_color_space.h"
#include "../static/static_sk_codec.h"
#include "../static/static_sk_android_codec.h"
#include "../static/static_sk_stream.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_i_size.h"

void SkAndroidCodec_delete(void * androidCodec); // (SkAndroidCodec *androidCodec)
const void * SkAndroidCodec_getInfo(void * androidCodec); // (SkAndroidCodec *androidCodec) - > const SkImageInfo *
const void * SkAndroidCodec_getICCProfile(void * androidCodec); // (SkAndroidCodec *androidCodec) -> const skcms_ICCProfile *
int SkAndroidCodec_getEncodedFormat(void * androidCodec); // (SkAndroidCodec *androidCodec) -> SkEncodedImageFormat
int SkAndroidCodec_computeOutputColorType(void * androidCodec, int requestedColorType); // (SkAndroidCodec *androidCodec, SkColorType requestedColorType) -> SkColorType
int SkAndroidCodec_computeOutputAlphaType(void * androidCodec, bool requestedUnpremul); // (SkAndroidCodec *androidCodec, bool requestedUnpremul) -> SkAlphaType
sk_color_space_t SkAndroidCodec_computeOutputColorSpace(void * androidCodec, int outputColorType, sk_color_space_t prefColorSpace); // (SkAndroidCodec *androidCodec, SkColorType outputColorType, sk_color_space_t prefColorSpace) -> sk_color_space_t
int SkAndroidCodec_computeSampleSize(void * androidCodec, void * size); // (SkAndroidCodec *androidCodec, SkISize* size) -> int
sk_i_size_t SkAndroidCodec_getSampledDimensions(void * androidCodec, int sampleSize); // (SkAndroidCodec *androidCodec, int sampleSize) -> sk_i_size_t
bool SkAndroidCodec_getSupportedSubset(void * androidCodec, void * desiredSubset); // (SkAndroidCodec *androidCodec, SkIRect* desiredSubset) -> bool
sk_i_size_t SkAndroidCodec_getSampledSubsetDimensions(void * androidCodec, int sampleSize, const void * subset); // (SkAndroidCodec *androidCodec, int sampleSize, const SkIRect* subset) -> sk_i_size_t
int SkAndroidCodec_getAndroidPixels(void * androidCodec, const void * info, void* pixels, size_t rowBytes, const void * options); // (SkAndroidCodec *androidCodec, const SkImageInfo* info, void* pixels, size_t rowBytes, const SkAndroidCodec::AndroidOptions* options) -> SkCodec::Result
int SkAndroidCodec_getAndroidPixels_2(void * androidCodec, const void * info, void* pixels, size_t rowBytes); // (SkAndroidCodec *androidCodec, const SkImageInfo* info, void* pixels, size_t rowBytes) -> SkCodec::Result
int SkAndroidCodec_getPixels(void * androidCodec, const void * info, void* pixels, size_t rowBytes); // (SkAndroidCodec *androidCodec, const SkImageInfo* info, void* pixels, size_t rowBytes) -> SkCodec::Result
void * SkAndroidCodec_codec(void * androidCodec); // (SkAndroidCodec *androidCodec) -> SkCodec *
bool SkAndroidCodec_getAndroidGainmap(void * androidCodec, void * outInfo, sk_stream_ptr_t outGainmapImageStream); // (SkAndroidCodec *androidCodec, SkGainmapInfo* outInfo, std::unique_ptr<SkStream>* outGainmapImageStream) -> bool

// static

int SkAndroidCodec_MakeFromCodec(sk_codec_t codec); // (sk_codec_t codec) -> sk_android_codec_t
int SkAndroidCodec_MakeFromStream(sk_codec_t codec, void * pngChunkReader); // (sk_codec_t codec, SkPngChunkReader* pngChunkReader) -> sk_android_codec_t
int SkAndroidCodec_MakeFromData(sk_codec_t codec, void * pngChunkReader); // (sk_codec_t codec, SkPngChunkReader* pngChunkReader) -> sk_android_codec_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_ANDROID_CODEC_H
