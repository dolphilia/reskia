//
// Created by dolphilia on 2024/01/10.
//

#include "static_sk_string.h"

#include <utility>
#include "static_sk_string-internal.h"

static std::set<int> static_sk_string_available_keys;
static std::map<int , SkString> static_sk_string;
static int static_sk_string_index = 0;
//
static std::set<int> static_sk_span_sk_string_available_keys;
static std::map<int , SkSpan<SkString>> static_sk_span_sk_string;
static int static_sk_span_sk_string_index = 0;

// SkString

int static_sk_string_make(SkString value) {
    int key;
    if (!static_sk_string_available_keys.empty()) {
        auto it = static_sk_string_available_keys.begin();
        key = *it;
        static_sk_string_available_keys.erase(it);
    } else {
        key = static_sk_string_index++;
    }
    static_sk_string[key] = std::move(value);
    return key;
}

void static_sk_string_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_string.erase(key);
    static_sk_string_available_keys.insert(key);
}

SkString static_sk_string_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_string[key];
}

void * static_sk_string_get_ptr(int key) { // -> SkString *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_string[key];
}

void static_sk_string_set(int key, SkString value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_string[key] = std::move(value);
}

// SkSpan<SkString>

int static_sk_span_sk_string_make(SkSpan<SkString> value) {
    int key;
    if (!static_sk_span_sk_string_available_keys.empty()) {
        auto it = static_sk_span_sk_string_available_keys.begin();
        key = *it;
        static_sk_span_sk_string_available_keys.erase(it);
    } else {
        key = static_sk_span_sk_string_index++;
    }
    static_sk_span_sk_string[key] = value;
    return key;
}

void static_sk_span_sk_string_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_span_sk_string.erase(key);
    static_sk_span_sk_string_available_keys.insert(key);
}

SkSpan<SkString> static_sk_span_sk_string_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_span_sk_string[key];
}

void * static_sk_span_sk_string_get_ptr(int key, int index) { // -> SkString *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_span_sk_string[key][index];
}

void static_sk_span_sk_string_set(int key, SkSpan<SkString> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_span_sk_string[key] = value;
}
