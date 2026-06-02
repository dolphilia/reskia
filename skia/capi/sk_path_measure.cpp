//
// Created by dolphilia on 2024/01/10.
//

#include "sk_path_measure.h"

#include "include/core/SkPath.h"
#include "include/core/SkPathBuilder.h"
#include "include/core/SkPathMeasure.h"

extern "C" {


reskia_path_measure_t *SkPathMeasure_new() {
    return reinterpret_cast<reskia_path_measure_t *>(new SkPathMeasure());
}

reskia_path_measure_t *SkPathMeasure_newWithPathForceClosedAndResScale(const reskia_path_t *path, bool forceClosed, float resScale) {
    if (path == nullptr) {
        return reinterpret_cast<reskia_path_measure_t *>(new SkPathMeasure());
    }
    return reinterpret_cast<reskia_path_measure_t *>(new SkPathMeasure(*reinterpret_cast<const SkPath *>(path), forceClosed, resScale));
}

void SkPathMeasure_delete(reskia_path_measure_t *path_measure) {
    delete reinterpret_cast<SkPathMeasure *>(path_measure);
}

void SkPathMeasure_setPath(reskia_path_measure_t *path_measure, const reskia_path_t *path, bool forceClosed) {
    if (path_measure == nullptr) {
        return;
    }
    reinterpret_cast<SkPathMeasure *>(path_measure)->setPath(reinterpret_cast<const SkPath *>(path), forceClosed);
}

float SkPathMeasure_getLength(reskia_path_measure_t *path_measure) {
    if (path_measure == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkPathMeasure *>(path_measure)->getLength();
}

bool SkPathMeasure_getPosTan(reskia_path_measure_t *path_measure, float distance, reskia_point_t *position, reskia_vector_t *tangent) {
    if (path_measure == nullptr || position == nullptr || tangent == nullptr) {
        return false;
    }
    return reinterpret_cast<SkPathMeasure *>(path_measure)->getPosTan(
        distance,
        reinterpret_cast<SkPoint *>(position),
        reinterpret_cast<SkVector *>(tangent));
}

bool SkPathMeasure_getMatrix(reskia_path_measure_t *path_measure, float distance, reskia_matrix_t *matrix, reskia_path_measure_matrix_flags_t flags) {
    if (path_measure == nullptr || matrix == nullptr) {
        return false;
    }
    return reinterpret_cast<SkPathMeasure *>(path_measure)->getMatrix(
        distance,
        reinterpret_cast<SkMatrix *>(matrix),
        static_cast<SkPathMeasure::MatrixFlags>(flags));
}

bool SkPathMeasure_getSegment(reskia_path_measure_t *path_measure, float startD, float stopD, reskia_path_t *dst, bool startWithMoveTo) {
    if (path_measure == nullptr || dst == nullptr) {
        return false;
    }
    SkPathBuilder builder;
    if (!reinterpret_cast<SkPathMeasure *>(path_measure)->getSegment(startD, stopD, &builder, startWithMoveTo)) {
        return false;
    }
    *reinterpret_cast<SkPath *>(dst) = builder.detach();
    return true;
}

bool SkPathMeasure_isClosed(reskia_path_measure_t *path_measure) {
    if (path_measure == nullptr) {
        return false;
    }
    return reinterpret_cast<SkPathMeasure *>(path_measure)->isClosed();
}

bool SkPathMeasure_nextContour(reskia_path_measure_t *path_measure) {
    if (path_measure == nullptr) {
        return false;
    }
    return reinterpret_cast<SkPathMeasure *>(path_measure)->nextContour();
}

const reskia_contour_measure_t *SkPathMeasure_currentMeasure(reskia_path_measure_t *path_measure) {
    if (path_measure == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_contour_measure_t *>(reinterpret_cast<SkPathMeasure *>(path_measure)->currentMeasure());
}

void SkPathMeasure_dump(reskia_path_measure_t *path_measure) {
    if (path_measure == nullptr) {
        return;
    }
    reinterpret_cast<SkPathMeasure *>(path_measure)->dump();
}

}
