//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_color_filter.h"
#include "static_sk_color_filter-internal.h"
#include "handle_table.hpp"

static reskia::static_registry::HandleTable<sk_sp<SkColorFilter>> static_sk_color_filter;

int static_sk_color_filter_make(sk_sp<SkColorFilter> value) {
    return static_sk_color_filter.create(std::move(value));
}

void static_sk_color_filter_set(int key, sk_sp<SkColorFilter> value) {
    static_sk_color_filter.set(key, std::move(value));
}

sk_sp<SkColorFilter> static_sk_color_filter_borrow_entity(int key) {
    sk_sp<SkColorFilter>* entity = static_sk_color_filter.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkColorFilter> static_sk_color_filter_take_entity(int key) {
    return static_sk_color_filter.take_or_default(key);
}

sk_sp<SkColorFilter> static_sk_color_filter_get_entity(int key) {
    return static_sk_color_filter_borrow_entity(key);
}

extern "C" {

void static_sk_color_filter_delete(int key) {
    static_sk_color_filter.erase(key);
}

void *static_sk_color_filter_get_ptr(int key) {
    sk_sp<SkColorFilter>* entity = static_sk_color_filter.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
