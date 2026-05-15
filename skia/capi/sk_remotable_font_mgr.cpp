//
// Created by Codex on 2026/05/16.
//

#include "sk_remotable_font_mgr.h"

#include <memory>
#include <utility>

#include "include/core/SkFontMgr.h"
#include "include/core/SkFontStyle.h"
#include "include/core/SkStream.h"
#include "include/ports/SkFontMgr_indirect.h"
#include "include/ports/SkRemotableFontMgr.h"

#include "../handles/static_sk_font_mgr-internal.h"
#include "../handles/static_sk_stream_asset-internal.h"

namespace {

SkFontIdentity to_sk_font_identity(const reskia_font_identity_t& identity) {
    return SkFontIdentity{
            identity.data_id,
            identity.ttc_index,
            SkFontStyle(identity.font_style_weight,
                        identity.font_style_width,
                        static_cast<SkFontStyle::Slant>(identity.font_style_slant))
    };
}

reskia_font_identity_t from_sk_font_identity(const SkFontIdentity& identity) {
    return reskia_font_identity_t{
            identity.fDataId,
            identity.fTtcIndex,
            identity.fFontStyle.weight(),
            identity.fFontStyle.width(),
            static_cast<reskia_font_style_slant_t>(identity.fFontStyle.slant())
    };
}

SkFontStyle to_sk_font_style(const reskia_font_style_t *style) {
    return *reinterpret_cast<const SkFontStyle *>(style);
}

SkRemotableFontIdentitySet *as_identity_set(const reskia_remotable_font_identity_set_t *set) {
    return const_cast<SkRemotableFontIdentitySet *>(
            reinterpret_cast<const SkRemotableFontIdentitySet *>(set));
}

SkRemotableFontMgr *as_remotable_font_mgr(const reskia_remotable_font_mgr_t *mgr) {
    return const_cast<SkRemotableFontMgr *>(
            reinterpret_cast<const SkRemotableFontMgr *>(mgr));
}

reskia_remotable_font_identity_set_t *to_identity_set(SkRemotableFontIdentitySet *set) {
    return reinterpret_cast<reskia_remotable_font_identity_set_t *>(set);
}

sk_font_mgr_t to_font_mgr_handle(sk_sp<SkFontMgr> mgr) {
    if (!mgr) {
        return 0;
    }
    return static_sk_font_mgr_make(std::move(mgr));
}

}  // namespace

