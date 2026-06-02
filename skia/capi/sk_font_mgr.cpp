//
// Created by dolphilia on 2024/01/08.
//

#include "sk_font_mgr.h"

#include <optional>
#include <utility>

#include "include/core/SkFontMgr.h"
#include "include/core/SkSpan.h"

#include "../handles/static_sk_font_mgr.h"
#include "../handles/static_sk_font_style_set.h"
#include "../handles/static_sk_typeface.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_stream_asset.h"
#include "../handles/static_sk_font_style.h"

#include "../handles/static_sk_font_mgr-internal.h"
#include "../handles/static_sk_font_style-internal.h"
#include "../handles/static_sk_font_style_set-internal.h"
#include "../handles/static_sk_stream_asset-internal.h"
#include "../handles/static_sk_typeface-internal.h"
#include "../handles/static_sk_data-internal.h"

namespace {

SkFontMgr *as_font_mgr(reskia_font_mgr_t *font_mgr) {
    return reinterpret_cast<SkFontMgr *>(font_mgr);
}

sk_font_mgr_t make_font_mgr_handle(sk_sp<SkFontMgr> font_mgr) {
    if (!font_mgr) {
        return 0;
    }
    return static_sk_font_mgr_make(std::move(font_mgr));
}

sk_font_style_set_t make_font_style_set_handle(sk_sp<SkFontStyleSet> style_set) {
    if (!style_set) {
        return 0;
    }
    return static_sk_font_style_set_make(std::move(style_set));
}

sk_typeface_t make_typeface_handle(sk_sp<SkTypeface> typeface) {
    if (!typeface) {
        return 0;
    }
    return static_sk_typeface_make(std::move(typeface));
}

bool is_valid_family_index(SkFontMgr *font_mgr, int index) {
    return font_mgr != nullptr && 0 <= index && index < font_mgr->countFamilies();
}

bool make_font_mgr_request(const reskia_font_mgr_request_t *request, SkFontMgr::Request *out_request) {
    if (request == nullptr || out_request == nullptr) {
        return false;
    }
    if ((request->cmap_entry_count > 0 && request->cmap_entries == nullptr) ||
        (request->bcp47_count > 0 && request->bcp47 == nullptr) ||
        (request->model_count > 0 && request->model == nullptr)) {
        return false;
    }
    out_request->cmapEntries = SkSpan<const SkFontMgr::Request::CMapEntry>(
            reinterpret_cast<const SkFontMgr::Request::CMapEntry *>(request->cmap_entries),
            request->cmap_entry_count);
    out_request->bcp47 = SkSpan<const char *>(request->bcp47, request->bcp47_count);
    out_request->familyName = request->family_name;
    out_request->model = SkSpan<const SkFontArguments::VariationPosition::Coordinate>(
            reinterpret_cast<const SkFontArguments::VariationPosition::Coordinate *>(request->model),
            request->model_count);
    out_request->syntheticBold = request->has_synthetic_bold
            ? std::optional<bool>(request->synthetic_bold)
            : std::nullopt;
    out_request->syntheticOblique = request->has_synthetic_oblique
            ? std::optional<bool>(request->synthetic_oblique)
            : std::nullopt;
    return true;
}

}  // namespace

