//
// Created by dolphilia on 2024/01/31.
//

#ifndef RAIA_SKIA_SK_FONT_MGR_FONTCONFIG_H
#define RAIA_SKIA_SK_FONT_MGR_FONTCONFIG_H

#include "include/core/SkFontMgr.h"
#include "include/ports/SkFontMgr_fontconfig.h"
#include "../handles/static_sk_font_mgr.h"

extern "C" {
sk_font_mgr_t CSkia_SkFontMgr_New_FontConfig(FcConfig *fc);
}

#endif //RAIA_SKIA_SK_FONT_MGR_FONTCONFIG_H
