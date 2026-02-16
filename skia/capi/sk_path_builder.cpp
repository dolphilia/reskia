//
// Created by dolphilia on 2024/01/09.
//

#include "sk_path_builder.h"

#include "include/core/SkPathBuilder.h"

#include "../handles/static_sk_rect.h"
#include "../handles/static_sk_path.h"
#include "../handles/static_sk_point.h"

#include "../handles/static_sk_path-internal.h"
#include "../handles/static_sk_point-internal.h"
#include "../handles/static_sk_rect-internal.h"

extern "C" {

// SkPathBuilder & operator=(const SkPath &)
// SkPathBuilder & operator=(const SkPathBuilder &)

reskia_path_builder_t *SkPathBuilder_new() {
    return reinterpret_cast<reskia_path_builder_t *>(new SkPathBuilder());
}

reskia_path_builder_t *SkPathBuilder_new_2(int type) {
    return reinterpret_cast<reskia_path_builder_t *>(new SkPathBuilder(static_cast<SkPathFillType>(type)));
}

reskia_path_builder_t *SkPathBuilder_new_3(const reskia_path_t *path) {
    return reinterpret_cast<reskia_path_builder_t *>(new SkPathBuilder(* reinterpret_cast<const SkPath *>(path)));
}

reskia_path_builder_t *SkPathBuilder_new_4(const reskia_path_builder_t *builder) {
    return reinterpret_cast<reskia_path_builder_t *>(new SkPathBuilder(* reinterpret_cast<const SkPathBuilder *>(builder)));
}

void SkPathBuilder_delete(reskia_path_builder_t *path_builder) {
    delete reinterpret_cast<SkPathBuilder *>(path_builder);
}

reskia_path_builder_fill_type_t SkPathBuilder_fillType(reskia_path_builder_t *path_builder) {
    return static_cast<reskia_path_builder_fill_type_t>(reinterpret_cast<SkPathBuilder *>(path_builder)->fillType());
}

sk_rect_t SkPathBuilder_computeBounds(reskia_path_builder_t *path_builder) {
    return static_sk_rect_make(reinterpret_cast<SkPathBuilder *>(path_builder)->computeBounds());
}

sk_path_t SkPathBuilder_snapshot(reskia_path_builder_t *path_builder) {
    return static_sk_path_make(reinterpret_cast<SkPathBuilder *>(path_builder)->snapshot());
}

sk_path_t SkPathBuilder_detach(reskia_path_builder_t *path_builder) {
    return static_sk_path_make(reinterpret_cast<SkPathBuilder *>(path_builder)->detach());
}

reskia_path_builder_t *SkPathBuilder_setFillType(reskia_path_builder_t *path_builder, int ft) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->setFillType(static_cast<SkPathFillType>(ft)));
}

reskia_path_builder_t *SkPathBuilder_setIsVolatile(reskia_path_builder_t *path_builder, bool isVolatile) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->setIsVolatile(isVolatile));
}

reskia_path_builder_t *SkPathBuilder_reset(reskia_path_builder_t *path_builder) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->reset());
}

reskia_path_builder_t *SkPathBuilder_moveTo(reskia_path_builder_t *path_builder, sk_point_t pt) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->moveTo(static_sk_point_get_entity(pt)));
}

reskia_path_builder_t *SkPathBuilder_moveTo_2(reskia_path_builder_t *path_builder, float x, float y) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->moveTo(x, y));
}

reskia_path_builder_t *SkPathBuilder_lineTo(reskia_path_builder_t *path_builder, sk_point_t pt) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->lineTo(static_sk_point_get_entity(pt)));
}

reskia_path_builder_t *SkPathBuilder_lineTo_2(reskia_path_builder_t *path_builder, float x, float y) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->lineTo(x, y));
}

reskia_path_builder_t *SkPathBuilder_quadTo(reskia_path_builder_t *path_builder, sk_point_t pt1, sk_point_t pt2) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->quadTo(static_sk_point_get_entity(pt1), static_sk_point_get_entity(pt2)));
}

reskia_path_builder_t *SkPathBuilder_quadTo_2(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->quadTo(x1, y1, x2, y2));
}

reskia_path_builder_t *SkPathBuilder_quadTo_3(reskia_path_builder_t *path_builder, const reskia_point_t *pts) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->quadTo(reinterpret_cast<const SkPoint *>(pts)));
}

