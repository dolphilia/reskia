//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_surface.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_surface-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkSurface>> static_sk_surface;

int static_sk_surface_make(sk_sp<SkSurface> value) {
    return static_sk_surface.create(std::move(value));
}

void static_sk_surface_set(int key, sk_sp<SkSurface> value) {
    static_sk_surface.set(key, std::move(value));
}

sk_sp<SkSurface> static_sk_surface_borrow_entity(int key) {
    sk_sp<SkSurface>* entity = static_sk_surface.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkSurface> static_sk_surface_take_entity(int key) {
    return static_sk_surface.take_or_default(key);
}

sk_sp<SkSurface> static_sk_surface_get_entity(int key) {
    return static_sk_surface_borrow_entity(key);
}

extern "C" {

void static_sk_surface_delete(int key) {
    static_sk_surface.erase(key);
}

void * static_sk_surface_get_ptr(int key) { // -> SkSurface *
    sk_sp<SkSurface>* entity = static_sk_surface.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return entity->get();
}

}
