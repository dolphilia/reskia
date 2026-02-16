//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_flattenable.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_flattenable-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkFlattenable>> static_sk_flattenable;

int static_sk_flattenable_make(sk_sp<SkFlattenable> value) {
    return static_sk_flattenable.create(std::move(value));
}

void static_sk_flattenable_set(int key, sk_sp<SkFlattenable> value) {
    static_sk_flattenable.set(key, std::move(value));
}

sk_sp<SkFlattenable> static_sk_flattenable_borrow_entity(int key) {
    sk_sp<SkFlattenable>* entity = static_sk_flattenable.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkFlattenable> static_sk_flattenable_take_entity(int key) {
    return static_sk_flattenable.take_or_default(key);
}

sk_sp<SkFlattenable> static_sk_flattenable_get_entity(int key) {
    return static_sk_flattenable_borrow_entity(key);
}

extern "C" {

void static_sk_flattenable_delete(int key) {
    static_sk_flattenable.erase(key);
}

void *static_sk_flattenable_get_ptr(int key) { // -> SkFlattenable *
    sk_sp<SkFlattenable>* entity = static_sk_flattenable.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
