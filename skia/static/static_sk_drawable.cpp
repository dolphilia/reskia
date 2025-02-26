//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_drawable.h"

#include <utility>
#include "static_sk_drawable-internal.h"

static std::set<int> static_sk_drawable_available_keys;
static std::map<int, sk_sp<SkDrawable>> static_sk_drawable;
static int static_sk_drawable_index = 0;

int static_sk_drawable_make(sk_sp<SkDrawable> value) {
    int key;
    if (!static_sk_drawable_available_keys.empty()) {
        auto it = static_sk_drawable_available_keys.begin();
        key = *it;
        static_sk_drawable_available_keys.erase(it);
    } else {
        key = static_sk_drawable_index++;
    }
    static_sk_drawable[key] = std::move(value);
    return key;
}

void static_sk_drawable_set(int key, sk_sp<SkDrawable> value) {
    static_sk_drawable[key] = std::move(value);
}

sk_sp<SkDrawable> static_sk_drawable_get_entity(int key) {
    return std::move(static_sk_drawable[key]);
}

extern "C" {

void static_sk_drawable_delete(int key) {
    static_sk_drawable[key].reset();
    static_sk_drawable.erase(key);
    static_sk_drawable_available_keys.insert(key);
}

void *static_sk_drawable_get_ptr(int key) { // -> SkDrawable *
    return static_sk_drawable[key].get();
}

}