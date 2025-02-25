//
// Created by dolphilia on 2024/01/09.
//

#include "sk_path.h"

#include "include/core/SkPath.h"

#include "../static/static_sk_data.h"
#include "../static/static_sk_rect.h"
#include "../static/static_sk_path.h"
#include "../static/static_sk_point.h"

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

bool SkPath_interpolate(void *path, const void *ending, float weight, void *out) {
    return static_cast<SkPath *>(path)->interpolate(* static_cast<const SkPath *>(ending), weight, static_cast<SkPath *>(out));
}

int SkPath_getFillType(void *path) {
    return static_cast<int>(static_cast<SkPath *>(path)->getFillType());
}

void SkPath_setFillType(void *path, int ft) {
    static_cast<SkPath *>(path)->setFillType(static_cast<SkPathFillType>(ft));
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

void * SkPath_reset(void *path) {
    auto *p = static_cast<SkPath *>(path);
    return &p->reset();
}

void * SkPath_rewind(void *path) {
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

void * SkPath_setIsVolatile(void *path, bool isVolatile) {
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

const void * SkPath_getBounds(void *path) {
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

void * SkPath_moveTo(void *path, float x, float y) {
    auto *p = static_cast<SkPath *>(path);
    return &p->moveTo(x, y);
}

void * SkPath_moveTo_2(void *path, const void *p) {
    auto *_path = static_cast<SkPath *>(path);
    return &_path->moveTo(* static_cast<const SkPoint *>(p));
}

void * SkPath_rMoveTo(void *path, float dx, float dy) {
    auto *p = static_cast<SkPath *>(path);
    return &p->rMoveTo(dx, dy);
}

void * SkPath_lineTo(void *path, float x, float y) {
    auto *p = static_cast<SkPath *>(path);
    return &p->lineTo(x, y);
}

void * SkPath_lineTo_2(void *path, const void *p) {
    auto *_path = static_cast<SkPath *>(path);
    return &_path->lineTo(* static_cast<const SkPoint *>(p));
}

void * SkPath_rLineTo(void *path, float dx, float dy) {
    auto *p = static_cast<SkPath *>(path);
    return &p->rLineTo(dx, dy);
}

void * SkPath_quadTo(void *path, float x1, float y1, float x2, float y2) {
    auto *p = static_cast<SkPath *>(path);
    return &p->quadTo(x1, y1, x2, y2);
}

void * SkPath_quadTo_2(void *path, const void *p1, const void *p2) {
    auto *p = static_cast<SkPath *>(path);
    return &p->quadTo(* static_cast<const SkPoint *>(p1), * static_cast<const SkPoint *>(p2));
}

void * SkPath_rQuadTo(void *path, float dx1, float dy1, float dx2, float dy2) {
    auto *p = static_cast<SkPath *>(path);
    return &p->rQuadTo(dx1, dy1, dx2, dy2);
}

void * SkPath_conicTo(void *path, float x1, float y1, float x2, float y2, float w) {
    auto *p = static_cast<SkPath *>(path);
    return &p->conicTo(x1, y1, x2, y2, w);
}

void * SkPath_conicTo_2(void *path, const void *p1, const void *p2, float w) {
    auto *p = static_cast<SkPath *>(path);
    return &p->conicTo(* static_cast<const SkPoint *>(p1), * static_cast<const SkPoint *>(p2), w);
}

void * SkPath_rConicTo(void *path, float dx1, float dy1, float dx2, float dy2, float w) {
    auto *p = static_cast<SkPath *>(path);
    return &p->rConicTo(dx1, dy1, dx2, dy2, w);
}

void * SkPath_cubicTo(void *path, float x1, float y1, float x2, float y2, float x3, float y3) {
    auto *p = static_cast<SkPath *>(path);
    return &p->cubicTo(x1, y1, x2, y2, x3, y3);
}

void * SkPath_cubicTo_2(void *path, const void *p1, const void *p2, const void *p3) {
    auto *p = static_cast<SkPath *>(path);
    return &p->cubicTo(* static_cast<const SkPoint *>(p1), * static_cast<const SkPoint *>(p2), * static_cast<const SkPoint *>(p3));
}

void * SkPath_rCubicTo(void *path, float dx1, float dy1, float dx2, float dy2, float dx3, float dy3) {
    auto *p = static_cast<SkPath *>(path);
    return &p->rCubicTo(dx1, dy1, dx2, dy2, dx3, dy3);
}

void * SkPath_arcTo(void *path, const void *oval, float startAngle, float sweepAngle, bool forceMoveTo) {
    auto *p = static_cast<SkPath *>(path);
    return &p->arcTo(* static_cast<const SkRect *>(oval), startAngle, sweepAngle, forceMoveTo);
}

void * SkPath_arcTo_2(void *path, float x1, float y1, float x2, float y2, float radius) {
    auto *p = static_cast<SkPath *>(path);
    return &p->arcTo(x1, y1, x2, y2, radius);
}

void * SkPath_arcTo_3(void *path, sk_point_t p1, sk_point_t p2, float radius) {
    auto *p = static_cast<SkPath *>(path);
    return &p->arcTo(static_sk_point_get_entity(p1), static_sk_point_get_entity(p2), radius);
}

void * SkPath_arcTo_4(void *path, float rx, float ry, float xAxisRotate, int largeArc, int sweep, float x, float y) {
    auto *p = static_cast<SkPath *>(path);
    return &p->arcTo(rx, ry, xAxisRotate, static_cast<SkPath::ArcSize>(largeArc), static_cast<SkPathDirection>(sweep), x, y);
}

void * SkPath_arcTo_5(void *path, sk_point_t r, float xAxisRotate, int largeArc, int sweep, sk_point_t xy) {
    auto *p = static_cast<SkPath *>(path);
    return &p->arcTo(static_sk_point_get_entity(r), xAxisRotate, static_cast<SkPath::ArcSize>(largeArc), static_cast<SkPathDirection>(sweep), static_sk_point_get_entity(xy));
}

void * SkPath_rArcTo(void *path, float rx, float ry, float xAxisRotate, int largeArc, int sweep, float dx, float dy) {
    auto *p = static_cast<SkPath *>(path);
    return &p->arcTo(rx, ry, xAxisRotate, static_cast<SkPath::ArcSize>(largeArc), static_cast<SkPathDirection>(sweep), dx, dy);
}

void * SkPath_close(void *path) {
    auto *p = static_cast<SkPath *>(path);
    return &p->close();
}

bool SkPath_isRect(void *path, void *rect, void *isClosed, void *direction) {
    return static_cast<SkPath *>(path)->isRect(static_cast<SkRect *>(rect), static_cast<bool *>(isClosed), static_cast<SkPathDirection *>(direction));
}

void * SkPath_addRect(void *path, const void *rect, int dir, unsigned start) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addRect(* static_cast<const SkRect *>(rect), static_cast<SkPathDirection>(dir), start);
}

void * SkPath_addRect_2(void *path, const void *rect, int dir) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addRect(* static_cast<const SkRect *>(rect), static_cast<SkPathDirection>(dir));
}

void * SkPath_addRect_3(void *path, float left, float top, float right, float bottom, int dir) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addRect(left, top, right, bottom, static_cast<SkPathDirection>(dir));
}

void * SkPath_addOval(void *path, const void *oval, int dir) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addOval(* static_cast<const SkRect *>(oval), static_cast<SkPathDirection>(dir));
}

