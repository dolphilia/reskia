//
// Created by dolphilia on 2024/02/02.
//

#include "sk_codec.h"

#include "include/codec/SkCodec.h"

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_stream.h"
#include "../handles/static_sk_codec.h"
#include "../handles/static_sk_image_info.h"
#include "../handles/static_sk_i_rect.h"
#include "../handles/static_std_tuple_sk_image_sk_codec_result.h"
#include "../handles/static_std_vector_sk_codec_frame_info.h"
#include "../handles/static_sk_i_size.h"

#include "../handles/static_sk_image_info-internal.h"
#include "../handles/static_sk_i_rect-internal.h"
#include "../handles/static_sk_i_size-internal.h"
#include "../handles/static_sk_stream-internal.h"
#include "../handles/static_std_tuple_sk_image_sk_codec_result-internal.h"
#include "../handles/static_std_vector_sk_codec_frame_info-internal.h"
#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_codec-internal.h"

namespace {

SkCodec *as_codec(reskia_codec_t *codec) {
    return reinterpret_cast<SkCodec *>(codec);
}

const SkCodec *as_codec(const reskia_codec_t *codec) {
    return reinterpret_cast<const SkCodec *>(codec);
}

constexpr reskia_codec_result_code_t kInvalidParameters =
        static_cast<reskia_codec_result_code_t>(SkCodec::kInvalidParameters);

constexpr reskia_codec_result_code_t kInvalidInput =
        static_cast<reskia_codec_result_code_t>(SkCodec::kInvalidInput);

bool is_valid_selection_policy(reskia_codec_selection_policy_t policy) {
    return policy == static_cast<reskia_codec_selection_policy_t>(SkCodec::SelectionPolicy::kPreferStillImage) ||
           policy == static_cast<reskia_codec_selection_policy_t>(SkCodec::SelectionPolicy::kPreferAnimation);
}

sk_codec_t make_codec_handle(std::unique_ptr<SkCodec> codec) {
    if (!codec) {
        return 0;
    }
    return static_sk_codec_make(std::move(codec));
}

} // namespace