extern "C" {

uint32_t SkFontIdentity_InvalidDataId(void) {
    return SkFontIdentity::kInvalidDataId;
}

reskia_remotable_font_identity_set_t *SkRemotableFontIdentitySet_new(const reskia_font_identity_t identities[], int count) {
    if (count < 0 || (count > 0 && identities == nullptr)) {
        return nullptr;
    }
    SkFontIdentity *data = nullptr;
    auto *set = new SkRemotableFontIdentitySet(count, &data);
    for (int i = 0; i < count; ++i) {
        data[i] = to_sk_font_identity(identities[i]);
    }
    return to_identity_set(set);
}

void SkRemotableFontIdentitySet_unref(reskia_remotable_font_identity_set_t *set) {
    if (set == nullptr) {
        return;
    }
    as_identity_set(set)->unref();
}

int SkRemotableFontIdentitySet_count(const reskia_remotable_font_identity_set_t *set) {
    if (set == nullptr) {
        return 0;
    }
    return as_identity_set(set)->count();
}

bool SkRemotableFontIdentitySet_at(const reskia_remotable_font_identity_set_t *set, int index, reskia_font_identity_t *out_identity) {
    if (set == nullptr || out_identity == nullptr) {
        return false;
    }
    auto *identity_set = as_identity_set(set);
    if (index < 0 || identity_set->count() <= index) {
        return false;
    }
    *out_identity = from_sk_font_identity(identity_set->at(index));
    return true;
}

reskia_remotable_font_identity_set_t *SkRemotableFontIdentitySet_NewEmpty(void) {
    return to_identity_set(SkRemotableFontIdentitySet::NewEmpty());
}

void SkRemotableFontMgr_ref(reskia_remotable_font_mgr_t *mgr) {
    if (mgr == nullptr) {
        return;
    }
    as_remotable_font_mgr(mgr)->ref();
}

void SkRemotableFontMgr_unref(reskia_remotable_font_mgr_t *mgr) {
    if (mgr == nullptr) {
        return;
    }
    as_remotable_font_mgr(mgr)->unref();
}

reskia_remotable_font_identity_set_t *SkRemotableFontMgr_getIndex(const reskia_remotable_font_mgr_t *mgr, int familyIndex) {
    if (mgr == nullptr) {
        return nullptr;
    }
    return to_identity_set(as_remotable_font_mgr(mgr)->getIndex(familyIndex));
}

bool SkRemotableFontMgr_matchIndexStyle(const reskia_remotable_font_mgr_t *mgr, int familyIndex, const reskia_font_style_t *style, reskia_font_identity_t *out_identity) {
    if (mgr == nullptr || style == nullptr || out_identity == nullptr) {
        return false;
    }
    *out_identity = from_sk_font_identity(
            as_remotable_font_mgr(mgr)->matchIndexStyle(familyIndex, to_sk_font_style(style)));
    return true;
}

reskia_remotable_font_identity_set_t *SkRemotableFontMgr_matchName(const reskia_remotable_font_mgr_t *mgr, const char familyName[]) {
    if (mgr == nullptr) {
        return nullptr;
    }
    return to_identity_set(as_remotable_font_mgr(mgr)->matchName(familyName));
}

bool SkRemotableFontMgr_matchNameStyle(const reskia_remotable_font_mgr_t *mgr, const char familyName[], const reskia_font_style_t *style, reskia_font_identity_t *out_identity) {
    if (mgr == nullptr || style == nullptr || out_identity == nullptr) {
        return false;
    }
    *out_identity = from_sk_font_identity(
            as_remotable_font_mgr(mgr)->matchNameStyle(familyName, to_sk_font_style(style)));
    return true;
}

bool SkRemotableFontMgr_matchNameStyleCharacter(const reskia_remotable_font_mgr_t *mgr, const char familyName[], const reskia_font_style_t *style, const char *bcp47[], int bcp47Count, int32_t character, reskia_font_identity_t *out_identity) {
    if (mgr == nullptr || style == nullptr || out_identity == nullptr || bcp47Count < 0 ||
        (bcp47Count > 0 && bcp47 == nullptr)) {
        return false;
    }
    *out_identity = from_sk_font_identity(
            as_remotable_font_mgr(mgr)->matchNameStyleCharacter(
                    familyName,
                    to_sk_font_style(style),
                    bcp47,
                    bcp47Count,
                    static_cast<SkUnichar>(character)));
    return true;
}

sk_stream_asset_t SkRemotableFontMgr_getData(const reskia_remotable_font_mgr_t *mgr, int dataId) {
    if (mgr == nullptr || dataId < 0) {
        return 0;
    }
    std::unique_ptr<SkStreamAsset> stream(as_remotable_font_mgr(mgr)->getData(dataId));
    if (!stream) {
        return 0;
    }
    return static_sk_stream_asset_make(std::move(stream));
}

sk_font_mgr_t SkFontMgr_Indirect_new(sk_font_mgr_t impl, reskia_remotable_font_mgr_t *proxy) {
    if (impl == 0 || proxy == nullptr) {
        return 0;
    }
    sk_sp<SkFontMgr> impl_mgr = static_sk_font_mgr_get_entity(impl);
    if (!impl_mgr) {
        return 0;
    }
    return to_font_mgr_handle(sk_make_sp<SkFontMgr_Indirect>(
            std::move(impl_mgr),
            sk_ref_sp(as_remotable_font_mgr(proxy))));
}

}
