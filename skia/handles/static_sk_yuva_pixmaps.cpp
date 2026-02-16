//
// Created by dolphilia on 2024/01/11.
//

#include "static_sk_yuva_pixmaps.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_yuva_pixmaps-internal.h"

static reskia::static_registry::HandleTable<SkYUVAPixmaps> static_sk_yuva_pixmaps;

int static_sk_yuva_pixmaps_make(SkYUVAPixmaps value) {
    return static_sk_yuva_pixmaps.create(std::move(value));
}

void static_sk_yuva_pixmaps_set(int key, SkYUVAPixmaps value) {
    static_sk_yuva_pixmaps.set(key, std::move(value));
}

SkYUVAPixmaps static_sk_yuva_pixmaps_get_entity(int key) {
    SkYUVAPixmaps* entity = static_sk_yuva_pixmaps.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_yuva_pixmaps_delete(int key) {
    static_sk_yuva_pixmaps.erase(key);
}

void * static_sk_yuva_pixmaps_get_ptr(int key) { // -> SkYUVAPixmaps *
    return static_sk_yuva_pixmaps.get_ptr(key);
}

}
