//
// Created by dolphilia on 2024/03/30.
//

#include "static_sk_color_4f.h"
#include "static_sk_color_4f-internal.h"
#include "handle_table.hpp"

static reskia::static_registry::HandleTable<SkColor4f> static_sk_color_4f;

int static_sk_color_4f_make(SkColor4f value) {
    return static_sk_color_4f.create(value);
}

void static_sk_color_4f_set(int key, SkColor4f value) {
    static_sk_color_4f.set(key, value);
}

SkColor4f static_sk_color_4f_get_entity(int key) {
    SkColor4f* entity = static_sk_color_4f.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_color_4f_delete(int key) {
    static_sk_color_4f.erase(key);
}

void * static_sk_color_4f_get_ptr(int key) { // -> SkColor4f *
    SkColor4f* entity = static_sk_color_4f.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity;
}

}
