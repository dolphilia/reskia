//
// Created by dolphilia on 2024/01/11.
//

#include "static_sk_runtime_effect_uniform.h"
#include "static_sk_runtime_effect_uniform-internal.h"

static std::set<int> static_const_sk_runtime_effect_uniform_available_keys;
static std::map<int , SkSpan<const SkRuntimeEffect::Uniform>> static_const_sk_runtime_effect_uniform;
static int static_const_sk_runtime_effect_uniform_index = 0;

int static_const_sk_runtime_effect_uniform_make(SkSpan<const SkRuntimeEffect::Uniform> value) {
    int key;
    if (!static_const_sk_runtime_effect_uniform_available_keys.empty()) {
        auto it = static_const_sk_runtime_effect_uniform_available_keys.begin();
        key = *it;
        static_const_sk_runtime_effect_uniform_available_keys.erase(it);
    } else {
        key = static_const_sk_runtime_effect_uniform_index++;
    }
    static_const_sk_runtime_effect_uniform[key] = value;
    return key;
}

void static_const_sk_runtime_effect_uniform_set(int key, SkSpan<const SkRuntimeEffect::Uniform> value) {
    static_const_sk_runtime_effect_uniform[key] = value;
}

SkSpan<const SkRuntimeEffect::Uniform> static_const_sk_runtime_effect_uniform_get_entity(int key) {
    return static_const_sk_runtime_effect_uniform[key];
}

extern "C" {

void static_const_sk_runtime_effect_uniform_delete(int key) {
    static_const_sk_runtime_effect_uniform.erase(key);
    static_const_sk_runtime_effect_uniform_available_keys.insert(key);
}

const void * static_const_sk_runtime_effect_uniform_get_ptr(int key, int index) { // -> SkRuntimeEffect::Uniform *
    return &static_const_sk_runtime_effect_uniform[key][index];
}

}