void * SkPath_addOval_2(void *path, const void *oval, int dir, unsigned start) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addOval(* static_cast<const SkRect *>(oval), static_cast<SkPathDirection>(dir), start);
}

void * SkPath_addCircle(void *path, float x, float y, float radius, int dir) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addCircle(x, y, radius, static_cast<SkPathDirection>(dir));
}

void * SkPath_addArc(void *path, const void *oval, float startAngle, float sweepAngle) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addArc(* static_cast<const SkRect *>(oval), startAngle, sweepAngle);
}

void * SkPath_addRoundRect(void *path, const void *rect, float rx, float ry, int dir) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addRoundRect(* static_cast<const SkRect *>(rect), rx, ry, static_cast<SkPathDirection>(dir));
}

void * SkPath_addRoundRect_2(void *path, const void *rect, const void * radii, int dir) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addRoundRect(* static_cast<const SkRect *>(rect), static_cast<const SkScalar *>(radii), static_cast<SkPathDirection>(dir));
}

void * SkPath_addRRect(void *path, const void *rrect, int dir) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addRRect(* static_cast<const SkRRect *>(rrect), static_cast<SkPathDirection>(dir));
}

void * SkPath_addRRect_2(void *path, const void *rrect, int dir, unsigned start) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addRRect(* static_cast<const SkRRect *>(rrect), static_cast<SkPathDirection>(dir), start);
}

