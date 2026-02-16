//
// Created by dolphilia on 2024/02/02.
//

#include "sk_ico_decoder.h"

#include "include/codec/SkIcoDecoder.h"

#include "../handles/static_sk_stream.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_codec.h"
#include "../handles/static_sk_codecs_decoder.h"

#include "../handles/static_sk_stream-internal.h"
#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_codecs_decoder-internal.h"
#include "../handles/static_sk_codec-internal.h"

extern "C" {

bool SkIcoDecoder_IsIco(const uint8_t *ptr, size_t size) {
    return SkIcoDecoder::IsIco(ptr, size);
}

sk_codec_t SkIcoDecoder_Decode(sk_stream_t stream, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext) {
    return static_sk_codec_make(SkIcoDecoder::Decode(
        static_sk_stream_take_entity(stream),
        reinterpret_cast<SkCodec::Result *>(result),
        reinterpret_cast<SkCodecs::DecodeContext>(decodeContext)));
}

sk_codec_t SkIcoDecoder_Decode_2(sk_data_t data, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext) {
    return static_sk_codec_make(SkIcoDecoder::Decode(
        static_sk_data_get_entity(data),
        reinterpret_cast<SkCodec::Result *>(result),
        reinterpret_cast<SkCodecs::DecodeContext>(decodeContext)));
}

sk_codecs_decoder_t SkIcoDecoder_Decoder() {
    return static_sk_codecs_decoder_make(SkIcoDecoder::Decoder());
}

}
