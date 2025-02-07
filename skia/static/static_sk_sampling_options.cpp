//
// Created by dolphilia on 2024/01/11.
//

#include "static_sk_sampling_options.h"
#include "static_sk_sampling_options-internal.h"

static std::set<int> static_sk_sampling_options_available_keys;
static std::map<int , SkSamplingOptions> static_sk_sampling_options;
static int static_sk_sampling_options_index = 0;

int static_sk_sampling_options_make(SkSamplingOptions value) {
    int key;
    if (!static_sk_sampling_options_available_keys.empty()) {
        auto it = static_sk_sampling_options_available_keys.begin();
        key = *it;
        static_sk_sampling_options_available_keys.erase(it);
    } else {
        key = static_sk_sampling_options_index++;
    }
    static_sk_sampling_options[key] = value;
    return key;
}

void static_sk_sampling_options_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_sampling_options.erase(key);
    static_sk_sampling_options_available_keys.insert(key);
}

SkSamplingOptions static_sk_sampling_options_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_sampling_options[key];
}

void * static_sk_sampling_options_get_ptr(int key) { // -> SkSamplingOptions *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_sampling_options[key];
}

void static_sk_sampling_options_set(int key, SkSamplingOptions value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_sampling_options[key] = value;
}
