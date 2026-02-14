//
// Created by dolphilia on 2024/01/11.
//

#include "static_sk_yuva_info.h"
#include "handle_table.hpp"
#include "static_sk_yuva_info-internal.h"

static reskia::static_registry::HandleTable<SkYUVAInfo> static_sk_yuva_info;

int static_sk_yuva_info_make(SkYUVAInfo value) {
    return static_sk_yuva_info.create(value);
}

void static_sk_yuva_info_set(int key, SkYUVAInfo value) {
    static_sk_yuva_info.set(key, value);
}

SkYUVAInfo static_sk_yuva_info_get_entity(int key) {
    SkYUVAInfo* entity = static_sk_yuva_info.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_yuva_info_delete(int key) {
    static_sk_yuva_info.erase(key);
}

void * static_sk_yuva_info_get_ptr(int key) { // -> SkYUVAInfo *
    return static_sk_yuva_info.get_ptr(key);
}

}
