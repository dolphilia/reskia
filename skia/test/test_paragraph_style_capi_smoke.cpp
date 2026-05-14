#include <cstdio>

#include "capi/sk_paragraph_style.h"
#include "capi/sk_string.h"
#include "handles/static_sk_font_style.h"

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[paragraph-style-capi-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool smoke_strut_style() {
    if (!check(SkParagraph_StrutStyle_getFontFamiliesCount(nullptr) == 0, "strut families null") ||
        !check(SkParagraph_StrutStyle_getFontFamilyAt(nullptr, 0) == nullptr, "strut family at null") ||
        !check(SkParagraph_StrutStyle_getFontStyle(nullptr) == 0, "strut font style null") ||
        !check(!SkParagraph_StrutStyle_setFontStyle(nullptr, 0), "strut set font style null") ||
        !check(SkParagraph_StrutStyle_getFontSize(nullptr) == 0.0f, "strut font size null") ||
        !check(!SkParagraph_StrutStyle_getStrutEnabled(nullptr), "strut enabled null")) {
        return false;
    }

    reskia_paragraph_strut_style_t *style = SkParagraph_StrutStyle_new();
    if (!check(style != nullptr, "strut new")) {
        return false;
    }

    const char *families[] = {"sans-serif", "serif"};
    if (!check(SkParagraph_StrutStyle_setFontFamilies(style, families, 2), "strut set families") ||
        !check(SkParagraph_StrutStyle_getFontFamiliesCount(style) == 2, "strut family count")) {
        SkParagraph_StrutStyle_delete(style);
        return false;
    }
    reskia_string_t *family = SkParagraph_StrutStyle_getFontFamilyAt(style, 0);
    if (!check(family != nullptr && SkString_equalsTextWithLength(family, "sans-serif", 10), "strut family at")) {
        SkString_delete(family);
        SkParagraph_StrutStyle_delete(style);
        return false;
    }
    SkString_delete(family);

    SkParagraph_StrutStyle_setFontSize(style, 18.0f);
    SkParagraph_StrutStyle_setHeight(style, 1.25f);
    SkParagraph_StrutStyle_setLeading(style, 2.0f);
    SkParagraph_StrutStyle_setStrutEnabled(style, true);
    SkParagraph_StrutStyle_setForceStrutHeight(style, true);
    SkParagraph_StrutStyle_setHeightOverride(style, true);
    SkParagraph_StrutStyle_setHalfLeading(style, true);
    if (!check(SkParagraph_StrutStyle_getFontSize(style) == 18.0f, "strut font size") ||
        !check(SkParagraph_StrutStyle_getHeight(style) == 1.25f, "strut height") ||
        !check(SkParagraph_StrutStyle_getLeading(style) == 2.0f, "strut leading") ||
        !check(SkParagraph_StrutStyle_getStrutEnabled(style), "strut enabled") ||
        !check(SkParagraph_StrutStyle_getForceStrutHeight(style), "strut force height") ||
        !check(SkParagraph_StrutStyle_getHeightOverride(style), "strut height override") ||
        !check(SkParagraph_StrutStyle_getHalfLeading(style), "strut half leading")) {
        SkParagraph_StrutStyle_delete(style);
        return false;
    }

    reskia_paragraph_strut_style_t *copy = SkParagraph_StrutStyle_copy(style);
    if (!check(copy != nullptr, "strut copy") ||
        !check(SkParagraph_StrutStyle_equals(style, copy), "strut equals")) {
        SkParagraph_StrutStyle_delete(copy);
        SkParagraph_StrutStyle_delete(style);
        return false;
    }
    SkParagraph_StrutStyle_delete(copy);
    SkParagraph_StrutStyle_delete(style);
    return true;
}

bool smoke_paragraph_style() {
    if (!check(SkParagraph_ParagraphStyle_copy(nullptr) == nullptr, "paragraph copy null") ||
        !check(!SkParagraph_ParagraphStyle_equals(nullptr, nullptr), "paragraph equals null") ||
        !check(SkParagraph_ParagraphStyle_getStrutStyle(nullptr) == nullptr, "paragraph strut null") ||
        !check(!SkParagraph_ParagraphStyle_setStrutStyle(nullptr, nullptr), "paragraph set strut null") ||
        !check(!SkParagraph_ParagraphStyle_setTextDirection(nullptr, RESKIA_PARAGRAPH_TEXT_DIRECTION_LTR), "paragraph set direction null") ||
        !check(!SkParagraph_ParagraphStyle_setTextAlign(nullptr, RESKIA_PARAGRAPH_TEXT_ALIGN_LEFT), "paragraph set align null") ||
        !check(SkParagraph_ParagraphStyle_getEllipsis(nullptr) == nullptr, "paragraph ellipsis null") ||
        !check(SkParagraph_ParagraphStyle_getEllipsisUtf16(nullptr, nullptr, 0) == -1, "paragraph ellipsis utf16 null")) {
        return false;
    }

    reskia_paragraph_style_t *style = SkParagraph_ParagraphStyle_new();
    reskia_paragraph_strut_style_t *strut = SkParagraph_StrutStyle_new();
    if (!check(style != nullptr, "paragraph new") ||
        !check(strut != nullptr, "paragraph strut new")) {
        SkParagraph_StrutStyle_delete(strut);
        SkParagraph_ParagraphStyle_delete(style);
        return false;
    }

    SkParagraph_StrutStyle_setFontSize(strut, 20.0f);
    if (!check(SkParagraph_ParagraphStyle_setStrutStyle(style, strut), "paragraph set strut")) {
        SkParagraph_StrutStyle_delete(strut);
        SkParagraph_ParagraphStyle_delete(style);
        return false;
    }
    reskia_paragraph_strut_style_t *strut_copy = SkParagraph_ParagraphStyle_getStrutStyle(style);
    if (!check(strut_copy != nullptr, "paragraph get strut") ||
        !check(SkParagraph_StrutStyle_getFontSize(strut_copy) == 20.0f, "paragraph strut font size")) {
        SkParagraph_StrutStyle_delete(strut_copy);
        SkParagraph_StrutStyle_delete(strut);
        SkParagraph_ParagraphStyle_delete(style);
        return false;
    }
    SkParagraph_StrutStyle_delete(strut_copy);
    SkParagraph_StrutStyle_delete(strut);

    if (!check(SkParagraph_ParagraphStyle_setTextDirection(style, RESKIA_PARAGRAPH_TEXT_DIRECTION_LTR), "paragraph set direction") ||
        !check(SkParagraph_ParagraphStyle_getTextDirection(style) == RESKIA_PARAGRAPH_TEXT_DIRECTION_LTR, "paragraph get direction") ||
        !check(SkParagraph_ParagraphStyle_setTextAlign(style, RESKIA_PARAGRAPH_TEXT_ALIGN_CENTER), "paragraph set align") ||
        !check(SkParagraph_ParagraphStyle_getTextAlign(style) == RESKIA_PARAGRAPH_TEXT_ALIGN_CENTER, "paragraph get align")) {
        SkParagraph_ParagraphStyle_delete(style);
        return false;
    }

    SkParagraph_ParagraphStyle_setMaxLines(style, 3);
    SkParagraph_ParagraphStyle_setHeight(style, 1.5f);
    SkParagraph_ParagraphStyle_setReplaceTabCharacters(style, true);
    SkParagraph_ParagraphStyle_setApplyRoundingHack(style, false);
    if (!check(SkParagraph_ParagraphStyle_getMaxLines(style) == 3, "paragraph max lines") ||
        !check(SkParagraph_ParagraphStyle_getHeight(style) == 1.5f, "paragraph height") ||
        !check(SkParagraph_ParagraphStyle_getReplaceTabCharacters(style), "paragraph replace tabs") ||
        !check(!SkParagraph_ParagraphStyle_getApplyRoundingHack(style), "paragraph rounding hack")) {
        SkParagraph_ParagraphStyle_delete(style);
        return false;
    }

    if (!check(SkParagraph_ParagraphStyle_setEllipsis(style, "..."), "paragraph set ellipsis") ||
        !check(SkParagraph_ParagraphStyle_ellipsized(style), "paragraph ellipsized")) {
        SkParagraph_ParagraphStyle_delete(style);
        return false;
    }
    reskia_string_t *ellipsis = SkParagraph_ParagraphStyle_getEllipsis(style);
    if (!check(ellipsis != nullptr && SkString_equalsTextWithLength(ellipsis, "...", 3), "paragraph get ellipsis")) {
        SkString_delete(ellipsis);
        SkParagraph_ParagraphStyle_delete(style);
        return false;
    }
    SkString_delete(ellipsis);

    const uint16_t utf16[] = {'.', '.'};
    uint16_t utf16_out[4] = {};
    if (!check(SkParagraph_ParagraphStyle_setEllipsisUtf16(style, utf16, 2), "paragraph set ellipsis utf16") ||
        !check(SkParagraph_ParagraphStyle_getEllipsisUtf16(style, utf16_out, 4) == 2, "paragraph get ellipsis utf16") ||
        !check(utf16_out[0] == '.' && utf16_out[1] == '.', "paragraph ellipsis utf16 contents")) {
        SkParagraph_ParagraphStyle_delete(style);
        return false;
    }

    if (!check(SkParagraph_ParagraphStyle_setTextHeightBehavior(style, RESKIA_PARAGRAPH_TEXT_HEIGHT_DISABLE_ALL), "paragraph set height behavior") ||
        !check(SkParagraph_ParagraphStyle_getTextHeightBehavior(style) == RESKIA_PARAGRAPH_TEXT_HEIGHT_DISABLE_ALL, "paragraph get height behavior") ||
        !check(SkParagraph_ParagraphStyle_effective_align(style) >= RESKIA_PARAGRAPH_TEXT_ALIGN_LEFT, "paragraph effective align") ||
        !check(SkParagraph_ParagraphStyle_hintingIsOn(style), "paragraph hinting on")) {
        SkParagraph_ParagraphStyle_delete(style);
        return false;
    }
    SkParagraph_ParagraphStyle_turnHintingOff(style);
    if (!check(!SkParagraph_ParagraphStyle_hintingIsOn(style), "paragraph hinting off")) {
        SkParagraph_ParagraphStyle_delete(style);
        return false;
    }

    reskia_paragraph_style_t *copy = SkParagraph_ParagraphStyle_copy(style);
    if (!check(copy != nullptr, "paragraph copy") ||
        !check(SkParagraph_ParagraphStyle_equals(style, copy), "paragraph equals")) {
        SkParagraph_ParagraphStyle_delete(copy);
        SkParagraph_ParagraphStyle_delete(style);
        return false;
    }
    SkParagraph_ParagraphStyle_delete(copy);
    SkParagraph_ParagraphStyle_delete(style);
    return true;
}

}  // namespace

int main() {
    return smoke_strut_style() && smoke_paragraph_style() ? 0 : 1;
}
