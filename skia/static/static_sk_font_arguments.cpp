//
// Created by dolphilia on 2024/01/08.
//

#include "static_sk_font_arguments.h"
#include "static_sk_font_arguments-internal.h"

static std::set<int> static_sk_font_arguments_available_keys;
static std::map<int , SkFontArguments> static_sk_font_arguments;
static int static_sk_font_arguments_index = 0;

int static_sk_font_arguments_make(SkFontArguments value) {
    int key;
    if (!static_sk_font_arguments_available_keys.empty()) {
        auto it = static_sk_font_arguments_available_keys.begin();
        key = *it;
        static_sk_font_arguments_available_keys.erase(it);
    } else {
        key = static_sk_font_arguments_index++;
    }
    static_sk_font_arguments[key] = value;
    return key;
}

void static_sk_font_arguments_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_font_arguments.erase(key);
    static_sk_font_arguments_available_keys.insert(key);
}

SkFontArguments static_sk_font_arguments_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_font_arguments[key];
}

void * static_sk_font_arguments_get_ptr(int key) { // -> SkFontArguments *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_font_arguments[key];
}

void static_sk_font_arguments_set(int key, SkFontArguments value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_font_arguments[key] = value;
}
