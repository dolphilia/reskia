//
// Created by dolphilia on 2024/01/11.
//

#include "static_sk_runtime_effect_child.h"
#include "static_sk_runtime_effect_child-internal.h"

static std::set<int> static_const_sk_runtime_effect_child_available_keys;
static std::map<int , SkSpan<const SkRuntimeEffect::Child>> static_const_sk_runtime_effect_child;
static int static_const_sk_runtime_effect_child_index = 0;

// const

int static_const_sk_runtime_effect_child_make(SkSpan<const SkRuntimeEffect::Child> value) {
    int key;
    if (!static_const_sk_runtime_effect_child_available_keys.empty()) {
        auto it = static_const_sk_runtime_effect_child_available_keys.begin();
        key = *it;
        static_const_sk_runtime_effect_child_available_keys.erase(it);
    } else {
        key = static_const_sk_runtime_effect_child_index++;
    }
    static_const_sk_runtime_effect_child[key] = value;
    return key;
}

void static_const_sk_runtime_effect_child_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_const_sk_runtime_effect_child.erase(key);
    static_const_sk_runtime_effect_child_available_keys.insert(key);
}

SkSpan<const SkRuntimeEffect::Child> static_const_sk_runtime_effect_child_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_const_sk_runtime_effect_child[key];
}

const void * static_const_sk_runtime_effect_child_get_ptr(int key, int index) { // -> const SkRuntimeEffect::Child *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_const_sk_runtime_effect_child[key][index];
}

void static_const_sk_runtime_effect_child_set(int key, SkSpan<const SkRuntimeEffect::Child> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_const_sk_runtime_effect_child[key] = value;
}
