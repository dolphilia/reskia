//
// Created by dolphilia on 2024/02/02.
//

#ifndef RAIA_SKIA_SK_BMP_DECODER_H_H
#define RAIA_SKIA_SK_BMP_DECODER_H_H

#include <stddef.h>
#include <stdint.h>
#include "../static/static_sk_codec.h"
#include "../static/static_sk_codecs_decoder.h"
#include "../static/static_sk_stream.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_codec_result_t reskia_codec_result_t;
typedef struct reskia_codecs_decode_context_t reskia_codecs_decode_context_t;

bool SkBmpDecoder_IsBmp(const uint8_t *ptr, size_t size); // (const void* ptr, size_t size) -> bool
sk_codec_t SkBmpDecoder_Decode(sk_stream_t stream, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext); // (sk_stream_t stream, SkCodec::Result* result, SkCodecs::DecodeContext decodeContext) -> sk_codec_t
sk_codec_t SkBmpDecoder_Decode_2(sk_stream_t stream, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext); // (sk_stream_t stream, SkCodec::Result* result, SkCodecs::DecodeContext decodeContext) -> sk_codec_t
sk_codecs_decoder_t SkBmpDecoder_Decoder(); // () -> sk_codecs_decoder_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_BMP_DECODER_H_H
