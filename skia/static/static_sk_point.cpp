//
// Created by dolphilia on 2024/03/30.
//

#include "static_sk_point.h"
#include "static_sk_point-internal.h"

static std::set<int> static_sk_point_available_keys;
static std::map<int , SkPoint> static_sk_point;
static int static_sk_point_index = 0;

int static_sk_point_make(SkPoint value) {
    int key;
    if (!static_sk_point_available_keys.empty()) {
        auto it = static_sk_point_available_keys.begin();
        key = *it;
        static_sk_point_available_keys.erase(it);
    } else {
        key = static_sk_point_index++;
    }
    static_sk_point[key] = value;
    return key;
}

void static_sk_point_set(int key, SkPoint value) {
    static_sk_point[key] = value;
}

SkPoint static_sk_point_get_entity(int key) {
    return static_sk_point[key];
}

extern "C" {

void static_sk_point_delete(int key) {
    static_sk_point.erase(key);
    static_sk_point_available_keys.insert(key);
}

void * static_sk_point_get_ptr(int key) { // -> SkPoint *
    return &static_sk_point[key];
}

}