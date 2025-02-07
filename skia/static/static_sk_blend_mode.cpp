//
// Created by dolphilia on 2024/01/09.
//

#include "static_sk_blend_mode.h"
#include "static_sk_blend_mode-internal.h"
#include <set>

static std::set<int> static_optional_sk_blend_mode_available_keys;
static std::map<int, std::optional<SkBlendMode>> static_optional_sk_blend_mode;
static int static_optional_sk_blend_mode_index = 0;

int static_optional_sk_blend_mode_make(std::optional<SkBlendMode> value) {
    int key;
    if (!static_optional_sk_blend_mode_available_keys.empty()) {
        auto it = static_optional_sk_blend_mode_available_keys.begin();
        key = *it;
        static_optional_sk_blend_mode_available_keys.erase(it);
    } else {
        key = static_optional_sk_blend_mode_index++;
    }
    static_optional_sk_blend_mode[key] = value;
    return key;
}

void static_optional_sk_blend_mode_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_optional_sk_blend_mode[key].reset();
    static_optional_sk_blend_mode.erase(key);
    static_optional_sk_blend_mode_available_keys.insert(key);
}

int static_optional_sk_blend_mode_get(int key) { // // -> (int)SkBlendMode
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_cast<int>(*static_optional_sk_blend_mode[key]);
}

void static_optional_sk_blend_mode_set(int key, std::optional<SkBlendMode> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_optional_sk_blend_mode[key] = value;
}

std::optional<SkBlendMode> static_optional_sk_blend_mode_move(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_optional_sk_blend_mode[key];
}