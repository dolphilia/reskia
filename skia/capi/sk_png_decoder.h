//
// Created by dolphilia on 2024/02/02.
//

#ifndef RAIA_SKIA_SK_PNG_DECODER_H
#define RAIA_SKIA_SK_PNG_DECODER_H

#include <stddef.h>
#include <stdint.h>

#include "../handles/static_sk_codec.h"
#include "../handles/static_sk_codecs_decoder.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_stream.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_codec_result_t reskia_codec_result_t;
typedef struct reskia_codecs_decode_context_t reskia_codecs_decode_context_t;

/**
 * ptr is required when size > 0.
 * invalid input returns false.
 */
bool SkPngDecoder_IsPng(const uint8_t *ptr, size_t size);
/**
 * stream must be a valid owned stream handle.
 * invalid input returns 0 and sets result to kInvalidInput.
 */
sk_codec_t SkPngDecoder_Decode(sk_stream_t stream, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext);
/**
 * data must be a valid SkData handle.
 * invalid input returns 0 and sets result to kInvalidInput.
 */
sk_codec_t SkPngDecoder_DecodeFromData(sk_data_t data, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext);
sk_codecs_decoder_t SkPngDecoder_Decoder(); // () -> sk_codecs_decoder_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PNG_DECODER_H
