#include "capi/sk_font_mgr.h"
#include "capi/sk_font_style.h"
#include "capi/sk_remotable_font_mgr.h"

#include <cstdint>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        (void)message;
        return false;
    }
    return true;
}

}  // namespace

int main() {
    reskia_font_identity_t identity{
            7,
            2,
            400,
            5,
            0,
    };
    reskia_remotable_font_identity_set_t *set =
            SkRemotableFontIdentitySet_new(&identity, 1);
    if (!check(set != nullptr, "SkRemotableFontIdentitySet_new")) {
        return 1;
    }
    if (!check(SkRemotableFontIdentitySet_count(set) == 1, "SkRemotableFontIdentitySet_count")) {
        SkRemotableFontIdentitySet_unref(set);
        return 1;
    }

    reskia_font_identity_t round_trip{};
    if (!check(SkRemotableFontIdentitySet_at(set, 0, &round_trip), "SkRemotableFontIdentitySet_at")) {
        SkRemotableFontIdentitySet_unref(set);
        return 1;
    }
    if (!check(round_trip.data_id == 7 && round_trip.ttc_index == 2 &&
               round_trip.font_style_weight == 400 && round_trip.font_style_width == 5 &&
               round_trip.font_style_slant == 0,
               "SkRemotableFontIdentitySet_at round trip")) {
        SkRemotableFontIdentitySet_unref(set);
        return 1;
    }
    if (!check(!SkRemotableFontIdentitySet_at(set, -1, &round_trip), "SkRemotableFontIdentitySet_at negative")) {
        SkRemotableFontIdentitySet_unref(set);
        return 1;
    }
    SkRemotableFontIdentitySet_unref(set);

    reskia_remotable_font_identity_set_t *empty = SkRemotableFontIdentitySet_NewEmpty();
    if (!check(empty != nullptr, "SkRemotableFontIdentitySet_NewEmpty")) {
        return 1;
    }
    if (!check(SkRemotableFontIdentitySet_count(empty) == 0, "SkRemotableFontIdentitySet_NewEmpty count")) {
        SkRemotableFontIdentitySet_unref(empty);
        return 1;
    }
    SkRemotableFontIdentitySet_unref(empty);

    reskia_font_style_t *normal = SkFontStyle_Normal();
    if (!check(normal != nullptr, "SkFontStyle_Normal")) {
        return 1;
    }
    if (!check(!SkRemotableFontMgr_matchIndexStyle(nullptr, 0, normal, &round_trip),
               "SkRemotableFontMgr_matchIndexStyle null")) {
        SkFontStyle_delete(normal);
        return 1;
    }
    SkFontStyle_delete(normal);

    if (!check(SkRemotableFontMgr_getIndex(nullptr, 0) == nullptr, "SkRemotableFontMgr_getIndex null")) {
        return 1;
    }
    if (!check(SkRemotableFontMgr_matchName(nullptr, nullptr) == nullptr, "SkRemotableFontMgr_matchName null")) {
        return 1;
    }
    if (!check(SkRemotableFontMgr_getData(nullptr, 0) == 0, "SkRemotableFontMgr_getData null")) {
        return 1;
    }
    if (!check(SkFontMgr_Indirect_new(0, nullptr) == 0, "SkFontMgr_Indirect_new null")) {
        return 1;
    }
    if (!check(SkFontIdentity_InvalidDataId() == UINT32_C(0xFFFFFFFF), "SkFontIdentity_InvalidDataId")) {
        return 1;
    }
    return 0;
}
