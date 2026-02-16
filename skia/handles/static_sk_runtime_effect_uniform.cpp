//
// Created by dolphilia on 2024/01/11.
//

#include "static_sk_runtime_effect_uniform.h"
#include "handle_table.hpp"
#include "static_sk_runtime_effect_uniform-internal.h"

static reskia::static_registry::HandleTable<SkSpan<const SkRuntimeEffect::Uniform>> static_const_sk_runtime_effect_uniform;

int static_const_sk_runtime_effect_uniform_make(SkSpan<const SkRuntimeEffect::Uniform> value) {
    return static_const_sk_runtime_effect_uniform.create(value);
}

void static_const_sk_runtime_effect_uniform_set(int key, SkSpan<const SkRuntimeEffect::Uniform> value) {
    static_const_sk_runtime_effect_uniform.set(key, value);
}

SkSpan<const SkRuntimeEffect::Uniform> static_const_sk_runtime_effect_uniform_get_entity(int key) {
    SkSpan<const SkRuntimeEffect::Uniform>* entity = static_const_sk_runtime_effect_uniform.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_const_sk_runtime_effect_uniform_delete(int key) {
    static_const_sk_runtime_effect_uniform.erase(key);
}

const void * static_const_sk_runtime_effect_uniform_get_ptr(int key, int index) { // -> SkRuntimeEffect::Uniform *
    SkSpan<const SkRuntimeEffect::Uniform>* entity = static_const_sk_runtime_effect_uniform.get_ptr(key);
    if (entity == nullptr || index < 0 || static_cast<size_t>(index) >= entity->size()) {
        return nullptr;
    }
    return &(*entity)[index];
}

}
