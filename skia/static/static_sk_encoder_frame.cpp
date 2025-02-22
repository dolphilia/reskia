//
// Created by dolphilia on 2024/02/01.
//

#include "static_sk_encoder_frame.h"
#include "static_sk_encoder_frame-internal.h"

static std::set<int> static_const_sk_encoder_frame_available_keys;
static std::map<int , SkSpan<const SkEncoder::Frame>> static_const_sk_encoder_frame;
static int static_const_sk_encoder_frame_index = 0;

int static_const_sk_encoder_frame_make(SkSpan<const SkEncoder::Frame> value) {
    int key;
    if (!static_const_sk_encoder_frame_available_keys.empty()) {
        auto it = static_const_sk_encoder_frame_available_keys.begin();
        key = *it;
        static_const_sk_encoder_frame_available_keys.erase(it);
    } else {
        key = static_const_sk_encoder_frame_index++;
    }
    static_const_sk_encoder_frame[key] = value;
    return key;
}

void static_const_sk_encoder_frame_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_const_sk_encoder_frame.erase(key);
    static_const_sk_encoder_frame_available_keys.insert(key);
}

SkSpan<const SkEncoder::Frame> static_const_sk_encoder_frame_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_const_sk_encoder_frame[key];
}

const void * static_const_sk_encoder_frame_get_ptr(int key, int index) { // -> const SkEncoder::Frame *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_const_sk_encoder_frame[key][index];
}

void static_const_encoder_frame_set(int key, SkSpan<const SkEncoder::Frame> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_const_sk_encoder_frame[key] = value;
}
