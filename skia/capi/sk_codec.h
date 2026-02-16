//
// Created by dolphilia on 2024/02/02.
//

#ifndef RAIA_SKIA_SK_CODEC_H
#define RAIA_SKIA_SK_CODEC_H

#include <stddef.h>
#include <stdint.h>
#include "../handles/static_sk_codec.h"
#include "../handles/static_sk_i_rect.h"
#include "../handles/static_sk_i_size.h"
#include "../handles/static_sk_image_info.h"
#include "../handles/static_sk_stream.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_codec_t reskia_codec_t;
typedef struct reskia_codec_frame_info_t reskia_codec_frame_info_t;
typedef struct reskia_codec_options_t reskia_codec_options_t;
typedef struct reskia_codec_result_t reskia_codec_result_t;
typedef struct reskia_codec_yuva_pixmap_info_t reskia_codec_yuva_pixmap_info_t;
typedef struct reskia_codec_yuva_pixmaps_t reskia_codec_yuva_pixmaps_t;
typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_image_info_t reskia_image_info_t;
typedef struct reskia_pixmap_t reskia_pixmap_t;
typedef struct reskia_png_chunk_reader_t reskia_png_chunk_reader_t;
typedef struct reskia_supported_data_types_t reskia_supported_data_types_t;
typedef int32_t reskia_codec_encoded_origin_t;
typedef int32_t reskia_codec_encoded_image_format_t;
typedef int32_t reskia_codec_result_code_t;
typedef int32_t reskia_codec_scanline_order_t;
typedef int32_t reskia_codec_selection_policy_t;

