//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_FONT_STYLE_SET_H
#define RAIA_SKIA_SK_FONT_STYLE_SET_H

#include "../handles/static_sk_font_style_set.h"
#include "../handles/static_sk_typeface.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_font_style_set_t reskia_font_style_set_t;
typedef struct reskia_font_style_t reskia_font_style_t;
typedef struct reskia_string_t reskia_string_t;

void SkFontStyleSet_delete(reskia_font_style_set_t *font_style_set); // owned: caller が保持する参照を release する (SkFontStyleSet *font_style_set)
int SkFontStyleSet_count(reskia_font_style_set_t *font_style_set); // (SkFontStyleSet *font_style_set) -> int
void SkFontStyleSet_getStyle(reskia_font_style_set_t *font_style_set, int index, reskia_font_style_t *font_style, reskia_string_t *style); // (SkFontStyleSet *font_style_set, int index, SkFontStyle *font_style, SkString *style)
sk_typeface_t SkFontStyleSet_createTypeface(reskia_font_style_set_t *font_style_set, int index); // (SkFontStyleSet *font_style_set, int index) -> sk_typeface_t
sk_typeface_t SkFontStyleSet_matchStyle(reskia_font_style_set_t *font_style_set, const reskia_font_style_t *pattern); // (SkFontStyleSet *font_style_set, const SkFontStyle *pattern) -> sk_typeface_t
bool SkFontStyleSet_unique(reskia_font_style_set_t *font_style_set); // (SkFontStyleSet *font_style_set) -> bool
void SkFontStyleSet_ref(reskia_font_style_set_t *font_style_set); // retained: 参照カウントを増やす (SkFontStyleSet *font_style_set)
void SkFontStyleSet_unref(reskia_font_style_set_t *font_style_set); // owned: 参照カウントを減らす (SkFontStyleSet *font_style_set)

// static

sk_font_style_set_t SkFontStyleSet_CreateEmpty(); // () -> sk_font_style_set_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_FONT_STYLE_SET_H
