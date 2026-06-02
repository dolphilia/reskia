//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_FONT_MGR_H
#define RAIA_SKIA_SK_FONT_MGR_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "reskia_status.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_font_mgr.h"
#include "../handles/static_sk_font_style.h"
#include "../handles/static_sk_font_style_set.h"
#include "../handles/static_sk_stream_asset.h"
#include "../handles/static_sk_typeface.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_font_arguments_t reskia_font_arguments_t;
typedef struct reskia_font_mgr_t reskia_font_mgr_t;
typedef struct reskia_font_style_t reskia_font_style_t;
typedef struct reskia_string_t reskia_string_t;
typedef int32_t reskia_font_mgr_unichar_t;
typedef uint32_t reskia_font_mgr_four_byte_tag_t;

typedef struct reskia_font_mgr_cmap_entry_t {
    reskia_font_mgr_unichar_t character;
    reskia_font_mgr_unichar_t variation;
} reskia_font_mgr_cmap_entry_t;

typedef struct reskia_font_mgr_variation_coordinate_t {
    reskia_font_mgr_four_byte_tag_t axis;
    float value;
} reskia_font_mgr_variation_coordinate_t;

typedef struct reskia_font_mgr_request_t {
    const reskia_font_mgr_cmap_entry_t *cmap_entries;
    size_t cmap_entry_count;
    const char **bcp47;
    size_t bcp47_count;
    const char *family_name;
    const reskia_font_mgr_variation_coordinate_t *model;
    size_t model_count;
    bool has_synthetic_bold;
    bool synthetic_bold;
    bool has_synthetic_oblique;
    bool synthetic_oblique;
} reskia_font_mgr_request_t;

void SkFontMgr_release(reskia_font_mgr_t *font_mgr); // owned: caller が保持する参照を release する。NULL 入力では no-op
int SkFontMgr_countFamilies(reskia_font_mgr_t *font_mgr); // NULL 入力では 0
void SkFontMgr_getFamilyName(reskia_font_mgr_t *font_mgr, int index, reskia_string_t *familyName); // index 範囲内、familyName 非 NULL。invalid 入力では no-op
/**
 * index 範囲内、out_style_set 非 NULL。invalid 入力では out 0 + INVALID_ARGUMENT
 */
reskia_status_t SkFontMgr_createStyleSet(reskia_font_mgr_t *font_mgr, int index, sk_font_style_set_t *out_style_set);
/**
 * familyName は NULL 許可、out_style_set 非 NULL。生成不能では out 0 + NOT_FOUND
 */
reskia_status_t SkFontMgr_matchFamily(reskia_font_mgr_t *font_mgr, const char familyName[], sk_font_style_set_t *out_style_set);
/**
 * familyName は NULL 許可、font_style 非 NULL。invalid 入力や生成不能では 0
 */
sk_typeface_t SkFontMgr_matchFamilyStyle(reskia_font_mgr_t *font_mgr, const char familyName[], const reskia_font_style_t *font_style);
/**
 * bcp47Count > 0 では bcp47 非 NULL。invalid 入力や生成不能では 0
 */
sk_typeface_t SkFontMgr_matchFamilyStyleCharacter(reskia_font_mgr_t *font_mgr, const char familyName[], const reskia_font_style_t *font_style, const char *bcp47[], int bcp47Count, reskia_font_mgr_unichar_t character);
sk_typeface_t SkFontMgr_match(reskia_font_mgr_t *font_mgr, const reskia_font_mgr_request_t *request); // request 非 NULL。invalid 入力や生成不能では 0
sk_typeface_t SkFontMgr_fallback(reskia_font_mgr_t *font_mgr, const reskia_font_mgr_request_t *request); // request 非 NULL。invalid 入力や生成不能では 0
sk_typeface_t SkFontMgr_makeFromData(reskia_font_mgr_t *font_mgr, sk_data_t data, int ttcIndex); // data 非 0、ttcIndex >= 0。invalid 入力や生成不能では 0
sk_typeface_t SkFontMgr_makeFromStream(reskia_font_mgr_t *font_mgr, sk_stream_asset_t stream_asset, int ttcIndex); // stream_asset は consumed。ttcIndex >= 0。invalid 入力や生成不能では 0
/**
 * stream_asset は consumed、font_arguments 非 NULL。invalid 入力や生成不能では 0
 */
sk_typeface_t SkFontMgr_makeFromStreamWithArguments(reskia_font_mgr_t *font_mgr, sk_stream_asset_t stream_asset, const reskia_font_arguments_t *font_argments);
sk_typeface_t SkFontMgr_makeFromFile(reskia_font_mgr_t *font_mgr, const char path[], int ttcIndex); // path 非 NULL、ttcIndex >= 0。invalid 入力や生成不能では 0
/**
 * familyName は NULL 許可。invalid 入力や生成不能では 0
 */
sk_typeface_t SkFontMgr_legacyMakeTypeface(reskia_font_mgr_t *font_mgr, const char familyName[], sk_font_style_t style);
bool SkFontMgr_unique(reskia_font_mgr_t *font_mgr); // NULL 入力では false
void SkFontMgr_ref(reskia_font_mgr_t *font_mgr); // retained: 参照カウントを増やす。NULL 入力では no-op
void SkFontMgr_unref(reskia_font_mgr_t *font_mgr); // owned: 参照カウントを減らす。NULL 入力では no-op
// static
sk_font_mgr_t SkFontMgr_RefEmpty(); // 生成不能では 0

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_FONT_MGR_H
