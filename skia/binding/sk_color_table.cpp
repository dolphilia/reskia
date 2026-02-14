//
// Created by dolphilia on 2024/01/08.
//

#include "sk_color_table.h"

#include "include/core/SkColorTable.h"

#include "../static/static_sk_color_table.h"

#include "../static/static_sk_color_table-internal.h"

extern "C" {

void SkColorTable_delete(reskia_color_table_t *color_table) {
    reinterpret_cast<SkColorTable *>(color_table)->unref();
}

const uint8_t *SkColorTable_alphaTable(reskia_color_table_t *color_table) {
    return reinterpret_cast<SkColorTable *>(color_table)->alphaTable();
}

const uint8_t *SkColorTable_redTable(reskia_color_table_t *color_table) {
    return reinterpret_cast<SkColorTable *>(color_table)->redTable();
}

const uint8_t *SkColorTable_greenTable(reskia_color_table_t *color_table) {
    return reinterpret_cast<SkColorTable *>(color_table)->greenTable();
}

const uint8_t *SkColorTable_blueTable(reskia_color_table_t *color_table) {
    return reinterpret_cast<SkColorTable *>(color_table)->blueTable();
}

void SkColorTable_flatten(reskia_color_table_t *color_table, reskia_write_buffer_t *buffer) {
    reinterpret_cast<SkColorTable *>(color_table)->flatten(*reinterpret_cast<SkWriteBuffer *>(buffer));
}

bool SkColorTable_unique(reskia_color_table_t *color_table) {
    return reinterpret_cast<SkColorTable *>(color_table)->unique();
}

void SkColorTable_ref(reskia_color_table_t *color_table) {
    return reinterpret_cast<SkColorTable *>(color_table)->ref();
}

void SkColorTable_unref(reskia_color_table_t *color_table) {
    reinterpret_cast<SkColorTable *>(color_table)->unref();
}

// static

sk_color_table_t SkColorTable_Make(const uint8_t table[256]) {
    return static_sk_color_table_make(SkColorTable::Make(table));
}

sk_color_table_t SkColorTable_Make_2(const uint8_t tableA[256], const uint8_t tableR[256], const uint8_t tableG[256], const uint8_t tableB[256]) {
    return static_sk_color_table_make(SkColorTable::Make(tableA, tableR, tableG, tableB));
}

sk_color_table_t SkColorTable_Deserialize(reskia_read_buffer_t *buffer) {
    return static_sk_color_table_make(SkColorTable::Deserialize(*reinterpret_cast<SkReadBuffer *>(buffer)));
}

}
