//
// Created by dolphilia on 2024/01/08.
//

#include "static_sk_color_info.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_color_info-internal.h"

static reskia::static_registry::HandleTable<SkColorInfo> static_sk_color_info;

int static_sk_color_info_make(SkColorInfo value) {
    return static_sk_color_info.create(std::move(value));
}

void static_sk_color_info_set(int key, SkColorInfo value) {
    static_sk_color_info.set(key, std::move(value));
}

SkColorInfo static_sk_color_info_get_entity(int key) {
    SkColorInfo* entity = static_sk_color_info.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_color_info_delete(int key) {
    static_sk_color_info.erase(key);
}

void * static_sk_color_info_get_ptr(int key) { // -> SkColorInfo *
    SkColorInfo* entity = static_sk_color_info.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity;
}

}
