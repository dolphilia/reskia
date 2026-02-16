//
// Created by dolphilia on 2024/04/03.
//

#include "static_sk_font_arguments_palette.h"
#include "static_sk_font_arguments_palette-internal.h"
#include "handle_table.hpp"

static reskia::static_registry::HandleTable<SkFontArguments::Palette> static_sk_font_arguments_palette;

int static_sk_font_arguments_palette_make(SkFontArguments::Palette value) {
    return static_sk_font_arguments_palette.create(value);
}

void static_sk_font_arguments_palette_set(int key, SkFontArguments::Palette value) {
    static_sk_font_arguments_palette.set(key, value);
}

SkFontArguments::Palette static_sk_font_arguments_palette_get_entity(int key) {
    SkFontArguments::Palette* entity = static_sk_font_arguments_palette.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_font_arguments_palette_delete(int key) {
    static_sk_font_arguments_palette.erase(key);
}

void * static_sk_font_arguments_palette_get_ptr(int key) { // -> SkFontArguments::Palette *
    SkFontArguments::Palette* entity = static_sk_font_arguments_palette.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity;
}

}
