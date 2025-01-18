//
// Created by dolphilia on 2024/01/08.
//

#include "sk_font_mgr.h"

#include "include/core/SkFontMgr.h"

#include "../static/static_sk_font_mgr.h"
#include "../static/static_sk_font_style_set.h"
#include "../static/static_sk_typeface.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_stream_asset.h"
#include "../static/static_sk_font_style.h"

#include "../static/static_sk_font_mgr-internal.h"
#include "../static/static_sk_font_style-internal.h"
#include "../static/static_sk_font_style_set-internal.h"
#include "../static/static_sk_stream_asset-internal.h"
#include "../static/static_sk_typeface-internal.h"
#include "../static/static_sk_data-internal.h"

extern "C" {

void SkFontMgr_delete(void *font_mgr) {
    delete static_cast<SkFontMgr *>(font_mgr);
}

int SkFontMgr_countFamilies(void *font_mgr) {
    return static_cast<SkFontMgr *>(font_mgr)->countFamilies();
}

void SkFontMgr_getFamilyName(void *font_mgr, int index, void *familyName) {
    static_cast<SkFontMgr *>(font_mgr)->getFamilyName(index, static_cast<SkString *>(familyName));
}

void SkFontMgr_createStyleSet(int sk_font_style_set_out, void *font_mgr, int index) {
    static_sk_font_style_set_set(sk_font_style_set_out, static_cast<SkFontMgr *>(font_mgr)->createStyleSet(index));
}

void SkFontMgr_matchFamily(int sk_font_style_set_out, void *font_mgr, const char familyName[]) {
    static_sk_font_style_set_set(sk_font_style_set_out, static_cast<SkFontMgr *>(font_mgr)->matchFamily(familyName));
}

sk_typeface_t SkFontMgr_matchFamilyStyle(void *font_mgr, const char familyName[], const void *font_style) {
    return static_sk_typeface_make(static_cast<SkFontMgr *>(font_mgr)->matchFamilyStyle(familyName, * static_cast<const SkFontStyle *>(font_style)));
}

sk_typeface_t SkFontMgr_matchFamilyStyleCharacter(void *font_mgr, const char familyName[], const void *font_style, const char *bcp47[], int bcp47Count, int character) {
    return static_sk_typeface_make(static_cast<SkFontMgr *>(font_mgr)->matchFamilyStyleCharacter(familyName, * static_cast<const SkFontStyle *>(font_style), bcp47, bcp47Count, character));
}

sk_typeface_t SkFontMgr_makeFromData(void *font_mgr, sk_data_t data, int ttcIndex) {
    return static_sk_typeface_make(static_cast<SkFontMgr *>(font_mgr)->makeFromData(static_sk_data_move(data), ttcIndex));
}

sk_typeface_t SkFontMgr_makeFromStream(void *font_mgr, sk_stream_asset_t stream_asset, int ttcIndex) {
    return static_sk_typeface_make(static_cast<SkFontMgr *>(font_mgr)->makeFromStream(static_sk_stream_asset_move(stream_asset), ttcIndex));
}

sk_typeface_t SkFontMgr_makeFromStream_2(void *font_mgr, sk_stream_asset_t stream_asset, const void *font_argments) {
    return static_sk_typeface_make(static_cast<SkFontMgr *>(font_mgr)->makeFromStream(static_sk_stream_asset_move(stream_asset), * static_cast<const SkFontArguments *>(font_argments)));
}

sk_typeface_t SkFontMgr_makeFromFile(void *font_mgr, const char path[], int ttcIndex) {
    return static_sk_typeface_make(static_cast<SkFontMgr *>(font_mgr)->makeFromFile(path, ttcIndex));
}

sk_typeface_t SkFontMgr_legacyMakeTypeface(void *font_mgr, const char familyName[], sk_font_style_t style) {
    return static_sk_typeface_make(static_cast<SkFontMgr *>(font_mgr)->legacyMakeTypeface(familyName, static_sk_font_style_get(style)));
}

bool SkFontMgr_unique(void *font_mgr) {
    return static_cast<SkFontMgr *>(font_mgr)->unique();
}

void SkFontMgr_ref(void *font_mgr) {
    static_cast<SkFontMgr *>(font_mgr)->ref();
}

void SkFontMgr_unref(void *font_mgr) {
    static_cast<SkFontMgr *>(font_mgr)->unref();
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
