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

namespace {

SkAndroidCodec *as_android_codec(reskia_android_codec_t *androidCodec) {
    return reinterpret_cast<SkAndroidCodec *>(androidCodec);
}

constexpr reskia_codec_result_code_t kInvalidParameters = static_cast<reskia_codec_result_code_t>(SkCodec::kInvalidParameters);

bool has_valid_sample_size(int sampleSize) {
    return sampleSize > 0;
}

sk_android_codec_t make_android_codec_handle(std::unique_ptr<SkAndroidCodec> codec) {
    if (codec == nullptr) {
        return 0;
    }
    return static_sk_android_codec_make(std::move(codec));
}

}  // namespace

#ifdef __cplusplus
extern "C" {
#endif

void SkAndroidCodec_delete(reskia_android_codec_t *androidCodec) {
    delete as_android_codec(androidCodec);
}

const reskia_image_info_t *SkAndroidCodec_getInfo(reskia_android_codec_t *androidCodec) {
    SkAndroidCodec *codec = as_android_codec(androidCodec);
    if (codec == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_image_info_t *>(&codec->getInfo());
}

const void *SkAndroidCodec_getICCProfile(reskia_android_codec_t *androidCodec) {
    SkAndroidCodec *codec = as_android_codec(androidCodec);
    return codec != nullptr ? codec->getICCProfile() : nullptr;
}

reskia_encoded_image_format_t SkAndroidCodec_getEncodedFormat(reskia_android_codec_t *androidCodec) {
    SkAndroidCodec *codec = as_android_codec(androidCodec);
    if (codec == nullptr) {
        return -1;
    }
    return static_cast<reskia_encoded_image_format_t>(codec->getEncodedFormat());
}

reskia_color_type_t SkAndroidCodec_computeOutputColorType(reskia_android_codec_t *androidCodec, reskia_color_type_t requestedColorType) {
    SkAndroidCodec *codec = as_android_codec(androidCodec);
    if (codec == nullptr) {
        return -1;
    }
    return static_cast<reskia_color_type_t>(codec->computeOutputColorType(static_cast<SkColorType>(requestedColorType)));
}

reskia_alpha_type_t SkAndroidCodec_computeOutputAlphaType(reskia_android_codec_t *androidCodec, bool requestedUnpremul) {
    SkAndroidCodec *codec = as_android_codec(androidCodec);
    if (codec == nullptr) {
        return -1;
    }
    return static_cast<reskia_alpha_type_t>(codec->computeOutputAlphaType(requestedUnpremul));
}

sk_color_space_t SkAndroidCodec_computeOutputColorSpace(reskia_android_codec_t *androidCodec, reskia_color_type_t outputColorType, sk_color_space_t prefColorSpace) {
    SkAndroidCodec *codec = as_android_codec(androidCodec);
    if (codec == nullptr) {
        return 0;
    }
    sk_sp<SkColorSpace> color_space = codec->computeOutputColorSpace(static_cast<SkColorType>(outputColorType), static_sk_color_space_get_entity(prefColorSpace));
    return color_space != nullptr ? static_sk_color_space_make(std::move(color_space)) : 0;
}

int SkAndroidCodec_computeSampleSize(reskia_android_codec_t *androidCodec, reskia_i_size_t *size) {
    SkAndroidCodec *codec = as_android_codec(androidCodec);
    if (codec == nullptr || size == nullptr) {
        return 0;
    }
    return codec->computeSampleSize(reinterpret_cast<SkISize *>(size));
}

sk_i_size_t SkAndroidCodec_getSampledDimensions(reskia_android_codec_t *androidCodec, int sampleSize) {
    SkAndroidCodec *codec = as_android_codec(androidCodec);
    if (codec == nullptr || !has_valid_sample_size(sampleSize)) {
        return 0;
    }
    return static_sk_i_size_make(codec->getSampledDimensions(sampleSize));
}

bool SkAndroidCodec_getSupportedSubset(reskia_android_codec_t *androidCodec, reskia_i_rect_t *desiredSubset) {
    SkAndroidCodec *codec = as_android_codec(androidCodec);
    if (codec == nullptr || desiredSubset == nullptr) {
        return false;
    }
    return codec->getSupportedSubset(reinterpret_cast<SkIRect *>(desiredSubset));
}

sk_i_size_t SkAndroidCodec_getSampledSubsetDimensions(reskia_android_codec_t *androidCodec, int sampleSize, const reskia_i_rect_t *subset) {
    SkAndroidCodec *codec = as_android_codec(androidCodec);
    if (codec == nullptr || !has_valid_sample_size(sampleSize) || subset == nullptr) {
        return 0;
    }
    return static_sk_i_size_make(codec->getSampledSubsetDimensions(sampleSize, *reinterpret_cast<const SkIRect *>(subset)));
}

reskia_codec_result_code_t SkAndroidCodec_getAndroidPixels(reskia_android_codec_t *androidCodec, const reskia_image_info_t *info, void *pixels, size_t rowBytes, const reskia_android_options_t *options) {
    SkAndroidCodec *codec = as_android_codec(androidCodec);
    if (codec == nullptr || info == nullptr || pixels == nullptr) {
        return kInvalidParameters;
    }
    return static_cast<reskia_codec_result_code_t>(codec->getAndroidPixels(*reinterpret_cast<const SkImageInfo *>(info), pixels, rowBytes, reinterpret_cast<const SkAndroidCodec::AndroidOptions *>(options)));
}

reskia_codec_result_code_t SkAndroidCodec_getAndroidPixels_withoutOptions(reskia_android_codec_t *androidCodec, const reskia_image_info_t *info, void *pixels, size_t rowBytes) {
    SkAndroidCodec *codec = as_android_codec(androidCodec);
    if (codec == nullptr || info == nullptr || pixels == nullptr) {
        return kInvalidParameters;
    }
    return static_cast<reskia_codec_result_code_t>(codec->getAndroidPixels(*reinterpret_cast<const SkImageInfo *>(info), pixels, rowBytes));
}

reskia_codec_result_code_t SkAndroidCodec_getPixels(reskia_android_codec_t *androidCodec, const reskia_image_info_t *info, void *pixels, size_t rowBytes) {
    SkAndroidCodec *codec = as_android_codec(androidCodec);
    if (codec == nullptr || info == nullptr || pixels == nullptr) {
        return kInvalidParameters;
    }
    return static_cast<reskia_codec_result_code_t>(codec->getPixels(*reinterpret_cast<const SkImageInfo *>(info), pixels, rowBytes));
}

reskia_codec_t *SkAndroidCodec_codec(reskia_android_codec_t *androidCodec) {
    SkAndroidCodec *codec = as_android_codec(androidCodec);
    return codec != nullptr ? reinterpret_cast<reskia_codec_t *>(codec->codec()) : nullptr;
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
    if (codec == 0) {
        return 0;
    }
    return make_android_codec_handle(SkAndroidCodec::MakeFromCodec(static_sk_codec_take_entity(codec)));
}

sk_android_codec_t SkAndroidCodec_MakeFromStream(sk_stream_t stream, reskia_png_chunk_reader_t *pngChunkReader) {
    if (stream == 0) {
        return 0;
    }
    return make_android_codec_handle(SkAndroidCodec::MakeFromStream(static_sk_stream_take_entity(stream), reinterpret_cast<SkPngChunkReader *>(pngChunkReader)));
}

sk_android_codec_t SkAndroidCodec_MakeFromData(sk_data_t data, reskia_png_chunk_reader_t *pngChunkReader) {
    if (data == 0) {
        return 0;
    }
    return make_android_codec_handle(SkAndroidCodec::MakeFromData(static_sk_data_get_entity(data), reinterpret_cast<SkPngChunkReader *>(pngChunkReader)));
}

#ifdef __cplusplus
}
#endif
