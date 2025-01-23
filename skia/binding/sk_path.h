//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_PATH_H
#define RAIA_SKIA_SK_PATH_H

#include "include/core/SkPath.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_rect.h"
#include "../static/static_sk_path.h"
#include "../static/static_sk_point.h"

extern "C" {

//SkPath & operator=(const SkPath &path)
void *SkPath_new(); // () -> SkPath *
void *SkPath_new_2(const void *path); // (const SkPath *path) -> SkPath *
void SkPath_delete(void *path); // (SkPath *path)
bool SkPath_isInterpolatable(void *path, const void *compare); // (SkPath *path, const SkPath *compare) -> bool
bool SkPath_interpolate(void *path, const void *ending, SkScalar weight, void *out); // (SkPath *path, const SkPath *ending, SkScalar weight, SkPath *out) -> bool
SkPathFillType SkPath_getFillType(void *path); // (SkPath *path) -> SkPathFillType
void SkPath_setFillType(void *path, SkPathFillType ft); // (SkPath *path, SkPathFillType ft)
bool SkPath_isInverseFillType(void *path); // (SkPath *path) -> bool
void SkPath_toggleInverseFillType(void *path); // (SkPath *path)
bool SkPath_isConvex(void *path); // (SkPath *path) -> bool
bool SkPath_isOval(void *path, void *bounds); // (SkPath *path, SkRect *bounds) -> bool
bool SkPath_isRRect(void *path, void *rrect); // (SkPath *path, SkRRect *rrect) -> bool
SkPath *SkPath_reset(void *path); // (SkPath *path) -> SkPath *
SkPath *SkPath_rewind(void *path); // (SkPath *path) -> SkPath *
bool SkPath_isEmpty(void *path); // (SkPath *path) -> bool
bool SkPath_isLastContourClosed(void *path); // (SkPath *path) -> bool
bool SkPath_isFinite(void *path); // (SkPath *path) -> bool
bool SkPath_isVolatile(void *path); // (SkPath *path) -> bool
SkPath *SkPath_setIsVolatile(void *path, bool isVolatile); // (SkPath *path, bool isVolatile) -> SkPath *
bool SkPath_isLine(void *path, void * line); // (SkPath *path, SkPoint line[2]) -> bool
int SkPath_countPoints(void *path); // (SkPath *path) -> int
sk_point_t SkPath_getPoint(void *path, int index); // (SkPath *path, int index) -> sk_point_t
int SkPath_getPoints(void *path, void * points, int max); // (SkPath *path, SkPoint points[], int max) -> int
int SkPath_countVerbs(void *path); // (SkPath *path) -> int
int SkPath_getVerbs(void *path, void * verbs, int max); // (SkPath *path, uint8_t verbs[], int max) -> int
size_t SkPath_approximateBytesUsed(void *path); // (SkPath *path) -> size_t
void SkPath_swap(void *path, SkPath *other); // (SkPath *path, SkPath *other)
const SkRect *SkPath_getBounds(void *path); // (SkPath *path) -> const SkRect *
void SkPath_updateBoundsCache(void *path); // (SkPath *path)
sk_rect_t SkPath_computeTightBounds(void *path); // (SkPath *path) -> sk_rect_t
bool SkPath_conservativelyContainsRect(void *path, const void *rect); // (SkPath *path, const SkRect *rect) -> bool
void SkPath_incReserve(void *path, int extraPtCount); // (SkPath *path, int extraPtCount)
SkPath *SkPath_moveTo(void *path, SkScalar x, SkScalar y); // (SkPath *path, SkScalar x, SkScalar y) -> SkPath *
SkPath *SkPath_moveTo_2(void *path, const void *p); // (SkPath *path, const SkPoint *p) -> SkPath *
SkPath *SkPath_rMoveTo(void *path, SkScalar dx, SkScalar dy); // (SkPath *path, SkScalar dx, SkScalar dy) -> SkPath *
SkPath *SkPath_lineTo(void *path, SkScalar x, SkScalar y); // (SkPath *path, SkScalar x, SkScalar y) -> SkPath *
SkPath *SkPath_lineTo_2(void *path, const void *p); // (SkPath *path, const SkPoint *p) -> SkPath *
SkPath *SkPath_rLineTo(void *path, SkScalar dx, SkScalar dy); // (SkPath *path, SkScalar dx, SkScalar dy) -> SkPath *
SkPath *SkPath_quadTo(void *path, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2); // (SkPath *path, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2) -> SkPath *
SkPath *SkPath_quadTo_2(void *path, const void *p1, const void *p2); // (SkPath *path, const SkPoint *p1, const SkPoint *p2) -> SkPath *
SkPath *SkPath_rQuadTo(void *path, SkScalar dx1, SkScalar dy1, SkScalar dx2, SkScalar dy2); // (SkPath *path, SkScalar dx1, SkScalar dy1, SkScalar dx2, SkScalar dy2) -> SkPath *
SkPath *SkPath_conicTo(void *path, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2, SkScalar w); // (SkPath *path, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2, SkScalar w) -> SkPath *
SkPath *SkPath_conicTo_2(void *path, const void *p1, const void *p2, SkScalar w); // (SkPath *path, const SkPoint *p1, const SkPoint *p2, SkScalar w) -> SkPath *
SkPath *SkPath_rConicTo(void *path, SkScalar dx1, SkScalar dy1, SkScalar dx2, SkScalar dy2, SkScalar w); // (SkPath *path, SkScalar dx1, SkScalar dy1, SkScalar dx2, SkScalar dy2, SkScalar w) -> SkPath *
SkPath *SkPath_cubicTo(void *path, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2, SkScalar x3, SkScalar y3); // (SkPath *path, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2, SkScalar x3, SkScalar y3) -> SkPath *
SkPath *SkPath_cubicTo_2(void *path, const void *p1, const void *p2, const void *p3); // (SkPath *path, const SkPoint *p1, const SkPoint *p2, const SkPoint *p3) -> SkPath *
SkPath *SkPath_rCubicTo(void *path, SkScalar dx1, SkScalar dy1, SkScalar dx2, SkScalar dy2, SkScalar dx3, SkScalar dy3); // (SkPath *path, SkScalar dx1, SkScalar dy1, SkScalar dx2, SkScalar dy2, SkScalar dx3, SkScalar dy3) -> SkPath *
SkPath *SkPath_arcTo(void *path, const void *oval, SkScalar startAngle, SkScalar sweepAngle, bool forceMoveTo); // (SkPath *path, const SkRect *oval, SkScalar startAngle, SkScalar sweepAngle, bool forceMoveTo) -> SkPath *
SkPath *SkPath_arcTo_2(void *path, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2, SkScalar radius); // (SkPath *path, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2, SkScalar radius) -> SkPath *
SkPath *SkPath_arcTo_3(void *path, sk_point_t p1, sk_point_t p2, SkScalar radius); // (SkPath *path, sk_point_t p1, sk_point_t p2, SkScalar radius) -> SkPath *
SkPath *SkPath_arcTo_4(void *path, SkScalar rx, SkScalar ry, SkScalar xAxisRotate, SkPath::ArcSize largeArc, SkPathDirection sweep, SkScalar x, SkScalar y); // (SkPath *path, SkScalar rx, SkScalar ry, SkScalar xAxisRotate, SkPath::ArcSize largeArc, SkPathDirection sweep, SkScalar x, SkScalar y) -> SkPath *
SkPath *SkPath_arcTo_5(void *path, sk_point_t r, SkScalar xAxisRotate, SkPath::ArcSize largeArc, SkPathDirection sweep, sk_point_t xy); // (SkPath *path, sk_point_t r, SkScalar xAxisRotate, SkPath::ArcSize largeArc, SkPathDirection sweep, sk_point_t xy) -> SkPath *
SkPath *SkPath_rArcTo(void *path, SkScalar rx, SkScalar ry, SkScalar xAxisRotate, SkPath::ArcSize largeArc, SkPathDirection sweep, SkScalar dx, SkScalar dy); // (SkPath *path, SkScalar rx, SkScalar ry, SkScalar xAxisRotate, SkPath::ArcSize largeArc, SkPathDirection sweep, SkScalar dx, SkScalar dy) -> SkPath *
SkPath *SkPath_close(void *path); // (SkPath *path) -> SkPath *
bool SkPath_isRect(void *path, void *rect, void *isClosed, void *direction); // (SkPath *path, SkRect *rect, bool *isClosed, SkPathDirection *direction) -> bool
SkPath *SkPath_addRect(void *path, const void *rect, SkPathDirection dir, unsigned start); // (SkPath *path, const SkRect *rect, SkPathDirection dir, unsigned start) -> SkPath *
SkPath *SkPath_addRect_2(void *path, const void *rect, SkPathDirection dir); // (SkPath *path, const SkRect *rect, SkPathDirection dir) -> SkPath *
SkPath *SkPath_addRect_3(void *path, SkScalar left, SkScalar top, SkScalar right, SkScalar bottom, SkPathDirection dir); // (SkPath *path, SkScalar left, SkScalar top, SkScalar right, SkScalar bottom, SkPathDirection dir) -> SkPath *
SkPath *SkPath_addOval(void *path, const void *oval, SkPathDirection dir); // (SkPath *path, const SkRect *oval, SkPathDirection dir) -> SkPath *
SkPath *SkPath_addOval_2(void *path, const void *oval, SkPathDirection dir, unsigned start); // (SkPath *path, const SkRect *oval, SkPathDirection dir, unsigned start) -> SkPath *
SkPath *SkPath_addCircle(void *path, SkScalar x, SkScalar y, SkScalar radius, SkPathDirection dir); // (SkPath *path, SkScalar x, SkScalar y, SkScalar radius, SkPathDirection dir) -> SkPath *
SkPath *SkPath_addArc(void *path, const void *oval, SkScalar startAngle, SkScalar sweepAngle); // (SkPath *path, const SkRect *oval, SkScalar startAngle, SkScalar sweepAngle) -> SkPath *
SkPath *SkPath_addRoundRect(void *path, const void *rect, SkScalar rx, SkScalar ry, SkPathDirection dir); // (SkPath *path, const SkRect *rect, SkScalar rx, SkScalar ry, SkPathDirection dir) -> SkPath *
SkPath *SkPath_addRoundRect_2(void *path, const void *rect, const void * radii, SkPathDirection dir); // (SkPath *path, const SkRect *rect, const SkScalar radii[], SkPathDirection dir) -> SkPath *
SkPath *SkPath_addRRect(void *path, const void *rrect, SkPathDirection dir); // (SkPath *path, const SkRRect *rrect, SkPathDirection dir) -> SkPath *
SkPath *SkPath_addRRect_2(void *path, const void *rrect, SkPathDirection dir, unsigned start); // (SkPath *path, const SkRRect *rrect, SkPathDirection dir, unsigned start) -> SkPath *
SkPath *SkPath_addPoly(void *path, const void * pts, int count, bool close); // (SkPath *path, const SkPoint pts[], int count, bool close) -> SkPath *
SkPath *SkPath_addPoly_2(void *path, const void *list, bool close); // (SkPath *path, const std::initializer_list<SkPoint> *list, bool close) -> SkPath *
SkPath *SkPath_addPath(void *path, const void *src, SkScalar dx, SkScalar dy, SkPath::AddPathMode mode); // (SkPath *path, const SkPath *src, SkScalar dx, SkScalar dy, SkPath::AddPathMode mode) -> SkPath *
SkPath *SkPath_addPath_2(void *path, const void *src, SkPath::AddPathMode modeSkPath); // (SkPath *path, const SkPath *src, SkPath::AddPathMode modeSkPath) -> SkPath *
SkPath *SkPath_addPath_3(void *path, const void *src, const void *matrix, SkPath::AddPathMode mode); // (SkPath *path, const SkPath *src, const SkMatrix *matrix, SkPath::AddPathMode mode) -> SkPath *
SkPath *SkPath_reverseAddPath(void *path, const void *src); // (SkPath *path, const SkPath *src) -> SkPath *
void SkPath_offset(void *path, SkScalar dx, SkScalar dy, void *dst); // (SkPath *path, SkScalar dx, SkScalar dy, SkPath *dst)
void SkPath_offset_2(void *path, SkScalar dx, SkScalar dy); // (SkPath *path, SkScalar dx, SkScalar dy)
void SkPath_transform(void *path, const void *matrix, void *dst, SkApplyPerspectiveClip pc); // (SkPath *path, const SkMatrix *matrix, SkPath *dst, SkApplyPerspectiveClip pc)
void SkPath_transform_2(void *path, const void *matrix, SkApplyPerspectiveClip pc); // (SkPath *path, const SkMatrix *matrix, SkApplyPerspectiveClip pc)
sk_path_t SkPath_makeTransform(void *path, const void *m, SkApplyPerspectiveClip pc); // (SkPath *path, const SkMatrix *m, SkApplyPerspectiveClip pc) -> sk_path_t
sk_path_t SkPath_makeScale(void *path, SkScalar sx, SkScalar sy); // (SkPath *path, SkScalar sx, SkScalar sy) -> sk_path_t
bool SkPath_getLastPt(void *path, void *lastPt); // (SkPath *path, SkPoint *lastPt) -> bool
void SkPath_setLastPt(void *path, SkScalar x, SkScalar y); // (SkPath *path, SkScalar x, SkScalar y)
void SkPath_setLastPt_2(void *path, const void *p); // (SkPath *path, const SkPoint *p)
uint32_t SkPath_getSegmentMasks(void *path); // (SkPath *path) -> uint32_t
bool SkPath_contains(void *path, SkScalar x, SkScalar y); // (SkPath *path, SkScalar x, SkScalar y) -> bool
void SkPath_dump(void *path, void *stream, bool dumpAsHex); // (SkPath *path, SkWStream *stream, bool dumpAsHex)
void SkPath_dump_2(void *path); // (SkPath *path)
void SkPath_dumpHex(void *path); // (SkPath *path)
void SkPath_dumpArrays(void *path, void *stream, bool dumpAsHex); // (SkPath *path, SkWStream *stream, bool dumpAsHex)
void SkPath_dumpArrays_2(void *path); // (SkPath *path)
size_t SkPath_writeToMemory(void *path, void *buffer); // (SkPath *path, void *buffer) -> size_t
sk_data_t SkPath_serialize(void *path); // (SkPath *path) -> sk_data_t
size_t SkPath_readFromMemory(void *path, const void *buffer, size_t length); // (SkPath *path, const void *buffer, size_t length) -> size_t
uint32_t SkPath_getGenerationID(void *path); // (SkPath *path) -> uint32_t
bool SkPath_isValid(void *path); // (SkPath *path) -> bool
// static
sk_path_t SkPath_Make(const void * point, int pointCount, const void * i, int verbCount, const void * v, int conicWeightCount, SkPathFillType type, bool isVolatile); // (const SkPoint point[], int pointCount, const uint8_t i[], int verbCount, const SkScalar v[], int conicWeightCount, SkPathFillType type, bool isVolatile) -> sk_path_t
sk_path_t SkPath_Rect(const void *rect, SkPathDirection dir, unsigned startIndex); // (const SkRect *rect, SkPathDirection dir, unsigned startIndex) -> sk_path_t
sk_path_t SkPath_Oval(const void *rect, SkPathDirection dir); // (const SkRect *rect, SkPathDirection dir) -> sk_path_t
sk_path_t SkPath_Oval_2(const void *rect, SkPathDirection dir, unsigned startIndex); // (const SkRect *rect, SkPathDirection dir, unsigned startIndex) -> sk_path_t
sk_path_t SkPath_Circle(SkScalar center_x, SkScalar center_y, SkScalar radius, SkPathDirection dir); // (SkScalar center_x, SkScalar center_y, SkScalar radius, SkPathDirection dir) -> sk_path_t
sk_path_t SkPath_RRect(const void *rrect, SkPathDirection dir); // (const SkRRect *rrect, SkPathDirection dir) -> sk_path_t
sk_path_t SkPath_RRect_2(const void *rrect, SkPathDirection dir, unsigned startIndex); // (const SkRRect *rrect, SkPathDirection dir, unsigned startIndex) -> sk_path_t
sk_path_t SkPath_RRect_3(const void *bounds, SkScalar rx, SkScalar ry, SkPathDirection dir); // (const SkRect *bounds, SkScalar rx, SkScalar ry, SkPathDirection dir) -> sk_path_t
sk_path_t SkPath_Polygon(const void * pts, int count, bool isClosed, SkPathFillType type, bool isVolatile); // (const SkPoint pts[], int count, bool isClosed, SkPathFillType type, bool isVolatile) -> sk_path_t
sk_path_t SkPath_Polygon_2(const void *list, bool isClosed, SkPathFillType fillType, bool isVolatile); // (const std::initializer_list<SkPoint> *list, bool isClosed, SkPathFillType fillType, bool isVolatile) -> sk_path_t
sk_path_t SkPath_Line(sk_point_t a, sk_point_t b); // (sk_point_t a, sk_point_t b) -> sk_path_t
bool SkPath_IsLineDegenerate(const void *p1, const void *p2, bool exact); // (const SkPoint *p1, const SkPoint *p2, bool exact) -> bool
bool SkPath_IsQuadDegenerate(const void *p1, const void *p2, const void *p3, bool exact); // (const SkPoint *p1, const SkPoint *p2, const SkPoint *p3, bool exact) -> bool
bool SkPath_IsCubicDegenerate(const void *p1, const void *p2, const void *p3, const void *p4, bool exact); // (const SkPoint *p1, const SkPoint *p2, const SkPoint *p3, const SkPoint *p4, bool exact) -> bool
int SkPath_ConvertConicToQuads(const void *p0, const void *p1, const void *p2, SkScalar w, void * pts, int pow2); // (const SkPoint *p0, const SkPoint *p1, const SkPoint *p2, SkScalar w, SkPoint pts[], int pow2) -> int

}

#endif //RAIA_SKIA_SK_PATH_H
