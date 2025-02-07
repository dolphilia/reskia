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

void static_sk_font_arguments_variation_position_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_font_arguments_variation_position.erase(key);
    static_sk_font_arguments_variation_position_available_keys.insert(key);
}

SkFontArguments::VariationPosition static_sk_font_arguments_variation_position_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_font_arguments_variation_position[key];
}

void * static_sk_font_arguments_variation_position_get_ptr(int key) { // -> SkFontArguments::VariationPosition *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_font_arguments_variation_position[key];
}

void static_sk_font_arguments_variation_position_set(int key, SkFontArguments::VariationPosition value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_font_arguments_variation_position[key] = value;
}
