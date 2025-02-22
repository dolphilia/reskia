//
// Created by dolphilia on 25/01/12.
//

#include "static_std_vector_int_ptr.h"
#include "static_std_vector_int_ptr-internal.h"

// std::vector<int>* を管理するためのグローバル変数たち
static std::set<int> static_int_vector_ptr_available_keys;
static std::map<int, std::vector<int>*> static_int_vector_ptr_map;
static int static_int_vector_ptr_index = 0;

int static_int_vector_ptr_make(std::vector<int>* value) {
    // 再利用可能なキーがあれば使い、なければインクリメント
    int key;
    if (!static_int_vector_ptr_available_keys.empty()) {
        auto it = static_int_vector_ptr_available_keys.begin();
        key = *it;
        static_int_vector_ptr_available_keys.erase(it);
    } else {
        key = static_int_vector_ptr_index++;
    }
    // マップに登録
    static_int_vector_ptr_map[key] = value;
    return key;
}

void static_int_vector_ptr_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_int_vector_ptr_map.erase(key);
    static_int_vector_ptr_available_keys.insert(key);
}

void* static_int_vector_ptr_get(int key) { // 実際は std::vector<int>* を返したい
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    // 返り値を C 互換の void* にしている例
    // もちろん C++ のみで使うなら、 std::vector<int>* をそのまま返してもOK
    return static_int_vector_ptr_map[key];
}

void static_int_vector_ptr_set(int key, std::vector<int>* value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_int_vector_ptr_map[key] = value;
}

std::vector<int>* static_int_vector_ptr_move(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    // マップから取り出して返す
    std::vector<int>* tmp = static_int_vector_ptr_map[key];
    // テーブルから削除
    static_int_vector_ptr_map.erase(key);
    // キーを再利用可にする
    static_int_vector_ptr_available_keys.insert(key);
    // 取り出したポインタを返す
    return tmp;
}
