//
// Created by dolphilia on 2024/01/08.
//

#include "sk_data_table.h"

#include "include/core/SkDataTable.h"

#include "../handles/static_sk_data_table.h"

#include "../handles/static_sk_data_table-internal.h"

extern "C" {

void SkDataTable_delete(reskia_data_table_t *data_table) {
    reinterpret_cast<SkDataTable *>(data_table)->unref();
}

bool SkDataTable_isEmpty(reskia_data_table_t *data_table) {
    return reinterpret_cast<SkDataTable *>(data_table)->isEmpty();
}

int SkDataTable_count(reskia_data_table_t *data_table) {
    return reinterpret_cast<SkDataTable *>(data_table)->count();
}

size_t SkDataTable_atSize(reskia_data_table_t *data_table, int index) {
    return reinterpret_cast<SkDataTable *>(data_table)->atSize(index);
}

const uint8_t * SkDataTable_at(reskia_data_table_t *data_table, int index, size_t *size) {
    return reinterpret_cast<const uint8_t *>(reinterpret_cast<SkDataTable *>(data_table)->at(index, size));
}

const char * SkDataTable_atStr(reskia_data_table_t *data_table, int index) {
    return reinterpret_cast<SkDataTable *>(data_table)->atStr(index);
}

bool SkDataTable_unique(reskia_data_table_t *data_table) {
    return reinterpret_cast<SkDataTable *>(data_table)->unique();
}

void SkDataTable_ref(reskia_data_table_t *data_table) {
    reinterpret_cast<SkDataTable *>(data_table)->ref();
}

void SkDataTable_unref(reskia_data_table_t *data_table) {
    reinterpret_cast<SkDataTable *>(data_table)->unref();
}

// static

sk_data_table_t SkDataTable_MakeEmpty() {
    return static_sk_data_table_make(SkDataTable::MakeEmpty());
}

sk_data_table_t SkDataTable_MakeCopyArrays(const uint8_t * const *ptrs, const size_t *sizes, int count) {
    return static_sk_data_table_make(SkDataTable::MakeCopyArrays(reinterpret_cast<const void *const *>(ptrs), sizes, count));
}

sk_data_table_t SkDataTable_MakeCopyArray(const uint8_t *array, size_t elemSize, int count) {
    return static_sk_data_table_make(SkDataTable::MakeCopyArray(array, elemSize, count));
}

sk_data_table_t SkDataTable_MakeArrayProc(const uint8_t *array, size_t elemSize, int count, void (*proc)(void*), void *context) {
    return static_sk_data_table_make(SkDataTable::MakeArrayProc(array, elemSize, count, proc, context));
}

}
