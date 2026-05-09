//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_FONT_ARGUMENTS_H
#define RAIA_SKIA_SK_FONT_ARGUMENTS_H

#include "../handles/static_sk_font_arguments.h"
#include "../handles/static_sk_font_arguments_palette.h"
#include "../handles/static_sk_font_arguments_variation_position.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_font_arguments_t reskia_font_arguments_t;

reskia_font_arguments_t *SkFontArguments_new(); // () -> SkFontArguments *
void SkFontArguments_delete(reskia_font_arguments_t *font_arguments); // NULL 入力では no-op
sk_font_arguments_t SkFontArguments_setCollectionIndex(reskia_font_arguments_t *font_arguments, int collectionIndex); // collectionIndex >= 0。invalid 入力では 0
sk_font_arguments_t SkFontArguments_setVariationDesignPosition(reskia_font_arguments_t *font_arguments, sk_font_arguments_variation_position_t position); // invalid font_arguments では 0。invalid position handle は default position として扱う
int SkFontArguments_getCollectionIndex(reskia_font_arguments_t *font_arguments); // NULL 入力では 0
sk_font_arguments_variation_position_t SkFontArguments_getVariationDesignPosition(reskia_font_arguments_t *font_arguments); // NULL 入力では 0
sk_font_arguments_t SkFontArguments_setPalette(reskia_font_arguments_t *font_arguments, sk_font_arguments_palette_t palette); // invalid font_arguments では 0。invalid palette handle は default palette として扱う
sk_font_arguments_palette_t SkFontArguments_getPalette(reskia_font_arguments_t *font_arguments); // NULL 入力では 0

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_FONT_ARGUMENTS_H
