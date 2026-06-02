//
// Created by dolphilia on 2024/01/08.
//

#include "sk_contour_measure.h"

#include "include/core/SkContourMeasure.h"
#include "include/core/SkPath.h"
#include "include/core/SkPathBuilder.h"

extern "C" {

void SkContourMeasure_release(reskia_contour_measure_t *contour_measure) {
    if (contour_measure == nullptr) {
        return;
    }
    reinterpret_cast<SkContourMeasure *>(contour_measure)->unref();
}

float SkContourMeasure_length(reskia_contour_measure_t *contour_measure) {
    if (contour_measure == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkContourMeasure *>(contour_measure)->length();
}

bool SkContourMeasure_getPosTan(reskia_contour_measure_t *contour_measure, float distance, reskia_point_t *position, reskia_vector_t *tangent) {
    if (contour_measure == nullptr || position == nullptr || tangent == nullptr) {
        return false;
    }
    return reinterpret_cast<SkContourMeasure *>(contour_measure)->getPosTan(distance, reinterpret_cast<SkPoint *>(position), reinterpret_cast<SkVector *>(tangent));
}

bool SkContourMeasure_getMatrix(reskia_contour_measure_t *contour_measure, float distance, reskia_matrix_t *matrix, reskia_contour_measure_matrix_flags_t flags) {
    if (contour_measure == nullptr || matrix == nullptr) {
        return false;
    }
    return reinterpret_cast<SkContourMeasure *>(contour_measure)->getMatrix(distance, reinterpret_cast<SkMatrix *>(matrix), static_cast<SkContourMeasure::MatrixFlags>(flags));
}

bool SkContourMeasure_getSegment(reskia_contour_measure_t *contour_measure, float startD, float stopD, reskia_path_t *dst, bool startWithMoveTo) {
    if (contour_measure == nullptr || dst == nullptr) {
        return false;
    }
    SkPathBuilder builder;
    if (!reinterpret_cast<SkContourMeasure *>(contour_measure)->getSegment(startD, stopD, &builder, startWithMoveTo)) {
        return false;
    }
    *reinterpret_cast<SkPath *>(dst) = builder.detach();
    return true;
}

bool SkContourMeasure_isClosed(reskia_contour_measure_t *contour_measure) {
    if (contour_measure == nullptr) {
        return false;
    }
    return reinterpret_cast<SkContourMeasure *>(contour_measure)->isClosed();
}

bool SkContourMeasure_unique(reskia_contour_measure_t *contour_measure) {
    if (contour_measure == nullptr) {
        return false;
    }
    return reinterpret_cast<SkContourMeasure *>(contour_measure)->unique();
}

void SkContourMeasure_ref(reskia_contour_measure_t *contour_measure) {
    if (contour_measure == nullptr) {
        return;
    }
    reinterpret_cast<SkContourMeasure *>(contour_measure)->ref();
}

void SkContourMeasure_unref(reskia_contour_measure_t *contour_measure) {
    if (contour_measure == nullptr) {
        return;
    }
    reinterpret_cast<SkContourMeasure *>(contour_measure)->unref();
}

}
