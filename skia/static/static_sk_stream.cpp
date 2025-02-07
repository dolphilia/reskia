//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_stream.h"
#include "static_sk_stream-internal.h"

static std::set<int> static_sk_stream_available_keys;
static std::map<int , std::unique_ptr<SkStream>> static_sk_stream;
static int static_sk_stream_index = 0;

// static_sk_stream

int static_sk_stream_make(std::unique_ptr<SkStream> value) {
    int key;
    if (!static_sk_stream_available_keys.empty()) {
        auto it = static_sk_stream_available_keys.begin();
        key = *it;
        static_sk_stream_available_keys.erase(it);
    } else {
        key = static_sk_stream_index++;
    }
    static_sk_stream[key] = std::move(value);
    return key;
}

void static_sk_stream_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    delete &static_sk_stream[key];
    static_sk_stream[key].reset();
    static_sk_stream.erase(key);
    static_sk_stream_available_keys.insert(key);
}

void *static_sk_stream_get(int key) { // -> SkStream *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_stream[key].get();
}

void static_sk_stream_set(int key, std::unique_ptr<SkStream> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_stream[key] = std::move(value);
}

std::unique_ptr<SkStream> static_sk_stream_move(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return std::move(static_sk_stream[key]);
}

// static_sk_stream_ptr

static std::set<int> static_sk_stream_ptr_available_keys;
static std::map<int, std::unique_ptr<SkStream>*> static_sk_stream_ptr;
static int static_sk_stream_ptr_index = 0;

int static_sk_stream_ptr_make(std::unique_ptr<SkStream>* value) {
    int key;
    if (!static_sk_stream_ptr_available_keys.empty()) {
        auto it = static_sk_stream_ptr_available_keys.begin();
        key = *it;
        static_sk_stream_ptr_available_keys.erase(it);
    } else {
        key = static_sk_stream_ptr_index++;
    }
    static_sk_stream_ptr[key] = value;
    return key;
}

void static_sk_stream_ptr_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_stream_ptr.erase(key);
    static_sk_stream_ptr_available_keys.insert(key);
}

void* static_sk_stream_ptr_get(int key) { // -> SkStream*
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_stream_ptr[key]->get();
}

void static_sk_stream_ptr_set(int key, std::unique_ptr<SkStream>* value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_stream_ptr[key] = value;
}

std::unique_ptr<SkStream>* static_sk_stream_ptr_move(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    auto tmp = static_sk_stream_ptr[key];
    static_sk_stream_ptr.erase(key);
    static_sk_stream_ptr_available_keys.insert(key);
    return tmp; // 所有権(？)の移動
}
