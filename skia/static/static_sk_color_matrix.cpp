//
// Created by dolphilia on 2024/01/08.
//

#include "static_sk_color_matrix.h"
#include "static_sk_color_matrix-internal.h"
#include "handle_table.hpp"

static reskia::static_registry::HandleTable<SkColorMatrix> static_sk_color_matrix;

int static_sk_color_matrix_make(SkColorMatrix value) {
    return static_sk_color_matrix.create(value);
}

void static_sk_color_matrix_set(int key, SkColorMatrix value) {
    static_sk_color_matrix.set(key, value);
}

SkColorMatrix static_sk_color_matrix_get_entity(int key) {
    SkColorMatrix* entity = static_sk_color_matrix.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_color_matrix_delete(int key) {
    static_sk_color_matrix.erase(key);
}

void * static_sk_color_matrix_get_ptr(int key) { // -> SkColorMatrix *
    SkColorMatrix* entity = static_sk_color_matrix.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity;
}

}
