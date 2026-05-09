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

void SkFontStyleSet_release(reskia_font_style_set_t *font_style_set); // owned: caller が保持する参照を release する。NULL 入力では no-op
int SkFontStyleSet_count(reskia_font_style_set_t *font_style_set); // NULL 入力では 0
void SkFontStyleSet_getStyle(reskia_font_style_set_t *font_style_set, int index, reskia_font_style_t *font_style, reskia_string_t *style); // index 範囲内。font_style/style はどちらか非 NULL。invalid 入力では no-op
sk_typeface_t SkFontStyleSet_createTypeface(reskia_font_style_set_t *font_style_set, int index); // index 範囲内。invalid 入力や生成不能では 0
sk_typeface_t SkFontStyleSet_matchStyle(reskia_font_style_set_t *font_style_set, const reskia_font_style_t *pattern); // pattern は非 NULL。NULL 入力や生成不能では 0
bool SkFontStyleSet_unique(reskia_font_style_set_t *font_style_set); // NULL 入力では false
void SkFontStyleSet_ref(reskia_font_style_set_t *font_style_set); // retained: 参照カウントを増やす。NULL 入力では no-op
void SkFontStyleSet_unref(reskia_font_style_set_t *font_style_set); // owned: 参照カウントを減らす。NULL 入力では no-op

// static

sk_font_style_set_t SkFontStyleSet_CreateEmpty(); // 生成不能では 0

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_FONT_STYLE_SET_H
