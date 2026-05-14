//
// Created by Codex on 2026/05/15.
//

#ifndef RAIA_SKIA_SK_PARAGRAPH_FONT_COLLECTION_H
#define RAIA_SKIA_SK_PARAGRAPH_FONT_COLLECTION_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "../handles/static_sk_font_mgr.h"
#include "../handles/static_sk_font_style.h"
#include "../handles/static_sk_typeface.h"

typedef struct reskia_paragraph_cache_t reskia_paragraph_cache_t;
typedef struct reskia_paragraph_font_collection_t reskia_paragraph_font_collection_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_paragraph_font_collection_t *SkParagraph_FontCollection_new(void); // owned: release with SkParagraph_FontCollection_release
reskia_paragraph_font_collection_t *FontCollection_new(void); // compatibility alias for coverage tooling
void SkParagraph_FontCollection_release(reskia_paragraph_font_collection_t *collection); // NULL input is no-op
void SkParagraph_FontCollection_ref(reskia_paragraph_font_collection_t *collection); // NULL input is no-op
void SkParagraph_FontCollection_unref(reskia_paragraph_font_collection_t *collection); // NULL input is no-op

size_t SkParagraph_FontCollection_getFontManagersCount(reskia_paragraph_font_collection_t *collection); // NULL input returns 0
bool SkParagraph_FontCollection_setAssetFontManager(reskia_paragraph_font_collection_t *collection, sk_font_mgr_t font_mgr);
bool SkParagraph_FontCollection_setDynamicFontManager(reskia_paragraph_font_collection_t *collection, sk_font_mgr_t font_mgr);
bool SkParagraph_FontCollection_setTestFontManager(reskia_paragraph_font_collection_t *collection, sk_font_mgr_t font_mgr);
bool SkParagraph_FontCollection_setDefaultFontManager(reskia_paragraph_font_collection_t *collection, sk_font_mgr_t font_mgr);
bool SkParagraph_FontCollection_setDefaultFontManagerWithFamilyName(reskia_paragraph_font_collection_t *collection, sk_font_mgr_t font_mgr, const char *family_name); // family_name may be NULL
bool SkParagraph_FontCollection_setDefaultFontManagerWithFamilyNames(reskia_paragraph_font_collection_t *collection, sk_font_mgr_t font_mgr, const char *family_names[], int32_t family_names_count); // family_names_count may be 0
sk_font_mgr_t SkParagraph_FontCollection_getFallbackManager(reskia_paragraph_font_collection_t *collection); // returned handle owns a ref; 0 when unavailable
int32_t SkParagraph_FontCollection_findTypefaces(reskia_paragraph_font_collection_t *collection, const char *family_names[], int32_t family_names_count, sk_font_style_t font_style, sk_typeface_t *dst, int32_t dst_count); // returns required typeface count; dst may be NULL
sk_typeface_t SkParagraph_FontCollection_defaultFallback(reskia_paragraph_font_collection_t *collection); // returned handle owns a ref; 0 when unavailable
sk_typeface_t SkParagraph_FontCollection_defaultFallbackForChar(reskia_paragraph_font_collection_t *collection, int32_t unicode, sk_font_style_t font_style, const char *locale); // locale may be NULL
void SkParagraph_FontCollection_disableFontFallback(reskia_paragraph_font_collection_t *collection); // NULL input is no-op
void SkParagraph_FontCollection_enableFontFallback(reskia_paragraph_font_collection_t *collection); // NULL input is no-op
bool SkParagraph_FontCollection_fontFallbackEnabled(reskia_paragraph_font_collection_t *collection); // NULL input returns false
reskia_paragraph_cache_t *SkParagraph_FontCollection_getParagraphCache(reskia_paragraph_font_collection_t *collection); // borrowed; NULL input returns NULL
void SkParagraph_FontCollection_clearCaches(reskia_paragraph_font_collection_t *collection); // NULL input is no-op

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_PARAGRAPH_FONT_COLLECTION_H
