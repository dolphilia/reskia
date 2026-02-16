//
// Created by dolphilia on 2024/01/09.
//

#include "sk_paint.h"

#include "include/core/SkPaint.h"

#include "../handles/static_sk_shader.h"
#include "../handles/static_sk_color_filter.h"
#include "../handles/static_sk_blender.h"
#include "../handles/static_sk_path_effect.h"
#include "../handles/static_sk_mask_filter.h"
#include "../handles/static_sk_image_filter.h"
#include "../handles/static_sk_blend_mode.h"
#include "../handles/static_sk_color_4f.h"

#include "../handles/static_sk_image_filter-internal.h"
#include "../handles/static_sk_mask_filter-internal.h"
#include "../handles/static_sk_path_effect-internal.h"
#include "../handles/static_sk_shader-internal.h"
#include "../handles/static_sk_color_filter-internal.h"
#include "../handles/static_sk_color_4f-internal.h"
#include "../handles/static_sk_blender-internal.h"
#include "../handles/static_sk_blend_mode-internal.h"

extern "C" {

//SkPaint & operator=(const SkPaint &paint)
//SkPaint & operator=(SkPaint &&paint)

reskia_paint_t *SkPaint_new() {
    return reinterpret_cast<reskia_paint_t *>(new SkPaint());
}

reskia_paint_t *SkPaint_new_2(const reskia_color_4f_t *color, reskia_color_space_t *colorSpace) {
    return reinterpret_cast<reskia_paint_t *>(new SkPaint(* reinterpret_cast<const SkColor4f *>(color), reinterpret_cast<SkColorSpace *>(colorSpace)));
}

reskia_paint_t *SkPaint_new_3(const reskia_paint_t *paint) {
    return reinterpret_cast<reskia_paint_t *>(new SkPaint(* reinterpret_cast<const SkPaint *>(paint)));
}

void SkPaint_delete(reskia_paint_t *paint) {
    delete reinterpret_cast<SkPaint *>(paint);
}

void SkPaint_reset(reskia_paint_t *paint) {
    reinterpret_cast<SkPaint *>(paint)->reset();
}

bool SkPaint_isAntiAlias(reskia_paint_t *paint) {
    return reinterpret_cast<SkPaint *>(paint)->isAntiAlias();
}

void SkPaint_setAntiAlias(reskia_paint_t *paint, bool aa) {
    reinterpret_cast<SkPaint *>(paint)->setAntiAlias(aa);
}

bool SkPaint_isDither(reskia_paint_t *paint) {
    return reinterpret_cast<SkPaint *>(paint)->isDither();
}

void SkPaint_setDither(reskia_paint_t *paint, bool dither) {
    reinterpret_cast<SkPaint *>(paint)->setDither(dither);
}

reskia_paint_style_t SkPaint_getStyle(reskia_paint_t *paint) {
    return static_cast<reskia_paint_style_t>(reinterpret_cast<SkPaint *>(paint)->getStyle());
}

void SkPaint_setStyle(reskia_paint_t *paint, reskia_paint_style_t style) {
    reinterpret_cast<SkPaint *>(paint)->setStyle(static_cast<SkPaint::Style>(style));
}

void SkPaint_setStroke(reskia_paint_t *paint, bool v) {
    reinterpret_cast<SkPaint *>(paint)->setStroke(v);
}

reskia_color_t SkPaint_getColor(reskia_paint_t *paint) {
    return reinterpret_cast<SkPaint *>(paint)->getColor();
}

sk_color_4f_t SkPaint_getColor4f(reskia_paint_t *paint) {
    return static_sk_color_4f_make(reinterpret_cast<SkPaint *>(paint)->getColor4f());
}

void SkPaint_setColor(reskia_paint_t *paint, reskia_color_t color) {
    reinterpret_cast<SkPaint *>(paint)->setColor(color);
}

void SkPaint_setColor_2(reskia_paint_t *paint, const reskia_color_4f_t *color, reskia_color_space_t *colorSpace) {
    reinterpret_cast<SkPaint *>(paint)->setColor(* reinterpret_cast<const SkColor4f *>(color), reinterpret_cast<SkColorSpace *>(colorSpace));
}

void SkPaint_setColor4f(reskia_paint_t *paint, const reskia_color_4f_t *color, reskia_color_space_t *colorSpace) {
    reinterpret_cast<SkPaint *>(paint)->setColor4f(* reinterpret_cast<const SkColor4f *>(color), reinterpret_cast<SkColorSpace *>(colorSpace));
}

float SkPaint_getAlphaf(reskia_paint_t *paint) {
    return reinterpret_cast<SkPaint *>(paint)->getAlphaf();
}

uint8_t SkPaint_getAlpha(reskia_paint_t *paint) {
    return reinterpret_cast<SkPaint *>(paint)->getAlpha();
}

void SkPaint_setAlphaf(reskia_paint_t *paint, float a) {
    reinterpret_cast<SkPaint *>(paint)->setAlphaf(a);
}

void SkPaint_setAlpha(reskia_paint_t *paint, uint8_t a) {
    reinterpret_cast<SkPaint *>(paint)->setAlpha(a);
}

void SkPaint_setARGB(reskia_paint_t *paint, uint8_t a, uint8_t r, uint8_t g, uint8_t b) {
    reinterpret_cast<SkPaint *>(paint)->setARGB(a, r, g, b);
}

float SkPaint_getStrokeWidth(reskia_paint_t *paint) {
    return reinterpret_cast<SkPaint *>(paint)->getStrokeWidth();
}

void SkPaint_setStrokeWidth(reskia_paint_t *paint, float width) {
    reinterpret_cast<SkPaint *>(paint)->setStrokeWidth(width);
}

float SkPaint_getStrokeMiter(reskia_paint_t *paint) {
    return reinterpret_cast<SkPaint *>(paint)->getStrokeMiter();
}

void SkPaint_setStrokeMiter(reskia_paint_t *paint, float miter) {
    reinterpret_cast<SkPaint *>(paint)->setStrokeMiter(miter);
}

reskia_paint_cap_t SkPaint_getStrokeCap(reskia_paint_t *paint) {
    return static_cast<reskia_paint_cap_t>(reinterpret_cast<SkPaint *>(paint)->getStrokeCap());
}

void SkPaint_setStrokeCap(reskia_paint_t *paint, reskia_paint_cap_t cap) {
    reinterpret_cast<SkPaint *>(paint)->setStrokeCap(static_cast<SkPaint::Cap>(cap));
}

reskia_paint_join_t SkPaint_getStrokeJoin(reskia_paint_t *paint) {
    return static_cast<reskia_paint_join_t>(reinterpret_cast<SkPaint *>(paint)->getStrokeJoin());
}

void SkPaint_setStrokeJoin(reskia_paint_t *paint, reskia_paint_join_t join) {
    reinterpret_cast<SkPaint *>(paint)->setStrokeJoin(static_cast<SkPaint::Join>(join));
}

reskia_shader_t * SkPaint_getShader(reskia_paint_t *paint) {
    return reinterpret_cast<reskia_shader_t *>(reinterpret_cast<SkPaint *>(paint)->getShader());
}

sk_shader_t SkPaint_refShader(reskia_paint_t *paint) {
    return static_sk_shader_make(reinterpret_cast<SkPaint *>(paint)->refShader());
}

void SkPaint_setShader(reskia_paint_t *paint, sk_shader_t shader) {
    reinterpret_cast<SkPaint *>(paint)->setShader(static_sk_shader_get_entity(shader));
}

reskia_color_filter_t * SkPaint_getColorFilter(reskia_paint_t *paint) {
    return reinterpret_cast<reskia_color_filter_t *>(reinterpret_cast<SkPaint *>(paint)->getColorFilter());
}

sk_color_filter_t SkPaint_refColorFilter(reskia_paint_t *paint) {
    return static_sk_color_filter_make(reinterpret_cast<SkPaint *>(paint)->refColorFilter());
}

void SkPaint_setColorFilter(reskia_paint_t *paint, sk_color_filter_t color_filter) {
    reinterpret_cast<SkPaint *>(paint)->setColorFilter(static_sk_color_filter_get_entity(color_filter));
}

optional_sk_blend_mode_t SkPaint_asBlendMode(reskia_paint_t *paint) {
    return static_optional_sk_blend_mode_make(reinterpret_cast<SkPaint *>(paint)->asBlendMode());
}

reskia_paint_blend_mode_t SkPaint_getBlendMode_or(reskia_paint_t *paint, reskia_paint_blend_mode_t defaultMode) {
    return static_cast<reskia_paint_blend_mode_t>(reinterpret_cast<SkPaint *>(paint)->getBlendMode_or(static_cast<SkBlendMode>(defaultMode)));
}

bool SkPaint_isSrcOver(reskia_paint_t *paint) {
    return reinterpret_cast<SkPaint *>(paint)->isSrcOver();
}

void SkPaint_setBlendMode(reskia_paint_t *paint, reskia_paint_blend_mode_t mode) {
    reinterpret_cast<SkPaint *>(paint)->setBlendMode(static_cast<SkBlendMode>(mode));
}

reskia_blender_t * SkPaint_getBlender(reskia_paint_t *paint) {
    return reinterpret_cast<reskia_blender_t *>(reinterpret_cast<SkPaint *>(paint)->getBlender());
}

sk_blender_t SkPaint_refBlender(reskia_paint_t *paint) {
    return static_sk_blender_make(reinterpret_cast<SkPaint *>(paint)->refBlender());
}

void SkPaint_setBlender(reskia_paint_t *paint, sk_blender_t blender) {
    reinterpret_cast<SkPaint *>(paint)->setBlender(static_sk_blender_get_entity(blender));
}

reskia_path_effect_t * SkPaint_getPathEffect(reskia_paint_t *paint) {
    return reinterpret_cast<reskia_path_effect_t *>(reinterpret_cast<SkPaint *>(paint)->getPathEffect());
}

sk_path_effect_t SkPaint_refPathEffect(reskia_paint_t *paint) {
    return static_sk_path_effect_make(reinterpret_cast<SkPaint *>(paint)->refPathEffect());
}

void SkPaint_setPathEffect(reskia_paint_t *paint, sk_path_effect_t path_effect) {
    reinterpret_cast<SkPaint *>(paint)->setPathEffect(static_sk_path_effect_get_entity(path_effect));
}

reskia_mask_filter_t * SkPaint_getMaskFilter(reskia_paint_t *paint) {
    return reinterpret_cast<reskia_mask_filter_t *>(reinterpret_cast<SkPaint *>(paint)->getMaskFilter());
}

sk_mask_filter_t SkPaint_refMaskFilter(reskia_paint_t *paint) {
    return static_sk_mask_filter_make(reinterpret_cast<SkPaint *>(paint)->refMaskFilter());
}

void SkPaint_setMaskFilter(reskia_paint_t *paint, sk_mask_filter_t mask_filter) {
    reinterpret_cast<SkPaint *>(paint)->setMaskFilter(static_sk_mask_filter_get_entity(mask_filter));
}

reskia_image_filter_t * SkPaint_getImageFilter(reskia_paint_t *paint) {
    return reinterpret_cast<reskia_image_filter_t *>(reinterpret_cast<SkPaint *>(paint)->getImageFilter());
}

sk_image_filter_t SkPaint_refImageFilter(reskia_paint_t *paint) {
    return static_sk_image_filter_make(reinterpret_cast<SkPaint *>(paint)->refImageFilter());
}

void SkPaint_setImageFilter(reskia_paint_t *paint, sk_image_filter_t image_filter) {
    reinterpret_cast<SkPaint *>(paint)->setImageFilter(static_sk_image_filter_get_entity(image_filter));
}

bool SkPaint_nothingToDraw(reskia_paint_t *paint) {
    return reinterpret_cast<SkPaint *>(paint)->nothingToDraw();
}

bool SkPaint_canComputeFastBounds(reskia_paint_t *paint) {
    return reinterpret_cast<SkPaint *>(paint)->canComputeFastBounds();
}

const reskia_rect_t * SkPaint_computeFastBounds(reskia_paint_t *paint, const reskia_rect_t *orig, reskia_rect_t *storage) {
    return reinterpret_cast<const reskia_rect_t *>(&reinterpret_cast<SkPaint *>(paint)->computeFastBounds(* reinterpret_cast<const SkRect *>(orig), reinterpret_cast<SkRect *>(storage)));
}

const reskia_rect_t * SkPaint_computeFastStrokeBounds(reskia_paint_t *paint, const reskia_rect_t *orig, reskia_rect_t *storage) {
    return reinterpret_cast<const reskia_rect_t *>(&reinterpret_cast<SkPaint *>(paint)->computeFastStrokeBounds(* reinterpret_cast<const SkRect *>(orig), reinterpret_cast<SkRect *>(storage)));
}

const reskia_rect_t * SkPaint_doComputeFastBounds(reskia_paint_t *paint, const reskia_rect_t *orig, reskia_rect_t *storage, reskia_paint_style_t style) {
    return reinterpret_cast<const reskia_rect_t *>(&reinterpret_cast<SkPaint *>(paint)->doComputeFastBounds(* reinterpret_cast<const SkRect *>(orig), reinterpret_cast<SkRect *>(storage), static_cast<SkPaint::Style>(style)));
}

}
