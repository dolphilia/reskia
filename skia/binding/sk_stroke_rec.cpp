//
// Created by dolphilia on 2024/01/11.
//

#include "sk_stroke_rec.h"

#include "include/core/SkStrokeRec.h"

#include "../static/static_sk_stroke_rec.h"

#include "../static/static_sk_stroke_rec-internal.h"

extern "C" {

void SkStrokeRec_delete(reskia_stroke_rec_t *stroke_rec) {
    delete reinterpret_cast<SkStrokeRec *>(stroke_rec);
}

sk_stroke_rec_t SkStrokeRec_static(reskia_stroke_rec_init_style_t style) {
    return static_sk_stroke_rec_make(SkStrokeRec(static_cast<SkStrokeRec::InitStyle>(style)));
}

sk_stroke_rec_t SkStrokeRec_static_2(const reskia_paint_t *paint, reskia_stroke_rec_paint_style_t style, float resScale) {
    return static_sk_stroke_rec_make(SkStrokeRec(* reinterpret_cast<const SkPaint *>(paint), static_cast<SkPaint::Style>(style), resScale));
}

sk_stroke_rec_t SkStrokeRec_static_3(const reskia_paint_t *paint, float resScale) {
    return static_sk_stroke_rec_make(SkStrokeRec(* reinterpret_cast<const SkPaint *>(paint), resScale));
}

reskia_stroke_rec_style_t SkStrokeRec_getStyle(reskia_stroke_rec_t *stroke_rec) {
    return static_cast<reskia_stroke_rec_style_t>(reinterpret_cast<SkStrokeRec *>(stroke_rec)->getStyle());
}

float SkStrokeRec_getWidth(reskia_stroke_rec_t *stroke_rec) {
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->getWidth();
}

float SkStrokeRec_getMiter(reskia_stroke_rec_t *stroke_rec) {
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->getMiter();
}

reskia_stroke_rec_cap_t SkStrokeRec_getCap(reskia_stroke_rec_t *stroke_rec) {
    return static_cast<reskia_stroke_rec_cap_t>(reinterpret_cast<SkStrokeRec *>(stroke_rec)->getCap());
}

reskia_stroke_rec_join_t SkStrokeRec_getJoin(reskia_stroke_rec_t *stroke_rec) {
    return static_cast<reskia_stroke_rec_join_t>(reinterpret_cast<SkStrokeRec *>(stroke_rec)->getJoin());
}

bool SkStrokeRec_isHairlineStyle(reskia_stroke_rec_t *stroke_rec) {
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->isHairlineStyle();
}

bool SkStrokeRec_isFillStyle(reskia_stroke_rec_t *stroke_rec) {
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->isFillStyle();
}

void SkStrokeRec_setFillStyle(reskia_stroke_rec_t *stroke_rec) {
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->setFillStyle();
}

void SkStrokeRec_setHairlineStyle(reskia_stroke_rec_t *stroke_rec) {
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->setHairlineStyle();
}

void SkStrokeRec_setStrokeStyle(reskia_stroke_rec_t *stroke_rec, float width, bool strokeAndFill) {
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->setStrokeStyle(width, strokeAndFill);
}

void SkStrokeRec_setStrokeParams(reskia_stroke_rec_t *stroke_rec, reskia_stroke_rec_cap_t cap, reskia_stroke_rec_join_t join, float miterLimit) {
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->setStrokeParams(static_cast<SkPaint::Cap>(cap), static_cast<SkPaint::Join>(join), miterLimit);
}

float SkStrokeRec_getResScale(reskia_stroke_rec_t *stroke_rec) {
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->getResScale();
}

void SkStrokeRec_setResScale(reskia_stroke_rec_t *stroke_rec, float rs) {
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->setResScale(rs);
}

bool SkStrokeRec_needToApply(reskia_stroke_rec_t *stroke_rec) {
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->needToApply();
}

bool SkStrokeRec_applyToPath(reskia_stroke_rec_t *stroke_rec, reskia_path_t *dst, const reskia_path_t *src) {
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->applyToPath(reinterpret_cast<SkPath *>(dst), * reinterpret_cast<const SkPath *>(src));
}

void SkStrokeRec_applyToPaint(reskia_stroke_rec_t *stroke_rec, reskia_paint_t *paint) {
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->applyToPaint(reinterpret_cast<SkPaint *>(paint));
}

float SkStrokeRec_getInflationRadius(reskia_stroke_rec_t *stroke_rec) {
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->getInflationRadius();
}

bool SkStrokeRec_hasEqualEffect(reskia_stroke_rec_t *stroke_rec, const reskia_stroke_rec_t *other) {
    return reinterpret_cast<SkStrokeRec *>(stroke_rec)->hasEqualEffect(* reinterpret_cast<const SkStrokeRec *>(other));
}

// static

float SkStrokeRec_GetInflationRadius(const reskia_paint_t *paint, reskia_stroke_rec_paint_style_t style) {
    return SkStrokeRec::GetInflationRadius(* reinterpret_cast<const SkPaint *>(paint), static_cast<SkPaint::Style>(style));
}

float SkStrokeRec_GetInflationRadius_2(reskia_stroke_rec_join_t join, float miterLimit, reskia_stroke_rec_cap_t cap, float strokeWidth) {
    return SkStrokeRec::GetInflationRadius(static_cast<SkPaint::Join>(join), miterLimit, static_cast<SkPaint::Cap>(cap), strokeWidth);
}

}
