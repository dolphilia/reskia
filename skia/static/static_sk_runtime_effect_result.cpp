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

void static_sk_runtime_effect_result_set(int key, SkRuntimeEffect::Result value) {
    static_sk_runtime_effect_result[key] = std::move(value);
}

SkRuntimeEffect::Result static_sk_runtime_effect_result_get_entity(int key) {
    return static_sk_runtime_effect_result[key];
}

extern "C" {

void static_sk_runtime_effect_result_delete(int key) {
    static_sk_runtime_effect_result.erase(key);
    static_sk_runtime_effect_result_available_keys.insert(key);
}

void * static_sk_runtime_effect_result_get_ptr(int key) { // -> SkRuntimeEffect::Result *
    return &static_sk_runtime_effect_result[key];
}

}