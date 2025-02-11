//
// Created by dolphilia on 2024/01/06.
//

#include "static_sk_m_44.h"
#include "static_sk_m_44-internal.h"

static std::set<int> static_sk_m_44_available_keys;
static std::map<int , SkM44> static_sk_m_44;
static int static_sk_m_44_index = 0;

int static_sk_m_44_make(SkM44 value) {
    int key;
    if (!static_sk_m_44_available_keys.empty()) {
        auto it = static_sk_m_44_available_keys.begin();
        key = *it;
        static_sk_m_44_available_keys.erase(it);
    } else {
        key = static_sk_m_44_index++;
    }
    static_sk_m_44[key] = value;
    return key;
}

void static_sk_m_44_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_m_44.erase(key);
    static_sk_m_44_available_keys.insert(key);
}

SkM44 static_sk_m_44_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_m_44[key];
}

void * static_sk_m_44_get_ptr(int key) { // -> SkM44 *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_m_44[key];
}

void static_sk_m_44_set(int key, SkM44 value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_m_44[key] = value;
}
