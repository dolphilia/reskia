//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_contour_measure.h"

#include <utility>
#include "static_sk_contour_measure-internal.h"

static std::set<int> static_sk_contour_measure_available_keys;
static std::map<int , sk_sp<SkContourMeasure>> static_sk_contour_measure;
static int static_sk_contour_measure_index = 0;

int static_sk_contour_measure_make(sk_sp<SkContourMeasure> value) {
    int key;
    if (!static_sk_contour_measure_available_keys.empty()) {
        auto it = static_sk_contour_measure_available_keys.begin();
        key = *it;
        static_sk_contour_measure_available_keys.erase(it);
    } else {
        key = static_sk_contour_measure_index++;
    }
    static_sk_contour_measure[key] = std::move(value);
    return key;
}

void static_sk_contour_measure_set(int key, sk_sp<SkContourMeasure> value) {
    static_sk_contour_measure[key] = std::move(value);
}

sk_sp<SkContourMeasure> static_sk_contour_measure_get_entity(int key) {
    return std::move(static_sk_contour_measure[key]);
}

extern "C" {

void static_sk_contour_measure_delete(int key) {
    static_sk_contour_measure[key].reset();
    static_sk_contour_measure.erase(key);
    static_sk_contour_measure_available_keys.insert(key);
}

void *static_sk_contour_measure_get_ptr(int key) { // -> SkContourMeasure *
    return static_sk_contour_measure[key].get();
}

}