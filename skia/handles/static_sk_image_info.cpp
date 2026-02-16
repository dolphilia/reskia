//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_image_info.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_image_info-internal.h"

static reskia::static_registry::HandleTable<SkImageInfo> static_sk_image_info;

int static_sk_image_info_make(SkImageInfo value) {
    return static_sk_image_info.create(std::move(value));
}

void static_sk_image_info_set(int key, SkImageInfo value) {
    static_sk_image_info.set(key, std::move(value));
}

SkImageInfo static_sk_image_info_get_entity(int key) {
    SkImageInfo* entity = static_sk_image_info.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_image_info_delete(int key) {
    static_sk_image_info.erase(key);
}

void * static_sk_image_info_get_ptr(int key) { // -> SkImageInfo *
    return static_sk_image_info.get_ptr(key);
}

}
