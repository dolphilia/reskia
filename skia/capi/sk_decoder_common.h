#ifndef RESKIA_CAPI_SK_DECODER_COMMON_H
#define RESKIA_CAPI_SK_DECODER_COMMON_H

#include <cstddef>
#include <cstdint>
#include <memory>

#include "include/codec/SkCodec.h"

#include "../handles/static_sk_codec-internal.h"
#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_stream-internal.h"

namespace reskia_capi {

inline bool has_encoded_bytes(const uint8_t *ptr, size_t size) {
    return ptr != nullptr || size == 0;
}

inline void set_invalid_input(reskia_codec_result_t *result) {
    if (result != nullptr) {
        *reinterpret_cast<SkCodec::Result *>(result) = SkCodec::kInvalidInput;
    }
}

inline sk_codec_t make_codec_handle(std::unique_ptr<SkCodec> codec) {
    if (!codec) {
        return 0;
    }
    return static_sk_codec_make(std::move(codec));
}

inline std::unique_ptr<SkStream> take_stream_or_set_invalid(sk_stream_t stream, reskia_codec_result_t *result) {
    std::unique_ptr<SkStream> native_stream = static_sk_stream_take_entity(stream);
    if (!native_stream) {
        set_invalid_input(result);
    }
    return native_stream;
}

inline sk_sp<SkData> get_data_or_set_invalid(sk_data_t data, reskia_codec_result_t *result) {
    sk_sp<SkData> native_data = static_sk_data_get_entity(data);
    if (!native_data) {
        set_invalid_input(result);
    }
    return native_data;
}

inline SkCodecs::DecodeContext as_decode_context(reskia_codecs_decode_context_t *decodeContext) {
    return reinterpret_cast<SkCodecs::DecodeContext>(decodeContext);
}

} // namespace reskia_capi

#endif // RESKIA_CAPI_SK_DECODER_COMMON_H
