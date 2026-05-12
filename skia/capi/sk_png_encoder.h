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

/**
 * dst/src/options are required.
 * invalid input returns false.
 */
bool SkPngEncoder_Encode(reskia_w_stream_t *dst, const reskia_pixmap_t *src, const reskia_png_encoder_options_t *options);
/**
 * img/options are required.
 * ctx may be NULL.
 * invalid input or encode failure returns 0.
 */
sk_data_t SkPngEncoder_EncodeFromImage(reskia_direct_context_t *ctx, const reskia_image_t *img, const reskia_png_encoder_options_t *options);
/**
 * dst/src/options are required.
 * invalid input or unsupported src returns 0.
 */
sk_encoder_t SkPngEncoder_Make(reskia_w_stream_t *dst, const reskia_pixmap_t *src, const reskia_png_encoder_options_t *options);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PNG_ENCODER_H
