//
// Created by dolphilia on 2024/04/03.
//

#include "static_sk_font_arguments_variation_position.h"
#include "static_sk_font_arguments_variation_position-internal.h"

static std::set<int> static_sk_font_arguments_variation_position_available_keys;
static std::map<int , SkFontArguments::VariationPosition> static_sk_font_arguments_variation_position;
static int static_sk_font_arguments_variation_position_index = 0;

int static_sk_font_arguments_variation_position_make(SkFontArguments::VariationPosition value) {
    int key;
    if (!static_sk_font_arguments_variation_position_available_keys.empty()) {
        auto it = static_sk_font_arguments_variation_position_available_keys.begin();
        key = *it;
        static_sk_font_arguments_variation_position_available_keys.erase(it);
    } else {
        key = static_sk_font_arguments_variation_position_index++;
    }
    static_sk_font_arguments_variation_position[key] = value;
    return key;
}

void static_sk_font_arguments_variation_position_set(int key, SkFontArguments::VariationPosition value) {
    static_sk_font_arguments_variation_position[key] = value;
}

SkFontArguments::VariationPosition static_sk_font_arguments_variation_position_get_entity(int key) {
    return static_sk_font_arguments_variation_position[key];
}

extern "C" {

void static_sk_font_arguments_variation_position_delete(int key) {
    static_sk_font_arguments_variation_position.erase(key);
    static_sk_font_arguments_variation_position_available_keys.insert(key);
}

void * static_sk_font_arguments_variation_position_get_ptr(int key) { // -> SkFontArguments::VariationPosition *
    return &static_sk_font_arguments_variation_position[key];
}

}