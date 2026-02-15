//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_STROKE_REC_H
#define RAIA_SKIA_SK_STROKE_REC_H

#include <stdint.h>

#include "../static/static_sk_stroke_rec.h"

typedef struct reskia_paint_t reskia_paint_t;
typedef struct reskia_path_t reskia_path_t;
typedef struct reskia_stroke_rec_t reskia_stroke_rec_t;
typedef int32_t reskia_stroke_rec_init_style_t;
typedef int32_t reskia_stroke_rec_paint_style_t;
typedef int32_t reskia_stroke_rec_style_t;
typedef int32_t reskia_stroke_rec_cap_t;
typedef int32_t reskia_stroke_rec_join_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkStrokeRec_delete(reskia_stroke_rec_t *stroke_rec); // (SkStrokeRec *stroke_rec)
sk_stroke_rec_t SkStrokeRec_static(reskia_stroke_rec_init_style_t style); // (SkStrokeRec::InitStyle style) -> sk_stroke_rec_t
sk_stroke_rec_t SkStrokeRec_static_2(const reskia_paint_t *paint, reskia_stroke_rec_paint_style_t style, float resScale); // (const SkPaint *paint, SkPaint::Style style, SkScalar resScale) -> sk_stroke_rec_t
sk_stroke_rec_t SkStrokeRec_static_3(const reskia_paint_t *paint, float resScale); // (const SkPaint *paint, SkScalar resScale) -> sk_stroke_rec_t
reskia_stroke_rec_style_t SkStrokeRec_getStyle(reskia_stroke_rec_t *stroke_rec); // (SkStrokeRec *stroke_rec) -> SkStrokeRec::Style
float SkStrokeRec_getWidth(reskia_stroke_rec_t *stroke_rec); // (SkStrokeRec *stroke_rec) -> SkScalar
float SkStrokeRec_getMiter(reskia_stroke_rec_t *stroke_rec); // (SkStrokeRec *stroke_rec) -> SkScalar
reskia_stroke_rec_cap_t SkStrokeRec_getCap(reskia_stroke_rec_t *stroke_rec); // (SkStrokeRec *stroke_rec) -> SkPaint::Cap
reskia_stroke_rec_join_t SkStrokeRec_getJoin(reskia_stroke_rec_t *stroke_rec); // (SkStrokeRec *stroke_rec) -> SkPaint::Join
bool SkStrokeRec_isHairlineStyle(reskia_stroke_rec_t *stroke_rec); // (SkStrokeRec *stroke_rec) -> bool
bool SkStrokeRec_isFillStyle(reskia_stroke_rec_t *stroke_rec); // (SkStrokeRec *stroke_rec) -> bool
void SkStrokeRec_setFillStyle(reskia_stroke_rec_t *stroke_rec); // (SkStrokeRec *stroke_rec)
void SkStrokeRec_setHairlineStyle(reskia_stroke_rec_t *stroke_rec); // (SkStrokeRec *stroke_rec)
void SkStrokeRec_setStrokeStyle(reskia_stroke_rec_t *stroke_rec, float width, bool strokeAndFill); // (SkStrokeRec *stroke_rec, SkScalar width, bool strokeAndFill)
void SkStrokeRec_setStrokeParams(reskia_stroke_rec_t *stroke_rec, reskia_stroke_rec_cap_t cap, reskia_stroke_rec_join_t join, float miterLimit); // (SkStrokeRec *stroke_rec, SkPaint::Cap cap, SkPaint::Join join, SkScalar miterLimit)
float SkStrokeRec_getResScale(reskia_stroke_rec_t *stroke_rec); // (SkStrokeRec *stroke_rec) -> SkScalar
void SkStrokeRec_setResScale(reskia_stroke_rec_t *stroke_rec, float rs); // (SkStrokeRec *stroke_rec, SkScalar rs)
bool SkStrokeRec_needToApply(reskia_stroke_rec_t *stroke_rec); // (SkStrokeRec *stroke_rec) -> bool
bool SkStrokeRec_applyToPath(reskia_stroke_rec_t *stroke_rec, reskia_path_t *dst, const reskia_path_t *src); // (SkStrokeRec *stroke_rec, SkPath *dst, const SkPath *src) -> bool
void SkStrokeRec_applyToPaint(reskia_stroke_rec_t *stroke_rec, reskia_paint_t *paint); // (SkStrokeRec *stroke_rec, SkPaint *paint)
float SkStrokeRec_getInflationRadius(reskia_stroke_rec_t *stroke_rec); // (SkStrokeRec *stroke_rec) -> SkScalar
bool SkStrokeRec_hasEqualEffect(reskia_stroke_rec_t *stroke_rec, const reskia_stroke_rec_t *other); // (SkStrokeRec *stroke_rec, const SkStrokeRec *other) -> bool

// static

float SkStrokeRec_GetInflationRadius(const reskia_paint_t *paint, reskia_stroke_rec_paint_style_t style); // (const SkPaint *paint, SkPaint::Style style) -> SkScalar
float SkStrokeRec_GetInflationRadius_2(reskia_stroke_rec_join_t join, float miterLimit, reskia_stroke_rec_cap_t cap, float strokeWidth); // (SkPaint::Join join, SkScalar miterLimit, SkPaint::Cap cap, SkScalar strokeWidth) -> SkScalar

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_STROKE_REC_H
