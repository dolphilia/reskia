//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_mask_filter.h"

#include <utility>
#include "static_sk_mask_filter-internal.h"

static std::set<int> static_sk_mask_filter_available_keys;
static std::map<int , sk_sp<SkMaskFilter>> static_sk_mask_filter;
static int static_sk_mask_filter_index = 0;

int static_sk_mask_filter_make(sk_sp<SkMaskFilter> value) {
    int key;
    if (!static_sk_mask_filter_available_keys.empty()) {
        auto it = static_sk_mask_filter_available_keys.begin();
        key = *it;
        static_sk_mask_filter_available_keys.erase(it);
    } else {
        key = static_sk_mask_filter_index++;
    }
    static_sk_mask_filter[key] = std::move(value);
    return key;
}

void static_sk_mask_filter_set(int key, sk_sp<SkMaskFilter> value) {
    static_sk_mask_filter[key] = std::move(value);
}

sk_sp<SkMaskFilter> static_sk_mask_filter_get_entity(int key) {
    return std::move(static_sk_mask_filter[key]);
}

extern "C" {

void static_sk_mask_filter_delete(int key) {
    static_sk_mask_filter[key].reset();
    static_sk_mask_filter.erase(key);
    static_sk_mask_filter_available_keys.insert(key);
}

void *static_sk_mask_filter_get_ptr(int key) { // -> SkMaskFilter *
    return static_sk_mask_filter[key].get();
}

}