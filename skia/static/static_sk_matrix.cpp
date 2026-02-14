//
// Created by dolphilia on 2024/01/06.
//

#include "static_sk_matrix.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_matrix-internal.h"

static reskia::static_registry::HandleTable<SkMatrix> static_sk_matrix;

int static_sk_matrix_make(SkMatrix value) {
    return static_sk_matrix.create(std::move(value));
}

void static_sk_matrix_set(int key, SkMatrix value) {
    static_sk_matrix.set(key, std::move(value));
}

SkMatrix static_sk_matrix_get_entity(int key) {
    SkMatrix* entity = static_sk_matrix.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_matrix_delete(int key) {
    static_sk_matrix.erase(key);
}

void * static_sk_matrix_get_ptr(int key) { // -> SkMatrix *
    return static_sk_matrix.get_ptr(key);
}

}
