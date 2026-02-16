//
// Created by dolphilia on 2024/01/10.
//

#include "sk_rect.h"

#include "include/core/SkRect.h"

#include "../handles/static_sk_rect.h"
#include "../handles/static_sk_i_rect.h"
#include "../handles/static_sk_point.h"

#include "../handles/static_sk_i_rect-internal.h"
#include "../handles/static_sk_point-internal.h"
#include "../handles/static_sk_rect-internal.h"

extern "C" {

void SkRect_delete(reskia_rect_t *rect) {
    delete reinterpret_cast<SkRect *>(rect);
}

bool SkRect_isEmpty(reskia_rect_t *rect) {
    return reinterpret_cast<SkRect *>(rect)->isEmpty();
}

bool SkRect_isSorted(reskia_rect_t *rect) {
    return reinterpret_cast<SkRect *>(rect)->isSorted();
}

bool SkRect_isFinite(reskia_rect_t *rect) {
    return reinterpret_cast<SkRect *>(rect)->isFinite();
}

float SkRect_x(reskia_rect_t *rect) {
    return reinterpret_cast<SkRect *>(rect)->x();
}

float SkRect_y(reskia_rect_t *rect) {
    return reinterpret_cast<SkRect *>(rect)->y();
}

float SkRect_left(reskia_rect_t *rect) {
    return reinterpret_cast<SkRect *>(rect)->left();
}

float SkRect_top(reskia_rect_t *rect) {
    return reinterpret_cast<SkRect *>(rect)->top();
}

float SkRect_right(reskia_rect_t *rect) {
    return reinterpret_cast<SkRect *>(rect)->right();
}

float SkRect_bottom(reskia_rect_t *rect) {
    return reinterpret_cast<SkRect *>(rect)->bottom();
}

float SkRect_width(reskia_rect_t *rect) {
    return reinterpret_cast<SkRect *>(rect)->width();
}

float SkRect_height(reskia_rect_t *rect) {
    return reinterpret_cast<SkRect *>(rect)->height();
}

float SkRect_centerX(reskia_rect_t *rect) {
    return reinterpret_cast<SkRect *>(rect)->centerX();
}

float SkRect_centerY(reskia_rect_t *rect) {
    return reinterpret_cast<SkRect *>(rect)->centerY();
}

sk_point_t SkRect_center(reskia_rect_t *rect) {
    return static_sk_point_make(reinterpret_cast<SkRect *>(rect)->center());
}

void SkRect_toQuad(reskia_rect_t *rect, reskia_point_t *quad) {
    reinterpret_cast<SkRect *>(rect)->toQuad(reinterpret_cast<SkPoint *>(quad));
}

void SkRect_setEmpty(reskia_rect_t *rect) {
    reinterpret_cast<SkRect *>(rect)->setEmpty();
}

void SkRect_set(reskia_rect_t *rect, const reskia_i_rect_t *src) {
    reinterpret_cast<SkRect *>(rect)->set(* reinterpret_cast<const SkIRect *>(src));
}

void SkRect_setLTRB(reskia_rect_t *rect, float left, float top, float right, float bottom) {
    reinterpret_cast<SkRect *>(rect)->setLTRB(left, top, right, bottom);
}

void SkRect_setBounds(reskia_rect_t *rect, const reskia_point_t *pts, int count) {
    reinterpret_cast<SkRect *>(rect)->setBounds(reinterpret_cast<const SkPoint *>(pts), count);
}

bool SkRect_setBoundsCheck(reskia_rect_t *rect, const reskia_point_t *pts, int count) {
    return reinterpret_cast<SkRect *>(rect)->setBoundsCheck(reinterpret_cast<const SkPoint *>(pts), count);
}

void SkRect_setBoundsNoCheck(reskia_rect_t *rect, const reskia_point_t *pts, int count) {
    reinterpret_cast<SkRect *>(rect)->setBoundsNoCheck(reinterpret_cast<const SkPoint *>(pts), count);
}

void SkRect_set_2(reskia_rect_t *rect, const reskia_point_t *p0, const reskia_point_t *p1) {
    reinterpret_cast<SkRect *>(rect)->set(* reinterpret_cast<const SkPoint *>(p0), * reinterpret_cast<const SkPoint *>(p1));
}

void SkRect_setXYWH(reskia_rect_t *rect, float x, float y, float width, float height) {
    reinterpret_cast<SkRect *>(rect)->setXYWH(x, y, width, height);
}

void SkRect_setWH(reskia_rect_t *rect, float width, float height) {
    reinterpret_cast<SkRect *>(rect)->setWH(width, height);
}

void SkRect_setIWH(reskia_rect_t *rect, int32_t width, int32_t height) {
    reinterpret_cast<SkRect *>(rect)->setIWH(width, height);
}

sk_rect_t SkRect_makeOffset(reskia_rect_t *rect, float dx, float dy) {
    return static_sk_rect_make(reinterpret_cast<SkRect *>(rect)->makeOutset(dx, dy));
}

sk_rect_t SkRect_makeOffset_2(reskia_rect_t *rect, sk_point_t v) {
    return static_sk_rect_make(reinterpret_cast<SkRect *>(rect)->makeOffset(static_sk_point_get_entity(v)));
}

sk_rect_t SkRect_makeInset(reskia_rect_t *rect, float dx, float dy) {
    return static_sk_rect_make(reinterpret_cast<SkRect *>(rect)->makeInset(dx, dy));
}

sk_rect_t SkRect_makeOutset(reskia_rect_t *rect, float dx, float dy) {
    return static_sk_rect_make(reinterpret_cast<SkRect *>(rect)->makeOutset(dx, dy));
}

void SkRect_offset(reskia_rect_t *rect, float dx, float dy) {
    reinterpret_cast<SkRect *>(rect)->offset(dx, dy);
}

void SkRect_offset_2(reskia_rect_t *rect, const reskia_point_t *delta) {
    reinterpret_cast<SkRect *>(rect)->offset(* reinterpret_cast<const SkPoint *>(delta));
}

void SkRect_offsetTo(reskia_rect_t *rect, float newX, float newY) {
    reinterpret_cast<SkRect *>(rect)->offsetTo(newX, newY);
}

void SkRect_inset(reskia_rect_t *rect, float dx, float dy) {
    reinterpret_cast<SkRect *>(rect)->inset(dx, dy);
}

void SkRect_outset(reskia_rect_t *rect, float dx, float dy) {
    reinterpret_cast<SkRect *>(rect)->outset(dx, dy);
}

bool SkRect_intersect(reskia_rect_t *rect, const reskia_rect_t *r) {
    return reinterpret_cast<SkRect *>(rect)->intersect(* reinterpret_cast<const SkRect *>(r));
}

bool SkRect_intersect_2(reskia_rect_t *rect, const reskia_rect_t *a, const reskia_rect_t *b) {
    return reinterpret_cast<SkRect *>(rect)->intersect(* reinterpret_cast<const SkRect *>(a), * reinterpret_cast<const SkRect *>(b));
}

bool SkRect_intersects(reskia_rect_t *rect, const reskia_rect_t *r) {
    return reinterpret_cast<SkRect *>(rect)->intersects(* reinterpret_cast<const SkRect *>(r));
}

void SkRect_join(reskia_rect_t *rect, const reskia_rect_t *r) {
    reinterpret_cast<SkRect *>(rect)->join(* reinterpret_cast<const SkRect *>(r));
}

void SkRect_joinNonEmptyArg(reskia_rect_t *rect, const reskia_rect_t *r) {
    reinterpret_cast<SkRect *>(rect)->joinNonEmptyArg(* reinterpret_cast<const SkRect *>(r));
}

void SkRect_joinPossiblyEmptyRect(reskia_rect_t *rect, const reskia_rect_t *r) {
    reinterpret_cast<SkRect *>(rect)->joinPossiblyEmptyRect(* reinterpret_cast<const SkRect *>(r));
}

bool SkRect_contains(reskia_rect_t *rect, float x, float y) {
    return reinterpret_cast<SkRect *>(rect)->contains(x, y);
}

bool SkRect_contains_2(reskia_rect_t *rect, const reskia_rect_t *r) {
    return reinterpret_cast<SkRect *>(rect)->contains(* reinterpret_cast<const SkRect *>(r));
}

bool SkRect_contains_3(reskia_rect_t *rect, const reskia_i_rect_t *r) {
    return reinterpret_cast<SkRect *>(rect)->contains(* reinterpret_cast<const SkIRect *>(r));
}

void SkRect_round(reskia_rect_t *rect, reskia_i_rect_t *dst) {
    reinterpret_cast<SkRect *>(rect)->round(reinterpret_cast<SkIRect *>(dst));
}

void SkRect_roundOut(reskia_rect_t *rect, reskia_i_rect_t *dst) {
    reinterpret_cast<SkRect *>(rect)->roundOut(reinterpret_cast<SkIRect *>(dst));
}

void SkRect_roundOut_2(reskia_rect_t *rect, reskia_rect_t *dst) {
    reinterpret_cast<SkRect *>(rect)->roundOut(reinterpret_cast<SkRect *>(dst));
}

void SkRect_roundIn(reskia_rect_t *rect, reskia_i_rect_t *dst) {
    reinterpret_cast<SkRect *>(rect)->roundIn(reinterpret_cast<SkIRect *>(dst));
}

sk_i_rect_t SkRect_round_2(reskia_rect_t *rect) {
    return static_sk_i_rect_make(reinterpret_cast<SkRect *>(rect)->round());
}

sk_i_rect_t SkRect_roundOut_3(reskia_rect_t *rect) {
    return static_sk_i_rect_make(reinterpret_cast<SkRect *>(rect)->roundOut());
}

sk_i_rect_t SkRect_roundIn_2(reskia_rect_t *rect) {
    return static_sk_i_rect_make(reinterpret_cast<SkRect *>(rect)->roundIn());
}

void SkRect_sort(reskia_rect_t *rect) {
    reinterpret_cast<SkRect *>(rect)->sort();
}

sk_rect_t SkRect_makeSorted(reskia_rect_t *rect) {
    return static_sk_rect_make(reinterpret_cast<SkRect *>(rect)->makeSorted());
}

const float * SkRect_asScalars(reskia_rect_t *rect) {
    return reinterpret_cast<SkRect *>(rect)->asScalars();
}

void SkRect_dump(reskia_rect_t *rect, bool asHex) {
    reinterpret_cast<SkRect *>(rect)->dump(asHex);
}

void SkRect_dump_2(reskia_rect_t *rect) {
    reinterpret_cast<SkRect *>(rect)->dump();
}

void SkRect_dumpHex(reskia_rect_t *rect) {
    reinterpret_cast<SkRect *>(rect)->dumpHex();
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

sk_rect_t SkRect_MakeSize(const reskia_size_t *size) {
    return static_sk_rect_make(SkRect::MakeSize(* reinterpret_cast<const SkSize *>(size)));
}

sk_rect_t SkRect_MakeLTRB(float l, float t, float r, float b) {
    return static_sk_rect_make(SkRect::MakeLTRB(l, t, r, b));
}

sk_rect_t SkRect_MakeXYWH(float x, float y, float w, float h) {
    return static_sk_rect_make(SkRect::MakeXYWH(x, y, w, h));
}

sk_rect_t SkRect_Make(const reskia_i_size_t *size) {
    return static_sk_rect_make(SkRect::Make(* reinterpret_cast<const SkISize *>(size)));
}

sk_rect_t SkRect_Make_2(const reskia_i_rect_t *irect) {
    return static_sk_rect_make(SkRect::Make(* reinterpret_cast<const SkIRect *>(irect)));
}

bool SkRect_Intersects(const reskia_rect_t *a, const reskia_rect_t *b) {
    return SkRect::Intersects(* reinterpret_cast<const SkRect *>(a), * reinterpret_cast<const SkRect *>(b));
}

}
