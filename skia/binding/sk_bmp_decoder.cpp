//
// Created by dolphilia on 2024/02/02.
//

#include "sk_bmp_decoder.h"

#include "include/codec/SkBmpDecoder.h"

#include "../static/static_sk_codec.h"
#include "../static/static_sk_stream.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_codecs_decoder.h"

#include "../static/static_sk_stream-internal.h"
#include "../static/static_sk_data-internal.h"
#include "../static/static_sk_codecs_decoder-internal.h"
#include "../static/static_sk_codec-internal.h"

extern "C" {

// static

bool SkBmpDecoder_IsBmp(const uint8_t *ptr, size_t size) {
    return SkBmpDecoder::IsBmp(ptr, size);
}

sk_codec_t SkBmpDecoder_Decode(sk_stream_t stream, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext) {
    return static_sk_codec_make(SkBmpDecoder::Decode(
        static_sk_stream_take_entity(stream),
        reinterpret_cast<SkCodec::Result *>(result),
        reinterpret_cast<SkCodecs::DecodeContext>(decodeContext)));
}

sk_codec_t SkBmpDecoder_Decode_2(sk_stream_t stream, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext) {
    return static_sk_codec_make(SkBmpDecoder::Decode(
        static_sk_data_get_entity(stream),
        reinterpret_cast<SkCodec::Result *>(result),
        reinterpret_cast<SkCodecs::DecodeContext>(decodeContext)));
}

sk_codecs_decoder_t SkBmpDecoder_Decoder() {
    return static_sk_codecs_decoder_make(SkBmpDecoder::Decoder());
}

}
