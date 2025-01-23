//
// Created by dolphilia on 2024/01/09.
//

#include "sk_path.h"

#include "../static/static_sk_path-internal.h"
#include "../static/static_sk_point-internal.h"
#include "../static/static_sk_rect-internal.h"
#include "../static/static_sk_data-internal.h"

extern "C" {

//SkPath & operator=(const SkPath &path)

void *SkPath_new() {
    return new SkPath();
}

void *SkPath_new_2(const void *path) {
    return new SkPath(* static_cast<const SkPath *>(path));
}

void SkPath_delete(void *path) {
    delete static_cast<SkPath *>(path);
}

bool SkPath_isInterpolatable(void *path, const void *compare) {
    return static_cast<SkPath *>(path)->isInterpolatable(* static_cast<const SkPath *>(compare));
}

bool SkPath_interpolate(void *path, const void *ending, SkScalar weight, void *out) {
    return static_cast<SkPath *>(path)->interpolate(* static_cast<const SkPath *>(ending), weight, static_cast<SkPath *>(out));
}

SkPathFillType SkPath_getFillType(void *path) {
    return static_cast<SkPath *>(path)->getFillType();
}

void SkPath_setFillType(void *path, SkPathFillType ft) {
    static_cast<SkPath *>(path)->setFillType(ft);
}

bool SkPath_isInverseFillType(void *path) {
    return static_cast<SkPath *>(path)->isInverseFillType();
}

void SkPath_toggleInverseFillType(void *path) {
    static_cast<SkPath *>(path)->toggleInverseFillType();
}

bool SkPath_isConvex(void *path) {
    return static_cast<SkPath *>(path)->isConvex();
}

bool SkPath_isOval(void *path, void *bounds) {
    return static_cast<SkPath *>(path)->isOval(static_cast<SkRect *>(bounds));
}

bool SkPath_isRRect(void *path, void *rrect) {
    return static_cast<SkPath *>(path)->isRRect(static_cast<SkRRect *>(rrect));
}

SkPath * SkPath_reset(void *path) {
    auto *p = static_cast<SkPath *>(path);
    return &p->reset();
}

SkPath * SkPath_rewind(void *path) {
    auto *p = static_cast<SkPath *>(path);
    return &p->rewind();
}

bool SkPath_isEmpty(void *path) {
    return static_cast<SkPath *>(path)->isEmpty();
}

bool SkPath_isLastContourClosed(void *path) {
    return static_cast<SkPath *>(path)->isLastContourClosed();
}

bool SkPath_isFinite(void *path) {
    return static_cast<SkPath *>(path)->isFinite();
}

bool SkPath_isVolatile(void *path) {
    return static_cast<SkPath *>(path)->isVolatile();
}

SkPath * SkPath_setIsVolatile(void *path, bool isVolatile) {
    auto *p = static_cast<SkPath *>(path);
    return &p->setIsVolatile(isVolatile);
}

bool SkPath_isLine(void *path, void * line) {
    return static_cast<SkPath *>(path)->isLine(static_cast<SkPoint *>(line));
}

int SkPath_countPoints(void *path) {
    return static_cast<SkPath *>(path)->countPoints();
}

sk_point_t SkPath_getPoint(void *path, int index) {
    return static_sk_point_make(static_cast<SkPath *>(path)->getPoint(index));
}

int SkPath_getPoints(void *path, void * points, int max) {
    return static_cast<SkPath *>(path)->getPoints(static_cast<SkPoint *>(points), max);
}

int SkPath_countVerbs(void *path) {
    return static_cast<SkPath *>(path)->countVerbs();
}

int SkPath_getVerbs(void *path, void * verbs, int max) {
    return static_cast<SkPath *>(path)->getVerbs(static_cast<uint8_t *>(verbs), max);
}

size_t SkPath_approximateBytesUsed(void *path) {
    return static_cast<SkPath *>(path)->approximateBytesUsed();
}

void SkPath_swap(void *path, void *other) {
    static_cast<SkPath *>(path)->swap(* static_cast<SkPath *>(other));
}

const SkRect * SkPath_getBounds(void *path) {
    auto *p = static_cast<SkPath *>(path);
    return &p->getBounds();
}

void SkPath_updateBoundsCache(void *path) {
    static_cast<SkPath *>(path)->updateBoundsCache();
}

sk_rect_t SkPath_computeTightBounds(void *path) {
    return static_sk_rect_make(static_cast<SkPath *>(path)->computeTightBounds());
}

bool SkPath_conservativelyContainsRect(void *path, const void *rect) {
    return static_cast<SkPath *>(path)->conservativelyContainsRect(* static_cast<const SkRect *>(rect));
}

void SkPath_incReserve(void *path, int extraPtCount) {
    static_cast<SkPath *>(path)->incReserve(extraPtCount);
}

SkPath * SkPath_moveTo(void *path, SkScalar x, SkScalar y) {
    auto *p = static_cast<SkPath *>(path);
    return &p->moveTo(x, y);
}

SkPath * SkPath_moveTo_2(void *path, const void *p) {
    auto *_path = static_cast<SkPath *>(path);
    return &_path->moveTo(* static_cast<const SkPoint *>(p));
}

SkPath * SkPath_rMoveTo(void *path, SkScalar dx, SkScalar dy) {
    auto *p = static_cast<SkPath *>(path);
    return &p->rMoveTo(dx, dy);
}

SkPath * SkPath_lineTo(void *path, SkScalar x, SkScalar y) {
    auto *p = static_cast<SkPath *>(path);
    return &p->lineTo(x, y);
}

SkPath * SkPath_lineTo_2(void *path, const void *p) {
    auto *_path = static_cast<SkPath *>(path);
    return &_path->lineTo(* static_cast<const SkPoint *>(p));
}

SkPath * SkPath_rLineTo(void *path, SkScalar dx, SkScalar dy) {
    auto *p = static_cast<SkPath *>(path);
    return &p->rLineTo(dx, dy);
}

SkPath * SkPath_quadTo(void *path, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2) {
    auto *p = static_cast<SkPath *>(path);
    return &p->quadTo(x1, y1, x2, y2);
}

SkPath * SkPath_quadTo_2(void *path, const void *p1, const void *p2) {
    auto *p = static_cast<SkPath *>(path);
    return &p->quadTo(* static_cast<const SkPoint *>(p1), * static_cast<const SkPoint *>(p2));
}

SkPath * SkPath_rQuadTo(void *path, SkScalar dx1, SkScalar dy1, SkScalar dx2, SkScalar dy2) {
    auto *p = static_cast<SkPath *>(path);
    return &p->rQuadTo(dx1, dy1, dx2, dy2);
}

SkPath * SkPath_conicTo(void *path, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2, SkScalar w) {
    auto *p = static_cast<SkPath *>(path);
    return &p->conicTo(x1, y1, x2, y2, w);
}

SkPath * SkPath_conicTo_2(void *path, const void *p1, const void *p2, SkScalar w) {
    auto *p = static_cast<SkPath *>(path);
    return &p->conicTo(* static_cast<const SkPoint *>(p1), * static_cast<const SkPoint *>(p2), w);
}

SkPath * SkPath_rConicTo(void *path, SkScalar dx1, SkScalar dy1, SkScalar dx2, SkScalar dy2, SkScalar w) {
    auto *p = static_cast<SkPath *>(path);
    return &p->rConicTo(dx1, dy1, dx2, dy2, w);
}

SkPath * SkPath_cubicTo(void *path, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2, SkScalar x3, SkScalar y3) {
    auto *p = static_cast<SkPath *>(path);
    return &p->cubicTo(x1, y1, x2, y2, x3, y3);
}

SkPath * SkPath_cubicTo_2(void *path, const void *p1, const void *p2, const void *p3) {
    auto *p = static_cast<SkPath *>(path);
    return &p->cubicTo(* static_cast<const SkPoint *>(p1), * static_cast<const SkPoint *>(p2), * static_cast<const SkPoint *>(p3));
}

SkPath * SkPath_rCubicTo(void *path, SkScalar dx1, SkScalar dy1, SkScalar dx2, SkScalar dy2, SkScalar dx3, SkScalar dy3) {
    auto *p = static_cast<SkPath *>(path);
    return &p->rCubicTo(dx1, dy1, dx2, dy2, dx3, dy3);
}

SkPath * SkPath_arcTo(void *path, const void *oval, SkScalar startAngle, SkScalar sweepAngle, bool forceMoveTo) {
    auto *p = static_cast<SkPath *>(path);
    return &p->arcTo(* static_cast<const SkRect *>(oval), startAngle, sweepAngle, forceMoveTo);
}

SkPath * SkPath_arcTo_2(void *path, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2, SkScalar radius) {
    auto *p = static_cast<SkPath *>(path);
    return &p->arcTo(x1, y1, x2, y2, radius);
}

SkPath * SkPath_arcTo_3(void *path, sk_point_t p1, sk_point_t p2, SkScalar radius) {
    auto *p = static_cast<SkPath *>(path);
    return &p->arcTo(static_sk_point_get(p1), static_sk_point_get(p2), radius);
}

SkPath * SkPath_arcTo_4(void *path, SkScalar rx, SkScalar ry, SkScalar xAxisRotate, SkPath::ArcSize largeArc, SkPathDirection sweep, SkScalar x, SkScalar y) {
    auto *p = static_cast<SkPath *>(path);
    return &p->arcTo(rx, ry, xAxisRotate, largeArc, sweep, x, y);
}

SkPath * SkPath_arcTo_5(void *path, sk_point_t r, SkScalar xAxisRotate, SkPath::ArcSize largeArc, SkPathDirection sweep, sk_point_t xy) {
    auto *p = static_cast<SkPath *>(path);
    return &p->arcTo(static_sk_point_get(r), xAxisRotate, largeArc, sweep, static_sk_point_get(xy));
}

SkPath * SkPath_rArcTo(void *path, SkScalar rx, SkScalar ry, SkScalar xAxisRotate, SkPath::ArcSize largeArc, SkPathDirection sweep, SkScalar dx, SkScalar dy) {
    auto *p = static_cast<SkPath *>(path);
    return &p->arcTo(rx, ry, xAxisRotate, largeArc, sweep, dx, dy);
}

SkPath * SkPath_close(void *path) {
    auto *p = static_cast<SkPath *>(path);
    return &p->close();
}

bool SkPath_isRect(void *path, void *rect, void *isClosed, void *direction) {
    return static_cast<SkPath *>(path)->isRect(static_cast<SkRect *>(rect), static_cast<bool *>(isClosed), static_cast<SkPathDirection *>(direction));
}

SkPath * SkPath_addRect(void *path, const void *rect, SkPathDirection dir, unsigned start) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addRect(* static_cast<const SkRect *>(rect), dir, start);
}

