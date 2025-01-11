//
// Created by dolphilia on 2024/04/03.
//

#ifndef RAIA_SKIA_STATIC_SK_FONT_ARGUMENTS_VARIATION_POSITION_H
#define RAIA_SKIA_STATIC_SK_FONT_ARGUMENTS_VARIATION_POSITION_H

#include <set>
#include <map>
#include "include/core/SkFontArguments.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_font_arguments_variation_position_t;
void static_sk_font_arguments_variation_position_delete(int key);
void * static_sk_font_arguments_variation_position_get_ptr(int key); // -> SkFontArguments::VariationPosition *
#ifdef __cplusplus
}
#endif

int static_sk_font_arguments_variation_position_make(SkFontArguments::VariationPosition value);
SkFontArguments::VariationPosition static_sk_font_arguments_variation_position_get(int key);
void static_sk_font_arguments_variation_position_set(int key, SkFontArguments::VariationPosition value);

#endif //RAIA_SKIA_STATIC_SK_FONT_ARGUMENTS_VARIATION_POSITION_H
