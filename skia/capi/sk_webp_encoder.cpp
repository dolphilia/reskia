//
// Created by dolphilia on 2024/02/01.
//

#include "sk_webp_encoder.h"

#include "include/encode/SkWebpEncoder.h"

extern "C" {

bool SkWebpEncoder_Encode(reskia_w_stream_t *dst, const reskia_pixmap_t *src, const reskia_webp_encoder_options_t *options) {
    return SkWebpEncoder::Encode(reinterpret_cast<SkWStream *>(dst), *reinterpret_cast<const SkPixmap *>(src), *reinterpret_cast<const SkWebpEncoder::Options *>(options));
}

sk_data_t SkWebpEncoder_EncodeFromImage(reskia_direct_context_t *ctx, const reskia_image_t *img, const reskia_webp_encoder_options_t *options) {
    return static_sk_data_make(SkWebpEncoder::Encode(reinterpret_cast<GrDirectContext *>(ctx), reinterpret_cast<const SkImage *>(img), *reinterpret_cast<const SkWebpEncoder::Options *>(options)));
}

bool SkWebpEncoder_EncodeAnimated(reskia_w_stream_t *dst, const_sk_encoder_frame_t encoderFrame, const reskia_webp_encoder_options_t *options) {
    return SkWebpEncoder::EncodeAnimated(reinterpret_cast<SkWStream *>(dst), static_const_sk_encoder_frame_get(encoderFrame), *reinterpret_cast<const SkWebpEncoder::Options *>(options));
}

}
