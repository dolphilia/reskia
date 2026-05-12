//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_REGION_H
#define RAIA_SKIA_SK_REGION_H

#include <stddef.h>
#include <stdint.h>

typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_path_t reskia_path_t;
typedef struct reskia_region_t reskia_region_t;
typedef int32_t reskia_region_op_t;

#ifdef __cplusplus
extern "C" {
#endif

//SkRegion & operator=(const SkRegion &region)
reskia_region_t *SkRegion_new(); // () -> SkRegion *
reskia_region_t *SkRegion_newCopy(const reskia_region_t *region); // (const SkRegion *region) -> SkRegion *. NULL region returns NULL.
reskia_region_t *SkRegion_newFromIRect(const reskia_i_rect_t *rect); // (const SkIRect *rect) -> SkRegion *. rect is required.
void SkRegion_delete(reskia_region_t *region); // (SkRegion *region). NULL region is no-op.
bool SkRegion_equals(reskia_region_t *region, const reskia_region_t *other); // (SkRegion *region, const SkRegion *other) -> bool. NULL input returns false.
bool SkRegion_notEquals(reskia_region_t *region, const reskia_region_t *other); // (SkRegion *region, const SkRegion *other) -> bool. NULL input returns false.
bool SkRegion_set(reskia_region_t *region, const reskia_region_t *src); // (SkRegion *region, const SkRegion *src) -> bool. region/src are required.
void SkRegion_swap(reskia_region_t *region, reskia_region_t *other); // (SkRegion *region, SkRegion *other). NULL input is no-op.
bool SkRegion_isEmpty(reskia_region_t *region); // (SkRegion *region) -> bool. NULL region is treated as empty.
bool SkRegion_isRect(reskia_region_t *region); // (SkRegion *region) -> bool. NULL region returns false.
bool SkRegion_isComplex(reskia_region_t *region); // (SkRegion *region) -> bool. NULL region returns false.
const reskia_i_rect_t *SkRegion_getBounds(reskia_region_t *region); // (SkRegion *region) -> const SkIRect *. Borrowed pointer; NULL region returns NULL.
int SkRegion_computeRegionComplexity(reskia_region_t *region); // (SkRegion *region) -> int. NULL region returns 0.
bool SkRegion_getBoundaryPath(reskia_region_t *region, reskia_path_t *path); // (SkRegion *region, SkPath *path) -> bool. region/path are required.
bool SkRegion_setEmpty(reskia_region_t *region); // (SkRegion *region) -> bool. NULL region returns false.
bool SkRegion_setRect(reskia_region_t *region, const reskia_i_rect_t *rect); // (SkRegion *region, const SkIRect *rect) -> bool. region/rect are required.
bool SkRegion_setRects(reskia_region_t *region, const reskia_i_rect_t *rects, int count); // (SkRegion *region, const SkIRect rects[], int count) -> bool. count > 0 requires rects; negative count returns false.
bool SkRegion_setRegion(reskia_region_t *region, const reskia_region_t *region_2); // (SkRegion *region, const SkRegion *region_2) -> bool. inputs are required.
bool SkRegion_setPath(reskia_region_t *region, const reskia_path_t *path, const reskia_region_t *clip); // (SkRegion *region, const SkPath *path, const SkRegion *clip) -> bool. inputs are required.
bool SkRegion_intersects(reskia_region_t *region, const reskia_i_rect_t *rect); // (SkRegion *region, const SkIRect *rect) -> bool. inputs are required.
bool SkRegion_intersectsRegion(reskia_region_t *region, const reskia_region_t *other); // (SkRegion *region, const SkRegion *other) -> bool. inputs are required.
bool SkRegion_contains(reskia_region_t *region, int x, int y); // (SkRegion *region, int32_t x, int32_t y) -> bool. NULL region returns false.
bool SkRegion_containsIRect(reskia_region_t *region, const reskia_i_rect_t *other); // (SkRegion *region, const SkIRect *other) -> bool. inputs are required.
bool SkRegion_containsRegion(reskia_region_t *region, const reskia_region_t *other); // (SkRegion *region, const SkRegion *other) -> bool. inputs are required.
bool SkRegion_quickContains(reskia_region_t *region, const reskia_i_rect_t *r); // (SkRegion *region, const SkIRect *r) -> bool. inputs are required.
bool SkRegion_quickReject(reskia_region_t *region, const reskia_i_rect_t *rect); // (SkRegion *region, const SkIRect *rect) -> bool. inputs are required.
bool SkRegion_quickRejectRegion(reskia_region_t *region, const reskia_region_t *rgn); // (SkRegion *region, const SkRegion *rgn) -> bool. inputs are required.
void SkRegion_translate(reskia_region_t *region, int dx, int dy); // (SkRegion *region, int dx, int dy). NULL region is no-op.
/**
 * (SkRegion *region, int dx, int dy, SkRegion *dst). region/dst are required.
 */
void SkRegion_translateToRegion(reskia_region_t *region, int dx, int dy, reskia_region_t *dst);
bool SkRegion_op(reskia_region_t *region, const reskia_i_rect_t *rect, reskia_region_op_t op); // (SkRegion *region, const SkIRect *rect, SkRegion::Op op) -> bool. inputs and valid op are required.
bool SkRegion_opWithRegion(reskia_region_t *region, const reskia_region_t *rgn, reskia_region_op_t op); // (SkRegion *region, const SkRegion *rgn, SkRegion::Op op) -> bool. inputs and valid op are required.
bool SkRegion_opWithIRectAndRegion(reskia_region_t *region, const reskia_i_rect_t *rect, const reskia_region_t *rgn, reskia_region_op_t op); // (SkRegion *region, const SkIRect *rect, const SkRegion *rgn, SkRegion::Op op) -> bool. inputs and valid op are required.
bool SkRegion_opWithRegionAndIRect(reskia_region_t *region, const reskia_region_t *rgn, const reskia_i_rect_t *rect, reskia_region_op_t op); // (SkRegion *region, const SkRegion *rgn, const SkIRect *rect, SkRegion::Op op) -> bool. inputs and valid op are required.
bool SkRegion_op_5(reskia_region_t *region, const reskia_region_t *rgna, const reskia_region_t *rgnb, reskia_region_op_t op); // (SkRegion *region, const SkRegion *rgna, const SkRegion *rgnb, SkRegion::Op op) -> bool. inputs and valid op are required.
size_t SkRegion_writeToMemory(reskia_region_t *region, void *buffer); // (SkRegion *region, void *buffer) -> size_t. buffer may be NULL for size query; NULL region returns 0.
size_t SkRegion_readFromMemory(reskia_region_t *region, const void *buffer, size_t length); // (SkRegion *region, const void *buffer, size_t length) -> size_t. region/buffer are required.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_REGION_H
