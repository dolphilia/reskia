//
// Created by dolphilia on 2024/04/04.
//

#include "static_sk_v2.h"
#include "handle_table.hpp"
#include "static_sk_v2-internal.h"

static reskia::static_registry::HandleTable<SkV2> static_sk_v2;

int static_sk_v2_make(SkV2 value) {
    return static_sk_v2.create(value);
}

void static_sk_v2_set(int key, SkV2 value) {
    static_sk_v2.set(key, value);
}

SkV2 static_sk_v2_get_entity(int key) {
    SkV2* entity = static_sk_v2.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_v2_delete(int key) {
    static_sk_v2.erase(key);
}

void * static_sk_v2_get_ptr(int key) { // -> SkV2 *
    return static_sk_v2.get_ptr(key);
}

}
