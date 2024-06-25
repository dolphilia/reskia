//
// Created by dolphilia on 2024/01/12.
//

#include "static_sk_color.h"
/*
static std::set<int> static_sk_color_available_keys;
static std::map<int , SkSpan<SkColor>> static_sk_color;
static int static_sk_color_index = 0;

int static_sk_color_make(SkSpan<SkColor> value) {
    int key;
    if (!static_sk_color_available_keys.empty()) {
        auto it = static_sk_color_available_keys.begin();
        key = *it;
        static_sk_color_available_keys.erase(it);
    } else {
        key = static_sk_color_index++;
    }
    static_sk_color[key] = value;
    return key;
}

void static_sk_color_delete(int key) {
    static_sk_color.erase(key);
    static_sk_color_available_keys.insert(key);
}

SkSpan<SkColor> static_sk_color_get(int key) {
    return static_sk_color[key];
}

SkColor static_sk_color_get_value(int key, int index) {
    return static_sk_color[key][index];
}

void static_color_set(int key, SkSpan<SkColor> value) {
    static_sk_color[key] = value;
}*/
//
// Created by dolphilia on 2024/01/12.
//

#include "static_sk_color.h"

struct color_t{
    int r;
    int g;
    int b;
    int a;
};

static std::set<int> color_available_keys;
static std::map<int, color_t> colors;
static int color_index = 0;

int color_make(color_t value) {
    int key;
    if (!color_available_keys.empty()) {
        auto it = color_available_keys.begin();
        key = *it;
        color_available_keys.erase(it);
    } else {
        key = color_index++;
    }
    colors[key] = value;
    return key;
}

void color_delete(int key) {
    colors.erase(key);
    color_available_keys.insert(key);
}

color_t color_get(int key) {
    return colors[key];
}

void color_set(int key, color_t value) {
    colors[key] = value;
}