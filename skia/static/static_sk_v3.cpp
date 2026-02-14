//
// Created by dolphilia on 2024/04/04.
//

#include "static_sk_v3.h"
#include "handle_table.hpp"
#include "static_sk_v3-internal.h"

static reskia::static_registry::HandleTable<SkV3> static_sk_v3;

int static_sk_v3_make(SkV3 value) {
    return static_sk_v3.create(value);
}

void static_sk_v3_set(int key, SkV3 value) {
    static_sk_v3.set(key, value);
}

SkV3 static_sk_v3_get_entity(int key) {
    SkV3* entity = static_sk_v3.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_v3_delete(int key) {
    static_sk_v3.erase(key);
}

void * static_sk_v3_get_ptr(int key) { // -> SkV3 *
    return static_sk_v3.get_ptr(key);
}

}
