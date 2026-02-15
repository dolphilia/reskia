//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_PATH_MEASURE_H
#define RAIA_SKIA_SK_PATH_MEASURE_H

typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_path_measure_t reskia_path_measure_t;
typedef struct reskia_path_t reskia_path_t;
typedef struct reskia_point_t reskia_point_t;
typedef struct reskia_vector_t reskia_vector_t;

#ifdef __cplusplus
extern "C" {
#endif

// SkPathMeasure & operator=(SkPathMeasure &&)

reskia_path_measure_t *SkPathMeasure_new(); // () -> SkPathMeasure *
reskia_path_measure_t *SkPathMeasure_new_2(const reskia_path_t *path, bool forceClosed, float resScale); // (const SkPath *path, bool forceClosed, SkScalar resScale) -> SkPathMeasure *
void SkPathMeasure_delete(reskia_path_measure_t *path_measure); // (SkPathMeasure *path_measure)
void SkPathMeasure_setPath(reskia_path_measure_t *path_measure, const reskia_path_t *path, bool forceClosed); // (SkPathMeasure *path_measure, const SkPath *path, bool forceClosed)
float SkPathMeasure_getLength(reskia_path_measure_t *path_measure); // (SkPathMeasure *path_measure) -> SkScalar
bool SkPathMeasure_getPosTan(reskia_path_measure_t *path_measure, float distance, reskia_point_t *position, reskia_vector_t *tangent); // (SkPathMeasure *path_measure, SkScalar distance, SkPoint *position, SkVector *tangent) -> bool
bool SkPathMeasure_getMatrix(reskia_path_measure_t *path_measure, float distance, reskia_matrix_t *matrix, int flags); // (SkPathMeasure *path_measure, SkScalar distance, SkMatrix *matrix, SkPathMeasure::MatrixFlags flags) -> bool
bool SkPathMeasure_getSegment(reskia_path_measure_t *path_measure, float startD, float stopD, reskia_path_t *dst, bool startWithMoveTo); // (SkPathMeasure *path_measure, SkScalar startD, SkScalar stopD, SkPath *dst, bool startWithMoveTo) -> bool
bool SkPathMeasure_isClosed(reskia_path_measure_t *path_measure); // (SkPathMeasure *path_measure) -> bool
bool SkPathMeasure_nextContour(reskia_path_measure_t *path_measure); // (SkPathMeasure *path_measure) -> bool

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PATH_MEASURE_H