SkPath * SkPath_addRect_2(void *path, const void *rect, SkPathDirection dir) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addRect(* static_cast<const SkRect *>(rect), dir);
}

SkPath * SkPath_addRect_3(void *path, SkScalar left, SkScalar top, SkScalar right, SkScalar bottom, SkPathDirection dir) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addRect(left, top, right, bottom, dir);
}

SkPath * SkPath_addOval(void *path, const void *oval, SkPathDirection dir) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addOval(* static_cast<const SkRect *>(oval), dir);
}

SkPath * SkPath_addOval_2(void *path, const void *oval, SkPathDirection dir, unsigned start) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addOval(* static_cast<const SkRect *>(oval), dir, start);
}

SkPath * SkPath_addCircle(void *path, SkScalar x, SkScalar y, SkScalar radius, SkPathDirection dir) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addCircle(x, y, radius, dir);
}

SkPath * SkPath_addArc(void *path, const void *oval, SkScalar startAngle, SkScalar sweepAngle) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addArc(* static_cast<const SkRect *>(oval), startAngle, sweepAngle);
}

SkPath * SkPath_addRoundRect(void *path, const void *rect, SkScalar rx, SkScalar ry, SkPathDirection dir) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addRoundRect(* static_cast<const SkRect *>(rect), rx, ry, dir);
}

