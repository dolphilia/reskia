//
// Created by dolphilia on 2024/01/13.
//

#ifndef RAIA_SKIA_SK_TILED_IMAGE_UTILS_H
#define RAIA_SKIA_SK_TILED_IMAGE_UTILS_H

#include <stdint.h>

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_image_t reskia_image_t;
typedef struct reskia_image_sp_t reskia_image_sp_t;
typedef struct reskia_paint_t reskia_paint_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_sampling_options_t reskia_sampling_options_t;
typedef int32_t reskia_tiled_image_utils_src_rect_constraint_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkTiledImageUtils_DrawImageRect(reskia_canvas_t *canvas, const reskia_image_t *image, const reskia_rect_t *src, const reskia_rect_t *dst, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint, reskia_tiled_image_utils_src_rect_constraint_t constraint); // (SkCanvas *canvas, const SkImage *image, const SkRect *src, const SkRect *dst, const SkSamplingOptions *sampling, const SkPaint *paint, SkCanvas::SrcRectConstraint constraint)
void SkTiledImageUtils_DrawImageRect_2(reskia_canvas_t *canvas, const reskia_image_sp_t *image, const reskia_rect_t *src, const reskia_rect_t *dst, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint, reskia_tiled_image_utils_src_rect_constraint_t constraint); // (SkCanvas *canvas, const sk_sp< SkImage > *image, const SkRect *src, const SkRect *dst, const SkSamplingOptions *sampling, const SkPaint *paint, SkCanvas::SrcRectConstraint constraint)
void SkTiledImageUtils_DrawImageRect_3(reskia_canvas_t *canvas, const reskia_image_t *image, const reskia_rect_t *dst, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint, reskia_tiled_image_utils_src_rect_constraint_t constraint); // (SkCanvas *canvas, const SkImage *image, const SkRect *dst, const SkSamplingOptions *sampling, const SkPaint *paint, SkCanvas::SrcRectConstraint constraint)
void SkTiledImageUtils_DrawImageRect_4(reskia_canvas_t *canvas, const reskia_image_sp_t *image, const reskia_rect_t *dst, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint, reskia_tiled_image_utils_src_rect_constraint_t constraint); // (SkCanvas *canvas, const sk_sp< SkImage > *image, const SkRect *dst, const SkSamplingOptions *sampling, const SkPaint *paint, SkCanvas::SrcRectConstraint constraint)
void SkTiledImageUtils_DrawImage(reskia_canvas_t *canvas, const reskia_image_t *image, float x, float y, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint, reskia_tiled_image_utils_src_rect_constraint_t constraint); // (SkCanvas *canvas, const SkImage *image, SkScalar x, SkScalar y, const SkSamplingOptions *sampling, const SkPaint *paint, SkCanvas::SrcRectConstraint constraint)
void SkTiledImageUtils_DrawImage_2(reskia_canvas_t *canvas, const reskia_image_sp_t *image, float x, float y, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint, reskia_tiled_image_utils_src_rect_constraint_t constraint); // (SkCanvas *canvas, const sk_sp< SkImage > *image, SkScalar x, SkScalar y, const SkSamplingOptions *sampling, const SkPaint *paint, SkCanvas::SrcRectConstraint constraint)
void SkTiledImageUtils_GetImageKeyValues(const reskia_image_t *image, uint32_t * keyValues); // (const SkImage *image, uint32_t keyValues[SkTiledImageUtils::kNumImageKeyValues])

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_TILED_IMAGE_UTILS_H
