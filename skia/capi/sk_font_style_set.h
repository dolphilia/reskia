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

void SkFontStyleSet_release(reskia_font_style_set_t *font_style_set); // Owned reference: releases the caller-held reference. No-op for NULL input.
int SkFontStyleSet_count(reskia_font_style_set_t *font_style_set); // Returns 0 for NULL input.
/**
 * index must be in range. At least one of font_style or style must be non-NULL.
 * No-op for invalid input.
 */
void SkFontStyleSet_getStyle(reskia_font_style_set_t *font_style_set, int index, reskia_font_style_t *font_style, reskia_string_t *style);
sk_typeface_t SkFontStyleSet_createTypeface(reskia_font_style_set_t *font_style_set, int index); // index must be in range. Returns 0 for invalid input or creation failure.
sk_typeface_t SkFontStyleSet_matchStyle(reskia_font_style_set_t *font_style_set, const reskia_font_style_t *pattern); // pattern must be non-NULL. Returns 0 for NULL input or creation failure.
bool SkFontStyleSet_unique(reskia_font_style_set_t *font_style_set); // Returns false for NULL input.
void SkFontStyleSet_ref(reskia_font_style_set_t *font_style_set); // Retains the object by incrementing the reference count. No-op for NULL input.
void SkFontStyleSet_unref(reskia_font_style_set_t *font_style_set); // Releases the object by decrementing the reference count. No-op for NULL input.

// static

sk_font_style_set_t SkFontStyleSet_CreateEmpty(); // Returns 0 on creation failure.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_FONT_STYLE_SET_H
