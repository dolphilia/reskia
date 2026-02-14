//
// Created by dolphilia on 2024/04/08.
//

#include "static_sk_runtime_effect_builder_builder_uniform.h"
#include "handle_table.hpp"
#include "static_sk_runtime_effect_builder_builder_uniform-internal.h"

static reskia::static_registry::HandleTable<SkRuntimeEffectBuilder::BuilderUniform>
    static_sk_runtime_effect_builder_builder_uniform;

int static_sk_runtime_effect_builder_builder_uniform_make(SkRuntimeEffectBuilder::BuilderUniform value) {
    return static_sk_runtime_effect_builder_builder_uniform.create(value);
}

void static_sk_runtime_effect_builder_builder_uniform_set(int key, SkRuntimeEffectBuilder::BuilderUniform value) {
    static_sk_runtime_effect_builder_builder_uniform.set(key, value);
}

SkRuntimeEffectBuilder::BuilderUniform static_sk_runtime_effect_builder_builder_uniform_get_entity(int key) {
    SkRuntimeEffectBuilder::BuilderUniform* entity = static_sk_runtime_effect_builder_builder_uniform.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_runtime_effect_builder_builder_uniform_delete(int key) {
    static_sk_runtime_effect_builder_builder_uniform.erase(key);
}

void * static_sk_runtime_effect_builder_builder_uniform_get_ptr(int key) { // -> SkRuntimeEffectBuilder::BuilderUniform *
    return static_sk_runtime_effect_builder_builder_uniform.get_ptr(key);
}

}
