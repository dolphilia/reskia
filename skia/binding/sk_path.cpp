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

reskia_path_t *SkPath_new() {
    return reinterpret_cast<reskia_path_t *>(new SkPath());
}

reskia_path_t *SkPath_new_2(const reskia_path_t *path) {
    return reinterpret_cast<reskia_path_t *>(new SkPath(*reinterpret_cast<const SkPath *>(path)));
}

void SkPath_delete(reskia_path_t *path) {
    delete reinterpret_cast<SkPath *>(path);
}

bool SkPath_isInterpolatable(reskia_path_t *path, const reskia_path_t *compare) {
    return reinterpret_cast<SkPath *>(path)->isInterpolatable(* reinterpret_cast<const SkPath *>(compare));
}

reskia_status_t SkPath_interpolate(reskia_path_t *path, const reskia_path_t *ending, float weight, reskia_path_t *out_path) {
    if (path == nullptr || ending == nullptr || out_path == nullptr) {
        return RESKIA_STATUS_INVALID_ARGUMENT;
    }
    const bool ok = reinterpret_cast<SkPath *>(path)->interpolate(
        *reinterpret_cast<const SkPath *>(ending),
        weight,
        reinterpret_cast<SkPath *>(out_path)
    );
    return ok ? RESKIA_STATUS_OK : RESKIA_STATUS_INTERNAL_ERROR;
}

reskia_path_fill_type_t SkPath_getFillType(reskia_path_t *path) {
    return static_cast<reskia_path_fill_type_t>(reinterpret_cast<SkPath *>(path)->getFillType());
}

void SkPath_setFillType(reskia_path_t *path, reskia_path_fill_type_t ft) {
    reinterpret_cast<SkPath *>(path)->setFillType(static_cast<SkPathFillType>(ft));
}

bool SkPath_isInverseFillType(reskia_path_t *path) {
    return reinterpret_cast<SkPath *>(path)->isInverseFillType();
}

void SkPath_toggleInverseFillType(reskia_path_t *path) {
    reinterpret_cast<SkPath *>(path)->toggleInverseFillType();
}

bool SkPath_isConvex(reskia_path_t *path) {
    return reinterpret_cast<SkPath *>(path)->isConvex();
}

bool SkPath_isOval(reskia_path_t *path, reskia_rect_t *bounds) {
    return reinterpret_cast<SkPath *>(path)->isOval(reinterpret_cast<SkRect *>(bounds));
}

bool SkPath_isRRect(reskia_path_t *path, reskia_r_rect_t *rrect) {
    return reinterpret_cast<SkPath *>(path)->isRRect(reinterpret_cast<SkRRect *>(rrect));
}

reskia_path_t *SkPath_reset(reskia_path_t *path) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->reset());
}

reskia_path_t *SkPath_rewind(reskia_path_t *path) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->rewind());
}

bool SkPath_isEmpty(reskia_path_t *path) {
    return reinterpret_cast<SkPath *>(path)->isEmpty();
}

bool SkPath_isLastContourClosed(reskia_path_t *path) {
    return reinterpret_cast<SkPath *>(path)->isLastContourClosed();
}

bool SkPath_isFinite(reskia_path_t *path) {
    return reinterpret_cast<SkPath *>(path)->isFinite();
}

bool SkPath_isVolatile(reskia_path_t *path) {
    return reinterpret_cast<SkPath *>(path)->isVolatile();
}

reskia_path_t *SkPath_setIsVolatile(reskia_path_t *path, bool isVolatile) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->setIsVolatile(isVolatile));
}

bool SkPath_isLine(reskia_path_t *path, reskia_point_t *line) {
    return reinterpret_cast<SkPath *>(path)->isLine(reinterpret_cast<SkPoint *>(line));
}

int SkPath_countPoints(reskia_path_t *path) {
    return reinterpret_cast<SkPath *>(path)->countPoints();
}

sk_point_t SkPath_getPoint(reskia_path_t *path, int index) {
    return static_sk_point_make(reinterpret_cast<SkPath *>(path)->getPoint(index));
}

