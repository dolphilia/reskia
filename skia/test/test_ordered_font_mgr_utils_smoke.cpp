#include <cstdio>

#include "capi/sk_font_mgr.h"
#include "capi/sk_ordered_font_mgr.h"
#include "handles/static_sk_font_mgr.h"

namespace {

bool check(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "[ordered-font-mgr-utils-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    reskia_ordered_font_mgr_t *ordered = SkOrderedFontMgr_new();
    if (!check(ordered != nullptr, "SkOrderedFontMgr_new")) {
        return 1;
    }
    reskia_font_mgr_t *as_font_mgr = SkOrderedFontMgr_asFontMgr(ordered);
    if (!check(as_font_mgr != nullptr, "SkOrderedFontMgr_asFontMgr")) {
        SkOrderedFontMgr_delete(ordered);
        return 1;
    }
    if (!check(SkFontMgr_countFamilies(as_font_mgr) == 0, "empty ordered font mgr families")) {
        SkOrderedFontMgr_delete(ordered);
        return 1;
    }

    sk_font_mgr_t empty = SkFontMgr_RefEmpty();
    if (!check(empty != 0, "SkFontMgr_RefEmpty")) {
        SkOrderedFontMgr_delete(ordered);
        return 1;
    }
    SkOrderedFontMgr_append(ordered, empty);
    if (!check(SkFontMgr_countFamilies(as_font_mgr) == 0, "ordered font mgr appended empty families")) {
        static_sk_font_mgr_delete(empty);
        SkOrderedFontMgr_delete(ordered);
        return 1;
    }
    sk_font_mgr_t ordered_handle = SkOrderedFontMgr_refAsFontMgr(ordered);
    if (!check(ordered_handle != 0, "SkOrderedFontMgr_refAsFontMgr")) {
        static_sk_font_mgr_delete(empty);
        SkOrderedFontMgr_delete(ordered);
        return 1;
    }
    auto *ordered_from_handle = reinterpret_cast<reskia_font_mgr_t *>(static_sk_font_mgr_get_ptr(ordered_handle));
    if (!check(ordered_from_handle != nullptr && SkFontMgr_countFamilies(ordered_from_handle) == 0,
               "SkOrderedFontMgr_refAsFontMgr usable")) {
        static_sk_font_mgr_delete(ordered_handle);
        static_sk_font_mgr_delete(empty);
        SkOrderedFontMgr_delete(ordered);
        return 1;
    }
    static_sk_font_mgr_delete(ordered_handle);
    static_sk_font_mgr_delete(empty);
    SkOrderedFontMgr_delete(ordered);

    std::fprintf(stdout, "[ordered-font-mgr-utils-smoke] PASS\n");
    return 0;
}
