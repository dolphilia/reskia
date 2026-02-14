//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_image.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_image-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkImage>> static_sk_image_table;

int static_sk_image_make(sk_sp<SkImage> value) {
    return static_sk_image_table.create(std::move(value));
}

void static_sk_image_set(int key, sk_sp<SkImage> value) {
    static_sk_image_table.set(key, std::move(value));
}

sk_sp<SkImage> static_sk_image_borrow_entity(int key) {
    sk_sp<SkImage>* entity = static_sk_image_table.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkImage> static_sk_image_take_entity(int key) {
    return static_sk_image_table.take_or_default(key);
}

sk_sp<SkImage> static_sk_image_get_entity(int key) {
    return static_sk_image_borrow_entity(key);
}

extern "C" {

void static_sk_image_delete(int key) {
    static_sk_image_table.erase(key);
}

void *static_sk_image_get_ptr(int key) { // -> SkImage *
    sk_sp<SkImage>* entity = static_sk_image_table.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
