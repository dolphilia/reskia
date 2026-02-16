//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_typeface.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_typeface-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkTypeface>> static_sk_typeface;

int static_sk_typeface_make(sk_sp<SkTypeface> value) {
    return static_sk_typeface.create(std::move(value));
}

void static_sk_typeface_set(int key, sk_sp<SkTypeface> value) {
    static_sk_typeface.set(key, std::move(value));
}

sk_sp<SkTypeface> static_sk_typeface_borrow_entity(int key) {
    sk_sp<SkTypeface>* entity = static_sk_typeface.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkTypeface> static_sk_typeface_take_entity(int key) {
    return static_sk_typeface.take_or_default(key);
}

sk_sp<SkTypeface> static_sk_typeface_get_entity(int key) {
    return static_sk_typeface_borrow_entity(key);
}

extern "C" {

void static_sk_typeface_delete(int key) {
    static_sk_typeface.erase(key);
}

void * static_sk_typeface_get_ptr(int key) { // -> SkTypeface *
    sk_sp<SkTypeface>* entity = static_sk_typeface.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
