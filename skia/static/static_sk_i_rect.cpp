//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_i_rect.h"
#include "static_sk_i_rect-internal.h"

static std::set<int> static_sk_i_rect_available_keys;
static std::map<int , SkIRect> static_sk_i_rect;
static int static_sk_i_rect_index = 0;

int static_sk_i_rect_make(SkIRect value) {
    int key;
    if (!static_sk_i_rect_available_keys.empty()) {
        auto it = static_sk_i_rect_available_keys.begin();
        key = *it;
        static_sk_i_rect_available_keys.erase(it);
    } else {
        key = static_sk_i_rect_index++;
    }
    static_sk_i_rect[key] = value;
    return key;
}

void static_sk_i_rect_set(int key, SkIRect value) {
    static_sk_i_rect[key] = value;
}

SkIRect static_sk_i_rect_get_entity(int key) {
    return static_sk_i_rect[key];
}

extern "C" {

void static_sk_i_rect_delete(int key) {
    static_sk_i_rect.erase(key);
    static_sk_i_rect_available_keys.insert(key);
}

void * static_sk_i_rect_get_ptr(int key) { // -> SkIRect *
    return &static_sk_i_rect[key];
}

}