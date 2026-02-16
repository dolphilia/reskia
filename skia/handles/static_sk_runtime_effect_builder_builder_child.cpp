//
// Created by dolphilia on 2024/04/08.
//

#include "static_sk_runtime_effect_builder_builder_child.h"
#include "handle_table.hpp"
#include "static_sk_runtime_effect_builder_builder_child-internal.h"

static reskia::static_registry::HandleTable<SkRuntimeEffectBuilder::BuilderChild>
    static_sk_runtime_effect_builder_builder_child;

int static_sk_runtime_effect_builder_builder_child_make(SkRuntimeEffectBuilder::BuilderChild value) {
    return static_sk_runtime_effect_builder_builder_child.create(value);
}

void static_sk_runtime_effect_builder_builder_child_set(int key, SkRuntimeEffectBuilder::BuilderChild value) {
    static_sk_runtime_effect_builder_builder_child.set(key, value);
}

SkRuntimeEffectBuilder::BuilderChild static_sk_runtime_effect_builder_builder_child_get_entity(int key) {
    SkRuntimeEffectBuilder::BuilderChild* entity = static_sk_runtime_effect_builder_builder_child.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_runtime_effect_builder_builder_child_delete(int key) {
    static_sk_runtime_effect_builder_builder_child.erase(key);
}

void * static_sk_runtime_effect_builder_builder_child_get_ptr(int key) { // -> SkRuntimeEffectBuilder::BuilderChild *
    return static_sk_runtime_effect_builder_builder_child.get_ptr(key);
}

}
