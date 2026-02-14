//
// Created by dolphilia on 2024/04/04.
//

#include "static_sk_v4.h"
#include "handle_table.hpp"
#include "static_sk_v4-internal.h"

static reskia::static_registry::HandleTable<SkV4> static_sk_v4;

int static_sk_v4_make(SkV4 value) {
    return static_sk_v4.create(value);
}

void static_sk_v4_set(int key, SkV4 value) {
    static_sk_v4.set(key, value);
}

SkV4 static_sk_v4_get_entity(int key) {
    SkV4* entity = static_sk_v4.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_v4_delete(int key) {
    static_sk_v4.erase(key);
}

void * static_sk_v4_get_ptr(int key) { // -> SkV4 *
    return static_sk_v4.get_ptr(key);
}

}
