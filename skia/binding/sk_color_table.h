//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_COLOR_TABLE_H
#define RAIA_SKIA_SK_COLOR_TABLE_H

#include "include/core/SkColorTable.h"
#include "../static/static_sk_color_table.h"
#include "export_api.h"

extern "C" {
RAIA_API void SkColorTable_delete(SkColorTable *color_table);
RAIA_API const uint8_t * SkColorTable_alphaTable(SkColorTable *color_table);
RAIA_API const uint8_t * SkColorTable_redTable(SkColorTable *color_table);
RAIA_API const uint8_t * SkColorTable_greenTable(SkColorTable *color_table);
RAIA_API const uint8_t * SkColorTable_blueTable(SkColorTable *color_table);
RAIA_API void SkColorTable_flatten(SkColorTable *color_table, SkWriteBuffer *buffer);
RAIA_API bool SkColorTable_unique(SkColorTable *color_table);
RAIA_API void SkColorTable_ref(SkColorTable *color_table);
RAIA_API void SkColorTable_unref(SkColorTable *color_table);
// static
RAIA_API sk_color_table_t SkColorTable_Make(const uint8_t table[256]);
RAIA_API sk_color_table_t SkColorTable_Make_2(const uint8_t tableA[256], const uint8_t tableR[256], const uint8_t tableG[256], const uint8_t tableB[256]);
RAIA_API sk_color_table_t SkColorTable_Deserialize(SkReadBuffer *buffer);
}

#endif //RAIA_SKIA_SK_COLOR_TABLE_H
