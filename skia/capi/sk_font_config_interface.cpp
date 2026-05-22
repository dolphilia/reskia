//
// Created by Codex on 2026/05/16.
//

#include "sk_font_config_interface.h"

#include <memory>
#include <utility>

#include "include/core/SkFontMgr.h"
#include "include/core/SkFontStyle.h"
#include "include/core/SkRefCnt.h"
#include "include/core/SkStream.h"
#include "include/core/SkString.h"
#include "include/core/SkTypeface.h"
#include "include/ports/SkFontConfigInterface.h"

#include "../handles/static_sk_font_mgr-internal.h"
#include "../handles/static_sk_stream_asset-internal.h"
#include "../handles/static_sk_typeface-internal.h"

namespace {

using FontIdentity = SkFontConfigInterface::FontIdentity;

FontIdentity *as_identity(const reskia_font_config_identity_t *identity) {
    return const_cast<FontIdentity *>(
            reinterpret_cast<const FontIdentity *>(identity));
}

SkFontConfigInterface *as_interface(const reskia_font_config_interface_t *interface_) {
    return const_cast<SkFontConfigInterface *>(
            reinterpret_cast<const SkFontConfigInterface *>(interface_));
}

SkString *as_string(reskia_string_t *string) {
    return reinterpret_cast<SkString *>(string);
}

const SkFontStyle *as_font_style(const reskia_font_style_t *style) {
    return reinterpret_cast<const SkFontStyle *>(style);
}

reskia_font_config_identity_t *to_identity(FontIdentity *identity) {
    return reinterpret_cast<reskia_font_config_identity_t *>(identity);
}

reskia_font_config_interface_t *to_interface(SkFontConfigInterface *interface_) {
    return reinterpret_cast<reskia_font_config_interface_t *>(interface_);
}

reskia_string_t *to_string(SkString *string) {
    return reinterpret_cast<reskia_string_t *>(string);
}

reskia_font_style_t *to_font_style(SkFontStyle *style) {
    return reinterpret_cast<reskia_font_style_t *>(style);
}

sk_stream_asset_t to_stream_asset_handle(std::unique_ptr<SkStreamAsset> stream) {
    if (!stream) {
        return 0;
    }
    return static_sk_stream_asset_make(std::move(stream));
}

sk_typeface_t to_typeface_handle(sk_sp<SkTypeface> typeface) {
    if (!typeface) {
        return 0;
    }
    return static_sk_typeface_make(std::move(typeface));
}

sk_sp<SkFontMgr> font_mgr_or_default(sk_font_mgr_t font_mgr) {
    if (font_mgr == 0) {
        return SkFontMgr::RefEmpty();
    }
    return static_sk_font_mgr_get_entity(font_mgr);
}

}  // namespace

