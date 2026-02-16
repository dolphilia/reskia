//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_PATH_BUILDER_H
#define RAIA_SKIA_SK_PATH_BUILDER_H

#include <stdint.h>

#include "../handles/static_sk_path.h"
#include "../handles/static_sk_rect.h"

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
reskia_path_builder_t *SkPathBuilder_newFromPath(const reskia_path_t *path); // (const SkPath *path) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_newCopy(const reskia_path_builder_t *builder); // (const SkPathBuilder *builder) -> SkPathBuilder *
void SkPathBuilder_delete(reskia_path_builder_t *path_builder); // (SkPathBuilder *path_builder)
reskia_path_builder_fill_type_t SkPathBuilder_fillType(reskia_path_builder_t *path_builder); // (SkPathBuilder *path_builder) -> SkPathFillType
sk_rect_t SkPathBuilder_computeBounds(reskia_path_builder_t *path_builder); // (SkPathBuilder *path_builder) -> sk_rect_t
sk_path_t SkPathBuilder_snapshot(reskia_path_builder_t *path_builder); // (SkPathBuilder *path_builder) -> sk_path_t
sk_path_t SkPathBuilder_detach(reskia_path_builder_t *path_builder); // (SkPathBuilder *path_builder) -> sk_path_t
reskia_path_builder_t *SkPathBuilder_setFillType(reskia_path_builder_t *path_builder, int ft); // (SkPathBuilder *path_builder, SkPathFillType ft) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_setIsVolatile(reskia_path_builder_t *path_builder, bool isVolatile); // (SkPathBuilder *path_builder, bool isVolatile) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_reset(reskia_path_builder_t *path_builder); // (SkPathBuilder *path_builder) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_moveTo(reskia_path_builder_t *path_builder, int pt); // (SkPathBuilder *path_builder, sk_point_t pt) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_moveToPoint(reskia_path_builder_t *path_builder, float x, float y); // (SkPathBuilder *path_builder, SkScalar x, SkScalar y) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_lineTo(reskia_path_builder_t *path_builder, int pt); // (SkPathBuilder *path_builder, sk_point_t pt) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_lineToPoint(reskia_path_builder_t *path_builder, float x, float y); // (SkPathBuilder *path_builder, SkScalar x, SkScalar y) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_quadTo(reskia_path_builder_t *path_builder, int pt1, int pt2); // (SkPathBuilder *path_builder, sk_point_t pt1, sk_point_t pt2) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_quadToCoordinates(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2); // (SkPathBuilder *path_builder, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_quadToPointArray(reskia_path_builder_t *path_builder, const reskia_point_t *pts); // (SkPathBuilder *path_builder, const SkPoint pts[2]) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_conicTo(reskia_path_builder_t *path_builder, int pt1, int pt2, float w); // (SkPathBuilder *path_builder, sk_point_t pt1, sk_point_t pt2, SkScalar w) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_conicToCoordinates(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2, float w); // (SkPathBuilder *path_builder, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2, SkScalar w) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_conicToPointArray(reskia_path_builder_t *path_builder, const reskia_point_t *pts, float w); // (SkPathBuilder *path_builder, const SkPoint pts[2], SkScalar w) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_cubicTo(reskia_path_builder_t *path_builder, int pt1, int pt2, int pt3); // (SkPathBuilder *path_builder, sk_point_t pt1, sk_point_t pt2, sk_point_t pt3) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_cubicToCoordinates(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2, float x3, float y3); // (SkPathBuilder *path_builder, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2, SkScalar x3, SkScalar y3) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_cubicToPointArray(reskia_path_builder_t *path_builder, const reskia_point_t *pts); // (SkPathBuilder *path_builder, const SkPoint pts[3]) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_close(reskia_path_builder_t *path_builder); // (SkPathBuilder *path_builder) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_polylineTo(reskia_path_builder_t *path_builder, const reskia_point_t *pts, int count); // (SkPathBuilder *path_builder, const SkPoint pts[], int count) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_polylineToFromList(reskia_path_builder_t *path_builder, const void *list); // (SkPathBuilder *path_builder, const std::initializer_list<SkPoint> *list) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_rLineTo(reskia_path_builder_t *path_builder, int pt); // (SkPathBuilder *path_builder, sk_point_t pt) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_rLineToPoint(reskia_path_builder_t *path_builder, float x, float y); // (SkPathBuilder *path_builder, SkScalar x, SkScalar y) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_rQuadTo(reskia_path_builder_t *path_builder, int pt1, int pt2); // (SkPathBuilder *path_builder, sk_point_t pt1, sk_point_t pt2) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_rQuadToCoordinates(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2); // (SkPathBuilder *path_builder, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_rConicTo(reskia_path_builder_t *path_builder, int p1, int p2, float w); // (SkPathBuilder *path_builder, sk_point_t p1, sk_point_t p2, SkScalar w) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_rConicToCoordinates(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2, float w); // (SkPathBuilder *path_builder, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2, SkScalar w) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_rCubicTo(reskia_path_builder_t *path_builder, int pt1, int pt2, int pt3); // (SkPathBuilder *path_builder, sk_point_t pt1, sk_point_t pt2, sk_point_t pt3) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_rCubicToCoordinates(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2, float x3, float y3); // (SkPathBuilder *path_builder, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2, SkScalar x3, SkScalar y3) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_arcTo(reskia_path_builder_t *path_builder, const reskia_rect_t *oval, float startAngleDeg, float sweepAngleDeg, bool forceMoveTo); // (SkPathBuilder *path_builder, const SkRect *oval, SkScalar startAngleDeg, SkScalar sweepAngleDeg, bool forceMoveTo) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_arcToTangentPoints(reskia_path_builder_t *path_builder, int p1, int p2, float radius); // (SkPathBuilder *path_builder, sk_point_t p1, sk_point_t p2, SkScalar radius) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_arcToArcSizeAndDirection(reskia_path_builder_t *path_builder, int r, float xAxisRotate, int largeArc, int sweep, int xy); // (SkPathBuilder *path_builder, sk_point_t r, SkScalar xAxisRotate, SkPathBuilder::ArcSize largeArc, SkPathDirection sweep, sk_point_t xy) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_addArc(reskia_path_builder_t *path_builder, const reskia_rect_t *oval, float startAngleDeg, float sweepAngleDeg); // (SkPathBuilder *path_builder, const SkRect *oval, SkScalar startAngleDeg, SkScalar sweepAngleDeg) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_addRect(reskia_path_builder_t *path_builder, const reskia_rect_t *rect, int dir, unsigned startIndex); // (SkPathBuilder *path_builder, const SkRect *rect, SkPathDirection dir, unsigned startIndex) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_addRectWithDirection(reskia_path_builder_t *path_builder, const reskia_rect_t *rect, int dir); // (SkPathBuilder *path_builder, const SkRect *rect, SkPathDirection dir) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_addOval(reskia_path_builder_t *path_builder, const reskia_rect_t *rect, int dir, unsigned startIndex); // (SkPathBuilder *path_builder, const SkRect *rect, SkPathDirection dir, unsigned startIndex) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_addOvalWithDirection(reskia_path_builder_t *path_builder, const reskia_rect_t *rect, int dir); // (SkPathBuilder *path_builder, const SkRect *rect, SkPathDirection dir) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_addRRect(reskia_path_builder_t *path_builder, const reskia_r_rect_t *rect, int dir, unsigned startIndex); // (SkPathBuilder *path_builder, const SkRRect *rect, SkPathDirection dir, unsigned startIndex) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_addRRectWithDirection(reskia_path_builder_t *path_builder, const reskia_r_rect_t *rrect, int dir); // (SkPathBuilder *path_builder, const SkRRect *rrect, SkPathDirection dir) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_addCircle(reskia_path_builder_t *path_builder, float center_x, float center_y, float radius, int dir); // (SkPathBuilder *path_builder, SkScalar center_x, SkScalar center_y, SkScalar radius, SkPathDirection dir) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_addPolygon(reskia_path_builder_t *path_builder, const reskia_point_t *pts, int count, bool isClosed); // (SkPathBuilder *path_builder, const SkPoint pts[], int count, bool isClosed) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_addPolygonFromList(reskia_path_builder_t *path_builder, const void *list, bool isClosed); // (SkPathBuilder *path_builder, const std::initializer_list<SkPoint> *list, bool isClosed) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_addPath(reskia_path_builder_t *path_builder, const reskia_path_t *path); // (SkPathBuilder *path_builder, const SkPath *path) -> SkPathBuilder *
void SkPathBuilder_incReserve(reskia_path_builder_t *path_builder, int extraPtCount, int extraVerbCount); // (SkPathBuilder *path_builder, int extraPtCount, int extraVerbCount)
void SkPathBuilder_incReservePoints(reskia_path_builder_t *path_builder, int extraPtCount); // (SkPathBuilder *path_builder, int extraPtCount)
reskia_path_builder_t *SkPathBuilder_offset(reskia_path_builder_t *path_builder, float dx, float dy); // (SkPathBuilder *path_builder, SkScalar dx, SkScalar dy) -> SkPathBuilder *
reskia_path_builder_t *SkPathBuilder_toggleInverseFillType(reskia_path_builder_t *path_builder); // (SkPathBuilder *path_builder) -> SkPathBuilder *

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PATH_BUILDER_H
