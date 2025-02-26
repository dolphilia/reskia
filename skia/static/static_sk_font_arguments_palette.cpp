//
// Created by dolphilia on 2024/04/03.
//

#include "static_sk_font_arguments_palette.h"
#include "static_sk_font_arguments_palette-internal.h"

static std::set<int> static_sk_font_arguments_palette_available_keys;
static std::map<int , SkFontArguments::Palette> static_sk_font_arguments_palette;
static int static_sk_font_arguments_palette_index = 0;

int static_sk_font_arguments_palette_make(SkFontArguments::Palette value) {
    int key;
    if (!static_sk_font_arguments_palette_available_keys.empty()) {
        auto it = static_sk_font_arguments_palette_available_keys.begin();
        key = *it;
        static_sk_font_arguments_palette_available_keys.erase(it);
    } else {
        key = static_sk_font_arguments_palette_index++;
    }
    static_sk_font_arguments_palette[key] = value;
    return key;
}

void static_sk_font_arguments_palette_set(int key, SkFontArguments::Palette value) {
    static_sk_font_arguments_palette[key] = value;
}

SkFontArguments::Palette static_sk_font_arguments_palette_get_entity(int key) {
    return static_sk_font_arguments_palette[key];
}

extern "C" {

void static_sk_font_arguments_palette_delete(int key) {
    static_sk_font_arguments_palette.erase(key);
    static_sk_font_arguments_palette_available_keys.insert(key);
}

void * static_sk_font_arguments_palette_get_ptr(int key) { // -> SkFontArguments::Palette *
    return &static_sk_font_arguments_palette[key];
}

}