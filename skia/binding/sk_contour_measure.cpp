//
// Created by dolphilia on 2024/01/08.
//

#include "sk_contour_measure.h"

#include "include/core/SkContourMeasure.h"

extern "C" {

void SkContourMeasure_delete(reskia_contour_measure_t *contour_measure) {
    reinterpret_cast<SkContourMeasure *>(contour_measure)->unref();
}

float SkContourMeasure_length(reskia_contour_measure_t *contour_measure) {
    return reinterpret_cast<SkContourMeasure *>(contour_measure)->length();
}

bool SkContourMeasure_getPosTan(reskia_contour_measure_t *contour_measure, float distance, reskia_point_t *position, reskia_vector_t *tangent) {
    return reinterpret_cast<SkContourMeasure *>(contour_measure)->getPosTan(distance, reinterpret_cast<SkPoint *>(position), reinterpret_cast<SkVector *>(tangent));
}

bool SkContourMeasure_getMatrix(reskia_contour_measure_t *contour_measure, float distance, reskia_matrix_t *matrix, int flags) {
    return reinterpret_cast<SkContourMeasure *>(contour_measure)->getMatrix(distance, reinterpret_cast<SkMatrix *>(matrix), static_cast<SkContourMeasure::MatrixFlags>(flags));
}

bool SkContourMeasure_getSegment(reskia_contour_measure_t *contour_measure, float startD, float stopD, reskia_path_t *dst, bool startWithMoveTo) {
    return reinterpret_cast<SkContourMeasure *>(contour_measure)->getSegment(startD, stopD, reinterpret_cast<SkPath *>(dst), startWithMoveTo);
}

bool SkContourMeasure_isClosed(reskia_contour_measure_t *contour_measure) {
    return reinterpret_cast<SkContourMeasure *>(contour_measure)->isClosed();
}

bool SkContourMeasure_unique(reskia_contour_measure_t *contour_measure) {
    return reinterpret_cast<SkContourMeasure *>(contour_measure)->unique();
}

void SkContourMeasure_ref(reskia_contour_measure_t *contour_measure) {
    reinterpret_cast<SkContourMeasure *>(contour_measure)->ref();
}

void SkContourMeasure_unref(reskia_contour_measure_t *contour_measure) {
    reinterpret_cast<SkContourMeasure *>(contour_measure)->unref();
}

}
