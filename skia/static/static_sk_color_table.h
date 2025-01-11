//
// Created by dolphilia on 2024/01/05.
//

#ifndef RAIA_SKIA_STATIC_SK_COLOR_TABLE_H
#define RAIA_SKIA_STATIC_SK_COLOR_TABLE_H

#include <set>
#include <map>
#include "include/core/SkColorTable.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_color_table_t;
void static_sk_color_table_delete(int key);
void *static_sk_color_table_get(int key); // -> SkColorTable *
#ifdef __cplusplus
}
#endif

int static_sk_color_table_make(sk_sp<SkColorTable> value);
void static_sk_color_table_set(int key, sk_sp<SkColorTable> value);
sk_sp<SkColorTable> static_sk_color_table_move(int key);

#endif //RAIA_SKIA_STATIC_SK_COLOR_TABLE_H
