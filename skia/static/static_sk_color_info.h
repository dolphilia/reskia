//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_STATIC_SK_COLOR_INFO_H
#define RAIA_SKIA_STATIC_SK_COLOR_INFO_H

#include <set>
#include <map>
#include "include/core/SkImageInfo.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_color_info_t;
void static_sk_color_info_delete(int key);
void * static_sk_color_info_get_ptr(int key); // -> SkColorInfo *
#ifdef __cplusplus
}
#endif

int static_sk_color_info_make(SkColorInfo value);
SkColorInfo static_sk_color_info_get(int key);
void static_sk_color_info_set(int key, SkColorInfo value);

#endif //RAIA_SKIA_STATIC_SK_COLOR_INFO_H
