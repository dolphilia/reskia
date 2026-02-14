//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_mask_filter.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_mask_filter-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkMaskFilter>> static_sk_mask_filter;

int static_sk_mask_filter_make(sk_sp<SkMaskFilter> value) {
    return static_sk_mask_filter.create(std::move(value));
}

void static_sk_mask_filter_set(int key, sk_sp<SkMaskFilter> value) {
    static_sk_mask_filter.set(key, std::move(value));
}

sk_sp<SkMaskFilter> static_sk_mask_filter_borrow_entity(int key) {
    sk_sp<SkMaskFilter>* entity = static_sk_mask_filter.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkMaskFilter> static_sk_mask_filter_take_entity(int key) {
    return static_sk_mask_filter.take_or_default(key);
}

sk_sp<SkMaskFilter> static_sk_mask_filter_get_entity(int key) {
    return static_sk_mask_filter_borrow_entity(key);
}

extern "C" {

void static_sk_mask_filter_delete(int key) {
    static_sk_mask_filter.erase(key);
}

void *static_sk_mask_filter_get_ptr(int key) { // -> SkMaskFilter *
    sk_sp<SkMaskFilter>* entity = static_sk_mask_filter.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
