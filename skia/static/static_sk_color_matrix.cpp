//
// Created by dolphilia on 2024/01/08.
//

#include "static_sk_color_matrix.h"
#include "static_sk_color_matrix-internal.h"

static std::set<int> static_sk_color_matrix_available_keys;
static std::map<int , SkColorMatrix> static_sk_color_matrix;
static int static_sk_color_matrix_index = 0;


int static_sk_color_matrix_make(SkColorMatrix value) {
    int key;
    if (!static_sk_color_matrix_available_keys.empty()) {
        auto it = static_sk_color_matrix_available_keys.begin();
        key = *it;
        static_sk_color_matrix_available_keys.erase(it);
    } else {
        key = static_sk_color_matrix_index++;
    }
    static_sk_color_matrix[key] = value;
    return key;
}

void static_sk_color_matrix_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_color_matrix.erase(key);
    static_sk_color_matrix_available_keys.insert(key);
}

SkColorMatrix static_sk_color_matrix_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_color_matrix[key];
}

void * static_sk_color_matrix_get_ptr(int key) { // -> SkColorMatrix *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_color_matrix[key];
}

void static_sk_color_matrix_set(int key, SkColorMatrix value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_color_matrix[key] = value;
}
