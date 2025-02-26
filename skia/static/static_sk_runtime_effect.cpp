//
// Created by dolphilia on 2024/01/12.
//

#include "static_sk_runtime_effect.h"

#include <utility>
#include "static_sk_runtime_effect-internal.h"

static std::set<int> static_sk_runtime_effect_available_keys;
static std::map<int , sk_sp<SkRuntimeEffect>> static_sk_runtime_effect;
static int static_sk_runtime_effect_index = 0;

int static_sk_runtime_effect_make(sk_sp<SkRuntimeEffect> value) {
    int key;
    if (!static_sk_runtime_effect_available_keys.empty()) {
        auto it = static_sk_runtime_effect_available_keys.begin();
        key = *it;
        static_sk_runtime_effect_available_keys.erase(it);
    } else {
        key = static_sk_runtime_effect_index++;
    }
    static_sk_runtime_effect[key] = std::move(value);
    return key;
}

void static_sk_runtime_effect_set(int key, sk_sp<SkRuntimeEffect> value) {
    static_sk_runtime_effect[key] = std::move(value);
}

sk_sp<SkRuntimeEffect> static_sk_runtime_effect_get_entity(int key) {
    return std::move(static_sk_runtime_effect[key]);
}

extern "C" {

void static_sk_runtime_effect_delete(int key) {
    static_sk_runtime_effect[key].reset();
    static_sk_runtime_effect.erase(key);
    static_sk_runtime_effect_available_keys.insert(key);
}

void *static_sk_runtime_effect_get_ptr(int key) { // -> SkRuntimeEffect *
    return static_sk_runtime_effect[key].get();
}

}