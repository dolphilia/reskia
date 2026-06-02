//
// Created by dolphilia on 2024/01/09.
//

#include "sk_path.h"
#include "sk_path_builder.h"

#include "include/core/SkArc.h"
#include "include/core/SkPath.h"
#include "include/core/SkPathBuilder.h"
#include "include/core/SkPathIter.h"
#include "include/core/SkRRect.h"
#include "include/pathops/SkPathOps.h"

#include <optional>
#include <utility>
#include <vector>

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_rect.h"
#include "../handles/static_sk_path.h"
#include "../handles/static_sk_point.h"

#include "../handles/static_sk_path-internal.h"
#include "../handles/static_sk_point-internal.h"
#include "../handles/static_sk_rect-internal.h"
#include "../handles/static_sk_data-internal.h"

namespace {

std::vector<SkPathVerb> make_verb_vector(const uint8_t *verbs, size_t verbs_count) {
    std::vector<SkPathVerb> native_verbs;
    native_verbs.reserve(verbs_count);
    for (size_t i = 0; i < verbs_count; ++i) {
        native_verbs.push_back(static_cast<SkPathVerb>(verbs[i]));
    }
    return native_verbs;
}

struct PathIterBox {
    std::vector<SkPathVerb> owned_verbs;
    SkPathIter iter;

    explicit PathIterBox(SkPathIter native_iter) : iter(std::move(native_iter)) {}

    PathIterBox(SkSpan<const SkPoint> points, const uint8_t *verbs, size_t verbs_count, SkSpan<const float> conic_weights)
            : owned_verbs(make_verb_vector(verbs, verbs_count))
            , iter(points, {owned_verbs.data(), owned_verbs.size()}, conic_weights) {}
};

struct PathContourIterBox {
    std::vector<SkPathVerb> owned_verbs;
    SkPathContourIter iter;

    PathContourIterBox(SkSpan<const SkPoint> points, const uint8_t *verbs, size_t verbs_count, SkSpan<const float> conic_weights)
            : owned_verbs(make_verb_vector(verbs, verbs_count))
            , iter(points, {owned_verbs.data(), owned_verbs.size()}, conic_weights) {}
};

PathIterBox *as_path_iter(reskia_path_iter_t *iter) {
    return reinterpret_cast<PathIterBox *>(iter);
}

const PathIterBox *as_path_iter(const reskia_path_iter_t *iter) {
    return reinterpret_cast<const PathIterBox *>(iter);
}

PathContourIterBox *as_path_contour_iter(reskia_path_contour_iter_t *iter) {
    return reinterpret_cast<PathContourIterBox *>(iter);
}

template <typename Fn>
reskia_path_t *mutate_path_with_builder(reskia_path_t *path, Fn fn) {
    if (path == nullptr) {
        return nullptr;
    }
    auto *native_path = reinterpret_cast<SkPath *>(path);
    SkPathBuilder builder(*native_path);
    fn(builder);
    *native_path = builder.detach();
    return path;
}

int path_points_in_verb(SkPathVerb verb) {
    switch (verb) {
        case SkPathVerb::kMove:  return 1;
        case SkPathVerb::kLine:  return 1;
        case SkPathVerb::kQuad:  return 2;
        case SkPathVerb::kConic: return 2;
        case SkPathVerb::kCubic: return 3;
        case SkPathVerb::kClose: return 0;
    }
    return 0;
}

void reverse_add_path(SkPathBuilder& builder, const SkPath& src) {
    std::vector<SkPathVerb> verbs(src.verbs().begin(), src.verbs().end());
    std::vector<SkPoint> points(src.points().begin(), src.points().end());
    std::vector<SkScalar> conicWeights(src.conicWeights().begin(), src.conicWeights().end());

    const SkPathVerb* verbsBegin = verbs.data();
    const SkPathVerb* verb = verbsBegin + verbs.size();
    const SkPoint* point = points.data() + points.size();
    const SkScalar* conicWeight = conicWeights.data() + conicWeights.size();

    bool needMove = true;
    bool needClose = false;
    while (verb > verbsBegin) {
        SkPathVerb currentVerb = *--verb;
        const int pointCount = path_points_in_verb(currentVerb);

        if (needMove) {
            --point;
            builder.moveTo(*point);
            needMove = false;
        }
        point -= pointCount;
        switch (currentVerb) {
            case SkPathVerb::kMove:
                if (needClose) {
                    builder.close();
                    needClose = false;
                }
                needMove = true;
                point += 1;
                break;
            case SkPathVerb::kLine:
                builder.lineTo(point[0]);
                break;
            case SkPathVerb::kQuad:
                builder.quadTo(point[1], point[0]);
                break;
            case SkPathVerb::kConic:
                builder.conicTo(point[1], point[0], *--conicWeight);
                break;
            case SkPathVerb::kCubic:
                builder.cubicTo(point[2], point[1], point[0]);
                break;
            case SkPathVerb::kClose:
                needClose = true;
                break;
        }
    }
}

bool is_valid_path_op(reskia_path_op_t op) {
    return op >= kDifference_SkPathOp && op <= kReverseDifference_SkPathOp;
}

}  // namespace

