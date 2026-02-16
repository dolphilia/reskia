//
// Created by dolphilia on 2024/02/01.
//

#include "sk_png_encoder.h"

#include "include/encode/SkPngEncoder.h"

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_encoder.h"

#include "../handles/static_sk_encoder-internal.h"
#include "../handles/static_sk_data-internal.h"

extern "C" {

bool SkPngEncoder_Encode(reskia_w_stream_t *dst, const reskia_pixmap_t *src, const reskia_png_encoder_options_t *options) {
    return SkPngEncoder::Encode(reinterpret_cast<SkWStream *>(dst), *reinterpret_cast<const SkPixmap *>(src), *reinterpret_cast<const SkPngEncoder::Options *>(options));
}

sk_data_t SkPngEncoder_EncodeFromImage(reskia_direct_context_t *ctx, const reskia_image_t *img, const reskia_png_encoder_options_t *options) {
    return static_sk_data_make(SkPngEncoder::Encode(reinterpret_cast<GrDirectContext *>(ctx), reinterpret_cast<const SkImage *>(img), *reinterpret_cast<const SkPngEncoder::Options *>(options)));
}

sk_encoder_t SkPngEncoder_Make(reskia_w_stream_t *dst, const reskia_pixmap_t *src, const reskia_png_encoder_options_t *options) {
    return static_sk_encoder_make(SkPngEncoder::Make(reinterpret_cast<SkWStream *>(dst), *reinterpret_cast<const SkPixmap *>(src), *reinterpret_cast<const SkPngEncoder::Options *>(options)));
}

}
