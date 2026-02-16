//
// Created by dolphilia on 2024/01/04.
//

#include "static_sk_rect.h"
#include "handle_table.hpp"
#include "static_sk_rect-internal.h"

static reskia::static_registry::HandleTable<SkRect> static_sk_rect;

int static_sk_rect_make(SkRect value) {
    return static_sk_rect.create(value);
}

void static_sk_rect_set(int key, SkRect value) {
    static_sk_rect.set(key, value);
}

SkRect static_sk_rect_get_entity(int key) {
    SkRect* entity = static_sk_rect.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_rect_delete(int key) {
    static_sk_rect.erase(key);
}

void *static_sk_rect_get_ptr(int key) { // -> SkRect *
    return static_sk_rect.get_ptr(key);
}

}
