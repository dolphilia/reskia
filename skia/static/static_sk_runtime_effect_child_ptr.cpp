//
// Created by dolphilia on 2024/01/10.
//

#include "static_sk_runtime_effect_child_ptr.h"
#include "handle_table.hpp"
#include "static_sk_runtime_effect_child_ptr-internal.h"

static reskia::static_registry::HandleTable<SkSpan<const SkRuntimeEffect::ChildPtr>> static_const_sk_runtime_effect_child_ptr;

// const

int static_const_sk_runtime_effect_child_ptr_make(SkSpan<const SkRuntimeEffect::ChildPtr> value) {
    return static_const_sk_runtime_effect_child_ptr.create(value);
}

void static_const_sk_runtime_effect_child_ptr_set(int key, SkSpan<const SkRuntimeEffect::ChildPtr> value) {
    static_const_sk_runtime_effect_child_ptr.set(key, value);
}

SkSpan<const SkRuntimeEffect::ChildPtr> static_const_sk_runtime_effect_child_ptr_get_entity(int key) {
    SkSpan<const SkRuntimeEffect::ChildPtr>* entity = static_const_sk_runtime_effect_child_ptr.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_const_sk_runtime_effect_child_ptr_delete(int key) {
    static_const_sk_runtime_effect_child_ptr.erase(key);
}

const void * static_const_sk_runtime_effect_child_ptr_get_ptr(int key, int index) { // -> const SkRuntimeEffect::ChildPtr *
    SkSpan<const SkRuntimeEffect::ChildPtr>* entity = static_const_sk_runtime_effect_child_ptr.get_ptr(key);
    if (entity == nullptr || index < 0 || static_cast<size_t>(index) >= entity->size()) {
        return nullptr;
    }
    return &(*entity)[index];
}

}
