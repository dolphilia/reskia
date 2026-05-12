//
// Created by dolphilia on 2024/02/02.
//

#ifndef RAIA_SKIA_SK_CODEC_H
#define RAIA_SKIA_SK_CODEC_H

#include <stddef.h>
#include <stdint.h>
#include "../handles/static_sk_codec.h"
#include "../handles/static_sk_data.h"
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

void SkCodec_delete(reskia_codec_t *codec); // (SkCodec* codec). NULL codec is no-op.
sk_image_info_t SkCodec_getInfo(reskia_codec_t *codec); // (SkCodec* codec) -> sk_image_info_t. NULL codec returns 0.
sk_i_size_t SkCodec_dimensions(reskia_codec_t *codec); // (SkCodec* codec) -> sk_i_size_t. NULL codec returns 0.
sk_i_rect_t SkCodec_bounds(reskia_codec_t *codec); // (SkCodec* codec) -> sk_i_rect_t. NULL codec returns 0.
const void * SkCodec_getICCProfile(reskia_codec_t *codec); // (SkCodec* codec) -> const skcms_ICCProfile*. NULL codec returns NULL.
reskia_codec_encoded_origin_t SkCodec_getOrigin(reskia_codec_t *codec); // (SkCodec* codec) -> SkEncodedOrigin. NULL codec returns -1.
sk_i_size_t SkCodec_getScaledDimensions(reskia_codec_t *codec, float desiredScale); // (SkCodec* codec, float desiredScale) -> sk_i_size_t. NULL codec returns 0.
bool SkCodec_getValidSubset(reskia_codec_t *codec, reskia_i_rect_t *desiredSubset); // (SkCodec* codec, SkIRect* desiredSubset) -> bool. codec/subset are required.
reskia_codec_encoded_image_format_t SkCodec_getEncodedFormat(reskia_codec_t *codec); // (SkCodec* codec) -> SkEncodedImageFormat. NULL codec returns -1.
/**
 * codec/info/pixels are required.
 * invalid input returns kInvalidParameters.
 */
reskia_codec_result_code_t SkCodec_getPixels(reskia_codec_t *codec, const reskia_image_info_t *info, void* pixels, size_t rowBytes, const reskia_codec_options_t *options);
/**
 * codec/info/pixels are required.
 * invalid input returns kInvalidParameters.
 */
reskia_codec_result_code_t SkCodec_getPixelsWithoutOptions(reskia_codec_t *codec, const reskia_image_info_t *info, void* pixels, size_t rowBytes);
/**
 * codec/pm are required.
 * invalid input returns kInvalidParameters.
 */
reskia_codec_result_code_t SkCodec_getPixelsFromPixmap(reskia_codec_t *codec, const reskia_pixmap_t *pm, const reskia_codec_options_t *opts);
/**
 * codec/info are required.
 * invalid input returns 0.
 */
int SkCodec_getImage(reskia_codec_t *codec, const reskia_image_info_t *info, const reskia_codec_options_t *opts);
int SkCodec_getImageDefault(reskia_codec_t *codec); // (SkCodec* codec) -> int. NULL codec returns 0.
/**
 * codec/supportedDataTypes/yuvaPixmapInfo are required.
 */
bool SkCodec_queryYUVAInfo(reskia_codec_t *codec, const reskia_supported_data_types_t *supportedDataTypes, reskia_codec_yuva_pixmap_info_t *yuvaPixmapInfo);
/**
 * codec/yuvaPixmaps are required.
 * invalid input returns kInvalidInput.
 */
reskia_codec_result_code_t SkCodec_getYUVAPlanes(reskia_codec_t *codec, const reskia_codec_yuva_pixmaps_t *yuvaPixmaps);
/**
 * codec/dstInfo/dst are required.
 * invalid input returns kInvalidParameters.
 */
reskia_codec_result_code_t SkCodec_startIncrementalDecode(reskia_codec_t *codec, const reskia_image_info_t *dstInfo, void* dst, size_t rowBytes, const reskia_codec_options_t *options);
/**
 * codec/dstInfo/dst are required.
 * invalid input returns kInvalidParameters.
 */
reskia_codec_result_code_t SkCodec_startIncrementalDecodeWithoutOptions(reskia_codec_t *codec, const reskia_image_info_t *dstInfo, void* dst, size_t rowBytes);
/**
 * rowsDecoded may be NULL.
 * NULL codec returns kInvalidParameters.
 */
reskia_codec_result_code_t SkCodec_incrementalDecode(reskia_codec_t *codec, int* rowsDecoded);
/**
 * codec/dstInfo are required.
 * invalid input returns kInvalidParameters.
 */
reskia_codec_result_code_t SkCodec_startScanlineDecode(reskia_codec_t *codec, const reskia_image_info_t *dstInfo, const reskia_codec_options_t *options);
/**
 * codec/dstInfo are required.
 * invalid input returns kInvalidParameters.
 */
reskia_codec_result_code_t SkCodec_startScanlineDecodeWithoutOptions(reskia_codec_t *codec, const reskia_image_info_t *dstInfo);
/**
 * codec/dst are required.
 * negative countLines returns 0.
 */
int SkCodec_getScanlines(reskia_codec_t *codec, void* dst, int countLines, size_t rowBytes);
bool SkCodec_skipScanlines(reskia_codec_t *codec, int countLines); // NULL codec or negative countLines returns false.
reskia_codec_scanline_order_t SkCodec_getScanlineOrder(reskia_codec_t *codec); // (SkCodec* codec) -> SkCodec::SkScanlineOrder. NULL codec returns -1.
int SkCodec_nextScanline(reskia_codec_t *codec); // (SkCodec* codec) -> int. NULL codec returns -1.
int SkCodec_outputScanline(reskia_codec_t *codec, int inputScanline); // (SkCodec* codec, int inputScanline) -> int. NULL codec returns -1.
int SkCodec_getFrameCount(reskia_codec_t *codec); // (SkCodec* codec) -> int. NULL codec returns 0.
/**
 * codec/info are required.
 * negative index returns false.
 */
bool SkCodec_getFrameInfo(reskia_codec_t *codec, int index, reskia_codec_frame_info_t *info);
int SkCodec_getFrameInfoList(reskia_codec_t *codec); // (SkCodec* codec) -> int. NULL codec returns 0.
int SkCodec_getRepetitionCount(reskia_codec_t *codec); // (SkCodec* codec) -> int. NULL codec returns 0.

// static

size_t SkCodec_MinBufferedBytesNeeded(); // () -> size_t
const char* SkCodec_ResultToString(reskia_codec_result_code_t result); // (SkCodec::Result result) -> const char*
/**
 * stream must be a valid owned stream handle.
 * returns 0 on invalid input or decode failure.
 */
sk_codec_t SkCodec_MakeFromStream(sk_stream_t stream, reskia_codec_result_t *result, reskia_png_chunk_reader_t *pngChunkReader, reskia_codec_selection_policy_t selectionPolicy);
/**
 * data must be a valid SkData handle.
 * returns 0 on invalid input or decode failure.
 */
sk_codec_t SkCodec_MakeFromData(sk_data_t data, reskia_png_chunk_reader_t *pngChunkReader);

//void SkCodec_Register(bool (*peek)(const void*, size_t), std::unique_ptr<SkCodec> (*make)(std::unique_ptr<SkStream>, SkCodec::Result*));

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_CODEC_H
