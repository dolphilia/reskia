//
// Created by dolphilia on 2024/01/08.
//

#include "sk_data_table.h"

#include "include/core/SkDataTable.h"

#include "../static/static_sk_data_table.h"

#include "../static/static_sk_data_table-internal.h"

extern "C" {

void SkDataTable_delete(void *data_table) {
    const SkDataTable *table = static_cast<SkDataTable *>(data_table);
    delete &table;
}

bool SkDataTable_isEmpty(void *data_table) {
    return static_cast<SkDataTable *>(data_table)->isEmpty();
}

int SkDataTable_count(void *data_table) {
    return static_cast<SkDataTable *>(data_table)->count();
}

size_t SkDataTable_atSize(void *data_table, int index) {
    return static_cast<SkDataTable *>(data_table)->atSize(index);
}

const void * SkDataTable_at(void *data_table, int index, void *size) {
    return static_cast<SkDataTable *>(data_table)->at(index, static_cast<size_t *>(size));
}

const char * SkDataTable_atStr(void *data_table, int index) {
    return static_cast<SkDataTable *>(data_table)->atStr(index);
}

bool SkDataTable_unique(void *data_table) {
    return static_cast<SkDataTable *>(data_table)->unique();
}

void SkDataTable_ref(void *data_table) {
    static_cast<SkDataTable *>(data_table)->ref();
}

void SkDataTable_unref(void *data_table) {
    static_cast<SkDataTable *>(data_table)->unref();
}

// static

sk_data_table_t SkDataTable_MakeEmpty() {
    return static_sk_data_table_make(SkDataTable::MakeEmpty());
}

sk_data_table_t SkDataTable_MakeCopyArrays(const void *const *ptrs, const void * sizes, int count) {
    return static_sk_data_table_make(SkDataTable::MakeCopyArrays(ptrs, static_cast<const size_t *>(sizes), count));
}

sk_data_table_t SkDataTable_MakeCopyArray(const void *array, size_t elemSize, int count) {
    return static_sk_data_table_make(SkDataTable::MakeCopyArray(array, elemSize, count));
}

sk_data_table_t SkDataTable_MakeArrayProc(const void *array, size_t elemSize, int count, void (*proc)(void*), void *context) {
    return static_sk_data_table_make(SkDataTable::MakeArrayProc(array, elemSize, count, proc, context));
}

}
