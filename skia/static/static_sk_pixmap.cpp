//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_pixmap.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_pixmap-internal.h"

static reskia::static_registry::HandleTable<SkPixmap> static_sk_pixmap;

int static_sk_pixmap_make(SkPixmap value) {
    return static_sk_pixmap.create(std::move(value));
}

void static_sk_pixmap_set(int key, SkPixmap value) {
    static_sk_pixmap.set(key, std::move(value));
}

SkPixmap static_sk_pixmap_get_entity(int key) {
    SkPixmap* entity = static_sk_pixmap.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_pixmap_delete(int key) {
    static_sk_pixmap.erase(key);
}

void * static_sk_pixmap_get_ptr(int key) { // -> SkPixmap *
    return static_sk_pixmap.get_ptr(key);
}

}
