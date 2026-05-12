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

void SkColorTable_release(reskia_color_table_t *color_table); // owned: caller が保持する参照を release する。NULL 入力では no-op
const uint8_t *SkColorTable_alphaTable(reskia_color_table_t *color_table); // borrowed: 256 要素、解放不要。NULL 入力では NULL
const uint8_t *SkColorTable_redTable(reskia_color_table_t *color_table); // borrowed: 256 要素、解放不要。NULL 入力では NULL
const uint8_t *SkColorTable_greenTable(reskia_color_table_t *color_table); // borrowed: 256 要素、解放不要。NULL 入力では NULL
const uint8_t *SkColorTable_blueTable(reskia_color_table_t *color_table); // borrowed: 256 要素、解放不要。NULL 入力では NULL
void SkColorTable_flatten(reskia_color_table_t *color_table, reskia_write_buffer_t *buffer); // buffer は非 NULL。NULL 入力では no-op
bool SkColorTable_unique(reskia_color_table_t *color_table); // NULL 入力では false
void SkColorTable_ref(reskia_color_table_t *color_table); // retained: 参照カウントを増やす。NULL 入力では no-op
void SkColorTable_unref(reskia_color_table_t *color_table); // owned: 参照カウントを減らす。NULL 入力では no-op

// static

sk_color_table_t SkColorTable_Make(const uint8_t table[256]); // table は 256 要素以上、非 NULL。NULL 入力では 0
/**
 * 各 table は NULL 許可で identity 扱い
 */
sk_color_table_t SkColorTable_MakeARGBTables(const uint8_t tableA[256], const uint8_t tableR[256], const uint8_t tableG[256], const uint8_t tableB[256]);
sk_color_table_t SkColorTable_Deserialize(reskia_read_buffer_t *buffer); // buffer は非 NULL。NULL 入力や生成不能では 0

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_COLOR_TABLE_H
