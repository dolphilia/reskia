//
// Created by dolphilia on 2024/01/11.
//

#include "sk_stroke_rec.h"

#include "include/core/SkStrokeRec.h"

#include "../static/static_sk_stroke_rec.h"

#include "../static/static_sk_stroke_rec-internal.h"

extern "C" {

void SkStrokeRec_delete(void *stroke_rec) {
    delete static_cast<SkStrokeRec *>(stroke_rec);
}

int SkStrokeRec_static(int style) {
    return static_sk_stroke_rec_make(SkStrokeRec(static_cast<SkStrokeRec::InitStyle>(style)));
}

int SkStrokeRec_static_2(const void *paint, int style, float resScale) {
    return static_sk_stroke_rec_make(SkStrokeRec(* static_cast<const SkPaint *>(paint), static_cast<SkPaint::Style>(style), resScale));
}

int SkStrokeRec_static_3(const void *paint, float resScale) {
    return static_sk_stroke_rec_make(SkStrokeRec(* static_cast<const SkPaint *>(paint), resScale));
}

int SkStrokeRec_getStyle(void *stroke_rec) {
    return static_cast<SkStrokeRec *>(stroke_rec)->getStyle();
}

float SkStrokeRec_getWidth(void *stroke_rec) {
    return static_cast<SkStrokeRec *>(stroke_rec)->getWidth();
}

float SkStrokeRec_getMiter(void *stroke_rec) {
    return static_cast<SkStrokeRec *>(stroke_rec)->getMiter();
}

int SkStrokeRec_getCap(void *stroke_rec) {
    return static_cast<SkStrokeRec *>(stroke_rec)->getCap();
}

int SkStrokeRec_getJoin(void *stroke_rec) {
    return static_cast<SkStrokeRec *>(stroke_rec)->getJoin();
}

bool SkStrokeRec_isHairlineStyle(void *stroke_rec) {
    return static_cast<SkStrokeRec *>(stroke_rec)->isHairlineStyle();
}

bool SkStrokeRec_isFillStyle(void *stroke_rec) {
    return static_cast<SkStrokeRec *>(stroke_rec)->isFillStyle();
}

void SkStrokeRec_setFillStyle(void *stroke_rec) {
    return static_cast<SkStrokeRec *>(stroke_rec)->setFillStyle();
}

void SkStrokeRec_setHairlineStyle(void *stroke_rec) {
    return static_cast<SkStrokeRec *>(stroke_rec)->setHairlineStyle();
}

void SkStrokeRec_setStrokeStyle(void *stroke_rec, float width, bool strokeAndFill) {
    return static_cast<SkStrokeRec *>(stroke_rec)->setStrokeStyle(width, strokeAndFill);
}

void SkStrokeRec_setStrokeParams(void *stroke_rec, int cap, int join, float miterLimit) {
    return static_cast<SkStrokeRec *>(stroke_rec)->setStrokeParams(static_cast<SkPaint::Cap>(cap), static_cast<SkPaint::Join>(join), miterLimit);
}

float SkStrokeRec_getResScale(void *stroke_rec) {
    return static_cast<SkStrokeRec *>(stroke_rec)->getResScale();
}

void SkStrokeRec_setResScale(void *stroke_rec, float rs) {
    return static_cast<SkStrokeRec *>(stroke_rec)->setResScale(rs);
}

bool SkStrokeRec_needToApply(void *stroke_rec) {
    return static_cast<SkStrokeRec *>(stroke_rec)->needToApply();
}

bool SkStrokeRec_applyToPath(void *stroke_rec, void *dst, const void *src) {
    return static_cast<SkStrokeRec *>(stroke_rec)->applyToPath(static_cast<SkPath *>(dst), * static_cast<const SkPath *>(src));
}

void SkStrokeRec_applyToPaint(void *stroke_rec, void *paint) {
    return static_cast<SkStrokeRec *>(stroke_rec)->applyToPaint(static_cast<SkPaint *>(paint));
}

float SkStrokeRec_getInflationRadius(void *stroke_rec) {
    return static_cast<SkStrokeRec *>(stroke_rec)->getInflationRadius();
}

bool SkStrokeRec_hasEqualEffect(void *stroke_rec, const void *other) {
    return static_cast<SkStrokeRec *>(stroke_rec)->hasEqualEffect(* static_cast<const SkStrokeRec *>(other));
}

// static

float SkStrokeRec_GetInflationRadius(const void *paint, int style) {
    return SkStrokeRec::GetInflationRadius(* static_cast<const SkPaint *>(paint), static_cast<SkPaint::Style>(style));
}

float SkStrokeRec_GetInflationRadius_2(int join, float miterLimit, int cap, float strokeWidth) {
    return SkStrokeRec::GetInflationRadius(static_cast<SkPaint::Join>(join), miterLimit, static_cast<SkPaint::Cap>(cap), strokeWidth);
}

}
