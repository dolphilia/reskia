//
// Created by dolphilia on 2024/01/11.
//

#include "static_std_tuple_int_sk_yuva_pixmap_info_data_type.h"

#include <utility>
#include "handle_table.hpp"
#include "static_std_tuple_int_sk_yuva_pixmap_info_data_type-internal.h"

static reskia::static_registry::HandleTable<std::tuple<int, SkYUVAPixmapInfo::DataType>>
    static_tuple_int_sk_yuva_pixmap_info_data_type;

int static_tuple_int_sk_yuva_pixmap_info_data_type_make(std::tuple<int, SkYUVAPixmapInfo::DataType> value) {
    return static_tuple_int_sk_yuva_pixmap_info_data_type.create(std::move(value));
}

void static_tuple_int_sk_yuva_pixmap_info_data_type_set(int key, std::tuple<int, SkYUVAPixmapInfo::DataType> value) {
    static_tuple_int_sk_yuva_pixmap_info_data_type.set(key, std::move(value));
}

std::tuple<int, SkYUVAPixmapInfo::DataType> static_tuple_int_sk_yuva_pixmap_info_data_type_get_entity(int key) {
    std::tuple<int, SkYUVAPixmapInfo::DataType>* entity =
        static_tuple_int_sk_yuva_pixmap_info_data_type.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_tuple_int_sk_yuva_pixmap_info_data_type_delete(int key) {
    static_tuple_int_sk_yuva_pixmap_info_data_type.erase(key);
}

}