extern "C" {

reskia_path_t *SkPath_new() {
    return reinterpret_cast<reskia_path_t *>(new SkPath());
}

reskia_path_t *SkPath_newCopy(const reskia_path_t *path) {
    if (path == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_path_t *>(new SkPath(*reinterpret_cast<const SkPath *>(path)));
}

void SkPath_delete(reskia_path_t *path) {
    delete reinterpret_cast<SkPath *>(path);
}

bool SkPath_isInterpolatable(reskia_path_t *path, const reskia_path_t *compare) {
    if (path == nullptr || compare == nullptr) {
        return false;
    }
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

sk_path_t SkPath_makeInterpolate(reskia_path_t *path, const reskia_path_t *ending, float weight) {
    if (path == nullptr || ending == nullptr) {
        return 0;
    }
    return static_sk_path_make(reinterpret_cast<SkPath *>(path)->makeInterpolate(*reinterpret_cast<const SkPath *>(ending), weight));
}

reskia_path_fill_type_t SkPath_getFillType(reskia_path_t *path) {
    if (path == nullptr) {
        return 0;
    }
    return static_cast<reskia_path_fill_type_t>(reinterpret_cast<SkPath *>(path)->getFillType());
}

void SkPath_setFillType(reskia_path_t *path, reskia_path_fill_type_t ft) {
    if (path == nullptr) {
        return;
    }
    reinterpret_cast<SkPath *>(path)->setFillType(static_cast<SkPathFillType>(ft));
}

bool SkPath_isInverseFillType(reskia_path_t *path) {
    if (path == nullptr) {
        return false;
    }
    return reinterpret_cast<SkPath *>(path)->isInverseFillType();
}

void SkPath_toggleInverseFillType(reskia_path_t *path) {
    if (path == nullptr) {
        return;
    }
    reinterpret_cast<SkPath *>(path)->toggleInverseFillType();
}

sk_path_t SkPath_makeFillType(reskia_path_t *path, reskia_path_fill_type_t newFillType) {
    if (path == nullptr) {
        return 0;
    }
    return static_sk_path_make(reinterpret_cast<SkPath *>(path)->makeFillType(static_cast<SkPathFillType>(newFillType)));
}

sk_path_t SkPath_makeToggleInverseFillType(reskia_path_t *path) {
    if (path == nullptr) {
        return 0;
    }
    return static_sk_path_make(reinterpret_cast<SkPath *>(path)->makeToggleInverseFillType());
}

bool SkPath_isConvex(reskia_path_t *path) {
    if (path == nullptr) {
        return false;
    }
    return reinterpret_cast<SkPath *>(path)->isConvex();
}

bool SkPath_isOval(reskia_path_t *path, reskia_rect_t *bounds) {
    if (path == nullptr) {
        return false;
    }
    return reinterpret_cast<SkPath *>(path)->isOval(reinterpret_cast<SkRect *>(bounds));
}

bool SkPath_isRRect(reskia_path_t *path, reskia_r_rect_t *rrect) {
    if (path == nullptr) {
        return false;
    }
    return reinterpret_cast<SkPath *>(path)->isRRect(reinterpret_cast<SkRRect *>(rrect));
}

reskia_path_t *SkPath_reset(reskia_path_t *path) {
    if (path == nullptr) {
        return nullptr;
    }
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->reset());
}

reskia_path_t *SkPath_rewind(reskia_path_t *path) {
    if (path == nullptr) {
        return nullptr;
    }
    return mutate_path_with_builder(path, [](SkPathBuilder& builder) {
        builder.reset();
    });
}

sk_path_t SkPath_snapshot(reskia_path_t *path) {
    if (path == nullptr) {
        return 0;
    }
    return static_sk_path_make(reinterpret_cast<SkPath *>(path)->snapshot());
}

sk_path_t SkPath_detach(reskia_path_t *path) {
    if (path == nullptr) {
        return 0;
    }
    auto *native_path = reinterpret_cast<SkPath *>(path);
    SkPath result = *native_path;
    native_path->reset();
    return static_sk_path_make(std::move(result));
}

bool SkPath_isEmpty(reskia_path_t *path) {
    if (path == nullptr) {
        return true;
    }
    return reinterpret_cast<SkPath *>(path)->isEmpty();
}

bool SkPath_isLastContourClosed(reskia_path_t *path) {
    if (path == nullptr) {
        return false;
    }
    return reinterpret_cast<SkPath *>(path)->isLastContourClosed();
}

bool SkPath_isFinite(reskia_path_t *path) {
    if (path == nullptr) {
        return false;
    }
    return reinterpret_cast<SkPath *>(path)->isFinite();
}

bool SkPath_isVolatile(reskia_path_t *path) {
    if (path == nullptr) {
        return false;
    }
    return reinterpret_cast<SkPath *>(path)->isVolatile();
}

reskia_path_t *SkPath_setIsVolatile(reskia_path_t *path, bool isVolatile) {
    if (path == nullptr) {
        return nullptr;
    }
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<reskia_path_t *>(&p->setIsVolatile(isVolatile));
}

sk_path_t SkPath_makeIsVolatile(reskia_path_t *path, bool isVolatile) {
    if (path == nullptr) {
        return 0;
    }
    return static_sk_path_make(reinterpret_cast<SkPath *>(path)->makeIsVolatile(isVolatile));
}

bool SkPath_isLine(reskia_path_t *path, reskia_point_t *line) {
    if (path == nullptr) {
        return false;
    }
    return reinterpret_cast<SkPath *>(path)->isLine(reinterpret_cast<SkPoint *>(line));
}

int SkPath_countPoints(reskia_path_t *path) {
    if (path == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkPath *>(path)->countPoints();
}

const reskia_point_t *SkPath_points(const reskia_path_t *path, size_t *out_count) {
    if (out_count != nullptr) {
        *out_count = 0;
    }
    if (path == nullptr) {
        return nullptr;
    }
    SkSpan<const SkPoint> points = reinterpret_cast<const SkPath *>(path)->points();
    if (out_count != nullptr) {
        *out_count = points.size();
    }
    return reinterpret_cast<const reskia_point_t *>(points.data());
}

sk_point_t SkPath_getPoint(reskia_path_t *path, int index) {
    if (path == nullptr) {
        return 0;
    }
    return static_sk_point_make(reinterpret_cast<SkPath *>(path)->getPoint(index));
}

int SkPath_getPoints(reskia_path_t *path, reskia_point_t *points, int max) {
    if (path == nullptr || max < 0 || (max > 0 && points == nullptr)) {
        return 0;
    }
    return reinterpret_cast<SkPath *>(path)->getPoints(
            {reinterpret_cast<SkPoint *>(points), static_cast<size_t>(max)});
}

int SkPath_countVerbs(reskia_path_t *path) {
    if (path == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkPath *>(path)->countVerbs();
}

const uint8_t *SkPath_verbs(const reskia_path_t *path, size_t *out_count) {
    if (out_count != nullptr) {
        *out_count = 0;
    }
    if (path == nullptr) {
        return nullptr;
    }
    SkSpan<const SkPathVerb> verbs = reinterpret_cast<const SkPath *>(path)->verbs();
    if (out_count != nullptr) {
        *out_count = verbs.size();
    }
    return reinterpret_cast<const uint8_t *>(verbs.data());
}

const float *SkPath_conicWeights(const reskia_path_t *path, size_t *out_count) {
    if (out_count != nullptr) {
        *out_count = 0;
    }
    if (path == nullptr) {
        return nullptr;
    }
    SkSpan<const float> weights = reinterpret_cast<const SkPath *>(path)->conicWeights();
    if (out_count != nullptr) {
        *out_count = weights.size();
    }
    return weights.data();
}

int SkPath_getVerbs(reskia_path_t *path, uint8_t *verbs, int max) {
    if (path == nullptr || max < 0 || (max > 0 && verbs == nullptr)) {
        return 0;
    }
    return reinterpret_cast<SkPath *>(path)->getVerbs(
            {reinterpret_cast<uint8_t *>(verbs), static_cast<size_t>(max)});
}

reskia_path_iter_t *SkPath_iter(const reskia_path_t *path) {
    if (path == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_path_iter_t *>(new PathIterBox(reinterpret_cast<const SkPath *>(path)->iter()));
}

reskia_path_iter_t *SkPathBuilder_iter(const reskia_path_builder_t *path_builder) {
    if (path_builder == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_path_iter_t *>(new PathIterBox(reinterpret_cast<const SkPathBuilder *>(path_builder)->iter()));
}

size_t SkPath_approximateBytesUsed(reskia_path_t *path) {
    if (path == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkPath *>(path)->approximateBytesUsed();
}

void SkPath_swap(reskia_path_t *path, reskia_path_t *other) {
    if (path == nullptr || other == nullptr) {
        return;
    }
    reinterpret_cast<SkPath *>(path)->swap(* reinterpret_cast<SkPath *>(other));
}

const reskia_rect_t *SkPath_getBounds(reskia_path_t *path) {
    if (path == nullptr) {
        return nullptr;
    }
    auto *p = reinterpret_cast<SkPath *>(path);
    return reinterpret_cast<const reskia_rect_t *>(&p->getBounds());
}

void SkPath_updateBoundsCache(reskia_path_t *path) {
    if (path == nullptr) {
        return;
    }
    reinterpret_cast<SkPath *>(path)->updateBoundsCache();
}

sk_rect_t SkPath_computeTightBounds(reskia_path_t *path) {
    if (path == nullptr) {
        return 0;
    }
    return static_sk_rect_make(reinterpret_cast<SkPath *>(path)->computeTightBounds());
}

bool SkPath_conservativelyContainsRect(reskia_path_t *path, const reskia_rect_t *rect) {
    if (path == nullptr || rect == nullptr) {
        return false;
    }
    return reinterpret_cast<SkPath *>(path)->conservativelyContainsRect(* reinterpret_cast<const SkRect *>(rect));
}

void SkPath_incReserve(reskia_path_t *path, int extraPtCount) {
    SkPath_incReserveWithCounts(path, extraPtCount, 0, 0);
}

void SkPath_incReserveWithCounts(reskia_path_t *path, int extraPtCount, int extraVerbCount, int extraConicCount) {
    if (path == nullptr) {
        return;
    }
    mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.incReserve(extraPtCount, extraVerbCount, extraConicCount);
    });
}

reskia_path_t *SkPath_moveTo(reskia_path_t *path, float x, float y) {
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.moveTo(x, y);
    });
}

reskia_path_t *SkPath_moveToPoint(reskia_path_t *path, const reskia_point_t *p) {
    if (path == nullptr || p == nullptr) {
        return nullptr;
    }
    const SkPoint point = *reinterpret_cast<const SkPoint *>(p);
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.moveTo(point);
    });
}

reskia_path_t *SkPath_rMoveTo(reskia_path_t *path, float dx, float dy) {
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.rMoveTo(dx, dy);
    });
}

