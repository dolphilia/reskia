//
// Created by Codex on 2026/05/16.
//

#ifndef RAIA_SKIA_SK_REMOTABLE_FONT_MGR_H
#define RAIA_SKIA_SK_REMOTABLE_FONT_MGR_H

#include <stdbool.h>
#include <stdint.h>

#include "../handles/static_sk_font_mgr.h"
#include "../handles/static_sk_stream_asset.h"
#include "sk_font_style.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_remotable_font_identity_set_t reskia_remotable_font_identity_set_t;
typedef struct reskia_remotable_font_mgr_t reskia_remotable_font_mgr_t;

typedef struct reskia_font_identity_t {
    uint32_t data_id;
    uint32_t ttc_index;
    int font_style_weight;
    int font_style_width;
    reskia_font_style_slant_t font_style_slant;
} reskia_font_identity_t;

uint32_t SkFontIdentity_InvalidDataId(void);

reskia_remotable_font_identity_set_t *SkRemotableFontIdentitySet_new(const reskia_font_identity_t identities[], int count);
void SkRemotableFontIdentitySet_unref(reskia_remotable_font_identity_set_t *set);
int SkRemotableFontIdentitySet_count(const reskia_remotable_font_identity_set_t *set);
bool SkRemotableFontIdentitySet_at(const reskia_remotable_font_identity_set_t *set, int index, reskia_font_identity_t *out_identity);
reskia_remotable_font_identity_set_t *SkRemotableFontIdentitySet_NewEmpty(void);

void SkRemotableFontMgr_ref(reskia_remotable_font_mgr_t *mgr);
void SkRemotableFontMgr_unref(reskia_remotable_font_mgr_t *mgr);
reskia_remotable_font_identity_set_t *SkRemotableFontMgr_getIndex(const reskia_remotable_font_mgr_t *mgr, int familyIndex);
bool SkRemotableFontMgr_matchIndexStyle(const reskia_remotable_font_mgr_t *mgr, int familyIndex, const reskia_font_style_t *style, reskia_font_identity_t *out_identity);
reskia_remotable_font_identity_set_t *SkRemotableFontMgr_matchName(const reskia_remotable_font_mgr_t *mgr, const char familyName[]);
bool SkRemotableFontMgr_matchNameStyle(const reskia_remotable_font_mgr_t *mgr, const char familyName[], const reskia_font_style_t *style, reskia_font_identity_t *out_identity);
bool SkRemotableFontMgr_matchNameStyleCharacter(const reskia_remotable_font_mgr_t *mgr, const char familyName[], const reskia_font_style_t *style, const char *bcp47[], int bcp47Count, int32_t character, reskia_font_identity_t *out_identity);
sk_stream_asset_t SkRemotableFontMgr_getData(const reskia_remotable_font_mgr_t *mgr, int dataId);

sk_font_mgr_t SkFontMgr_Indirect_new(sk_font_mgr_t impl, reskia_remotable_font_mgr_t *proxy);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_REMOTABLE_FONT_MGR_H