reskia_path_builder_t *SkPathBuilder_conicTo(reskia_path_builder_t *path_builder, sk_point_t pt1, sk_point_t pt2, float w) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->conicTo(static_sk_point_get_entity(pt1), static_sk_point_get_entity(pt2), w));
}

reskia_path_builder_t *SkPathBuilder_conicTo_2(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2, float w) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->conicTo(x1, y1, x2, y2, w));
}

reskia_path_builder_t *SkPathBuilder_conicTo_3(reskia_path_builder_t *path_builder, const reskia_point_t *pts, float w) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->conicTo(reinterpret_cast<const SkPoint *>(pts), w));
}

reskia_path_builder_t *SkPathBuilder_cubicTo(reskia_path_builder_t *path_builder, sk_point_t pt1, sk_point_t pt2, sk_point_t pt3) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->cubicTo(static_sk_point_get_entity(pt1), static_sk_point_get_entity(pt2), static_sk_point_get_entity(pt3)));
}

reskia_path_builder_t *SkPathBuilder_cubicTo_2(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2, float x3, float y3) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->cubicTo(x1, y1, x2, y2, x3, y3));
}

reskia_path_builder_t *SkPathBuilder_cubicTo_3(reskia_path_builder_t *path_builder, const reskia_point_t *pts) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->cubicTo(reinterpret_cast<const SkPoint *>(pts)));
}

reskia_path_builder_t *SkPathBuilder_close(reskia_path_builder_t *path_builder) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->close());
}

reskia_path_builder_t *SkPathBuilder_polylineTo(reskia_path_builder_t *path_builder, const reskia_point_t *pts, int count) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->polylineTo(reinterpret_cast<const SkPoint *>(pts), count));
}

reskia_path_builder_t *SkPathBuilder_polylineTo_2(reskia_path_builder_t *path_builder, const void *list) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->polylineTo(* reinterpret_cast<const std::initializer_list<SkPoint> *>(list)));
}

reskia_path_builder_t *SkPathBuilder_rLineTo(reskia_path_builder_t *path_builder, sk_point_t pt) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->rLineTo(static_sk_point_get_entity(pt)));
}

reskia_path_builder_t *SkPathBuilder_rLineTo_2(reskia_path_builder_t *path_builder, float x, float y) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->rLineTo(x, y));
}

reskia_path_builder_t *SkPathBuilder_rQuadTo(reskia_path_builder_t *path_builder, sk_point_t pt1, sk_point_t pt2) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->rQuadTo(static_sk_point_get_entity(pt1), static_sk_point_get_entity(pt2)));
}

reskia_path_builder_t *SkPathBuilder_rQuadTo_2(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->rQuadTo(x1, y1, x2, y2));
}

reskia_path_builder_t *SkPathBuilder_rConicTo(reskia_path_builder_t *path_builder, sk_point_t p1, sk_point_t p2, float w) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->rConicTo(static_sk_point_get_entity(p1), static_sk_point_get_entity(p2), w));
}

reskia_path_builder_t *SkPathBuilder_rConicTo_2(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2, float w) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->rConicTo(x1, y1, x2, y2, w));
}

reskia_path_builder_t *SkPathBuilder_rCubicTo(reskia_path_builder_t *path_builder, sk_point_t pt1, sk_point_t pt2, sk_point_t pt3) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->rCubicTo(static_sk_point_get_entity(pt1), static_sk_point_get_entity(pt2), static_sk_point_get_entity(pt3)));
}

reskia_path_builder_t *SkPathBuilder_rCubicTo_2(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2, float x3, float y3) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->rCubicTo(x1, y1, x2, y2, x3, y3));
}

reskia_path_builder_t *SkPathBuilder_arcTo(reskia_path_builder_t *path_builder, const reskia_rect_t *oval, float startAngleDeg, float sweepAngleDeg, bool forceMoveTo) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->arcTo(* reinterpret_cast<const SkRect *>(oval), startAngleDeg, sweepAngleDeg, forceMoveTo));
}

reskia_path_builder_t *SkPathBuilder_arcTo_2(reskia_path_builder_t *path_builder, sk_point_t p1, sk_point_t p2, float radius) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->arcTo(static_sk_point_get_entity(p1), static_sk_point_get_entity(p2), radius));
}

