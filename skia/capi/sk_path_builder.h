//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_PATH_BUILDER_H
#define RAIA_SKIA_SK_PATH_BUILDER_H

#include <stddef.h>
#include <stdint.h>

#include "../handles/static_sk_path.h"
#include "../handles/static_sk_point.h"
#include "../handles/static_sk_rect.h"

typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_path_iter_t reskia_path_iter_t;
typedef struct reskia_path_builder_t reskia_path_builder_t;
typedef struct reskia_path_t reskia_path_t;
typedef struct reskia_point_t reskia_point_t;
typedef struct reskia_r_rect_t reskia_r_rect_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef int32_t reskia_path_builder_fill_type_t;

#ifdef __cplusplus
extern "C" {
#endif

// SkPathBuilder & operator=(const SkPath &)
// SkPathBuilder & operator=(const SkPathBuilder &)

reskia_path_builder_t *SkPathBuilder_new(); // () -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_newWithFillType(int type); // (SkPathFillType type) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_newFromPath(const reskia_path_t *path); // path は非 NULL。NULL なら NULL (const SkPath *path) -> SkPathBuilder *
/**
 * builder は非 NULL。NULL なら NULL (const SkPathBuilder *builder) -> SkPathBuilder *
 */
reskia_path_builder_t *SkPathBuilder_newCopy(const reskia_path_builder_t *builder);
void SkPathBuilder_delete(reskia_path_builder_t *path_builder); // NULL path_builder は no-op (SkPathBuilder *path_builder)
bool SkPathBuilder_equals(const reskia_path_builder_t *path_builder, const reskia_path_builder_t *other); // NULL input returns false
bool SkPathBuilder_notEquals(const reskia_path_builder_t *path_builder, const reskia_path_builder_t *other); // NULL input returns false
/**
 * NULL path_builder なら 0 (SkPathBuilder *path_builder) -> SkPathFillType
 */
reskia_path_builder_fill_type_t SkPathBuilder_fillType(reskia_path_builder_t *path_builder);
sk_rect_t SkPathBuilder_computeBounds(reskia_path_builder_t *path_builder); // NULL path_builder なら 0 (SkPathBuilder *path_builder) -> sk_rect_t
bool SkPathBuilder_computeFiniteBounds(reskia_path_builder_t *path_builder, reskia_rect_t *out_bounds); // NULL/non-finite returns false
sk_path_t SkPathBuilder_snapshot(reskia_path_builder_t *path_builder); // NULL path_builder なら 0 (SkPathBuilder *path_builder) -> sk_path_t
sk_path_t SkPathBuilder_detach(reskia_path_builder_t *path_builder); // NULL path_builder なら 0 (SkPathBuilder *path_builder) -> sk_path_t
/**
 * NULL path_builder なら NULL (SkPathBuilder *path_builder, SkPathFillType ft) -> SkPathBuilder *
 */
reskia_path_builder_t *SkPathBuilder_setFillType(reskia_path_builder_t *path_builder, int ft);
/**
 * NULL path_builder なら NULL (SkPathBuilder *path_builder, bool isVolatile) -> SkPathBuilder *
 */
reskia_path_builder_t *SkPathBuilder_setIsVolatile(reskia_path_builder_t *path_builder, bool isVolatile);
reskia_path_builder_t *SkPathBuilder_reset(reskia_path_builder_t *path_builder); // NULL path_builder なら NULL (SkPathBuilder *path_builder) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_moveTo(reskia_path_builder_t *path_builder, int pt); // (SkPathBuilder *path_builder, sk_point_t pt) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_moveToPoint(reskia_path_builder_t *path_builder, float x, float y); // (SkPathBuilder *path_builder, SkScalar x, SkScalar y) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_lineTo(reskia_path_builder_t *path_builder, int pt); // (SkPathBuilder *path_builder, sk_point_t pt) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_lineToPoint(reskia_path_builder_t *path_builder, float x, float y); // (SkPathBuilder *path_builder, SkScalar x, SkScalar y) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_addLine(reskia_path_builder_t *path_builder, int a, int b); // (SkPathBuilder *path_builder, SkPoint a, SkPoint b) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_addLinePoints(reskia_path_builder_t *path_builder, float ax, float ay, float bx, float by); // (SkPathBuilder *path_builder, SkScalar ax, SkScalar ay, SkScalar bx, SkScalar by) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_quadTo(reskia_path_builder_t *path_builder, int pt1, int pt2); // (SkPathBuilder *path_builder, sk_point_t pt1, sk_point_t pt2) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_quadToCoordinates(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2); // (SkPathBuilder *path_builder, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2) -> SkPathBuilder *
/**
 * pts は非 NULL。NULL pts は no-op、NULL path_builder なら NULL (SkPathBuilder *path_builder, const SkPoint pts[2]) -> SkPathBuilder *
 */
reskia_path_builder_t *SkPathBuilder_quadToPointArray(reskia_path_builder_t *path_builder, const reskia_point_t *pts);
reskia_path_builder_t *SkPathBuilder_conicTo(reskia_path_builder_t *path_builder, int pt1, int pt2, float w); // (SkPathBuilder *path_builder, sk_point_t pt1, sk_point_t pt2, SkScalar w) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_conicToCoordinates(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2, float w); // (SkPathBuilder *path_builder, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2, SkScalar w) -> SkPathBuilder *
/**
 * pts は非 NULL。NULL pts は no-op、NULL path_builder なら NULL (SkPathBuilder *path_builder, const SkPoint pts[2], SkScalar w) -> SkPathBuilder *
 */
reskia_path_builder_t *SkPathBuilder_conicToPointArray(reskia_path_builder_t *path_builder, const reskia_point_t *pts, float w);
reskia_path_builder_t *SkPathBuilder_cubicTo(reskia_path_builder_t *path_builder, int pt1, int pt2, int pt3); // (SkPathBuilder *path_builder, sk_point_t pt1, sk_point_t pt2, sk_point_t pt3) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_cubicToCoordinates(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2, float x3, float y3); // (SkPathBuilder *path_builder, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2, SkScalar x3, SkScalar y3) -> SkPathBuilder *
/**
 * pts は非 NULL。NULL pts は no-op、NULL path_builder なら NULL (SkPathBuilder *path_builder, const SkPoint pts[3]) -> SkPathBuilder *
 */
reskia_path_builder_t *SkPathBuilder_cubicToPointArray(reskia_path_builder_t *path_builder, const reskia_point_t *pts);
reskia_path_builder_t *SkPathBuilder_close(reskia_path_builder_t *path_builder); // (SkPathBuilder *path_builder) -> SkPathBuilder *
/**
 * pts は非 NULL かつ count > 0。invalid 入力は no-op、NULL path_builder なら NULL (SkPathBuilder *path_builder, const SkPoint pts[], int count) -> SkPathBuilder *
 */
reskia_path_builder_t *SkPathBuilder_polylineTo(reskia_path_builder_t *path_builder, const reskia_point_t *pts, int count);
/**
 * list は非 NULL。NULL list は no-op、NULL path_builder なら NULL (SkPathBuilder *path_builder, const std::initializer_list<SkPoint> *list) -> SkPathBuilder *
 */
reskia_path_builder_t *SkPathBuilder_polylineToFromList(reskia_path_builder_t *path_builder, const void *list);
reskia_path_builder_t *SkPathBuilder_rLineTo(reskia_path_builder_t *path_builder, int pt); // (SkPathBuilder *path_builder, sk_point_t pt) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_rLineToPoint(reskia_path_builder_t *path_builder, float x, float y); // (SkPathBuilder *path_builder, SkScalar x, SkScalar y) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_rQuadTo(reskia_path_builder_t *path_builder, int pt1, int pt2); // (SkPathBuilder *path_builder, sk_point_t pt1, sk_point_t pt2) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_rQuadToCoordinates(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2); // (SkPathBuilder *path_builder, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_rConicTo(reskia_path_builder_t *path_builder, int p1, int p2, float w); // (SkPathBuilder *path_builder, sk_point_t p1, sk_point_t p2, SkScalar w) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_rConicToCoordinates(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2, float w); // (SkPathBuilder *path_builder, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2, SkScalar w) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_rCubicTo(reskia_path_builder_t *path_builder, int pt1, int pt2, int pt3); // (SkPathBuilder *path_builder, sk_point_t pt1, sk_point_t pt2, sk_point_t pt3) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_rCubicToCoordinates(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2, float x3, float y3); // (SkPathBuilder *path_builder, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2, SkScalar x3, SkScalar y3) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_rArcTo(reskia_path_builder_t *path_builder, float rx, float ry, float xAxisRotate, int largeArc, int sweep, float dx, float dy); // (SkPathBuilder *path_builder, SkScalar rx, SkScalar ry, SkScalar xAxisRotate, ArcSize largeArc, SkPathDirection sweep, SkScalar dx, SkScalar dy) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_rMoveTo(reskia_path_builder_t *path_builder, sk_point_t pt); // NULL path_builder returns NULL
/**
 * oval は非 NULL。NULL oval は no-op、NULL path_builder なら NULL (SkPathBuilder *path_builder, const SkRect *oval, SkScalar startAngleDeg, SkScalar sweepAngleDeg, bool forceMoveTo) -> SkPathBuilder *
 */
reskia_path_builder_t *SkPathBuilder_arcTo(reskia_path_builder_t *path_builder, const reskia_rect_t *oval, float startAngleDeg, float sweepAngleDeg, bool forceMoveTo);
reskia_path_builder_t *SkPathBuilder_arcToTangentPoints(reskia_path_builder_t *path_builder, int p1, int p2, float radius); // (SkPathBuilder *path_builder, sk_point_t p1, sk_point_t p2, SkScalar radius) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_arcToArcSizeAndDirection(reskia_path_builder_t *path_builder, int r, float xAxisRotate, int largeArc, int sweep, int xy); // (SkPathBuilder *path_builder, sk_point_t r, SkScalar xAxisRotate, SkPathBuilder::ArcSize largeArc, SkPathDirection sweep, sk_point_t xy) -> SkPathBuilder *
/**
 * oval は非 NULL。NULL oval は no-op、NULL path_builder なら NULL (SkPathBuilder *path_builder, const SkRect *oval, SkScalar startAngleDeg, SkScalar sweepAngleDeg) -> SkPathBuilder *
 */
reskia_path_builder_t *SkPathBuilder_addArc(reskia_path_builder_t *path_builder, const reskia_rect_t *oval, float startAngleDeg, float sweepAngleDeg);
/**
 * rect は非 NULL。NULL rect は no-op、NULL path_builder なら NULL (SkPathBuilder *path_builder, const SkRect *rect, SkPathDirection dir, unsigned startIndex) -> SkPathBuilder *
 */
reskia_path_builder_t *SkPathBuilder_addRect(reskia_path_builder_t *path_builder, const reskia_rect_t *rect, int dir, unsigned startIndex);
/**
 * rect は非 NULL。NULL rect は no-op、NULL path_builder なら NULL (SkPathBuilder *path_builder, const SkRect *rect, SkPathDirection dir) -> SkPathBuilder *
 */
reskia_path_builder_t *SkPathBuilder_addRectWithDirection(reskia_path_builder_t *path_builder, const reskia_rect_t *rect, int dir);
/**
 * rect は非 NULL。NULL rect は no-op、NULL path_builder なら NULL (SkPathBuilder *path_builder, const SkRect *rect, SkPathDirection dir, unsigned startIndex) -> SkPathBuilder *
 */
reskia_path_builder_t *SkPathBuilder_addOval(reskia_path_builder_t *path_builder, const reskia_rect_t *rect, int dir, unsigned startIndex);
/**
 * rect は非 NULL。NULL rect は no-op、NULL path_builder なら NULL (SkPathBuilder *path_builder, const SkRect *rect, SkPathDirection dir) -> SkPathBuilder *
 */
reskia_path_builder_t *SkPathBuilder_addOvalWithDirection(reskia_path_builder_t *path_builder, const reskia_rect_t *rect, int dir);
/**
 * rect は非 NULL。NULL rect は no-op、NULL path_builder なら NULL (SkPathBuilder *path_builder, const SkRRect *rect, SkPathDirection dir, unsigned startIndex) -> SkPathBuilder *
 */
reskia_path_builder_t *SkPathBuilder_addRRect(reskia_path_builder_t *path_builder, const reskia_r_rect_t *rect, int dir, unsigned startIndex);
/**
 * rrect は非 NULL。NULL rrect は no-op、NULL path_builder なら NULL (SkPathBuilder *path_builder, const SkRRect *rrect, SkPathDirection dir) -> SkPathBuilder *
 */
reskia_path_builder_t *SkPathBuilder_addRRectWithDirection(reskia_path_builder_t *path_builder, const reskia_r_rect_t *rrect, int dir);
reskia_path_builder_t *SkPathBuilder_addCircle(reskia_path_builder_t *path_builder, float center_x, float center_y, float radius, int dir); // (SkPathBuilder *path_builder, SkScalar center_x, SkScalar center_y, SkScalar radius, SkPathDirection dir) -> SkPathBuilder *
/**
 * pts は非 NULL かつ count > 0。invalid 入力は no-op、NULL path_builder なら NULL (SkPathBuilder *path_builder, const SkPoint pts[], int count, bool isClosed) -> SkPathBuilder *
 */
reskia_path_builder_t *SkPathBuilder_addPolygon(reskia_path_builder_t *path_builder, const reskia_point_t *pts, int count, bool isClosed);
/**
 * list は非 NULL。NULL list は no-op、NULL path_builder なら NULL (SkPathBuilder *path_builder, const std::initializer_list<SkPoint> *list, bool isClosed) -> SkPathBuilder *
 */
reskia_path_builder_t *SkPathBuilder_addPolygonFromList(reskia_path_builder_t *path_builder, const void *list, bool isClosed);
/**
 * path は非 NULL。NULL path は no-op、NULL path_builder なら NULL (SkPathBuilder *path_builder, const SkPath *path) -> SkPathBuilder *
 */
reskia_path_builder_t *SkPathBuilder_addPath(reskia_path_builder_t *path_builder, const reskia_path_t *path);
reskia_path_builder_t *SkPathBuilder_addRaw(reskia_path_builder_t *path_builder, const reskia_point_t *points, int pointCount, const uint8_t *verbs, int verbCount, const float *conicWeights, int conicWeightCount); // invalid raw input is no-op
/**
 * NULL path_builder は no-op (SkPathBuilder *path_builder, int extraPtCount, int extraVerbCount)
 */
void SkPathBuilder_incReserve(reskia_path_builder_t *path_builder, int extraPtCount, int extraVerbCount);
void SkPathBuilder_incReserveWithConics(reskia_path_builder_t *path_builder, int extraPtCount, int extraVerbCount, int extraConicCount);
/**
 * NULL path_builder は no-op (SkPathBuilder *path_builder, int extraPtCount)
 */
void SkPathBuilder_incReservePoints(reskia_path_builder_t *path_builder, int extraPtCount);
reskia_path_builder_t *SkPathBuilder_offset(reskia_path_builder_t *path_builder, float dx, float dy); // (SkPathBuilder *path_builder, SkScalar dx, SkScalar dy) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_transform(reskia_path_builder_t *path_builder, const reskia_matrix_t *matrix, int pc); // invalid input returns original builder or NULL
reskia_path_builder_t *SkPathBuilder_toggleInverseFillType(reskia_path_builder_t *path_builder); // (SkPathBuilder *path_builder) -> SkPathBuilder *
bool SkPathBuilder_isEmpty(reskia_path_builder_t *path_builder); // NULL input returns true
bool SkPathBuilder_isFinite(reskia_path_builder_t *path_builder); // NULL input returns true
sk_point_t SkPathBuilder_getLastPt(reskia_path_builder_t *path_builder); // NULL or empty returns 0
void SkPathBuilder_setLastPt(reskia_path_builder_t *path_builder, float x, float y); // NULL input is no-op
int SkPathBuilder_countPoints(reskia_path_builder_t *path_builder); // NULL input returns 0
bool SkPathBuilder_isInverseFillType(reskia_path_builder_t *path_builder); // NULL input returns false
const reskia_point_t *SkPathBuilder_points(const reskia_path_builder_t *path_builder, size_t *count); // borrowed; NULL input returns NULL and count 0
const uint8_t *SkPathBuilder_verbs(const reskia_path_builder_t *path_builder, size_t *count); // borrowed; NULL input returns NULL and count 0
const float *SkPathBuilder_conicWeights(const reskia_path_builder_t *path_builder, size_t *count); // borrowed; NULL input returns NULL and count 0
reskia_path_iter_t *SkPathBuilder_iter(const reskia_path_builder_t *path_builder); // borrowed builder storage; delete iterator with SkPathIter_delete

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PATH_BUILDER_H
