//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_canvas.h"
#include "static_sk_canvas-internal.h"

static std::set<int> static_sk_canvas_available_keys;
static std::map<int , std::unique_ptr<SkCanvas>> static_sk_canvas;
static int static_sk_canvas_index = 0;

int static_sk_canvas_make(std::unique_ptr<SkCanvas> value) {
    int key;
    if (!static_sk_canvas_available_keys.empty()) {
        auto it = static_sk_canvas_available_keys.begin();
        key = *it;
        static_sk_canvas_available_keys.erase(it);
    } else {
        key = static_sk_canvas_index++;
    }
    static_sk_canvas[key] = std::move(value);
    return key;
}

void static_sk_canvas_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_canvas[key].reset();
    static_sk_canvas.erase(key);
    static_sk_canvas_available_keys.insert(key);
}

void *static_sk_canvas_get(int key) {  // -> SkCanvas *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_canvas[key].get();
}

void static_sk_canvas_set(int key, std::unique_ptr<SkCanvas> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_canvas[key] = std::move(value);
}

std::unique_ptr<SkCanvas> static_sk_canvas_move(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return std::move(static_sk_canvas[key]);
}
