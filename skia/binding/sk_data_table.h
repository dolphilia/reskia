//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_DATA_TABLE_H
#define RAIA_SKIA_SK_DATA_TABLE_H

#include <stddef.h>
#include <stdint.h>
#include "../static/static_sk_data_table.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_data_table_t reskia_data_table_t;

void SkDataTable_delete(reskia_data_table_t *data_table); // owned: caller が保持する参照を release する (SkDataTable *data_table)
bool SkDataTable_isEmpty(reskia_data_table_t *data_table); // (SkDataTable *data_table) -> bool
int SkDataTable_count(reskia_data_table_t *data_table); // (SkDataTable *data_table) -> int
size_t SkDataTable_atSize(reskia_data_table_t *data_table, int index); // (SkDataTable *data_table, int index) -> size_t
const uint8_t * SkDataTable_at(reskia_data_table_t *data_table, int index, size_t *size); // borrowed: 解放不要の借用ポインタ (SkDataTable *data_table, int index, size_t *size) -> const void *
const char * SkDataTable_atStr(reskia_data_table_t *data_table, int index); // borrowed: 解放不要の借用ポインタ (SkDataTable *data_table, int index) -> const char *
bool SkDataTable_unique(reskia_data_table_t *data_table); // (SkDataTable *data_table) -> bool
void SkDataTable_ref(reskia_data_table_t *data_table); // retained: 参照カウントを増やす (SkDataTable *data_table)
void SkDataTable_unref(reskia_data_table_t *data_table); // owned: 参照カウントを減らす (SkDataTable *data_table)

// static

sk_data_table_t SkDataTable_MakeEmpty(); // () -> sk_data_table_t
sk_data_table_t SkDataTable_MakeCopyArrays(const uint8_t * const *ptrs, const size_t *sizes, int count); // (const void *const *ptrs, const size_t sizes[], int count) -> sk_data_table_t
sk_data_table_t SkDataTable_MakeCopyArray(const uint8_t *array, size_t elemSize, int count); // (const void *array, size_t elemSize, int count) -> sk_data_table_t
sk_data_table_t SkDataTable_MakeArrayProc(const uint8_t *array, size_t elemSize, int count, void (*proc)(void*), void *context); // (const void *array, size_t elemSize, int count, SkDataTable::FreeProc proc, void *context) -> sk_data_table_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_DATA_TABLE_H
