//
// Created by dolphilia on 2024/01/08.
//

#include "sk_contour_measure_iter.h"

#include "include/core/SkContourMeasure.h"

#include "../handles/static_sk_contour_measure.h"

#include "../handles/static_sk_contour_measure-internal.h"

extern "C" {

reskia_contour_measure_iter_t *SkContourMeasureIter_new() {
    return reinterpret_cast<reskia_contour_measure_iter_t *>(new SkContourMeasureIter());
}

reskia_contour_measure_iter_t *SkContourMeasureIter_new_2(const reskia_path_t *path, bool forceClosed, float resScale) {
    return reinterpret_cast<reskia_contour_measure_iter_t *>(new SkContourMeasureIter(* reinterpret_cast<const SkPath *>(path), forceClosed, resScale));
}

void SkContourMeasureIter_delete(reskia_contour_measure_iter_t *contour_measure_iter) {
    delete reinterpret_cast<SkContourMeasureIter *>(contour_measure_iter);
}

void SkContourMeasureIter_reset(reskia_contour_measure_iter_t *contour_measure_iter, const reskia_path_t *path, bool forceClosed, float resScale) {
    reinterpret_cast<SkContourMeasureIter *>(contour_measure_iter)->reset(* reinterpret_cast<const SkPath *>(path), forceClosed, resScale);
}

sk_contour_measure_t SkContourMeasureIter_next(reskia_contour_measure_iter_t *contour_measure_iter) {
    return static_sk_contour_measure_make(reinterpret_cast<SkContourMeasureIter *>(contour_measure_iter)->next());
}

}