reskia_path_t *SkPath_lineTo(reskia_path_t *path, float x, float y) {
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.lineTo(x, y);
    });
}

reskia_path_t *SkPath_lineToPoint(reskia_path_t *path, const reskia_point_t *p) {
    if (path == nullptr || p == nullptr) {
        return nullptr;
    }
    const SkPoint point = *reinterpret_cast<const SkPoint *>(p);
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.lineTo(point);
    });
}

reskia_path_t *SkPath_rLineTo(reskia_path_t *path, float dx, float dy) {
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.rLineTo(dx, dy);
    });
}

reskia_path_t *SkPath_quadTo(reskia_path_t *path, float x1, float y1, float x2, float y2) {
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.quadTo(x1, y1, x2, y2);
    });
}

reskia_path_t *SkPath_quadToPoints(reskia_path_t *path, const reskia_point_t *p1, const reskia_point_t *p2) {
    if (path == nullptr || p1 == nullptr || p2 == nullptr) {
        return nullptr;
    }
    const SkPoint point1 = *reinterpret_cast<const SkPoint *>(p1);
    const SkPoint point2 = *reinterpret_cast<const SkPoint *>(p2);
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.quadTo(point1, point2);
    });
}

reskia_path_t *SkPath_rQuadTo(reskia_path_t *path, float dx1, float dy1, float dx2, float dy2) {
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.rQuadTo(dx1, dy1, dx2, dy2);
    });
}

reskia_path_t *SkPath_conicTo(reskia_path_t *path, float x1, float y1, float x2, float y2, float w) {
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.conicTo(x1, y1, x2, y2, w);
    });
}

