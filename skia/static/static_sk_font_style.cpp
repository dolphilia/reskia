//
// Created by dolphilia on 2024/01/11.
//

#include "static_sk_font_style.h"
#include "static_sk_font_style-internal.h"
#include "handle_table.hpp"

static reskia::static_registry::HandleTable<SkFontStyle> static_sk_font_style;

int static_sk_font_style_make(SkFontStyle value) {
    return static_sk_font_style.create(value);
}

void static_sk_font_style_set(int key, SkFontStyle value) {
    static_sk_font_style.set(key, value);
}

SkFontStyle static_sk_font_style_get_entity(int key) {
    SkFontStyle* entity = static_sk_font_style.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_font_style_delete(int key) {
    static_sk_font_style.erase(key);
}

void * static_sk_font_style_get_ptr(int key) { // -> SkFontStyle *
    SkFontStyle* entity = static_sk_font_style.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity;
}

}
