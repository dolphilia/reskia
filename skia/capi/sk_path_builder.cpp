//
// Created by dolphilia on 2024/01/09.
//

#include "sk_path_builder.h"

#include "include/core/SkMatrix.h"
#include "include/core/SkPathBuilder.h"

#include <initializer_list>

#include "../handles/static_sk_path.h"
#include "../handles/static_sk_point.h"
#include "../handles/static_sk_rect.h"

#include "../handles/static_sk_path-internal.h"
#include "../handles/static_sk_point-internal.h"
#include "../handles/static_sk_rect-internal.h"

namespace {

SkPathBuilder *as_builder(reskia_path_builder_t *path_builder) {
    return reinterpret_cast<SkPathBuilder *>(path_builder);
}

const SkPathBuilder *as_builder(const reskia_path_builder_t *path_builder) {
    return reinterpret_cast<const SkPathBuilder *>(path_builder);
}

reskia_path_builder_t *to_api(SkPathBuilder *path_builder) {
    return reinterpret_cast<reskia_path_builder_t *>(path_builder);
}

const SkPath *as_path(const reskia_path_t *path) {
    return reinterpret_cast<const SkPath *>(path);
}

const SkRect *as_rect(const reskia_rect_t *rect) {
    return reinterpret_cast<const SkRect *>(rect);
}

const SkRRect *as_rrect(const reskia_r_rect_t *rrect) {
    return reinterpret_cast<const SkRRect *>(rrect);
}

reskia_path_builder_t *return_self_or_null(SkPathBuilder *path_builder) {
    return path_builder != nullptr ? to_api(path_builder) : nullptr;
}

} // namespace

extern "C" {

// SkPathBuilder & operator=(const SkPath &)
// SkPathBuilder & operator=(const SkPathBuilder &)

reskia_path_builder_t *SkPathBuilder_new() {
    return reinterpret_cast<reskia_path_builder_t *>(new SkPathBuilder());
}

reskia_path_builder_t *SkPathBuilder_newWithFillType(int type) {
    return reinterpret_cast<reskia_path_builder_t *>(new SkPathBuilder(static_cast<SkPathFillType>(type)));
}

reskia_path_builder_t *SkPathBuilder_newFromPath(const reskia_path_t *path) {
    const SkPath *native = as_path(path);
    return native != nullptr ? reinterpret_cast<reskia_path_builder_t *>(new SkPathBuilder(*native)) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_newCopy(const reskia_path_builder_t *builder) {
    const SkPathBuilder *native = as_builder(builder);
    return native != nullptr ? reinterpret_cast<reskia_path_builder_t *>(new SkPathBuilder(*native)) : nullptr;
}

void SkPathBuilder_delete(reskia_path_builder_t *path_builder) {
    delete as_builder(path_builder);
}

reskia_path_builder_fill_type_t SkPathBuilder_fillType(reskia_path_builder_t *path_builder) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? static_cast<reskia_path_builder_fill_type_t>(native->fillType()) : 0;
}

sk_rect_t SkPathBuilder_computeBounds(reskia_path_builder_t *path_builder) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? static_sk_rect_make(native->computeBounds()) : 0;
}

sk_path_t SkPathBuilder_snapshot(reskia_path_builder_t *path_builder) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? static_sk_path_make(native->snapshot()) : 0;
}

sk_path_t SkPathBuilder_detach(reskia_path_builder_t *path_builder) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? static_sk_path_make(native->detach()) : 0;
}

reskia_path_builder_t *SkPathBuilder_setFillType(reskia_path_builder_t *path_builder, int ft) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->setFillType(static_cast<SkPathFillType>(ft))) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_setIsVolatile(reskia_path_builder_t *path_builder, bool isVolatile) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->setIsVolatile(isVolatile)) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_reset(reskia_path_builder_t *path_builder) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->reset()) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_moveTo(reskia_path_builder_t *path_builder, sk_point_t pt) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->moveTo(static_sk_point_get_entity(pt))) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_moveToPoint(reskia_path_builder_t *path_builder, float x, float y) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->moveTo(x, y)) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_lineTo(reskia_path_builder_t *path_builder, sk_point_t pt) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->lineTo(static_sk_point_get_entity(pt))) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_lineToPoint(reskia_path_builder_t *path_builder, float x, float y) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->lineTo(x, y)) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_quadTo(reskia_path_builder_t *path_builder, sk_point_t pt1, sk_point_t pt2) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->quadTo(static_sk_point_get_entity(pt1), static_sk_point_get_entity(pt2))) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_quadToCoordinates(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->quadTo(x1, y1, x2, y2)) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_quadToPointArray(reskia_path_builder_t *path_builder, const reskia_point_t *pts) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr && pts != nullptr ? to_api(&native->quadTo(reinterpret_cast<const SkPoint *>(pts))) : return_self_or_null(native);
}

