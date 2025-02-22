//
// Created by dolphilia on 2024/01/11.
//

#include "static_sk_stream_memory.h"
#include "static_sk_stream_memory-internal.h"

static std::set<int> static_sk_stream_memory_available_keys;
static std::map<int , std::unique_ptr<SkStreamMemory>> static_sk_stream_memory;
static int static_sk_stream_memory_index = 0;

int static_sk_stream_memory_make(std::unique_ptr<SkStreamMemory> value) {
    int key;
    if (!static_sk_stream_memory_available_keys.empty()) {
        auto it = static_sk_stream_memory_available_keys.begin();
        key = *it;
        static_sk_stream_memory_available_keys.erase(it);
    } else {
        key = static_sk_stream_memory_index++;
    }
    static_sk_stream_memory[key] = std::move(value);
    return key;
}

void static_sk_stream_memory_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_stream_memory[key].reset();
    static_sk_stream_memory.erase(key);
    static_sk_stream_memory_available_keys.insert(key);
}

void *static_sk_stream_memory_get(int key) { // -> SkStreamMemory *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_stream_memory[key].get();
}

void static_sk_stream_memory_set(int key, std::unique_ptr<SkStreamMemory> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_stream_memory[key] = std::move(value);
}

std::unique_ptr<SkStreamMemory> static_sk_stream_memory_move(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return std::move(static_sk_stream_memory[key]);
}
