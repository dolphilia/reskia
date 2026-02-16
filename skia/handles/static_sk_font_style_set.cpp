//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_font_style_set.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_font_style_set-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkFontStyleSet>> static_sk_font_style_set;

int static_sk_font_style_set_make(sk_sp<SkFontStyleSet> value) {
    return static_sk_font_style_set.create(std::move(value));
}

void static_sk_font_style_set_set(int key, sk_sp<SkFontStyleSet> value) {
    static_sk_font_style_set.set(key, std::move(value));
}

sk_sp<SkFontStyleSet> static_sk_font_style_set_borrow_entity(int key) {
    sk_sp<SkFontStyleSet>* entity = static_sk_font_style_set.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkFontStyleSet> static_sk_font_style_set_take_entity(int key) {
    return static_sk_font_style_set.take_or_default(key);
}

sk_sp<SkFontStyleSet> static_sk_font_style_set_get_entity(int key) {
    return static_sk_font_style_set_borrow_entity(key);
}

extern "C" {

void static_sk_font_style_set_delete(int key) {
    static_sk_font_style_set.erase(key);
}

void *static_sk_font_style_set_get_ptr(int key) { // -> SkFontStyleSet *
    sk_sp<SkFontStyleSet>* entity = static_sk_font_style_set.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
