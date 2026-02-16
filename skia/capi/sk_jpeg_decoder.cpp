//
// Created by dolphilia on 2024/02/02.
//

#include "sk_jpeg_decoder.h"

#include "include/codec/SkJpegDecoder.h"

#include "../handles/static_sk_stream.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_codec.h"
#include "../handles/static_sk_codecs_decoder.h"

#include "../handles/static_sk_stream-internal.h"
#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_codecs_decoder-internal.h"
#include "../handles/static_sk_codec-internal.h"

extern "C" {

bool SkJpegDecoder_IsJpeg(const uint8_t *ptr, size_t size) {
    return SkJpegDecoder::IsJpeg(ptr, size);
}

sk_codec_t SkJpegDecoder_Decode(int static_stream, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext) {
    return static_sk_codec_make(SkJpegDecoder::Decode(static_sk_stream_take_entity(static_stream), reinterpret_cast<SkCodec::Result *>(result), decodeContext));
}

sk_codec_t SkJpegDecoder_Decode_2(int static_data, reskia_codec_result_t *result, reskia_codecs_decode_context_t *decodeContext) {
    return static_sk_codec_make(SkJpegDecoder::Decode(static_sk_data_get_entity(static_data), reinterpret_cast<SkCodec::Result *>(result), decodeContext));
}

sk_codecs_decoder_t SkJpegDecoder_Decoder() {
    return static_sk_codecs_decoder_make(SkJpegDecoder::Decoder());
}

}