extern "C" {

void SkFontMgr_release(reskia_font_mgr_t *font_mgr) {
    if (font_mgr == nullptr) {
        return;
    }
    as_font_mgr(font_mgr)->unref();
}

int SkFontMgr_countFamilies(reskia_font_mgr_t *font_mgr) {
    if (font_mgr == nullptr) {
        return 0;
    }
    return as_font_mgr(font_mgr)->countFamilies();
}

void SkFontMgr_getFamilyName(reskia_font_mgr_t *font_mgr, int index, reskia_string_t *familyName) {
    auto *sk_font_mgr = as_font_mgr(font_mgr);
    if (!is_valid_family_index(sk_font_mgr, index) || familyName == nullptr) {
        return;
    }
    sk_font_mgr->getFamilyName(index, reinterpret_cast<SkString *>(familyName));
}

reskia_status_t SkFontMgr_createStyleSet(reskia_font_mgr_t *font_mgr, int index, sk_font_style_set_t *out_style_set) {
    if (out_style_set != nullptr) {
        *out_style_set = 0;
    }
    auto *sk_font_mgr = as_font_mgr(font_mgr);
    if (sk_font_mgr == nullptr || out_style_set == nullptr || !is_valid_family_index(sk_font_mgr, index)) {
        return RESKIA_STATUS_INVALID_ARGUMENT;
    }
    sk_sp<SkFontStyleSet> style_set = sk_font_mgr->createStyleSet(index);
    if (style_set == nullptr) {
        return RESKIA_STATUS_NOT_FOUND;
    }
    *out_style_set = make_font_style_set_handle(std::move(style_set));
    return RESKIA_STATUS_OK;
}

reskia_status_t SkFontMgr_matchFamily(reskia_font_mgr_t *font_mgr, const char familyName[], sk_font_style_set_t *out_style_set) {
    if (out_style_set != nullptr) {
        *out_style_set = 0;
    }
    if (font_mgr == nullptr || out_style_set == nullptr) {
        return RESKIA_STATUS_INVALID_ARGUMENT;
    }
    sk_sp<SkFontStyleSet> style_set = as_font_mgr(font_mgr)->matchFamily(familyName);
    if (style_set == nullptr) {
        return RESKIA_STATUS_NOT_FOUND;
    }
    *out_style_set = make_font_style_set_handle(std::move(style_set));
    return RESKIA_STATUS_OK;
}

sk_typeface_t SkFontMgr_matchFamilyStyle(reskia_font_mgr_t *font_mgr, const char familyName[], const reskia_font_style_t *font_style) {
    if (font_mgr == nullptr || font_style == nullptr) {
        return 0;
    }
    return make_typeface_handle(as_font_mgr(font_mgr)->matchFamilyStyle(familyName, * reinterpret_cast<const SkFontStyle *>(font_style)));
}

sk_typeface_t SkFontMgr_matchFamilyStyleCharacter(reskia_font_mgr_t *font_mgr, const char familyName[], const reskia_font_style_t *font_style, const char *bcp47[], int bcp47Count, reskia_font_mgr_unichar_t character) {
    if (font_mgr == nullptr || font_style == nullptr || bcp47Count < 0 || (bcp47Count > 0 && bcp47 == nullptr)) {
        return 0;
    }
    return make_typeface_handle(as_font_mgr(font_mgr)->matchFamilyStyleCharacter(familyName, * reinterpret_cast<const SkFontStyle *>(font_style), bcp47, bcp47Count, static_cast<SkUnichar>(character)));
}

sk_typeface_t SkFontMgr_match(reskia_font_mgr_t *font_mgr, const reskia_font_mgr_request_t *request) {
    SkFontMgr::Request native_request{};
    if (font_mgr == nullptr || !make_font_mgr_request(request, &native_request)) {
        return 0;
    }
    return make_typeface_handle(as_font_mgr(font_mgr)->match(native_request));
}

sk_typeface_t SkFontMgr_fallback(reskia_font_mgr_t *font_mgr, const reskia_font_mgr_request_t *request) {
    SkFontMgr::Request native_request{};
    if (font_mgr == nullptr || !make_font_mgr_request(request, &native_request)) {
        return 0;
    }
    return make_typeface_handle(as_font_mgr(font_mgr)->fallback(native_request));
}

sk_typeface_t SkFontMgr_makeFromData(reskia_font_mgr_t *font_mgr, sk_data_t data, int ttcIndex) {
    if (font_mgr == nullptr || data == 0 || ttcIndex < 0) {
        return 0;
    }
    return make_typeface_handle(as_font_mgr(font_mgr)->makeFromData(static_sk_data_get_entity(data), ttcIndex));
}

sk_typeface_t SkFontMgr_makeFromStream(reskia_font_mgr_t *font_mgr, sk_stream_asset_t stream_asset, int ttcIndex) {
    if (font_mgr == nullptr || stream_asset == 0 || ttcIndex < 0) {
        return 0;
    }
    return make_typeface_handle(as_font_mgr(font_mgr)->makeFromStream(static_sk_stream_asset_take_entity(stream_asset), ttcIndex));
}

sk_typeface_t SkFontMgr_makeFromStreamWithArguments(reskia_font_mgr_t *font_mgr, sk_stream_asset_t stream_asset, const reskia_font_arguments_t *font_argments) {
    if (font_mgr == nullptr || stream_asset == 0 || font_argments == nullptr) {
        return 0;
    }
    return make_typeface_handle(as_font_mgr(font_mgr)->makeFromStream(static_sk_stream_asset_take_entity(stream_asset), * reinterpret_cast<const SkFontArguments *>(font_argments)));
}

sk_typeface_t SkFontMgr_makeFromFile(reskia_font_mgr_t *font_mgr, const char path[], int ttcIndex) {
    if (font_mgr == nullptr || path == nullptr || ttcIndex < 0) {
        return 0;
    }
    return make_typeface_handle(as_font_mgr(font_mgr)->makeFromFile(path, ttcIndex));
}

sk_typeface_t SkFontMgr_legacyMakeTypeface(reskia_font_mgr_t *font_mgr, const char familyName[], sk_font_style_t style) {
    if (font_mgr == nullptr) {
        return 0;
    }
    return make_typeface_handle(as_font_mgr(font_mgr)->legacyMakeTypeface(familyName, static_sk_font_style_get_entity(style)));
}

bool SkFontMgr_unique(reskia_font_mgr_t *font_mgr) {
    return font_mgr != nullptr && as_font_mgr(font_mgr)->unique();
}

void SkFontMgr_ref(reskia_font_mgr_t *font_mgr) {
    if (font_mgr == nullptr) {
        return;
    }
    as_font_mgr(font_mgr)->ref();
}

void SkFontMgr_unref(reskia_font_mgr_t *font_mgr) {
    if (font_mgr == nullptr) {
        return;
    }
    as_font_mgr(font_mgr)->unref();
}

// static

sk_font_mgr_t SkFontMgr_RefEmpty() {
    return make_font_mgr_handle(SkFontMgr::RefEmpty());
}

}
