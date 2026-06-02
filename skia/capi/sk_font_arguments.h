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
void SkFontArguments_delete(reskia_font_arguments_t *font_arguments); // No-op for NULL input.
sk_font_arguments_t SkFontArguments_setCollectionIndex(reskia_font_arguments_t *font_arguments, int collectionIndex); // collectionIndex must be >= 0. Returns 0 for invalid input.
sk_font_arguments_t SkFontArguments_setVariationDesignPosition(reskia_font_arguments_t *font_arguments, sk_font_arguments_variation_position_t position); // Returns 0 for invalid font_arguments. Invalid position handles are treated as the default position.
int SkFontArguments_getCollectionIndex(reskia_font_arguments_t *font_arguments); // Returns 0 for NULL input.
sk_font_arguments_variation_position_t SkFontArguments_getVariationDesignPosition(reskia_font_arguments_t *font_arguments); // Returns 0 for NULL input.
sk_font_arguments_t SkFontArguments_setPalette(reskia_font_arguments_t *font_arguments, sk_font_arguments_palette_t palette); // Returns 0 for invalid font_arguments. Invalid palette handles are treated as the default palette.
sk_font_arguments_palette_t SkFontArguments_getPalette(reskia_font_arguments_t *font_arguments); // Returns 0 for NULL input.
sk_font_arguments_t SkFontArguments_setSyntheticBold(reskia_font_arguments_t *font_arguments, bool hasValue, bool bold); // Returns 0 for invalid font_arguments.
bool SkFontArguments_getSyntheticBold(reskia_font_arguments_t *font_arguments, bool *bold); // Returns true and writes bold when a value is present. Returns false for NULL input.
sk_font_arguments_t SkFontArguments_setSyntheticOblique(reskia_font_arguments_t *font_arguments, bool hasValue, bool oblique); // Returns 0 for invalid font_arguments.
bool SkFontArguments_getSyntheticOblique(reskia_font_arguments_t *font_arguments, bool *oblique); // Returns true and writes oblique when a value is present. Returns false for NULL input.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_FONT_ARGUMENTS_H