void * SkPath_addPoly(void *path, const void * pts, int count, bool close) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addPoly(static_cast<const SkPoint *>(pts), count, close);
}

void * SkPath_addPoly_2(void *path, const void *list, bool close) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addPoly(* static_cast<const std::initializer_list<SkPoint> *>(list), close);
}

void * SkPath_addPath(void *path, const void *src, float dx, float dy, int mode) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addPath(* static_cast<const SkPath *>(src), dx, dy, static_cast<SkPath::AddPathMode>(mode));
}

void * SkPath_addPath_2(void *path, const void *src, int modeSkPath) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addPath(* static_cast<const SkPath *>(src), static_cast<SkPath::AddPathMode>(modeSkPath));
}

void * SkPath_addPath_3(void *path, const void *src, const void *matrix, int mode) {
    auto *p = static_cast<SkPath *>(path);
    return &p->addPath(* static_cast<const SkPath *>(src), * static_cast<const SkMatrix *>(matrix), static_cast<SkPath::AddPathMode>(mode));
}

void * SkPath_reverseAddPath(void *path, const void *src) {
    auto *p = static_cast<SkPath *>(path);
    return &p->reverseAddPath(* static_cast<const SkPath *>(src));
}

void SkPath_offset(void *path, float dx, float dy, void *dst) {
    static_cast<SkPath *>(path)->offset(dx, dy, static_cast<SkPath *>(dst));
}

void SkPath_offset_2(void *path, float dx, float dy) {
    static_cast<SkPath *>(path)->offset(dx, dy);
}

void SkPath_transform(void *path, const void *matrix, void *dst, int pc) {
    static_cast<SkPath *>(path)->transform(* static_cast<const SkMatrix *>(matrix), static_cast<SkPath *>(dst), static_cast<SkApplyPerspectiveClip>(pc));
}

void SkPath_transform_2(void *path, const void *matrix, int pc) {
    static_cast<SkPath *>(path)->transform(* static_cast<const SkMatrix *>(matrix), static_cast<SkApplyPerspectiveClip>(pc));
}

sk_path_t SkPath_makeTransform(void *path, const void *m, int pc) {
    return static_sk_path_make(static_cast<SkPath *>(path)->makeTransform(* static_cast<const SkMatrix *>(m), static_cast<SkApplyPerspectiveClip>(pc)));
}

sk_path_t SkPath_makeScale(void *path, float sx, float sy) {
    return static_sk_path_make(static_cast<SkPath *>(path)->makeScale(sx, sy));
}

bool SkPath_getLastPt(void *path, void *lastPt) {
    return static_cast<SkPath *>(path)->getLastPt(static_cast<SkPoint *>(lastPt));
}

void SkPath_setLastPt(void *path, float x, float y) {
    static_cast<SkPath *>(path)->setLastPt(x, y);
}

void SkPath_setLastPt_2(void *path, const void *p) {
    static_cast<SkPath *>(path)->setLastPt(* static_cast<const SkPoint *>(p));
}

uint32_t SkPath_getSegmentMasks(void *path) {
    return static_cast<SkPath *>(path)->getSegmentMasks();
}

bool SkPath_contains(void *path, float x, float y) {
    return static_cast<SkPath *>(path)->contains(x, y);
}

void SkPath_dump(void *path, void *stream, bool dumpAsHex) {
    static_cast<SkPath *>(path)->dump(static_cast<SkWStream *>(stream), dumpAsHex);
}

void SkPath_dump_2(void *path) {
    static_cast<SkPath *>(path)->dump();
}

void SkPath_dumpHex(void *path) {
    static_cast<SkPath *>(path)->dumpHex();
}

