//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_DATA_TABLE_H
#define RAIA_SKIA_SK_DATA_TABLE_H

#include <stddef.h>
#include <stdint.h>
#include "../handles/static_sk_data_table.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_data_table_t reskia_data_table_t;

void SkDataTable_release(reskia_data_table_t *data_table); // owned: caller が保持する参照を release する。NULL 入力では no-op
bool SkDataTable_isEmpty(reskia_data_table_t *data_table); // NULL 入力では true (SkDataTable *data_table) -> bool
int SkDataTable_count(reskia_data_table_t *data_table); // NULL 入力では 0 (SkDataTable *data_table) -> int
size_t SkDataTable_atSize(reskia_data_table_t *data_table, int index); // 範囲外/NULL 入力では 0 (SkDataTable *data_table, int index) -> size_t
const uint8_t * SkDataTable_at(reskia_data_table_t *data_table, int index, size_t *size); // borrowed: 解放不要。範囲外/NULL 入力では NULL、size が非 NULL なら 0
const char * SkDataTable_atStr(reskia_data_table_t *data_table, int index); // borrowed: 解放不要。範囲外/NULL 入力では NULL
bool SkDataTable_unique(reskia_data_table_t *data_table); // (SkDataTable *data_table) -> bool
void SkDataTable_ref(reskia_data_table_t *data_table); // retained: 参照カウントを増やす。NULL 入力では no-op
void SkDataTable_unref(reskia_data_table_t *data_table); // owned: 参照カウントを減らす。NULL 入力では no-op

// static

sk_data_table_t SkDataTable_MakeEmpty(); // () -> sk_data_table_t
sk_data_table_t SkDataTable_MakeCopyArrays(const uint8_t * const *ptrs, const size_t *sizes, int count); // ptrs/sizes は count 要素以上。count <= 0 は空 table。NULL 入力では 0
sk_data_table_t SkDataTable_MakeCopyArray(const uint8_t *array, size_t elemSize, int count); // array は elemSize*count バイト以上。count <= 0 は空 table。NULL/elemSize 0 では 0
sk_data_table_t SkDataTable_MakeArrayProc(const uint8_t *array, size_t elemSize, int count, void (*proc)(void*), void *context); // array ownership を渡す。count <= 0 は空 table。NULL/elemSize 0 では 0

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_DATA_TABLE_H
