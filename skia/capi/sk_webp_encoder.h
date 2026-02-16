//
// Created by dolphilia on 2024/02/01.
//

#ifndef RAIA_SKIA_SK_WEBP_ENCODER_H
#define RAIA_SKIA_SK_WEBP_ENCODER_H

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_encoder_frame.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_direct_context_t reskia_direct_context_t;
typedef struct reskia_image_t reskia_image_t;
typedef struct reskia_pixmap_t reskia_pixmap_t;
typedef struct reskia_w_stream_t reskia_w_stream_t;
typedef struct reskia_webp_encoder_options_t reskia_webp_encoder_options_t;

bool SkWebpEncoder_Encode(reskia_w_stream_t *dst, const reskia_pixmap_t *src, const reskia_webp_encoder_options_t *options);
sk_data_t SkWebpEncoder_EncodeFromImage(reskia_direct_context_t *ctx, const reskia_image_t *img, const reskia_webp_encoder_options_t *options);
bool SkWebpEncoder_EncodeAnimated(reskia_w_stream_t *dst, const_sk_encoder_frame_t encoderFrame, const reskia_webp_encoder_options_t *options);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_WEBP_ENCODER_H
