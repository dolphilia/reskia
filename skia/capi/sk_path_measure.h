//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_PATH_MEASURE_H
#define RAIA_SKIA_SK_PATH_MEASURE_H

#include <stdint.h>

typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_path_measure_t reskia_path_measure_t;
typedef struct reskia_path_t reskia_path_t;
typedef struct reskia_point_t reskia_point_t;
typedef struct reskia_vector_t reskia_vector_t;
typedef int32_t reskia_path_measure_matrix_flags_t;

#ifdef __cplusplus
extern "C" {
#endif

// SkPathMeasure & operator=(SkPathMeasure &&)

reskia_path_measure_t *SkPathMeasure_new(); // () -> SkPathMeasure *
reskia_path_measure_t *SkPathMeasure_newWithPathForceClosedAndResScale(const reskia_path_t *path, bool forceClosed, float resScale); // path NULL では空の SkPathMeasure を返す
void SkPathMeasure_delete(reskia_path_measure_t *path_measure); // (SkPathMeasure *path_measure)
void SkPathMeasure_setPath(reskia_path_measure_t *path_measure, const reskia_path_t *path, bool forceClosed); // path は NULL 許可で reset。path_measure NULL では no-op
float SkPathMeasure_getLength(reskia_path_measure_t *path_measure); // NULL 入力では 0
bool SkPathMeasure_getPosTan(reskia_path_measure_t *path_measure, float distance, reskia_point_t *position, reskia_vector_t *tangent); // position/tangent は非 NULL。NULL 入力では false
bool SkPathMeasure_getMatrix(reskia_path_measure_t *path_measure, float distance, reskia_matrix_t *matrix, reskia_path_measure_matrix_flags_t flags); // matrix は非 NULL。NULL 入力では false
bool SkPathMeasure_getSegment(reskia_path_measure_t *path_measure, float startD, float stopD, reskia_path_t *dst, bool startWithMoveTo); // dst は非 NULL。NULL 入力では false
bool SkPathMeasure_isClosed(reskia_path_measure_t *path_measure); // (SkPathMeasure *path_measure) -> bool
bool SkPathMeasure_nextContour(reskia_path_measure_t *path_measure); // (SkPathMeasure *path_measure) -> bool

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PATH_MEASURE_H
