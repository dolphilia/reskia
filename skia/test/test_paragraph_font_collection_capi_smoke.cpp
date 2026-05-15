#include <cstdio>

#include "capi/sk_font_mgr.h"
#include "capi/sk_paragraph_font_collection.h"
#include "handles/static_sk_font_mgr.h"
#include "handles/static_sk_typeface.h"

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[paragraph-font-collection-capi-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool smoke_null_inputs() {
    const char *families[] = {"sans-serif"};
    sk_typeface_t typefaces[2] = {};
    return check(SkParagraph_FontCollection_getFontManagersCount(nullptr) == 0, "count null") &&
           check(!SkParagraph_FontCollection_setAssetFontManager(nullptr, 0), "set asset null") &&
           check(!SkParagraph_FontCollection_setDynamicFontManager(nullptr, 0), "set dynamic null") &&
           check(!SkParagraph_FontCollection_setTestFontManager(nullptr, 0), "set test null") &&
           check(!SkParagraph_FontCollection_setDefaultFontManager(nullptr, 0), "set default null") &&
           check(!SkParagraph_FontCollection_setDefaultFontManagerWithFamilyName(nullptr, 0, nullptr), "set default family null") &&
           check(!SkParagraph_FontCollection_setDefaultFontManagerWithFamilyNames(nullptr, 0, families, 1), "set default families null") &&
           check(SkParagraph_FontCollection_getFallbackManager(nullptr) == 0, "fallback manager null") &&
           check(SkParagraph_FontCollection_findTypefaces(nullptr, families, 1, 0, typefaces, 2) == -1, "find typefaces null") &&
           check(SkParagraph_FontCollection_defaultFallback(nullptr) == 0, "default fallback null") &&
           check(SkParagraph_FontCollection_defaultFallbackForChar(nullptr, 'A', 0, nullptr) == 0, "default fallback char null") &&
           check(!SkParagraph_FontCollection_fontFallbackEnabled(nullptr), "fallback enabled null") &&
           check(SkParagraph_FontCollection_getParagraphCache(nullptr) == nullptr, "paragraph cache null") &&
           check(SkParagraph_ParagraphCache_count(nullptr) == 0, "cache count null");
}

bool smoke_collection() {
    reskia_paragraph_font_collection_t *collection = SkParagraph_FontCollection_new();
    if (!check(collection != nullptr, "FontCollection new")) {
        return false;
    }

    SkParagraph_FontCollection_ref(collection);
    SkParagraph_FontCollection_unref(collection);

    if (!check(SkParagraph_FontCollection_getFontManagersCount(collection) == 0, "initial manager count")) {
        SkParagraph_FontCollection_release(collection);
        return false;
    }

    sk_font_mgr_t font_mgr = SkFontMgr_RefDefault();
    if (font_mgr == 0) {
        font_mgr = SkFontMgr_RefEmpty();
    }
    if (!check(font_mgr != 0, "font manager handle")) {
        SkParagraph_FontCollection_release(collection);
        return false;
    }

    if (!check(SkParagraph_FontCollection_setDefaultFontManager(collection, font_mgr), "set default manager") ||
        !check(SkParagraph_FontCollection_getFontManagersCount(collection) >= 1, "manager count after default")) {
        static_sk_font_mgr_delete(font_mgr);
        SkParagraph_FontCollection_release(collection);
        return false;
    }

    const char *families[] = {"sans-serif"};
    if (!check(SkParagraph_FontCollection_setDefaultFontManagerWithFamilyName(collection, font_mgr, families[0]), "set default family name") ||
        !check(SkParagraph_FontCollection_setDefaultFontManagerWithFamilyNames(collection, font_mgr, families, 1), "set default family names") ||
        !check(SkParagraph_FontCollection_setAssetFontManager(collection, 0), "clear asset manager") ||
        !check(SkParagraph_FontCollection_setDynamicFontManager(collection, 0), "clear dynamic manager") ||
        !check(SkParagraph_FontCollection_setTestFontManager(collection, 0), "clear test manager")) {
        static_sk_font_mgr_delete(font_mgr);
        SkParagraph_FontCollection_release(collection);
        return false;
    }

    sk_font_mgr_t fallback_manager = SkParagraph_FontCollection_getFallbackManager(collection);
    if (!check(fallback_manager != 0, "get fallback manager")) {
        static_sk_font_mgr_delete(font_mgr);
        SkParagraph_FontCollection_release(collection);
        return false;
    }
    static_sk_font_mgr_delete(fallback_manager);

    sk_typeface_t typefaces[4] = {};
    int32_t typeface_count = SkParagraph_FontCollection_findTypefaces(collection, families, 1, 0, typefaces, 4);
    if (!check(typeface_count >= 0, "find typefaces")) {
        static_sk_font_mgr_delete(font_mgr);
        SkParagraph_FontCollection_release(collection);
        return false;
    }
    for (int32_t i = 0; i < typeface_count && i < 4; ++i) {
        if (typefaces[i] != 0) {
            static_sk_typeface_delete(typefaces[i]);
        }
    }

    sk_typeface_t fallback = SkParagraph_FontCollection_defaultFallback(collection);
    if (fallback != 0) {
        static_sk_typeface_delete(fallback);
    }
    fallback = SkParagraph_FontCollection_defaultFallbackForChar(collection, 'A', 0, "en");
    if (fallback != 0) {
        static_sk_typeface_delete(fallback);
    }

    SkParagraph_FontCollection_disableFontFallback(collection);
    if (!check(!SkParagraph_FontCollection_fontFallbackEnabled(collection), "fallback disabled")) {
        static_sk_font_mgr_delete(font_mgr);
        SkParagraph_FontCollection_release(collection);
        return false;
    }
    SkParagraph_FontCollection_enableFontFallback(collection);
    reskia_paragraph_cache_t *borrowed_cache = SkParagraph_FontCollection_getParagraphCache(collection);
    if (!check(SkParagraph_FontCollection_fontFallbackEnabled(collection), "fallback enabled") ||
        !check(borrowed_cache != nullptr, "get paragraph cache") ||
        !check(SkParagraph_ParagraphCache_count(borrowed_cache) == 0, "borrowed cache count")) {
        static_sk_font_mgr_delete(font_mgr);
        SkParagraph_FontCollection_release(collection);
        return false;
    }
    SkParagraph_ParagraphCache_turnOn(borrowed_cache, false);
    SkParagraph_ParagraphCache_turnOn(borrowed_cache, true);
    SkParagraph_ParagraphCache_reset(borrowed_cache);
    SkParagraph_FontCollection_clearCaches(collection);

    reskia_paragraph_cache_t *owned_cache = SkParagraph_ParagraphCache_new();
    if (!check(owned_cache != nullptr, "cache new") ||
        !check(SkParagraph_ParagraphCache_count(owned_cache) == 0, "owned cache count")) {
        SkParagraph_ParagraphCache_delete(owned_cache);
        static_sk_font_mgr_delete(font_mgr);
        SkParagraph_FontCollection_release(collection);
        return false;
    }
    SkParagraph_ParagraphCache_turnOn(owned_cache, true);
    SkParagraph_ParagraphCache_reset(owned_cache);
    SkParagraph_ParagraphCache_abandon(owned_cache);
    SkParagraph_ParagraphCache_delete(owned_cache);

    static_sk_font_mgr_delete(font_mgr);
    SkParagraph_FontCollection_release(collection);
    return true;
}

}  // namespace

int main() {
    return smoke_null_inputs() && smoke_collection() ? 0 : 1;
}
