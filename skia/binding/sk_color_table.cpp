//
// Created by dolphilia on 2024/01/08.
//

#include "sk_color_table.h"

#include "include/core/SkColorTable.h"

#include "../static/static_sk_color_table.h"

#include "../static/static_sk_color_table-internal.h"

extern "C" {

void SkColorTable_delete(void *color_table) {
    static_cast<SkColorTable *>(color_table)->unref();
}

const void * SkColorTable_alphaTable(void *color_table) {
    return static_cast<SkColorTable *>(color_table)->alphaTable();
}

const void * SkColorTable_redTable(void *color_table) {
    return static_cast<SkColorTable *>(color_table)->redTable();
}

const void * SkColorTable_greenTable(void *color_table) {
    return static_cast<SkColorTable *>(color_table)->greenTable();
}

const void * SkColorTable_blueTable(void *color_table) {
    return static_cast<SkColorTable *>(color_table)->blueTable();
}

void SkColorTable_flatten(void *color_table, void *buffer) {
    static_cast<SkColorTable *>(color_table)->flatten(* static_cast<SkWriteBuffer *>(buffer));
}

bool SkColorTable_unique(void *color_table) {
    return static_cast<SkColorTable *>(color_table)->unique();
}

void SkColorTable_ref(void *color_table) {
    return static_cast<SkColorTable *>(color_table)->ref();
}

void SkColorTable_unref(void *color_table) {
    static_cast<SkColorTable *>(color_table)->unref();
}

// static

sk_color_table_t SkColorTable_Make(const void * table) {
    return static_sk_color_table_make(SkColorTable::Make(static_cast<const uint8_t *>(table)));
}

sk_color_table_t SkColorTable_Make_2(const void * tableA, const void * tableR, const void * tableG, const void * tableB) {
    return static_sk_color_table_make(SkColorTable::Make(static_cast<const uint8_t *>(tableA), static_cast<const uint8_t *>(tableR), static_cast<const uint8_t *>(tableG), static_cast<const uint8_t *>(tableB)));
}

sk_color_table_t SkColorTable_Deserialize(void * buffer) {
    return static_sk_color_table_make(SkColorTable::Deserialize(* static_cast<SkReadBuffer *>(buffer)));
}

}
