//
// Created by Codex on 2026/05/15.
//

#ifndef RAIA_SKIA_SK_PARAGRAPH_TYPEFACE_FONT_PROVIDER_H
#define RAIA_SKIA_SK_PARAGRAPH_TYPEFACE_FONT_PROVIDER_H

#include <stddef.h>
#include <stdint.h>

#include "../handles/static_sk_font_mgr.h"
#include "../handles/static_sk_font_style.h"
#include "../handles/static_sk_font_style_set.h"
#include "../handles/static_sk_typeface.h"

typedef struct reskia_font_arguments_t reskia_font_arguments_t;
typedef struct reskia_paragraph_typeface_font_provider_t reskia_paragraph_typeface_font_provider_t;
typedef struct reskia_string_t reskia_string_t;
typedef int32_t reskia_font_mgr_unichar_t;
typedef int sk_data_t;
typedef int sk_stream_asset_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_paragraph_typeface_font_provider_t *SkParagraph_TypefaceFontProvider_new(void);
void SkParagraph_TypefaceFontProvider_release(reskia_paragraph_typeface_font_provider_t *provider);
void SkParagraph_TypefaceFontProvider_ref(reskia_paragraph_typeface_font_provider_t *provider);
void SkParagraph_TypefaceFontProvider_unref(reskia_paragraph_typeface_font_provider_t *provider);
sk_font_mgr_t SkParagraph_TypefaceFontProvider_refFontMgr(reskia_paragraph_typeface_font_provider_t *provider);
size_t SkParagraph_TypefaceFontProvider_registerTypeface(reskia_paragraph_typeface_font_provider_t *provider, sk_typeface_t typeface);
size_t SkParagraph_TypefaceFontProvider_registerTypefaceWithAlias(reskia_paragraph_typeface_font_provider_t *provider, sk_typeface_t typeface, const char *alias);
int SkParagraph_TypefaceFontProvider_onCountFamilies(const reskia_paragraph_typeface_font_provider_t *provider);
reskia_string_t *SkParagraph_TypefaceFontProvider_onGetFamilyName(const reskia_paragraph_typeface_font_provider_t *provider, int index);
sk_font_style_set_t SkParagraph_TypefaceFontProvider_onMatchFamily(const reskia_paragraph_typeface_font_provider_t *provider, const char *family_name);
sk_font_style_set_t SkParagraph_TypefaceFontProvider_onCreateStyleSet(const reskia_paragraph_typeface_font_provider_t *provider, int index);
sk_typeface_t SkParagraph_TypefaceFontProvider_onMatchFamilyStyle(const reskia_paragraph_typeface_font_provider_t *provider, const char *family_name, sk_font_style_t style);
sk_typeface_t SkParagraph_TypefaceFontProvider_onMatchFamilyStyleCharacter(const reskia_paragraph_typeface_font_provider_t *provider, const char *family_name, sk_font_style_t style, const char *bcp47[], int bcp47_count, reskia_font_mgr_unichar_t character);
sk_typeface_t SkParagraph_TypefaceFontProvider_onMakeFromData(const reskia_paragraph_typeface_font_provider_t *provider, sk_data_t data, int ttc_index);
sk_typeface_t SkParagraph_TypefaceFontProvider_onMakeFromStreamIndex(const reskia_paragraph_typeface_font_provider_t *provider, sk_stream_asset_t stream_asset, int ttc_index);
sk_typeface_t SkParagraph_TypefaceFontProvider_onMakeFromStreamArgs(const reskia_paragraph_typeface_font_provider_t *provider, sk_stream_asset_t stream_asset, const reskia_font_arguments_t *arguments);
sk_typeface_t SkParagraph_TypefaceFontProvider_onMakeFromFile(const reskia_paragraph_typeface_font_provider_t *provider, const char *path, int ttc_index);
sk_typeface_t SkParagraph_TypefaceFontProvider_onLegacyMakeTypeface(const reskia_paragraph_typeface_font_provider_t *provider, const char *family_name, sk_font_style_t style);

reskia_string_t *SkParagraph_TypefaceFontStyleSet_getFamilyName(sk_font_style_set_t style_set);
reskia_string_t *SkParagraph_TypefaceFontStyleSet_getAlias(sk_font_style_set_t style_set);
bool SkParagraph_TypefaceFontStyleSet_appendTypeface(sk_font_style_set_t style_set, sk_typeface_t typeface);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_PARAGRAPH_TYPEFACE_FONT_PROVIDER_H
