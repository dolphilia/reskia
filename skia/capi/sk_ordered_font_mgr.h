#ifndef RAIA_SKIA_SK_ORDERED_FONT_MGR_H
#define RAIA_SKIA_SK_ORDERED_FONT_MGR_H

#include "../handles/static_sk_font_mgr.h"

typedef struct reskia_font_mgr_t reskia_font_mgr_t;
typedef struct reskia_ordered_font_mgr_t reskia_ordered_font_mgr_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_ordered_font_mgr_t *SkOrderedFontMgr_new();
void SkOrderedFontMgr_delete(reskia_ordered_font_mgr_t *font_mgr);
reskia_font_mgr_t *SkOrderedFontMgr_asFontMgr(reskia_ordered_font_mgr_t *font_mgr); // borrowed
sk_font_mgr_t SkOrderedFontMgr_refAsFontMgr(reskia_ordered_font_mgr_t *font_mgr); // returned handle owns a ref; delete with static_sk_font_mgr_delete.
void SkOrderedFontMgr_append(reskia_ordered_font_mgr_t *font_mgr, sk_font_mgr_t child_font_mgr); // child handle is borrowed and retained.

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_ORDERED_FONT_MGR_H