SkPath * SkPath_addRoundRect_2(void *path, const void *rect, const void * radii, SkPathDirection dir) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addRoundRect(* static_cast<const SkRect *>(rect), static_cast<const SkScalar *>(radii), dir);
}

SkPath * SkPath_addRRect(void *path, const SkRRect *rrect, SkPathDirection dir) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addRRect(*rrect, dir);
}

SkPath * SkPath_addRRect_2(void *path, const SkRRect *rrect, SkPathDirection dir, unsigned start) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addRRect(*rrect, dir, start);
}

SkPath * SkPath_addPoly(void *path, const SkPoint pts[], int count, bool close) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addPoly(pts, count, close);
}

SkPath * SkPath_addPoly_2(void *path, const std::initializer_list<SkPoint> *list, bool close) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addPoly(*list, close);
}

SkPath * SkPath_addPath(void *path, const SkPath *src, SkScalar dx, SkScalar dy, SkPath::AddPathMode mode) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addPath(*src, dx, dy, mode);
}

SkPath * SkPath_addPath_2(void *path, const SkPath *src, SkPath::AddPathMode modeSkPath) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addPath(*src, modeSkPath);
}

SkPath * SkPath_addPath_3(void *path, const SkPath *src, const SkMatrix *matrix, SkPath::AddPathMode mode) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addPath(*src, *matrix, mode);
}

