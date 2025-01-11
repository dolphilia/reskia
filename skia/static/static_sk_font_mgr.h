//
// Created by dolphilia on 2024/01/05.
//

#ifndef RAIA_SKIA_STATIC_SK_FONT_MGR_H
#define RAIA_SKIA_STATIC_SK_FONT_MGR_H

#include <set>
#include <map>
#include "include/core/SkFontMgr.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_font_mgr_t;
void static_sk_font_mgr_delete(int key);
SkFontMgr *static_sk_font_mgr_get(int key);
#ifdef __cplusplus
}
#endif

int static_sk_font_mgr_make(sk_sp<SkFontMgr> value);
void static_sk_font_mgr_set(int key, sk_sp<SkFontMgr> value);
sk_sp<SkFontMgr> static_sk_font_mgr_move(int key);

#endif //RAIA_SKIA_STATIC_SK_FONT_MGR_H