reskia_path_builder_t *SkPathBuilder_conicTo(reskia_path_builder_t *path_builder, sk_point_t pt1, sk_point_t pt2, float w) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->conicTo(static_sk_point_get_entity(pt1), static_sk_point_get_entity(pt2), w)) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_conicToCoordinates(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2, float w) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->conicTo(x1, y1, x2, y2, w)) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_conicToPointArray(reskia_path_builder_t *path_builder, const reskia_point_t *pts, float w) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr && pts != nullptr ? to_api(&native->conicTo(reinterpret_cast<const SkPoint *>(pts), w)) : return_self_or_null(native);
}

reskia_path_builder_t *SkPathBuilder_cubicTo(reskia_path_builder_t *path_builder, sk_point_t pt1, sk_point_t pt2, sk_point_t pt3) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->cubicTo(static_sk_point_get_entity(pt1), static_sk_point_get_entity(pt2), static_sk_point_get_entity(pt3))) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_cubicToCoordinates(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2, float x3, float y3) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->cubicTo(x1, y1, x2, y2, x3, y3)) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_cubicToPointArray(reskia_path_builder_t *path_builder, const reskia_point_t *pts) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr && pts != nullptr ? to_api(&native->cubicTo(reinterpret_cast<const SkPoint *>(pts))) : return_self_or_null(native);
}

reskia_path_builder_t *SkPathBuilder_close(reskia_path_builder_t *path_builder) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->close()) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_polylineTo(reskia_path_builder_t *path_builder, const reskia_point_t *pts, int count) {
    SkPathBuilder *native = as_builder(path_builder);
    if (native == nullptr) {
        return nullptr;
    }
    if (pts == nullptr || count <= 0) {
        return to_api(native);
    }
    return to_api(&native->polylineTo(
            {reinterpret_cast<const SkPoint *>(pts), static_cast<size_t>(count)}));
}

reskia_path_builder_t *SkPathBuilder_polylineToFromList(reskia_path_builder_t *path_builder, const void *list) {
    SkPathBuilder *native = as_builder(path_builder);
    if (native == nullptr) {
        return nullptr;
    }
    if (list == nullptr) {
        return to_api(native);
    }
    return to_api(&native->polylineTo(*reinterpret_cast<const std::initializer_list<SkPoint> *>(list)));
}

reskia_path_builder_t *SkPathBuilder_rLineTo(reskia_path_builder_t *path_builder, sk_point_t pt) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->rLineTo(static_sk_point_get_entity(pt))) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_rLineToPoint(reskia_path_builder_t *path_builder, float x, float y) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->rLineTo(x, y)) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_rQuadTo(reskia_path_builder_t *path_builder, sk_point_t pt1, sk_point_t pt2) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->rQuadTo(static_sk_point_get_entity(pt1), static_sk_point_get_entity(pt2))) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_rQuadToCoordinates(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->rQuadTo(x1, y1, x2, y2)) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_rConicTo(reskia_path_builder_t *path_builder, sk_point_t p1, sk_point_t p2, float w) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->rConicTo(static_sk_point_get_entity(p1), static_sk_point_get_entity(p2), w)) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_rConicToCoordinates(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2, float w) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->rConicTo(x1, y1, x2, y2, w)) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_rCubicTo(reskia_path_builder_t *path_builder, sk_point_t pt1, sk_point_t pt2, sk_point_t pt3) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->rCubicTo(static_sk_point_get_entity(pt1), static_sk_point_get_entity(pt2), static_sk_point_get_entity(pt3))) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_rCubicToCoordinates(reskia_path_builder_t *path_builder, float x1, float y1, float x2, float y2, float x3, float y3) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->rCubicTo(x1, y1, x2, y2, x3, y3)) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_rArcTo(reskia_path_builder_t *path_builder, float rx, float ry, float xAxisRotate, int largeArc, int sweep, float dx, float dy) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->rArcTo(rx, ry, xAxisRotate, static_cast<SkPathBuilder::ArcSize>(largeArc), static_cast<SkPathDirection>(sweep), dx, dy)) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_arcTo(reskia_path_builder_t *path_builder, const reskia_rect_t *oval, float startAngleDeg, float sweepAngleDeg, bool forceMoveTo) {
    SkPathBuilder *native = as_builder(path_builder);
    const SkRect *native_oval = as_rect(oval);
    return native != nullptr && native_oval != nullptr ? to_api(&native->arcTo(*native_oval, startAngleDeg, sweepAngleDeg, forceMoveTo)) : return_self_or_null(native);
}

