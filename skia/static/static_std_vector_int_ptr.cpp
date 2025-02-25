//
// Created by dolphilia on 25/01/12.
//

#include "static_std_vector_int_ptr.h"
#include "static_std_vector_int_ptr-internal.h"

static std::set<int> static_int_vector_ptr_available_keys;
static std::map<int, std::vector<int>*> static_int_vector_ptr_map;
static int static_int_vector_ptr_index = 0;

int static_int_vector_ptr_make(std::vector<int>* value) {
    int key;
    if (!static_int_vector_ptr_available_keys.empty()) {
        auto it = static_int_vector_ptr_available_keys.begin();
        key = *it;
        static_int_vector_ptr_available_keys.erase(it);
    } else {
        key = static_int_vector_ptr_index++;
    }
    static_int_vector_ptr_map[key] = value;
    return key;
}

void static_int_vector_ptr_set(int key, std::vector<int>* value) {
    static_int_vector_ptr_map[key] = value;
}

std::vector<int>* static_int_vector_ptr_get_entity(int key) {
    std::vector<int>* tmp = static_int_vector_ptr_map[key];
    static_int_vector_ptr_map.erase(key);
    static_int_vector_ptr_available_keys.insert(key);
    return tmp;
}

extern "C" {

void static_int_vector_ptr_delete(int key) {
    static_int_vector_ptr_map.erase(key);
    static_int_vector_ptr_available_keys.insert(key);
}

void* static_int_vector_ptr_get_ptr(int key) {
    return static_int_vector_ptr_map[key];
}

}