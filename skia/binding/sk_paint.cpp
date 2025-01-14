//
// Created by dolphilia on 2024/01/09.
//

#include "sk_paint.h"

#include "include/core/SkPaint.h"

#include "../static/static_sk_shader.h"
#include "../static/static_sk_color_filter.h"
#include "../static/static_sk_blender.h"
#include "../static/static_sk_path_effect.h"
#include "../static/static_sk_mask_filter.h"
#include "../static/static_sk_image_filter.h"
#include "../static/static_sk_blend_mode.h"
#include "../static/static_sk_color_4f.h"

#include "../static/static_sk_image_filter-internal.h"
#include "../static/static_sk_mask_filter-internal.h"
#include "../static/static_sk_path_effect-internal.h"
#include "../static/static_sk_shader-internal.h"
#include "../static/static_sk_color_filter-internal.h"
#include "../static/static_sk_color_4f-internal.h"
#include "../static/static_sk_blender-internal.h"
#include "../static/static_sk_blend_mode-internal.h"

extern "C" {

//SkPaint & operator=(const SkPaint &paint)
//SkPaint & operator=(SkPaint &&paint)

void *SkPaint_new() {
    return new SkPaint();
}

void *SkPaint_new_2(const void *color, void *colorSpace) {
    return new SkPaint(* static_cast<const SkColor4f *>(color), static_cast<SkColorSpace *>(colorSpace));
}

void *SkPaint_new_3(const void *paint) {
    return new SkPaint(* static_cast<const SkPaint *>(paint));
}

void SkPaint_delete(void *paint) {
    delete static_cast<SkPaint *>(paint);
}

void SkPaint_reset(void *paint) {
    static_cast<SkPaint *>(paint)->reset();
}

bool SkPaint_isAntiAlias(void *paint) {
    return static_cast<SkPaint *>(paint)->isAntiAlias();
}

void SkPaint_setAntiAlias(void *paint, bool aa) {
    static_cast<SkPaint *>(paint)->setAntiAlias(aa);
}

bool SkPaint_isDither(void *paint) {
    return static_cast<SkPaint *>(paint)->isDither();
}

void SkPaint_setDither(void *paint, bool dither) {
    static_cast<SkPaint *>(paint)->setDither(dither);
}

int SkPaint_getStyle(void *paint) {
    return static_cast<SkPaint *>(paint)->getStyle();
}

void SkPaint_setStyle(void *paint, int style) {
    static_cast<SkPaint *>(paint)->setStyle(static_cast<SkPaint::Style>(style));
}

void SkPaint_setStroke(void *paint, bool v) {
    static_cast<SkPaint *>(paint)->setStroke(v);
}

unsigned int SkPaint_getColor(void *paint) {
    return static_cast<SkPaint *>(paint)->getColor();
}

sk_color_4f_t SkPaint_getColor4f(void *paint) {
    return static_sk_color_4f_make(static_cast<SkPaint *>(paint)->getColor4f());
}

void SkPaint_setColor(void *paint, unsigned int color) {
    static_cast<SkPaint *>(paint)->setColor(color);
}

void SkPaint_setColor_2(void *paint, const void *color, void *colorSpace) {
    static_cast<SkPaint *>(paint)->setColor(* static_cast<const SkColor4f *>(color), static_cast<SkColorSpace *>(colorSpace));
}

void SkPaint_setColor4f(void *paint, const void *color, void *colorSpace) {
    static_cast<SkPaint *>(paint)->setColor4f(* static_cast<const SkColor4f *>(color), static_cast<SkColorSpace *>(colorSpace));
}

float SkPaint_getAlphaf(void *paint) {
    return static_cast<SkPaint *>(paint)->getAlphaf();
}

uint8_t SkPaint_getAlpha(void *paint) {
    return static_cast<SkPaint *>(paint)->getAlpha();
}

void SkPaint_setAlphaf(void *paint, float a) {
    static_cast<SkPaint *>(paint)->setAlphaf(a);
}

void SkPaint_setAlpha(void *paint, unsigned int a) {
    static_cast<SkPaint *>(paint)->setAlpha(a);
}

void SkPaint_setARGB(void *paint, unsigned int a, unsigned int r, unsigned int g, unsigned int b) {
    static_cast<SkPaint *>(paint)->setARGB(a, r, g, b);
}

float SkPaint_getStrokeWidth(void *paint) {
    return static_cast<SkPaint *>(paint)->getStrokeWidth();
}

void SkPaint_setStrokeWidth(void *paint, float width) {
    static_cast<SkPaint *>(paint)->setStrokeWidth(width);
}

float SkPaint_getStrokeMiter(void *paint) {
    return static_cast<SkPaint *>(paint)->getStrokeMiter();
}

void SkPaint_setStrokeMiter(void *paint, float miter) {
    static_cast<SkPaint *>(paint)->setStrokeMiter(miter);
}

int SkPaint_getStrokeCap(void *paint) {
    return static_cast<SkPaint *>(paint)->getStrokeCap();
}

void SkPaint_setStrokeCap(void *paint, int cap) {
    static_cast<SkPaint *>(paint)->setStrokeCap(static_cast<SkPaint::Cap>(cap));
}

int SkPaint_getStrokeJoin(void *paint) {
    return static_cast<SkPaint *>(paint)->getStrokeJoin();
}

void SkPaint_setStrokeJoin(void *paint, int join) {
    static_cast<SkPaint *>(paint)->setStrokeJoin(static_cast<SkPaint::Join>(join));
}

void * SkPaint_getShader(void *paint) {
    return static_cast<SkPaint *>(paint)->getShader();
}

sk_shader_t SkPaint_refShader(void *paint) {
    return static_sk_shader_make(static_cast<SkPaint *>(paint)->refShader());
}

void SkPaint_setShader(void *paint, sk_shader_t shader) {
    static_cast<SkPaint *>(paint)->setShader(static_sk_shader_move(shader));
}

void * SkPaint_getColorFilter(void *paint) {
    return static_cast<SkPaint *>(paint)->getColorFilter();
}

sk_color_filter_t SkPaint_refColorFilter(void *paint) {
    return static_sk_color_filter_make(static_cast<SkPaint *>(paint)->refColorFilter());
}

void SkPaint_setColorFilter(void *paint, sk_color_filter_t color_filter) {
    static_cast<SkPaint *>(paint)->setColorFilter(static_sk_color_filter_move(color_filter));
}

optional_sk_blend_mode_t SkPaint_asBlendMode(void *paint) {
    return static_optional_sk_blend_mode_make(static_cast<SkPaint *>(paint)->asBlendMode());
}

int SkPaint_getBlendMode_or(void *paint, int defaultMode) {
    return static_cast<int>(static_cast<SkPaint *>(paint)->getBlendMode_or(static_cast<SkBlendMode>(defaultMode)));
}

bool SkPaint_isSrcOver(void *paint) {
    return static_cast<SkPaint *>(paint)->isSrcOver();
}

void SkPaint_setBlendMode(void *paint, int mode) {
    static_cast<SkPaint *>(paint)->setBlendMode(static_cast<SkBlendMode>(mode));
}

void * SkPaint_getBlender(void *paint) {
    return static_cast<SkPaint *>(paint)->getBlender();
}

sk_blender_t SkPaint_refBlender(void *paint) {
    return static_sk_blender_make(static_cast<SkPaint *>(paint)->refBlender());
}

void SkPaint_setBlender(void *paint, sk_blender_t blender) {
    static_cast<SkPaint *>(paint)->setBlender(static_sk_blender_move(blender));
}

void * SkPaint_getPathEffect(void *paint) {
    return static_cast<SkPaint *>(paint)->getPathEffect();
}

sk_path_effect_t SkPaint_refPathEffect(void *paint) {
    return static_sk_path_effect_make(static_cast<SkPaint *>(paint)->refPathEffect());
}

void SkPaint_setPathEffect(void *paint, sk_path_effect_t path_effect) {
    static_cast<SkPaint *>(paint)->setPathEffect(static_sk_path_effect_move(path_effect));
}

void * SkPaint_getMaskFilter(void *paint) {
    return static_cast<SkPaint *>(paint)->getMaskFilter();
}

sk_mask_filter_t SkPaint_refMaskFilter(void *paint) {
    return static_sk_mask_filter_make(static_cast<SkPaint *>(paint)->refMaskFilter());
}

void SkPaint_setMaskFilter(void *paint, sk_mask_filter_t mask_filter) {
    static_cast<SkPaint *>(paint)->setMaskFilter(static_sk_mask_filter_move(mask_filter));
}

void * SkPaint_getImageFilter(void *paint) {
    return static_cast<SkPaint *>(paint)->getImageFilter();
}

sk_image_filter_t SkPaint_refImageFilter(void *paint) {
    return static_sk_image_filter_make(static_cast<SkPaint *>(paint)->refImageFilter());
}

void SkPaint_setImageFilter(void *paint, sk_image_filter_t image_filter) {
    static_cast<SkPaint *>(paint)->setImageFilter(static_sk_image_filter_move(image_filter));
}

bool SkPaint_nothingToDraw(void *paint) {
    return static_cast<SkPaint *>(paint)->nothingToDraw();
}

bool SkPaint_canComputeFastBounds(void *paint) {
    return static_cast<SkPaint *>(paint)->canComputeFastBounds();
}

const void * SkPaint_computeFastBounds(void *paint, const void *orig, void *storage) {
    return &static_cast<SkPaint *>(paint)->computeFastBounds(* static_cast<const SkRect *>(orig), static_cast<SkRect *>(storage));
}

const void * SkPaint_computeFastStrokeBounds(void *paint, const void *orig, void *storage) {
    return &static_cast<SkPaint *>(paint)->computeFastStrokeBounds(* static_cast<const SkRect *>(orig), static_cast<SkRect *>(storage));
}

const void * SkPaint_doComputeFastBounds(void *paint, const void *orig, void *storage, int style) {
    return &static_cast<SkPaint *>(paint)->doComputeFastBounds(* static_cast<const SkRect *>(orig), static_cast<SkRect *>(storage), static_cast<SkPaint::Style>(style));
}

}