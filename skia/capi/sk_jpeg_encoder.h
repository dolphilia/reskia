//
// Created by dolphilia on 2024/02/01.
//

#ifndef RAIA_SKIA_SK_JPEG_ENCODER_H
#define RAIA_SKIA_SK_JPEG_ENCODER_H

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_encoder.h"

extern "C" {

typedef struct reskia_color_space_t reskia_color_space_t;
typedef struct reskia_direct_context_t reskia_direct_context_t;
typedef struct reskia_image_t reskia_image_t;
typedef struct reskia_jpeg_encoder_options_t reskia_jpeg_encoder_options_t;
typedef struct reskia_pixmap_t reskia_pixmap_t;
typedef struct reskia_w_stream_t reskia_w_stream_t;
typedef struct reskia_yuva_pixmaps_t reskia_yuva_pixmaps_t;

bool SkJpegEncoder_Encode(reskia_w_stream_t *dst, const reskia_pixmap_t *src, const reskia_jpeg_encoder_options_t *options);
bool SkJpegEncoder_Encode_2(reskia_w_stream_t *dst, const reskia_yuva_pixmaps_t *src, const reskia_color_space_t *srcColorSpace, const reskia_jpeg_encoder_options_t *options);
sk_data_t SkJpegEncoder_Encode_3(reskia_direct_context_t *ctx, const reskia_image_t *img, const reskia_jpeg_encoder_options_t *options);
sk_encoder_t SkJpegEncoder_Make(reskia_w_stream_t *dst, const reskia_pixmap_t *src, const reskia_jpeg_encoder_options_t *options);
sk_encoder_t SkJpegEncoder_Make_2(reskia_w_stream_t *dst, const reskia_yuva_pixmaps_t *src, const reskia_color_space_t *srcColorSpace, const reskia_jpeg_encoder_options_t *options);
}

#endif //RAIA_SKIA_SK_JPEG_ENCODER_H
