//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_text_blob.h"

#include <utility>
#include "static_sk_text_blob-internal.h"

static std::set<int> static_sk_text_blob_available_keys;
static std::map<int , sk_sp<SkTextBlob>> static_sk_text_blob;
static int static_sk_text_blob_index = 0;

int static_sk_text_blob_make(sk_sp<SkTextBlob> value) {
    int key;
    if (!static_sk_text_blob_available_keys.empty()) {
        auto it = static_sk_text_blob_available_keys.begin();
        key = *it;
        static_sk_text_blob_available_keys.erase(it);
    } else {
        key = static_sk_text_blob_index++;
    }
    static_sk_text_blob[key] = std::move(value);
    return key;
}

void static_sk_text_blob_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_text_blob[key].reset();
    static_sk_text_blob.erase(key);
    static_sk_text_blob_available_keys.insert(key);
}

void * static_sk_text_blob_get(int key) { // -> SkTextBlob *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_text_blob[key].get();
}

void static_sk_text_blob_set(int key, sk_sp<SkTextBlob> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_text_blob[key] = std::move(value);
}

sk_sp<SkTextBlob> static_sk_text_blob_move(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return std::move(static_sk_text_blob[key]);
}