reskia_path_builder_t *SkPathBuilder_arcToTangentPoints(reskia_path_builder_t *path_builder, sk_point_t p1, sk_point_t p2, float radius) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->arcTo(static_sk_point_get_entity(p1), static_sk_point_get_entity(p2), radius)) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_arcToArcSizeAndDirection(reskia_path_builder_t *path_builder, sk_point_t r, float xAxisRotate, int largeArc, int sweep, sk_point_t xy) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->arcTo(static_sk_point_get_entity(r), xAxisRotate, static_cast<SkPathBuilder::ArcSize>(largeArc), static_cast<SkPathDirection>(sweep), static_sk_point_get_entity(xy))) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_addArc(reskia_path_builder_t *path_builder, const reskia_rect_t *oval, float startAngleDeg, float sweepAngleDeg) {
    SkPathBuilder *native = as_builder(path_builder);
    const SkRect *native_oval = as_rect(oval);
    return native != nullptr && native_oval != nullptr ? to_api(&native->addArc(*native_oval, startAngleDeg, sweepAngleDeg)) : return_self_or_null(native);
}

reskia_path_builder_t *SkPathBuilder_addRect(reskia_path_builder_t *path_builder, const reskia_rect_t *rect, int dir, unsigned startIndex) {
    SkPathBuilder *native = as_builder(path_builder);
    const SkRect *native_rect = as_rect(rect);
    return native != nullptr && native_rect != nullptr ? to_api(&native->addRect(*native_rect, static_cast<SkPathDirection>(dir), startIndex)) : return_self_or_null(native);
}

reskia_path_builder_t *SkPathBuilder_addRectWithDirection(reskia_path_builder_t *path_builder, const reskia_rect_t *rect, int dir) {
    SkPathBuilder *native = as_builder(path_builder);
    const SkRect *native_rect = as_rect(rect);
    return native != nullptr && native_rect != nullptr ? to_api(&native->addRect(*native_rect, static_cast<SkPathDirection>(dir))) : return_self_or_null(native);
}

reskia_path_builder_t *SkPathBuilder_addOval(reskia_path_builder_t *path_builder, const reskia_rect_t *rect, int dir, unsigned startIndex) {
    SkPathBuilder *native = as_builder(path_builder);
    const SkRect *native_rect = as_rect(rect);
    return native != nullptr && native_rect != nullptr ? to_api(&native->addOval(*native_rect, static_cast<SkPathDirection>(dir), startIndex)) : return_self_or_null(native);
}

reskia_path_builder_t *SkPathBuilder_addOvalWithDirection(reskia_path_builder_t *path_builder, const reskia_rect_t *rect, int dir) {
    SkPathBuilder *native = as_builder(path_builder);
    const SkRect *native_rect = as_rect(rect);
    return native != nullptr && native_rect != nullptr ? to_api(&native->addOval(*native_rect, static_cast<SkPathDirection>(dir))) : return_self_or_null(native);
}

reskia_path_builder_t *SkPathBuilder_addRRect(reskia_path_builder_t *path_builder, const reskia_r_rect_t *rect, int dir, unsigned startIndex) {
    SkPathBuilder *native = as_builder(path_builder);
    const SkRRect *native_rect = as_rrect(rect);
    return native != nullptr && native_rect != nullptr ? to_api(&native->addRRect(*native_rect, static_cast<SkPathDirection>(dir), startIndex)) : return_self_or_null(native);
}

