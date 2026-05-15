#include "sk_ordered_font_mgr.h"

#include "include/core/SkFontMgr.h"
#include "include/utils/SkOrderedFontMgr.h"

#include "../handles/static_sk_font_mgr-internal.h"

extern "C" {

reskia_ordered_font_mgr_t *SkOrderedFontMgr_new() {
    return reinterpret_cast<reskia_ordered_font_mgr_t *>(new SkOrderedFontMgr());
}

void SkOrderedFontMgr_delete(reskia_ordered_font_mgr_t *font_mgr) {
    delete reinterpret_cast<SkOrderedFontMgr *>(font_mgr);
}

reskia_font_mgr_t *SkOrderedFontMgr_asFontMgr(reskia_ordered_font_mgr_t *font_mgr) {
    return reinterpret_cast<reskia_font_mgr_t *>(font_mgr);
}

sk_font_mgr_t SkOrderedFontMgr_refAsFontMgr(reskia_ordered_font_mgr_t *font_mgr) {
    if (font_mgr == nullptr) {
        return 0;
    }
    return static_sk_font_mgr_make(sk_ref_sp(reinterpret_cast<SkOrderedFontMgr *>(font_mgr)));
}

void SkOrderedFontMgr_append(reskia_ordered_font_mgr_t *font_mgr, sk_font_mgr_t child_font_mgr) {
    if (font_mgr == nullptr || child_font_mgr == 0) {
        return;
    }
    sk_sp<SkFontMgr> child = static_sk_font_mgr_get_entity(child_font_mgr);
    if (!child) {
        return;
    }
    reinterpret_cast<SkOrderedFontMgr *>(font_mgr)->append(std::move(child));
}

} // extern "C"
