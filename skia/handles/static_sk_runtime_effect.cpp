//
// Created by dolphilia on 2024/01/12.
//

#include "static_sk_runtime_effect.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_runtime_effect-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkRuntimeEffect>> static_sk_runtime_effect;

int static_sk_runtime_effect_make(sk_sp<SkRuntimeEffect> value) {
    return static_sk_runtime_effect.create(std::move(value));
}

void static_sk_runtime_effect_set(int key, sk_sp<SkRuntimeEffect> value) {
    static_sk_runtime_effect.set(key, std::move(value));
}

sk_sp<SkRuntimeEffect> static_sk_runtime_effect_borrow_entity(int key) {
    sk_sp<SkRuntimeEffect>* entity = static_sk_runtime_effect.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkRuntimeEffect> static_sk_runtime_effect_take_entity(int key) {
    return static_sk_runtime_effect.take_or_default(key);
}

sk_sp<SkRuntimeEffect> static_sk_runtime_effect_get_entity(int key) {
    return static_sk_runtime_effect_borrow_entity(key);
}

extern "C" {

void static_sk_runtime_effect_delete(int key) {
    static_sk_runtime_effect.erase(key);
}

void *static_sk_runtime_effect_get_ptr(int key) { // -> SkRuntimeEffect *
    sk_sp<SkRuntimeEffect>* entity = static_sk_runtime_effect.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
