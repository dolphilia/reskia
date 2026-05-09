#include "capi/reskia_status.h"
#include "capi/sk_font_mgr.h"
#include "handles/static_sk_font_mgr.h"

#include "include/core/SkFontStyle.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[font-mgr-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkFontMgr_release(nullptr);
    SkFontMgr_getFamilyName(nullptr, 0, nullptr);
    SkFontMgr_ref(nullptr);
    SkFontMgr_unref(nullptr);

    if (!check(SkFontMgr_countFamilies(nullptr) == 0, "SkFontMgr_countFamilies(nullptr)")) {
        return 1;
    }

    sk_font_style_set_t style_set = 99;
    if (!check(SkFontMgr_createStyleSet(nullptr, 0, &style_set) == RESKIA_STATUS_INVALID_ARGUMENT && style_set == 0, "SkFontMgr_createStyleSet(nullptr)")) {
        return 2;
    }
    if (!check(SkFontMgr_createStyleSet(nullptr, 0, nullptr) == RESKIA_STATUS_INVALID_ARGUMENT, "SkFontMgr_createStyleSet(null out)")) {
        return 3;
    }

    style_set = 99;
    if (!check(SkFontMgr_matchFamily(nullptr, nullptr, &style_set) == RESKIA_STATUS_INVALID_ARGUMENT && style_set == 0, "SkFontMgr_matchFamily(nullptr)")) {
        return 4;
    }
    if (!check(SkFontMgr_matchFamily(nullptr, nullptr, nullptr) == RESKIA_STATUS_INVALID_ARGUMENT, "SkFontMgr_matchFamily(null out)")) {
        return 5;
    }

    SkFontStyle font_style;
    auto *reskia_style = reinterpret_cast<const reskia_font_style_t *>(&font_style);
    const char *bcp47[] = {"en"};

    if (!check(SkFontMgr_matchFamilyStyle(nullptr, nullptr, reskia_style) == 0, "SkFontMgr_matchFamilyStyle(nullptr)")) {
        return 6;
    }
    if (!check(SkFontMgr_matchFamilyStyleCharacter(nullptr, nullptr, reskia_style, nullptr, 0, 65) == 0, "SkFontMgr_matchFamilyStyleCharacter(nullptr)")) {
        return 7;
    }
    if (!check(SkFontMgr_matchFamilyStyleCharacter(reinterpret_cast<reskia_font_mgr_t *>(1), nullptr, reskia_style, nullptr, 1, 65) == 0, "SkFontMgr_matchFamilyStyleCharacter(null bcp47 with count)")) {
        return 8;
    }
    if (!check(SkFontMgr_makeFromData(nullptr, 0, 0) == 0, "SkFontMgr_makeFromData(nullptr)")) {
        return 9;
    }
    if (!check(SkFontMgr_makeFromStream(nullptr, 0, 0) == 0, "SkFontMgr_makeFromStream(nullptr)")) {
        return 10;
    }
    if (!check(SkFontMgr_makeFromStreamWithArguments(nullptr, 0, nullptr) == 0, "SkFontMgr_makeFromStreamWithArguments(nullptr)")) {
        return 11;
    }
    if (!check(SkFontMgr_makeFromFile(nullptr, nullptr, 0) == 0, "SkFontMgr_makeFromFile(nullptr)")) {
        return 12;
    }
    if (!check(SkFontMgr_legacyMakeTypeface(nullptr, nullptr, 0) == 0, "SkFontMgr_legacyMakeTypeface(nullptr)")) {
        return 13;
    }
    if (!check(!SkFontMgr_unique(nullptr), "SkFontMgr_unique(nullptr)")) {
        return 14;
    }

    const sk_font_mgr_t empty_handle = SkFontMgr_RefEmpty();
    auto *empty_mgr = static_cast<reskia_font_mgr_t *>(static_sk_font_mgr_get_ptr(empty_handle));
    if (!check(empty_handle != 0 && empty_mgr != nullptr, "SkFontMgr_RefEmpty()")) {
        return 15;
    }
    if (!check(SkFontMgr_countFamilies(empty_mgr) == 0, "SkFontMgr_countFamilies(empty)")) {
        static_sk_font_mgr_delete(empty_handle);
        return 16;
    }
    style_set = 99;
    if (!check(SkFontMgr_createStyleSet(empty_mgr, 0, &style_set) == RESKIA_STATUS_INVALID_ARGUMENT && style_set == 0, "SkFontMgr_createStyleSet(empty out of range)")) {
        static_sk_font_mgr_delete(empty_handle);
        return 17;
    }
    SkFontMgr_getFamilyName(empty_mgr, 0, nullptr);
    if (!check(SkFontMgr_matchFamilyStyle(empty_mgr, nullptr, nullptr) == 0, "SkFontMgr_matchFamilyStyle(null style)")) {
        static_sk_font_mgr_delete(empty_handle);
        return 18;
    }
    if (!check(SkFontMgr_matchFamilyStyle(empty_mgr, nullptr, reskia_style) == 0, "SkFontMgr_matchFamilyStyle(empty)")) {
        static_sk_font_mgr_delete(empty_handle);
        return 19;
    }
    if (!check(SkFontMgr_matchFamilyStyleCharacter(empty_mgr, nullptr, reskia_style, bcp47, 1, 65) == 0, "SkFontMgr_matchFamilyStyleCharacter(empty)")) {
        static_sk_font_mgr_delete(empty_handle);
        return 20;
    }
    if (!check(SkFontMgr_makeFromData(empty_mgr, 0, 0) == 0, "SkFontMgr_makeFromData(empty invalid data)")) {
        static_sk_font_mgr_delete(empty_handle);
        return 21;
    }
    if (!check(SkFontMgr_makeFromFile(empty_mgr, nullptr, 0) == 0, "SkFontMgr_makeFromFile(empty null path)")) {
        static_sk_font_mgr_delete(empty_handle);
        return 22;
    }
    if (!check(SkFontMgr_makeFromFile(empty_mgr, "__reskia_missing_font__.ttf", -1) == 0, "SkFontMgr_makeFromFile(negative index)")) {
        static_sk_font_mgr_delete(empty_handle);
        return 23;
    }
    if (!check(SkFontMgr_legacyMakeTypeface(empty_mgr, nullptr, 0) == 0, "SkFontMgr_legacyMakeTypeface(empty)")) {
        static_sk_font_mgr_delete(empty_handle);
        return 24;
    }
    SkFontMgr_ref(empty_mgr);
    SkFontMgr_unref(empty_mgr);
    static_sk_font_mgr_delete(empty_handle);
    return 0;
}
