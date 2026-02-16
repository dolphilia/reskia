//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_color_space.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_color_space-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkColorSpace>> static_sk_color_space;

int static_sk_color_space_make(sk_sp<SkColorSpace> value) {
    return static_sk_color_space.create(std::move(value));
}

void static_sk_color_space_set(int key, sk_sp<SkColorSpace> value) {
    static_sk_color_space.set(key, std::move(value));
}

sk_sp<SkColorSpace> static_sk_color_space_borrow_entity(int key) {
    sk_sp<SkColorSpace>* entity = static_sk_color_space.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkColorSpace> static_sk_color_space_take_entity(int key) {
    return static_sk_color_space.take_or_default(key);
}

sk_sp<SkColorSpace> static_sk_color_space_get_entity(int key) {
    return static_sk_color_space_borrow_entity(key);
}

extern "C" {

void static_sk_color_space_delete(int key) {
    static_sk_color_space.erase(key);
}

void *static_sk_color_space_get_ptr(int key) { // -> SkColorSpace *
    sk_sp<SkColorSpace>* entity = static_sk_color_space.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
