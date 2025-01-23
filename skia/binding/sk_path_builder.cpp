//
// Created by dolphilia on 2024/01/09.
//

#include "sk_path_builder.h"

#include "include/core/SkPathBuilder.h"

#include "../static/static_sk_rect.h"
#include "../static/static_sk_path.h"
#include "../static/static_sk_point.h"

#include "../static/static_sk_path-internal.h"
#include "../static/static_sk_point-internal.h"
#include "../static/static_sk_rect-internal.h"

extern "C" {

// SkPathBuilder & operator=(const SkPath &)
// SkPathBuilder & operator=(const SkPathBuilder &)

void *SkPathBuilder_new() {
    return new SkPathBuilder();
}

void *SkPathBuilder_new_2(int type) {
    return new SkPathBuilder(static_cast<SkPathFillType>(type));
}

void *SkPathBuilder_new_3(const void *path) {
    return new SkPathBuilder(* static_cast<const SkPath *>(path));
}

void *SkPathBuilder_new_4(const void *builder) {
    return new SkPathBuilder(* static_cast<const SkPathBuilder *>(builder));
}

void SkPathBuilder_delete(void *path_builder) {
    delete static_cast<SkPathBuilder *>(path_builder);
}

int SkPathBuilder_fillType(void *path_builder) {
    return static_cast<int>(static_cast<SkPathBuilder *>(path_builder)->fillType());
}

sk_rect_t SkPathBuilder_computeBounds(void *path_builder) {
    return static_sk_rect_make(static_cast<SkPathBuilder *>(path_builder)->computeBounds());
}

sk_path_t SkPathBuilder_snapshot(void *path_builder) {
    return static_sk_path_make(static_cast<SkPathBuilder *>(path_builder)->snapshot());
}

sk_path_t SkPathBuilder_detach(void *path_builder) {
    return static_sk_path_make(static_cast<SkPathBuilder *>(path_builder)->detach());
}

void * SkPathBuilder_setFillType(void *path_builder, int ft) {
    return &static_cast<SkPathBuilder *>(path_builder)->setFillType(static_cast<SkPathFillType>(ft));
}

void * SkPathBuilder_setIsVolatile(void *path_builder, bool isVolatile) {
    return &static_cast<SkPathBuilder *>(path_builder)->setIsVolatile(isVolatile);
}

void * SkPathBuilder_reset(void *path_builder) {
    return &static_cast<SkPathBuilder *>(path_builder)->reset();
}

void * SkPathBuilder_moveTo(void *path_builder, sk_point_t pt) {
    return &static_cast<SkPathBuilder *>(path_builder)->moveTo(static_sk_point_get(pt));
}

void * SkPathBuilder_moveTo_2(void *path_builder, float x, float y) {
    return &static_cast<SkPathBuilder *>(path_builder)->moveTo(x, y);
}

void * SkPathBuilder_lineTo(void *path_builder, sk_point_t pt) {
    return &static_cast<SkPathBuilder *>(path_builder)->lineTo(static_sk_point_get(pt));
}

void * SkPathBuilder_lineTo_2(void *path_builder, float x, float y) {
    return &static_cast<SkPathBuilder *>(path_builder)->lineTo(x, y);
}

void * SkPathBuilder_quadTo(void *path_builder, sk_point_t pt1, sk_point_t pt2) {
    return &static_cast<SkPathBuilder *>(path_builder)->quadTo(static_sk_point_get(pt1), static_sk_point_get(pt2));
}

void * SkPathBuilder_quadTo_2(void *path_builder, float x1, float y1, float x2, float y2) {
    return &static_cast<SkPathBuilder *>(path_builder)->quadTo(x1, y1, x2, y2);
}

void * SkPathBuilder_quadTo_3(void *path_builder, const void * pts) {
    return &static_cast<SkPathBuilder *>(path_builder)->quadTo(static_cast<const SkPoint *>(pts));
}

void * SkPathBuilder_conicTo(void *path_builder, sk_point_t pt1, sk_point_t pt2, float w) {
    return &static_cast<SkPathBuilder *>(path_builder)->conicTo(static_sk_point_get(pt1), static_sk_point_get(pt2), w);
}

void * SkPathBuilder_conicTo_2(void *path_builder, float x1, float y1, float x2, float y2, float w) {
    return &static_cast<SkPathBuilder *>(path_builder)->conicTo(x1, y1, x2, y2, w);
}

void * SkPathBuilder_conicTo_3(void *path_builder, const void * pts, float w) {
    return &static_cast<SkPathBuilder *>(path_builder)->conicTo(static_cast<const SkPoint *>(pts), w);
}

void * SkPathBuilder_cubicTo(void *path_builder, sk_point_t pt1, sk_point_t pt2, sk_point_t pt3) {
    return &static_cast<SkPathBuilder *>(path_builder)->cubicTo(static_sk_point_get(pt1), static_sk_point_get(pt2), static_sk_point_get(pt3));
}

void * SkPathBuilder_cubicTo_2(void *path_builder, float x1, float y1, float x2, float y2, float x3, float y3) {
    return &static_cast<SkPathBuilder *>(path_builder)->cubicTo(x1, y1, x2, y2, x3, y3);
}

void * SkPathBuilder_cubicTo_3(void *path_builder, const void * pts) {
    return &static_cast<SkPathBuilder *>(path_builder)->cubicTo(static_cast<const SkPoint *>(pts));
}

void * SkPathBuilder_close(void *path_builder) {
    return &static_cast<SkPathBuilder *>(path_builder)->close();
}

void * SkPathBuilder_polylineTo(void *path_builder, const void * pts, int count) {
    return &static_cast<SkPathBuilder *>(path_builder)->polylineTo(static_cast<const SkPoint *>(pts), count);
}

void * SkPathBuilder_polylineTo_2(void *path_builder, const void *list) {
    return &static_cast<SkPathBuilder *>(path_builder)->polylineTo(* static_cast<const std::initializer_list<SkPoint> *>(list));
}

void * SkPathBuilder_rLineTo(void *path_builder, sk_point_t pt) {
    return &static_cast<SkPathBuilder *>(path_builder)->rLineTo(static_sk_point_get(pt));
}

void * SkPathBuilder_rLineTo_2(void *path_builder, float x, float y) {
    return &static_cast<SkPathBuilder *>(path_builder)->rLineTo(x, y);
}

void * SkPathBuilder_rQuadTo(void *path_builder, sk_point_t pt1, sk_point_t pt2) {
    return &static_cast<SkPathBuilder *>(path_builder)->rQuadTo(static_sk_point_get(pt1), static_sk_point_get(pt2));
}

void * SkPathBuilder_rQuadTo_2(void *path_builder, float x1, float y1, float x2, float y2) {
    return &static_cast<SkPathBuilder *>(path_builder)->rQuadTo(x1, y1, x2, y2);
}

void * SkPathBuilder_rConicTo(void *path_builder, sk_point_t p1, sk_point_t p2, float w) {
    return &static_cast<SkPathBuilder *>(path_builder)->rConicTo(static_sk_point_get(p1), static_sk_point_get(p2), w);
}

void * SkPathBuilder_rConicTo_2(void *path_builder, float x1, float y1, float x2, float y2, float w) {
    return &static_cast<SkPathBuilder *>(path_builder)->rConicTo(x1, y1, x2, y2, w);
}

void * SkPathBuilder_rCubicTo(void *path_builder, sk_point_t pt1, sk_point_t pt2, sk_point_t pt3) {
    return &static_cast<SkPathBuilder *>(path_builder)->rCubicTo(static_sk_point_get(pt1), static_sk_point_get(pt2), static_sk_point_get(pt3));
}

void * SkPathBuilder_rCubicTo_2(void *path_builder, float x1, float y1, float x2, float y2, float x3, float y3) {
    return &static_cast<SkPathBuilder *>(path_builder)->rCubicTo(x1, y1, x2, y2, x3, y3);
}

void * SkPathBuilder_arcTo(void *path_builder, const void *oval, float startAngleDeg, float sweepAngleDeg, bool forceMoveTo) {
    return &static_cast<SkPathBuilder *>(path_builder)->arcTo(* static_cast<const SkRect *>(oval), startAngleDeg, sweepAngleDeg, forceMoveTo);
}

void * SkPathBuilder_arcTo_2(void *path_builder, sk_point_t p1, sk_point_t p2, float radius) {
    return &static_cast<SkPathBuilder *>(path_builder)->arcTo(static_sk_point_get(p1), static_sk_point_get(p2), radius);
}

void * SkPathBuilder_arcTo_3(void *path_builder, sk_point_t r, float xAxisRotate, int largeArc, int sweep, sk_point_t xy) {
    return &static_cast<SkPathBuilder *>(path_builder)->arcTo(static_sk_point_get(r), xAxisRotate, static_cast<SkPathBuilder::ArcSize>(largeArc), static_cast<SkPathDirection>(sweep), static_sk_point_get(xy));
}

void * SkPathBuilder_addArc(void *path_builder, const void *oval, float startAngleDeg, float sweepAngleDeg) {
    return &static_cast<SkPathBuilder *>(path_builder)->addArc(* static_cast<const SkRect *>(oval), startAngleDeg, sweepAngleDeg);
}

void * SkPathBuilder_addRect(void *path_builder, const void *rect, int dir, unsigned startIndex) {
    return &static_cast<SkPathBuilder *>(path_builder)->addRect(* static_cast<const SkRect *>(rect), static_cast<SkPathDirection>(dir), startIndex);
}

void * SkPathBuilder_addRect_2(void *path_builder, const void *rect, int dir) {
    return &static_cast<SkPathBuilder *>(path_builder)->addRect(* static_cast<const SkRect *>(rect), (SkPathDirection)dir);
}

void * SkPathBuilder_addOval(void *path_builder, const void *rect, int dir, unsigned startIndex) {
    return &static_cast<SkPathBuilder *>(path_builder)->addOval(* static_cast<const SkRect *>(rect), (SkPathDirection)dir, startIndex);
}

void * SkPathBuilder_addOval_2(void *path_builder, const void *rect, int dir) {
    return &static_cast<SkPathBuilder *>(path_builder)->addOval(* static_cast<const SkRect *>(rect), (SkPathDirection)dir);
}

void * SkPathBuilder_addRRect(void *path_builder, const void *rect, int dir, unsigned startIndex) {
    return &static_cast<SkPathBuilder *>(path_builder)->addRRect(* static_cast<const SkRRect *>(rect), (SkPathDirection)dir, startIndex);
}

void * SkPathBuilder_addRRect_2(void *path_builder, const void *rrect, int dir) {
    return &static_cast<SkPathBuilder *>(path_builder)->addRRect(* static_cast<const SkRRect *>(rrect), (SkPathDirection)dir);
}

void * SkPathBuilder_addCircle(void *path_builder, float center_x, float center_y, float radius, int dir) {
    return &static_cast<SkPathBuilder *>(path_builder)->addCircle(center_x, center_y, radius, (SkPathDirection)dir);
}

void * SkPathBuilder_addPolygon(void *path_builder, const void * pts, int count, bool isClosed) {
    return &static_cast<SkPathBuilder *>(path_builder)->addPolygon(static_cast<const SkPoint *>(pts), count, isClosed);
}

void * SkPathBuilder_addPolygon_2(void *path_builder, const void *list, bool isClosed) {
    return &static_cast<SkPathBuilder *>(path_builder)->addPolygon(* static_cast<const std::initializer_list<SkPoint> *>(list), isClosed);
}

void * SkPathBuilder_addPath(void *path_builder, const void *path) {
    return &static_cast<SkPathBuilder *>(path_builder)->addPath(* static_cast<const SkPath *>(path));
}

void SkPathBuilder_incReserve(void *path_builder, int extraPtCount, int extraVerbCount) {
    static_cast<SkPathBuilder *>(path_builder)->incReserve(extraPtCount, extraVerbCount);
}

void SkPathBuilder_incReserve_2(void *path_builder, int extraPtCount) {
    static_cast<SkPathBuilder *>(path_builder)->incReserve(extraPtCount);
}

void * SkPathBuilder_offset(void *path_builder, float dx, float dy) {
    return &static_cast<SkPathBuilder *>(path_builder)->offset(dx, dy);
}

void * SkPathBuilder_toggleInverseFillType(void *path_builder) {
    return &static_cast<SkPathBuilder *>(path_builder)->toggleInverseFillType();
}

}
