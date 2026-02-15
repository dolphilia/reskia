//
// Created by dolphilia on 2024/02/02.
//

#include "sk_codec.h"

#include "include/codec/SkCodec.h"

#include "../static/static_sk_data.h"
#include "../static/static_sk_stream.h"
#include "../static/static_sk_codec.h"
#include "../static/static_sk_image_info.h"
#include "../static/static_sk_i_rect.h"
#include "../static/static_std_tuple_sk_image_sk_codec_result.h"
#include "../static/static_std_vector_sk_codec_frame_info.h"
#include "../static/static_sk_i_size.h"

#include "../static/static_sk_image_info-internal.h"
#include "../static/static_sk_i_rect-internal.h"
#include "../static/static_sk_i_size-internal.h"
#include "../static/static_sk_stream-internal.h"
#include "../static/static_std_tuple_sk_image_sk_codec_result-internal.h"
#include "../static/static_std_vector_sk_codec_frame_info-internal.h"
#include "../static/static_sk_data-internal.h"
#include "../static/static_sk_codec-internal.h"

extern "C" {

void SkCodec_delete(reskia_codec_t *codec) {
    delete reinterpret_cast<SkCodec *>(codec);
}

sk_image_info_t SkCodec_getInfo(reskia_codec_t *codec) {
    return static_sk_image_info_make(reinterpret_cast<SkCodec *>(codec)->getInfo());
}

sk_i_size_t SkCodec_dimensions(reskia_codec_t *codec) {
    return static_sk_i_size_make(reinterpret_cast<SkCodec *>(codec)->dimensions());
}

sk_i_rect_t SkCodec_bounds(reskia_codec_t *codec) {
    return static_sk_i_rect_make(reinterpret_cast<SkCodec *>(codec)->bounds());
}

const void *SkCodec_getICCProfile(reskia_codec_t *codec) {
    return reinterpret_cast<SkCodec *>(codec)->getICCProfile();
}

reskia_codec_encoded_origin_t SkCodec_getOrigin(reskia_codec_t *codec) {
    return static_cast<reskia_codec_encoded_origin_t>(reinterpret_cast<SkCodec *>(codec)->getOrigin());
}

sk_i_size_t SkCodec_getScaledDimensions(reskia_codec_t *codec, float desiredScale) {
    return static_sk_i_size_make(reinterpret_cast<SkCodec *>(codec)->getScaledDimensions(desiredScale));
}

bool SkCodec_getValidSubset(reskia_codec_t *codec, reskia_i_rect_t *desiredSubset) {
    return reinterpret_cast<SkCodec *>(codec)->getValidSubset(reinterpret_cast<SkIRect *>(desiredSubset));
}

reskia_codec_encoded_image_format_t SkCodec_getEncodedFormat(reskia_codec_t *codec) {
    return static_cast<reskia_codec_encoded_image_format_t>(reinterpret_cast<SkCodec *>(codec)->getEncodedFormat());
}

reskia_codec_result_code_t SkCodec_getPixels(reskia_codec_t *codec, const reskia_image_info_t *info, void* pixels, size_t rowBytes, const reskia_codec_options_t *options) {
    return static_cast<reskia_codec_result_code_t>(reinterpret_cast<SkCodec *>(codec)->getPixels(* reinterpret_cast<const SkImageInfo *>(info), pixels, rowBytes, reinterpret_cast<const SkCodec::Options *>(options)));
}

reskia_codec_result_code_t SkCodec_getPixels_2(reskia_codec_t *codec, const reskia_image_info_t *info, void* pixels, size_t rowBytes) {
    return static_cast<reskia_codec_result_code_t>(reinterpret_cast<SkCodec *>(codec)->getPixels(* reinterpret_cast<const SkImageInfo *>(info), pixels, rowBytes));
}

reskia_codec_result_code_t SkCodec_getPixels_3(reskia_codec_t *codec, const reskia_pixmap_t *pm, const reskia_codec_options_t *opts) {
    return static_cast<reskia_codec_result_code_t>(reinterpret_cast<SkCodec *>(codec)->getPixels(* reinterpret_cast<const SkPixmap *>(pm), reinterpret_cast<const SkCodec::Options *>(opts)));
}

tuple_sk_image_sk_codec_result_t SkCodec_getImage(reskia_codec_t *codec, const reskia_image_info_t *info, const reskia_codec_options_t *opts) {
    return static_tuple_sk_image_sk_codec_result_make(reinterpret_cast<SkCodec *>(codec)->getImage(* reinterpret_cast<const SkImageInfo *>(info), reinterpret_cast<const SkCodec::Options *>(opts)));
}

tuple_sk_image_sk_codec_result_t SkCodec_getImage_2(reskia_codec_t *codec) {
    return static_tuple_sk_image_sk_codec_result_make(reinterpret_cast<SkCodec *>(codec)->getImage());
}

bool SkCodec_queryYUVAInfo(reskia_codec_t *codec, const reskia_supported_data_types_t *supportedDataTypes, reskia_codec_yuva_pixmap_info_t *yuvaPixmapInfo) {
    return reinterpret_cast<SkCodec *>(codec)->queryYUVAInfo(* reinterpret_cast<const SkYUVAPixmapInfo::SupportedDataTypes *>(supportedDataTypes), reinterpret_cast<SkYUVAPixmapInfo *>(yuvaPixmapInfo));
}

reskia_codec_result_code_t SkCodec_getYUVAPlanes(reskia_codec_t *codec, const reskia_codec_yuva_pixmaps_t *yuvaPixmaps) {
    return static_cast<reskia_codec_result_code_t>(reinterpret_cast<SkCodec *>(codec)->getYUVAPlanes(* reinterpret_cast<const SkYUVAPixmaps *>(yuvaPixmaps)));
}

reskia_codec_result_code_t SkCodec_startIncrementalDecode(reskia_codec_t *codec, const reskia_image_info_t *dstInfo, void* dst, size_t rowBytes, const reskia_codec_options_t *options) {
    return static_cast<reskia_codec_result_code_t>(reinterpret_cast<SkCodec *>(codec)->startIncrementalDecode(* reinterpret_cast<const SkImageInfo *>(dstInfo), dst, rowBytes, reinterpret_cast<const SkCodec::Options *>(options)));
}

reskia_codec_result_code_t SkCodec_startIncrementalDecode_2(reskia_codec_t *codec, const reskia_image_info_t *dstInfo, void* dst, size_t rowBytes) {
    return static_cast<reskia_codec_result_code_t>(reinterpret_cast<SkCodec *>(codec)->startIncrementalDecode(* reinterpret_cast<const SkImageInfo *>(dstInfo), dst, rowBytes));
}

reskia_codec_result_code_t SkCodec_incrementalDecode(reskia_codec_t *codec, int* rowsDecoded) {
    return static_cast<reskia_codec_result_code_t>(reinterpret_cast<SkCodec *>(codec)->incrementalDecode(rowsDecoded));
}

reskia_codec_result_code_t SkCodec_startScanlineDecode(reskia_codec_t *codec, const reskia_image_info_t *dstInfo, const reskia_codec_options_t *options) {
    return static_cast<reskia_codec_result_code_t>(reinterpret_cast<SkCodec *>(codec)->startScanlineDecode(* reinterpret_cast<const SkImageInfo *>(dstInfo), reinterpret_cast<const SkCodec::Options *>(options)));
}

reskia_codec_result_code_t SkCodec_startScanlineDecode_2(reskia_codec_t *codec, const reskia_image_info_t *dstInfo) {
    return static_cast<reskia_codec_result_code_t>(reinterpret_cast<SkCodec *>(codec)->startScanlineDecode(* reinterpret_cast<const SkImageInfo *>(dstInfo)));
}

int SkCodec_getScanlines(reskia_codec_t *codec, void* dst, int countLines, size_t rowBytes) {
    return reinterpret_cast<SkCodec *>(codec)->getScanlines(dst, countLines, rowBytes);
}

bool SkCodec_skipScanlines(reskia_codec_t *codec, int countLines) {
    return reinterpret_cast<SkCodec *>(codec)->skipScanlines(countLines);
}

reskia_codec_scanline_order_t SkCodec_getScanlineOrder(reskia_codec_t *codec) {
    return static_cast<reskia_codec_scanline_order_t>(reinterpret_cast<SkCodec *>(codec)->getScanlineOrder());
}

int SkCodec_nextScanline(reskia_codec_t *codec) {
    return reinterpret_cast<SkCodec *>(codec)->nextScanline();
}

int SkCodec_outputScanline(reskia_codec_t *codec, int inputScanline) {
    return reinterpret_cast<SkCodec *>(codec)->outputScanline(inputScanline);
}

int SkCodec_getFrameCount(reskia_codec_t *codec) {
    return reinterpret_cast<SkCodec *>(codec)->getFrameCount();
}

bool SkCodec_getFrameInfo(reskia_codec_t *codec, int index, reskia_codec_frame_info_t *info) {
    return reinterpret_cast<SkCodec *>(codec)->getFrameInfo(index, reinterpret_cast<SkCodec::FrameInfo *>(info));
}

vector_sk_codec_frame_info_t SkCodec_getFrameInfo_2(reskia_codec_t *codec) {
    return static_vector_sk_codec_frame_info_make(reinterpret_cast<SkCodec *>(codec)->getFrameInfo());
}

int SkCodec_getRepetitionCount(reskia_codec_t *codec) {
    return reinterpret_cast<SkCodec *>(codec)->getRepetitionCount();
}

// static

size_t SkCodec_MinBufferedBytesNeeded() {
    return SkCodec::MinBufferedBytesNeeded();
}

const char* SkCodec_ResultToString(reskia_codec_result_code_t result) {
    return SkCodec::ResultToString(static_cast<SkCodec::Result>(result));
}

sk_codec_t SkCodec_MakeFromStream(sk_stream_t stream, reskia_codec_result_t *result, reskia_png_chunk_reader_t *pngChunkReader, reskia_codec_selection_policy_t selectionPolicy) {
    return static_sk_codec_make(SkCodec::MakeFromStream(static_sk_stream_take_entity(stream), reinterpret_cast<SkCodec::Result *>(result), reinterpret_cast<SkPngChunkReader *>(pngChunkReader), static_cast<SkCodec::SelectionPolicy>(selectionPolicy)));
}

sk_codec_t SkCodec_MakeFromData(sk_stream_t stream, reskia_png_chunk_reader_t *pngChunkReader) {
    return static_sk_codec_make(SkCodec::MakeFromData(static_sk_data_get_entity(stream), reinterpret_cast<SkPngChunkReader *>(pngChunkReader)));
}

//void SkCodec_Register(bool (*peek)(const void*, size_t), std::unique_ptr<SkCodec> (*make)(std::unique_ptr<SkStream>, SkCodec::Result*)) {
//    SkCodec::Register(peek, make);
//}

}
