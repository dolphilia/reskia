//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_STATIC_SK_FONT_H
#define RAIA_SKIA_STATIC_SK_FONT_H

#include <set>
#include <map>
#include "include/core/SkFont.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_font_t;
void static_sk_font_delete(int key);
SkFont * static_sk_font_get_ptr(int key);
#ifdef __cplusplus
}
#endif

int static_sk_font_make(SkFont value);
SkFont static_sk_font_get(int key);
void static_sk_font_set(int key, SkFont value);

#endif //RAIA_SKIA_STATIC_SK_FONT_H
