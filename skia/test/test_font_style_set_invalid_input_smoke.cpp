#include "capi/sk_font_style.h"
#include "capi/sk_font_style_set.h"
#include "handles/static_sk_font_style.h"
#include "handles/static_sk_font_style-internal.h"
#include "handles/static_sk_font_style_set.h"

#include "include/core/SkFontStyle.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[font-style-set-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkFontStyle_delete(nullptr);

    if (!check(SkFontStyle_weight(nullptr) == 0, "SkFontStyle_weight(nullptr)")) {
        return 1;
    }
    if (!check(SkFontStyle_width(nullptr) == 0, "SkFontStyle_width(nullptr)")) {
        return 2;
    }
    if (!check(SkFontStyle_slant(nullptr) == -1, "SkFontStyle_slant(nullptr)")) {
        return 3;
    }

    const sk_font_style_t style_handle = static_sk_font_style_make(SkFontStyle());
    auto *style = static_cast<reskia_font_style_t *>(static_sk_font_style_get_ptr(style_handle));
    if (!check(style_handle != 0 && style != nullptr, "static_sk_font_style_make(valid)")) {
        return 4;
    }
    if (!check(SkFontStyle_weight(style) == 400, "SkFontStyle_weight(valid)")) {
        static_sk_font_style_delete(style_handle);
        return 5;
    }
    if (!check(SkFontStyle_width(style) == 5, "SkFontStyle_width(valid)")) {
        static_sk_font_style_delete(style_handle);
        return 6;
    }
    if (!check(SkFontStyle_slant(style) == 0, "SkFontStyle_slant(valid)")) {
        static_sk_font_style_delete(style_handle);
        return 7;
    }

    SkFontStyleSet_release(nullptr);
    SkFontStyleSet_ref(nullptr);
    SkFontStyleSet_unref(nullptr);
    SkFontStyleSet_getStyle(nullptr, 0, nullptr, nullptr);

    if (!check(SkFontStyleSet_count(nullptr) == 0, "SkFontStyleSet_count(nullptr)")) {
        static_sk_font_style_delete(style_handle);
        return 8;
    }
    if (!check(SkFontStyleSet_createTypeface(nullptr, 0) == 0, "SkFontStyleSet_createTypeface(nullptr)")) {
        static_sk_font_style_delete(style_handle);
        return 9;
    }
    if (!check(SkFontStyleSet_matchStyle(nullptr, nullptr) == 0, "SkFontStyleSet_matchStyle(nullptr, nullptr)")) {
        static_sk_font_style_delete(style_handle);
        return 10;
    }
    if (!check(!SkFontStyleSet_unique(nullptr), "SkFontStyleSet_unique(nullptr)")) {
        static_sk_font_style_delete(style_handle);
        return 11;
    }

    const sk_font_style_set_t set_handle = SkFontStyleSet_CreateEmpty();
    auto *set = static_cast<reskia_font_style_set_t *>(static_sk_font_style_set_get_ptr(set_handle));
    if (!check(set_handle != 0 && set != nullptr, "SkFontStyleSet_CreateEmpty(valid)")) {
        static_sk_font_style_delete(style_handle);
        return 12;
    }
    if (!check(SkFontStyleSet_count(set) == 0, "SkFontStyleSet_count(empty)")) {
        static_sk_font_style_set_delete(set_handle);
        static_sk_font_style_delete(style_handle);
        return 13;
    }

    SkFontStyleSet_getStyle(set, -1, style, nullptr);
    SkFontStyleSet_getStyle(set, 0, style, nullptr);

    if (!check(SkFontStyleSet_createTypeface(set, -1) == 0, "SkFontStyleSet_createTypeface(negative index)")) {
        static_sk_font_style_set_delete(set_handle);
        static_sk_font_style_delete(style_handle);
        return 14;
    }
    if (!check(SkFontStyleSet_createTypeface(set, 0) == 0, "SkFontStyleSet_createTypeface(empty)")) {
        static_sk_font_style_set_delete(set_handle);
        static_sk_font_style_delete(style_handle);
        return 15;
    }
    if (!check(SkFontStyleSet_matchStyle(set, nullptr) == 0, "SkFontStyleSet_matchStyle(null pattern)")) {
        static_sk_font_style_set_delete(set_handle);
        static_sk_font_style_delete(style_handle);
        return 16;
    }
    if (!check(SkFontStyleSet_matchStyle(set, style) == 0, "SkFontStyleSet_matchStyle(empty)")) {
        static_sk_font_style_set_delete(set_handle);
        static_sk_font_style_delete(style_handle);
        return 17;
    }

    SkFontStyleSet_ref(set);
    SkFontStyleSet_unref(set);

    static_sk_font_style_set_delete(set_handle);
    static_sk_font_style_delete(style_handle);
    return 0;
}
