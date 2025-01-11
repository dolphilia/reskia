//
// Created by dolphilia on 2024/04/03.
//

#ifndef RAIA_SKIA_STATIC_SK_FONT_ARGUMENTS_PALETTE_H
#define RAIA_SKIA_STATIC_SK_FONT_ARGUMENTS_PALETTE_H

#include <set>
#include <map>
#include "include/core/SkFontArguments.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_font_arguments_palette_t;
void static_sk_font_arguments_palette_delete(int key);
void * static_sk_font_arguments_palette_get_ptr(int key); // -> SkFontArguments::Palette *
#ifdef __cplusplus
}
#endif

int static_sk_font_arguments_palette_make(SkFontArguments::Palette value);
SkFontArguments::Palette static_sk_font_arguments_palette_get(int key);
void static_sk_font_arguments_palette_set(int key, SkFontArguments::Palette value);

#endif //RAIA_SKIA_STATIC_SK_FONT_ARGUMENTS_PALETTE_H