reskia_path_t *SkPath_conicToPoints(reskia_path_t *path, const reskia_point_t *p1, const reskia_point_t *p2, float w) {
    if (path == nullptr || p1 == nullptr || p2 == nullptr) {
        return nullptr;
    }
    const SkPoint point1 = *reinterpret_cast<const SkPoint *>(p1);
    const SkPoint point2 = *reinterpret_cast<const SkPoint *>(p2);
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.conicTo(point1, point2, w);
    });
}

reskia_path_t *SkPath_rConicTo(reskia_path_t *path, float dx1, float dy1, float dx2, float dy2, float w) {
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.rConicTo(dx1, dy1, dx2, dy2, w);
    });
}

reskia_path_t *SkPath_cubicTo(reskia_path_t *path, float x1, float y1, float x2, float y2, float x3, float y3) {
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.cubicTo(x1, y1, x2, y2, x3, y3);
    });
}

reskia_path_t *SkPath_cubicToPoints(reskia_path_t *path, const reskia_point_t *p1, const reskia_point_t *p2, const reskia_point_t *p3) {
    if (path == nullptr || p1 == nullptr || p2 == nullptr || p3 == nullptr) {
        return nullptr;
    }
    const SkPoint point1 = *reinterpret_cast<const SkPoint *>(p1);
    const SkPoint point2 = *reinterpret_cast<const SkPoint *>(p2);
    const SkPoint point3 = *reinterpret_cast<const SkPoint *>(p3);
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.cubicTo(point1, point2, point3);
    });
}

reskia_path_t *SkPath_rCubicTo(reskia_path_t *path, float dx1, float dy1, float dx2, float dy2, float dx3, float dy3) {
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.rCubicTo(dx1, dy1, dx2, dy2, dx3, dy3);
    });
}

reskia_path_t *SkPath_arcTo(reskia_path_t *path, const reskia_rect_t *oval, float startAngle, float sweepAngle, bool forceMoveTo) {
    if (path == nullptr || oval == nullptr) {
        return nullptr;
    }
    const SkRect rect = *reinterpret_cast<const SkRect *>(oval);
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.arcTo(rect, startAngle, sweepAngle, forceMoveTo);
    });
}

reskia_path_t *SkPath_arcToTangent(reskia_path_t *path, float x1, float y1, float x2, float y2, float radius) {
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.arcTo(SkPoint::Make(x1, y1), SkPoint::Make(x2, y2), radius);
    });
}

reskia_path_t *SkPath_arcToPoints(reskia_path_t *path, sk_point_t p1, sk_point_t p2, float radius) {
    const SkPoint point1 = static_sk_point_get_entity(p1);
    const SkPoint point2 = static_sk_point_get_entity(p2);
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.arcTo(point1, point2, radius);
    });
}

reskia_path_t *SkPath_arcToArcSize(reskia_path_t *path, float rx, float ry, float xAxisRotate, int largeArc, int sweep, float x, float y) {
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.arcTo(SkPoint::Make(rx, ry), xAxisRotate, static_cast<SkPathBuilder::ArcSize>(largeArc), static_cast<SkPathDirection>(sweep), SkPoint::Make(x, y));
    });
}

reskia_path_t *SkPath_arcToArcSizePoints(reskia_path_t *path, sk_point_t r, float xAxisRotate, int largeArc, int sweep, sk_point_t xy) {
    const SkPoint radius = static_sk_point_get_entity(r);
    const SkPoint end = static_sk_point_get_entity(xy);
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.arcTo(radius, xAxisRotate, static_cast<SkPathBuilder::ArcSize>(largeArc), static_cast<SkPathDirection>(sweep), end);
    });
}

reskia_path_t *SkPath_rArcTo(reskia_path_t *path, float rx, float ry, float xAxisRotate, int largeArc, int sweep, float dx, float dy) {
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.rArcTo(SkPoint::Make(rx, ry), xAxisRotate, static_cast<SkPathBuilder::ArcSize>(largeArc), static_cast<SkPathDirection>(sweep), SkPoint::Make(dx, dy));
    });
}

reskia_path_t *SkPath_close(reskia_path_t *path) {
    return mutate_path_with_builder(path, [](SkPathBuilder& builder) {
        builder.close();
    });
}

bool SkPath_isRect(reskia_path_t *path, reskia_rect_t *rect, bool *isClosed, int *direction) {
    if (path == nullptr) {
        return false;
    }
    return reinterpret_cast<SkPath *>(path)->isRect(
        reinterpret_cast<SkRect *>(rect),
        isClosed,
        reinterpret_cast<SkPathDirection *>(direction));
}

reskia_path_t *SkPath_addRect(reskia_path_t *path, const reskia_rect_t *rect, int dir, unsigned start) {
    if (path == nullptr || rect == nullptr) {
        return nullptr;
    }
    const SkRect native_rect = *reinterpret_cast<const SkRect *>(rect);
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.addRect(native_rect, static_cast<SkPathDirection>(dir), start);
    });
}

reskia_path_t *SkPath_addRectWithDirection(reskia_path_t *path, const reskia_rect_t *rect, int dir) {
    if (path == nullptr || rect == nullptr) {
        return nullptr;
    }
    const SkRect native_rect = *reinterpret_cast<const SkRect *>(rect);
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.addRect(native_rect, static_cast<SkPathDirection>(dir));
    });
}

reskia_path_t *SkPath_addRectLTRBWithDirection(reskia_path_t *path, float left, float top, float right, float bottom, int dir) {
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.addRect(SkRect::MakeLTRB(left, top, right, bottom), static_cast<SkPathDirection>(dir));
    });
}

reskia_path_t *SkPath_addOval(reskia_path_t *path, const reskia_rect_t *oval, int dir) {
    if (path == nullptr || oval == nullptr) {
        return nullptr;
    }
    const SkRect native_oval = *reinterpret_cast<const SkRect *>(oval);
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.addOval(native_oval, static_cast<SkPathDirection>(dir));
    });
}

reskia_path_t *SkPath_addOvalWithStart(reskia_path_t *path, const reskia_rect_t *oval, int dir, unsigned start) {
    if (path == nullptr || oval == nullptr) {
        return nullptr;
    }
    const SkRect native_oval = *reinterpret_cast<const SkRect *>(oval);
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.addOval(native_oval, static_cast<SkPathDirection>(dir), start);
    });
}

