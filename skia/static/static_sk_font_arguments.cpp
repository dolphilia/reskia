//
// Created by dolphilia on 2024/01/08.
//

#include "static_sk_font_arguments.h"
#include "static_sk_font_arguments-internal.h"
#include "handle_table.hpp"

static reskia::static_registry::HandleTable<SkFontArguments> static_sk_font_arguments;

int static_sk_font_arguments_make(SkFontArguments value) {
    return static_sk_font_arguments.create(value);
}

void static_sk_font_arguments_set(int key, SkFontArguments value) {
    static_sk_font_arguments.set(key, value);
}

SkFontArguments static_sk_font_arguments_get_entity(int key) {
    SkFontArguments* entity = static_sk_font_arguments.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_font_arguments_delete(int key) {
    static_sk_font_arguments.erase(key);
}

void * static_sk_font_arguments_get_ptr(int key) { // -> SkFontArguments *
    SkFontArguments* entity = static_sk_font_arguments.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity;
}

}
