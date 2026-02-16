//
// Created by dolphilia on 2024/01/10.
//

#include "static_sk_r_rect.h"
#include "handle_table.hpp"
#include "static_sk_r_rect-internal.h"

static reskia::static_registry::HandleTable<SkRRect> static_sk_r_rect;

int static_sk_r_rect_make(SkRRect value) {
    return static_sk_r_rect.create(value);
}

void static_sk_r_rect_set(int key, SkRRect value) {
    static_sk_r_rect.set(key, value);
}

SkRRect static_sk_r_rect_get_entity(int key) {
    SkRRect* entity = static_sk_r_rect.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_r_rect_delete(int key) {
    static_sk_r_rect.erase(key);
}

void * static_sk_r_rect_get_ptr(int key) { // -> SkRRect *
    return static_sk_r_rect.get_ptr(key);
}

}
