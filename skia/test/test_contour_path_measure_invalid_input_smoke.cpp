#include "capi/sk_contour_measure.h"
#include "capi/sk_contour_measure_iter.h"
#include "capi/sk_path.h"
#include "capi/sk_path_measure.h"
#include "handles/static_sk_contour_measure.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[contour-path-measure-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkContourMeasure_release(nullptr);
    SkContourMeasure_ref(nullptr);
    SkContourMeasure_unref(nullptr);
    if (!check(SkContourMeasure_length(nullptr) == 0.0f, "SkContourMeasure_length(nullptr)")) {
        return 1;
    }
    if (!check(!SkContourMeasure_getPosTan(nullptr, 0.0f, nullptr, nullptr), "SkContourMeasure_getPosTan(nullptr)")) {
        return 2;
    }
    if (!check(!SkContourMeasure_getMatrix(nullptr, 0.0f, nullptr, 0), "SkContourMeasure_getMatrix(nullptr)")) {
        return 3;
    }
    if (!check(!SkContourMeasure_getSegment(nullptr, 0.0f, 1.0f, nullptr, true), "SkContourMeasure_getSegment(nullptr)")) {
        return 4;
    }
    if (!check(!SkContourMeasure_isClosed(nullptr), "SkContourMeasure_isClosed(nullptr)")) {
        return 5;
    }
    if (!check(!SkContourMeasure_unique(nullptr), "SkContourMeasure_unique(nullptr)")) {
        return 6;
    }

    if (!check(SkContourMeasureIter_newWithPath(nullptr, false, 1.0f) == nullptr, "SkContourMeasureIter_newWithPath(nullptr)")) {
        return 7;
    }
    SkContourMeasureIter_reset(nullptr, nullptr, false, 1.0f);
    if (!check(SkContourMeasureIter_next(nullptr) == 0, "SkContourMeasureIter_next(nullptr)")) {
        return 8;
    }

    reskia_path_measure_t *empty_measure = SkPathMeasure_newWithPathForceClosedAndResScale(nullptr, false, 1.0f);
    if (!check(empty_measure != nullptr, "SkPathMeasure_newWithPathForceClosedAndResScale(nullptr)")) {
        return 9;
    }
    if (!check(SkPathMeasure_getLength(empty_measure) == 0.0f, "empty SkPathMeasure length")) {
        SkPathMeasure_delete(empty_measure);
        return 10;
    }
    SkPathMeasure_setPath(nullptr, nullptr, false);
    if (!check(SkPathMeasure_getLength(nullptr) == 0.0f, "SkPathMeasure_getLength(nullptr)")) {
        SkPathMeasure_delete(empty_measure);
        return 11;
    }
    if (!check(!SkPathMeasure_getPosTan(nullptr, 0.0f, nullptr, nullptr), "SkPathMeasure_getPosTan(nullptr)")) {
        SkPathMeasure_delete(empty_measure);
        return 12;
    }
    if (!check(!SkPathMeasure_getMatrix(nullptr, 0.0f, nullptr, 0), "SkPathMeasure_getMatrix(nullptr)")) {
        SkPathMeasure_delete(empty_measure);
        return 13;
    }
    if (!check(!SkPathMeasure_getSegment(nullptr, 0.0f, 1.0f, nullptr, true), "SkPathMeasure_getSegment(nullptr)")) {
        SkPathMeasure_delete(empty_measure);
        return 14;
    }
    if (!check(!SkPathMeasure_isClosed(nullptr), "SkPathMeasure_isClosed(nullptr)")) {
        SkPathMeasure_delete(empty_measure);
        return 15;
    }
    if (!check(!SkPathMeasure_nextContour(nullptr), "SkPathMeasure_nextContour(nullptr)")) {
        SkPathMeasure_delete(empty_measure);
        return 16;
    }
    SkPathMeasure_dump(nullptr);
    SkPathMeasure_dump(empty_measure);

    reskia_path_t *path = SkPath_new();
    if (!check(path != nullptr, "SkPath_new")) {
        SkPathMeasure_delete(empty_measure);
        return 17;
    }
    SkPath_moveTo(path, 0.0f, 0.0f);
    SkPath_lineTo(path, 10.0f, 0.0f);

    reskia_contour_measure_iter_t *iter = SkContourMeasureIter_newWithPath(path, false, 1.0f);
    if (!check(iter != nullptr, "SkContourMeasureIter_newWithPath(valid)")) {
        SkPath_delete(path);
        SkPathMeasure_delete(empty_measure);
        return 18;
    }
    const sk_contour_measure_t contour_handle = SkContourMeasureIter_next(iter);
    auto *contour = static_cast<reskia_contour_measure_t *>(static_sk_contour_measure_get_ptr(contour_handle));
    if (!check(contour != nullptr, "SkContourMeasureIter_next(valid)")) {
        SkContourMeasureIter_delete(iter);
        SkPath_delete(path);
        SkPathMeasure_delete(empty_measure);
        return 19;
    }
    if (!check(SkContourMeasure_length(contour) == 10.0f, "SkContourMeasure_length(valid)")) {
        static_sk_contour_measure_delete(contour_handle);
        SkContourMeasureIter_delete(iter);
        SkPath_delete(path);
        SkPathMeasure_delete(empty_measure);
        return 20;
    }
    if (!check(SkContourMeasureIter_next(iter) == 0, "SkContourMeasureIter_next(end)")) {
        static_sk_contour_measure_delete(contour_handle);
        SkContourMeasureIter_delete(iter);
        SkPath_delete(path);
        SkPathMeasure_delete(empty_measure);
        return 21;
    }

    reskia_path_measure_t *path_measure = SkPathMeasure_newWithPathForceClosedAndResScale(path, false, 1.0f);
    if (!check(path_measure != nullptr, "SkPathMeasure_newWithPathForceClosedAndResScale(valid)")) {
        static_sk_contour_measure_delete(contour_handle);
        SkContourMeasureIter_delete(iter);
        SkPath_delete(path);
        SkPathMeasure_delete(empty_measure);
        return 22;
    }
    if (!check(SkPathMeasure_getLength(path_measure) == 10.0f, "SkPathMeasure_getLength(valid)")) {
        SkPathMeasure_delete(path_measure);
        static_sk_contour_measure_delete(contour_handle);
        SkContourMeasureIter_delete(iter);
        SkPath_delete(path);
        SkPathMeasure_delete(empty_measure);
        return 23;
    }

    SkPathMeasure_delete(path_measure);
    static_sk_contour_measure_delete(contour_handle);
    SkContourMeasureIter_delete(iter);
    SkPath_delete(path);
    SkPathMeasure_delete(empty_measure);
    return 0;
}
