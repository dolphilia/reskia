//
// Created by dolphilia on 2024/01/08.
//

#include "sk_contour_measure.h"

#include "include/core/SkContourMeasure.h"

extern "C" {

void SkContourMeasure_delete(void *contour_measure) {
    static_cast<SkContourMeasure *>(contour_measure)->unref();
}

float SkContourMeasure_length(void *contour_measure) {
    return static_cast<SkContourMeasure *>(contour_measure)->length();
}

bool SkContourMeasure_getPosTan(void *contour_measure, float distance, void *position, void *tangent) {
    return static_cast<SkContourMeasure *>(contour_measure)->getPosTan(distance, static_cast<SkPoint *>(position), static_cast<SkVector *>(tangent));
}

bool SkContourMeasure_getMatrix(void *contour_measure, float distance, void *matrix, int flags) {
    return static_cast<SkContourMeasure *>(contour_measure)->getMatrix(distance, static_cast<SkMatrix *>(matrix), static_cast<SkContourMeasure::MatrixFlags>(flags));
}

bool SkContourMeasure_getSegment(void *contour_measure, float startD, float stopD, void *dst, bool startWithMoveTo) {
    return static_cast<SkContourMeasure *>(contour_measure)->getSegment(startD, stopD, static_cast<SkPath *>(dst), startWithMoveTo);
}

bool SkContourMeasure_isClosed(void *contour_measure) {
    return static_cast<SkContourMeasure *>(contour_measure)->isClosed();
}

bool SkContourMeasure_unique(void *contour_measure) {
    return static_cast<SkContourMeasure *>(contour_measure)->unique();
}

void SkContourMeasure_ref(void *contour_measure) {
    static_cast<SkContourMeasure *>(contour_measure)->ref();
}

void SkContourMeasure_unref(void *contour_measure) {
    static_cast<SkContourMeasure *>(contour_measure)->unref();
}

}
