//
// Created by dolphilia on 2024/03/30.
//

#include "static_sk_point.h"
#include "handle_table.hpp"
#include "static_sk_point-internal.h"

static reskia::static_registry::HandleTable<SkPoint> static_sk_point;

int static_sk_point_make(SkPoint value) {
    return static_sk_point.create(value);
}

void static_sk_point_set(int key, SkPoint value) {
    static_sk_point.set(key, value);
}

SkPoint static_sk_point_get_entity(int key) {
    SkPoint* entity = static_sk_point.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_point_delete(int key) {
    static_sk_point.erase(key);
}

void * static_sk_point_get_ptr(int key) { // -> SkPoint *
    return static_sk_point.get_ptr(key);
}

}
