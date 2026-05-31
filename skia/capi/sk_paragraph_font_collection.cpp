//
// Created by Codex on 2026/05/15.
//

#include "sk_paragraph_font_collection.h"

#include "include/core/SkFontMgr.h"
#include "modules/skparagraph/include/FontCollection.h"
#include "modules/skparagraph/include/ParagraphCache.h"

#include "../handles/static_sk_font_mgr-internal.h"
#include "../handles/static_sk_font_style-internal.h"
#include "../handles/static_sk_typeface-internal.h"

#include <algorithm>
#include <optional>
#include <utility>
#include <vector>

namespace {

using skia::textlayout::FontCollection;
using skia::textlayout::ParagraphCache;

FontCollection *as_font_collection(reskia_paragraph_font_collection_t *collection) {
    return reinterpret_cast<FontCollection *>(collection);
}

sk_sp<SkFontMgr> borrow_font_mgr(sk_font_mgr_t font_mgr) {
    return font_mgr == 0 ? nullptr : static_sk_font_mgr_borrow_entity(font_mgr);
}

SkFontStyle font_style_or_normal(sk_font_style_t font_style) {
    if (font_style == 0) {
        return SkFontStyle();
    }
    return static_sk_font_style_get_entity(font_style);
}

std::vector<SkString> make_family_names(const char *family_names[], int32_t family_names_count) {
    std::vector<SkString> names;
    names.reserve(static_cast<size_t>(family_names_count));
    for (int32_t i = 0; i < family_names_count; ++i) {
        if (family_names[i] != nullptr) {
            names.emplace_back(family_names[i]);
        }
    }
    return names;
}

sk_font_mgr_t make_font_mgr_handle(sk_sp<SkFontMgr> font_mgr) {
    if (!font_mgr) {
        return 0;
    }
    return static_sk_font_mgr_make(std::move(font_mgr));
}

sk_typeface_t make_typeface_handle(sk_sp<SkTypeface> typeface) {
    if (!typeface) {
        return 0;
    }
    return static_sk_typeface_make(std::move(typeface));
}

}  // namespace

