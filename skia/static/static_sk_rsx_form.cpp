//
// Created by dolphilia on 2024/04/05.
//

#include "static_sk_rsx_form.h"
#include "static_sk_rsx_form-internal.h"

static std::set<int> static_sk_rsx_form_available_keys;
static std::map<int , SkRSXform> static_sk_rsx_form;
static int static_sk_rsx_form_index = 0;

int static_sk_rsx_form_make(SkRSXform value) {
    int key;
    if (!static_sk_rsx_form_available_keys.empty()) {
        auto it = static_sk_rsx_form_available_keys.begin();
        key = *it;
        static_sk_rsx_form_available_keys.erase(it);
    } else {
        key = static_sk_rsx_form_index++;
    }
    static_sk_rsx_form[key] = value;
    return key;
}

void static_sk_rsx_form_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_rsx_form.erase(key);
    static_sk_rsx_form_available_keys.insert(key);
}

SkRSXform static_sk_rsx_form_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_rsx_form[key];
}

void * static_sk_rsx_form_get_ptr(int key) { // -> SkRSXform *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_rsx_form[key];
}

void static_sk_rsx_form_set(int key, SkRSXform value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_rsx_form[key] = value;
}
