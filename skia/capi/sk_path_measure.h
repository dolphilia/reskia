//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_PATH_MEASURE_H
#define RAIA_SKIA_SK_PATH_MEASURE_H

#include <stdint.h>

typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_contour_measure_t reskia_contour_measure_t;
typedef struct reskia_path_measure_t reskia_path_measure_t;
typedef struct reskia_path_t reskia_path_t;
typedef struct reskia_point_t reskia_point_t;
typedef struct reskia_vector_t reskia_vector_t;
typedef int32_t reskia_path_measure_matrix_flags_t;

#ifdef __cplusplus
extern "C" {
#endif


reskia_path_measure_t *SkPathMeasure_new(); // () -> SkPathMeasure *
/**
 * Returns an empty SkPathMeasure when path is NULL.
 */
reskia_path_measure_t *SkPathMeasure_newWithPathForceClosedAndResScale(const reskia_path_t *path, bool forceClosed, float resScale);
void SkPathMeasure_delete(reskia_path_measure_t *path_measure); // (SkPathMeasure *path_measure)
/**
 * path may be NULL and resets the measure. No-op when path_measure is NULL.
 */
void SkPathMeasure_setPath(reskia_path_measure_t *path_measure, const reskia_path_t *path, bool forceClosed);
float SkPathMeasure_getLength(reskia_path_measure_t *path_measure); // Returns 0 for NULL input.
/**
 * position and tangent must be non-NULL. Returns false for NULL input.
 */
bool SkPathMeasure_getPosTan(reskia_path_measure_t *path_measure, float distance, reskia_point_t *position, reskia_vector_t *tangent);
/**
 * matrix must be non-NULL. Returns false for NULL input.
 */
bool SkPathMeasure_getMatrix(reskia_path_measure_t *path_measure, float distance, reskia_matrix_t *matrix, reskia_path_measure_matrix_flags_t flags);
/**
 * dst must be non-NULL. Returns false for NULL input.
 */
bool SkPathMeasure_getSegment(reskia_path_measure_t *path_measure, float startD, float stopD, reskia_path_t *dst, bool startWithMoveTo);
bool SkPathMeasure_isClosed(reskia_path_measure_t *path_measure); // (SkPathMeasure *path_measure) -> bool
bool SkPathMeasure_nextContour(reskia_path_measure_t *path_measure); // (SkPathMeasure *path_measure) -> bool
const reskia_contour_measure_t *SkPathMeasure_currentMeasure(reskia_path_measure_t *path_measure); // borrowed pointer。NULL input returns NULL
void SkPathMeasure_dump(reskia_path_measure_t *path_measure); // NULL input is no-op

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PATH_MEASURE_H
