//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_picture.h"

#include <utility>
#include "static_sk_picture-internal.h"

static std::set<int> static_sk_picture_available_keys;
static std::map<int , sk_sp<SkPicture>> static_sk_picture;
static int static_sk_picture_index = 0;

int static_sk_picture_make(sk_sp<SkPicture> value) {
    int key;
    if (!static_sk_picture_available_keys.empty()) {
        auto it = static_sk_picture_available_keys.begin();
        key = *it;
        static_sk_picture_available_keys.erase(it);
    } else {
        key = static_sk_picture_index++;
    }
    static_sk_picture[key] = std::move(value);
    return key;
}

void static_sk_picture_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_picture[key].reset();
    static_sk_picture.erase(key);
    static_sk_picture_available_keys.insert(key);
}

void *static_sk_picture_get(int key) { // -> SkPicture *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_picture[key].get();
}

void static_sk_picture_set(int key, sk_sp<SkPicture> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_picture[key] = std::move(value);
}

sk_sp<SkPicture> static_sk_picture_move(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return std::move(static_sk_picture[key]);
}
