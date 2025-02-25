//
// Created by dolphilia on 2024/01/10.
//

#include "sk_rect.h"

#include "include/core/SkRect.h"

#include "../static/static_sk_rect.h"
#include "../static/static_sk_i_rect.h"
#include "../static/static_sk_point.h"

#include "../static/static_sk_i_rect-internal.h"
#include "../static/static_sk_point-internal.h"
#include "../static/static_sk_rect-internal.h"

extern "C" {

void SkRect_delete(void *rect) {
    delete static_cast<SkRect *>(rect);
}

bool SkRect_isEmpty(void *rect) {
    return static_cast<SkRect *>(rect)->isEmpty();
}

bool SkRect_isSorted(void *rect) {
    return static_cast<SkRect *>(rect)->isSorted();
}

bool SkRect_isFinite(void *rect) {
    return static_cast<SkRect *>(rect)->isFinite();
}

float SkRect_x(void *rect) {
    return static_cast<SkRect *>(rect)->x();
}

float SkRect_y(void *rect) {
    return static_cast<SkRect *>(rect)->y();
}

float SkRect_left(void *rect) {
    return static_cast<SkRect *>(rect)->left();
}

float SkRect_top(void *rect) {
    return static_cast<SkRect *>(rect)->top();
}

float SkRect_right(void *rect) {
    return static_cast<SkRect *>(rect)->right();
}

float SkRect_bottom(void *rect) {
    return static_cast<SkRect *>(rect)->bottom();
}

float SkRect_width(void *rect) {
    return static_cast<SkRect *>(rect)->width();
}

float SkRect_height(void *rect) {
    return static_cast<SkRect *>(rect)->height();
}

float SkRect_centerX(void *rect) {
    return static_cast<SkRect *>(rect)->centerX();
}

float SkRect_centerY(void *rect) {
    return static_cast<SkRect *>(rect)->centerY();
}

sk_point_t SkRect_center(void *rect) {
    return static_sk_point_make(static_cast<SkRect *>(rect)->center());
}

void SkRect_toQuad(void *rect, void * quad) {
    static_cast<SkRect *>(rect)->toQuad(static_cast<SkPoint *>(quad));
}

void SkRect_setEmpty(void *rect) {
    static_cast<SkRect *>(rect)->setEmpty();
}

void SkRect_set(void *rect, const void *src) {
    static_cast<SkRect *>(rect)->set(* static_cast<const SkIRect *>(src));
}

void SkRect_setLTRB(void *rect, float left, float top, float right, float bottom) {
    static_cast<SkRect *>(rect)->setLTRB(left, top, right, bottom);
}

void SkRect_setBounds(void *rect, const void * pts, int count) {
    static_cast<SkRect *>(rect)->setBounds(static_cast<const SkPoint *>(pts), count);
}

bool SkRect_setBoundsCheck(void *rect, const void * pts, int count) {
    return static_cast<SkRect *>(rect)->setBoundsCheck(static_cast<const SkPoint *>(pts), count);
}

void SkRect_setBoundsNoCheck(void *rect, const void * pts, int count) {
    static_cast<SkRect *>(rect)->setBoundsNoCheck(static_cast<const SkPoint *>(pts), count);
}

void SkRect_set_2(void *rect, const void *p0, const void *p1) {
    static_cast<SkRect *>(rect)->set(* static_cast<const SkPoint *>(p0), * static_cast<const SkPoint *>(p1));
}

void SkRect_setXYWH(void *rect, float x, float y, float width, float height) {
    static_cast<SkRect *>(rect)->setXYWH(x, y, width, height);
}

void SkRect_setWH(void *rect, float width, float height) {
    static_cast<SkRect *>(rect)->setWH(width, height);
}

void SkRect_setIWH(void *rect, int32_t width, int32_t height) {
    static_cast<SkRect *>(rect)->setIWH(width, height);
}

sk_rect_t SkRect_makeOffset(void *rect, float dx, float dy) {
    return static_sk_rect_make(static_cast<SkRect *>(rect)->makeOutset(dx, dy));
}

sk_rect_t SkRect_makeOffset_2(void *rect, sk_point_t v) {
    return static_sk_rect_make(static_cast<SkRect *>(rect)->makeOffset(static_sk_point_get_entity(v)));
}

sk_rect_t SkRect_makeInset(void *rect, float dx, float dy) {
    return static_sk_rect_make(static_cast<SkRect *>(rect)->makeInset(dx, dy));
}

sk_rect_t SkRect_makeOutset(void *rect, float dx, float dy) {
    return static_sk_rect_make(static_cast<SkRect *>(rect)->makeOutset(dx, dy));
}

void SkRect_offset(void *rect, float dx, float dy) {
    static_cast<SkRect *>(rect)->offset(dx, dy);
}

void SkRect_offset_2(void *rect, const void *delta) {
    static_cast<SkRect *>(rect)->offset(* static_cast<const SkPoint *>(delta));
}

void SkRect_offsetTo(void *rect, float newX, float newY) {
    static_cast<SkRect *>(rect)->offsetTo(newX, newY);
}

void SkRect_inset(void *rect, float dx, float dy) {
    static_cast<SkRect *>(rect)->inset(dx, dy);
}

void SkRect_outset(void *rect, float dx, float dy) {
    static_cast<SkRect *>(rect)->outset(dx, dy);
}

bool SkRect_intersect(void *rect, const void *r) {
    return static_cast<SkRect *>(rect)->intersect(* static_cast<const SkRect *>(r));
}

bool SkRect_intersect_2(void *rect, const void *a, const void *b) {
    return static_cast<SkRect *>(rect)->intersect(* static_cast<const SkRect *>(a), * static_cast<const SkRect *>(b));
}

bool SkRect_intersects(void *rect, const void *r) {
    return static_cast<SkRect *>(rect)->intersects(* static_cast<const SkRect *>(r));
}

void SkRect_join(void *rect, const void *r) {
    static_cast<SkRect *>(rect)->join(* static_cast<const SkRect *>(r));
}

void SkRect_joinNonEmptyArg(void *rect, const void *r) {
    static_cast<SkRect *>(rect)->joinNonEmptyArg(* static_cast<const SkRect *>(r));
}

void SkRect_joinPossiblyEmptyRect(void *rect, const void *r) {
    static_cast<SkRect *>(rect)->joinPossiblyEmptyRect(* static_cast<const SkRect *>(r));
}

bool SkRect_contains(void *rect, float x, float y) {
    return static_cast<SkRect *>(rect)->contains(x, y);
}

bool SkRect_contains_2(void *rect, const void *r) {
    return static_cast<SkRect *>(rect)->contains(* static_cast<const SkRect *>(r));
}

bool SkRect_contains_3(void *rect, const void *r) {
    return static_cast<SkRect *>(rect)->contains(* static_cast<const SkIRect *>(r));
}

void SkRect_round(void *rect, void *dst) {
    static_cast<SkRect *>(rect)->round(static_cast<SkIRect *>(dst));
}

void SkRect_roundOut(void *rect, void *dst) {
    static_cast<SkRect *>(rect)->roundOut(static_cast<SkIRect *>(dst));
}

void SkRect_roundOut_2(void *rect, void *dst) {
    static_cast<SkRect *>(rect)->roundOut(static_cast<SkRect *>(dst));
}

void SkRect_roundIn(void *rect, void *dst) {
    static_cast<SkRect *>(rect)->roundIn(static_cast<SkIRect *>(dst));
}

sk_i_rect_t SkRect_round_2(void *rect) {
    return static_sk_i_rect_make(static_cast<SkRect *>(rect)->round());
}

sk_i_rect_t SkRect_roundOut_3(void *rect) {
    return static_sk_i_rect_make(static_cast<SkRect *>(rect)->roundOut());
}

sk_i_rect_t SkRect_roundIn_2(void *rect) {
    return static_sk_i_rect_make(static_cast<SkRect *>(rect)->roundIn());
}

void SkRect_sort(void *rect) {
    static_cast<SkRect *>(rect)->sort();
}

sk_rect_t SkRect_makeSorted(void *rect) {
    return static_sk_rect_make(static_cast<SkRect *>(rect)->makeSorted());
}

const float * SkRect_asScalars(void *rect) {
    return static_cast<SkRect *>(rect)->asScalars();
}

void SkRect_dump(void *rect, bool asHex) {
    static_cast<SkRect *>(rect)->dump(asHex);
}

void SkRect_dump_2(void *rect) {
    static_cast<SkRect *>(rect)->dump();
}

void SkRect_dumpHex(void *rect) {
    static_cast<SkRect *>(rect)->dumpHex();
}

// static

sk_rect_t SkRect_MakeEmpty() {
    return static_sk_rect_make(SkRect::MakeEmpty());
}

sk_rect_t SkRect_MakeWH(float w, float h) {
    return static_sk_rect_make(SkRect::MakeWH(w, h));
}

sk_rect_t SkRect_MakeIWH(int w, int h) {
    return static_sk_rect_make(SkRect::MakeIWH(w, h));
}

sk_rect_t SkRect_MakeSize(const void *size) {
    return static_sk_rect_make(SkRect::MakeSize(* static_cast<const SkSize *>(size)));
}

sk_rect_t SkRect_MakeLTRB(float l, float t, float r, float b) {
    return static_sk_rect_make(SkRect::MakeLTRB(l, t, r, b));
}

sk_rect_t SkRect_MakeXYWH(float x, float y, float w, float h) {
    return static_sk_rect_make(SkRect::MakeXYWH(x, y, w, h));
}

sk_rect_t SkRect_Make(const void *size) {
    return static_sk_rect_make(SkRect::Make(* static_cast<const SkISize *>(size)));
}

sk_rect_t SkRect_Make_2(const void *irect) {
    return static_sk_rect_make(SkRect::Make(* static_cast<const SkIRect *>(irect)));
}

bool SkRect_Intersects(const void *a, const void *b) {
    return SkRect::Intersects(* static_cast<const SkRect *>(a), * static_cast<const SkRect *>(b));
}

}
