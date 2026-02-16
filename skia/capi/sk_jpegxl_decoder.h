//
// Created by dolphilia on 2024/02/02.
//

#ifndef RAIA_SKIA_SK_JPEGXL_DECODER_H
#define RAIA_SKIA_SK_JPEGXL_DECODER_H

#include <stddef.h>
#include <stdint.h>

#include "../handles/static_sk_stream.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_codec.h"
#include "../handles/static_sk_codecs_decoder.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_codec_result_t reskia_codec_result_t;
typedef struct reskia_codecs_decode_context_t reskia_codecs_decode_context_t;

bool SkJpegxlDecoder_IsJpegxl(const uint8_t *ptr, size_t size);
sk_codec_t SkJpegxlDecoder_Decode(sk_stream_t stream, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext);
sk_codec_t SkJpegxlDecoder_DecodeFromData(sk_data_t data, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext);
sk_codecs_decoder_t SkJpegxlDecoder_Decoder();

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_JPEGXL_DECODER_H
