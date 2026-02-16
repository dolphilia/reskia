//
// Created by dolphilia on 2024/01/08.
//

#include "sk_font_mgr.h"

#include <utility>

#include "include/core/SkFontMgr.h"

#include "../handles/static_sk_font_mgr.h"
#include "../handles/static_sk_font_style_set.h"
#include "../handles/static_sk_typeface.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_stream_asset.h"
#include "../handles/static_sk_font_style.h"

#include "../handles/static_sk_font_mgr-internal.h"
#include "../handles/static_sk_font_style-internal.h"
#include "../handles/static_sk_font_style_set-internal.h"
#include "../handles/static_sk_stream_asset-internal.h"
#include "../handles/static_sk_typeface-internal.h"
#include "../handles/static_sk_data-internal.h"

extern "C" {

void SkFontMgr_release(reskia_font_mgr_t *font_mgr) {
    reinterpret_cast<SkFontMgr *>(font_mgr)->unref();
}

int SkFontMgr_countFamilies(reskia_font_mgr_t *font_mgr) {
    return reinterpret_cast<SkFontMgr *>(font_mgr)->countFamilies();
}

void SkFontMgr_getFamilyName(reskia_font_mgr_t *font_mgr, int index, reskia_string_t *familyName) {
    reinterpret_cast<SkFontMgr *>(font_mgr)->getFamilyName(index, reinterpret_cast<SkString *>(familyName));
}

reskia_status_t SkFontMgr_createStyleSet(reskia_font_mgr_t *font_mgr, int index, sk_font_style_set_t *out_style_set) {
    if (font_mgr == nullptr || out_style_set == nullptr) {
        return RESKIA_STATUS_INVALID_ARGUMENT;
    }
    sk_sp<SkFontStyleSet> style_set = reinterpret_cast<SkFontMgr *>(font_mgr)->createStyleSet(index);
    if (style_set == nullptr) {
        *out_style_set = 0;
        return RESKIA_STATUS_NOT_FOUND;
    }
    *out_style_set = static_sk_font_style_set_make(std::move(style_set));
    return RESKIA_STATUS_OK;
}

reskia_status_t SkFontMgr_matchFamily(reskia_font_mgr_t *font_mgr, const char familyName[], sk_font_style_set_t *out_style_set) {
    if (font_mgr == nullptr || out_style_set == nullptr) {
        return RESKIA_STATUS_INVALID_ARGUMENT;
    }
    sk_sp<SkFontStyleSet> style_set = reinterpret_cast<SkFontMgr *>(font_mgr)->matchFamily(familyName);
    if (style_set == nullptr) {
        *out_style_set = 0;
        return RESKIA_STATUS_NOT_FOUND;
    }
    *out_style_set = static_sk_font_style_set_make(std::move(style_set));
    return RESKIA_STATUS_OK;
}

sk_typeface_t SkFontMgr_matchFamilyStyle(reskia_font_mgr_t *font_mgr, const char familyName[], const reskia_font_style_t *font_style) {
    return static_sk_typeface_make(reinterpret_cast<SkFontMgr *>(font_mgr)->matchFamilyStyle(familyName, * reinterpret_cast<const SkFontStyle *>(font_style)));
}

sk_typeface_t SkFontMgr_matchFamilyStyleCharacter(reskia_font_mgr_t *font_mgr, const char familyName[], const reskia_font_style_t *font_style, const char *bcp47[], int bcp47Count, reskia_font_mgr_unichar_t character) {
    return static_sk_typeface_make(reinterpret_cast<SkFontMgr *>(font_mgr)->matchFamilyStyleCharacter(familyName, * reinterpret_cast<const SkFontStyle *>(font_style), bcp47, bcp47Count, static_cast<SkUnichar>(character)));
}

sk_typeface_t SkFontMgr_makeFromData(reskia_font_mgr_t *font_mgr, sk_data_t data, int ttcIndex) {
    return static_sk_typeface_make(reinterpret_cast<SkFontMgr *>(font_mgr)->makeFromData(static_sk_data_get_entity(data), ttcIndex));
}

sk_typeface_t SkFontMgr_makeFromStream(reskia_font_mgr_t *font_mgr, sk_stream_asset_t stream_asset, int ttcIndex) {
    return static_sk_typeface_make(reinterpret_cast<SkFontMgr *>(font_mgr)->makeFromStream(static_sk_stream_asset_take_entity(stream_asset), ttcIndex));
}

sk_typeface_t SkFontMgr_makeFromStream_2(reskia_font_mgr_t *font_mgr, sk_stream_asset_t stream_asset, const reskia_font_arguments_t *font_argments) {
    return static_sk_typeface_make(reinterpret_cast<SkFontMgr *>(font_mgr)->makeFromStream(static_sk_stream_asset_take_entity(stream_asset), * reinterpret_cast<const SkFontArguments *>(font_argments)));
}

sk_typeface_t SkFontMgr_makeFromFile(reskia_font_mgr_t *font_mgr, const char path[], int ttcIndex) {
    return static_sk_typeface_make(reinterpret_cast<SkFontMgr *>(font_mgr)->makeFromFile(path, ttcIndex));
}

sk_typeface_t SkFontMgr_legacyMakeTypeface(reskia_font_mgr_t *font_mgr, const char familyName[], sk_font_style_t style) {
    return static_sk_typeface_make(reinterpret_cast<SkFontMgr *>(font_mgr)->legacyMakeTypeface(familyName, static_sk_font_style_get_entity(style)));
}

bool SkFontMgr_unique(reskia_font_mgr_t *font_mgr) {
    return reinterpret_cast<SkFontMgr *>(font_mgr)->unique();
}

void SkFontMgr_ref(reskia_font_mgr_t *font_mgr) {
    reinterpret_cast<SkFontMgr *>(font_mgr)->ref();
}

void SkFontMgr_unref(reskia_font_mgr_t *font_mgr) {
    reinterpret_cast<SkFontMgr *>(font_mgr)->unref();
}

// static

sk_font_mgr_t SkFontMgr_RefEmpty() {
    return static_sk_font_mgr_make(SkFontMgr::RefEmpty());
}

#if !defined(SK_DISABLE_LEGACY_FONTMGR_REFDEFAULT)
sk_font_mgr_t SkFontMgr_RefDefault() {
    return static_sk_font_mgr_make(SkFontMgr::RefDefault());
}
#endif

}
