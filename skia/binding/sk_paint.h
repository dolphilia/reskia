//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_PAINT_H
#define RAIA_SKIA_SK_PAINT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_blender_t reskia_blender_t;
typedef uint32_t reskia_color_t;
typedef struct reskia_color_4f_t reskia_color_4f_t;
typedef struct reskia_color_filter_t reskia_color_filter_t;
typedef struct reskia_color_space_t reskia_color_space_t;
typedef struct reskia_image_filter_t reskia_image_filter_t;
typedef struct reskia_mask_filter_t reskia_mask_filter_t;
typedef struct reskia_paint_t reskia_paint_t;
typedef struct reskia_path_effect_t reskia_path_effect_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_shader_t reskia_shader_t;

//SkPaint & operator=(const SkPaint &paint)
//SkPaint & operator=(SkPaint &&paint)

reskia_paint_t *SkPaint_new(); // () -> SkPaint *
reskia_paint_t *SkPaint_new_2(const reskia_color_4f_t *color, reskia_color_space_t *colorSpace); // (const SkColor4f *color, SkColorSpace *colorSpace) -> SkPaint *
reskia_paint_t *SkPaint_new_3(const reskia_paint_t *paint); // (const SkPaint *paint) -> SkPaint *
void SkPaint_delete(reskia_paint_t *paint); // (SkPaint *paint)
void SkPaint_reset(reskia_paint_t *paint); // (SkPaint *paint)
bool SkPaint_isAntiAlias(reskia_paint_t *paint); // (SkPaint *paint) -> bool
void SkPaint_setAntiAlias(reskia_paint_t *paint, bool aa); // (SkPaint *paint, bool aa)
bool SkPaint_isDither(reskia_paint_t *paint); // (SkPaint *paint) -> bool
void SkPaint_setDither(reskia_paint_t *paint, bool dither); // (SkPaint *paint, bool dither)
int SkPaint_getStyle(reskia_paint_t *paint); // (SkPaint *paint) -> SkPaint::Style
void SkPaint_setStyle(reskia_paint_t *paint, int style); // (SkPaint *paint, SkPaint::Style style)
void SkPaint_setStroke(reskia_paint_t *paint, bool v); // (SkPaint *paint, bool v)
reskia_color_t SkPaint_getColor(reskia_paint_t *paint); // (SkPaint *paint) -> SkColor
int SkPaint_getColor4f(reskia_paint_t *paint); // (SkPaint *paint) -> sk_color_4f_t
void SkPaint_setColor(reskia_paint_t *paint, reskia_color_t color); // (SkPaint *paint, SkColor color)
void SkPaint_setColor_2(reskia_paint_t *paint, const reskia_color_4f_t *color, reskia_color_space_t *colorSpace); // (SkPaint *paint, const SkColor4f *color, SkColorSpace *colorSpace)
void SkPaint_setColor4f(reskia_paint_t *paint, const reskia_color_4f_t *color, reskia_color_space_t *colorSpace); // (SkPaint *paint, const SkColor4f *color, SkColorSpace *colorSpace)
float SkPaint_getAlphaf(reskia_paint_t *paint); // (SkPaint *paint) -> float
uint8_t SkPaint_getAlpha(reskia_paint_t *paint); // (SkPaint *paint) -> uint8_t
void SkPaint_setAlphaf(reskia_paint_t *paint, float a); // (SkPaint *paint, float a)
void SkPaint_setAlpha(reskia_paint_t *paint, uint8_t a); // (SkPaint *paint, U8CPU a)
void SkPaint_setARGB(reskia_paint_t *paint, uint8_t a, uint8_t r, uint8_t g, uint8_t b); // (SkPaint *paint, U8CPU a, U8CPU r, U8CPU g, U8CPU b)
float SkPaint_getStrokeWidth(reskia_paint_t *paint); // (SkPaint *paint) -> SkScalar
void SkPaint_setStrokeWidth(reskia_paint_t *paint, float width); // (SkPaint *paint, SkScalar width)
float SkPaint_getStrokeMiter(reskia_paint_t *paint); // (SkPaint *paint) -> SkScalar
void SkPaint_setStrokeMiter(reskia_paint_t *paint, float miter); // (SkPaint *paint, SkScalar miter)
int SkPaint_getStrokeCap(reskia_paint_t *paint); // (SkPaint *paint) -> SkPaint::Cap
void SkPaint_setStrokeCap(reskia_paint_t *paint, int cap); // (SkPaint *paint, SkPaint::Cap cap)
int SkPaint_getStrokeJoin(reskia_paint_t *paint); // (SkPaint *paint) -> SkPaint::Join
void SkPaint_setStrokeJoin(reskia_paint_t *paint, int join); // (SkPaint *paint, SkPaint::Join join)
reskia_shader_t * SkPaint_getShader(reskia_paint_t *paint); // (SkPaint *paint) -> SkShader *
int SkPaint_refShader(reskia_paint_t *paint); // (SkPaint *paint) -> sk_shader_t
void SkPaint_setShader(reskia_paint_t *paint, int shader); // (SkPaint *paint, sk_shader_t shader)
reskia_color_filter_t * SkPaint_getColorFilter(reskia_paint_t *paint); // (SkPaint *paint) -> SkColorFilter *
int SkPaint_refColorFilter(reskia_paint_t *paint); // (SkPaint *paint) -> sk_color_filter_t
void SkPaint_setColorFilter(reskia_paint_t *paint, int color_filter); // (SkPaint *paint, sk_color_filter_t color_filter)
int SkPaint_asBlendMode(reskia_paint_t *paint); // (SkPaint *paint) -> int
int SkPaint_getBlendMode_or(reskia_paint_t *paint, int defaultMode); // (SkPaint *paint, SkBlendMode defaultMode) -> SkBlendMode
bool SkPaint_isSrcOver(reskia_paint_t *paint); // (SkPaint *paint) -> bool
void SkPaint_setBlendMode(reskia_paint_t *paint, int mode); // (SkPaint *paint, SkBlendMode mode)
reskia_blender_t * SkPaint_getBlender(reskia_paint_t *paint); // (SkPaint *paint) -> SkBlender *
int SkPaint_refBlender(reskia_paint_t *paint); // (SkPaint *paint) -> sk_blender_t
void SkPaint_setBlender(reskia_paint_t *paint, int blender); // (SkPaint *paint, sk_blender_t blender)
reskia_path_effect_t * SkPaint_getPathEffect(reskia_paint_t *paint); // (SkPaint *paint) -> SkPathEffect *
int SkPaint_refPathEffect(reskia_paint_t *paint); // (SkPaint *paint) -> sk_path_effect_t
void SkPaint_setPathEffect(reskia_paint_t *paint, int path_effect); // (SkPaint *paint, sk_path_effect_t path_effect)
reskia_mask_filter_t * SkPaint_getMaskFilter(reskia_paint_t *paint); // (SkPaint *paint) -> SkMaskFilter *
int SkPaint_refMaskFilter(reskia_paint_t *paint); // (SkPaint *paint) -> sk_mask_filter_t
void SkPaint_setMaskFilter(reskia_paint_t *paint, int mask_filter); // (SkPaint *paint, sk_mask_filter_t mask_filter)
reskia_image_filter_t * SkPaint_getImageFilter(reskia_paint_t *paint); // (SkPaint *paint) -> SkImageFilter *
int SkPaint_refImageFilter(reskia_paint_t *paint); // (SkPaint *paint) -> sk_image_filter_t
void SkPaint_setImageFilter(reskia_paint_t *paint, int image_filter); // (SkPaint *paint, sk_image_filter_t image_filter)
bool SkPaint_nothingToDraw(reskia_paint_t *paint); // (SkPaint *paint) -> bool
bool SkPaint_canComputeFastBounds(reskia_paint_t *paint); // (SkPaint *paint) -> bool
const reskia_rect_t * SkPaint_computeFastBounds(reskia_paint_t *paint, const reskia_rect_t *orig, reskia_rect_t *storage); // (SkPaint *paint, const SkRect *orig, SkRect *storage) -> const SkRect *
const reskia_rect_t * SkPaint_computeFastStrokeBounds(reskia_paint_t *paint, const reskia_rect_t *orig, reskia_rect_t *storage); // (SkPaint *paint, const SkRect *orig, SkRect *storage) -> const SkRect *
const reskia_rect_t * SkPaint_doComputeFastBounds(reskia_paint_t *paint, const reskia_rect_t *orig, reskia_rect_t *storage, int style); // (SkPaint *paint, const SkRect *orig, SkRect *storage, SkPaint::Style style) -> const SkRect *

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PAINT_H
