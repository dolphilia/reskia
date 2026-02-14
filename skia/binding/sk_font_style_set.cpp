//
// Created by dolphilia on 2024/01/08.
//

#include "sk_font_style_set.h"

#include "include/core/SkFontMgr.h"

#include "../static/static_sk_typeface.h"
#include "../static/static_sk_font_style_set.h"

#include "../static/static_sk_font_style_set-internal.h"
#include "../static/static_sk_typeface-internal.h"

extern "C" {

void SkFontStyleSet_delete(reskia_font_style_set_t *font_style_set) {
    reinterpret_cast<SkFontStyleSet *>(font_style_set)->unref();
}

int SkFontStyleSet_count(reskia_font_style_set_t *font_style_set) {
    return reinterpret_cast<SkFontStyleSet *>(font_style_set)->count();
}

void SkFontStyleSet_getStyle(reskia_font_style_set_t *font_style_set, int index, reskia_font_style_t *font_style, reskia_string_t *style) {
    return reinterpret_cast<SkFontStyleSet *>(font_style_set)->getStyle(index, reinterpret_cast<SkFontStyle *>(font_style), reinterpret_cast<SkString *>(style));
}

sk_typeface_t SkFontStyleSet_createTypeface(reskia_font_style_set_t *font_style_set, int index) {
    return static_sk_typeface_make(reinterpret_cast<SkFontStyleSet *>(font_style_set)->createTypeface(index));
}

sk_typeface_t SkFontStyleSet_matchStyle(reskia_font_style_set_t *font_style_set, const reskia_font_style_t *pattern) {
    return static_sk_typeface_make(reinterpret_cast<SkFontStyleSet *>(font_style_set)->matchStyle(* reinterpret_cast<const SkFontStyle *>(pattern)));
}

bool SkFontStyleSet_unique(reskia_font_style_set_t *font_style_set) {
    return reinterpret_cast<SkFontStyleSet *>(font_style_set)->unique();
}

void SkFontStyleSet_ref(reskia_font_style_set_t *font_style_set) {
    return reinterpret_cast<SkFontStyleSet *>(font_style_set)->ref();
}

void SkFontStyleSet_unref(reskia_font_style_set_t *font_style_set) {
    return reinterpret_cast<SkFontStyleSet *>(font_style_set)->unref();
}

// static

sk_font_style_set_t SkFontStyleSet_CreateEmpty() {
    return static_sk_font_style_set_make(SkFontStyleSet::CreateEmpty());
}

}
