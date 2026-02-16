//
// Created by dolphilia on 2024/01/08.
//

#include "static_sk_font.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_font-internal.h"

static reskia::static_registry::HandleTable<SkFont> static_sk_font;

int static_sk_font_make(SkFont value) {
    return static_sk_font.create(std::move(value));
}

void static_sk_font_set(int key, SkFont value) {
    static_sk_font.set(key, std::move(value));
}

SkFont static_sk_font_get_entity(int key) {
    SkFont* entity = static_sk_font.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_font_delete(int key) {
    static_sk_font.erase(key);
}

void * static_sk_font_get_ptr(int key) { // -> SkFont *
    SkFont* entity = static_sk_font.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity;
}

}