reskia_path_t *SkPath_addCircle(reskia_path_t *path, float x, float y, float radius, int dir) {
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.addCircle(x, y, radius, static_cast<SkPathDirection>(dir));
    });
}

reskia_path_t *SkPath_addArc(reskia_path_t *path, const reskia_rect_t *oval, float startAngle, float sweepAngle) {
    if (path == nullptr || oval == nullptr) {
        return nullptr;
    }
    const SkRect native_oval = *reinterpret_cast<const SkRect *>(oval);
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.addArc(native_oval, startAngle, sweepAngle);
    });
}

reskia_path_t *SkPath_addRoundRect(reskia_path_t *path, const reskia_rect_t *rect, float rx, float ry, int dir) {
    if (path == nullptr || rect == nullptr) {
        return nullptr;
    }
    const SkRect native_rect = *reinterpret_cast<const SkRect *>(rect);
    SkRRect native_rrect;
    native_rrect.setRectXY(native_rect, rx, ry);
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.addRRect(native_rrect, static_cast<SkPathDirection>(dir));
    });
}

reskia_path_t *SkPath_addRoundRectWithRadii(reskia_path_t *path, const reskia_rect_t *rect, const float *radii, int dir) {
    if (path == nullptr || rect == nullptr || radii == nullptr) {
        return nullptr;
    }
    const SkRect native_rect = *reinterpret_cast<const SkRect *>(rect);
    SkRRect native_rrect;
    native_rrect.setRectRadii(native_rect, reinterpret_cast<const SkVector *>(radii));
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.addRRect(native_rrect, static_cast<SkPathDirection>(dir));
    });
}

reskia_path_t *SkPath_addRRect(reskia_path_t *path, const reskia_r_rect_t *rrect, int dir) {
    if (path == nullptr || rrect == nullptr) {
        return nullptr;
    }
    const SkRRect native_rrect = *reinterpret_cast<const SkRRect *>(rrect);
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.addRRect(native_rrect, static_cast<SkPathDirection>(dir));
    });
}

reskia_path_t *SkPath_addRRectWithStart(reskia_path_t *path, const reskia_r_rect_t *rrect, int dir, unsigned start) {
    if (path == nullptr || rrect == nullptr) {
        return nullptr;
    }
    const SkRRect native_rrect = *reinterpret_cast<const SkRRect *>(rrect);
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.addRRect(native_rrect, static_cast<SkPathDirection>(dir), start);
    });
}

reskia_path_t *SkPath_addPoly(reskia_path_t *path, const reskia_point_t *pts, int count, bool close) {
    if (path == nullptr || count < 0 || (count > 0 && pts == nullptr)) {
        return nullptr;
    }
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.addPolygon({reinterpret_cast<const SkPoint *>(pts), static_cast<size_t>(count)}, close);
    });
}

reskia_path_t *SkPath_addPolyFromList(reskia_path_t *path, const void *list, bool close) {
    if (path == nullptr || list == nullptr) {
        return nullptr;
    }
    const auto& points = *reinterpret_cast<const std::initializer_list<SkPoint> *>(list);
    return mutate_path_with_builder(path, [&](SkPathBuilder& builder) {
        builder.addPolygon({points.begin(), points.size()}, close);
    });
}

reskia_path_t *SkPath_addPath(reskia_path_t *path, const reskia_path_t *src, float dx, float dy, int mode) {
    if (path == nullptr || src == nullptr) {
        return nullptr;
    }
    const SkPath native_src = *reinterpret_cast<const SkPath *>(src);
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.addPath(native_src, dx, dy, static_cast<SkPath::AddPathMode>(mode));
    });
}

reskia_path_t *SkPath_addPathWithMode(reskia_path_t *path, const reskia_path_t *src, int modeSkPath) {
    if (path == nullptr || src == nullptr) {
        return nullptr;
    }
    const SkPath native_src = *reinterpret_cast<const SkPath *>(src);
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.addPath(native_src, static_cast<SkPath::AddPathMode>(modeSkPath));
    });
}

reskia_path_t *SkPath_addPathWithMatrixAndMode(reskia_path_t *path, const reskia_path_t *src, const reskia_matrix_t *matrix, int mode) {
    if (path == nullptr || src == nullptr || matrix == nullptr) {
        return nullptr;
    }
    const SkPath native_src = *reinterpret_cast<const SkPath *>(src);
    const SkMatrix native_matrix = *reinterpret_cast<const SkMatrix *>(matrix);
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.addPath(native_src, native_matrix, static_cast<SkPath::AddPathMode>(mode));
    });
}

reskia_path_t *SkPath_reverseAddPath(reskia_path_t *path, const reskia_path_t *src) {
    if (path == nullptr || src == nullptr) {
        return nullptr;
    }
    const SkPath native_src = *reinterpret_cast<const SkPath *>(src);
    return mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        reverse_add_path(builder, native_src);
    });
}

void SkPath_offset(reskia_path_t *path, float dx, float dy, reskia_path_t *dst) {
    if (path == nullptr) {
        return;
    }
    SkPath result = reinterpret_cast<SkPath *>(path)->makeOffset(dx, dy);
    if (dst != nullptr) {
        *reinterpret_cast<SkPath *>(dst) = std::move(result);
    }
}

void SkPath_offsetInPlace(reskia_path_t *path, float dx, float dy) {
    if (path == nullptr) {
        return;
    }
    auto *native_path = reinterpret_cast<SkPath *>(path);
    *native_path = native_path->makeOffset(dx, dy);
}

sk_path_t SkPath_makeOffset(reskia_path_t *path, float dx, float dy) {
    if (path == nullptr) {
        return 0;
    }
    return static_sk_path_make(reinterpret_cast<SkPath *>(path)->makeOffset(dx, dy));
}

