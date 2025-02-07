//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_shader.h"

#include <utility>
#include "static_sk_shader-internal.h"

static std::set<int> static_sk_shader_available_keys;
static std::map<int , sk_sp<SkShader>> static_sk_shader;
static int static_sk_shader_index = 0;

int static_sk_shader_make(sk_sp<SkShader> value) {
    int key;
    if (!static_sk_shader_available_keys.empty()) {
        auto it = static_sk_shader_available_keys.begin();
        key = *it;
        static_sk_shader_available_keys.erase(it);
    } else {
        key = static_sk_shader_index++;
    }
    static_sk_shader[key] = std::move(value);
    return key;
}

void static_sk_shader_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_shader[key].reset();
    static_sk_shader.erase(key);
    static_sk_shader_available_keys.insert(key);
}

void * static_sk_shader_get(int key) { // -> SkShader *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_shader[key].get();
}

void static_sk_shader_set(int key, sk_sp<SkShader> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_shader[key] = std::move(value);
}

sk_sp<SkShader> static_sk_shader_move(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return std::move(static_sk_shader[key]);
}
