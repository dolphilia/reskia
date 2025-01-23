//
// Created by dolphilia on 2024/01/10.
//

#include "sk_path_measure.h"

#include "include/core/SkPathMeasure.h"

extern "C" {

// SkPathMeasure & operator=(SkPathMeasure &&)

void *SkPathMeasure_new() {
    return new SkPathMeasure();
}

void *SkPathMeasure_new_2(const void *path, bool forceClosed, float resScale) {
    return new SkPathMeasure(* static_cast<const SkPath *>(path), forceClosed, resScale);
}

void SkPathMeasure_delete(void *path_measure) {
    delete static_cast<SkPathMeasure *>(path_measure);
}

void SkPathMeasure_setPath(void *path_measure, const void *path, bool forceClosed) {
    static_cast<SkPathMeasure *>(path_measure)->setPath(static_cast<const SkPath *>(path), forceClosed);
}

float SkPathMeasure_getLength(void *path_measure) {
    return static_cast<SkPathMeasure *>(path_measure)->getLength();
}

bool SkPathMeasure_getPosTan(void *path_measure, float distance, void *position, void *tangent) {
    return static_cast<SkPathMeasure *>(path_measure)->getPosTan(distance, static_cast<SkPoint *>(position), static_cast<SkVector *>(tangent));
}

bool SkPathMeasure_getMatrix(void *path_measure, float distance, void *matrix, int flags) {
    return static_cast<SkPathMeasure *>(path_measure)->getMatrix(distance, static_cast<SkMatrix *>(matrix), static_cast<SkPathMeasure::MatrixFlags>(flags));
}

bool SkPathMeasure_getSegment(void *path_measure, float startD, float stopD, void *dst, bool startWithMoveTo) {
    return static_cast<SkPathMeasure *>(path_measure)->getSegment(startD, stopD, static_cast<SkPath *>(dst), startWithMoveTo);
}

bool SkPathMeasure_isClosed(void *path_measure) {
    return static_cast<SkPathMeasure *>(path_measure)->isClosed();
}

bool SkPathMeasure_nextContour(void *path_measure) {
    return static_cast<SkPathMeasure *>(path_measure)->nextContour();
}

}