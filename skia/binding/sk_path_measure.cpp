//
// Created by dolphilia on 2024/01/10.
//

#include "sk_path_measure.h"

#include "include/core/SkPathMeasure.h"

extern "C" {

// SkPathMeasure & operator=(SkPathMeasure &&)

reskia_path_measure_t *SkPathMeasure_new() {
    return reinterpret_cast<reskia_path_measure_t *>(new SkPathMeasure());
}

reskia_path_measure_t *SkPathMeasure_new_2(const reskia_path_t *path, bool forceClosed, float resScale) {
    return reinterpret_cast<reskia_path_measure_t *>(new SkPathMeasure(*reinterpret_cast<const SkPath *>(path), forceClosed, resScale));
}

void SkPathMeasure_delete(reskia_path_measure_t *path_measure) {
    delete reinterpret_cast<SkPathMeasure *>(path_measure);
}

void SkPathMeasure_setPath(reskia_path_measure_t *path_measure, const reskia_path_t *path, bool forceClosed) {
    reinterpret_cast<SkPathMeasure *>(path_measure)->setPath(reinterpret_cast<const SkPath *>(path), forceClosed);
}

float SkPathMeasure_getLength(reskia_path_measure_t *path_measure) {
    return reinterpret_cast<SkPathMeasure *>(path_measure)->getLength();
}

bool SkPathMeasure_getPosTan(reskia_path_measure_t *path_measure, float distance, reskia_point_t *position, reskia_vector_t *tangent) {
    return reinterpret_cast<SkPathMeasure *>(path_measure)->getPosTan(
        distance,
        reinterpret_cast<SkPoint *>(position),
        reinterpret_cast<SkVector *>(tangent));
}

bool SkPathMeasure_getMatrix(reskia_path_measure_t *path_measure, float distance, reskia_matrix_t *matrix, int flags) {
    return reinterpret_cast<SkPathMeasure *>(path_measure)->getMatrix(
        distance,
        reinterpret_cast<SkMatrix *>(matrix),
        static_cast<SkPathMeasure::MatrixFlags>(flags));
}

bool SkPathMeasure_getSegment(reskia_path_measure_t *path_measure, float startD, float stopD, reskia_path_t *dst, bool startWithMoveTo) {
    return reinterpret_cast<SkPathMeasure *>(path_measure)->getSegment(startD, stopD, reinterpret_cast<SkPath *>(dst), startWithMoveTo);
}

bool SkPathMeasure_isClosed(reskia_path_measure_t *path_measure) {
    return reinterpret_cast<SkPathMeasure *>(path_measure)->isClosed();
}

bool SkPathMeasure_nextContour(reskia_path_measure_t *path_measure) {
    return reinterpret_cast<SkPathMeasure *>(path_measure)->nextContour();
}

}
