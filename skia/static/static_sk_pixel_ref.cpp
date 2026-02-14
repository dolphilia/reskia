//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_pixel_ref.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_pixel_ref-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkPixelRef>> static_sk_pixel_ref;

int static_sk_pixel_ref_make(sk_sp<SkPixelRef> value) {
    return static_sk_pixel_ref.create(std::move(value));
}

void static_sk_pixel_ref_set(int key, sk_sp<SkPixelRef> value) {
    static_sk_pixel_ref.set(key, std::move(value));
}

sk_sp<SkPixelRef> static_sk_pixel_ref_borrow_entity(int key) {
    sk_sp<SkPixelRef>* entity = static_sk_pixel_ref.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkPixelRef> static_sk_pixel_ref_take_entity(int key) {
    return static_sk_pixel_ref.take_or_default(key);
}

sk_sp<SkPixelRef> static_sk_pixel_ref_get_entity(int key) {
    return static_sk_pixel_ref_borrow_entity(key);
}

extern "C" {

void static_sk_pixel_ref_delete(int key) {
    static_sk_pixel_ref.erase(key);
}

void *static_sk_pixel_ref_get_ptr(int key) { // -> SkPixelRef *
    sk_sp<SkPixelRef>* entity = static_sk_pixel_ref.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
