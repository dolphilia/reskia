#include <cstdio>

#include "capi/sk_font_mgr.h"
#include "capi/sk_font_style_set.h"
#include "capi/sk_paragraph_typeface_font_provider.h"
#include "capi/sk_string.h"
#include "handles/static_sk_font_mgr.h"
#include "handles/static_sk_font_style_set.h"
#include "handles/static_sk_typeface.h"

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[paragraph-typeface-font-provider-capi-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool smoke_null_inputs() {
    return check(SkParagraph_TypefaceFontProvider_refFontMgr(nullptr) == 0, "ref font mgr null") &&
           check(SkParagraph_TypefaceFontProvider_registerTypeface(nullptr, 0) == 0, "register null") &&
           check(SkParagraph_TypefaceFontProvider_registerTypefaceWithAlias(nullptr, 0, nullptr) == 0, "register alias null") &&
           check(SkParagraph_TypefaceFontProvider_onCountFamilies(nullptr) == 0, "count null") &&
           check(SkParagraph_TypefaceFontProvider_onGetFamilyName(nullptr, 0) == nullptr, "family name null") &&
           check(SkParagraph_TypefaceFontProvider_onMatchFamily(nullptr, nullptr) == 0, "match family null") &&
           check(SkParagraph_TypefaceFontProvider_onCreateStyleSet(nullptr, 0) == 0, "create style set null") &&
           check(SkParagraph_TypefaceFontProvider_onMatchFamilyStyle(nullptr, nullptr, 0) == 0, "match family style null") &&
           check(SkParagraph_TypefaceFontProvider_onMatchFamilyStyleCharacter(nullptr, nullptr, 0, nullptr, 0, 0) == 0, "match character null") &&
           check(SkParagraph_TypefaceFontProvider_onMakeFromData(nullptr, 0, 0) == 0, "make data null") &&
           check(SkParagraph_TypefaceFontProvider_onMakeFromStreamIndex(nullptr, 0, 0) == 0, "make stream index null") &&
           check(SkParagraph_TypefaceFontProvider_onMakeFromStreamArgs(nullptr, 0, nullptr) == 0, "make stream args null") &&
           check(SkParagraph_TypefaceFontProvider_onMakeFromFile(nullptr, nullptr, 0) == 0, "make file null") &&
           check(SkParagraph_TypefaceFontProvider_onLegacyMakeTypeface(nullptr, nullptr, 0) == 0, "legacy null") &&
           check(SkParagraph_TypefaceFontStyleSet_getFamilyName(0) == nullptr, "style set family null") &&
           check(SkParagraph_TypefaceFontStyleSet_getAlias(0) == nullptr, "style set alias null") &&
           check(!SkParagraph_TypefaceFontStyleSet_appendTypeface(0, 0), "style set append null");
}

bool smoke_typeface_font_provider() {
    auto *provider = SkParagraph_TypefaceFontProvider_new();
    if (!check(provider != nullptr, "provider new")) {
        return false;
    }

    if (!check(SkParagraph_TypefaceFontProvider_onCountFamilies(provider) == 0, "initial family count") ||
        !check(SkParagraph_TypefaceFontProvider_onGetFamilyName(provider, 0) == nullptr, "initial family name") ||
        !check(SkParagraph_TypefaceFontProvider_onMatchFamily(provider, "reskia-alias") == 0, "initial match family")) {
        SkParagraph_TypefaceFontProvider_release(provider);
        return false;
    }

    sk_font_mgr_t provider_mgr = SkParagraph_TypefaceFontProvider_refFontMgr(provider);
    if (!check(provider_mgr != 0, "provider font mgr handle")) {
        SkParagraph_TypefaceFontProvider_release(provider);
        return false;
    }
    auto *provider_mgr_ptr = reinterpret_cast<reskia_font_mgr_t *>(static_sk_font_mgr_get_ptr(provider_mgr));
    if (!check(provider_mgr_ptr != nullptr, "provider font mgr ptr") ||
        !check(SkFontMgr_countFamilies(provider_mgr_ptr) == 0, "provider font mgr count")) {
        static_sk_font_mgr_delete(provider_mgr);
        SkParagraph_TypefaceFontProvider_release(provider);
        return false;
    }

    sk_font_mgr_t default_mgr = SkFontMgr_RefEmpty();
    auto *default_mgr_ptr = reinterpret_cast<reskia_font_mgr_t *>(static_sk_font_mgr_get_ptr(default_mgr));
    sk_typeface_t typeface = default_mgr_ptr == nullptr ? 0 : SkFontMgr_legacyMakeTypeface(default_mgr_ptr, nullptr, 0);
    if (!check(typeface != 0, "default typeface")) {
        static_sk_font_mgr_delete(default_mgr);
        static_sk_font_mgr_delete(provider_mgr);
        SkParagraph_TypefaceFontProvider_release(provider);
        return false;
    }

    if (!check(SkParagraph_TypefaceFontProvider_registerTypefaceWithAlias(provider, typeface, "reskia-alias") == 1, "register alias") ||
        !check(SkParagraph_TypefaceFontProvider_onCountFamilies(provider) == 1, "family count")) {
        static_sk_typeface_delete(typeface);
        static_sk_font_mgr_delete(default_mgr);
        static_sk_font_mgr_delete(provider_mgr);
        SkParagraph_TypefaceFontProvider_release(provider);
        return false;
    }

    reskia_string_t *family_name = SkParagraph_TypefaceFontProvider_onGetFamilyName(provider, 0);
    if (!check(family_name != nullptr && SkString_equalsText(family_name, "reskia-alias"), "family name")) {
        SkString_delete(family_name);
        static_sk_typeface_delete(typeface);
        static_sk_font_mgr_delete(default_mgr);
        static_sk_font_mgr_delete(provider_mgr);
        SkParagraph_TypefaceFontProvider_release(provider);
        return false;
    }
    SkString_delete(family_name);

    sk_font_style_set_t style_set = SkParagraph_TypefaceFontProvider_onMatchFamily(provider, "reskia-alias");
    if (!check(style_set != 0, "match family")) {
        static_sk_typeface_delete(typeface);
        static_sk_font_mgr_delete(default_mgr);
        static_sk_font_mgr_delete(provider_mgr);
        SkParagraph_TypefaceFontProvider_release(provider);
        return false;
    }
    auto *style_set_ptr = reinterpret_cast<reskia_font_style_set_t *>(static_sk_font_style_set_get_ptr(style_set));
    if (!check(style_set_ptr != nullptr && SkFontStyleSet_count(style_set_ptr) == 1, "style set count")) {
        static_sk_font_style_set_delete(style_set);
        static_sk_typeface_delete(typeface);
        static_sk_font_mgr_delete(default_mgr);
        static_sk_font_mgr_delete(provider_mgr);
        SkParagraph_TypefaceFontProvider_release(provider);
        return false;
    }
    reskia_string_t *style_family = SkParagraph_TypefaceFontStyleSet_getFamilyName(style_set);
    if (!check(style_family != nullptr && SkString_equalsText(style_family, "reskia-alias"), "style set family")) {
        SkString_delete(style_family);
        static_sk_font_style_set_delete(style_set);
        static_sk_typeface_delete(typeface);
        static_sk_font_mgr_delete(default_mgr);
        static_sk_font_mgr_delete(provider_mgr);
        SkParagraph_TypefaceFontProvider_release(provider);
        return false;
    }
    SkString_delete(style_family);
    reskia_string_t *style_alias = SkParagraph_TypefaceFontStyleSet_getAlias(style_set);
    if (!check(style_alias != nullptr, "style set alias")) {
        SkString_delete(style_alias);
        static_sk_font_style_set_delete(style_set);
        static_sk_typeface_delete(typeface);
        static_sk_font_mgr_delete(default_mgr);
        static_sk_font_mgr_delete(provider_mgr);
        SkParagraph_TypefaceFontProvider_release(provider);
        return false;
    }
    SkString_delete(style_alias);
    if (!check(SkParagraph_TypefaceFontStyleSet_appendTypeface(style_set, typeface), "style set append") ||
        !check(SkFontStyleSet_count(style_set_ptr) == 2, "style set count after append")) {
        static_sk_font_style_set_delete(style_set);
        static_sk_typeface_delete(typeface);
        static_sk_font_mgr_delete(default_mgr);
        static_sk_font_mgr_delete(provider_mgr);
        SkParagraph_TypefaceFontProvider_release(provider);
        return false;
    }

    sk_typeface_t matched = SkFontStyleSet_createTypeface(style_set_ptr, 0);
    if (!check(matched != 0, "style set create typeface")) {
        static_sk_font_style_set_delete(style_set);
        static_sk_typeface_delete(typeface);
        static_sk_font_mgr_delete(default_mgr);
        static_sk_font_mgr_delete(provider_mgr);
        SkParagraph_TypefaceFontProvider_release(provider);
        return false;
    }

    static_sk_typeface_delete(matched);
    static_sk_font_style_set_delete(style_set);
    static_sk_typeface_delete(typeface);
    static_sk_font_mgr_delete(default_mgr);
    static_sk_font_mgr_delete(provider_mgr);
    SkParagraph_TypefaceFontProvider_release(provider);
    return true;
}

}  // namespace

int main() {
    return smoke_null_inputs() && smoke_typeface_font_provider() ? 0 : 1;
}
