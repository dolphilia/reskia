//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_path_effect.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_path_effect-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkPathEffect>> static_sk_path_effect;

int static_sk_path_effect_make(sk_sp<SkPathEffect> value) {
    return static_sk_path_effect.create(std::move(value));
}

void static_sk_path_effect_set(int key, sk_sp<SkPathEffect> value) {
    static_sk_path_effect.set(key, std::move(value));
}

sk_sp<SkPathEffect> static_sk_path_effect_borrow_entity(int key) {
    sk_sp<SkPathEffect>* entity = static_sk_path_effect.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkPathEffect> static_sk_path_effect_take_entity(int key) {
    return static_sk_path_effect.take_or_default(key);
}

sk_sp<SkPathEffect> static_sk_path_effect_get_entity(int key) {
    return static_sk_path_effect_borrow_entity(key);
}

extern "C" {

void static_sk_path_effect_delete(int key) {
    static_sk_path_effect.erase(key);
}

void *static_sk_path_effect_get_ptr(int key) { // -> SkPathEffect *
    sk_sp<SkPathEffect>* entity = static_sk_path_effect.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
