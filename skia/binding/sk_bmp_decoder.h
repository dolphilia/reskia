//
// Created by dolphilia on 2024/02/02.
//

#ifndef RAIA_SKIA_SK_BMP_DECODER_H_H
#define RAIA_SKIA_SK_BMP_DECODER_H_H

#include "../static/static_sk_codec.h"
#include "../static/static_sk_stream.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_codecs_decoder.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

bool SkBmpDecoder_IsBmp(const void* ptr, size_t size); // (const void* ptr, size_t size) -> bool
sk_codec_t SkBmpDecoder_Decode(sk_stream_t stream, void * result, void * decodeContext); // (sk_stream_t stream, SkCodec::Result* result, SkCodecs::DecodeContext decodeContext) -> sk_codec_t
sk_codec_t SkBmpDecoder_Decode_2(sk_stream_t stream, void * result, void * decodeContext); // (sk_stream_t stream, SkCodec::Result* result, SkCodecs::DecodeContext decodeContext) -> sk_codec_t
sk_codecs_decoder_t SkBmpDecoder_Decoder(); // () -> sk_codecs_decoder_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_BMP_DECODER_H_H
