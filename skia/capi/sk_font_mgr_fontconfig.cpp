//
// Created by dolphilia on 2024/01/31.
//

#include "sk_font_mgr_fontconfig.h"
#include "../handles/static_sk_font_mgr-internal.h"

#include <utility>

extern "C" {

sk_font_mgr_t CSkia_SkFontMgr_New_FontConfig(FcConfig *fc) {
    sk_sp<SkFontMgr> font_mgr = SkFontMgr_New_FontConfig(fc);
    if (!font_mgr) {
        return 0;
    }
    return static_sk_font_mgr_make(std::move(font_mgr));
}

}
