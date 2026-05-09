//
// Created by dolphilia on 2024/01/08.
//

#include "sk_font_style_set.h"

#include "include/core/SkFontMgr.h"
#include "include/core/SkString.h"

#include "../handles/static_sk_typeface.h"
#include "../handles/static_sk_font_style_set.h"

#include "../handles/static_sk_font_style_set-internal.h"
#include "../handles/static_sk_typeface-internal.h"

#include <utility>

namespace {

sk_typeface_t make_typeface_handle(sk_sp<SkTypeface> typeface) {
    if (!typeface) {
        return 0;
    }
    return static_sk_typeface_make(std::move(typeface));
}

sk_font_style_set_t make_font_style_set_handle(sk_sp<SkFontStyleSet> font_style_set) {
    if (!font_style_set) {
        return 0;
    }
    return static_sk_font_style_set_make(std::move(font_style_set));
}

bool is_valid_index(SkFontStyleSet *font_style_set, int index) {
    return font_style_set != nullptr && 0 <= index && index < font_style_set->count();
}

}  // namespace

extern "C" {

void SkFontStyleSet_release(reskia_font_style_set_t *font_style_set) {
    if (font_style_set == nullptr) {
        return;
    }
    reinterpret_cast<SkFontStyleSet *>(font_style_set)->unref();
}

int SkFontStyleSet_count(reskia_font_style_set_t *font_style_set) {
    if (font_style_set == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkFontStyleSet *>(font_style_set)->count();
}

void SkFontStyleSet_getStyle(reskia_font_style_set_t *font_style_set, int index, reskia_font_style_t *font_style, reskia_string_t *style) {
    auto *sk_font_style_set = reinterpret_cast<SkFontStyleSet *>(font_style_set);
    if (!is_valid_index(sk_font_style_set, index) || (font_style == nullptr && style == nullptr)) {
        return;
    }
    SkFontStyle scratch_font_style;
    SkString scratch_style;
    sk_font_style_set->getStyle(
            index,
            font_style != nullptr ? reinterpret_cast<SkFontStyle *>(font_style) : &scratch_font_style,
            style != nullptr ? reinterpret_cast<SkString *>(style) : &scratch_style);
}

sk_typeface_t SkFontStyleSet_createTypeface(reskia_font_style_set_t *font_style_set, int index) {
    auto *sk_font_style_set = reinterpret_cast<SkFontStyleSet *>(font_style_set);
    if (!is_valid_index(sk_font_style_set, index)) {
        return 0;
    }
    return make_typeface_handle(sk_font_style_set->createTypeface(index));
}

sk_typeface_t SkFontStyleSet_matchStyle(reskia_font_style_set_t *font_style_set, const reskia_font_style_t *pattern) {
    if (font_style_set == nullptr || pattern == nullptr) {
        return 0;
    }
    return make_typeface_handle(reinterpret_cast<SkFontStyleSet *>(font_style_set)->matchStyle(* reinterpret_cast<const SkFontStyle *>(pattern)));
}

bool SkFontStyleSet_unique(reskia_font_style_set_t *font_style_set) {
    if (font_style_set == nullptr) {
        return false;
    }
    return reinterpret_cast<SkFontStyleSet *>(font_style_set)->unique();
}

void SkFontStyleSet_ref(reskia_font_style_set_t *font_style_set) {
    if (font_style_set == nullptr) {
        return;
    }
    reinterpret_cast<SkFontStyleSet *>(font_style_set)->ref();
}

void SkFontStyleSet_unref(reskia_font_style_set_t *font_style_set) {
    if (font_style_set == nullptr) {
        return;
    }
    return reinterpret_cast<SkFontStyleSet *>(font_style_set)->unref();
}

// static

sk_font_style_set_t SkFontStyleSet_CreateEmpty() {
    return make_font_style_set_handle(SkFontStyleSet::CreateEmpty());
}

}
