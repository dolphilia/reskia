//
// Created by dolphilia on 2024/03/30.
//

#include "static_sk_color_4f.h"
#include "static_sk_color_4f-internal.h"

static std::set<int> static_sk_color_4f_available_keys;
static std::map<int , SkColor4f> static_sk_color_4f;
static int static_sk_color_4f_index = 0;

int static_sk_color_4f_make(SkColor4f value) {
    int key;
    if (!static_sk_color_4f_available_keys.empty()) {
        auto it = static_sk_color_4f_available_keys.begin();
        key = *it;
        static_sk_color_4f_available_keys.erase(it);
    } else {
        key = static_sk_color_4f_index++;
    }
    static_sk_color_4f[key] = value;
    return key;
}

void static_sk_color_4f_set(int key, SkColor4f value) {
    static_sk_color_4f[key] = value;
}

SkColor4f static_sk_color_4f_get_entity(int key) {
    return static_sk_color_4f[key];
}

extern "C" {

void static_sk_color_4f_delete(int key) {
    static_sk_color_4f.erase(key);
    static_sk_color_4f_available_keys.insert(key);
}

void * static_sk_color_4f_get_ptr(int key) { // -> SkColor4f *
    return &static_sk_color_4f[key];
}

}