reskia_path_builder_t *SkPathBuilder_addRRectWithDirection(reskia_path_builder_t *path_builder, const reskia_r_rect_t *rrect, int dir) {
    SkPathBuilder *native = as_builder(path_builder);
    const SkRRect *native_rrect = as_rrect(rrect);
    return native != nullptr && native_rrect != nullptr ? to_api(&native->addRRect(*native_rrect, static_cast<SkPathDirection>(dir))) : return_self_or_null(native);
}

reskia_path_builder_t *SkPathBuilder_addCircle(reskia_path_builder_t *path_builder, float center_x, float center_y, float radius, int dir) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->addCircle(center_x, center_y, radius, static_cast<SkPathDirection>(dir))) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_addPolygon(reskia_path_builder_t *path_builder, const reskia_point_t *pts, int count, bool isClosed) {
    SkPathBuilder *native = as_builder(path_builder);
    if (native == nullptr) {
        return nullptr;
    }
    if (pts == nullptr || count <= 0) {
        return to_api(native);
    }
    return to_api(&native->addPolygon(
            {reinterpret_cast<const SkPoint *>(pts), static_cast<size_t>(count)},
            isClosed));
}

reskia_path_builder_t *SkPathBuilder_addPolygonFromList(reskia_path_builder_t *path_builder, const void *list, bool isClosed) {
    SkPathBuilder *native = as_builder(path_builder);
    if (native == nullptr) {
        return nullptr;
    }
    if (list == nullptr) {
        return to_api(native);
    }
    return to_api(&native->addPolygon(*reinterpret_cast<const std::initializer_list<SkPoint> *>(list), isClosed));
}

reskia_path_builder_t *SkPathBuilder_addPath(reskia_path_builder_t *path_builder, const reskia_path_t *path) {
    SkPathBuilder *native = as_builder(path_builder);
    const SkPath *native_path = as_path(path);
    return native != nullptr && native_path != nullptr ? to_api(&native->addPath(*native_path)) : return_self_or_null(native);
}

void SkPathBuilder_incReserve(reskia_path_builder_t *path_builder, int extraPtCount, int extraVerbCount) {
    SkPathBuilder *native = as_builder(path_builder);
    if (native != nullptr) {
        native->incReserve(extraPtCount, extraVerbCount);
    }
}

void SkPathBuilder_incReservePoints(reskia_path_builder_t *path_builder, int extraPtCount) {
    SkPathBuilder *native = as_builder(path_builder);
    if (native != nullptr) {
        native->incReserve(extraPtCount);
    }
}

reskia_path_builder_t *SkPathBuilder_offset(reskia_path_builder_t *path_builder, float dx, float dy) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->offset(dx, dy)) : nullptr;
}

reskia_path_builder_t *SkPathBuilder_transform(reskia_path_builder_t *path_builder, const reskia_matrix_t *matrix, int pc) {
    SkPathBuilder *native = as_builder(path_builder);
    if (native == nullptr) {
        return nullptr;
    }
    if (matrix == nullptr) {
        return to_api(native);
    }
    return to_api(&native->transform(*reinterpret_cast<const SkMatrix *>(matrix), static_cast<SkApplyPerspectiveClip>(pc)));
}

reskia_path_builder_t *SkPathBuilder_toggleInverseFillType(reskia_path_builder_t *path_builder) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? to_api(&native->toggleInverseFillType()) : nullptr;
}

bool SkPathBuilder_isEmpty(reskia_path_builder_t *path_builder) {
    SkPathBuilder *native = as_builder(path_builder);
    return native == nullptr || native->isEmpty();
}

sk_point_t SkPathBuilder_getLastPt(reskia_path_builder_t *path_builder) {
    SkPathBuilder *native = as_builder(path_builder);
    if (native == nullptr) {
        return 0;
    }
    std::optional<SkPoint> point = native->getLastPt();
    return point.has_value() ? static_sk_point_make(*point) : 0;
}

void SkPathBuilder_setLastPt(reskia_path_builder_t *path_builder, float x, float y) {
    SkPathBuilder *native = as_builder(path_builder);
    if (native != nullptr) {
        native->setLastPt(x, y);
    }
}

int SkPathBuilder_countPoints(reskia_path_builder_t *path_builder) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr ? native->countPoints() : 0;
}

bool SkPathBuilder_isInverseFillType(reskia_path_builder_t *path_builder) {
    SkPathBuilder *native = as_builder(path_builder);
    return native != nullptr && native->isInverseFillType();
}

}
