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

void SkCodec_delete(void * codec) {
    delete static_cast<SkCodec *>(codec);
}

sk_image_info_t SkCodec_getInfo(void * codec) {
    return static_sk_image_info_make(static_cast<SkCodec *>(codec)->getInfo());
}

sk_i_size_t SkCodec_dimensions(void * codec) {
    return static_sk_i_size_make(static_cast<SkCodec *>(codec)->dimensions());
}

sk_i_rect_t SkCodec_bounds(void * codec) {
    return static_sk_i_rect_make(static_cast<SkCodec *>(codec)->bounds());
}

const void * SkCodec_getICCProfile(void * codec) {
    return static_cast<SkCodec *>(codec)->getICCProfile();
}

int SkCodec_getOrigin(void * codec) {
    return static_cast<SkCodec *>(codec)->getOrigin();
}

sk_i_size_t SkCodec_getScaledDimensions(void * codec, float desiredScale) {
    return static_sk_i_size_make(static_cast<SkCodec *>(codec)->getScaledDimensions(desiredScale));
}

bool SkCodec_getValidSubset(void * codec, void * desiredSubset) {
    return static_cast<SkCodec *>(codec)->getValidSubset(static_cast<SkIRect *>(desiredSubset));
}

int SkCodec_getEncodedFormat(void * codec) {
    return static_cast<int>(static_cast<SkCodec *>(codec)->getEncodedFormat());
}

int SkCodec_getPixels(void * codec, const void * info, void* pixels, size_t rowBytes, const void * options) {
    return static_cast<SkCodec *>(codec)->getPixels(* static_cast<const SkImageInfo *>(info), pixels, rowBytes, static_cast<const SkCodec::Options *>(options));
}

int SkCodec_getPixels_2(void * codec, const void * info, void* pixels, size_t rowBytes) {
    return static_cast<SkCodec *>(codec)->getPixels(* static_cast<const SkImageInfo *>(info), pixels, rowBytes);
}

int SkCodec_getPixels_3(void * codec, const void * pm, const void * opts) {
    return static_cast<SkCodec *>(codec)->getPixels(* static_cast<const SkPixmap *>(pm), static_cast<const SkCodec::Options *>(opts));
}

tuple_sk_image_sk_codec_result_t SkCodec_getImage(void * codec, const void * info, const void * opts) {
    return static_tuple_sk_image_sk_codec_result_make(static_cast<SkCodec *>(codec)->getImage(* static_cast<const SkImageInfo *>(info), static_cast<const SkCodec::Options *>(opts)));
}

tuple_sk_image_sk_codec_result_t SkCodec_getImage_2(void * codec) {
    return static_tuple_sk_image_sk_codec_result_make(static_cast<SkCodec *>(codec)->getImage());
}

bool SkCodec_queryYUVAInfo(void * codec, const void * supportedDataTypes, void * yuvaPixmapInfo) {
    return static_cast<SkCodec *>(codec)->queryYUVAInfo(* static_cast<const SkYUVAPixmapInfo::SupportedDataTypes *>(supportedDataTypes), static_cast<SkYUVAPixmapInfo *>(yuvaPixmapInfo));
}

int SkCodec_getYUVAPlanes(void * codec, const void * yuvaPixmaps) {
    return static_cast<SkCodec *>(codec)->getYUVAPlanes(* static_cast<const SkYUVAPixmaps *>(yuvaPixmaps));
}

int SkCodec_startIncrementalDecode(void * codec, const void * dstInfo, void* dst, size_t rowBytes, const void * options) {
    return static_cast<SkCodec *>(codec)->startIncrementalDecode(* static_cast<const SkImageInfo *>(dstInfo), dst, rowBytes, static_cast<const SkCodec::Options *>(options));
}

int SkCodec_startIncrementalDecode_2(void * codec, const void * dstInfo, void* dst, size_t rowBytes) {
    return static_cast<SkCodec *>(codec)->startIncrementalDecode(* static_cast<const SkImageInfo *>(dstInfo), dst, rowBytes);
}

int SkCodec_incrementalDecode(void * codec, int* rowsDecoded) {
    return static_cast<SkCodec *>(codec)->incrementalDecode(rowsDecoded);
}

int SkCodec_startScanlineDecode(void * codec, const void * dstInfo, const void * options) {
    return static_cast<SkCodec *>(codec)->startScanlineDecode(* static_cast<const SkImageInfo *>(dstInfo), static_cast<const SkCodec::Options *>(options));
}

int SkCodec_startScanlineDecode_2(void * codec, const void * dstInfo) {
    return static_cast<SkCodec *>(codec)->startScanlineDecode(* static_cast<const SkImageInfo *>(dstInfo));
}

int SkCodec_getScanlines(void * codec, void* dst, int countLines, size_t rowBytes) {
    return static_cast<SkCodec *>(codec)->getScanlines(dst, countLines, rowBytes);
}

bool SkCodec_skipScanlines(void * codec, int countLines) {
    return static_cast<SkCodec *>(codec)->skipScanlines(countLines);
}

int SkCodec_getScanlineOrder(void * codec) {
    return static_cast<SkCodec *>(codec)->getScanlineOrder();
}

int SkCodec_nextScanline(void * codec) {
    return static_cast<SkCodec *>(codec)->nextScanline();
}

int SkCodec_outputScanline(void * codec, int inputScanline) {
    return static_cast<SkCodec *>(codec)->outputScanline(inputScanline);
}

int SkCodec_getFrameCount(void * codec) {
    return static_cast<SkCodec *>(codec)->getFrameCount();
}

bool SkCodec_getFrameInfo(void * codec, int index, void * info) {
    return static_cast<SkCodec *>(codec)->getFrameInfo(index, static_cast<SkCodec::FrameInfo *>(info));
}

vector_sk_codec_frame_info_t SkCodec_getFrameInfo_2(void * codec) {
    return static_vector_sk_codec_frame_info_make(static_cast<SkCodec *>(codec)->getFrameInfo());
}

int SkCodec_getRepetitionCount(void * codec) {
    return static_cast<SkCodec *>(codec)->getRepetitionCount();
}

// static

size_t SkCodec_MinBufferedBytesNeeded() {
    return SkCodec::MinBufferedBytesNeeded();
}

const char* SkCodec_ResultToString(int result) {
    return SkCodec::ResultToString(static_cast<SkCodec::Result>(result));
}

sk_codec_t SkCodec_MakeFromStream(sk_stream_t stream, void * result, void * pngChunkReader, int selectionPolicy) {
    return static_sk_codec_make(SkCodec::MakeFromStream(static_sk_stream_take_entity(stream), static_cast<SkCodec::Result *>(result), static_cast<SkPngChunkReader *>(pngChunkReader), static_cast<SkCodec::SelectionPolicy>(selectionPolicy)));
}

sk_codec_t SkCodec_MakeFromData(sk_stream_t stream, void * pngChunkReader) {
    return static_sk_codec_make(SkCodec::MakeFromData(static_sk_data_get_entity(stream), static_cast<SkPngChunkReader *>(pngChunkReader)));
}

//void SkCodec_Register(bool (*peek)(const void*, size_t), std::unique_ptr<SkCodec> (*make)(std::unique_ptr<SkStream>, SkCodec::Result*)) {
//    SkCodec::Register(peek, make);
//}

}
