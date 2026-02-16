//
// Created by dolphilia on 2024/02/02.
//

#include "sk_android_codec.h"

#include <utility>

#include "include/codec/SkAndroidCodec.h"

#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_codec.h"
#include "../handles/static_sk_android_codec.h"
#include "../handles/static_sk_stream.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_i_size.h"

#include "../handles/static_sk_i_size-internal.h"
#include "../handles/static_sk_stream-internal.h"
#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_color_space-internal.h"
#include "../handles/static_sk_codec-internal.h"
#include "../handles/static_sk_android_codec-internal.h"

#ifdef __cplusplus
extern "C" {
#endif

void SkAndroidCodec_delete(reskia_android_codec_t *androidCodec) {
    delete reinterpret_cast<SkAndroidCodec *>(androidCodec);
}

const reskia_image_info_t *SkAndroidCodec_getInfo(reskia_android_codec_t *androidCodec) {
    return reinterpret_cast<const reskia_image_info_t *>(&reinterpret_cast<SkAndroidCodec *>(androidCodec)->getInfo());
}

const void *SkAndroidCodec_getICCProfile(reskia_android_codec_t *androidCodec) {
    return reinterpret_cast<SkAndroidCodec *>(androidCodec)->getICCProfile();
}

reskia_encoded_image_format_t SkAndroidCodec_getEncodedFormat(reskia_android_codec_t *androidCodec) {
    return static_cast<reskia_encoded_image_format_t>(reinterpret_cast<SkAndroidCodec *>(androidCodec)->getEncodedFormat());
}

reskia_color_type_t SkAndroidCodec_computeOutputColorType(reskia_android_codec_t *androidCodec, reskia_color_type_t requestedColorType) {
    return static_cast<reskia_color_type_t>(reinterpret_cast<SkAndroidCodec *>(androidCodec)->computeOutputColorType(static_cast<SkColorType>(requestedColorType)));
}

reskia_alpha_type_t SkAndroidCodec_computeOutputAlphaType(reskia_android_codec_t *androidCodec, bool requestedUnpremul) {
    return static_cast<reskia_alpha_type_t>(reinterpret_cast<SkAndroidCodec *>(androidCodec)->computeOutputAlphaType(requestedUnpremul));
}

sk_color_space_t SkAndroidCodec_computeOutputColorSpace(reskia_android_codec_t *androidCodec, reskia_color_type_t outputColorType, sk_color_space_t prefColorSpace) {
    return static_sk_color_space_make(reinterpret_cast<SkAndroidCodec *>(androidCodec)->computeOutputColorSpace(static_cast<SkColorType>(outputColorType), static_sk_color_space_get_entity(prefColorSpace)));
}

int SkAndroidCodec_computeSampleSize(reskia_android_codec_t *androidCodec, reskia_i_size_t *size) {
    return reinterpret_cast<SkAndroidCodec *>(androidCodec)->computeSampleSize(reinterpret_cast<SkISize *>(size));
}

sk_i_size_t SkAndroidCodec_getSampledDimensions(reskia_android_codec_t *androidCodec, int sampleSize) {
    return static_sk_i_size_make(reinterpret_cast<SkAndroidCodec *>(androidCodec)->getSampledDimensions(sampleSize));
}

bool SkAndroidCodec_getSupportedSubset(reskia_android_codec_t *androidCodec, reskia_i_rect_t *desiredSubset) {
    return reinterpret_cast<SkAndroidCodec *>(androidCodec)->getSupportedSubset(reinterpret_cast<SkIRect *>(desiredSubset));
}

sk_i_size_t SkAndroidCodec_getSampledSubsetDimensions(reskia_android_codec_t *androidCodec, int sampleSize, const reskia_i_rect_t *subset) {
    return static_sk_i_size_make(reinterpret_cast<SkAndroidCodec *>(androidCodec)->getSampledSubsetDimensions(sampleSize, *reinterpret_cast<const SkIRect *>(subset)));
}

reskia_codec_result_code_t SkAndroidCodec_getAndroidPixels(reskia_android_codec_t *androidCodec, const reskia_image_info_t *info, void *pixels, size_t rowBytes, const reskia_android_options_t *options) {
    return static_cast<reskia_codec_result_code_t>(reinterpret_cast<SkAndroidCodec *>(androidCodec)->getAndroidPixels(*reinterpret_cast<const SkImageInfo *>(info), pixels, rowBytes, reinterpret_cast<const SkAndroidCodec::AndroidOptions *>(options)));
}

reskia_codec_result_code_t SkAndroidCodec_getAndroidPixels_withoutOptions(reskia_android_codec_t *androidCodec, const reskia_image_info_t *info, void *pixels, size_t rowBytes) {
    return static_cast<reskia_codec_result_code_t>(reinterpret_cast<SkAndroidCodec *>(androidCodec)->getAndroidPixels(*reinterpret_cast<const SkImageInfo *>(info), pixels, rowBytes));
}

reskia_codec_result_code_t SkAndroidCodec_getPixels(reskia_android_codec_t *androidCodec, const reskia_image_info_t *info, void *pixels, size_t rowBytes) {
    return static_cast<reskia_codec_result_code_t>(reinterpret_cast<SkAndroidCodec *>(androidCodec)->getPixels(*reinterpret_cast<const SkImageInfo *>(info), pixels, rowBytes));
}

reskia_codec_t *SkAndroidCodec_codec(reskia_android_codec_t *androidCodec) {
    return reinterpret_cast<reskia_codec_t *>(reinterpret_cast<SkAndroidCodec *>(androidCodec)->codec());
}

reskia_status_t SkAndroidCodec_getAndroidGainmap(reskia_android_codec_t *androidCodec, reskia_gainmap_info_t *out_info, sk_stream_t *out_gainmap_image_stream) {
    if (androidCodec == nullptr || out_info == nullptr || out_gainmap_image_stream == nullptr) {
        return RESKIA_STATUS_INVALID_ARGUMENT;
    }
    std::unique_ptr<SkStream> gainmap_stream;
    const bool ok = reinterpret_cast<SkAndroidCodec *>(androidCodec)->getAndroidGainmap(
        reinterpret_cast<SkGainmapInfo *>(out_info),
        &gainmap_stream
    );
    if (!ok || gainmap_stream == nullptr) {
        *out_gainmap_image_stream = 0;
        return RESKIA_STATUS_NOT_FOUND;
    }
    *out_gainmap_image_stream = static_sk_stream_make(std::move(gainmap_stream));
    return RESKIA_STATUS_OK;
}

// static

sk_android_codec_t SkAndroidCodec_MakeFromCodec(sk_codec_t codec) {
    return static_sk_android_codec_make(SkAndroidCodec::MakeFromCodec(static_sk_codec_take_entity(codec)));
}

sk_android_codec_t SkAndroidCodec_MakeFromStream(sk_codec_t codec, reskia_png_chunk_reader_t *pngChunkReader) {
    return static_sk_android_codec_make(SkAndroidCodec::MakeFromStream(static_sk_stream_take_entity(codec), reinterpret_cast<SkPngChunkReader *>(pngChunkReader)));
}

sk_android_codec_t SkAndroidCodec_MakeFromData(sk_codec_t codec, reskia_png_chunk_reader_t *pngChunkReader) {
    return static_sk_android_codec_make(SkAndroidCodec::MakeFromData(static_sk_data_get_entity(codec), reinterpret_cast<SkPngChunkReader *>(pngChunkReader)));
}

#ifdef __cplusplus
}
#endif