void SkPath_transform(reskia_path_t *path, const reskia_matrix_t *matrix, reskia_path_t *dst, reskia_path_perspective_clip_t pc) {
    if (path == nullptr || matrix == nullptr) {
        return;
    }
    (void) pc;
    SkPath result = reinterpret_cast<SkPath *>(path)->makeTransform(* reinterpret_cast<const SkMatrix *>(matrix));
    if (dst != nullptr) {
        *reinterpret_cast<SkPath *>(dst) = std::move(result);
    }
}

void SkPath_transformInPlace(reskia_path_t *path, const reskia_matrix_t *matrix, reskia_path_perspective_clip_t pc) {
    if (path == nullptr || matrix == nullptr) {
        return;
    }
    (void) pc;
    auto *native_path = reinterpret_cast<SkPath *>(path);
    *native_path = native_path->makeTransform(* reinterpret_cast<const SkMatrix *>(matrix));
}

sk_path_t SkPath_makeTransform(reskia_path_t *path, const reskia_matrix_t *m, reskia_path_perspective_clip_t pc) {
    if (path == nullptr || m == nullptr) {
        return 0;
    }
    (void) pc;
    return static_sk_path_make(reinterpret_cast<SkPath *>(path)->makeTransform(* reinterpret_cast<const SkMatrix *>(m)));
}

sk_path_t SkPath_makeScale(reskia_path_t *path, float sx, float sy) {
    if (path == nullptr) {
        return 0;
    }
    return static_sk_path_make(reinterpret_cast<SkPath *>(path)->makeScale(sx, sy));
}

sk_path_t SkPath_tryMakeTransform(reskia_path_t *path, const reskia_matrix_t *matrix) {
    if (path == nullptr || matrix == nullptr) {
        return 0;
    }
    auto result = reinterpret_cast<SkPath *>(path)->tryMakeTransform(*reinterpret_cast<const SkMatrix *>(matrix));
    return result.has_value() ? static_sk_path_make(std::move(*result)) : 0;
}

sk_path_t SkPath_tryMakeOffset(reskia_path_t *path, float dx, float dy) {
    if (path == nullptr) {
        return 0;
    }
    auto result = reinterpret_cast<SkPath *>(path)->tryMakeOffset(dx, dy);
    return result.has_value() ? static_sk_path_make(std::move(*result)) : 0;
}

sk_path_t SkPath_tryMakeScale(reskia_path_t *path, float sx, float sy) {
    if (path == nullptr) {
        return 0;
    }
    auto result = reinterpret_cast<SkPath *>(path)->tryMakeScale(sx, sy);
    return result.has_value() ? static_sk_path_make(std::move(*result)) : 0;
}

bool SkPath_getLastPt(reskia_path_t *path, reskia_point_t *lastPt) {
    if (path == nullptr || lastPt == nullptr) {
        return false;
    }
    return reinterpret_cast<SkPath *>(path)->getLastPt(reinterpret_cast<SkPoint *>(lastPt));
}

void SkPath_setLastPt(reskia_path_t *path, float x, float y) {
    if (path == nullptr) {
        return;
    }
    mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.setLastPt(x, y);
    });
}

void SkPath_setLastPtPoint(reskia_path_t *path, const reskia_point_t *p) {
    if (path == nullptr || p == nullptr) {
        return;
    }
    const SkPoint point = *reinterpret_cast<const SkPoint *>(p);
    mutate_path_with_builder(path, [=](SkPathBuilder& builder) {
        builder.setLastPt(point.fX, point.fY);
    });
}

