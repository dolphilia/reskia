//
// Created by dolphilia on 2024/01/08.
//

#include "sk_contour_measure_iter.h"

#include "include/core/SkContourMeasure.h"

#include "../static/static_sk_contour_measure.h"

#include "../static/static_sk_contour_measure-internal.h"

extern "C" {

void *SkContourMeasureIter_new() {
    return new SkContourMeasureIter();
}

void *SkContourMeasureIter_new_2(const void *path, bool forceClosed, float resScale) {
    return new SkContourMeasureIter(* static_cast<const SkPath *>(path), forceClosed, resScale);
}

void SkContourMeasureIter_delete(void *contour_measure_iter) {
    delete static_cast<SkContourMeasureIter *>(contour_measure_iter);
}

void SkContourMeasureIter_reset(void *contour_measure_iter, const void *path, bool forceClosed, float resScale) {
    static_cast<SkContourMeasureIter *>(contour_measure_iter)->reset(* static_cast<const SkPath *>(path), forceClosed, resScale);
}

sk_contour_measure_t SkContourMeasureIter_next(void *contour_measure_iter) {
    return static_sk_contour_measure_make(static_cast<SkContourMeasureIter *>(contour_measure_iter)->next());
}

}
