//
// Created by dolphilia on 2024/01/11.
//

#include "static_sk_font_style.h"
#include "static_sk_font_style-internal.h"

static std::set<int> static_sk_font_style_available_keys;
static std::map<int , SkFontStyle> static_sk_font_style;
static int static_sk_font_style_index = 0;

int static_sk_font_style_make(SkFontStyle value) {
    int key;
    if (!static_sk_font_style_available_keys.empty()) {
        auto it = static_sk_font_style_available_keys.begin();
        key = *it;
        static_sk_font_style_available_keys.erase(it);
    } else {
        key = static_sk_font_style_index++;
    }
    static_sk_font_style[key] = value;
    return key;
}

void static_sk_font_style_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_font_style.erase(key);
    static_sk_font_style_available_keys.insert(key);
}

SkFontStyle static_sk_font_style_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_font_style[key];
}

void * static_sk_font_style_get_ptr(int key) { // -> SkFontStyle *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_font_style[key];
}

void static_sk_font_style_set(int key, SkFontStyle value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_font_style[key] = value;
}
