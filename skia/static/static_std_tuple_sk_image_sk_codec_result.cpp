//
// Created by dolphilia on 2024/02/02.
//

#include "static_std_tuple_sk_image_sk_codec_result.h"
#include "static_std_tuple_sk_image_sk_codec_result-internal.h"

static std::set<int> static_tuple_sk_image_sk_codec_result_available_keys;
static std::map<int , std::tuple<sk_sp<SkImage>, SkCodec::Result>> static_tuple_sk_image_sk_codec_result;
static int static_tuple_sk_image_sk_codec_result_index = 0;

int static_tuple_sk_image_sk_codec_result_make(std::tuple<sk_sp<SkImage>, SkCodec::Result> value) {
    int key;
    if (!static_tuple_sk_image_sk_codec_result_available_keys.empty()) {
        auto it = static_tuple_sk_image_sk_codec_result_available_keys.begin();
        key = *it;
        static_tuple_sk_image_sk_codec_result_available_keys.erase(it);
    } else {
        key = static_tuple_sk_image_sk_codec_result_index++;
    }
    static_tuple_sk_image_sk_codec_result[key] = std::move(value);
    return key;
}

void static_tuple_sk_image_sk_codec_result_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_tuple_sk_image_sk_codec_result.erase(key);
    static_tuple_sk_image_sk_codec_result_available_keys.insert(key);
}

std::tuple<sk_sp<SkImage>, SkCodec::Result> static_tuple_sk_image_sk_codec_result_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_tuple_sk_image_sk_codec_result[key];
}

void static_tuple_sk_image_sk_codec_result_set(int key, std::tuple<sk_sp<SkImage>, SkCodec::Result> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_tuple_sk_image_sk_codec_result[key] = std::move(value);
}
