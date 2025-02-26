//
// Created by dolphilia on 2024/02/02.
//

#include "sk_png_decoder.h"

#include "include/codec/SkPngDecoder.h"

#include "../static/static_sk_stream.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_codec.h"
#include "../static/static_sk_codecs_decoder.h"

#include "../static/static_sk_stream-internal.h"
#include "../static/static_sk_data-internal.h"
#include "../static/static_sk_codecs_decoder-internal.h"
#include "../static/static_sk_codec-internal.h"

extern "C" {

bool SkPngDecoder_IsPng(const void* ptr, size_t size) {
    return SkPngDecoder::IsPng(ptr, size);
}

sk_codec_t SkPngDecoder_Decode(int static_stream, void * result, void * decodeContext) {
    return static_sk_codec_make(SkPngDecoder::Decode(static_sk_stream_get_entity(static_stream), static_cast<SkCodec::Result *>(result), decodeContext));
}

sk_codec_t SkPngDecoder_Decode_2(int static_data, void * result, void * decodeContext) {
    return static_sk_codec_make(SkPngDecoder::Decode(static_sk_data_get_entity(static_data), static_cast<SkCodec::Result *>(result), decodeContext));
}

sk_codecs_decoder_t SkPngDecoder_Decoder() {
    return static_sk_codecs_decoder_make(SkPngDecoder::Decoder());
}

}