extern "C" {

reskia_paragraph_font_collection_t *SkParagraph_FontCollection_new(void) {
    auto collection = sk_make_sp<FontCollection>();
    return reinterpret_cast<reskia_paragraph_font_collection_t *>(collection.release());
}

reskia_paragraph_font_collection_t *FontCollection_new(void) {
    return SkParagraph_FontCollection_new();
}

void SkParagraph_FontCollection_release(reskia_paragraph_font_collection_t *collection) {
    if (collection == nullptr) {
        return;
    }
    as_font_collection(collection)->unref();
}

void SkParagraph_FontCollection_ref(reskia_paragraph_font_collection_t *collection) {
    if (collection == nullptr) {
        return;
    }
    as_font_collection(collection)->ref();
}

void SkParagraph_FontCollection_unref(reskia_paragraph_font_collection_t *collection) {
    if (collection == nullptr) {
        return;
    }
    as_font_collection(collection)->unref();
}

size_t SkParagraph_FontCollection_getFontManagersCount(reskia_paragraph_font_collection_t *collection) {
    if (collection == nullptr) {
        return 0;
    }
    return as_font_collection(collection)->getFontManagersCount();
}

bool SkParagraph_FontCollection_setAssetFontManager(reskia_paragraph_font_collection_t *collection, sk_font_mgr_t font_mgr) {
    if (collection == nullptr) {
        return false;
    }
    as_font_collection(collection)->setAssetFontManager(borrow_font_mgr(font_mgr));
    return true;
}

bool SkParagraph_FontCollection_setDynamicFontManager(reskia_paragraph_font_collection_t *collection, sk_font_mgr_t font_mgr) {
    if (collection == nullptr) {
        return false;
    }
    as_font_collection(collection)->setDynamicFontManager(borrow_font_mgr(font_mgr));
    return true;
}

bool SkParagraph_FontCollection_setTestFontManager(reskia_paragraph_font_collection_t *collection, sk_font_mgr_t font_mgr) {
    if (collection == nullptr) {
        return false;
    }
    as_font_collection(collection)->setTestFontManager(borrow_font_mgr(font_mgr));
    return true;
}

bool SkParagraph_FontCollection_setDefaultFontManager(reskia_paragraph_font_collection_t *collection, sk_font_mgr_t font_mgr) {
    if (collection == nullptr) {
        return false;
    }
    as_font_collection(collection)->setDefaultFontManager(borrow_font_mgr(font_mgr));
    return true;
}

bool SkParagraph_FontCollection_setDefaultFontManagerWithFamilyName(reskia_paragraph_font_collection_t *collection, sk_font_mgr_t font_mgr, const char *family_name) {
    if (collection == nullptr) {
        return false;
    }
    as_font_collection(collection)->setDefaultFontManager(borrow_font_mgr(font_mgr), family_name);
    return true;
}

bool SkParagraph_FontCollection_setDefaultFontManagerWithFamilyNames(reskia_paragraph_font_collection_t *collection, sk_font_mgr_t font_mgr, const char *family_names[], int32_t family_names_count) {
    if (collection == nullptr || family_names_count < 0 || (family_names_count > 0 && family_names == nullptr)) {
        return false;
    }
    auto names = make_family_names(family_names, family_names_count);
    as_font_collection(collection)->setDefaultFontManager(borrow_font_mgr(font_mgr), names);
    return true;
}

sk_font_mgr_t SkParagraph_FontCollection_getFallbackManager(reskia_paragraph_font_collection_t *collection) {
    if (collection == nullptr) {
        return 0;
    }
    return make_font_mgr_handle(as_font_collection(collection)->getFallbackManager());
}

int32_t SkParagraph_FontCollection_findTypefaces(reskia_paragraph_font_collection_t *collection, const char *family_names[], int32_t family_names_count, sk_font_style_t font_style, sk_typeface_t *dst, int32_t dst_count) {
    if (collection == nullptr || family_names_count < 0 || dst_count < 0 || (family_names_count > 0 && family_names == nullptr)) {
        return -1;
    }
    auto names = make_family_names(family_names, family_names_count);
    auto typefaces = as_font_collection(collection)->findTypefaces(names, font_style_or_normal(font_style));
    if (dst != nullptr && dst_count > 0) {
        const int32_t copy_count = std::min<int32_t>(dst_count, static_cast<int32_t>(typefaces.size()));
        for (int32_t i = 0; i < copy_count; ++i) {
            dst[i] = make_typeface_handle(typefaces[i]);
        }
    }
    return static_cast<int32_t>(typefaces.size());
}

sk_typeface_t SkParagraph_FontCollection_defaultFallback(reskia_paragraph_font_collection_t *collection) {
    if (collection == nullptr) {
        return 0;
    }
    return make_typeface_handle(as_font_collection(collection)->defaultFallback());
}

sk_typeface_t SkParagraph_FontCollection_defaultFallbackForChar(reskia_paragraph_font_collection_t *collection, int32_t unicode, sk_font_style_t font_style, const char *locale) {
    if (collection == nullptr) {
        return 0;
    }
    return make_typeface_handle(as_font_collection(collection)->defaultFallback(static_cast<SkUnichar>(unicode), font_style_or_normal(font_style), SkString(locale == nullptr ? "" : locale), std::nullopt));
}

sk_typeface_t SkParagraph_FontCollection_defaultEmojiFallback(reskia_paragraph_font_collection_t *collection, int32_t emoji_start, sk_font_style_t font_style, const char *locale) {
    if (collection == nullptr) {
        return 0;
    }
    return make_typeface_handle(as_font_collection(collection)->defaultEmojiFallback(static_cast<SkUnichar>(emoji_start), font_style_or_normal(font_style), SkString(locale == nullptr ? "" : locale)));
}

void SkParagraph_FontCollection_disableFontFallback(reskia_paragraph_font_collection_t *collection) {
    if (collection == nullptr) {
        return;
    }
    as_font_collection(collection)->disableFontFallback();
}

void SkParagraph_FontCollection_enableFontFallback(reskia_paragraph_font_collection_t *collection) {
    if (collection == nullptr) {
        return;
    }
    as_font_collection(collection)->enableFontFallback();
}

bool SkParagraph_FontCollection_fontFallbackEnabled(reskia_paragraph_font_collection_t *collection) {
    return collection != nullptr && as_font_collection(collection)->fontFallbackEnabled();
}

reskia_paragraph_cache_t *SkParagraph_FontCollection_getParagraphCache(reskia_paragraph_font_collection_t *collection) {
    if (collection == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_paragraph_cache_t *>(as_font_collection(collection)->getParagraphCache());
}

void SkParagraph_FontCollection_clearCaches(reskia_paragraph_font_collection_t *collection) {
    if (collection == nullptr) {
        return;
    }
    as_font_collection(collection)->clearCaches();
}

reskia_paragraph_cache_t *SkParagraph_ParagraphCache_new(void) {
    return reinterpret_cast<reskia_paragraph_cache_t *>(new ParagraphCache());
}

void SkParagraph_ParagraphCache_delete(reskia_paragraph_cache_t *cache) {
    delete reinterpret_cast<ParagraphCache *>(cache);
}

void SkParagraph_ParagraphCache_abandon(reskia_paragraph_cache_t *cache) {
    if (cache != nullptr) {
        reinterpret_cast<ParagraphCache *>(cache)->abandon();
    }
}

void SkParagraph_ParagraphCache_reset(reskia_paragraph_cache_t *cache) {
    if (cache != nullptr) {
        reinterpret_cast<ParagraphCache *>(cache)->reset();
    }
}

void SkParagraph_ParagraphCache_printStatistics(reskia_paragraph_cache_t *cache) {
    if (cache != nullptr) {
        reinterpret_cast<ParagraphCache *>(cache)->printStatistics();
    }
}

void SkParagraph_ParagraphCache_turnOn(reskia_paragraph_cache_t *cache, bool value) {
    if (cache != nullptr) {
        reinterpret_cast<ParagraphCache *>(cache)->turnOn(value);
    }
}

int SkParagraph_ParagraphCache_count(reskia_paragraph_cache_t *cache) {
    return cache == nullptr ? 0 : reinterpret_cast<ParagraphCache *>(cache)->count();
}

} // extern "C"
