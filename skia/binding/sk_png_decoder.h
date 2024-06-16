//
// Created by dolphilia on 2024/02/02.
//

#ifndef RAIA_SKIA_SK_PNG_DECODER_H
#define RAIA_SKIA_SK_PNG_DECODER_H

#include "include/codec/SkPngDecoder.h"
#include "../static/static_sk_stream.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_codec.h"
#include "../static/static_sk_codecs_decoder.h"

extern "C" {
bool SkPngDecoder_IsPng(const void* ptr, size_t size);
sk_codec_t SkPngDecoder_Decode(int static_stream, SkCodec::Result* result, SkCodecs::DecodeContext decodeContext);
sk_codec_t SkPngDecoder_Decode_2(int static_data, SkCodec::Result* result, SkCodecs::DecodeContext decodeContext);
sk_codecs_decoder_t SkPngDecoder_Decoder();
}

#endif //RAIA_SKIA_SK_PNG_DECODER_H
