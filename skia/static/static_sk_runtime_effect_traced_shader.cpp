//
// Created by dolphilia on 2024/01/11.
//

#include "static_sk_runtime_effect_traced_shader.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_runtime_effect_traced_shader-internal.h"

static reskia::static_registry::HandleTable<SkRuntimeEffect::TracedShader> static_sk_runtime_effect_traced_shader;

int static_sk_runtime_effect_traced_shader_make(SkRuntimeEffect::TracedShader value) {
    return static_sk_runtime_effect_traced_shader.create(std::move(value));
}

void static_sk_runtime_effect_traced_shader_set(int key, SkRuntimeEffect::TracedShader value) {
    static_sk_runtime_effect_traced_shader.set(key, std::move(value));
}

SkRuntimeEffect::TracedShader static_sk_runtime_effect_traced_shader_get_entity(int key) {
    SkRuntimeEffect::TracedShader* entity = static_sk_runtime_effect_traced_shader.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_runtime_effect_traced_shader_delete(int key) {
    static_sk_runtime_effect_traced_shader.erase(key);
}

void * static_sk_runtime_effect_traced_shader_get_ptr(int key) { // -> SkRuntimeEffect::TracedShader *
    return static_sk_runtime_effect_traced_shader.get_ptr(key);
}

}
