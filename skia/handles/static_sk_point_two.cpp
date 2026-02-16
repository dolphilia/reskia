//
// Created by dolphilia on 24/06/20.
//

#include "static_sk_point_two.h"

#include <array>
#include "handle_table.hpp"
#include "static_sk_point_two-internal.h"

static reskia::static_registry::HandleTable<std::array<SkPoint, 2>> static_sk_point_two;

int static_sk_point_two_make(SkPoint value1, SkPoint value2) {
    return static_sk_point_two.create(std::array<SkPoint, 2>{value1, value2});
}

int static_sk_point_two_make_float(float fx1, float fy1, float fx2, float fy2) {
    SkPoint value1 = {fx1, fy1};
    SkPoint value2 = {fx2, fy2};
    return static_sk_point_two.create(std::array<SkPoint, 2>{value1, value2});
}

void static_sk_point_two_set(int key, SkPoint value1, SkPoint value2) {
    static_sk_point_two.set(key, std::array<SkPoint, 2>{value1, value2});
}

extern "C" {

void static_sk_point_two_delete(int key) {
    static_sk_point_two.erase(key);
}

void * static_sk_point_two_get_ptr(int key) { // -> SkPoint *
    std::array<SkPoint, 2>* entity = static_sk_point_two.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->data();
}

}
