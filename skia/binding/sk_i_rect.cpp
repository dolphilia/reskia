//
// Created by dolphilia on 2024/01/09.
//

#include "sk_i_rect.h"

#include "include/core/SkRect.h"

#include "../static/static_sk_i_rect.h"
#include "../static/static_sk_i_size.h"
#include "../static/static_sk_i_point.h"

#include "../static/static_sk_i_point-internal.h"
#include "../static/static_sk_i_rect-internal.h"
#include "../static/static_sk_i_size-internal.h"

extern "C" {

void SkIRect_delete(void *i_rect) {
    delete static_cast<SkIRect *>(i_rect);
}

int32_t SkIRect_left(void *i_rect) {
    return static_cast<SkIRect *>(i_rect)->left();
}

int32_t SkIRect_top(void *i_rect) {
    return static_cast<SkIRect *>(i_rect)->top();
}

int32_t SkIRect_right(void *i_rect) {
    return static_cast<SkIRect *>(i_rect)->right();
}

int32_t SkIRect_bottom(void *i_rect) {
    return static_cast<SkIRect *>(i_rect)->bottom();
}

int32_t SkIRect_x(void *i_rect) {
    return static_cast<SkIRect *>(i_rect)->x();
}

int32_t SkIRect_y(void *i_rect) {
    return static_cast<SkIRect *>(i_rect)->y();
}

sk_i_point_t SkIRect_topLeft(void *i_rect) {
    return static_sk_i_point_make(static_cast<SkIRect *>(i_rect)->topLeft());
}

int32_t SkIRect_width(void *i_rect) {
    return static_cast<SkIRect *>(i_rect)->width();
}

int32_t SkIRect_height(void *i_rect) {
    return static_cast<SkIRect *>(i_rect)->height();
}

sk_i_size_t SkIRect_size(void *i_rect) {
    return static_sk_i_size_make(static_cast<SkIRect *>(i_rect)->size());
}

int64_t SkIRect_width64(void *i_rect) {
    return static_cast<SkIRect *>(i_rect)->width64();
}

int64_t SkIRect_height64(void *i_rect) {
    return static_cast<SkIRect *>(i_rect)->height64();
}

bool SkIRect_isEmpty64(void *i_rect) {
    return static_cast<SkIRect *>(i_rect)->isEmpty64();
}

bool SkIRect_isEmpty(void *i_rect) {
    return static_cast<SkIRect *>(i_rect)->isEmpty();
}

void SkIRect_setEmpty(void *i_rect) {
    static_cast<SkIRect *>(i_rect)->setEmpty();
}

void SkIRect_setLTRB(void *i_rect, int32_t left, int32_t top, int32_t right, int32_t bottom) {
    static_cast<SkIRect *>(i_rect)->setLTRB(left, top, right, bottom);
}

void SkIRect_setXYWH(void *i_rect, int32_t x, int32_t y, int32_t width, int32_t height) {
    static_cast<SkIRect *>(i_rect)->setXYWH(x, y, width, height);
}

void SkIRect_setWH(void *i_rect, int32_t width, int32_t height) {
    static_cast<SkIRect *>(i_rect)->setWH(width, height);
}

void SkIRect_setSize(void *i_rect, sk_i_size_t size) {
    static_cast<SkIRect *>(i_rect)->setSize(static_sk_i_size_get(size));
}

sk_i_rect_t SkIRect_makeOffset(void *i_rect, int32_t dx, int32_t dy) {
    return static_sk_i_rect_make(static_cast<SkIRect *>(i_rect)->makeOffset(dx, dy));
}

sk_i_rect_t SkIRect_makeOffset_2(void *i_rect, sk_i_point_t offset) {
    return static_sk_i_rect_make(static_cast<SkIRect *>(i_rect)->makeOffset(static_sk_i_point_get(offset)));
}

sk_i_rect_t SkIRect_makeInset(void *i_rect, int32_t dx, int32_t dy) {
    return static_sk_i_rect_make(static_cast<SkIRect *>(i_rect)->makeInset(dx, dy));
}

sk_i_rect_t SkIRect_makeOutset(void *i_rect, int32_t dx, int32_t dy) {
    return static_sk_i_rect_make(static_cast<SkIRect *>(i_rect)->makeOutset(dx, dy));
}

void SkIRect_offset(void *i_rect, int32_t dx, int32_t dy) {
    return static_cast<SkIRect *>(i_rect)->offset(dx, dy);
}

void SkIRect_offset_2(void *i_rect, const void *delta) {
    static_cast<SkIRect *>(i_rect)->offset(* static_cast<const SkIPoint *>(delta));
}

void SkIRect_offsetTo(void *i_rect, int32_t newX, int32_t newY) {
    static_cast<SkIRect *>(i_rect)->offsetTo(newX, newY);
}

void SkIRect_inset(void *i_rect, int32_t dx, int32_t dy) {
    return static_cast<SkIRect *>(i_rect)->inset(dx, dy);
}

void SkIRect_outset(void *i_rect, int32_t dx, int32_t dy) {
    static_cast<SkIRect *>(i_rect)->outset(dx, dy);
}

void SkIRect_adjust(void *i_rect, int32_t dL, int32_t dT, int32_t dR, int32_t dB) {
    static_cast<SkIRect *>(i_rect)->adjust(dL, dT, dR, dB);
}

bool SkIRect_contains(void *i_rect, int32_t x, int32_t y) {
    return static_cast<SkIRect *>(i_rect)->contains(x, y);
}

bool SkIRect_contains_2(void *i_rect, const void *r) {
    return static_cast<SkIRect *>(i_rect)->contains(* static_cast<const SkIRect *>(r));
}

bool SkIRect_contains_3(void *i_rect, const void *r) {
    return static_cast<SkIRect *>(i_rect)->contains(* static_cast<const SkRect *>(r));
}

bool SkIRect_containsNoEmptyCheck(void *i_rect, const void *r) {
    return static_cast<SkIRect *>(i_rect)->containsNoEmptyCheck(* static_cast<const SkIRect *>(r));
}

bool SkIRect_intersect(void *i_rect, const void *r) {
    return static_cast<SkIRect *>(i_rect)->intersect(* static_cast<const SkIRect *>(r));
}

bool SkIRect_intersect_2(void *i_rect, const void *a, const void *b) {
    return static_cast<SkIRect *>(i_rect)->intersect(* static_cast<const SkIRect *>(a), * static_cast<const SkIRect *>(b));
}

void SkIRect_join(void *i_rect, const void *r) {
    static_cast<SkIRect *>(i_rect)->join(* static_cast<const SkIRect *>(r));
}

void SkIRect_sort(void *i_rect) {
    static_cast<SkIRect *>(i_rect)->sort();
}

sk_i_rect_t SkIRect_makeSorted(void *i_rect) {
    return static_sk_i_rect_make(static_cast<SkIRect *>(i_rect)->makeSorted());
}

// static

sk_i_rect_t SkIRect_MakeEmpty() {
    return static_sk_i_rect_make(SkIRect::MakeEmpty());
}

sk_i_rect_t SkIRect_MakeWH(int32_t w, int32_t h) {
    return static_sk_i_rect_make(SkIRect::MakeWH(w, h));
}

sk_i_rect_t SkIRect_MakeSize(const void *size) {
    return static_sk_i_rect_make(SkIRect::MakeSize(* static_cast<const SkISize *>(size)));
}

sk_i_rect_t SkIRect_MakePtSize(sk_i_point_t pt, sk_i_size_t size) {
    return static_sk_i_rect_make(SkIRect::MakePtSize(static_sk_i_point_get(pt), static_sk_i_size_get(size)));
}

sk_i_rect_t SkIRect_MakeLTRB(int32_t l, int32_t t, int32_t r, int32_t b) {
    return static_sk_i_rect_make(SkIRect::MakeLTRB(l, t, r, b));
}

sk_i_rect_t SkIRect_MakeXYWH(int32_t x, int32_t y, int32_t w, int32_t h) {
    return static_sk_i_rect_make(SkIRect::MakeXYWH(x, y, w, h));
}

bool SkIRect_Intersects(const void *a, const void *b) {
    return SkIRect::Intersects(* static_cast<const SkIRect *>(a), * static_cast<const SkIRect *>(b));
}

}
