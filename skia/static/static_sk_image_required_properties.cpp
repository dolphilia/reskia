//
// Created by dolphilia on 2024/04/03.
//

#include "static_sk_image_required_properties.h"
#include "static_sk_image_required_properties-internal.h"

static std::set<int> static_sk_image_required_properties_available_keys;
static std::map<int , SkImage::RequiredProperties> static_sk_image_required_properties;
static int static_sk_image_required_properties_index = 0;

int static_sk_image_required_properties_make(SkImage::RequiredProperties value) {
    int key;
    if (!static_sk_image_required_properties_available_keys.empty()) {
        auto it = static_sk_image_required_properties_available_keys.begin();
        key = *it;
        static_sk_image_required_properties_available_keys.erase(it);
    } else {
        key = static_sk_image_required_properties_index++;
    }
    static_sk_image_required_properties[key] = value;
    return key;
}

void static_sk_image_required_properties_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_image_required_properties.erase(key);
    static_sk_image_required_properties_available_keys.insert(key);
}

SkImage::RequiredProperties static_sk_image_required_properties_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_image_required_properties[key];
}

void * static_sk_image_required_properties_get_ptr(int key) { // -> SkImage::RequiredProperties *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_image_required_properties[key];
}

void static_sk_image_required_properties_set(int key, SkImage::RequiredProperties value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_image_required_properties[key] = value;
}
