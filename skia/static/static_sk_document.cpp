//
// Created by dolphilia on 2024/01/13.
//

#include "static_sk_document.h"

#include <utility>
#include "static_sk_document-internal.h"

static std::set<int> static_sk_document_available_keys;
static std::map<int , sk_sp<SkDocument>> static_sk_document;
static int static_sk_document_index = 0;

int static_sk_document_make(sk_sp<SkDocument> value) {
    int key;
    if (!static_sk_document_available_keys.empty()) {
        auto it = static_sk_document_available_keys.begin();
        key = *it;
        static_sk_document_available_keys.erase(it);
    } else {
        key = static_sk_document_index++;
    }
    static_sk_document[key] = std::move(value);
    return key;
}

void static_sk_document_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_document[key].reset();
    static_sk_document.erase(key);
    static_sk_document_available_keys.insert(key);
}

void *static_sk_document_get(int key) { // -> SkDocument *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_document[key].get();
}

void static_sk_document_set(int key, sk_sp<SkDocument> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_document[key] = std::move(value);
}

sk_sp<SkDocument> static_sk_document_move(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return std::move(static_sk_document[key]);
}