reskia_path_builder_t *SkPathBuilder_arcTo_3(reskia_path_builder_t *path_builder, sk_point_t r, float xAxisRotate, int largeArc, int sweep, sk_point_t xy) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->arcTo(static_sk_point_get_entity(r), xAxisRotate, static_cast<SkPathBuilder::ArcSize>(largeArc), static_cast<SkPathDirection>(sweep), static_sk_point_get_entity(xy)));
}

reskia_path_builder_t *SkPathBuilder_addArc(reskia_path_builder_t *path_builder, const reskia_rect_t *oval, float startAngleDeg, float sweepAngleDeg) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->addArc(* reinterpret_cast<const SkRect *>(oval), startAngleDeg, sweepAngleDeg));
}

reskia_path_builder_t *SkPathBuilder_addRect(reskia_path_builder_t *path_builder, const reskia_rect_t *rect, int dir, unsigned startIndex) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->addRect(* reinterpret_cast<const SkRect *>(rect), static_cast<SkPathDirection>(dir), startIndex));
}

reskia_path_builder_t *SkPathBuilder_addRect_2(reskia_path_builder_t *path_builder, const reskia_rect_t *rect, int dir) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->addRect(* reinterpret_cast<const SkRect *>(rect), (SkPathDirection)dir));
}

reskia_path_builder_t *SkPathBuilder_addOval(reskia_path_builder_t *path_builder, const reskia_rect_t *rect, int dir, unsigned startIndex) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->addOval(* reinterpret_cast<const SkRect *>(rect), (SkPathDirection)dir, startIndex));
}

reskia_path_builder_t *SkPathBuilder_addOval_2(reskia_path_builder_t *path_builder, const reskia_rect_t *rect, int dir) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->addOval(* reinterpret_cast<const SkRect *>(rect), (SkPathDirection)dir));
}

reskia_path_builder_t *SkPathBuilder_addRRect(reskia_path_builder_t *path_builder, const reskia_r_rect_t *rect, int dir, unsigned startIndex) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->addRRect(* reinterpret_cast<const SkRRect *>(rect), (SkPathDirection)dir, startIndex));
}

reskia_path_builder_t *SkPathBuilder_addRRect_2(reskia_path_builder_t *path_builder, const reskia_r_rect_t *rrect, int dir) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->addRRect(* reinterpret_cast<const SkRRect *>(rrect), (SkPathDirection)dir));
}

reskia_path_builder_t *SkPathBuilder_addCircle(reskia_path_builder_t *path_builder, float center_x, float center_y, float radius, int dir) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->addCircle(center_x, center_y, radius, (SkPathDirection)dir));
}

reskia_path_builder_t *SkPathBuilder_addPolygon(reskia_path_builder_t *path_builder, const reskia_point_t *pts, int count, bool isClosed) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->addPolygon(reinterpret_cast<const SkPoint *>(pts), count, isClosed));
}

reskia_path_builder_t *SkPathBuilder_addPolygon_2(reskia_path_builder_t *path_builder, const void *list, bool isClosed) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->addPolygon(* reinterpret_cast<const std::initializer_list<SkPoint> *>(list), isClosed));
}

reskia_path_builder_t *SkPathBuilder_addPath(reskia_path_builder_t *path_builder, const reskia_path_t *path) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->addPath(* reinterpret_cast<const SkPath *>(path)));
}

void SkPathBuilder_incReserve(reskia_path_builder_t *path_builder, int extraPtCount, int extraVerbCount) {
    reinterpret_cast<SkPathBuilder *>(path_builder)->incReserve(extraPtCount, extraVerbCount);
}

void SkPathBuilder_incReserve_2(reskia_path_builder_t *path_builder, int extraPtCount) {
    reinterpret_cast<SkPathBuilder *>(path_builder)->incReserve(extraPtCount);
}

reskia_path_builder_t *SkPathBuilder_offset(reskia_path_builder_t *path_builder, float dx, float dy) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->offset(dx, dy));
}

reskia_path_builder_t *SkPathBuilder_toggleInverseFillType(reskia_path_builder_t *path_builder) {
    return reinterpret_cast<reskia_path_builder_t *>(&reinterpret_cast<SkPathBuilder *>(path_builder)->toggleInverseFillType());
}

}
