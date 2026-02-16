//
// Created by dolphilia on 2024/02/01.
//

#include "sk_jpeg_encoder.h"

#include "include/core/SkData.h"
#include "include/encode/SkEncoder.h"
#include "include/encode/SkJpegEncoder.h"

#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_encoder-internal.h"

extern "C" {

bool SkJpegEncoder_Encode(reskia_w_stream_t *dst, const reskia_pixmap_t *src, const reskia_jpeg_encoder_options_t *options) {
    return SkJpegEncoder::Encode(reinterpret_cast<SkWStream *>(dst), *reinterpret_cast<const SkPixmap *>(src), *reinterpret_cast<const SkJpegEncoder::Options *>(options));
}

bool SkJpegEncoder_EncodeYuvaPixmaps(reskia_w_stream_t *dst, const reskia_yuva_pixmaps_t *src, const reskia_color_space_t *srcColorSpace, const reskia_jpeg_encoder_options_t *options) {
    return SkJpegEncoder::Encode(reinterpret_cast<SkWStream *>(dst), *reinterpret_cast<const SkYUVAPixmaps *>(src), reinterpret_cast<const SkColorSpace *>(srcColorSpace), *reinterpret_cast<const SkJpegEncoder::Options *>(options));
}

sk_data_t SkJpegEncoder_EncodeImage(reskia_direct_context_t *ctx, const reskia_image_t *img, const reskia_jpeg_encoder_options_t *options) {
    return static_sk_data_make(SkJpegEncoder::Encode(reinterpret_cast<GrDirectContext *>(ctx), reinterpret_cast<const SkImage *>(img), *reinterpret_cast<const SkJpegEncoder::Options *>(options)));
}

sk_encoder_t SkJpegEncoder_Make(reskia_w_stream_t *dst, const reskia_pixmap_t *src, const reskia_jpeg_encoder_options_t *options) {
    return static_sk_encoder_make(SkJpegEncoder::Make(reinterpret_cast<SkWStream *>(dst), *reinterpret_cast<const SkPixmap *>(src), *reinterpret_cast<const SkJpegEncoder::Options *>(options)));
}

sk_encoder_t SkJpegEncoder_MakeYuvaPixmaps(reskia_w_stream_t *dst, const reskia_yuva_pixmaps_t *src, const reskia_color_space_t *srcColorSpace, const reskia_jpeg_encoder_options_t *options) {
    return static_sk_encoder_make(SkJpegEncoder::Make(reinterpret_cast<SkWStream *>(dst), *reinterpret_cast<const SkYUVAPixmaps *>(src), reinterpret_cast<const SkColorSpace *>(srcColorSpace), *reinterpret_cast<const SkJpegEncoder::Options *>(options)));
}

}
