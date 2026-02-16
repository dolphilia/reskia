//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_shader.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_shader-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkShader>> static_sk_shader;

int static_sk_shader_make(sk_sp<SkShader> value) {
    return static_sk_shader.create(std::move(value));
}

void static_sk_shader_set(int key, sk_sp<SkShader> value) {
    static_sk_shader.set(key, std::move(value));
}

sk_sp<SkShader> static_sk_shader_borrow_entity(int key) {
    sk_sp<SkShader>* entity = static_sk_shader.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkShader> static_sk_shader_take_entity(int key) {
    return static_sk_shader.take_or_default(key);
}

sk_sp<SkShader> static_sk_shader_get_entity(int key) {
    return static_sk_shader_borrow_entity(key);
}

extern "C" {

void static_sk_shader_delete(int key) {
    static_sk_shader.erase(key);
}

void * static_sk_shader_get_ptr(int key) { // -> SkShader *
    sk_sp<SkShader>* entity = static_sk_shader.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
