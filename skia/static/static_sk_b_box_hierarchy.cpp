//
// Created by dolphilia on 2024/01/12.
//

#include "static_sk_b_box_hierarchy.h"
#include "static_sk_b_box_hierarchy-internal.h"

#include <set>
#include <map>

static std::set<int> static_sk_b_box_hierarchy_available_keys;
static std::map<int, sk_sp<SkBBoxHierarchy>> static_sk_b_box_hierarchy;
static int static_sk_b_box_hierarchy_index = 0;

int static_sk_b_box_hierarchy_make(sk_sp<SkBBoxHierarchy> value) {
    int key;
    if (!static_sk_b_box_hierarchy_available_keys.empty()) {
        auto it = static_sk_b_box_hierarchy_available_keys.begin();
        key = *it;
        static_sk_b_box_hierarchy_available_keys.erase(it);
    } else {
        key = static_sk_b_box_hierarchy_index++;
    }
    static_sk_b_box_hierarchy[key] = std::move(value);
    return key;
}

void static_sk_b_box_hierarchy_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_b_box_hierarchy[key].reset();
    static_sk_b_box_hierarchy.erase(key);
    static_sk_b_box_hierarchy_available_keys.insert(key);
}

void *static_sk_b_box_hierarchy_get(int key) { // -> SkBBoxHierarchy
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_b_box_hierarchy[key].get();
}

void static_sk_b_box_hierarchy_set(int key, sk_sp<SkBBoxHierarchy> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_b_box_hierarchy[key] = std::move(value);
}

sk_sp<SkBBoxHierarchy> static_sk_b_box_hierarchy_move(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return std::move(static_sk_b_box_hierarchy[key]);
}