int SkPath_getPoints(reskia_path_t *path, reskia_point_t *points, int max) {
    return reinterpret_cast<SkPath *>(path)->getPoints(reinterpret_cast<SkPoint *>(points), max);
}

int SkPath_countVerbs(reskia_path_t *path) {
    return reinterpret_cast<SkPath *>(path)->countVerbs();
}

int SkPath_getVerbs(reskia_path_t *path, uint8_t *verbs, int max) {
    return reinterpret_cast<SkPath *>(path)->getVerbs(reinterpret_cast<uint8_t *>(verbs), max);
}

size_t SkPath_approximateBytesUsed(reskia_path_t *path) {
    return reinterpret_cast<SkPath *>(path)->approximateBytesUsed();
}

void SkPath_swap(reskia_path_t *path, reskia_path_t *other) {
    reinterpret_cast<SkPath *>(path)->swap(* reinterpret_cast<SkPath *>(other));
}

const reskia_rect_t *SkPath_getBounds(reskia_path_t *path) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<const reskia_rect_t *>(&p->getBounds());
}

void SkPath_updateBoundsCache(reskia_path_t *path) {
    reinterpret_cast<SkPath *>(path)->updateBoundsCache();
}

sk_rect_t SkPath_computeTightBounds(reskia_path_t *path) {
    return static_sk_rect_make(reinterpret_cast<SkPath *>(path)->computeTightBounds());
}

bool SkPath_conservativelyContainsRect(reskia_path_t *path, const reskia_rect_t *rect) {
    return reinterpret_cast<SkPath *>(path)->conservativelyContainsRect(* reinterpret_cast<const SkRect *>(rect));
}

void SkPath_incReserve(reskia_path_t *path, int extraPtCount) {
    reinterpret_cast<SkPath *>(path)->incReserve(extraPtCount);
}

reskia_path_t *SkPath_moveTo(reskia_path_t *path, float x, float y) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->moveTo(x, y));
}

reskia_path_t *SkPath_moveTo_2(reskia_path_t *path, const reskia_point_t *p) {
    auto *_path = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&_path->moveTo(* reinterpret_cast<const SkPoint *>(p)));
}

reskia_path_t *SkPath_rMoveTo(reskia_path_t *path, float dx, float dy) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->rMoveTo(dx, dy));
}

reskia_path_t *SkPath_lineTo(reskia_path_t *path, float x, float y) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->lineTo(x, y));
}

reskia_path_t *SkPath_lineTo_2(reskia_path_t *path, const reskia_point_t *p) {
    auto *_path = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&_path->lineTo(* reinterpret_cast<const SkPoint *>(p)));
}

reskia_path_t *SkPath_rLineTo(reskia_path_t *path, float dx, float dy) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->rLineTo(dx, dy));
}

reskia_path_t *SkPath_quadTo(reskia_path_t *path, float x1, float y1, float x2, float y2) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->quadTo(x1, y1, x2, y2));
}

reskia_path_t *SkPath_quadTo_2(reskia_path_t *path, const reskia_point_t *p1, const reskia_point_t *p2) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->quadTo(* reinterpret_cast<const SkPoint *>(p1), * reinterpret_cast<const SkPoint *>(p2)));
}

reskia_path_t *SkPath_rQuadTo(reskia_path_t *path, float dx1, float dy1, float dx2, float dy2) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->rQuadTo(dx1, dy1, dx2, dy2));
}

reskia_path_t *SkPath_conicTo(reskia_path_t *path, float x1, float y1, float x2, float y2, float w) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->conicTo(x1, y1, x2, y2, w));
}

reskia_path_t *SkPath_conicTo_2(reskia_path_t *path, const reskia_point_t *p1, const reskia_point_t *p2, float w) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->conicTo(* reinterpret_cast<const SkPoint *>(p1), * reinterpret_cast<const SkPoint *>(p2), w));
}

reskia_path_t *SkPath_rConicTo(reskia_path_t *path, float dx1, float dy1, float dx2, float dy2, float w) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->rConicTo(dx1, dy1, dx2, dy2, w));
}

reskia_path_t *SkPath_cubicTo(reskia_path_t *path, float x1, float y1, float x2, float y2, float x3, float y3) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->cubicTo(x1, y1, x2, y2, x3, y3));
}

