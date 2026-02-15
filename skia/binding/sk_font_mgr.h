//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_FONT_MGR_H
#define RAIA_SKIA_SK_FONT_MGR_H

#include "../static/static_sk_data.h"
#include "../static/static_sk_font_mgr.h"
#include "../static/static_sk_font_style.h"
#include "../static/static_sk_stream_asset.h"
#include "../static/static_sk_typeface.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_font_arguments_t reskia_font_arguments_t;
typedef struct reskia_font_mgr_t reskia_font_mgr_t;
typedef struct reskia_font_style_t reskia_font_style_t;
typedef struct reskia_string_t reskia_string_t;

void SkFontMgr_delete(reskia_font_mgr_t *font_mgr); // owned: caller が保持する参照を release する (SkFontMgr *font_mgr)
int SkFontMgr_countFamilies(reskia_font_mgr_t *font_mgr); // (SkFontMgr *font_mgr) -> int
void SkFontMgr_getFamilyName(reskia_font_mgr_t *font_mgr, int index, reskia_string_t *familyName); // (SkFontMgr *font_mgr, int index, SkString *familyName)
void SkFontMgr_createStyleSet(int sk_font_style_set_out, reskia_font_mgr_t *font_mgr, int index); // (int sk_font_style_set_out, SkFontMgr *font_mgr, int index)
void SkFontMgr_matchFamily(int sk_font_style_set_out, reskia_font_mgr_t *font_mgr, const char familyName[]); // (int sk_font_style_set_out, SkFontMgr *font_mgr, const char familyName[])
sk_typeface_t SkFontMgr_matchFamilyStyle(reskia_font_mgr_t *font_mgr, const char familyName[], const reskia_font_style_t *font_style); // (SkFontMgr *font_mgr, const char familyName[], const SkFontStyle *font_style) -> sk_typeface_t
sk_typeface_t SkFontMgr_matchFamilyStyleCharacter(reskia_font_mgr_t *font_mgr, const char familyName[], const reskia_font_style_t *font_style, const char *bcp47[], int bcp47Count, int character); // (SkFontMgr *font_mgr, const char familyName[], const SkFontStyle *font_style, const char *bcp47[], int bcp47Count, SkUnichar character) -> sk_typeface_t
sk_typeface_t SkFontMgr_makeFromData(reskia_font_mgr_t *font_mgr, sk_data_t data, int ttcIndex); // (SkFontMgr *font_mgr, sk_data_t data, int ttcIndex) -> sk_typeface_t
sk_typeface_t SkFontMgr_makeFromStream(reskia_font_mgr_t *font_mgr, sk_stream_asset_t stream_asset, int ttcIndex); // (SkFontMgr *font_mgr, sk_stream_asset_t stream_asset, int ttcIndex) -> sk_typeface_t
sk_typeface_t SkFontMgr_makeFromStream_2(reskia_font_mgr_t *font_mgr, sk_stream_asset_t stream_asset, const reskia_font_arguments_t *font_argments); // (SkFontMgr *font_mgr, sk_stream_asset_t stream_asset, const SkFontArguments *font_argments) -> sk_typeface_t
sk_typeface_t SkFontMgr_makeFromFile(reskia_font_mgr_t *font_mgr, const char path[], int ttcIndex); // (SkFontMgr *font_mgr, const char path[], int ttcIndex) -> sk_typeface_t
sk_typeface_t SkFontMgr_legacyMakeTypeface(reskia_font_mgr_t *font_mgr, const char familyName[], sk_font_style_t style); // (SkFontMgr *font_mgr, const char familyName[], sk_font_style_t style) -> sk_typeface_t
bool SkFontMgr_unique(reskia_font_mgr_t *font_mgr); // (SkFontMgr *font_mgr) -> bool
void SkFontMgr_ref(reskia_font_mgr_t *font_mgr); // retained: 参照カウントを増やす (SkFontMgr *font_mgr)
void SkFontMgr_unref(reskia_font_mgr_t *font_mgr); // owned: 参照カウントを減らす (SkFontMgr *font_mgr)
// static
sk_font_mgr_t SkFontMgr_RefEmpty(); // () -> sk_font_mgr_t
#if !defined(SK_DISABLE_LEGACY_FONTMGR_REFDEFAULT)
sk_font_mgr_t SkFontMgr_RefDefault(); // () -> sk_font_mgr_t
#endif

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_FONT_MGR_H
