//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_STROKE_REC_H
#define RAIA_SKIA_SK_STROKE_REC_H

#include <stdint.h>

#include "../handles/static_sk_stroke_rec.h"

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

void SkStrokeRec_delete(reskia_stroke_rec_t *stroke_rec); // NULL stroke_rec is no-op.
sk_stroke_rec_t SkStrokeRec_static(reskia_stroke_rec_init_style_t style); // Returns a caller-owned handle; invalid style returns 0.
sk_stroke_rec_t SkStrokeRec_staticWithPaintStyleAndResScale(const reskia_paint_t *paint, reskia_stroke_rec_paint_style_t style, float resScale); // paint is required; invalid input returns 0.
sk_stroke_rec_t SkStrokeRec_staticWithPaintAndResScale(const reskia_paint_t *paint, float resScale); // paint is required; invalid input returns 0.
reskia_stroke_rec_style_t SkStrokeRec_getStyle(reskia_stroke_rec_t *stroke_rec); // NULL stroke_rec returns 0.
float SkStrokeRec_getWidth(reskia_stroke_rec_t *stroke_rec); // NULL stroke_rec returns 0.
float SkStrokeRec_getMiter(reskia_stroke_rec_t *stroke_rec); // NULL stroke_rec returns 0.
reskia_stroke_rec_cap_t SkStrokeRec_getCap(reskia_stroke_rec_t *stroke_rec); // NULL stroke_rec returns 0.
reskia_stroke_rec_join_t SkStrokeRec_getJoin(reskia_stroke_rec_t *stroke_rec); // NULL stroke_rec returns 0.
bool SkStrokeRec_isHairlineStyle(reskia_stroke_rec_t *stroke_rec); // NULL stroke_rec returns false.
bool SkStrokeRec_isFillStyle(reskia_stroke_rec_t *stroke_rec); // NULL stroke_rec returns false.
void SkStrokeRec_setFillStyle(reskia_stroke_rec_t *stroke_rec); // NULL stroke_rec is no-op.
void SkStrokeRec_setHairlineStyle(reskia_stroke_rec_t *stroke_rec); // NULL stroke_rec is no-op.
void SkStrokeRec_setStrokeStyle(reskia_stroke_rec_t *stroke_rec, float width, bool strokeAndFill); // NULL stroke_rec is no-op.
void SkStrokeRec_setStrokeParams(reskia_stroke_rec_t *stroke_rec, reskia_stroke_rec_cap_t cap, reskia_stroke_rec_join_t join, float miterLimit); // NULL stroke_rec or invalid enum is no-op.
float SkStrokeRec_getResScale(reskia_stroke_rec_t *stroke_rec); // NULL stroke_rec returns 0.
void SkStrokeRec_setResScale(reskia_stroke_rec_t *stroke_rec, float rs); // NULL stroke_rec or non-positive/non-finite rs is no-op.
bool SkStrokeRec_needToApply(reskia_stroke_rec_t *stroke_rec); // NULL stroke_rec returns false.
bool SkStrokeRec_applyToPath(reskia_stroke_rec_t *stroke_rec, reskia_path_t *dst, const reskia_path_t *src); // stroke_rec, dst, and src are required; invalid input returns false.
void SkStrokeRec_applyToPaint(reskia_stroke_rec_t *stroke_rec, reskia_paint_t *paint); // stroke_rec and paint are required; invalid input is no-op.
float SkStrokeRec_getInflationRadius(reskia_stroke_rec_t *stroke_rec); // NULL stroke_rec returns 0.
bool SkStrokeRec_hasEqualEffect(reskia_stroke_rec_t *stroke_rec, const reskia_stroke_rec_t *other); // NULL input returns false.

// static

float SkStrokeRec_GetInflationRadius(const reskia_paint_t *paint, reskia_stroke_rec_paint_style_t style); // paint is required; invalid input returns 0.
float SkStrokeRec_GetInflationRadiusWithJoinMiterCapAndStrokeWidth(reskia_stroke_rec_join_t join, float miterLimit, reskia_stroke_rec_cap_t cap, float strokeWidth); // Invalid cap/join returns 0.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_STROKE_REC_H