reskia_path_t *SkPath_cubicTo_2(reskia_path_t *path, const reskia_point_t *p1, const reskia_point_t *p2, const reskia_point_t *p3) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->cubicTo(* reinterpret_cast<const SkPoint *>(p1), * reinterpret_cast<const SkPoint *>(p2), * reinterpret_cast<const SkPoint *>(p3)));
}

reskia_path_t *SkPath_rCubicTo(reskia_path_t *path, float dx1, float dy1, float dx2, float dy2, float dx3, float dy3) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->rCubicTo(dx1, dy1, dx2, dy2, dx3, dy3));
}

reskia_path_t *SkPath_arcTo(reskia_path_t *path, const reskia_rect_t *oval, float startAngle, float sweepAngle, bool forceMoveTo) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->arcTo(* reinterpret_cast<const SkRect *>(oval), startAngle, sweepAngle, forceMoveTo));
}

reskia_path_t *SkPath_arcTo_2(reskia_path_t *path, float x1, float y1, float x2, float y2, float radius) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->arcTo(x1, y1, x2, y2, radius));
}

reskia_path_t *SkPath_arcTo_3(reskia_path_t *path, sk_point_t p1, sk_point_t p2, float radius) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->arcTo(static_sk_point_get_entity(p1), static_sk_point_get_entity(p2), radius));
}

reskia_path_t *SkPath_arcTo_4(reskia_path_t *path, float rx, float ry, float xAxisRotate, int largeArc, int sweep, float x, float y) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->arcTo(rx, ry, xAxisRotate, static_cast<SkPath::ArcSize>(largeArc), static_cast<SkPathDirection>(sweep), x, y));
}

reskia_path_t *SkPath_arcTo_5(reskia_path_t *path, sk_point_t r, float xAxisRotate, int largeArc, int sweep, sk_point_t xy) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->arcTo(static_sk_point_get_entity(r), xAxisRotate, static_cast<SkPath::ArcSize>(largeArc), static_cast<SkPathDirection>(sweep), static_sk_point_get_entity(xy)));
}

reskia_path_t *SkPath_rArcTo(reskia_path_t *path, float rx, float ry, float xAxisRotate, int largeArc, int sweep, float dx, float dy) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->arcTo(rx, ry, xAxisRotate, static_cast<SkPath::ArcSize>(largeArc), static_cast<SkPathDirection>(sweep), dx, dy));
}

reskia_path_t *SkPath_close(reskia_path_t *path) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->close());
}

bool SkPath_isRect(reskia_path_t *path, reskia_rect_t *rect, bool *isClosed, int *direction) {
    return reinterpret_cast<SkPath *>(path)->isRect(
        reinterpret_cast<SkRect *>(rect),
        isClosed,
        reinterpret_cast<SkPathDirection *>(direction));
}

reskia_path_t *SkPath_addRect(reskia_path_t *path, const reskia_rect_t *rect, int dir, unsigned start) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->addRect(* reinterpret_cast<const SkRect *>(rect), static_cast<SkPathDirection>(dir), start));
}

reskia_path_t *SkPath_addRect_2(reskia_path_t *path, const reskia_rect_t *rect, int dir) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->addRect(* reinterpret_cast<const SkRect *>(rect), static_cast<SkPathDirection>(dir)));
}

reskia_path_t *SkPath_addRect_3(reskia_path_t *path, float left, float top, float right, float bottom, int dir) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->addRect(left, top, right, bottom, static_cast<SkPathDirection>(dir)));
}

reskia_path_t *SkPath_addOval(reskia_path_t *path, const reskia_rect_t *oval, int dir) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->addOval(* reinterpret_cast<const SkRect *>(oval), static_cast<SkPathDirection>(dir)));
}

reskia_path_t *SkPath_addOval_2(reskia_path_t *path, const reskia_rect_t *oval, int dir, unsigned start) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->addOval(* reinterpret_cast<const SkRect *>(oval), static_cast<SkPathDirection>(dir), start));
}

