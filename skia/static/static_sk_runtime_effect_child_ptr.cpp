//
// Created by dolphilia on 2024/01/10.
//

#include "static_sk_runtime_effect_child_ptr.h"
#include "static_sk_runtime_effect_child_ptr-internal.h"

static std::set<int> static_const_sk_runtime_effect_child_ptr_available_keys;
static std::map<int , SkSpan<const SkRuntimeEffect::ChildPtr>> static_const_sk_runtime_effect_child_ptr;
static int static_const_sk_runtime_effect_child_ptr_index = 0;

// const

int static_const_sk_runtime_effect_child_ptr_make(SkSpan<const SkRuntimeEffect::ChildPtr> value) {
    int key;
    if (!static_const_sk_runtime_effect_child_ptr_available_keys.empty()) {
        auto it = static_const_sk_runtime_effect_child_ptr_available_keys.begin();
        key = *it;
        static_const_sk_runtime_effect_child_ptr_available_keys.erase(it);
    } else {
        key = static_const_sk_runtime_effect_child_ptr_index++;
    }
    static_const_sk_runtime_effect_child_ptr[key] = value;
    return key;
}

void static_const_sk_runtime_effect_child_ptr_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_const_sk_runtime_effect_child_ptr.erase(key);
    static_const_sk_runtime_effect_child_ptr_available_keys.insert(key);
}

SkSpan<const SkRuntimeEffect::ChildPtr> static_const_sk_runtime_effect_child_ptr_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_const_sk_runtime_effect_child_ptr[key];
}

const void * static_const_sk_runtime_effect_child_ptr_get_ptr(int key, int index) { // -> const SkRuntimeEffect::ChildPtr *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_const_sk_runtime_effect_child_ptr[key][index];
}

void static_const_sk_runtime_effect_child_ptr_set(int key, SkSpan<const SkRuntimeEffect::ChildPtr> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_const_sk_runtime_effect_child_ptr[key] = value;
}
