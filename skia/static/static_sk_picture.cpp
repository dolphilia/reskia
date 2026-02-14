//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_picture.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_picture-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkPicture>> static_sk_picture;

int static_sk_picture_make(sk_sp<SkPicture> value) {
    return static_sk_picture.create(std::move(value));
}

void static_sk_picture_set(int key, sk_sp<SkPicture> value) {
    static_sk_picture.set(key, std::move(value));
}

sk_sp<SkPicture> static_sk_picture_borrow_entity(int key) {
    sk_sp<SkPicture>* entity = static_sk_picture.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkPicture> static_sk_picture_take_entity(int key) {
    return static_sk_picture.take_or_default(key);
}

sk_sp<SkPicture> static_sk_picture_get_entity(int key) {
    return static_sk_picture_borrow_entity(key);
}

extern "C" {

void static_sk_picture_delete(int key) {
    static_sk_picture.erase(key);
}

void *static_sk_picture_get_ptr(int key) { // -> SkPicture *
    sk_sp<SkPicture>* entity = static_sk_picture.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