reskia_path_t *SkPath_addCircle(reskia_path_t *path, float x, float y, float radius, int dir) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->addCircle(x, y, radius, static_cast<SkPathDirection>(dir)));
}

reskia_path_t *SkPath_addArc(reskia_path_t *path, const reskia_rect_t *oval, float startAngle, float sweepAngle) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->addArc(* reinterpret_cast<const SkRect *>(oval), startAngle, sweepAngle));
}

reskia_path_t *SkPath_addRoundRect(reskia_path_t *path, const reskia_rect_t *rect, float rx, float ry, int dir) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->addRoundRect(* reinterpret_cast<const SkRect *>(rect), rx, ry, static_cast<SkPathDirection>(dir)));
}

reskia_path_t *SkPath_addRoundRect_2(reskia_path_t *path, const reskia_rect_t *rect, const float *radii, int dir) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->addRoundRect(* reinterpret_cast<const SkRect *>(rect), reinterpret_cast<const SkScalar *>(radii), static_cast<SkPathDirection>(dir)));
}

reskia_path_t *SkPath_addRRect(reskia_path_t *path, const reskia_r_rect_t *rrect, int dir) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->addRRect(* reinterpret_cast<const SkRRect *>(rrect), static_cast<SkPathDirection>(dir)));
}

reskia_path_t *SkPath_addRRect_2(reskia_path_t *path, const reskia_r_rect_t *rrect, int dir, unsigned start) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->addRRect(* reinterpret_cast<const SkRRect *>(rrect), static_cast<SkPathDirection>(dir), start));
}

reskia_path_t *SkPath_addPoly(reskia_path_t *path, const reskia_point_t *pts, int count, bool close) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->addPoly(reinterpret_cast<const SkPoint *>(pts), count, close));
}

reskia_path_t *SkPath_addPoly_2(reskia_path_t *path, const void *list, bool close) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->addPoly(* reinterpret_cast<const std::initializer_list<SkPoint> *>(list), close));
}

reskia_path_t *SkPath_addPath(reskia_path_t *path, const reskia_path_t *src, float dx, float dy, int mode) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->addPath(* reinterpret_cast<const SkPath *>(src), dx, dy, static_cast<SkPath::AddPathMode>(mode)));
}

reskia_path_t *SkPath_addPath_2(reskia_path_t *path, const reskia_path_t *src, int modeSkPath) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->addPath(* reinterpret_cast<const SkPath *>(src), static_cast<SkPath::AddPathMode>(modeSkPath)));
}

reskia_path_t *SkPath_addPath_3(reskia_path_t *path, const reskia_path_t *src, const reskia_matrix_t *matrix, int mode) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->addPath(* reinterpret_cast<const SkPath *>(src), * reinterpret_cast<const SkMatrix *>(matrix), static_cast<SkPath::AddPathMode>(mode)));
}

reskia_path_t *SkPath_reverseAddPath(reskia_path_t *path, const reskia_path_t *src) {
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->reverseAddPath(* reinterpret_cast<const SkPath *>(src)));
}

void SkPath_offset(reskia_path_t *path, float dx, float dy, reskia_path_t *dst) {
    reinterpret_cast<SkPath *>(path)->offset(dx, dy, reinterpret_cast<SkPath *>(dst));
}

void SkPath_offset_2(reskia_path_t *path, float dx, float dy) {
    reinterpret_cast<SkPath *>(path)->offset(dx, dy);
}

void SkPath_transform(reskia_path_t *path, const reskia_matrix_t *matrix, reskia_path_t *dst, reskia_path_perspective_clip_t pc) {
    reinterpret_cast<SkPath *>(path)->transform(* reinterpret_cast<const SkMatrix *>(matrix), reinterpret_cast<SkPath *>(dst), static_cast<SkApplyPerspectiveClip>(pc));
}

void SkPath_transform_2(reskia_path_t *path, const reskia_matrix_t *matrix, reskia_path_perspective_clip_t pc) {
    reinterpret_cast<SkPath *>(path)->transform(* reinterpret_cast<const SkMatrix *>(matrix), static_cast<SkApplyPerspectiveClip>(pc));
}

