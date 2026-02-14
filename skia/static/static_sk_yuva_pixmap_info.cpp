//
// Created by dolphilia on 2024/01/11.
//

#include "static_sk_yuva_pixmap_info.h"
#include "handle_table.hpp"
#include "static_sk_yuva_pixmap_info-internal.h"

static reskia::static_registry::HandleTable<SkYUVAPixmapInfo> static_sk_yuva_pixmap_info;

int static_sk_yuva_pixmap_info_make(SkYUVAPixmapInfo value) {
    return static_sk_yuva_pixmap_info.create(value);
}

void static_sk_yuva_pixmap_info_set(int key, SkYUVAPixmapInfo value) {
    static_sk_yuva_pixmap_info.set(key, value);
}

SkYUVAPixmapInfo static_sk_yuva_pixmap_info_get_entity(int key) {
    SkYUVAPixmapInfo* entity = static_sk_yuva_pixmap_info.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_yuva_pixmap_info_delete(int key) {
    static_sk_yuva_pixmap_info.erase(key);
}

void * static_sk_yuva_pixmap_info_get_ptr(int key) { // -> SkYUVAPixmapInfo *
    return static_sk_yuva_pixmap_info.get_ptr(key);
}

}
