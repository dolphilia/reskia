//
// Created by dolphilia on 2024/01/06.
//

#include "static_sk_matrix.h"
#include "static_sk_matrix-internal.h"

static std::set<int> static_sk_matrix_available_keys;
static std::map<int , SkMatrix> static_sk_matrix;
static int static_sk_matrix_index = 0;

int static_sk_matrix_make(SkMatrix value) {
    int key;
    if (!static_sk_matrix_available_keys.empty()) {
        auto it = static_sk_matrix_available_keys.begin();
        key = *it;
        static_sk_matrix_available_keys.erase(it);
    } else {
        key = static_sk_matrix_index++;
    }
    static_sk_matrix[key] = value;
    return key;
}

void static_sk_matrix_set(int key, SkMatrix value) {
    static_sk_matrix[key] = value;
}

SkMatrix static_sk_matrix_get_entity(int key) {
    return static_sk_matrix[key];
}

extern "C" {

void static_sk_matrix_delete(int key) {
    static_sk_matrix.erase(key);
    static_sk_matrix_available_keys.insert(key);
}

void * static_sk_matrix_get_ptr(int key) { // -> SkMatrix *
    return &static_sk_matrix[key];
}

}