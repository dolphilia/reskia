//
// Created by dolphilia on 2024/02/02.
//

#include "sk_gif_decoder.h"

#include "include/codec/SkGifDecoder.h"

#include "../static/static_sk_stream-internal.h"
#include "../static/static_sk_data-internal.h"

extern "C" {

bool SkGifDecoder_IsGif(const uint8_t *ptr, size_t size) {
    return SkGifDecoder::IsGif(ptr, size);
}

sk_codec_t SkGifDecoder_Decode(sk_stream_t stream, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext) {
    return static_sk_codec_make(SkGifDecoder::Decode(
        static_sk_stream_take_entity(stream),
        reinterpret_cast<SkCodec::Result *>(result),
        reinterpret_cast<SkCodecs::DecodeContext>(decodeContext)));
}

sk_codec_t SkGifDecoder_Decode_2(sk_data_t data, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext) {
    return static_sk_codec_make(SkGifDecoder::Decode(
        static_sk_data_get_entity(data),
        reinterpret_cast<SkCodec::Result *>(result),
        reinterpret_cast<SkCodecs::DecodeContext>(decodeContext)));
}

sk_codecs_decoder_t SkGifDecoder_Decoder() {
    return static_sk_codecs_decoder_make(SkGifDecoder::Decoder());
}

}
