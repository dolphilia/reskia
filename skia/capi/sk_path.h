//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_PATH_H
#define RAIA_SKIA_SK_PATH_H

#include <stddef.h>
#include <stdint.h>

#include "reskia_status.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_path.h"
#include "../handles/static_sk_point.h"
#include "../handles/static_sk_rect.h"

typedef struct reskia_data_t reskia_data_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_path_t reskia_path_t;
typedef struct reskia_point_t reskia_point_t;
typedef struct reskia_r_rect_t reskia_r_rect_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_w_stream_t reskia_w_stream_t;
typedef int32_t reskia_path_fill_type_t;
typedef int32_t reskia_path_direction_t;
typedef int32_t reskia_path_perspective_clip_t;

#ifdef __cplusplus
extern "C" {
#endif

//SkPath & operator=(const SkPath &path)
reskia_path_t *SkPath_new(); // () -> SkPath *
reskia_path_t *SkPath_newCopy(const reskia_path_t *path); // (const SkPath *path) -> SkPath *
void SkPath_delete(reskia_path_t *path); // (SkPath *path)
bool SkPath_isInterpolatable(reskia_path_t *path, const reskia_path_t *compare); // (SkPath *path, const SkPath *compare) -> bool
reskia_status_t SkPath_interpolate(reskia_path_t *path, const reskia_path_t *ending, float weight, reskia_path_t *out_path); // out_path: non-null
reskia_path_fill_type_t SkPath_getFillType(reskia_path_t *path); // (SkPath *path) -> SkPathFillType
void SkPath_setFillType(reskia_path_t *path, reskia_path_fill_type_t ft); // (SkPath *path, SkPathFillType ft)
bool SkPath_isInverseFillType(reskia_path_t *path); // (SkPath *path) -> bool
void SkPath_toggleInverseFillType(reskia_path_t *path); // (SkPath *path)
bool SkPath_isConvex(reskia_path_t *path); // (SkPath *path) -> bool
bool SkPath_isOval(reskia_path_t *path, reskia_rect_t *bounds); // (SkPath *path, SkRect *bounds) -> bool
bool SkPath_isRRect(reskia_path_t *path, reskia_r_rect_t *rrect); // (SkPath *path, SkRRect *rrect) -> bool
reskia_path_t *SkPath_reset(reskia_path_t *path); // (SkPath *path) -> SkPath *
reskia_path_t *SkPath_rewind(reskia_path_t *path); // (SkPath *path) -> SkPath *
bool SkPath_isEmpty(reskia_path_t *path); // (SkPath *path) -> bool
bool SkPath_isLastContourClosed(reskia_path_t *path); // (SkPath *path) -> bool
bool SkPath_isFinite(reskia_path_t *path); // (SkPath *path) -> bool
bool SkPath_isVolatile(reskia_path_t *path); // (SkPath *path) -> bool
reskia_path_t *SkPath_setIsVolatile(reskia_path_t *path, bool isVolatile); // (SkPath *path, bool isVolatile) -> SkPath *
bool SkPath_isLine(reskia_path_t *path, reskia_point_t *line); // (SkPath *path, SkPoint line[2]) -> bool
int SkPath_countPoints(reskia_path_t *path); // (SkPath *path) -> int
sk_point_t SkPath_getPoint(reskia_path_t *path, int index); // (SkPath *path, int index) -> sk_point_t
int SkPath_getPoints(reskia_path_t *path, reskia_point_t *points, int max); // (SkPath *path, SkPoint points[], int max) -> int
int SkPath_countVerbs(reskia_path_t *path); // (SkPath *path) -> int
int SkPath_getVerbs(reskia_path_t *path, uint8_t *verbs, int max); // (SkPath *path, uint8_t verbs[], int max) -> int
size_t SkPath_approximateBytesUsed(reskia_path_t *path); // (SkPath *path) -> size_t
void SkPath_swap(reskia_path_t *path, reskia_path_t *other); // (SkPath *path, SkPath *other)
const reskia_rect_t *SkPath_getBounds(reskia_path_t *path); // (SkPath *path) -> const SkRect *
void SkPath_updateBoundsCache(reskia_path_t *path); // (SkPath *path)
sk_rect_t SkPath_computeTightBounds(reskia_path_t *path); // (SkPath *path) -> sk_rect_t
bool SkPath_conservativelyContainsRect(reskia_path_t *path, const reskia_rect_t *rect); // (SkPath *path, const SkRect *rect) -> bool
void SkPath_incReserve(reskia_path_t *path, int extraPtCount); // (SkPath *path, int extraPtCount)
reskia_path_t *SkPath_moveTo(reskia_path_t *path, float x, float y); // (SkPath *path, SkScalar x, SkScalar y) -> SkPath *
reskia_path_t *SkPath_moveToPoint(reskia_path_t *path, const reskia_point_t *p); // (SkPath *path, const SkPoint *p) -> SkPath *
reskia_path_t *SkPath_rMoveTo(reskia_path_t *path, float dx, float dy); // (SkPath *path, SkScalar dx, SkScalar dy) -> SkPath *
reskia_path_t *SkPath_lineTo(reskia_path_t *path, float x, float y); // (SkPath *path, SkScalar x, SkScalar y) -> SkPath *
reskia_path_t *SkPath_lineToPoint(reskia_path_t *path, const reskia_point_t *p); // (SkPath *path, const SkPoint *p) -> SkPath *
reskia_path_t *SkPath_rLineTo(reskia_path_t *path, float dx, float dy); // (SkPath *path, SkScalar dx, SkScalar dy) -> SkPath *
reskia_path_t *SkPath_quadTo(reskia_path_t *path, float x1, float y1, float x2, float y2); // (SkPath *path, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2) -> SkPath *
reskia_path_t *SkPath_quadToPoints(reskia_path_t *path, const reskia_point_t *p1, const reskia_point_t *p2); // (SkPath *path, const SkPoint *p1, const SkPoint *p2) -> SkPath *
reskia_path_t *SkPath_rQuadTo(reskia_path_t *path, float dx1, float dy1, float dx2, float dy2); // (SkPath *path, SkScalar dx1, SkScalar dy1, SkScalar dx2, SkScalar dy2) -> SkPath *
reskia_path_t *SkPath_conicTo(reskia_path_t *path, float x1, float y1, float x2, float y2, float w); // (SkPath *path, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2, SkScalar w) -> SkPath *
reskia_path_t *SkPath_conicToPoints(reskia_path_t *path, const reskia_point_t *p1, const reskia_point_t *p2, float w); // (SkPath *path, const SkPoint *p1, const SkPoint *p2, SkScalar w) -> SkPath *
reskia_path_t *SkPath_rConicTo(reskia_path_t *path, float dx1, float dy1, float dx2, float dy2, float w); // (SkPath *path, SkScalar dx1, SkScalar dy1, SkScalar dx2, SkScalar dy2, SkScalar w) -> SkPath *
reskia_path_t *SkPath_cubicTo(reskia_path_t *path, float x1, float y1, float x2, float y2, float x3, float y3); // (SkPath *path, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2, SkScalar x3, SkScalar y3) -> SkPath *
reskia_path_t *SkPath_cubicToPoints(reskia_path_t *path, const reskia_point_t *p1, const reskia_point_t *p2, const reskia_point_t *p3); // (SkPath *path, const SkPoint *p1, const SkPoint *p2, const SkPoint *p3) -> SkPath *
reskia_path_t *SkPath_rCubicTo(reskia_path_t *path, float dx1, float dy1, float dx2, float dy2, float dx3, float dy3); // (SkPath *path, SkScalar dx1, SkScalar dy1, SkScalar dx2, SkScalar dy2, SkScalar dx3, SkScalar dy3) -> SkPath *
reskia_path_t *SkPath_arcTo(reskia_path_t *path, const reskia_rect_t *oval, float startAngle, float sweepAngle, bool forceMoveTo); // (SkPath *path, const SkRect *oval, SkScalar startAngle, SkScalar sweepAngle, bool forceMoveTo) -> SkPath *
reskia_path_t *SkPath_arcToTangent(reskia_path_t *path, float x1, float y1, float x2, float y2, float radius); // (SkPath *path, SkScalar x1, SkScalar y1, SkScalar x2, SkScalar y2, SkScalar radius) -> SkPath *
reskia_path_t *SkPath_arcToPoints(reskia_path_t *path, int p1, int p2, float radius); // (SkPath *path, sk_point_t p1, sk_point_t p2, SkScalar radius) -> SkPath *
reskia_path_t *SkPath_arcToArcSize(reskia_path_t *path, float rx, float ry, float xAxisRotate, int largeArc, int sweep, float x, float y); // (SkPath *path, SkScalar rx, SkScalar ry, SkScalar xAxisRotate, SkPath::ArcSize largeArc, SkPathDirection sweep, SkScalar x, SkScalar y) -> SkPath *
reskia_path_t *SkPath_arcTo_5(reskia_path_t *path, int r, float xAxisRotate, int largeArc, int sweep, int xy); // (SkPath *path, sk_point_t r, SkScalar xAxisRotate, SkPath::ArcSize largeArc, SkPathDirection sweep, sk_point_t xy) -> SkPath *
reskia_path_t *SkPath_rArcTo(reskia_path_t *path, float rx, float ry, float xAxisRotate, int largeArc, int sweep, float dx, float dy); // (SkPath *path, SkScalar rx, SkScalar ry, SkScalar xAxisRotate, SkPath::ArcSize largeArc, SkPathDirection sweep, SkScalar dx, SkScalar dy) -> SkPath *
reskia_path_t *SkPath_close(reskia_path_t *path); // (SkPath *path) -> SkPath *
bool SkPath_isRect(reskia_path_t *path, reskia_rect_t *rect, bool *isClosed, int *direction); // (SkPath *path, SkRect *rect, bool *isClosed, SkPathDirection *direction) -> bool
reskia_path_t *SkPath_addRect(reskia_path_t *path, const reskia_rect_t *rect, int dir, unsigned start); // (SkPath *path, const SkRect *rect, SkPathDirection dir, unsigned start) -> SkPath *
reskia_path_t *SkPath_addRectWithDirection(reskia_path_t *path, const reskia_rect_t *rect, int dir); // (SkPath *path, const SkRect *rect, SkPathDirection dir) -> SkPath *
reskia_path_t *SkPath_addRectLTRBWithDirection(reskia_path_t *path, float left, float top, float right, float bottom, int dir); // (SkPath *path, SkScalar left, SkScalar top, SkScalar right, SkScalar bottom, SkPathDirection dir) -> SkPath *
reskia_path_t *SkPath_addOval(reskia_path_t *path, const reskia_rect_t *oval, int dir); // (SkPath *path, const SkRect *oval, SkPathDirection dir) -> SkPath *
reskia_path_t *SkPath_addOvalWithStart(reskia_path_t *path, const reskia_rect_t *oval, int dir, unsigned start); // (SkPath *path, const SkRect *oval, SkPathDirection dir, unsigned start) -> SkPath *
reskia_path_t *SkPath_addCircle(reskia_path_t *path, float x, float y, float radius, int dir); // (SkPath *path, SkScalar x, SkScalar y, SkScalar radius, SkPathDirection dir) -> SkPath *
reskia_path_t *SkPath_addArc(reskia_path_t *path, const reskia_rect_t *oval, float startAngle, float sweepAngle); // (SkPath *path, const SkRect *oval, SkScalar startAngle, SkScalar sweepAngle) -> SkPath *
reskia_path_t *SkPath_addRoundRect(reskia_path_t *path, const reskia_rect_t *rect, float rx, float ry, int dir); // (SkPath *path, const SkRect *rect, SkScalar rx, SkScalar ry, SkPathDirection dir) -> SkPath *
reskia_path_t *SkPath_addRoundRectWithRadii(reskia_path_t *path, const reskia_rect_t *rect, const float *radii, int dir); // (SkPath *path, const SkRect *rect, const SkScalar radii[], SkPathDirection dir) -> SkPath *
reskia_path_t *SkPath_addRRect(reskia_path_t *path, const reskia_r_rect_t *rrect, int dir); // (SkPath *path, const SkRRect *rrect, SkPathDirection dir) -> SkPath *
reskia_path_t *SkPath_addRRectWithStart(reskia_path_t *path, const reskia_r_rect_t *rrect, int dir, unsigned start); // (SkPath *path, const SkRRect *rrect, SkPathDirection dir, unsigned start) -> SkPath *
reskia_path_t *SkPath_addPoly(reskia_path_t *path, const reskia_point_t *pts, int count, bool close); // (SkPath *path, const SkPoint pts[], int count, bool close) -> SkPath *
reskia_path_t *SkPath_addPolyFromList(reskia_path_t *path, const void *list, bool close); // (SkPath *path, const std::initializer_list<SkPoint> *list, bool close) -> SkPath *
reskia_path_t *SkPath_addPath(reskia_path_t *path, const reskia_path_t *src, float dx, float dy, int mode); // (SkPath *path, const SkPath *src, SkScalar dx, SkScalar dy, SkPath::AddPathMode mode) -> SkPath *
reskia_path_t *SkPath_addPathWithMode(reskia_path_t *path, const reskia_path_t *src, int modeSkPath); // (SkPath *path, const SkPath *src, SkPath::AddPathMode modeSkPath) -> SkPath *
reskia_path_t *SkPath_addPathWithMatrixAndMode(reskia_path_t *path, const reskia_path_t *src, const reskia_matrix_t *matrix, int mode); // (SkPath *path, const SkPath *src, const SkMatrix *matrix, SkPath::AddPathMode mode) -> SkPath *
reskia_path_t *SkPath_reverseAddPath(reskia_path_t *path, const reskia_path_t *src); // (SkPath *path, const SkPath *src) -> SkPath *
void SkPath_offset(reskia_path_t *path, float dx, float dy, reskia_path_t *dst); // (SkPath *path, SkScalar dx, SkScalar dy, SkPath *dst)
void SkPath_offsetInPlace(reskia_path_t *path, float dx, float dy); // (SkPath *path, SkScalar dx, SkScalar dy)
void SkPath_transform(reskia_path_t *path, const reskia_matrix_t *matrix, reskia_path_t *dst, reskia_path_perspective_clip_t pc); // (SkPath *path, const SkMatrix *matrix, SkPath *dst, SkApplyPerspectiveClip pc)
void SkPath_transformInPlace(reskia_path_t *path, const reskia_matrix_t *matrix, reskia_path_perspective_clip_t pc); // (SkPath *path, const SkMatrix *matrix, SkApplyPerspectiveClip pc)
sk_path_t SkPath_makeTransform(reskia_path_t *path, const reskia_matrix_t *m, reskia_path_perspective_clip_t pc); // (SkPath *path, const SkMatrix *m, SkApplyPerspectiveClip pc) -> sk_path_t
sk_path_t SkPath_makeScale(reskia_path_t *path, float sx, float sy); // (SkPath *path, SkScalar sx, SkScalar sy) -> sk_path_t
bool SkPath_getLastPt(reskia_path_t *path, reskia_point_t *lastPt); // (SkPath *path, SkPoint *lastPt) -> bool
void SkPath_setLastPt(reskia_path_t *path, float x, float y); // (SkPath *path, SkScalar x, SkScalar y)
void SkPath_setLastPtPoint(reskia_path_t *path, const reskia_point_t *p); // (SkPath *path, const SkPoint *p)
unsigned int SkPath_getSegmentMasks(reskia_path_t *path); // (SkPath *path) -> uint32_t
bool SkPath_contains(reskia_path_t *path, float x, float y); // (SkPath *path, SkScalar x, SkScalar y) -> bool
void SkPath_dump(reskia_path_t *path, reskia_w_stream_t *stream, bool dumpAsHex); // (SkPath *path, SkWStream *stream, bool dumpAsHex)
void SkPath_dumpDefault(reskia_path_t *path); // (SkPath *path)
void SkPath_dumpHex(reskia_path_t *path); // (SkPath *path)
void SkPath_dumpArrays(reskia_path_t *path, reskia_w_stream_t *stream, bool dumpAsHex); // (SkPath *path, SkWStream *stream, bool dumpAsHex)
void SkPath_dumpArraysDefault(reskia_path_t *path); // (SkPath *path)
size_t SkPath_writeToMemory(reskia_path_t *path, void *buffer); // (SkPath *path, void *buffer) -> size_t
sk_data_t SkPath_serialize(reskia_path_t *path); // (SkPath *path) -> sk_data_t
size_t SkPath_readFromMemory(reskia_path_t *path, const void *buffer, size_t length); // (SkPath *path, const void *buffer, size_t length) -> size_t
unsigned int SkPath_getGenerationID(reskia_path_t *path); // (SkPath *path) -> uint32_t
bool SkPath_isValid(reskia_path_t *path); // (SkPath *path) -> bool

// static

sk_path_t SkPath_Make(const reskia_point_t *point, int pointCount, const uint8_t *i, int verbCount, const float *v, int conicWeightCount, reskia_path_fill_type_t type, bool isVolatile); // (const SkPoint point[], int pointCount, const uint8_t i[], int verbCount, const SkScalar v[], int conicWeightCount, SkPathFillType type, bool isVolatile) -> sk_path_t
sk_path_t SkPath_Rect(const reskia_rect_t *rect, reskia_path_direction_t dir, unsigned startIndex); // (const SkRect *rect, SkPathDirection dir, unsigned startIndex) -> sk_path_t
sk_path_t SkPath_Oval(const reskia_rect_t *rect, reskia_path_direction_t dir); // (const SkRect *rect, SkPathDirection dir) -> sk_path_t
sk_path_t SkPath_OvalWithStart(const reskia_rect_t *rect, reskia_path_direction_t dir, unsigned startIndex); // (const SkRect *rect, SkPathDirection dir, unsigned startIndex) -> sk_path_t
sk_path_t SkPath_Circle(float center_x, float center_y, float radius, reskia_path_direction_t dir); // (SkScalar center_x, SkScalar center_y, SkScalar radius, SkPathDirection dir) -> sk_path_t
sk_path_t SkPath_RRect(const reskia_r_rect_t *rrect, reskia_path_direction_t dir); // (const SkRRect *rrect, SkPathDirection dir) -> sk_path_t
sk_path_t SkPath_RRectWithStart(const reskia_r_rect_t *rrect, reskia_path_direction_t dir, unsigned startIndex); // (const SkRRect *rrect, SkPathDirection dir, unsigned startIndex) -> sk_path_t
sk_path_t SkPath_RRectFromRectAndRadii(const reskia_rect_t *bounds, float rx, float ry, reskia_path_direction_t dir); // (const SkRect *bounds, SkScalar rx, SkScalar ry, SkPathDirection dir) -> sk_path_t
sk_path_t SkPath_Polygon(const reskia_point_t *pts, int count, bool isClosed, reskia_path_fill_type_t type, bool isVolatile); // (const SkPoint pts[], int count, bool isClosed, SkPathFillType type, bool isVolatile) -> sk_path_t
sk_path_t SkPath_PolygonFromList(const void *list, bool isClosed, reskia_path_fill_type_t fillType, bool isVolatile); // (const std::initializer_list<SkPoint> *list, bool isClosed, SkPathFillType fillType, bool isVolatile) -> sk_path_t
sk_path_t SkPath_Line(sk_point_t a, sk_point_t b); // (sk_point_t a, sk_point_t b) -> sk_path_t
bool SkPath_IsLineDegenerate(const reskia_point_t *p1, const reskia_point_t *p2, bool exact); // (const SkPoint *p1, const SkPoint *p2, bool exact) -> bool
bool SkPath_IsQuadDegenerate(const reskia_point_t *p1, const reskia_point_t *p2, const reskia_point_t *p3, bool exact); // (const SkPoint *p1, const SkPoint *p2, const SkPoint *p3, bool exact) -> bool
bool SkPath_IsCubicDegenerate(const reskia_point_t *p1, const reskia_point_t *p2, const reskia_point_t *p3, const reskia_point_t *p4, bool exact); // (const SkPoint *p1, const SkPoint *p2, const SkPoint *p3, const SkPoint *p4, bool exact) -> bool
int SkPath_ConvertConicToQuads(const reskia_point_t *p0, const reskia_point_t *p1, const reskia_point_t *p2, float w, reskia_point_t *pts, int pow2); // (const SkPoint *p0, const SkPoint *p1, const SkPoint *p2, SkScalar w, SkPoint pts[], int pow2) -> int

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PATH_H
