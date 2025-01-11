//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_STATIC_SK_FONT_ARGUMENTS_H
#define RAIA_SKIA_STATIC_SK_FONT_ARGUMENTS_H

#include <set>
#include <map>
#include "include/core/SkFontArguments.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_font_arguments_t;
void static_sk_font_arguments_delete(int key);
void * static_sk_font_arguments_get_ptr(int key); // -> SkFontArguments *
#ifdef __cplusplus
}
#endif

int static_sk_font_arguments_make(SkFontArguments value);
SkFontArguments static_sk_font_arguments_get(int key);
void static_sk_font_arguments_set(int key, SkFontArguments value);

#endif //RAIA_SKIA_STATIC_SK_FONT_ARGUMENTS_H
