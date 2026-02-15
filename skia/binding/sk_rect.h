//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_RECT_H
#define RAIA_SKIA_SK_RECT_H

#include "../static/static_sk_i_rect.h"
#include "../static/static_sk_point.h"
#include "../static/static_sk_rect.h"

typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_i_size_t reskia_i_size_t;
typedef struct reskia_point_t reskia_point_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_size_t reskia_size_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkRect_delete(reskia_rect_t *rect); // (SkRect *rect)
bool SkRect_isEmpty(reskia_rect_t *rect); // (SkRect *rect) -> bool
bool SkRect_isSorted(reskia_rect_t *rect); // (SkRect *rect) -> bool
bool SkRect_isFinite(reskia_rect_t *rect); // (SkRect *rect) -> bool
float SkRect_x(reskia_rect_t *rect); // (SkRect *rect) -> float
float SkRect_y(reskia_rect_t *rect); // (SkRect *rect) -> float
float SkRect_left(reskia_rect_t *rect); // (SkRect *rect) -> float
float SkRect_top(reskia_rect_t *rect); // (SkRect *rect) -> float
float SkRect_right(reskia_rect_t *rect); // (SkRect *rect) -> float
float SkRect_bottom(reskia_rect_t *rect); // (SkRect *rect) -> float
float SkRect_width(reskia_rect_t *rect); // (SkRect *rect) -> float
float SkRect_height(reskia_rect_t *rect); // (SkRect *rect) -> float
float SkRect_centerX(reskia_rect_t *rect); // (SkRect *rect) -> float
float SkRect_centerY(reskia_rect_t *rect); // (SkRect *rect) -> float
sk_point_t SkRect_center(reskia_rect_t *rect); // (SkRect *rect) -> sk_point_t
void SkRect_toQuad(reskia_rect_t *rect, reskia_point_t *quad); // (SkRect *rect, SkPoint quad[4])
void SkRect_setEmpty(reskia_rect_t *rect); // (SkRect *rect)
void SkRect_set(reskia_rect_t *rect, const reskia_i_rect_t *src); // (SkRect *rect, const SkIRect *src)
void SkRect_setLTRB(reskia_rect_t *rect, float left, float top, float right, float bottom); // (SkRect *rect, float left, float top, float right, float bottom)
void SkRect_setBounds(reskia_rect_t *rect, const reskia_point_t *pts, int count); // (SkRect *rect, const SkPoint pts[], int count)
bool SkRect_setBoundsCheck(reskia_rect_t *rect, const reskia_point_t *pts, int count); // (SkRect *rect, const SkPoint pts[], int count) -> bool
void SkRect_setBoundsNoCheck(reskia_rect_t *rect, const reskia_point_t *pts, int count); // (SkRect *rect, const SkPoint pts[], int count)
void SkRect_set_2(reskia_rect_t *rect, const reskia_point_t *p0, const reskia_point_t *p1); // (SkRect *rect, const SkPoint *p0, const SkPoint *p1)
void SkRect_setXYWH(reskia_rect_t *rect, float x, float y, float width, float height); // (SkRect *rect, float x, float y, float width, float height)
void SkRect_setWH(reskia_rect_t *rect, float width, float height); // (SkRect *rect, float width, float height)
void SkRect_setIWH(reskia_rect_t *rect, int width, int height); // (SkRect *rect, int32_t width, int32_t height)
sk_rect_t SkRect_makeOffset(reskia_rect_t *rect, float dx, float dy); // (SkRect *rect, float dx, float dy) -> sk_rect_t
sk_rect_t SkRect_makeOffset_2(reskia_rect_t *rect, sk_point_t v); // (SkRect *rect, sk_point_t v) -> sk_rect_t
sk_rect_t SkRect_makeInset(reskia_rect_t *rect, float dx, float dy); // (SkRect *rect, float dx, float dy) -> sk_rect_t
sk_rect_t SkRect_makeOutset(reskia_rect_t *rect, float dx, float dy); // (SkRect *rect, float dx, float dy) -> sk_rect_t
void SkRect_offset(reskia_rect_t *rect, float dx, float dy); // (SkRect *rect, float dx, float dy)
void SkRect_offset_2(reskia_rect_t *rect, const reskia_point_t *delta); // (SkRect *rect, const SkPoint *delta)
void SkRect_offsetTo(reskia_rect_t *rect, float newX, float newY); // (SkRect *rect, float newX, float newY)
void SkRect_inset(reskia_rect_t *rect, float dx, float dy); // (SkRect *rect, float dx, float dy)
void SkRect_outset(reskia_rect_t *rect, float dx, float dy); // (SkRect *rect, float dx, float dy)
bool SkRect_intersect(reskia_rect_t *rect, const reskia_rect_t *r); // (SkRect *rect, const SkRect *r) -> bool
bool SkRect_intersect_2(reskia_rect_t *rect, const reskia_rect_t *a, const reskia_rect_t *b); // (SkRect *rect, const SkRect *a, const SkRect *b) -> bool
bool SkRect_intersects(reskia_rect_t *rect, const reskia_rect_t *r); // (SkRect *rect, const SkRect *r) -> bool
void SkRect_join(reskia_rect_t *rect, const reskia_rect_t *r); // (SkRect *rect, const SkRect *r)
void SkRect_joinNonEmptyArg(reskia_rect_t *rect, const reskia_rect_t *r); // (SkRect *rect, const SkRect *r)
void SkRect_joinPossiblyEmptyRect(reskia_rect_t *rect, const reskia_rect_t *r); // (SkRect *rect, const SkRect *r)
bool SkRect_contains(reskia_rect_t *rect, float x, float y); // (SkRect *rect, float x, float y) -> bool
bool SkRect_contains_2(reskia_rect_t *rect, const reskia_rect_t *r); // (SkRect *rect, const SkRect *r) -> bool
bool SkRect_contains_3(reskia_rect_t *rect, const reskia_i_rect_t *r); // (SkRect *rect, const SkIRect *r) -> bool
void SkRect_round(reskia_rect_t *rect, reskia_i_rect_t *dst); // (SkRect *rect, SkIRect *dst)
void SkRect_roundOut(reskia_rect_t *rect, reskia_i_rect_t *dst); // (SkRect *rect, SkIRect *dst)
void SkRect_roundOut_2(reskia_rect_t *rect, reskia_rect_t *dst); // (SkRect *rect, SkRect *dst)
void SkRect_roundIn(reskia_rect_t *rect, reskia_i_rect_t *dst); // (SkRect *rect, SkIRect *dst)
sk_i_rect_t SkRect_round_2(reskia_rect_t *rect); // (SkRect *rect) -> sk_i_rect_t
sk_i_rect_t SkRect_roundOut_3(reskia_rect_t *rect); // (SkRect *rect) -> sk_i_rect_t
sk_i_rect_t SkRect_roundIn_2(reskia_rect_t *rect); // (SkRect *rect) -> sk_i_rect_t
void SkRect_sort(reskia_rect_t *rect); // (SkRect *rect)
sk_rect_t SkRect_makeSorted(reskia_rect_t *rect); // (SkRect *rect) -> sk_rect_t
const float * SkRect_asScalars(reskia_rect_t *rect); // (SkRect *rect) -> const float *
void SkRect_dump(reskia_rect_t *rect, bool asHex); // (SkRect *rect, bool asHex)
void SkRect_dump_2(reskia_rect_t *rect); // (SkRect *rect)
void SkRect_dumpHex(reskia_rect_t *rect); // (SkRect *rect)

// static

sk_rect_t SkRect_MakeEmpty(); // () -> sk_rect_t
sk_rect_t SkRect_MakeWH(float w, float h); // (float w, float h) -> sk_rect_t
sk_rect_t SkRect_MakeIWH(int w, int h); // (int w, int h) -> sk_rect_t
sk_rect_t SkRect_MakeSize(const reskia_size_t *size); // (const SkSize *size) -> sk_rect_t
sk_rect_t SkRect_MakeLTRB(float l, float t, float r, float b); // (float l, float t, float r, float b) -> sk_rect_t
sk_rect_t SkRect_MakeXYWH(float x, float y, float w, float h); // (float x, float y, float w, float h) -> sk_rect_t
sk_rect_t SkRect_Make(const reskia_i_size_t *size); // (const SkISize *size) -> sk_rect_t
sk_rect_t SkRect_Make_2(const reskia_i_rect_t *irect); // (const SkIRect *irect) -> sk_rect_t
bool SkRect_Intersects(const reskia_rect_t *a, const reskia_rect_t *b); // (const SkRect *a, const SkRect *b) -> bool

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_RECT_H