extern "C" {

reskia_font_config_identity_t *SkFontConfigInterface_FontIdentity_new(void) {
    return to_identity(new FontIdentity());
}

void SkFontConfigInterface_FontIdentity_delete(reskia_font_config_identity_t *identity) {
    delete as_identity(identity);
}

uint32_t SkFontConfigInterface_FontIdentity_getID(const reskia_font_config_identity_t *identity) {
    if (identity == nullptr) {
        return 0;
    }
    return as_identity(identity)->fID;
}

void SkFontConfigInterface_FontIdentity_setID(reskia_font_config_identity_t *identity, uint32_t id) {
    if (identity == nullptr) {
        return;
    }
    as_identity(identity)->fID = id;
}

int32_t SkFontConfigInterface_FontIdentity_getTTCIndex(const reskia_font_config_identity_t *identity) {
    if (identity == nullptr) {
        return 0;
    }
    return as_identity(identity)->fTTCIndex;
}

void SkFontConfigInterface_FontIdentity_setTTCIndex(reskia_font_config_identity_t *identity, int32_t ttc_index) {
    if (identity == nullptr) {
        return;
    }
    as_identity(identity)->fTTCIndex = ttc_index;
}

reskia_string_t *SkFontConfigInterface_FontIdentity_getString(const reskia_font_config_identity_t *identity) {
    if (identity == nullptr) {
        return nullptr;
    }
    return to_string(new SkString(as_identity(identity)->fString));
}

void SkFontConfigInterface_FontIdentity_setString(reskia_font_config_identity_t *identity, const char text[]) {
    if (identity == nullptr) {
        return;
    }
    if (text == nullptr) {
        as_identity(identity)->fString.reset();
        return;
    }
    as_identity(identity)->fString.set(text);
}

reskia_font_style_t *SkFontConfigInterface_FontIdentity_getStyle(const reskia_font_config_identity_t *identity) {
    if (identity == nullptr) {
        return nullptr;
    }
    return to_font_style(new SkFontStyle(as_identity(identity)->fStyle));
}

void SkFontConfigInterface_FontIdentity_setStyle(reskia_font_config_identity_t *identity, const reskia_font_style_t *style) {
    if (identity == nullptr || style == nullptr) {
        return;
    }
    as_identity(identity)->fStyle = *as_font_style(style);
}

size_t SkFontConfigInterface_FontIdentity_writeToMemory(const reskia_font_config_identity_t *identity, void *buffer) {
    if (identity == nullptr) {
        return 0;
    }
    return as_identity(identity)->writeToMemory(buffer);
}

size_t SkFontConfigInterface_FontIdentity_readFromMemory(reskia_font_config_identity_t *identity, const void *buffer, size_t length) {
    if (identity == nullptr || (buffer == nullptr && length > 0)) {
        return 0;
    }
    return as_identity(identity)->readFromMemory(buffer, length);
}

reskia_font_config_interface_t *SkFontConfigInterface_RefGlobal(void) {
    sk_sp<SkFontConfigInterface> interface_ = SkFontConfigInterface::RefGlobal();
    if (!interface_) {
        return nullptr;
    }
    return to_interface(interface_.release());
}

void SkFontConfigInterface_SetGlobal(reskia_font_config_interface_t *interface_) {
    SkFontConfigInterface::SetGlobal(sk_ref_sp(as_interface(interface_)));
}

reskia_font_config_interface_t *SkFontConfigInterface_GetSingletonDirectInterface(void) {
    return to_interface(SkFontConfigInterface::GetSingletonDirectInterface());
}

void SkFontConfigInterface_ref(reskia_font_config_interface_t *interface_) {
    if (interface_ == nullptr) {
        return;
    }
    as_interface(interface_)->ref();
}

void SkFontConfigInterface_unref(reskia_font_config_interface_t *interface_) {
    if (interface_ == nullptr) {
        return;
    }
    as_interface(interface_)->unref();
}

bool SkFontConfigInterface_matchFamilyName(
        reskia_font_config_interface_t *interface_,
        const char family_name[],
        const reskia_font_style_t *requested,
        reskia_font_config_identity_t *out_font_identifier,
        reskia_string_t *out_family_name,
        reskia_font_style_t **out_style) {
    if (interface_ == nullptr || requested == nullptr || out_font_identifier == nullptr) {
        return false;
    }

    SkFontStyle style;
    SkFontStyle *style_ptr = out_style == nullptr ? nullptr : &style;
    const bool matched = as_interface(interface_)->matchFamilyName(
            family_name,
            *as_font_style(requested),
            as_identity(out_font_identifier),
            as_string(out_family_name),
            style_ptr);
    if (matched && out_style != nullptr) {
        *out_style = to_font_style(new SkFontStyle(style));
    }
    return matched;
}

sk_stream_asset_t SkFontConfigInterface_openStream(
        reskia_font_config_interface_t *interface_,
        const reskia_font_config_identity_t *identity) {
    if (interface_ == nullptr || identity == nullptr) {
        return 0;
    }
    return to_stream_asset_handle(
            std::unique_ptr<SkStreamAsset>(as_interface(interface_)->openStream(*as_identity(identity))));
}

sk_typeface_t SkFontConfigInterface_makeTypeface(
        reskia_font_config_interface_t *interface_,
        const reskia_font_config_identity_t *identity,
        sk_font_mgr_t font_mgr) {
    if (interface_ == nullptr || identity == nullptr) {
        return 0;
    }
    sk_sp<SkFontMgr> mgr = font_mgr_or_default(font_mgr);
    if (!mgr) {
        return 0;
    }
    return to_typeface_handle(as_interface(interface_)->makeTypeface(*as_identity(identity), std::move(mgr)));
}

}
