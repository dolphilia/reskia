//
// Created by dolphilia on 2024/01/09.
//

#include "sk_i_rect.h"

#include "include/core/SkRect.h"

#include "../handles/static_sk_i_rect.h"
#include "../handles/static_sk_i_size.h"
#include "../handles/static_sk_i_point.h"

#include "../handles/static_sk_i_point-internal.h"
#include "../handles/static_sk_i_rect-internal.h"
#include "../handles/static_sk_i_size-internal.h"

extern "C" {

void SkIRect_delete(reskia_i_rect_t *i_rect) {
    delete reinterpret_cast<SkIRect *>(i_rect);
}

int32_t SkIRect_left(reskia_i_rect_t *i_rect) {
    return reinterpret_cast<SkIRect *>(i_rect)->left();
}

int32_t SkIRect_top(reskia_i_rect_t *i_rect) {
    return reinterpret_cast<SkIRect *>(i_rect)->top();
}

int32_t SkIRect_right(reskia_i_rect_t *i_rect) {
    return reinterpret_cast<SkIRect *>(i_rect)->right();
}

int32_t SkIRect_bottom(reskia_i_rect_t *i_rect) {
    return reinterpret_cast<SkIRect *>(i_rect)->bottom();
}

int32_t SkIRect_x(reskia_i_rect_t *i_rect) {
    return reinterpret_cast<SkIRect *>(i_rect)->x();
}

int32_t SkIRect_y(reskia_i_rect_t *i_rect) {
    return reinterpret_cast<SkIRect *>(i_rect)->y();
}

sk_i_point_t SkIRect_topLeft(reskia_i_rect_t *i_rect) {
    return static_sk_i_point_make(reinterpret_cast<SkIRect *>(i_rect)->topLeft());
}

int32_t SkIRect_width(reskia_i_rect_t *i_rect) {
    return reinterpret_cast<SkIRect *>(i_rect)->width();
}

int32_t SkIRect_height(reskia_i_rect_t *i_rect) {
    return reinterpret_cast<SkIRect *>(i_rect)->height();
}

sk_i_size_t SkIRect_size(reskia_i_rect_t *i_rect) {
    return static_sk_i_size_make(reinterpret_cast<SkIRect *>(i_rect)->size());
}

int64_t SkIRect_width64(reskia_i_rect_t *i_rect) {
    return reinterpret_cast<SkIRect *>(i_rect)->width64();
}

int64_t SkIRect_height64(reskia_i_rect_t *i_rect) {
    return reinterpret_cast<SkIRect *>(i_rect)->height64();
}

bool SkIRect_isEmpty64(reskia_i_rect_t *i_rect) {
    return reinterpret_cast<SkIRect *>(i_rect)->isEmpty64();
}

bool SkIRect_isEmpty(reskia_i_rect_t *i_rect) {
    return reinterpret_cast<SkIRect *>(i_rect)->isEmpty();
}

void SkIRect_setEmpty(reskia_i_rect_t *i_rect) {
    reinterpret_cast<SkIRect *>(i_rect)->setEmpty();
}

void SkIRect_setLTRB(reskia_i_rect_t *i_rect, int32_t left, int32_t top, int32_t right, int32_t bottom) {
    reinterpret_cast<SkIRect *>(i_rect)->setLTRB(left, top, right, bottom);
}

void SkIRect_setXYWH(reskia_i_rect_t *i_rect, int32_t x, int32_t y, int32_t width, int32_t height) {
    reinterpret_cast<SkIRect *>(i_rect)->setXYWH(x, y, width, height);
}

void SkIRect_setWH(reskia_i_rect_t *i_rect, int32_t width, int32_t height) {
    reinterpret_cast<SkIRect *>(i_rect)->setWH(width, height);
}

void SkIRect_setSize(reskia_i_rect_t *i_rect, sk_i_size_t size) {
    reinterpret_cast<SkIRect *>(i_rect)->setSize(static_sk_i_size_get_entity(size));
}

sk_i_rect_t SkIRect_makeOffset(reskia_i_rect_t *i_rect, int32_t dx, int32_t dy) {
    return static_sk_i_rect_make(reinterpret_cast<SkIRect *>(i_rect)->makeOffset(dx, dy));
}

sk_i_rect_t SkIRect_makeOffsetWithPoint(reskia_i_rect_t *i_rect, sk_i_point_t offset) {
    return static_sk_i_rect_make(reinterpret_cast<SkIRect *>(i_rect)->makeOffset(static_sk_i_point_get_entity(offset)));
}

sk_i_rect_t SkIRect_makeInset(reskia_i_rect_t *i_rect, int32_t dx, int32_t dy) {
    return static_sk_i_rect_make(reinterpret_cast<SkIRect *>(i_rect)->makeInset(dx, dy));
}

sk_i_rect_t SkIRect_makeOutset(reskia_i_rect_t *i_rect, int32_t dx, int32_t dy) {
    return static_sk_i_rect_make(reinterpret_cast<SkIRect *>(i_rect)->makeOutset(dx, dy));
}

void SkIRect_offset(reskia_i_rect_t *i_rect, int32_t dx, int32_t dy) {
    return reinterpret_cast<SkIRect *>(i_rect)->offset(dx, dy);
}

void SkIRect_offsetWithPoint(reskia_i_rect_t *i_rect, const reskia_i_point_t *delta) {
    reinterpret_cast<SkIRect *>(i_rect)->offset(* reinterpret_cast<const SkIPoint *>(delta));
}

void SkIRect_offsetTo(reskia_i_rect_t *i_rect, int32_t newX, int32_t newY) {
    reinterpret_cast<SkIRect *>(i_rect)->offsetTo(newX, newY);
}

void SkIRect_inset(reskia_i_rect_t *i_rect, int32_t dx, int32_t dy) {
    return reinterpret_cast<SkIRect *>(i_rect)->inset(dx, dy);
}

void SkIRect_outset(reskia_i_rect_t *i_rect, int32_t dx, int32_t dy) {
    reinterpret_cast<SkIRect *>(i_rect)->outset(dx, dy);
}

void SkIRect_adjust(reskia_i_rect_t *i_rect, int32_t dL, int32_t dT, int32_t dR, int32_t dB) {
    reinterpret_cast<SkIRect *>(i_rect)->adjust(dL, dT, dR, dB);
}

bool SkIRect_contains(reskia_i_rect_t *i_rect, int32_t x, int32_t y) {
    return reinterpret_cast<SkIRect *>(i_rect)->contains(x, y);
}

bool SkIRect_containsIRect(reskia_i_rect_t *i_rect, const reskia_i_rect_t *r) {
    return reinterpret_cast<SkIRect *>(i_rect)->contains(* reinterpret_cast<const SkIRect *>(r));
}

bool SkIRect_containsRect(reskia_i_rect_t *i_rect, const reskia_rect_t *r) {
    return reinterpret_cast<SkIRect *>(i_rect)->contains(* reinterpret_cast<const SkRect *>(r));
}

bool SkIRect_containsNoEmptyCheck(reskia_i_rect_t *i_rect, const reskia_i_rect_t *r) {
    return reinterpret_cast<SkIRect *>(i_rect)->containsNoEmptyCheck(* reinterpret_cast<const SkIRect *>(r));
}

bool SkIRect_intersect(reskia_i_rect_t *i_rect, const reskia_i_rect_t *r) {
    return reinterpret_cast<SkIRect *>(i_rect)->intersect(* reinterpret_cast<const SkIRect *>(r));
}

bool SkIRect_intersectFromRects(reskia_i_rect_t *i_rect, const reskia_i_rect_t *a, const reskia_i_rect_t *b) {
    return reinterpret_cast<SkIRect *>(i_rect)->intersect(* reinterpret_cast<const SkIRect *>(a), * reinterpret_cast<const SkIRect *>(b));
}

void SkIRect_join(reskia_i_rect_t *i_rect, const reskia_i_rect_t *r) {
    reinterpret_cast<SkIRect *>(i_rect)->join(* reinterpret_cast<const SkIRect *>(r));
}

void SkIRect_sort(reskia_i_rect_t *i_rect) {
    reinterpret_cast<SkIRect *>(i_rect)->sort();
}

sk_i_rect_t SkIRect_makeSorted(reskia_i_rect_t *i_rect) {
    return static_sk_i_rect_make(reinterpret_cast<SkIRect *>(i_rect)->makeSorted());
}

// static

sk_i_rect_t SkIRect_MakeEmpty() {
    return static_sk_i_rect_make(SkIRect::MakeEmpty());
}

sk_i_rect_t SkIRect_MakeWH(int32_t w, int32_t h) {
    return static_sk_i_rect_make(SkIRect::MakeWH(w, h));
}

sk_i_rect_t SkIRect_MakeSize(const reskia_i_size_t *size) {
    return static_sk_i_rect_make(SkIRect::MakeSize(* reinterpret_cast<const SkISize *>(size)));
}

sk_i_rect_t SkIRect_MakePtSize(sk_i_point_t pt, sk_i_size_t size) {
    return static_sk_i_rect_make(SkIRect::MakePtSize(static_sk_i_point_get_entity(pt), static_sk_i_size_get_entity(size)));
}

sk_i_rect_t SkIRect_MakeLTRB(int32_t l, int32_t t, int32_t r, int32_t b) {
    return static_sk_i_rect_make(SkIRect::MakeLTRB(l, t, r, b));
}

sk_i_rect_t SkIRect_MakeXYWH(int32_t x, int32_t y, int32_t w, int32_t h) {
    return static_sk_i_rect_make(SkIRect::MakeXYWH(x, y, w, h));
}

bool SkIRect_Intersects(const reskia_i_rect_t *a, const reskia_i_rect_t *b) {
    return SkIRect::Intersects(* reinterpret_cast<const SkIRect *>(a), * reinterpret_cast<const SkIRect *>(b));
}

}
