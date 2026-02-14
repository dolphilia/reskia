//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_CONTOUR_MEASURE_H
#define RAIA_SKIA_SK_CONTOUR_MEASURE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_contour_measure_t reskia_contour_measure_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_path_t reskia_path_t;
typedef struct reskia_point_t reskia_point_t;
typedef struct reskia_vector_t reskia_vector_t;

void SkContourMeasure_delete(reskia_contour_measure_t *contour_measure); // owned: caller が保持する参照を release する (SkContourMeasure *contour_measure)
float SkContourMeasure_length(reskia_contour_measure_t *contour_measure); // (SkContourMeasure *contour_measure) -> SkScalar
bool SkContourMeasure_getPosTan(reskia_contour_measure_t *contour_measure, float distance, reskia_point_t *position, reskia_vector_t *tangent); // (SkContourMeasure *contour_measure, SkScalar distance, SkPoint *position, SkVector *tangent) -> bool
bool SkContourMeasure_getMatrix(reskia_contour_measure_t *contour_measure, float distance, reskia_matrix_t *matrix, int flags); // (SkContourMeasure *contour_measure, SkScalar distance, SkMatrix *matrix, SkContourMeasure::MatrixFlags flags) -> bool
bool SkContourMeasure_getSegment(reskia_contour_measure_t *contour_measure, float startD, float stopD, reskia_path_t *dst, bool startWithMoveTo); // (SkContourMeasure *contour_measure, SkScalar startD, SkScalar stopD, SkPath *dst, bool startWithMoveTo) -> bool
bool SkContourMeasure_isClosed(reskia_contour_measure_t *contour_measure); // (SkContourMeasure *contour_measure) -> bool
bool SkContourMeasure_unique(reskia_contour_measure_t *contour_measure); // (SkContourMeasure *contour_measure) -> bool
void SkContourMeasure_ref(reskia_contour_measure_t *contour_measure); // retained: 参照カウントを増やす (SkContourMeasure *contour_measure)
void SkContourMeasure_unref(reskia_contour_measure_t *contour_measure); // owned: 参照カウントを減らす (SkContourMeasure *contour_measure)

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_CONTOUR_MEASURE_H