void SkPath_dumpArrays(void *path, void *stream, bool dumpAsHex) {
    static_cast<SkPath *>(path)->dumpArrays(static_cast<SkWStream *>(stream), dumpAsHex);
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

sk_path_t SkPath_Make(const void * point, int pointCount, const void * i, int verbCount, const void * v, int conicWeightCount, int type, bool isVolatile) {
    return static_sk_path_make(SkPath::Make(static_cast<const SkPoint *>(point), pointCount, static_cast<const uint8_t *>(i), verbCount, static_cast<const SkScalar *>(v), conicWeightCount, static_cast<SkPathFillType>(type), isVolatile));
}

sk_path_t SkPath_Rect(const void *rect, int dir, unsigned startIndex) {
    return static_sk_path_make(SkPath::Rect(* static_cast<const SkRect *>(rect), static_cast<SkPathDirection>(dir), startIndex));
}

sk_path_t SkPath_Oval(const void *rect, int dir) {
    return static_sk_path_make(SkPath::Oval(* static_cast<const SkRect *>(rect), static_cast<SkPathDirection>(dir)));
}

sk_path_t SkPath_Oval_2(const void *rect, int dir, unsigned startIndex) {
    return static_sk_path_make(SkPath::Oval(* static_cast<const SkRect *>(rect), static_cast<SkPathDirection>(dir), startIndex));
}

sk_path_t SkPath_Circle(float center_x, float center_y, float radius, int dir) {
    return static_sk_path_make(SkPath::Circle(center_x, center_y, radius, static_cast<SkPathDirection>(dir)));
}

sk_path_t SkPath_RRect(const void *rrect, int dir) {
    return static_sk_path_make(SkPath::RRect(* static_cast<const SkRRect *>(rrect), static_cast<SkPathDirection>(dir)));
}

sk_path_t SkPath_RRect_2(const void *rrect, int dir, unsigned startIndex) {
    return static_sk_path_make(SkPath::RRect(* static_cast<const SkRRect *>(rrect), static_cast<SkPathDirection>(dir), startIndex));
}

sk_path_t SkPath_RRect_3(const void *bounds, float rx, float ry, int dir) {
    return static_sk_path_make(SkPath::RRect(* static_cast<const SkRect *>(bounds), rx, ry, static_cast<SkPathDirection>(dir)));
}

sk_path_t SkPath_Polygon(const void * pts, int count, bool isClosed, int type, bool isVolatile) {
    return static_sk_path_make(SkPath::Polygon(static_cast<const SkPoint *>(pts), count, isClosed, static_cast<SkPathFillType>(type), isVolatile));
}

sk_path_t SkPath_Polygon_2(const void *list, bool isClosed, int fillType, bool isVolatile) {
    return static_sk_path_make(SkPath::Polygon(* static_cast<const std::initializer_list<SkPoint> *>(list), isClosed, static_cast<SkPathFillType>(fillType), isVolatile));
}

sk_path_t SkPath_Line(sk_point_t a, sk_point_t b) {
    return static_sk_path_make(SkPath::Line(static_sk_point_get_entity(a), static_sk_point_get_entity(b)));
}

bool SkPath_IsLineDegenerate(const void *p1, const void *p2, bool exact) {
    return SkPath::IsLineDegenerate(* static_cast<const SkPoint *>(p1), * static_cast<const SkPoint *>(p2), exact);
}

bool SkPath_IsQuadDegenerate(const void *p1, const void *p2, const void *p3, bool exact) {
    return SkPath::IsQuadDegenerate(* static_cast<const SkPoint *>(p1), * static_cast<const SkPoint *>(p2), * static_cast<const SkPoint *>(p3), exact);
}

bool SkPath_IsCubicDegenerate(const void *p1, const void *p2, const void *p3, const void *p4, bool exact) {
    return SkPath::IsCubicDegenerate(* static_cast<const SkPoint *>(p1), * static_cast<const SkPoint *>(p2), * static_cast<const SkPoint *>(p3), * static_cast<const SkPoint *>(p4), exact);
}

int SkPath_ConvertConicToQuads(const void *p0, const void *p1, const void *p2, float w, void * pts, int pow2) {
    return SkPath::ConvertConicToQuads(* static_cast<const SkPoint *>(p0), * static_cast<const SkPoint *>(p1), * static_cast<const SkPoint *>(p2), w, static_cast<SkPoint *>(pts), pow2);
}

}
