//
// Created by dolphilia on 2024/01/11.
//

#include "static_sk_runtime_effect_result.h"

#include <utility>
#include "static_sk_runtime_effect_result-internal.h"

static std::set<int> static_sk_runtime_effect_result_available_keys;
static std::map<int , SkRuntimeEffect::Result> static_sk_runtime_effect_result;
static int static_sk_runtime_effect_result_index = 0;

int static_sk_runtime_effect_result_make(SkRuntimeEffect::Result value) {
    int key;
    if (!static_sk_runtime_effect_result_available_keys.empty()) {
        auto it = static_sk_runtime_effect_result_available_keys.begin();
        key = *it;
        static_sk_runtime_effect_result_available_keys.erase(it);
    } else {
        key = static_sk_runtime_effect_result_index++;
    }
    static_sk_runtime_effect_result[key] = std::move(value);
    return key;
}

// const

void static_sk_runtime_effect_result_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_runtime_effect_result.erase(key);
    static_sk_runtime_effect_result_available_keys.insert(key);
}

SkRuntimeEffect::Result static_sk_runtime_effect_result_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_runtime_effect_result[key];
}

void * static_sk_runtime_effect_result_get_ptr(int key) { // -> SkRuntimeEffect::Result *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_runtime_effect_result[key];
}

void static_sk_runtime_effect_result_set(int key, SkRuntimeEffect::Result value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_runtime_effect_result[key] = std::move(value);
}
