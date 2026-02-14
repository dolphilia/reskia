//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_I_RECT_H
#define RAIA_SKIA_SK_I_RECT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_i_point_t reskia_i_point_t;
typedef struct reskia_i_size_t reskia_i_size_t;
typedef struct reskia_rect_t reskia_rect_t;

void SkIRect_delete(reskia_i_rect_t *i_rect); // (SkIRect *i_rect)
int SkIRect_left(reskia_i_rect_t *i_rect); // (SkIRect *i_rect) -> int32_t
int SkIRect_top(reskia_i_rect_t *i_rect); // (SkIRect *i_rect) -> int32_t
int SkIRect_right(reskia_i_rect_t *i_rect); // (SkIRect *i_rect) -> int32_t
int SkIRect_bottom(reskia_i_rect_t *i_rect); // (SkIRect *i_rect) -> int32_t
int SkIRect_x(reskia_i_rect_t *i_rect); // (SkIRect *i_rect) -> int32_t
int SkIRect_y(reskia_i_rect_t *i_rect); // (SkIRect *i_rect) -> int32_t
int SkIRect_topLeft(reskia_i_rect_t *i_rect); // (SkIRect *i_rect) -> sk_i_point_t
int SkIRect_width(reskia_i_rect_t *i_rect); // (SkIRect *i_rect) -> int32_t
int SkIRect_height(reskia_i_rect_t *i_rect); // (SkIRect *i_rect) -> int32_t
int SkIRect_size(reskia_i_rect_t *i_rect); // (SkIRect *i_rect) -> sk_i_size_t
int64_t SkIRect_width64(reskia_i_rect_t *i_rect); // (SkIRect *i_rect) -> int64_t
int64_t SkIRect_height64(reskia_i_rect_t *i_rect); // (SkIRect *i_rect) -> int64_t
bool SkIRect_isEmpty64(reskia_i_rect_t *i_rect); // (SkIRect *i_rect) -> bool
bool SkIRect_isEmpty(reskia_i_rect_t *i_rect); // (SkIRect *i_rect) -> bool
void SkIRect_setEmpty(reskia_i_rect_t *i_rect); // (SkIRect *i_rect)
void SkIRect_setLTRB(reskia_i_rect_t *i_rect, int left, int top, int right, int bottom); // (SkIRect *i_rect, int32_t left, int32_t top, int32_t right, int32_t bottom)
void SkIRect_setXYWH(reskia_i_rect_t *i_rect, int x, int y, int width, int height); // (SkIRect *i_rect, int32_t x, int32_t y, int32_t width, int32_t height)
void SkIRect_setWH(reskia_i_rect_t *i_rect, int width, int height); // (SkIRect *i_rect, int32_t width, int32_t height)
void SkIRect_setSize(reskia_i_rect_t *i_rect, int size); // (SkIRect *i_rect, sk_i_size_t size)
int SkIRect_makeOffset(reskia_i_rect_t *i_rect, int dx, int dy); // (SkIRect *i_rect, int32_t dx, int32_t dy) -> sk_i_rect_t
int SkIRect_makeOffset_2(reskia_i_rect_t *i_rect, int offset); // (SkIRect *i_rect, sk_i_point_t offset) -> sk_i_rect_t
int SkIRect_makeInset(reskia_i_rect_t *i_rect, int dx, int dy); // (SkIRect *i_rect, int32_t dx, int32_t dy) -> sk_i_rect_t
int SkIRect_makeOutset(reskia_i_rect_t *i_rect, int dx, int dy); // (SkIRect *i_rect, int32_t dx, int32_t dy) -> sk_i_rect_t
void SkIRect_offset(reskia_i_rect_t *i_rect, int dx, int dy); // (SkIRect *i_rect, int32_t dx, int32_t dy)
void SkIRect_offset_2(reskia_i_rect_t *i_rect, const reskia_i_point_t *delta); // (SkIRect *i_rect, const SkIPoint *delta)
void SkIRect_offsetTo(reskia_i_rect_t *i_rect, int newX, int newY); // (SkIRect *i_rect, int32_t newX, int32_t newY)
void SkIRect_inset(reskia_i_rect_t *i_rect, int dx, int dy); // (SkIRect *i_rect, int32_t dx, int32_t dy)
void SkIRect_outset(reskia_i_rect_t *i_rect, int dx, int dy); // (SkIRect *i_rect, int32_t dx, int32_t dy)
void SkIRect_adjust(reskia_i_rect_t *i_rect, int dL, int dT, int dR, int dB); // (SkIRect *i_rect, int32_t dL, int32_t dT, int32_t dR, int32_t dB)
bool SkIRect_contains(reskia_i_rect_t *i_rect, int x, int y); // (SkIRect *i_rect, int32_t x, int32_t y) -> bool
bool SkIRect_contains_2(reskia_i_rect_t *i_rect, const reskia_i_rect_t *r); // (SkIRect *i_rect, const SkIRect *r) -> bool
bool SkIRect_contains_3(reskia_i_rect_t *i_rect, const reskia_rect_t *r); // (SkIRect *i_rect, const SkRect *r) -> bool
bool SkIRect_containsNoEmptyCheck(reskia_i_rect_t *i_rect, const reskia_i_rect_t *r); // (SkIRect *i_rect, const SkIRect *r) -> bool
bool SkIRect_intersect(reskia_i_rect_t *i_rect, const reskia_i_rect_t *r); // (SkIRect *i_rect, const SkIRect *r) -> bool
bool SkIRect_intersect_2(reskia_i_rect_t *i_rect, const reskia_i_rect_t *a, const reskia_i_rect_t *b); // (SkIRect *i_rect, const SkIRect *a, const SkIRect *b) -> bool
void SkIRect_join(reskia_i_rect_t *i_rect, const reskia_i_rect_t *r); // (SkIRect *i_rect, const SkIRect *r)
void SkIRect_sort(reskia_i_rect_t *i_rect); // (SkIRect *i_rect)
int SkIRect_makeSorted(reskia_i_rect_t *i_rect); // (SkIRect *i_rect) -> sk_i_rect_t

// static

int SkIRect_MakeEmpty(); // () -> sk_i_rect_t
int SkIRect_MakeWH(int w, int h); // (int32_t w, int32_t h) -> sk_i_rect_t
int SkIRect_MakeSize(const reskia_i_size_t *size); // (const SkISize *size) -> sk_i_rect_t
int SkIRect_MakePtSize(int pt, int size); // (sk_i_point_t pt, sk_i_size_t size) -> sk_i_rect_t
int SkIRect_MakeLTRB(int l, int t, int r, int b); // (int32_t l, int32_t t, int32_t r, int32_t b) -> sk_i_rect_t
int SkIRect_MakeXYWH(int x, int y, int w, int h); // (int32_t x, int32_t y, int32_t w, int32_t h) -> sk_i_rect_t
bool SkIRect_Intersects(const reskia_i_rect_t *a, const reskia_i_rect_t *b); // (const SkIRect *a, const SkIRect *b) -> bool

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_I_RECT_H