extern "C" {

void SkCodec_delete(reskia_codec_t *codec) {
    delete as_codec(codec);
}

sk_image_info_t SkCodec_getInfo(reskia_codec_t *codec) {
    SkCodec *native = as_codec(codec);
    return native != nullptr ? static_sk_image_info_make(native->getInfo()) : 0;
}

sk_i_size_t SkCodec_dimensions(reskia_codec_t *codec) {
    SkCodec *native = as_codec(codec);
    return native != nullptr ? static_sk_i_size_make(native->dimensions()) : 0;
}

sk_i_rect_t SkCodec_bounds(reskia_codec_t *codec) {
    SkCodec *native = as_codec(codec);
    return native != nullptr ? static_sk_i_rect_make(native->bounds()) : 0;
}

const void *SkCodec_getICCProfile(reskia_codec_t *codec) {
    SkCodec *native = as_codec(codec);
    return native != nullptr ? native->getICCProfile() : nullptr;
}

reskia_codec_encoded_origin_t SkCodec_getOrigin(reskia_codec_t *codec) {
    SkCodec *native = as_codec(codec);
    return native != nullptr ? static_cast<reskia_codec_encoded_origin_t>(native->getOrigin()) : -1;
}

sk_i_size_t SkCodec_getScaledDimensions(reskia_codec_t *codec, float desiredScale) {
    SkCodec *native = as_codec(codec);
    return native != nullptr ? static_sk_i_size_make(native->getScaledDimensions(desiredScale)) : 0;
}

bool SkCodec_getValidSubset(reskia_codec_t *codec, reskia_i_rect_t *desiredSubset) {
    SkCodec *native = as_codec(codec);
    if (native == nullptr || desiredSubset == nullptr) {
        return false;
    }
    return native->getValidSubset(reinterpret_cast<SkIRect *>(desiredSubset));
}

reskia_codec_encoded_image_format_t SkCodec_getEncodedFormat(reskia_codec_t *codec) {
    SkCodec *native = as_codec(codec);
    return native != nullptr ? static_cast<reskia_codec_encoded_image_format_t>(native->getEncodedFormat()) : -1;
}

reskia_codec_result_code_t SkCodec_getPixels(reskia_codec_t *codec, const reskia_image_info_t *info, void* pixels, size_t rowBytes, const reskia_codec_options_t *options) {
    SkCodec *native = as_codec(codec);
    if (native == nullptr || info == nullptr || pixels == nullptr) {
        return kInvalidParameters;
    }
    return static_cast<reskia_codec_result_code_t>(native->getPixels(* reinterpret_cast<const SkImageInfo *>(info), pixels, rowBytes, reinterpret_cast<const SkCodec::Options *>(options)));
}

reskia_codec_result_code_t SkCodec_getPixelsWithoutOptions(reskia_codec_t *codec, const reskia_image_info_t *info, void* pixels, size_t rowBytes) {
    SkCodec *native = as_codec(codec);
    if (native == nullptr || info == nullptr || pixels == nullptr) {
        return kInvalidParameters;
    }
    return static_cast<reskia_codec_result_code_t>(native->getPixels(* reinterpret_cast<const SkImageInfo *>(info), pixels, rowBytes));
}

reskia_codec_result_code_t SkCodec_getPixelsFromPixmap(reskia_codec_t *codec, const reskia_pixmap_t *pm, const reskia_codec_options_t *opts) {
    SkCodec *native = as_codec(codec);
    if (native == nullptr || pm == nullptr) {
        return kInvalidParameters;
    }
    return static_cast<reskia_codec_result_code_t>(native->getPixels(* reinterpret_cast<const SkPixmap *>(pm), reinterpret_cast<const SkCodec::Options *>(opts)));
}

tuple_sk_image_sk_codec_result_t SkCodec_getImage(reskia_codec_t *codec, const reskia_image_info_t *info, const reskia_codec_options_t *opts) {
    SkCodec *native = as_codec(codec);
    if (native == nullptr || info == nullptr) {
        return 0;
    }
    return static_tuple_sk_image_sk_codec_result_make(native->getImage(* reinterpret_cast<const SkImageInfo *>(info), reinterpret_cast<const SkCodec::Options *>(opts)));
}

tuple_sk_image_sk_codec_result_t SkCodec_getImageDefault(reskia_codec_t *codec) {
    SkCodec *native = as_codec(codec);
    return native != nullptr ? static_tuple_sk_image_sk_codec_result_make(native->getImage()) : 0;
}

bool SkCodec_queryYUVAInfo(reskia_codec_t *codec, const reskia_supported_data_types_t *supportedDataTypes, reskia_codec_yuva_pixmap_info_t *yuvaPixmapInfo) {
    SkCodec *native = as_codec(codec);
    if (native == nullptr || supportedDataTypes == nullptr || yuvaPixmapInfo == nullptr) {
        return false;
    }
    return native->queryYUVAInfo(* reinterpret_cast<const SkYUVAPixmapInfo::SupportedDataTypes *>(supportedDataTypes), reinterpret_cast<SkYUVAPixmapInfo *>(yuvaPixmapInfo));
}

reskia_codec_result_code_t SkCodec_getYUVAPlanes(reskia_codec_t *codec, const reskia_codec_yuva_pixmaps_t *yuvaPixmaps) {
    SkCodec *native = as_codec(codec);
    if (native == nullptr || yuvaPixmaps == nullptr) {
        return kInvalidInput;
    }
    return static_cast<reskia_codec_result_code_t>(native->getYUVAPlanes(* reinterpret_cast<const SkYUVAPixmaps *>(yuvaPixmaps)));
}

reskia_codec_result_code_t SkCodec_startIncrementalDecode(reskia_codec_t *codec, const reskia_image_info_t *dstInfo, void* dst, size_t rowBytes, const reskia_codec_options_t *options) {
    SkCodec *native = as_codec(codec);
    if (native == nullptr || dstInfo == nullptr || dst == nullptr) {
        return kInvalidParameters;
    }
    return static_cast<reskia_codec_result_code_t>(native->startIncrementalDecode(* reinterpret_cast<const SkImageInfo *>(dstInfo), dst, rowBytes, reinterpret_cast<const SkCodec::Options *>(options)));
}

reskia_codec_result_code_t SkCodec_startIncrementalDecodeWithoutOptions(reskia_codec_t *codec, const reskia_image_info_t *dstInfo, void* dst, size_t rowBytes) {
    SkCodec *native = as_codec(codec);
    if (native == nullptr || dstInfo == nullptr || dst == nullptr) {
        return kInvalidParameters;
    }
    return static_cast<reskia_codec_result_code_t>(native->startIncrementalDecode(* reinterpret_cast<const SkImageInfo *>(dstInfo), dst, rowBytes));
}

reskia_codec_result_code_t SkCodec_incrementalDecode(reskia_codec_t *codec, int* rowsDecoded) {
    SkCodec *native = as_codec(codec);
    return native != nullptr ? static_cast<reskia_codec_result_code_t>(native->incrementalDecode(rowsDecoded)) : kInvalidParameters;
}

reskia_codec_result_code_t SkCodec_startScanlineDecode(reskia_codec_t *codec, const reskia_image_info_t *dstInfo, const reskia_codec_options_t *options) {
    SkCodec *native = as_codec(codec);
    if (native == nullptr || dstInfo == nullptr) {
        return kInvalidParameters;
    }
    return static_cast<reskia_codec_result_code_t>(native->startScanlineDecode(* reinterpret_cast<const SkImageInfo *>(dstInfo), reinterpret_cast<const SkCodec::Options *>(options)));
}

reskia_codec_result_code_t SkCodec_startScanlineDecodeWithoutOptions(reskia_codec_t *codec, const reskia_image_info_t *dstInfo) {
    SkCodec *native = as_codec(codec);
    if (native == nullptr || dstInfo == nullptr) {
        return kInvalidParameters;
    }
    return static_cast<reskia_codec_result_code_t>(native->startScanlineDecode(* reinterpret_cast<const SkImageInfo *>(dstInfo)));
}

int SkCodec_getScanlines(reskia_codec_t *codec, void* dst, int countLines, size_t rowBytes) {
    SkCodec *native = as_codec(codec);
    if (native == nullptr || dst == nullptr || countLines < 0) {
        return 0;
    }
    return native->getScanlines(dst, countLines, rowBytes);
}

bool SkCodec_skipScanlines(reskia_codec_t *codec, int countLines) {
    SkCodec *native = as_codec(codec);
    if (native == nullptr || countLines < 0) {
        return false;
    }
    return native->skipScanlines(countLines);
}

reskia_codec_scanline_order_t SkCodec_getScanlineOrder(reskia_codec_t *codec) {
    SkCodec *native = as_codec(codec);
    return native != nullptr ? static_cast<reskia_codec_scanline_order_t>(native->getScanlineOrder()) : -1;
}

int SkCodec_nextScanline(reskia_codec_t *codec) {
    SkCodec *native = as_codec(codec);
    return native != nullptr ? native->nextScanline() : -1;
}

int SkCodec_outputScanline(reskia_codec_t *codec, int inputScanline) {
    SkCodec *native = as_codec(codec);
    return native != nullptr ? native->outputScanline(inputScanline) : -1;
}

int SkCodec_getFrameCount(reskia_codec_t *codec) {
    SkCodec *native = as_codec(codec);
    return native != nullptr ? native->getFrameCount() : 0;
}

bool SkCodec_getFrameInfo(reskia_codec_t *codec, int index, reskia_codec_frame_info_t *info) {
    SkCodec *native = as_codec(codec);
    if (native == nullptr || index < 0 || info == nullptr) {
        return false;
    }
    return native->getFrameInfo(index, reinterpret_cast<SkCodec::FrameInfo *>(info));
}

vector_sk_codec_frame_info_t SkCodec_getFrameInfoList(reskia_codec_t *codec) {
    SkCodec *native = as_codec(codec);
    return native != nullptr ? static_vector_sk_codec_frame_info_make(native->getFrameInfo()) : 0;
}

int SkCodec_getRepetitionCount(reskia_codec_t *codec) {
    SkCodec *native = as_codec(codec);
    return native != nullptr ? native->getRepetitionCount() : 0;
}

// static

size_t SkCodec_MinBufferedBytesNeeded() {
    return SkCodec::MinBufferedBytesNeeded();
}

const char* SkCodec_ResultToString(reskia_codec_result_code_t result) {
    return SkCodec::ResultToString(static_cast<SkCodec::Result>(result));
}

sk_codec_t SkCodec_MakeFromStream(sk_stream_t stream, reskia_codec_result_t *result, reskia_png_chunk_reader_t *pngChunkReader, reskia_codec_selection_policy_t selectionPolicy) {
    if (!is_valid_selection_policy(selectionPolicy)) {
        if (result != nullptr) {
            *reinterpret_cast<SkCodec::Result *>(result) = SkCodec::kInvalidParameters;
        }
        return 0;
    }
    std::unique_ptr<SkStream> native_stream = static_sk_stream_take_entity(stream);
    if (!native_stream) {
        if (result != nullptr) {
            *reinterpret_cast<SkCodec::Result *>(result) = SkCodec::kInvalidInput;
        }
        return 0;
    }
    return make_codec_handle(SkCodec::MakeFromStream(std::move(native_stream), reinterpret_cast<SkCodec::Result *>(result), reinterpret_cast<SkPngChunkReader *>(pngChunkReader), static_cast<SkCodec::SelectionPolicy>(selectionPolicy)));
}

sk_codec_t SkCodec_MakeFromData(sk_data_t data, reskia_png_chunk_reader_t *pngChunkReader) {
    sk_sp<SkData> native_data = static_sk_data_get_entity(data);
    if (!native_data) {
        return 0;
    }
    return make_codec_handle(SkCodec::MakeFromData(std::move(native_data), reinterpret_cast<SkPngChunkReader *>(pngChunkReader)));
}

//void SkCodec_Register(bool (*peek)(const void*, size_t), std::unique_ptr<SkCodec> (*make)(std::unique_ptr<SkStream>, SkCodec::Result*)) {
//    SkCodec::Register(peek, make);
//}

}
