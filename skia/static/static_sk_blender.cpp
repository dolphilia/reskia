//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_blender.h"
#include "static_sk_blender-internal.h"
#include "handle_table.hpp"

static reskia::static_registry::HandleTable<sk_sp<SkBlender>> static_sk_blender;

int static_sk_blender_make(sk_sp<SkBlender> value) {
    return static_sk_blender.create(std::move(value));
}

void static_sk_blender_set(int key, sk_sp<SkBlender> value) {
    static_sk_blender.set(key, std::move(value));
}

sk_sp<SkBlender> static_sk_blender_borrow_entity(int key) {
    sk_sp<SkBlender>* entity = static_sk_blender.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkBlender> static_sk_blender_take_entity(int key) {
    return static_sk_blender.take_or_default(key);
}

sk_sp<SkBlender> static_sk_blender_get_entity(int key) {
    return static_sk_blender_borrow_entity(key);
}

extern "C" {

void static_sk_blender_delete(int key) {
    static_sk_blender.erase(key);
}

void *static_sk_blender_get_ptr(int key) { // -> SkBlender *
    sk_sp<SkBlender>* entity = static_sk_blender.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