void SkCodec_delete(reskia_codec_t *codec); // (SkCodec* codec)
sk_image_info_t SkCodec_getInfo(reskia_codec_t *codec); // (SkCodec* codec) -> sk_image_info_t
sk_i_size_t SkCodec_dimensions(reskia_codec_t *codec); // (SkCodec* codec) -> sk_i_size_t
sk_i_rect_t SkCodec_bounds(reskia_codec_t *codec); // (SkCodec* codec) -> sk_i_rect_t
const void * SkCodec_getICCProfile(reskia_codec_t *codec); // (SkCodec* codec) -> const skcms_ICCProfile*
reskia_codec_encoded_origin_t SkCodec_getOrigin(reskia_codec_t *codec); // (SkCodec* codec) -> SkEncodedOrigin
sk_i_size_t SkCodec_getScaledDimensions(reskia_codec_t *codec, float desiredScale); // (SkCodec* codec, float desiredScale) -> sk_i_size_t
bool SkCodec_getValidSubset(reskia_codec_t *codec, reskia_i_rect_t *desiredSubset); // (SkCodec* codec, SkIRect* desiredSubset) -> bool
reskia_codec_encoded_image_format_t SkCodec_getEncodedFormat(reskia_codec_t *codec); // (SkCodec* codec) -> SkEncodedImageFormat
reskia_codec_result_code_t SkCodec_getPixels(reskia_codec_t *codec, const reskia_image_info_t *info, void* pixels, size_t rowBytes, const reskia_codec_options_t *options); // (SkCodec* codec, const SkImageInfo* info, void* pixels, size_t rowBytes, const SkCodec::Options* options) -> SkCodec::Result
reskia_codec_result_code_t SkCodec_getPixelsWithoutOptions(reskia_codec_t *codec, const reskia_image_info_t *info, void* pixels, size_t rowBytes); // (SkCodec* codec, const SkImageInfo* info, void* pixels, size_t rowBytes) -> SkCodec::Result
reskia_codec_result_code_t SkCodec_getPixelsFromPixmap(reskia_codec_t *codec, const reskia_pixmap_t *pm, const reskia_codec_options_t *opts); // (SkCodec* codec, const SkPixmap* pm, const SkCodec::Options* opts) -> SkCodec::Result
int SkCodec_getImage(reskia_codec_t *codec, const reskia_image_info_t *info, const reskia_codec_options_t *opts); // (SkCodec* codec, const SkImageInfo* info, const SkCodec::Options* opts) -> int
int SkCodec_getImageDefault(reskia_codec_t *codec); // (SkCodec* codec) -> int
bool SkCodec_queryYUVAInfo(reskia_codec_t *codec, const reskia_supported_data_types_t *supportedDataTypes, reskia_codec_yuva_pixmap_info_t *yuvaPixmapInfo); // (SkCodec* codec, const SkYUVAPixmapInfo::SupportedDataTypes* supportedDataTypes, SkYUVAPixmapInfo* yuvaPixmapInfo) -> bool
reskia_codec_result_code_t SkCodec_getYUVAPlanes(reskia_codec_t *codec, const reskia_codec_yuva_pixmaps_t *yuvaPixmaps); // (SkCodec* codec, const SkYUVAPixmaps* yuvaPixmaps) -> SkCodec::Result
reskia_codec_result_code_t SkCodec_startIncrementalDecode(reskia_codec_t *codec, const reskia_image_info_t *dstInfo, void* dst, size_t rowBytes, const reskia_codec_options_t *options); // (SkCodec* codec, const SkImageInfo* dstInfo, void* dst, size_t rowBytes, const SkCodec::Options* options) -> SkCodec::Result
reskia_codec_result_code_t SkCodec_startIncrementalDecodeWithoutOptions(reskia_codec_t *codec, const reskia_image_info_t *dstInfo, void* dst, size_t rowBytes); // (SkCodec* codec, const SkImageInfo* dstInfo, void* dst, size_t rowBytes) -> SkCodec::Result
reskia_codec_result_code_t SkCodec_incrementalDecode(reskia_codec_t *codec, int* rowsDecoded); // (SkCodec* codec, int* rowsDecoded) -> SkCodec::Result
reskia_codec_result_code_t SkCodec_startScanlineDecode(reskia_codec_t *codec, const reskia_image_info_t *dstInfo, const reskia_codec_options_t *options); // (SkCodec* codec, const SkImageInfo* dstInfo, const SkCodec::Options* options) -> SkCodec::Result
reskia_codec_result_code_t SkCodec_startScanlineDecodeWithoutOptions(reskia_codec_t *codec, const reskia_image_info_t *dstInfo); // (SkCodec* codec, const SkImageInfo* dstInfo) -> SkCodec::Result
int SkCodec_getScanlines(reskia_codec_t *codec, void* dst, int countLines, size_t rowBytes); // (SkCodec* codec, void* dst, int countLines, size_t rowBytes) -> int
bool SkCodec_skipScanlines(reskia_codec_t *codec, int countLines); // (SkCodec* codec, int countLines) -> bool
reskia_codec_scanline_order_t SkCodec_getScanlineOrder(reskia_codec_t *codec); // (SkCodec* codec) -> SkCodec::SkScanlineOrder
int SkCodec_nextScanline(reskia_codec_t *codec); // (SkCodec* codec) -> int
int SkCodec_outputScanline(reskia_codec_t *codec, int inputScanline); // (SkCodec* codec, int inputScanline) -> int
int SkCodec_getFrameCount(reskia_codec_t *codec); // (SkCodec* codec) -> int
bool SkCodec_getFrameInfo(reskia_codec_t *codec, int index, reskia_codec_frame_info_t *info); // (SkCodec* codec, int index, SkCodec::FrameInfo* info) -> bool
int SkCodec_getFrameInfoList(reskia_codec_t *codec); // (SkCodec* codec) -> int
int SkCodec_getRepetitionCount(reskia_codec_t *codec); // (SkCodec* codec) -> int

// static

size_t SkCodec_MinBufferedBytesNeeded(); // () -> size_t
const char* SkCodec_ResultToString(reskia_codec_result_code_t result); // (SkCodec::Result result) -> const char*
sk_codec_t SkCodec_MakeFromStream(sk_stream_t stream, reskia_codec_result_t *result, reskia_png_chunk_reader_t *pngChunkReader, reskia_codec_selection_policy_t selectionPolicy); // (sk_stream_t stream, SkCodec::Result* result, SkPngChunkReader* pngChunkReader, SkCodec::SelectionPolicy selectionPolicy) -> sk_codec_t
sk_codec_t SkCodec_MakeFromData(sk_stream_t stream, reskia_png_chunk_reader_t *pngChunkReader); // (sk_stream_t stream, SkPngChunkReader* pngChunkReader) -> sk_codec_t

//void SkCodec_Register(bool (*peek)(const void*, size_t), std::unique_ptr<SkCodec> (*make)(std::unique_ptr<SkStream>, SkCodec::Result*));

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_CODEC_H
