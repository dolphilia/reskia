//
// Created by dolphilia on 2024/02/02.
//

#include "sk_android_codec.h"

#include "include/codec/SkAndroidCodec.h"

#include "../static/static_sk_i_size-internal.h"
#include "../static/static_sk_stream-internal.h"
#include "../static/static_sk_data-internal.h"
#include "../static/static_sk_color_space-internal.h"
#include "../static/static_sk_codec-internal.h"
#include "../static/static_sk_android_codec-internal.h"

#ifdef __cplusplus
extern "C" {
#endif

void SkAndroidCodec_delete(void * androidCodec) {
    delete static_cast<SkAndroidCodec *>(androidCodec);
}

const void * SkAndroidCodec_getInfo(void * androidCodec) {
    return const_cast<SkImageInfo *>(&static_cast<SkAndroidCodec *>(androidCodec)->getInfo());
}

const void * SkAndroidCodec_getICCProfile(void * androidCodec) {
    return static_cast<SkAndroidCodec *>(androidCodec)->getICCProfile();
}

int SkAndroidCodec_getEncodedFormat(void * androidCodec) {
    return static_cast<int>(static_cast<SkAndroidCodec *>(androidCodec)->getEncodedFormat());
}

int SkAndroidCodec_computeOutputColorType(void * androidCodec, int requestedColorType) {
    return static_cast<SkAndroidCodec *>(androidCodec)->computeOutputColorType(static_cast<SkColorType>(requestedColorType));
}

int SkAndroidCodec_computeOutputAlphaType(void * androidCodec, bool requestedUnpremul) {
    return static_cast<SkAndroidCodec *>(androidCodec)->computeOutputAlphaType(requestedUnpremul);
}

sk_color_space_t SkAndroidCodec_computeOutputColorSpace(void * androidCodec, int outputColorType, sk_color_space_t prefColorSpace) {
    return static_sk_color_space_make(static_cast<SkAndroidCodec *>(androidCodec)->computeOutputColorSpace(static_cast<SkColorType>(outputColorType), static_sk_color_space_move(prefColorSpace)));
}

int SkAndroidCodec_computeSampleSize(void * androidCodec, void * size) {
    return static_cast<SkAndroidCodec *>(androidCodec)->computeSampleSize(static_cast<SkISize *>(size));
}

sk_i_size_t SkAndroidCodec_getSampledDimensions(void * androidCodec, int sampleSize) {
    return static_sk_i_size_make(static_cast<SkAndroidCodec *>(androidCodec)->getSampledDimensions(sampleSize));
}

bool SkAndroidCodec_getSupportedSubset(void * androidCodec, void * desiredSubset) {
    return static_cast<SkAndroidCodec *>(androidCodec)->getSupportedSubset(static_cast<SkIRect *>(desiredSubset));
}

sk_i_size_t SkAndroidCodec_getSampledSubsetDimensions(void * androidCodec, int sampleSize, const void * subset) {
    return static_sk_i_size_make(static_cast<SkAndroidCodec *>(androidCodec)->getSampledSubsetDimensions(sampleSize, * static_cast<const SkIRect *>(subset)));
}

int SkAndroidCodec_getAndroidPixels(void * androidCodec, const void * info, void* pixels, size_t rowBytes, const void * options) {
    return static_cast<SkAndroidCodec *>(androidCodec)->getAndroidPixels(* static_cast<const SkImageInfo *>(info), pixels, rowBytes, static_cast<const SkAndroidCodec::AndroidOptions *>(options));
}

int SkAndroidCodec_getAndroidPixels_2(void * androidCodec, const void * info, void* pixels, size_t rowBytes) {
    return static_cast<SkAndroidCodec *>(androidCodec)->getAndroidPixels(* static_cast<const SkImageInfo *>(info), pixels, rowBytes);
}

int SkAndroidCodec_getPixels(void * androidCodec, const void * info, void* pixels, size_t rowBytes) {
    return static_cast<SkAndroidCodec *>(androidCodec)->getPixels(* static_cast<const SkImageInfo *>(info), pixels, rowBytes);
}

void * SkAndroidCodec_codec(void * androidCodec) {
    return static_cast<SkAndroidCodec *>(androidCodec)->codec();
}

bool SkAndroidCodec_getAndroidGainmap(void *androidCodec, void *outInfo, sk_stream_ptr_t outGainmapImageStream) {
    return static_cast<SkAndroidCodec *>(androidCodec)->getAndroidGainmap(static_cast<SkGainmapInfo *>(outInfo), static_sk_stream_ptr_move(outGainmapImageStream));
}

// static

sk_android_codec_t SkAndroidCodec_MakeFromCodec(sk_codec_t codec) {
    return static_sk_android_codec_make(SkAndroidCodec::MakeFromCodec(static_sk_codec_move(codec)));
}

sk_android_codec_t SkAndroidCodec_MakeFromStream(sk_codec_t codec, void * pngChunkReader) {
    return static_sk_android_codec_make(SkAndroidCodec::MakeFromStream(static_sk_stream_move(codec), static_cast<SkPngChunkReader *>(pngChunkReader)));
}

sk_android_codec_t SkAndroidCodec_MakeFromData(sk_codec_t codec, void * pngChunkReader) {
    return static_sk_android_codec_make(SkAndroidCodec::MakeFromData(static_sk_data_move(codec), static_cast<SkPngChunkReader *>(pngChunkReader)));
}

#ifdef __cplusplus
}
#endif