//
// Created by dolphilia on 2024/02/02.
//

#include "static_std_vector_sk_codec_frame_info.h"
#include "static_std_vector_sk_codec_frame_info-internal.h"

static std::set<int> static_vector_sk_codec_frame_into_available_keys;
static std::map<int , std::vector<SkCodec::FrameInfo>> static_vector_sk_codec_frame_into;
static int static_vector_sk_codec_frame_into_index = 0;

int static_vector_sk_codec_frame_info_make(std::vector<SkCodec::FrameInfo> value) {
    int key;
    if (!static_vector_sk_codec_frame_into_available_keys.empty()) {
        auto it = static_vector_sk_codec_frame_into_available_keys.begin();
        key = *it;
        static_vector_sk_codec_frame_into_available_keys.erase(it);
    } else {
        key = static_vector_sk_codec_frame_into_index++;
    }
    static_vector_sk_codec_frame_into[key] = std::move(value);
    return key;
}

void static_vector_sk_codec_frame_info_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_vector_sk_codec_frame_into.erase(key);
    static_vector_sk_codec_frame_into_available_keys.insert(key);
}

SkCodec::FrameInfo static_vector_sk_codec_frame_info_get(int key, int index) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_vector_sk_codec_frame_into[key][index];
}

void static_vector_sk_codec_frame_info_set(int key, std::vector<SkCodec::FrameInfo> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_vector_sk_codec_frame_into[key] = std::move(value);
}

void static_vector_sk_codec_frame_info_push_back(int key, SkCodec::FrameInfo value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_vector_sk_codec_frame_into[key].push_back(value);
}

void static_vector_sk_codec_frame_info_insert(int key, int index, SkCodec::FrameInfo value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_vector_sk_codec_frame_into[key].insert(static_vector_sk_codec_frame_into[key].begin() + index, value);
}

void static_vector_sk_codec_frame_info_pop_back(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_vector_sk_codec_frame_into[key].pop_back();
}

void static_vector_sk_codec_frame_info_erase(int key, int index) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_vector_sk_codec_frame_into[key].erase(static_vector_sk_codec_frame_into[key].begin() + index);
}
