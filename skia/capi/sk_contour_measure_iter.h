//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_CONTOUR_MEASURE_ITER_H
#define RAIA_SKIA_SK_CONTOUR_MEASURE_ITER_H

#include "../handles/static_sk_contour_measure.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_contour_measure_iter_t reskia_contour_measure_iter_t;
typedef struct reskia_path_t reskia_path_t;

reskia_contour_measure_iter_t *SkContourMeasureIter_new(); // () -> SkContourMeasureIter *
reskia_contour_measure_iter_t *SkContourMeasureIter_newWithPath(const reskia_path_t *path, bool forceClosed, float resScale); // path は非 NULL。NULL 入力では NULL
void SkContourMeasureIter_delete(reskia_contour_measure_iter_t *contour_measure_iter); // (SkContourMeasureIter *contour_measure_iter)
void SkContourMeasureIter_reset(reskia_contour_measure_iter_t *contour_measure_iter, const reskia_path_t *path, bool forceClosed, float resScale); // contour_measure_iter/path は非 NULL。NULL 入力では no-op
sk_contour_measure_t SkContourMeasureIter_next(reskia_contour_measure_iter_t *contour_measure_iter); // 終了または NULL 入力では 0

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_CONTOUR_MEASURE_ITER_H
