//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_drawable.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_drawable-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkDrawable>> static_sk_drawable;

int static_sk_drawable_make(sk_sp<SkDrawable> value) {
    return static_sk_drawable.create(std::move(value));
}

void static_sk_drawable_set(int key, sk_sp<SkDrawable> value) {
    static_sk_drawable.set(key, std::move(value));
}

sk_sp<SkDrawable> static_sk_drawable_borrow_entity(int key) {
    sk_sp<SkDrawable>* entity = static_sk_drawable.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkDrawable> static_sk_drawable_take_entity(int key) {
    return static_sk_drawable.take_or_default(key);
}

sk_sp<SkDrawable> static_sk_drawable_get_entity(int key) {
    return static_sk_drawable_borrow_entity(key);
}

extern "C" {

void static_sk_drawable_delete(int key) {
    static_sk_drawable.erase(key);
}

void *static_sk_drawable_get_ptr(int key) { // -> SkDrawable *
    sk_sp<SkDrawable>* entity = static_sk_drawable.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
