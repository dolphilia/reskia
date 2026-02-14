//
// Created by dolphilia on 2024/04/08.
//

#include "static_sk_size_t.h"
#include "handle_table.hpp"
#include "static_sk_size_t-internal.h"

static reskia::static_registry::HandleTable<SkSize> static_sk_size;

int static_sk_size_make(SkSize value) {
    return static_sk_size.create(value);
}

void static_sk_size_set(int key, SkSize value) {
    static_sk_size.set(key, value);
}

SkSize static_sk_size_get_entity(int key) {
    SkSize* entity = static_sk_size.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_size_delete(int key) {
    static_sk_size.erase(key);
}

void * static_sk_size_get_ptr(int key) { // -> SkSize *
    return static_sk_size.get_ptr(key);
}

}
