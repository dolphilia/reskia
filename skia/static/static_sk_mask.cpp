//
// Created by dolphilia on 25/01/30.
//

#include "static_sk_mask.h"

#include "static_sk_mask-internal.h"

static std::set<int> static_sk_mask_available_keys;
static std::map<int, std::unique_ptr<SkMask>> static_sk_mask;
static int static_sk_mask_index = 0;

int static_sk_mask_make(const SkMask& value) {
    int key;
    if (!static_sk_mask_available_keys.empty()) {
        auto it = static_sk_mask_available_keys.begin();
        key = *it;
        static_sk_mask_available_keys.erase(it);
    } else {
        key = static_sk_mask_index++;
    }
    static_sk_mask[key] = std::make_unique<SkMask>(value);
    return key;
}

void static_sk_mask_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_mask.erase(key);
    static_sk_mask_available_keys.insert(key);
}

void* static_sk_mask_get_ptr(int key) { // -> SkMask*
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    // unique_ptr の中身を返す
    return static_sk_mask[key].get();
}

void static_sk_mask_set(int key, const SkMask& value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_mask[key] = std::make_unique<SkMask>(value);
}