uint32_t SkPath_getSegmentMasks(reskia_path_t *path) {
    if (path == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkPath *>(path)->getSegmentMasks();
}

bool SkPath_contains(reskia_path_t *path, float x, float y) {
    if (path == nullptr) {
        return false;
    }
    return reinterpret_cast<SkPath *>(path)->contains(x, y);
}

void SkPath_dump(reskia_path_t *path, reskia_w_stream_t *stream, bool dumpAsHex) {
    if (path == nullptr || stream == nullptr) {
        return;
    }
    reinterpret_cast<SkPath *>(path)->dump(reinterpret_cast<SkWStream *>(stream), dumpAsHex);
}

void SkPath_dumpDefault(reskia_path_t *path) {
    if (path == nullptr) {
        return;
    }
    reinterpret_cast<SkPath *>(path)->dump();
}

void SkPath_dumpHex(reskia_path_t *path) {
    if (path == nullptr) {
        return;
    }
    reinterpret_cast<SkPath *>(path)->dumpHex();
}

size_t SkPath_writeToMemory(reskia_path_t *path, void *buffer) {
    if (path == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkPath *>(path)->writeToMemory(buffer);
}

sk_data_t SkPath_serialize(reskia_path_t *path) {
    if (path == nullptr) {
        return 0;
    }
    return static_sk_data_make(reinterpret_cast<SkPath *>(path)->serialize());
}

size_t SkPath_readFromMemory(reskia_path_t *path, const void *buffer, size_t length) {
    if (path == nullptr || (buffer == nullptr && length > 0)) {
        return 0;
    }
    size_t bytesRead = 0;
    std::optional<SkPath> result = SkPath::ReadFromMemory(buffer, length, &bytesRead);
    if (!result.has_value()) {
        return 0;
    }
    *reinterpret_cast<SkPath *>(path) = std::move(*result);
    return bytesRead;
}

sk_path_t SkPath_ReadFromMemory(const void *buffer, size_t length, size_t *bytesRead) {
    if (buffer == nullptr && length > 0) {
        return 0;
    }
    std::optional<SkPath> path = SkPath::ReadFromMemory(buffer, length, bytesRead);
    return path.has_value() ? static_sk_path_make(*path) : 0;
}

uint32_t SkPath_getGenerationID(reskia_path_t *path) {
    if (path == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkPath *>(path)->getGenerationID();
}

bool SkPath_isValid(reskia_path_t *path) {
    if (path == nullptr) {
        return false;
    }
    return reinterpret_cast<SkPath *>(path)->isValid();
}

bool SkPathOps_Op(const reskia_path_t *one, const reskia_path_t *two, reskia_path_op_t op, reskia_path_t *result) {
    if (one == nullptr || two == nullptr || result == nullptr || !is_valid_path_op(op)) {
        return false;
    }
    return Op(*reinterpret_cast<const SkPath *>(one), *reinterpret_cast<const SkPath *>(two), static_cast<SkPathOp>(op), reinterpret_cast<SkPath *>(result));
}

bool SkPathOps_Simplify(const reskia_path_t *path, reskia_path_t *result) {
    if (path == nullptr || result == nullptr) {
        return false;
    }
    return Simplify(*reinterpret_cast<const SkPath *>(path), reinterpret_cast<SkPath *>(result));
}

bool SkPathOps_TightBounds(const reskia_path_t *path, reskia_rect_t *result) {
    if (path == nullptr || result == nullptr) {
        return false;
    }
    return TightBounds(*reinterpret_cast<const SkPath *>(path), reinterpret_cast<SkRect *>(result));
}

bool SkPathOps_AsWinding(const reskia_path_t *path, reskia_path_t *result) {
    if (path == nullptr || result == nullptr) {
        return false;
    }
    return AsWinding(*reinterpret_cast<const SkPath *>(path), reinterpret_cast<SkPath *>(result));
}

// static

sk_path_t SkPath_Make(const reskia_point_t *point, int pointCount, const uint8_t *i, int verbCount, const float *v, int conicWeightCount, reskia_path_fill_type_t type, bool isVolatile) {
    if (pointCount < 0 || verbCount < 0 || conicWeightCount < 0 ||
        (pointCount > 0 && point == nullptr) ||
        (verbCount > 0 && i == nullptr) ||
        (conicWeightCount > 0 && v == nullptr)) {
        return 0;
    }
    return static_sk_path_make(SkPath::Make(
            {reinterpret_cast<const SkPoint *>(point), static_cast<size_t>(pointCount)},
            {reinterpret_cast<const uint8_t *>(i), static_cast<size_t>(verbCount)},
            {reinterpret_cast<const SkScalar *>(v), static_cast<size_t>(conicWeightCount)},
            static_cast<SkPathFillType>(type),
            isVolatile));
}

sk_path_t SkPath_Raw(const reskia_point_t *point, int pointCount, const uint8_t *verbs, int verbCount, const float *conicWeights, int conicWeightCount, reskia_path_fill_type_t type, bool isVolatile) {
    if (pointCount < 0 || verbCount < 0 || conicWeightCount < 0 ||
        (pointCount > 0 && point == nullptr) ||
        (verbCount > 0 && verbs == nullptr) ||
        (conicWeightCount > 0 && conicWeights == nullptr)) {
        return 0;
    }
    return static_sk_path_make(SkPath::Raw(
            {reinterpret_cast<const SkPoint *>(point), static_cast<size_t>(pointCount)},
            {reinterpret_cast<const SkPathVerb *>(verbs), static_cast<size_t>(verbCount)},
            {reinterpret_cast<const SkScalar *>(conicWeights), static_cast<size_t>(conicWeightCount)},
            static_cast<SkPathFillType>(type),
            isVolatile));
}

sk_path_t SkPath_Rect(const reskia_rect_t *rect, reskia_path_direction_t dir, unsigned startIndex) {
    if (rect == nullptr) {
        return 0;
    }
    return static_sk_path_make(SkPath::Rect(* reinterpret_cast<const SkRect *>(rect), static_cast<SkPathDirection>(dir), startIndex));
}

sk_path_t SkPath_Oval(const reskia_rect_t *rect, reskia_path_direction_t dir) {
    if (rect == nullptr) {
        return 0;
    }
    return static_sk_path_make(SkPath::Oval(* reinterpret_cast<const SkRect *>(rect), static_cast<SkPathDirection>(dir)));
}

sk_path_t SkPath_OvalWithStart(const reskia_rect_t *rect, reskia_path_direction_t dir, unsigned startIndex) {
    if (rect == nullptr) {
        return 0;
    }
    return static_sk_path_make(SkPath::Oval(* reinterpret_cast<const SkRect *>(rect), static_cast<SkPathDirection>(dir), startIndex));
}

sk_path_t SkPath_Circle(float center_x, float center_y, float radius, reskia_path_direction_t dir) {
    return static_sk_path_make(SkPath::Circle(center_x, center_y, radius, static_cast<SkPathDirection>(dir)));
}

sk_path_t SkPath_RRect(const reskia_r_rect_t *rrect, reskia_path_direction_t dir) {
    if (rrect == nullptr) {
        return 0;
    }
    return static_sk_path_make(SkPath::RRect(* reinterpret_cast<const SkRRect *>(rrect), static_cast<SkPathDirection>(dir)));
}

sk_path_t SkPath_RRectWithStart(const reskia_r_rect_t *rrect, reskia_path_direction_t dir, unsigned startIndex) {
    if (rrect == nullptr) {
        return 0;
    }
    return static_sk_path_make(SkPath::RRect(* reinterpret_cast<const SkRRect *>(rrect), static_cast<SkPathDirection>(dir), startIndex));
}

sk_path_t SkPath_RRectFromRectAndRadii(const reskia_rect_t *bounds, float rx, float ry, reskia_path_direction_t dir) {
    if (bounds == nullptr) {
        return 0;
    }
    return static_sk_path_make(SkPath::RRect(* reinterpret_cast<const SkRect *>(bounds), rx, ry, static_cast<SkPathDirection>(dir)));
}

sk_path_t SkPath_Polygon(const reskia_point_t *pts, int count, bool isClosed, reskia_path_fill_type_t type, bool isVolatile) {
    if (count < 0 || (count > 0 && pts == nullptr)) {
        return 0;
    }
    return static_sk_path_make(SkPath::Polygon(
            {reinterpret_cast<const SkPoint *>(pts), static_cast<size_t>(count)},
            isClosed,
            static_cast<SkPathFillType>(type),
            isVolatile));
}

sk_path_t SkPath_PolygonFromList(const void *list, bool isClosed, reskia_path_fill_type_t fillType, bool isVolatile) {
    if (list == nullptr) {
        return 0;
    }
    return static_sk_path_make(SkPath::Polygon(* reinterpret_cast<const std::initializer_list<SkPoint> *>(list), isClosed, static_cast<SkPathFillType>(fillType), isVolatile));
}

sk_path_t SkPath_Line(sk_point_t a, sk_point_t b) {
    return static_sk_path_make(SkPath::Line(static_sk_point_get_entity(a), static_sk_point_get_entity(b)));
}

bool SkPath_IsLineDegenerate(const reskia_point_t *p1, const reskia_point_t *p2, bool exact) {
    if (p1 == nullptr || p2 == nullptr) {
        return true;
    }
    return SkPath::IsLineDegenerate(* reinterpret_cast<const SkPoint *>(p1), * reinterpret_cast<const SkPoint *>(p2), exact);
}

bool SkPath_IsQuadDegenerate(const reskia_point_t *p1, const reskia_point_t *p2, const reskia_point_t *p3, bool exact) {
    if (p1 == nullptr || p2 == nullptr || p3 == nullptr) {
        return true;
    }
    return SkPath::IsQuadDegenerate(* reinterpret_cast<const SkPoint *>(p1), * reinterpret_cast<const SkPoint *>(p2), * reinterpret_cast<const SkPoint *>(p3), exact);
}

bool SkPath_IsCubicDegenerate(const reskia_point_t *p1, const reskia_point_t *p2, const reskia_point_t *p3, const reskia_point_t *p4, bool exact) {
    if (p1 == nullptr || p2 == nullptr || p3 == nullptr || p4 == nullptr) {
        return true;
    }
    return SkPath::IsCubicDegenerate(* reinterpret_cast<const SkPoint *>(p1), * reinterpret_cast<const SkPoint *>(p2), * reinterpret_cast<const SkPoint *>(p3), * reinterpret_cast<const SkPoint *>(p4), exact);
}

int SkPath_ConvertConicToQuads(const reskia_point_t *p0, const reskia_point_t *p1, const reskia_point_t *p2, float w, reskia_point_t *pts, int pow2) {
    if (p0 == nullptr || p1 == nullptr || p2 == nullptr || pts == nullptr || pow2 < 0) {
        return 0;
    }
    return SkPath::ConvertConicToQuads(* reinterpret_cast<const SkPoint *>(p0), * reinterpret_cast<const SkPoint *>(p1), * reinterpret_cast<const SkPoint *>(p2), w, reinterpret_cast<SkPoint *>(pts), pow2);
}

reskia_path_iter_t *SkPathIter_new(const reskia_point_t *points, size_t points_count, const uint8_t *verbs, size_t verbs_count, const float *conic_weights, size_t conic_weights_count) {
    if ((points_count > 0 && points == nullptr) || (verbs_count > 0 && verbs == nullptr) || (conic_weights_count > 0 && conic_weights == nullptr)) {
        return nullptr;
    }
    return reinterpret_cast<reskia_path_iter_t *>(new PathIterBox(
            {reinterpret_cast<const SkPoint *>(points), points_count},
            verbs,
            verbs_count,
            {conic_weights, conic_weights_count}));
}

void SkPathIter_delete(reskia_path_iter_t *iter) {
    delete as_path_iter(iter);
}

bool SkPathIter_next(reskia_path_iter_t *iter, reskia_path_iter_rec_t *out_rec) {
    if (iter == nullptr || out_rec == nullptr) {
        return false;
    }
    std::optional<SkPathIter::Rec> rec = as_path_iter(iter)->iter.next();
    if (!rec.has_value()) {
        return false;
    }
    out_rec->points = reinterpret_cast<const reskia_point_t *>(rec->fPoints.data());
    out_rec->points_count = rec->fPoints.size();
    out_rec->conic_weight = rec->fConicWeight;
    out_rec->verb = static_cast<uint8_t>(rec->fVerb);
    return true;
}

bool SkPathIter_peekNextVerb(const reskia_path_iter_t *iter, uint8_t *out_verb) {
    if (iter == nullptr || out_verb == nullptr) {
        return false;
    }
    std::optional<SkPathVerb> verb = as_path_iter(iter)->iter.peekNextVerb();
    if (!verb.has_value()) {
        return false;
    }
    *out_verb = static_cast<uint8_t>(*verb);
    return true;
}

reskia_path_contour_iter_t *SkPathContourIter_new(const reskia_point_t *points, size_t points_count, const uint8_t *verbs, size_t verbs_count, const float *conic_weights, size_t conic_weights_count) {
    if ((points_count > 0 && points == nullptr) || (verbs_count > 0 && verbs == nullptr) || (conic_weights_count > 0 && conic_weights == nullptr)) {
        return nullptr;
    }
    return reinterpret_cast<reskia_path_contour_iter_t *>(new PathContourIterBox(
            {reinterpret_cast<const SkPoint *>(points), points_count},
            verbs,
            verbs_count,
            {conic_weights, conic_weights_count}));
}

void SkPathContourIter_delete(reskia_path_contour_iter_t *iter) {
    delete as_path_contour_iter(iter);
}

bool SkPathContourIter_next(reskia_path_contour_iter_t *iter, reskia_path_contour_iter_rec_t *out_rec) {
    if (iter == nullptr || out_rec == nullptr) {
        return false;
    }
    std::optional<SkPathContourIter::Rec> rec = as_path_contour_iter(iter)->iter.next();
    if (!rec.has_value()) {
        return false;
    }
    out_rec->points = reinterpret_cast<const reskia_point_t *>(rec->fPoints.data());
    out_rec->points_count = rec->fPoints.size();
    out_rec->verbs = reinterpret_cast<const uint8_t *>(rec->fVerbs.data());
    out_rec->verbs_count = rec->fVerbs.size();
    out_rec->conic_weights = rec->fConics.data();
    out_rec->conic_weights_count = rec->fConics.size();
    return true;
}

}
