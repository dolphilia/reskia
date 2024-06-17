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
#include "export_api.h"

extern "C" {
RAIA_API bool SkWebpDecoder_IsWbmp(const void* ptr, size_t size);
RAIA_API sk_codec_t SkWebpDecoder_Decode(int static_stream, SkCodec::Result* result, SkCodecs::DecodeContext decodeContext);
RAIA_API sk_codec_t SkWebpDecoder_Decode_2(int static_data, SkCodec::Result* result, SkCodecs::DecodeContext decodeContext);
RAIA_API sk_codecs_decoder_t SkWebpDecoder_Decoder();
}

#endif //RAIA_SKIA_SK_WEBP_DECODER_H
