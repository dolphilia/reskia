//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_file_stream.h"
#include "static_sk_file_stream-internal.h"

static std::set<int> static_sk_file_stream_available_keys;
static std::map<int , std::unique_ptr<SkFILEStream>> static_sk_file_stream;
static int static_sk_file_stream_index = 0;

int static_sk_file_stream_make(std::unique_ptr<SkFILEStream> value) {
    int key;
    if (!static_sk_file_stream_available_keys.empty()) {
        auto it = static_sk_file_stream_available_keys.begin();
        key = *it;
        static_sk_file_stream_available_keys.erase(it);
    } else {
        key = static_sk_file_stream_index++;
    }
    static_sk_file_stream[key] = std::move(value);
    return key;
}

void static_sk_file_stream_set(int key, std::unique_ptr<SkFILEStream> value) {
    static_sk_file_stream[key] = std::move(value);
}

std::unique_ptr<SkFILEStream> static_sk_file_stream_get_entity(int key) {
    return std::move(static_sk_file_stream[key]);
}

extern "C" {

void static_sk_file_stream_delete(int key) {
    static_sk_file_stream[key].reset();
    static_sk_file_stream.erase(key);
    static_sk_file_stream_available_keys.insert(key);
}

void *static_sk_file_stream_get_ptr(int key) { // -> SkFILEStream *
    return static_sk_file_stream[key].get();
}

}