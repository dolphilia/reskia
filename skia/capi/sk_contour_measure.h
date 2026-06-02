//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_CONTOUR_MEASURE_H
#define RAIA_SKIA_SK_CONTOUR_MEASURE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_contour_measure_t reskia_contour_measure_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_path_t reskia_path_t;
typedef struct reskia_point_t reskia_point_t;
typedef struct reskia_vector_t reskia_vector_t;
typedef int32_t reskia_contour_measure_matrix_flags_t;

/**
 * owned: releases the caller-held reference. No-op for NULL input.
 * (SkContourMeasure *contour_measure)
 */
void SkContourMeasure_release(reskia_contour_measure_t *contour_measure);
float SkContourMeasure_length(reskia_contour_measure_t *contour_measure); // Returns 0 for NULL input. (SkContourMeasure *contour_measure) -> SkScalar
/**
 * position and tangent must be non-NULL. Returns false for NULL input.
 */
bool SkContourMeasure_getPosTan(reskia_contour_measure_t *contour_measure, float distance, reskia_point_t *position, reskia_vector_t *tangent);
/**
 * matrix must be non-NULL. Returns false for NULL input.
 */
bool SkContourMeasure_getMatrix(reskia_contour_measure_t *contour_measure, float distance, reskia_matrix_t *matrix, reskia_contour_measure_matrix_flags_t flags);
/**
 * dst must be non-NULL. Returns false for NULL input.
 */
bool SkContourMeasure_getSegment(reskia_contour_measure_t *contour_measure, float startD, float stopD, reskia_path_t *dst, bool startWithMoveTo);
bool SkContourMeasure_isClosed(reskia_contour_measure_t *contour_measure); // (SkContourMeasure *contour_measure) -> bool
bool SkContourMeasure_unique(reskia_contour_measure_t *contour_measure); // (SkContourMeasure *contour_measure) -> bool
void SkContourMeasure_ref(reskia_contour_measure_t *contour_measure); // retained: increments the reference count. No-op for NULL input.
void SkContourMeasure_unref(reskia_contour_measure_t *contour_measure); // owned: decrements the reference count. No-op for NULL input.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_CONTOUR_MEASURE_H
