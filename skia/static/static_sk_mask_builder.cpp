//
// Created by dolphilia on 25/01/30.
//

#include "static_sk_mask_builder.h"

#include "static_sk_mask_builder-internal.h"

static std::set<int> static_sk_mask_builder_available_keys;
static std::map<int , SkMaskBuilder> static_sk_mask_builder;
static int static_sk_mask_builder_index = 0;

int static_sk_mask_builder_make(SkMaskBuilder value) {
    int key;
    if (!static_sk_mask_builder_available_keys.empty()) {
        auto it = static_sk_mask_builder_available_keys.begin();
        key = *it;
        static_sk_mask_builder_available_keys.erase(it);
    } else {
        key = static_sk_mask_builder_index++;
    }
    static_sk_mask_builder[key] = std::move(value);
    return key;
}

void static_sk_mask_builder_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_mask_builder.erase(key);
    static_sk_mask_builder_available_keys.insert(key);
}

//SkMaskBuilder static_sk_mask_builder_get(int key) {
//    return static_sk_mask_builder[key];
//}

void * static_sk_mask_builder_get_ptr(int key) { // -> SkMaskBuilder *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_mask_builder[key];
}

void static_sk_mask_builder_set(int key, SkMaskBuilder value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_mask_builder[key] = std::move(value);
}