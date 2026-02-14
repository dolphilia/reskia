//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_i_rect.h"
#include "static_sk_i_rect-internal.h"
#include "handle_table.hpp"

static reskia::static_registry::HandleTable<SkIRect> static_sk_i_rect;

int static_sk_i_rect_make(SkIRect value) {
    return static_sk_i_rect.create(value);
}

void static_sk_i_rect_set(int key, SkIRect value) {
    static_sk_i_rect.set(key, value);
}

SkIRect static_sk_i_rect_get_entity(int key) {
    SkIRect* entity = static_sk_i_rect.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_i_rect_delete(int key) {
    static_sk_i_rect.erase(key);
}

void * static_sk_i_rect_get_ptr(int key) { // -> SkIRect *
    SkIRect* entity = static_sk_i_rect.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity;
}

}
