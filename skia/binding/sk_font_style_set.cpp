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

void SkFontStyleSet_delete(void *font_style_set) {
    delete static_cast<SkFontStyleSet *>(font_style_set);
}

int SkFontStyleSet_count(void *font_style_set) {
    return static_cast<SkFontStyleSet *>(font_style_set)->count();
}

void SkFontStyleSet_getStyle(void *font_style_set, int index, void * font_style, void *style) {
    return static_cast<SkFontStyleSet *>(font_style_set)->getStyle(index, static_cast<SkFontStyle *>(font_style), static_cast<SkString *>(style));
}

sk_typeface_t SkFontStyleSet_createTypeface(void *font_style_set, int index) {
    return static_sk_typeface_make(static_cast<SkFontStyleSet *>(font_style_set)->createTypeface(index));
}

sk_typeface_t SkFontStyleSet_matchStyle(void *font_style_set, const void *pattern) {
    return static_sk_typeface_make(static_cast<SkFontStyleSet *>(font_style_set)->matchStyle(* static_cast<const SkFontStyle *>(pattern)));
}

bool SkFontStyleSet_unique(void *font_style_set) {
    return static_cast<SkFontStyleSet *>(font_style_set)->unique();
}

void SkFontStyleSet_ref(void *font_style_set) {
    return static_cast<SkFontStyleSet *>(font_style_set)->ref();
}

void SkFontStyleSet_unref(void *font_style_set) {
    return static_cast<SkFontStyleSet *>(font_style_set)->unref();
}

// static

sk_font_style_set_t SkFontStyleSet_CreateEmpty() {
    return static_sk_font_style_set_make(SkFontStyleSet::CreateEmpty());
}

}
