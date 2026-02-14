//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_image_filter.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_image_filter-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkImageFilter>> static_sk_image_filter_table;

int static_sk_image_filter_make(sk_sp<SkImageFilter> value) {
    return static_sk_image_filter_table.create(std::move(value));
}

void static_sk_image_filter_set(int key, sk_sp<SkImageFilter> value) {
    static_sk_image_filter_table.set(key, std::move(value));
}

sk_sp<SkImageFilter> static_sk_image_filter_borrow_entity(int key) {
    sk_sp<SkImageFilter>* entity = static_sk_image_filter_table.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkImageFilter> static_sk_image_filter_take_entity(int key) {
    return static_sk_image_filter_table.take_or_default(key);
}

sk_sp<SkImageFilter> static_sk_image_filter_get_entity(int key) {
    return static_sk_image_filter_borrow_entity(key);
}

extern "C" {

void static_sk_image_filter_delete(int key) {
    static_sk_image_filter_table.erase(key);
}

void *static_sk_image_filter_get_ptr(int key) { // -> SkImageFilter *
    sk_sp<SkImageFilter>* entity = static_sk_image_filter_table.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
