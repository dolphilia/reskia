//
// Created by dolphilia on 2024/02/02.
//

#include "sk_webp_decoder.h"

#include "include/codec/SkWebpDecoder.h"

#include "../static/static_sk_stream.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_codec.h"
#include "../static/static_sk_codecs_decoder.h"

#include "../static/static_sk_stream-internal.h"
#include "../static/static_sk_data-internal.h"
#include "../static/static_sk_codecs_decoder-internal.h"
#include "../static/static_sk_codec-internal.h"

extern "C" {

bool SkWebpDecoder_IsWbmp(const void* ptr, size_t size) {
    return SkWebpDecoder::IsWebp(ptr, size);
}

sk_codec_t SkWebpDecoder_Decode(int static_stream, void * result, void * decodeContext) {
    return static_sk_codec_make(SkWebpDecoder::Decode(static_sk_stream_move(static_stream), static_cast<SkCodec::Result *>(result), decodeContext));
}

sk_codec_t SkWebpDecoder_Decode_2(int static_data, void * result, void * decodeContext) {
    return static_sk_codec_make(SkWebpDecoder::Decode(static_sk_data_move(static_data), static_cast<SkCodec::Result *>(result), decodeContext));
}

sk_codecs_decoder_t SkWebpDecoder_Decoder() {
    return static_sk_codecs_decoder_make(SkWebpDecoder::Decoder());
}

}
