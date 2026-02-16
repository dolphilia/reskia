//
// Created by dolphilia on 2024/02/02.
//

#ifndef RAIA_SKIA_SK_ICO_DECODER_H
#define RAIA_SKIA_SK_ICO_DECODER_H

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

bool SkIcoDecoder_IsIco(const uint8_t *ptr, size_t size); // (const void* ptr, size_t size) -> bool
sk_codec_t SkIcoDecoder_Decode(sk_stream_t stream, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext); // (sk_stream_t stream, SkCodec::Result* result, SkCodecs::DecodeContext decodeContext) -> sk_codec_t
sk_codec_t SkIcoDecoder_Decode_2(sk_data_t data, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext); // (sk_data_t data, SkCodec::Result* result, SkCodecs::DecodeContext decodeContext) -> sk_codec_t
sk_codecs_decoder_t SkIcoDecoder_Decoder(); // () -> sk_codecs_decoder_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_ICO_DECODER_H
