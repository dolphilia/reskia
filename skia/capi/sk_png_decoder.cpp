//
// Created by dolphilia on 2024/02/02.
//

#include "sk_png_decoder.h"

#include "include/codec/SkPngDecoder.h"

#include "../handles/static_sk_stream.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_codec.h"
#include "../handles/static_sk_codecs_decoder.h"

#include "../handles/static_sk_stream-internal.h"
#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_codecs_decoder-internal.h"
#include "../handles/static_sk_codec-internal.h"

extern "C" {

bool SkPngDecoder_IsPng(const uint8_t *ptr, size_t size) {
    return SkPngDecoder::IsPng(ptr, size);
}

sk_codec_t SkPngDecoder_Decode(int static_stream, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext) {
    return static_sk_codec_make(SkPngDecoder::Decode(static_sk_stream_take_entity(static_stream), reinterpret_cast<SkCodec::Result *>(result), decodeContext));
}

sk_codec_t SkPngDecoder_DecodeFromData(int static_data, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext) {
    return static_sk_codec_make(SkPngDecoder::Decode(static_sk_data_get_entity(static_data), reinterpret_cast<SkCodec::Result *>(result), decodeContext));
}

sk_codecs_decoder_t SkPngDecoder_Decoder() {
    return static_sk_codecs_decoder_make(SkPngDecoder::Decoder());
}

}
