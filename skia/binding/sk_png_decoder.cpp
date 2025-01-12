//
// Created by dolphilia on 2024/02/02.
//

#include "sk_png_decoder.h"

#include "../static/static_sk_stream-internal.h"
#include "../static/static_sk_data-internal.h"
#include "../static/static_sk_codecs_decoder-internal.h"
#include "../static/static_sk_codec-internal.h"

extern "C" {

bool SkPngDecoder_IsPng(const void* ptr, size_t size) {
    return SkPngDecoder::IsPng(ptr, size);
}

sk_codec_t SkPngDecoder_Decode(int static_stream, SkCodec::Result* result, SkCodecs::DecodeContext decodeContext) {
    return static_sk_codec_make(SkPngDecoder::Decode(static_sk_stream_move(static_stream), result, decodeContext));
}

sk_codec_t SkPngDecoder_Decode_2(int static_data, SkCodec::Result* result, SkCodecs::DecodeContext decodeContext) {
    return static_sk_codec_make(SkPngDecoder::Decode(static_sk_data_move(static_data), result, decodeContext));
}

sk_codecs_decoder_t SkPngDecoder_Decoder() {
    return static_sk_codecs_decoder_make(SkPngDecoder::Decoder());
}

}