sk_path_t SkPath_makeTransform(reskia_path_t *path, const reskia_matrix_t *m, reskia_path_perspective_clip_t pc) {
    return static_sk_path_make(reinterpret_cast<SkPath *>(path)->makeTransform(* reinterpret_cast<const SkMatrix *>(m), static_cast<SkApplyPerspectiveClip>(pc)));
}

sk_path_t SkPath_makeScale(reskia_path_t *path, float sx, float sy) {
    return static_sk_path_make(reinterpret_cast<SkPath *>(path)->makeScale(sx, sy));
}

bool SkPath_getLastPt(reskia_path_t *path, reskia_point_t *lastPt) {
    return reinterpret_cast<SkPath *>(path)->getLastPt(reinterpret_cast<SkPoint *>(lastPt));
}

void SkPath_setLastPt(reskia_path_t *path, float x, float y) {
    reinterpret_cast<SkPath *>(path)->setLastPt(x, y);
}

void SkPath_setLastPt_2(reskia_path_t *path, const reskia_point_t *p) {
    reinterpret_cast<SkPath *>(path)->setLastPt(* reinterpret_cast<const SkPoint *>(p));
}

uint32_t SkPath_getSegmentMasks(reskia_path_t *path) {
    return reinterpret_cast<SkPath *>(path)->getSegmentMasks();
}

bool SkPath_contains(reskia_path_t *path, float x, float y) {
    return reinterpret_cast<SkPath *>(path)->contains(x, y);
}

void SkPath_dump(reskia_path_t *path, reskia_w_stream_t *stream, bool dumpAsHex) {
    reinterpret_cast<SkPath *>(path)->dump(reinterpret_cast<SkWStream *>(stream), dumpAsHex);
}

void SkPath_dump_2(reskia_path_t *path) {
    reinterpret_cast<SkPath *>(path)->dump();
}

void SkPath_dumpHex(reskia_path_t *path) {
    reinterpret_cast<SkPath *>(path)->dumpHex();
}

void SkPath_dumpArrays(reskia_path_t *path, reskia_w_stream_t *stream, bool dumpAsHex) {
    reinterpret_cast<SkPath *>(path)->dumpArrays(reinterpret_cast<SkWStream *>(stream), dumpAsHex);
}

void SkPath_dumpArrays_2(reskia_path_t *path) {
    reinterpret_cast<SkPath *>(path)->dumpArrays();
}

size_t SkPath_writeToMemory(reskia_path_t *path, void *buffer) {
    return reinterpret_cast<SkPath *>(path)->writeToMemory(buffer);
}

sk_data_t SkPath_serialize(reskia_path_t *path) {
    return static_sk_data_make(reinterpret_cast<SkPath *>(path)->serialize());
}

size_t SkPath_readFromMemory(reskia_path_t *path, const void *buffer, size_t length) {
    return reinterpret_cast<SkPath *>(path)->readFromMemory(buffer, length);
}

uint32_t SkPath_getGenerationID(reskia_path_t *path) {
    return reinterpret_cast<SkPath *>(path)->getGenerationID();
}

bool SkPath_isValid(reskia_path_t *path) {
    return reinterpret_cast<SkPath *>(path)->isValid();
}


// static

sk_path_t SkPath_Make(const reskia_point_t *point, int pointCount, const uint8_t *i, int verbCount, const float *v, int conicWeightCount, reskia_path_fill_type_t type, bool isVolatile) {
    return static_sk_path_make(SkPath::Make(reinterpret_cast<const SkPoint *>(point), pointCount, reinterpret_cast<const uint8_t *>(i), verbCount, reinterpret_cast<const SkScalar *>(v), conicWeightCount, static_cast<SkPathFillType>(type), isVolatile));
}

sk_path_t SkPath_Rect(const reskia_rect_t *rect, reskia_path_direction_t dir, unsigned startIndex) {
    return static_sk_path_make(SkPath::Rect(* reinterpret_cast<const SkRect *>(rect), static_cast<SkPathDirection>(dir), startIndex));
}