SkPath * SkPath_reverseAddPath(void *path, const SkPath *src) {
    auto *p = static_cast<SkPath *>(path);
    return &p->reverseAddPath(*src);
}

void SkPath_offset(void *path, SkScalar dx, SkScalar dy, SkPath *dst) {
    static_cast<SkPath *>(path)->offset(dx, dy, dst);
}

void SkPath_offset_2(void *path, SkScalar dx, SkScalar dy) {
    static_cast<SkPath *>(path)->offset(dx, dy);
}

void SkPath_transform(void *path, const SkMatrix *matrix, SkPath *dst, SkApplyPerspectiveClip pc) {
    static_cast<SkPath *>(path)->transform(*matrix, dst, pc);
}

void SkPath_transform_2(void *path, const SkMatrix *matrix, SkApplyPerspectiveClip pc) {
    static_cast<SkPath *>(path)->transform(*matrix, pc);
}

sk_path_t SkPath_makeTransform(void *path, const SkMatrix *m, SkApplyPerspectiveClip pc) {
    return static_sk_path_make(static_cast<SkPath *>(path)->makeTransform(*m, pc));
}

sk_path_t SkPath_makeScale(void *path, SkScalar sx, SkScalar sy) {
    return static_sk_path_make(static_cast<SkPath *>(path)->makeScale(sx, sy));
}

bool SkPath_getLastPt(void *path, SkPoint *lastPt) {
    return static_cast<SkPath *>(path)->getLastPt(lastPt);
}

void SkPath_setLastPt(void *path, SkScalar x, SkScalar y) {
    static_cast<SkPath *>(path)->setLastPt(x, y);
}

void SkPath_setLastPt_2(void *path, const SkPoint *p) {
    static_cast<SkPath *>(path)->setLastPt(*p);
}

uint32_t SkPath_getSegmentMasks(void *path) {
    return static_cast<SkPath *>(path)->getSegmentMasks();
}

bool SkPath_contains(void *path, SkScalar x, SkScalar y) {
    return static_cast<SkPath *>(path)->contains(x, y);
}

void SkPath_dump(void *path, SkWStream *stream, bool dumpAsHex) {
    static_cast<SkPath *>(path)->dump(stream, dumpAsHex);
}

void SkPath_dump_2(void *path) {
    static_cast<SkPath *>(path)->dump();
}

void SkPath_dumpHex(void *path) {
    static_cast<SkPath *>(path)->dumpHex();
}

void SkPath_dumpArrays(void *path, SkWStream *stream, bool dumpAsHex) {
    static_cast<SkPath *>(path)->dumpArrays(stream, dumpAsHex);
}

void SkPath_dumpArrays_2(void *path) {
    static_cast<SkPath *>(path)->dumpArrays();
}

