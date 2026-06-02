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

void SkDataTable_release(reskia_data_table_t *data_table); // owned: releases the caller-held reference. No-op for NULL input.
bool SkDataTable_isEmpty(reskia_data_table_t *data_table); // Returns true for NULL input. (SkDataTable *data_table) -> bool
int SkDataTable_count(reskia_data_table_t *data_table); // Returns 0 for NULL input. (SkDataTable *data_table) -> int
size_t SkDataTable_atSize(reskia_data_table_t *data_table, int index); // Returns 0 for out-of-range/NULL input. (SkDataTable *data_table, int index) -> size_t
const uint8_t * SkDataTable_at(reskia_data_table_t *data_table, int index, size_t *size); // borrowed: do not free. Returns NULL for out-of-range/NULL input and writes 0 when size is non-NULL.
const char * SkDataTable_atStr(reskia_data_table_t *data_table, int index); // borrowed: do not free. Returns NULL for out-of-range/NULL input.
bool SkDataTable_unique(reskia_data_table_t *data_table); // (SkDataTable *data_table) -> bool
void SkDataTable_ref(reskia_data_table_t *data_table); // retained: increments the reference count. No-op for NULL input.
void SkDataTable_unref(reskia_data_table_t *data_table); // owned: decrements the reference count. No-op for NULL input.

// static

sk_data_table_t SkDataTable_MakeEmpty(); // () -> sk_data_table_t
/**
 * ptrs and sizes must contain at least count elements. count <= 0 creates an empty table.
 * Returns 0 for NULL input.
 */
sk_data_table_t SkDataTable_MakeCopyArrays(const uint8_t * const *ptrs, const size_t *sizes, int count);
/**
 * array must contain at least elemSize * count bytes. count <= 0 creates an empty table.
 * Returns 0 when array is NULL or elemSize is 0.
 */
sk_data_table_t SkDataTable_MakeCopyArray(const uint8_t *array, size_t elemSize, int count);
/**
 * Transfers array ownership. count <= 0 creates an empty table.
 * Returns 0 when array is NULL or elemSize is 0.
 */
sk_data_table_t SkDataTable_MakeArrayProc(const uint8_t *array, size_t elemSize, int count, void (*proc)(void*), void *context);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_DATA_TABLE_H
