//
// Created by dolphilia on 2024/03/30.
//

#include "static_sk_i_point.h"
#include "static_sk_i_point-internal.h"
#include "handle_table.hpp"

static reskia::static_registry::HandleTable<SkIPoint> static_sk_i_point;

int static_sk_i_point_make(SkIPoint value) {
    return static_sk_i_point.create(value);
}

void static_sk_i_point_set(int key, SkIPoint value) {
    static_sk_i_point.set(key, value);
}

SkIPoint static_sk_i_point_get_entity(int key) {
    SkIPoint* entity = static_sk_i_point.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_i_point_delete(int key) {
    static_sk_i_point.erase(key);
}

void * static_sk_i_point_get_ptr(int key) { // -> SkIPoint *
    SkIPoint* entity = static_sk_i_point.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity;
}

}
