//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_COLOR_TABLE_H
#define RAIA_SKIA_SK_COLOR_TABLE_H

#include <stdint.h>
#include "../static/static_sk_color_table.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_color_table_t reskia_color_table_t;
typedef struct reskia_read_buffer_t reskia_read_buffer_t;
typedef struct reskia_write_buffer_t reskia_write_buffer_t;

void SkColorTable_delete(reskia_color_table_t *color_table); // owned: caller が保持する参照を release する (SkColorTable *color_table)
const uint8_t *SkColorTable_alphaTable(reskia_color_table_t *color_table); // borrowed: 解放不要の借用ポインタ (SkColorTable *color_table) -> const uint8_t *
const uint8_t *SkColorTable_redTable(reskia_color_table_t *color_table); // borrowed: 解放不要の借用ポインタ (SkColorTable *color_table) -> const uint8_t *
const uint8_t *SkColorTable_greenTable(reskia_color_table_t *color_table); // borrowed: 解放不要の借用ポインタ (SkColorTable *color_table) -> const uint8_t *
const uint8_t *SkColorTable_blueTable(reskia_color_table_t *color_table); // borrowed: 解放不要の借用ポインタ (SkColorTable *color_table) -> const uint8_t *
void SkColorTable_flatten(reskia_color_table_t *color_table, reskia_write_buffer_t *buffer); // (SkColorTable *color_table, SkWriteBuffer *buffer)
bool SkColorTable_unique(reskia_color_table_t *color_table); // (SkColorTable *color_table) -> bool
void SkColorTable_ref(reskia_color_table_t *color_table); // retained: 参照カウントを増やす (SkColorTable *color_table)
void SkColorTable_unref(reskia_color_table_t *color_table); // owned: 参照カウントを減らす (SkColorTable *color_table)

// static

sk_color_table_t SkColorTable_Make(const uint8_t table[256]); // (const uint8_t table[256]) -> sk_color_table_t
sk_color_table_t SkColorTable_Make_2(const uint8_t tableA[256], const uint8_t tableR[256], const uint8_t tableG[256], const uint8_t tableB[256]); // (const uint8_t tableA[256], const uint8_t tableR[256], const uint8_t tableG[256], const uint8_t tableB[256]) -> sk_color_table_t
sk_color_table_t SkColorTable_Deserialize(reskia_read_buffer_t *buffer); // (SkReadBuffer *buffer) -> sk_color_table_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_COLOR_TABLE_H
