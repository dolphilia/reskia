//
// Created by Codex on 2026/05/16.
//

#ifndef RAIA_SKIA_SK_FONT_CONFIG_INTERFACE_H
#define RAIA_SKIA_SK_FONT_CONFIG_INTERFACE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "../handles/static_sk_font_mgr.h"
#include "../handles/static_sk_stream_asset.h"
#include "../handles/static_sk_typeface.h"
#include "sk_font_style.h"
#include "sk_string.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_font_config_identity_t reskia_font_config_identity_t;
typedef struct reskia_font_config_interface_t reskia_font_config_interface_t;

reskia_font_config_identity_t *SkFontConfigInterface_FontIdentity_new(void);
void SkFontConfigInterface_FontIdentity_delete(reskia_font_config_identity_t *identity);
uint32_t SkFontConfigInterface_FontIdentity_getID(const reskia_font_config_identity_t *identity);
void SkFontConfigInterface_FontIdentity_setID(reskia_font_config_identity_t *identity, uint32_t id);
int32_t SkFontConfigInterface_FontIdentity_getTTCIndex(const reskia_font_config_identity_t *identity);
void SkFontConfigInterface_FontIdentity_setTTCIndex(reskia_font_config_identity_t *identity, int32_t ttc_index);
reskia_string_t *SkFontConfigInterface_FontIdentity_getString(const reskia_font_config_identity_t *identity);
void SkFontConfigInterface_FontIdentity_setString(reskia_font_config_identity_t *identity, const char text[]);
reskia_font_style_t *SkFontConfigInterface_FontIdentity_getStyle(const reskia_font_config_identity_t *identity);
void SkFontConfigInterface_FontIdentity_setStyle(reskia_font_config_identity_t *identity, const reskia_font_style_t *style);
size_t SkFontConfigInterface_FontIdentity_writeToMemory(const reskia_font_config_identity_t *identity, void *buffer);
size_t SkFontConfigInterface_FontIdentity_readFromMemory(reskia_font_config_identity_t *identity, const void *buffer, size_t length);

reskia_font_config_interface_t *SkFontConfigInterface_RefGlobal(void);
void SkFontConfigInterface_SetGlobal(reskia_font_config_interface_t *interface_); // retains interface_; NULL clears global
reskia_font_config_interface_t *SkFontConfigInterface_GetSingletonDirectInterface(void); // borrowed singleton
void SkFontConfigInterface_ref(reskia_font_config_interface_t *interface_);
void SkFontConfigInterface_unref(reskia_font_config_interface_t *interface_);

bool SkFontConfigInterface_matchFamilyName(reskia_font_config_interface_t *interface_, const char family_name[], const reskia_font_style_t *requested, reskia_font_config_identity_t *out_font_identifier, reskia_string_t *out_family_name, reskia_font_style_t **out_style);
sk_stream_asset_t SkFontConfigInterface_openStream(reskia_font_config_interface_t *interface_, const reskia_font_config_identity_t *identity);
sk_typeface_t SkFontConfigInterface_makeTypeface(reskia_font_config_interface_t *interface_, const reskia_font_config_identity_t *identity);
sk_typeface_t SkFontConfigInterface_makeTypefaceWithFontMgr(reskia_font_config_interface_t *interface_, const reskia_font_config_identity_t *identity, sk_font_mgr_t font_mgr);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_FONT_CONFIG_INTERFACE_H
