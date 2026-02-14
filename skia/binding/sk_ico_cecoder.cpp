//
// Created by dolphilia on 2024/02/02.
//

#include "sk_ico_cecoder.h"

#include "include/codec/SkIcoDecoder.h"

#include "../static/static_sk_stream.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_codec.h"
#include "../static/static_sk_codecs_decoder.h"

#include "../static/static_sk_stream-internal.h"
#include "../static/static_sk_data-internal.h"
#include "../static/static_sk_codecs_decoder-internal.h"
#include "../static/static_sk_codec-internal.h"

extern "C" {

bool SkIcoDecoder_IsIco(const void* ptr, size_t size) {
    return SkIcoDecoder::IsIco(ptr, size);
}

sk_codec_t SkIcoDecoder_Decode(int static_stream, void * result, void * decodeContext) {
    return static_sk_codec_make(SkIcoDecoder::Decode(static_sk_stream_take_entity(static_stream), static_cast<SkCodec::Result *>(result), decodeContext));
}

sk_codec_t SkIcoDecoder_Decode_2(int static_data, void * result, void * decodeContext) {
    return static_sk_codec_make(SkIcoDecoder::Decode(static_sk_data_get_entity(static_data), static_cast<SkCodec::Result *>(result), decodeContext));
}

sk_codecs_decoder_t SkIcoDecoder_Decoder() {
    return static_sk_codecs_decoder_make(SkIcoDecoder::Decoder());
}

}
