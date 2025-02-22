//
// Created by dolphilia on 2024/01/11.
//

#include "static_sk_stroke_rec.h"
#include "static_sk_stroke_rec-internal.h"

static std::set<int> static_sk_stroke_rec_available_keys;
static std::map<int , SkStrokeRec> static_sk_stroke_rec;
static int static_sk_stroke_rec_index = 0;

int static_sk_stroke_rec_make(SkStrokeRec value) {
    int key;
    if (!static_sk_stroke_rec_available_keys.empty()) {
        auto it = static_sk_stroke_rec_available_keys.begin();
        key = *it;
        static_sk_stroke_rec_available_keys.erase(it);
    } else {
        key = static_sk_stroke_rec_index++;
    }
    static_sk_stroke_rec.at(key) = value;
    return key;
}

void static_sk_stroke_rec_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_stroke_rec.erase(key);
    static_sk_stroke_rec_available_keys.insert(key);
}

SkStrokeRec static_sk_stroke_rec_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_stroke_rec.at(key);
}

void * static_sk_stroke_rec_get_ptr(int key) { // -> SkStrokeRec *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_stroke_rec.at(key);
}

void static_sk_stroke_rec_set(int key, SkStrokeRec value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_stroke_rec.at(key) = value;
}
