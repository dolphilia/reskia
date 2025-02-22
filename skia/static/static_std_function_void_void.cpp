//
// Created by dolphilia on 2024/01/12.
//

#include "static_std_function_void_void.h"

#include <utility>
#include "static_std_function_void_void-internal.h"

static std::set<int> static_function_void_void_available_keys;
static std::map<int , std::function<void(void)>> static_function_void_void;
static int static_function_void_void_index = 0;

int static_function_void_void_make(std::function<void(void)> value) {
    int key;
    if (!static_function_void_void_available_keys.empty()) {
        auto it = static_function_void_void_available_keys.begin();
        key = *it;
        static_function_void_void_available_keys.erase(it);
    } else {
        key = static_function_void_void_index++;
    }
    static_function_void_void[key] = std::move(value);
    return key;
}

void static_function_void_void_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_function_void_void.erase(key);
    static_function_void_void_available_keys.insert(key);
}

std::function<void(void)> static_function_void_void_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_function_void_void[key];
}

void static_function_void_void_set(int key, std::function<void(void)> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_function_void_void[key] = std::move(value);
}
