//
// Created by dolphilia on 2024/04/03.
//

#include "static_sk_font_arguments_variation_position.h"
#include "static_sk_font_arguments_variation_position-internal.h"
#include "handle_table.hpp"

static reskia::static_registry::HandleTable<SkFontArguments::VariationPosition> static_sk_font_arguments_variation_position;

int static_sk_font_arguments_variation_position_make(SkFontArguments::VariationPosition value) {
    return static_sk_font_arguments_variation_position.create(value);
}

void static_sk_font_arguments_variation_position_set(int key, SkFontArguments::VariationPosition value) {
    static_sk_font_arguments_variation_position.set(key, value);
}

SkFontArguments::VariationPosition static_sk_font_arguments_variation_position_get_entity(int key) {
    SkFontArguments::VariationPosition* entity = static_sk_font_arguments_variation_position.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_font_arguments_variation_position_delete(int key) {
    static_sk_font_arguments_variation_position.erase(key);
}

void * static_sk_font_arguments_variation_position_get_ptr(int key) { // -> SkFontArguments::VariationPosition *
    SkFontArguments::VariationPosition* entity = static_sk_font_arguments_variation_position.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity;
}

}
