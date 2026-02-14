//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_contour_measure.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_contour_measure-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkContourMeasure>> static_sk_contour_measure;

int static_sk_contour_measure_make(sk_sp<SkContourMeasure> value) {
    return static_sk_contour_measure.create(std::move(value));
}

void static_sk_contour_measure_set(int key, sk_sp<SkContourMeasure> value) {
    static_sk_contour_measure.set(key, std::move(value));
}

sk_sp<SkContourMeasure> static_sk_contour_measure_borrow_entity(int key) {
    sk_sp<SkContourMeasure>* entity = static_sk_contour_measure.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkContourMeasure> static_sk_contour_measure_take_entity(int key) {
    return static_sk_contour_measure.take_or_default(key);
}

sk_sp<SkContourMeasure> static_sk_contour_measure_get_entity(int key) {
    return static_sk_contour_measure_borrow_entity(key);
}

extern "C" {

void static_sk_contour_measure_delete(int key) {
    static_sk_contour_measure.erase(key);
}

void *static_sk_contour_measure_get_ptr(int key) { // -> SkContourMeasure *
    sk_sp<SkContourMeasure>* entity = static_sk_contour_measure.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
