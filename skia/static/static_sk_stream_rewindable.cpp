//
// Created by dolphilia on 2024/01/11.
//

#include "static_sk_stream_rewindable.h"
#include "static_sk_stream_rewindable-internal.h"

static std::set<int> static_sk_stream_rewindable_available_keys;
static std::map<int , std::unique_ptr<SkStreamRewindable>> static_sk_stream_rewindable;
static int static_sk_stream_rewindable_index = 0;

int static_sk_stream_rewindable_make(std::unique_ptr<SkStreamRewindable> value) {
    int key;
    if (!static_sk_stream_rewindable_available_keys.empty()) {
        auto it = static_sk_stream_rewindable_available_keys.begin();
        key = *it;
        static_sk_stream_rewindable_available_keys.erase(it);
    } else {
        key = static_sk_stream_rewindable_index++;
    }
    static_sk_stream_rewindable[key] = std::move(value);
    return key;
}

void static_sk_stream_rewindable_set(int key, std::unique_ptr<SkStreamRewindable> value) {
    static_sk_stream_rewindable[key] = std::move(value);
}

std::unique_ptr<SkStreamRewindable> static_sk_stream_rewindable_get_entity(int key) {
    return std::move(static_sk_stream_rewindable[key]);
}

extern "C" {

void static_sk_stream_rewindable_delete(int key) {
    static_sk_stream_rewindable[key].reset();
    static_sk_stream_rewindable.erase(key);
    static_sk_stream_rewindable_available_keys.insert(key);
}

void *static_sk_stream_rewindable_get_ptr(int key) { // -> SkStreamRewindable *
    return static_sk_stream_rewindable[key].get();
}

}