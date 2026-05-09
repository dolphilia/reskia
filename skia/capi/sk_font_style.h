//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_FONT_STYLE_H
#define RAIA_SKIA_SK_FONT_STYLE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_font_style_t reskia_font_style_t;
typedef int32_t reskia_font_style_slant_t;

void SkFontStyle_delete(reskia_font_style_t *font_style); // NULL 入力では no-op
int SkFontStyle_weight(reskia_font_style_t *font_style); // NULL 入力では 0
int SkFontStyle_width(reskia_font_style_t *font_style); // NULL 入力では 0
reskia_font_style_slant_t SkFontStyle_slant(reskia_font_style_t *font_style); // NULL 入力では -1

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_FONT_STYLE_H
