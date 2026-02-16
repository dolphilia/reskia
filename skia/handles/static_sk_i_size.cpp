//
// Created by dolphilia on 2024/03/30.
//

#include "static_sk_i_size.h"
#include "static_sk_i_size-internal.h"
#include "handle_table.hpp"

static reskia::static_registry::HandleTable<SkISize> static_sk_i_size;

int static_sk_i_size_make(SkISize value) {
    return static_sk_i_size.create(value);
}

void static_sk_i_size_set(int key, SkISize value) {
    static_sk_i_size.set(key, value);
}

SkISize static_sk_i_size_get_entity(int key) {
    SkISize* entity = static_sk_i_size.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_i_size_delete(int key) {
    static_sk_i_size.erase(key);
}

void * static_sk_i_size_get_ptr(int key) { // -> SkISize *
    SkISize* entity = static_sk_i_size.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity;
}

}
