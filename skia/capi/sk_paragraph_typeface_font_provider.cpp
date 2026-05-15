//
// Created by Codex on 2026/05/15.
//

#include "sk_paragraph_typeface_font_provider.h"

#include "include/core/SkData.h"
#include "include/core/SkFontArguments.h"
#include "include/core/SkFontStyle.h"
#include "include/core/SkStream.h"
#include "include/core/SkString.h"
#include "include/core/SkTypeface.h"
#include "modules/skparagraph/include/TypefaceFontProvider.h"

#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_font_mgr-internal.h"
#include "../handles/static_sk_font_style-internal.h"
#include "../handles/static_sk_font_style_set-internal.h"
#include "../handles/static_sk_stream_asset-internal.h"
#include "../handles/static_sk_typeface-internal.h"

#include <memory>
#include <utility>

namespace {

using skia::textlayout::TypefaceFontProvider;
using skia::textlayout::TypefaceFontStyleSet;

TypefaceFontProvider *as_provider(reskia_paragraph_typeface_font_provider_t *provider) {
    return reinterpret_cast<TypefaceFontProvider *>(provider);
}

const TypefaceFontProvider *as_provider(const reskia_paragraph_typeface_font_provider_t *provider) {
    return reinterpret_cast<const TypefaceFontProvider *>(provider);
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

SkFontStyle font_style_or_normal(sk_font_style_t style) {
    return style == 0 ? SkFontStyle() : static_sk_font_style_get_entity(style);
}

}  // namespace

extern "C" {

reskia_paragraph_typeface_font_provider_t *SkParagraph_TypefaceFontProvider_new(void) {
    return reinterpret_cast<reskia_paragraph_typeface_font_provider_t *>(new TypefaceFontProvider());
}

void SkParagraph_TypefaceFontProvider_release(reskia_paragraph_typeface_font_provider_t *provider) {
    if (provider != nullptr) {
        as_provider(provider)->unref();
    }
}

void SkParagraph_TypefaceFontProvider_ref(reskia_paragraph_typeface_font_provider_t *provider) {
    if (provider != nullptr) {
        as_provider(provider)->ref();
    }
}

void SkParagraph_TypefaceFontProvider_unref(reskia_paragraph_typeface_font_provider_t *provider) {
    SkParagraph_TypefaceFontProvider_release(provider);
}

sk_font_mgr_t SkParagraph_TypefaceFontProvider_refFontMgr(reskia_paragraph_typeface_font_provider_t *provider) {
    if (provider == nullptr) {
        return 0;
    }
    return static_sk_font_mgr_make(sk_ref_sp(static_cast<SkFontMgr *>(as_provider(provider))));
}

size_t SkParagraph_TypefaceFontProvider_registerTypeface(reskia_paragraph_typeface_font_provider_t *provider, sk_typeface_t typeface) {
    if (provider == nullptr || typeface == 0) {
        return 0;
    }
    return as_provider(provider)->registerTypeface(static_sk_typeface_get_entity(typeface));
}

size_t SkParagraph_TypefaceFontProvider_registerTypefaceWithAlias(reskia_paragraph_typeface_font_provider_t *provider, sk_typeface_t typeface, const char *alias) {
    if (provider == nullptr || typeface == 0 || alias == nullptr) {
        return 0;
    }
    return as_provider(provider)->registerTypeface(static_sk_typeface_get_entity(typeface), SkString(alias));
}

int SkParagraph_TypefaceFontProvider_onCountFamilies(const reskia_paragraph_typeface_font_provider_t *provider) {
    return provider == nullptr ? 0 : as_provider(provider)->onCountFamilies();
}

reskia_string_t *SkParagraph_TypefaceFontProvider_onGetFamilyName(const reskia_paragraph_typeface_font_provider_t *provider, int index) {
    if (provider == nullptr || index < 0 || index >= as_provider(provider)->onCountFamilies()) {
        return nullptr;
    }
    auto *family_name = new SkString();
    as_provider(provider)->onGetFamilyName(index, family_name);
    return reinterpret_cast<reskia_string_t *>(family_name);
}

sk_font_style_set_t SkParagraph_TypefaceFontProvider_onMatchFamily(const reskia_paragraph_typeface_font_provider_t *provider, const char *family_name) {
    if (provider == nullptr) {
        return 0;
    }
    return make_font_style_set_handle(as_provider(provider)->onMatchFamily(family_name));
}

sk_font_style_set_t SkParagraph_TypefaceFontProvider_onCreateStyleSet(const reskia_paragraph_typeface_font_provider_t *provider, int index) {
    if (provider == nullptr || index < 0) {
        return 0;
    }
    return make_font_style_set_handle(as_provider(provider)->onCreateStyleSet(index));
}

sk_typeface_t SkParagraph_TypefaceFontProvider_onMatchFamilyStyle(const reskia_paragraph_typeface_font_provider_t *provider, const char *family_name, sk_font_style_t style) {
    if (provider == nullptr) {
        return 0;
    }
    return make_typeface_handle(as_provider(provider)->onMatchFamilyStyle(family_name, font_style_or_normal(style)));
}

sk_typeface_t SkParagraph_TypefaceFontProvider_onMatchFamilyStyleCharacter(const reskia_paragraph_typeface_font_provider_t *provider, const char *family_name, sk_font_style_t style, const char *bcp47[], int bcp47_count, reskia_font_mgr_unichar_t character) {
    if (provider == nullptr || bcp47_count < 0 || (bcp47_count > 0 && bcp47 == nullptr)) {
        return 0;
    }
    return make_typeface_handle(as_provider(provider)->onMatchFamilyStyleCharacter(family_name, font_style_or_normal(style), bcp47, bcp47_count, static_cast<SkUnichar>(character)));
}

sk_typeface_t SkParagraph_TypefaceFontProvider_onMakeFromData(const reskia_paragraph_typeface_font_provider_t *provider, sk_data_t data, int ttc_index) {
    if (provider == nullptr || data == 0 || ttc_index < 0) {
        return 0;
    }
    return make_typeface_handle(as_provider(provider)->onMakeFromData(static_sk_data_get_entity(data), ttc_index));
}

sk_typeface_t SkParagraph_TypefaceFontProvider_onMakeFromStreamIndex(const reskia_paragraph_typeface_font_provider_t *provider, sk_stream_asset_t stream_asset, int ttc_index) {
    if (provider == nullptr || stream_asset == 0 || ttc_index < 0) {
        return 0;
    }
    return make_typeface_handle(as_provider(provider)->onMakeFromStreamIndex(static_sk_stream_asset_take_entity(stream_asset), ttc_index));
}

sk_typeface_t SkParagraph_TypefaceFontProvider_onMakeFromStreamArgs(const reskia_paragraph_typeface_font_provider_t *provider, sk_stream_asset_t stream_asset, const reskia_font_arguments_t *arguments) {
    if (provider == nullptr || stream_asset == 0 || arguments == nullptr) {
        return 0;
    }
    return make_typeface_handle(as_provider(provider)->onMakeFromStreamArgs(static_sk_stream_asset_take_entity(stream_asset), *reinterpret_cast<const SkFontArguments *>(arguments)));
}

sk_typeface_t SkParagraph_TypefaceFontProvider_onMakeFromFile(const reskia_paragraph_typeface_font_provider_t *provider, const char *path, int ttc_index) {
    if (provider == nullptr || path == nullptr || ttc_index < 0) {
        return 0;
    }
    return make_typeface_handle(as_provider(provider)->onMakeFromFile(path, ttc_index));
}

sk_typeface_t SkParagraph_TypefaceFontProvider_onLegacyMakeTypeface(const reskia_paragraph_typeface_font_provider_t *provider, const char *family_name, sk_font_style_t style) {
    if (provider == nullptr) {
        return 0;
    }
    return make_typeface_handle(as_provider(provider)->onLegacyMakeTypeface(family_name, font_style_or_normal(style)));
}

reskia_string_t *SkParagraph_TypefaceFontStyleSet_getFamilyName(sk_font_style_set_t style_set) {
    if (style_set == 0) {
        return nullptr;
    }
    auto font_style_set = static_sk_font_style_set_borrow_entity(style_set);
    auto *paragraph_style_set = dynamic_cast<TypefaceFontStyleSet *>(font_style_set.get());
    if (paragraph_style_set == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_string_t *>(new SkString(paragraph_style_set->getFamilyName()));
}

reskia_string_t *SkParagraph_TypefaceFontStyleSet_getAlias(sk_font_style_set_t style_set) {
    if (style_set == 0) {
        return nullptr;
    }
    auto font_style_set = static_sk_font_style_set_borrow_entity(style_set);
    auto *paragraph_style_set = dynamic_cast<TypefaceFontStyleSet *>(font_style_set.get());
    if (paragraph_style_set == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_string_t *>(new SkString(paragraph_style_set->getAlias()));
}

bool SkParagraph_TypefaceFontStyleSet_appendTypeface(sk_font_style_set_t style_set, sk_typeface_t typeface) {
    if (style_set == 0 || typeface == 0) {
        return false;
    }
    auto font_style_set = static_sk_font_style_set_borrow_entity(style_set);
    auto *paragraph_style_set = dynamic_cast<TypefaceFontStyleSet *>(font_style_set.get());
    if (paragraph_style_set == nullptr) {
        return false;
    }
    paragraph_style_set->appendTypeface(static_sk_typeface_get_entity(typeface));
    return true;
}

}  // extern "C"
