//
// Created by dolphilia on 2024/02/01.
//

#include "sk_webp_encoder.h"

#include "include/core/SkData.h"
#include "include/encode/SkEncoder.h"
#include "include/encode/SkWebpEncoder.h"

#include <utility>

#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_encoder_frame-internal.h"

namespace {

sk_data_t make_data_handle(sk_sp<SkData> data) {
    if (!data) {
        return 0;
    }
    return static_sk_data_make(std::move(data));
}

} // namespace

extern "C" {

bool SkWebpEncoder_Encode(reskia_w_stream_t *dst, const reskia_pixmap_t *src, const reskia_webp_encoder_options_t *options) {
    if (dst == nullptr || src == nullptr || options == nullptr) {
        return false;
    }
    return SkWebpEncoder::Encode(reinterpret_cast<SkWStream *>(dst), *reinterpret_cast<const SkPixmap *>(src), *reinterpret_cast<const SkWebpEncoder::Options *>(options));
}

sk_data_t SkWebpEncoder_EncodeFromImage(reskia_direct_context_t *ctx, const reskia_image_t *img, const reskia_webp_encoder_options_t *options) {
    if (img == nullptr || options == nullptr) {
        return 0;
    }
    return make_data_handle(SkWebpEncoder::Encode(reinterpret_cast<GrDirectContext *>(ctx), reinterpret_cast<const SkImage *>(img), *reinterpret_cast<const SkWebpEncoder::Options *>(options)));
}

bool SkWebpEncoder_EncodeAnimated(reskia_w_stream_t *dst, const_sk_encoder_frame_t encoderFrame, const reskia_webp_encoder_options_t *options) {
    SkSpan<const SkEncoder::Frame> frames = static_const_sk_encoder_frame_get_entity(encoderFrame);
    if (dst == nullptr || frames.empty() || options == nullptr) {
        return false;
    }
    return SkWebpEncoder::EncodeAnimated(
        reinterpret_cast<SkWStream *>(dst),
        frames,
        *reinterpret_cast<const SkWebpEncoder::Options *>(options));
}

}
