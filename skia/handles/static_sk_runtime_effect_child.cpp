//
// Created by dolphilia on 2024/01/11.
//

#include "static_sk_runtime_effect_child.h"
#include "handle_table.hpp"
#include "static_sk_runtime_effect_child-internal.h"

static reskia::static_registry::HandleTable<SkSpan<const SkRuntimeEffect::Child>> static_const_sk_runtime_effect_child;

// const

int static_const_sk_runtime_effect_child_make(SkSpan<const SkRuntimeEffect::Child> value) {
    return static_const_sk_runtime_effect_child.create(value);
}

void static_const_sk_runtime_effect_child_set(int key, SkSpan<const SkRuntimeEffect::Child> value) {
    static_const_sk_runtime_effect_child.set(key, value);
}

SkSpan<const SkRuntimeEffect::Child> static_const_sk_runtime_effect_child_get_entity(int key) {
    SkSpan<const SkRuntimeEffect::Child>* entity = static_const_sk_runtime_effect_child.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_const_sk_runtime_effect_child_delete(int key) {
    static_const_sk_runtime_effect_child.erase(key);
}

const void * static_const_sk_runtime_effect_child_get_ptr(int key, int index) { // -> const SkRuntimeEffect::Child *
    SkSpan<const SkRuntimeEffect::Child>* entity = static_const_sk_runtime_effect_child.get_ptr(key);
    if (entity == nullptr || index < 0 || static_cast<size_t>(index) >= entity->size()) {
        return nullptr;
    }
    return &(*entity)[index];
}

}