sk_path_t SkPath_Oval(const reskia_rect_t *rect, reskia_path_direction_t dir) {
    return static_sk_path_make(SkPath::Oval(* reinterpret_cast<const SkRect *>(rect), static_cast<SkPathDirection>(dir)));
}

sk_path_t SkPath_Oval_2(const reskia_rect_t *rect, reskia_path_direction_t dir, unsigned startIndex) {
    return static_sk_path_make(SkPath::Oval(* reinterpret_cast<const SkRect *>(rect), static_cast<SkPathDirection>(dir), startIndex));
}

sk_path_t SkPath_Circle(float center_x, float center_y, float radius, reskia_path_direction_t dir) {
    return static_sk_path_make(SkPath::Circle(center_x, center_y, radius, static_cast<SkPathDirection>(dir)));
}

sk_path_t SkPath_RRect(const reskia_r_rect_t *rrect, reskia_path_direction_t dir) {
    return static_sk_path_make(SkPath::RRect(* reinterpret_cast<const SkRRect *>(rrect), static_cast<SkPathDirection>(dir)));
}

sk_path_t SkPath_RRect_2(const reskia_r_rect_t *rrect, reskia_path_direction_t dir, unsigned startIndex) {
    return static_sk_path_make(SkPath::RRect(* reinterpret_cast<const SkRRect *>(rrect), static_cast<SkPathDirection>(dir), startIndex));
}

sk_path_t SkPath_RRect_3(const reskia_rect_t *bounds, float rx, float ry, reskia_path_direction_t dir) {
    return static_sk_path_make(SkPath::RRect(* reinterpret_cast<const SkRect *>(bounds), rx, ry, static_cast<SkPathDirection>(dir)));
}

sk_path_t SkPath_Polygon(const reskia_point_t *pts, int count, bool isClosed, reskia_path_fill_type_t type, bool isVolatile) {
    return static_sk_path_make(SkPath::Polygon(reinterpret_cast<const SkPoint *>(pts), count, isClosed, static_cast<SkPathFillType>(type), isVolatile));
}

sk_path_t SkPath_Polygon_2(const void *list, bool isClosed, reskia_path_fill_type_t fillType, bool isVolatile) {
    return static_sk_path_make(SkPath::Polygon(* reinterpret_cast<const std::initializer_list<SkPoint> *>(list), isClosed, static_cast<SkPathFillType>(fillType), isVolatile));
}

sk_path_t SkPath_Line(sk_point_t a, sk_point_t b) {
    return static_sk_path_make(SkPath::Line(static_sk_point_get_entity(a), static_sk_point_get_entity(b)));
}

bool SkPath_IsLineDegenerate(const reskia_point_t *p1, const reskia_point_t *p2, bool exact) {
    return SkPath::IsLineDegenerate(* reinterpret_cast<const SkPoint *>(p1), * reinterpret_cast<const SkPoint *>(p2), exact);
}

bool SkPath_IsQuadDegenerate(const reskia_point_t *p1, const reskia_point_t *p2, const reskia_point_t *p3, bool exact) {
    return SkPath::IsQuadDegenerate(* reinterpret_cast<const SkPoint *>(p1), * reinterpret_cast<const SkPoint *>(p2), * reinterpret_cast<const SkPoint *>(p3), exact);
}

bool SkPath_IsCubicDegenerate(const reskia_point_t *p1, const reskia_point_t *p2, const reskia_point_t *p3, const reskia_point_t *p4, bool exact) {
    return SkPath::IsCubicDegenerate(* reinterpret_cast<const SkPoint *>(p1), * reinterpret_cast<const SkPoint *>(p2), * reinterpret_cast<const SkPoint *>(p3), * reinterpret_cast<const SkPoint *>(p4), exact);
}

int SkPath_ConvertConicToQuads(const reskia_point_t *p0, const reskia_point_t *p1, const reskia_point_t *p2, float w, reskia_point_t *pts, int pow2) {
    return SkPath::ConvertConicToQuads(* reinterpret_cast<const SkPoint *>(p0), * reinterpret_cast<const SkPoint *>(p1), * reinterpret_cast<const SkPoint *>(p2), w, reinterpret_cast<SkPoint *>(pts), pow2);
}

}
