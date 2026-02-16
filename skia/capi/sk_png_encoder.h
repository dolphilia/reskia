//
// Created by dolphilia on 2024/02/01.
//

#ifndef RAIA_SKIA_SK_PNG_ENCODER_H
#define RAIA_SKIA_SK_PNG_ENCODER_H

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_encoder.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_direct_context_t reskia_direct_context_t;
typedef struct reskia_image_t reskia_image_t;
typedef struct reskia_pixmap_t reskia_pixmap_t;
typedef struct reskia_png_encoder_options_t reskia_png_encoder_options_t;
typedef struct reskia_w_stream_t reskia_w_stream_t;

bool SkPngEncoder_Encode(reskia_w_stream_t *dst, const reskia_pixmap_t *src, const reskia_png_encoder_options_t *options); // (SkWStream* dst, const SkPixmap* src, const SkPngEncoder::Options* options) -> bool
sk_data_t SkPngEncoder_Encode_2(reskia_direct_context_t *ctx, const reskia_image_t *img, const reskia_png_encoder_options_t *options); // (GrDirectContext* ctx, const SkImage* img, const SkPngEncoder::Options* options) -> sk_data_t
sk_encoder_t SkPngEncoder_Make(reskia_w_stream_t *dst, const reskia_pixmap_t *src, const reskia_png_encoder_options_t *options); // (SkWStream* dst, const SkPixmap* src, const SkPngEncoder::Options* options) -> sk_encoder_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PNG_ENCODER_H
