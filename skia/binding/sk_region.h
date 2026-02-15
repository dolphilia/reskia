//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_REGION_H
#define RAIA_SKIA_SK_REGION_H

#include <stddef.h>

typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_path_t reskia_path_t;
typedef struct reskia_region_t reskia_region_t;

#ifdef __cplusplus
extern "C" {
#endif

//SkRegion & operator=(const SkRegion &region)
//bool operator==(const SkRegion &other)
//bool operator!=(const SkRegion &other)

reskia_region_t *SkRegion_new(); // () -> SkRegion *
reskia_region_t *SkRegion_new_2(const reskia_region_t *region); // (const SkRegion *region) -> SkRegion *
reskia_region_t *SkRegion_new_3(const reskia_i_rect_t *rect); // (const SkIRect *rect) -> SkRegion *
void SkRegion_delete(reskia_region_t *region); // (SkRegion *region)
bool SkRegion_set(reskia_region_t *region, const reskia_region_t *src); // (SkRegion *region, const SkRegion *src) -> bool
void SkRegion_swap(reskia_region_t *region, reskia_region_t *other); // (SkRegion *region, SkRegion *other)
bool SkRegion_isEmpty(reskia_region_t *region); // (SkRegion *region) -> bool
bool SkRegion_isRect(reskia_region_t *region); // (SkRegion *region) -> bool
bool SkRegion_isComplex(reskia_region_t *region); // (SkRegion *region) -> bool
const reskia_i_rect_t *SkRegion_getBounds(reskia_region_t *region); // (SkRegion *region) -> const SkIRect *
int SkRegion_computeRegionComplexity(reskia_region_t *region); // (SkRegion *region) -> int
bool SkRegion_getBoundaryPath(reskia_region_t *region, reskia_path_t *path); // (SkRegion *region, SkPath *path) -> bool
bool SkRegion_setEmpty(reskia_region_t *region); // (SkRegion *region) -> bool
bool SkRegion_setRect(reskia_region_t *region, const reskia_i_rect_t *rect); // (SkRegion *region, const SkIRect *rect) -> bool
bool SkRegion_setRects(reskia_region_t *region, const reskia_i_rect_t *rects, int count); // (SkRegion *region, const SkIRect rects[], int count) -> bool
bool SkRegion_setRegion(reskia_region_t *region, const reskia_region_t *region_2); // (SkRegion *region, const SkRegion *region_2) -> bool
bool SkRegion_setPath(reskia_region_t *region, const reskia_path_t *path, const reskia_region_t *clip); // (SkRegion *region, const SkPath *path, const SkRegion *clip) -> bool
bool SkRegion_intersects(reskia_region_t *region, const reskia_i_rect_t *rect); // (SkRegion *region, const SkIRect *rect) -> bool
bool SkRegion_intersects_2(reskia_region_t *region, const reskia_region_t *other); // (SkRegion *region, const SkRegion *other) -> bool
bool SkRegion_contains(reskia_region_t *region, int x, int y); // (SkRegion *region, int32_t x, int32_t y) -> bool
bool SkRegion_contains_2(reskia_region_t *region, const reskia_i_rect_t *other); // (SkRegion *region, const SkIRect *other) -> bool
bool SkRegion_contains_3(reskia_region_t *region, const reskia_region_t *other); // (SkRegion *region, const SkRegion *other) -> bool
bool SkRegion_quickContains(reskia_region_t *region, const reskia_i_rect_t *r); // (SkRegion *region, const SkIRect *r) -> bool
bool SkRegion_quickReject(reskia_region_t *region, const reskia_i_rect_t *rect); // (SkRegion *region, const SkIRect *rect) -> bool
bool SkRegion_quickReject_2(reskia_region_t *region, const reskia_region_t *rgn); // (SkRegion *region, const SkRegion *rgn) -> bool
void SkRegion_translate(reskia_region_t *region, int dx, int dy); // (SkRegion *region, int dx, int dy)
void SkRegion_translate_2(reskia_region_t *region, int dx, int dy, reskia_region_t *dst); // (SkRegion *region, int dx, int dy, SkRegion *dst)
bool SkRegion_op(reskia_region_t *region, const reskia_i_rect_t *rect, int op); // (SkRegion *region, const SkIRect *rect, SkRegion::Op op) -> bool
bool SkRegion_op_2(reskia_region_t *region, const reskia_region_t *rgn, int op); // (SkRegion *region, const SkRegion *rgn, SkRegion::Op op) -> bool
bool SkRegion_op_3(reskia_region_t *region, const reskia_i_rect_t *rect, const reskia_region_t *rgn, int op); // (SkRegion *region, const SkIRect *rect, const SkRegion *rgn, SkRegion::Op op) -> bool
bool SkRegion_op_4(reskia_region_t *region, const reskia_region_t *rgn, const reskia_i_rect_t *rect, int op); // (SkRegion *region, const SkRegion *rgn, const SkIRect *rect, SkRegion::Op op) -> bool
bool SkRegion_op_5(reskia_region_t *region, const reskia_region_t *rgna, const reskia_region_t *rgnb, int op); // (SkRegion *region, const SkRegion *rgna, const SkRegion *rgnb, SkRegion::Op op) -> bool
size_t SkRegion_writeToMemory(reskia_region_t *region, void *buffer); // (SkRegion *region, void *buffer) -> size_t
size_t SkRegion_readFromMemory(reskia_region_t *region, const void *buffer, size_t length); // (SkRegion *region, const void *buffer, size_t length) -> size_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_REGION_H
