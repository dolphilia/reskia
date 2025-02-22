//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_drawable_gpu_draw_handler.h"
#include "static_sk_drawable_gpu_draw_handler-internal.h"

static std::set<int> static_sk_drawable_gpu_draw_handler_available_keys;
static std::map<int , std::unique_ptr<SkDrawable::GpuDrawHandler>> static_sk_drawable_gpu_draw_handler;
static int static_sk_drawable_gpu_draw_handler_index = 0;

int static_sk_drawable_gpu_draw_handler_make(std::unique_ptr<SkDrawable::GpuDrawHandler> value) {
    int key;
    if (!static_sk_drawable_gpu_draw_handler_available_keys.empty()) {
        auto it = static_sk_drawable_gpu_draw_handler_available_keys.begin();
        key = *it;
        static_sk_drawable_gpu_draw_handler_available_keys.erase(it);
    } else {
        key = static_sk_drawable_gpu_draw_handler_index++;
    }
    static_sk_drawable_gpu_draw_handler[key] = std::move(value);
    return key;
}

void static_sk_drawable_gpu_draw_handler_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_drawable_gpu_draw_handler[key].reset();
    static_sk_drawable_gpu_draw_handler.erase(key);
    static_sk_drawable_gpu_draw_handler_available_keys.insert(key);
}

void *static_sk_drawable_gpu_draw_handler_get(int key) { // -> SkDrawable::GpuDrawHandler *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_drawable_gpu_draw_handler[key].get();
}

void static_sk_drawable_gpu_draw_handler_set(int key, std::unique_ptr<SkDrawable::GpuDrawHandler> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_drawable_gpu_draw_handler[key] = std::move(value);
}

std::unique_ptr<SkDrawable::GpuDrawHandler> static_sk_drawable_gpu_draw_handler_move(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return std::move(static_sk_drawable_gpu_draw_handler[key]);
}
