//
// Created by dolphilia on 2024/02/02.
//

#include "sk_ico_decoder.h"

#include "include/codec/SkIcoDecoder.h"

#include "sk_decoder_common.h"

#include "../handles/static_sk_stream.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_codec.h"
#include "../handles/static_sk_codecs_decoder.h"

#include "../handles/static_sk_codecs_decoder-internal.h"

extern "C" {

bool SkIcoDecoder_IsIco(const uint8_t *ptr, size_t size) {
    if (!reskia_capi::has_encoded_bytes(ptr, size)) {
        return false;
    }
    return SkIcoDecoder::IsIco(ptr, size);
}

sk_codec_t SkIcoDecoder_Decode(sk_stream_t stream, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext) {
    std::unique_ptr<SkStream> native_stream = reskia_capi::take_stream_or_set_invalid(stream, result);
    if (!native_stream) {
        return 0;
    }
    return reskia_capi::make_codec_handle(SkIcoDecoder::Decode(
        std::move(native_stream),
        reinterpret_cast<SkCodec::Result *>(result),
        reskia_capi::as_decode_context(decodeContext)));
}

sk_codec_t SkIcoDecoder_DecodeFromData(sk_data_t data, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext) {
    sk_sp<SkData> native_data = reskia_capi::get_data_or_set_invalid(data, result);
    if (!native_data) {
        return 0;
    }
    return reskia_capi::make_codec_handle(SkIcoDecoder::Decode(
        std::move(native_data),
        reinterpret_cast<SkCodec::Result *>(result),
        reskia_capi::as_decode_context(decodeContext)));
}

sk_codecs_decoder_t SkIcoDecoder_Decoder() {
    return static_sk_codecs_decoder_make(SkIcoDecoder::Decoder());
}

}
