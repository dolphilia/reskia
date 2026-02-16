//
// Created by dolphilia on 2024/02/02.
//

#include "sk_raw_decoder.h"

#include "include/codec/SkRawDecoder.h"

#include "../handles/static_sk_stream.h"
#include "../handles/static_sk_data.h"

extern "C" {

bool SkRawDecoder_IsRaw(const uint8_t *ptr, size_t size) {
    return SkRawDecoder::IsRaw(ptr, size);
}

sk_codec_t SkRawDecoder_Decode(int static_stream, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext) {
    return static_sk_codec_make(SkRawDecoder::Decode(static_sk_stream_move(static_stream), reinterpret_cast<SkCodec::Result *>(result), decodeContext));
}

sk_codec_t SkRawDecoder_DecodeFromData(int static_data, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext) {
    return static_sk_codec_make(SkRawDecoder::Decode(static_sk_data_move(static_data), reinterpret_cast<SkCodec::Result *>(result), decodeContext));
}

sk_codecs_decoder_t SkRawDecoder_Decoder() {
    return static_sk_codecs_decoder_make(SkRawDecoder::Decoder());
}

}
