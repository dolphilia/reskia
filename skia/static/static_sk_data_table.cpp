//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_data_table.h"

#include <utility>
#include "static_sk_data_table-internal.h"

static std::set<int> static_sk_data_table_available_keys;
static std::map<int , sk_sp<SkDataTable>> static_sk_data_table;
static int static_sk_data_table_index = 0;

int static_sk_data_table_make(sk_sp<SkDataTable> value) {
    int key;
    if (!static_sk_data_table_available_keys.empty()) {
        auto it = static_sk_data_table_available_keys.begin();
        key = *it;
        static_sk_data_table_available_keys.erase(it);
    } else {
        key = static_sk_data_table_index++;
    }
    static_sk_data_table[key] = std::move(value);
    return key;
}

void static_sk_data_table_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_data_table[key].reset();
    static_sk_data_table.erase(key);
    static_sk_data_table_available_keys.insert(key);
}

void *static_sk_data_table_get(int key) { // -> SkDataTable *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_data_table[key].get();
}

void static_sk_data_table_set(int key, sk_sp<SkDataTable> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_data_table[key] = std::move(value);
}

sk_sp<SkDataTable> static_sk_data_table_move(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return std::move(static_sk_data_table[key]);
}
