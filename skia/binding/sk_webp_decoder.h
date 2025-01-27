//
// Created by dolphilia on 2024/02/02.
//

#ifndef RAIA_SKIA_SK_WEBP_DECODER_H
#define RAIA_SKIA_SK_WEBP_DECODER_H

#include "include/codec/SkWebpDecoder.h"
#include "../static/static_sk_stream.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_codec.h"
#include "../static/static_sk_codecs_decoder.h"

extern "C" {

bool SkWebpDecoder_IsWbmp(const void* ptr, size_t size); // (const void* ptr, size_t size) -> bool
sk_codec_t SkWebpDecoder_Decode(int static_stream, SkCodec::Result* result, SkCodecs::DecodeContext decodeContext); // (int static_stream, SkCodec::Result* result, SkCodecs::DecodeContext decodeContext) -> sk_codec_t
sk_codec_t SkWebpDecoder_Decode_2(int static_data, SkCodec::Result* result, SkCodecs::DecodeContext decodeContext); // (int static_data, SkCodec::Result* result, SkCodecs::DecodeContext decodeContext) -> sk_codec_t
sk_codecs_decoder_t SkWebpDecoder_Decoder(); // () -> sk_codecs_decoder_t

}

#endif //RAIA_SKIA_SK_WEBP_DECODER_H
