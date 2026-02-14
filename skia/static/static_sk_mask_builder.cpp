//
// Created by dolphilia on 25/01/30.
//

#include "static_sk_mask_builder.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_mask_builder-internal.h"

static reskia::static_registry::HandleTable<SkMaskBuilder> static_sk_mask_builder;

int static_sk_mask_builder_make(SkMaskBuilder value) {
    return static_sk_mask_builder.create(std::move(value));
}

void static_sk_mask_builder_set(int key, SkMaskBuilder value) {
    static_sk_mask_builder.set(key, std::move(value));
}

extern "C" {

void static_sk_mask_builder_delete(int key) {
    static_sk_mask_builder.erase(key);
}

void * static_sk_mask_builder_get_ptr(int key) { // -> SkMaskBuilder *
    return static_sk_mask_builder.get_ptr(key);
}

}
