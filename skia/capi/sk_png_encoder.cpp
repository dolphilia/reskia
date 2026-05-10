//
// Created by dolphilia on 2024/02/01.
//

#include "sk_png_encoder.h"

#include "include/encode/SkPngEncoder.h"

#include <utility>

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_encoder.h"

#include "../handles/static_sk_encoder-internal.h"
#include "../handles/static_sk_data-internal.h"

namespace {

sk_data_t make_data_handle(sk_sp<SkData> data) {
    if (!data) {
        return 0;
    }
    return static_sk_data_make(std::move(data));
}

sk_encoder_t make_encoder_handle(std::unique_ptr<SkEncoder> encoder) {
    if (!encoder) {
        return 0;
    }
    return static_sk_encoder_make(std::move(encoder));
}

} // namespace

extern "C" {

bool SkPngEncoder_Encode(reskia_w_stream_t *dst, const reskia_pixmap_t *src, const reskia_png_encoder_options_t *options) {
    if (dst == nullptr || src == nullptr || options == nullptr) {
        return false;
    }
    return SkPngEncoder::Encode(reinterpret_cast<SkWStream *>(dst), *reinterpret_cast<const SkPixmap *>(src), *reinterpret_cast<const SkPngEncoder::Options *>(options));
}

sk_data_t SkPngEncoder_EncodeFromImage(reskia_direct_context_t *ctx, const reskia_image_t *img, const reskia_png_encoder_options_t *options) {
    if (img == nullptr || options == nullptr) {
        return 0;
    }
    return make_data_handle(SkPngEncoder::Encode(reinterpret_cast<GrDirectContext *>(ctx), reinterpret_cast<const SkImage *>(img), *reinterpret_cast<const SkPngEncoder::Options *>(options)));
}

sk_encoder_t SkPngEncoder_Make(reskia_w_stream_t *dst, const reskia_pixmap_t *src, const reskia_png_encoder_options_t *options) {
    if (dst == nullptr || src == nullptr || options == nullptr) {
        return 0;
    }
    return make_encoder_handle(SkPngEncoder::Make(reinterpret_cast<SkWStream *>(dst), *reinterpret_cast<const SkPixmap *>(src), *reinterpret_cast<const SkPngEncoder::Options *>(options)));
}

}
