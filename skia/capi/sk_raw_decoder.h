//
// Created by dolphilia on 2024/02/02.
//

#ifndef RAIA_SKIA_SK_RAW_DECODER_H
#define RAIA_SKIA_SK_RAW_DECODER_H

#include <stddef.h>
#include <stdint.h>

#include "../handles/static_sk_codec.h"
#include "../handles/static_sk_codecs_decoder.h"

extern "C" {

typedef struct reskia_codec_result_t reskia_codec_result_t;
typedef struct reskia_codecs_decode_context_t reskia_codecs_decode_context_t;

bool SkRawDecoder_IsRaw(const uint8_t *ptr, size_t size);
sk_codec_t SkRawDecoder_Decode(int static_stream, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext);
sk_codec_t SkRawDecoder_Decode_2(int static_data, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext);
sk_codecs_decoder_t SkRawDecoder_Decoder();
}

#endif //RAIA_SKIA_SK_RAW_DECODER_H
