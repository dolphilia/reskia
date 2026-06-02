//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_COLOR_TABLE_H
#define RAIA_SKIA_SK_COLOR_TABLE_H

#include <stdint.h>
#include "../handles/static_sk_color_table.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_color_table_t reskia_color_table_t;
typedef struct reskia_read_buffer_t reskia_read_buffer_t;
typedef struct reskia_write_buffer_t reskia_write_buffer_t;

void SkColorTable_release(reskia_color_table_t *color_table); // owned: releases the caller-held reference. No-op for NULL input.
const uint8_t *SkColorTable_alphaTable(reskia_color_table_t *color_table); // borrowed: 256 elements. Do not free. Returns NULL for NULL input.
const uint8_t *SkColorTable_redTable(reskia_color_table_t *color_table); // borrowed: 256 elements. Do not free. Returns NULL for NULL input.
const uint8_t *SkColorTable_greenTable(reskia_color_table_t *color_table); // borrowed: 256 elements. Do not free. Returns NULL for NULL input.
const uint8_t *SkColorTable_blueTable(reskia_color_table_t *color_table); // borrowed: 256 elements. Do not free. Returns NULL for NULL input.
void SkColorTable_flatten(reskia_color_table_t *color_table, reskia_write_buffer_t *buffer); // buffer must be non-NULL. No-op for NULL input.
bool SkColorTable_unique(reskia_color_table_t *color_table); // Returns false for NULL input.
void SkColorTable_ref(reskia_color_table_t *color_table); // retained: increments the reference count. No-op for NULL input.
void SkColorTable_unref(reskia_color_table_t *color_table); // owned: decrements the reference count. No-op for NULL input.

// static

sk_color_table_t SkColorTable_Make(const uint8_t table[256]); // table must contain at least 256 elements and be non-NULL. Returns 0 for NULL input.
/**
 * Each table may be NULL and is treated as identity.
 */
sk_color_table_t SkColorTable_MakeARGBTables(const uint8_t tableA[256], const uint8_t tableR[256], const uint8_t tableG[256], const uint8_t tableB[256]);
sk_color_table_t SkColorTable_Deserialize(reskia_read_buffer_t *buffer); // buffer must be non-NULL. Returns 0 for NULL input or failure.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_COLOR_TABLE_H
