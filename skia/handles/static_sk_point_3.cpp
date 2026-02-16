//
// Created by dolphilia on 2024/04/05.
//

#include "static_sk_point_3.h"
#include "handle_table.hpp"
#include "static_sk_point_3-internal.h"

static reskia::static_registry::HandleTable<SkPoint3> static_sk_point_3;

int static_sk_point_3_make(SkPoint3 value) {
    return static_sk_point_3.create(value);
}

void static_sk_point_3_set(int key, SkPoint3 value) {
    static_sk_point_3.set(key, value);
}

SkPoint3 static_sk_point_3_get_entity(int key) {
    SkPoint3* entity = static_sk_point_3.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_point_3_delete(int key) {
    static_sk_point_3.erase(key);
}

void * static_sk_point_3_get_ptr(int key) { // -> SkPoint3 *
    return static_sk_point_3.get_ptr(key);
}

}
