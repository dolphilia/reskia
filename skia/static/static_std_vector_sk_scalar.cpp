//
// Created by dolphilia on 2024/01/08.
//

#include "static_std_vector_sk_scalar.h"

#include <utility>
#include "handle_table.hpp"
#include "static_std_vector_sk_scalar-internal.h"

static reskia::static_registry::HandleTable<std::vector<SkScalar>> static_vector_float;

int static_vector_sk_scalar_make(std::vector<SkScalar> value) {
    return static_vector_float.create(std::move(value));
}

void static_vector_sk_scalar_set(int key, std::vector<SkScalar> value) {
    static_vector_float.set(key, std::move(value));
}

extern "C" {

void static_vector_sk_scalar_delete(int key) {
    static_vector_float.erase(key);
}

float static_vector_sk_scalar_get(int key, int index) { // -> SkScalar
    std::vector<SkScalar>* entity = static_vector_float.get_ptr(key);
    if (entity == nullptr || index < 0 || static_cast<size_t>(index) >= entity->size()) {
        return 0.0f;
    }
    return (*entity)[index];
}

void static_vector_sk_scalar_push_back(int key, float value) { // SkScalar value
    std::vector<SkScalar>* entity = static_vector_float.get_ptr(key);
    if (entity == nullptr) {
        return;
    }
    entity->push_back(value);
}

void static_vector_sk_scalar_insert(int key, int index, float value) { // SkScalar value
    std::vector<SkScalar>* entity = static_vector_float.get_ptr(key);
    if (entity == nullptr || index < 0 || static_cast<size_t>(index) > entity->size()) {
        return;
    }
    entity->insert(entity->begin() + index, value);
}

void static_vector_sk_scalar_pop_back(int key) {
    std::vector<SkScalar>* entity = static_vector_float.get_ptr(key);
    if (entity == nullptr || entity->empty()) {
        return;
    }
    entity->pop_back();
}

void static_vector_sk_scalar_erase(int key, int index) {
    std::vector<SkScalar>* entity = static_vector_float.get_ptr(key);
    if (entity == nullptr || index < 0 || static_cast<size_t>(index) >= entity->size()) {
        return;
    }
    entity->erase(entity->begin() + index);
}

}