size_t SkPath_writeToMemory(void *path, void *buffer) {
    return static_cast<SkPath *>(path)->writeToMemory(buffer);
}

sk_data_t SkPath_serialize(void *path) {
    return static_sk_data_make(static_cast<SkPath *>(path)->serialize());
}

size_t SkPath_readFromMemory(void *path, const void *buffer, size_t length) {
    return static_cast<SkPath *>(path)->readFromMemory(buffer, length);
}

uint32_t SkPath_getGenerationID(void *path) {
    return static_cast<SkPath *>(path)->getGenerationID();
}

bool SkPath_isValid(void *path) {
    return static_cast<SkPath *>(path)->isValid();
}


// static

sk_path_t SkPath_Make(const SkPoint point[], int pointCount, const uint8_t i[], int verbCount, const SkScalar v[], int conicWeightCount, SkPathFillType type, bool isVolatile) {
    return static_sk_path_make(SkPath::Make(point, pointCount, i, verbCount, v, conicWeightCount, type, isVolatile));
}

sk_path_t SkPath_Rect(const SkRect *rect, SkPathDirection dir, unsigned startIndex) {
    return static_sk_path_make(SkPath::Rect(*rect, dir, startIndex));
}

sk_path_t SkPath_Oval(const SkRect *rect, SkPathDirection dir) {
    return static_sk_path_make(SkPath::Oval(*rect, dir));
}

sk_path_t SkPath_Oval_2(const SkRect *rect, SkPathDirection dir, unsigned startIndex) {
    return static_sk_path_make(SkPath::Oval(*rect, dir, startIndex));
}

sk_path_t SkPath_Circle(SkScalar center_x, SkScalar center_y, SkScalar radius, SkPathDirection dir) {
    return static_sk_path_make(SkPath::Circle(center_x, center_y, radius, dir));
}

sk_path_t SkPath_RRect(const SkRRect *rrect, SkPathDirection dir) {
    return static_sk_path_make(SkPath::RRect(*rrect, dir));
}

sk_path_t SkPath_RRect_2(const SkRRect *rrect, SkPathDirection dir, unsigned startIndex) {
    return static_sk_path_make(SkPath::RRect(*rrect, dir, startIndex));
}

sk_path_t SkPath_RRect_3(const SkRect *bounds, SkScalar rx, SkScalar ry, SkPathDirection dir) {
    return static_sk_path_make(SkPath::RRect(*bounds, rx, ry, dir));
}

sk_path_t SkPath_Polygon(const SkPoint pts[], int count, bool isClosed, SkPathFillType type, bool isVolatile) {
    return static_sk_path_make(SkPath::Polygon(pts, count, isClosed, type, isVolatile));
}

sk_path_t SkPath_Polygon_2(const std::initializer_list<SkPoint> *list, bool isClosed, SkPathFillType fillType, bool isVolatile) {
    return static_sk_path_make(SkPath::Polygon(*list, isClosed, fillType, isVolatile));
}

sk_path_t SkPath_Line(sk_point_t a, sk_point_t b) {
    return static_sk_path_make(SkPath::Line(static_sk_point_get(a), static_sk_point_get(b)));
}

bool SkPath_IsLineDegenerate(const SkPoint *p1, const SkPoint *p2, bool exact) {
    return SkPath::IsLineDegenerate(*p1, *p2, exact);
}

bool SkPath_IsQuadDegenerate(const SkPoint *p1, const SkPoint *p2, const SkPoint *p3, bool exact) {
    return SkPath::IsQuadDegenerate(*p1, *p2, *p3, exact);
}

bool SkPath_IsCubicDegenerate(const SkPoint *p1, const SkPoint *p2, const SkPoint *p3, const SkPoint *p4, bool exact) {
    return SkPath::IsCubicDegenerate(*p1, *p2, *p3, *p4, exact);
}

int SkPath_ConvertConicToQuads(const SkPoint *p0, const SkPoint *p1, const SkPoint *p2, SkScalar w, SkPoint pts[], int pow2) {
    return SkPath::ConvertConicToQuads(*p0, *p1, *p2, w, pts, pow2);
}

}
