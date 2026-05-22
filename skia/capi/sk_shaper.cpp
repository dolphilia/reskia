//
// Created by Codex on 2026/05/17.
//

#include "sk_shaper.h"

#include "include/core/SkFont.h"
#include "include/core/SkFontMgr.h"
#include "include/core/SkFontStyle.h"
#include "modules/skshaper/include/SkShaper.h"
#include "modules/skunicode/include/SkUnicode.h"

#include "../handles/static_sk_font_mgr-internal.h"

#include <algorithm>
#include <memory>
#include <vector>

namespace {

SkShaper *as_shaper(reskia_shaper_t *shaper) {
    return reinterpret_cast<SkShaper *>(shaper);
}

const SkFont *as_font(const reskia_font_t *font) {
    return reinterpret_cast<const SkFont *>(font);
}

SkUnicode *as_unicode(reskia_unicode_t *unicode) {
    return reinterpret_cast<SkUnicode *>(unicode);
}

SkShaper::FontRunIterator *as_font_iterator(reskia_shaper_font_run_iterator_t *iterator) {
    return reinterpret_cast<SkShaper::FontRunIterator *>(iterator);
}

const SkShaper::LanguageRunIterator *as_language_iterator(const reskia_shaper_language_run_iterator_t *iterator) {
    return reinterpret_cast<const SkShaper::LanguageRunIterator *>(iterator);
}

SkShaper::BiDiRunIterator *as_bidi_iterator(reskia_shaper_bidi_run_iterator_t *iterator) {
    return reinterpret_cast<SkShaper::BiDiRunIterator *>(iterator);
}

SkShaper::ScriptRunIterator *as_script_iterator(reskia_shaper_script_run_iterator_t *iterator) {
    return reinterpret_cast<SkShaper::ScriptRunIterator *>(iterator);
}

SkShaper::LanguageRunIterator *as_language_iterator(reskia_shaper_language_run_iterator_t *iterator) {
    return reinterpret_cast<SkShaper::LanguageRunIterator *>(iterator);
}

reskia_shaper_t *release_shaper(std::unique_ptr<SkShaper> shaper) {
    return reinterpret_cast<reskia_shaper_t *>(shaper.release());
}

reskia_shaper_font_run_iterator_t *release_font_iterator(std::unique_ptr<SkShaper::FontRunIterator> iterator) {
    return reinterpret_cast<reskia_shaper_font_run_iterator_t *>(iterator.release());
}

reskia_shaper_bidi_run_iterator_t *release_bidi_iterator(std::unique_ptr<SkShaper::BiDiRunIterator> iterator) {
    return reinterpret_cast<reskia_shaper_bidi_run_iterator_t *>(iterator.release());
}

reskia_shaper_script_run_iterator_t *release_script_iterator(std::unique_ptr<SkShaper::ScriptRunIterator> iterator) {
    return reinterpret_cast<reskia_shaper_script_run_iterator_t *>(iterator.release());
}

reskia_shaper_language_run_iterator_t *release_language_iterator(std::unique_ptr<SkShaper::LanguageRunIterator> iterator) {
    return reinterpret_cast<reskia_shaper_language_run_iterator_t *>(iterator.release());
}

bool valid_text(const char *utf8, size_t utf8_bytes) {
    return utf8 != nullptr || utf8_bytes == 0;
}

sk_sp<SkFontMgr> font_mgr_or_null(sk_font_mgr_t font_mgr) {
    return font_mgr == 0 ? nullptr : static_sk_font_mgr_get_entity(font_mgr);
}

sk_sp<SkFontMgr> font_mgr_or_default(sk_font_mgr_t font_mgr) {
    sk_sp<SkFontMgr> manager = font_mgr_or_null(font_mgr);
    return manager ? manager : SkFontMgr::RefEmpty();
}

template <typename Iterator>
bool consume_iterator(Iterator *iterator) {
    if (iterator == nullptr || iterator->atEnd()) {
        return false;
    }
    iterator->consume();
    return true;
}

template <typename Iterator>
size_t end_of_current_run(Iterator *iterator) {
    return iterator == nullptr ? 0 : iterator->endOfCurrentRun();
}

template <typename Iterator>
bool iterator_at_end(Iterator *iterator) {
    return iterator == nullptr || iterator->atEnd();
}

std::vector<SkShaper::Feature> make_features(const reskia_shaper_feature_t *features, size_t features_count) {
    std::vector<SkShaper::Feature> out;
    if (features == nullptr || features_count == 0) {
        return out;
    }
    out.reserve(features_count);
    for (size_t i = 0; i < features_count; ++i) {
        out.push_back({
            static_cast<SkFourByteTag>(features[i].tag),
            features[i].value,
            features[i].start,
            features[i].end,
        });
    }
    return out;
}

} // namespace

extern "C" {

reskia_shaper_t *SkShaper_Make(void) {
    return release_shaper(SkShaper::Make());
}

reskia_shaper_t *SkShaper_MakeWithFontMgr(sk_font_mgr_t font_mgr) {
    return release_shaper(SkShaper::Make(font_mgr_or_null(font_mgr)));
}

reskia_shaper_t *SkShaper_MakePrimitive(void) {
    return release_shaper(SkShaper::MakePrimitive());
}

reskia_shaper_t *SkShaper_MakeShaperDrivenWrapper(sk_font_mgr_t font_mgr) {
#if defined(SK_SHAPER_HARFBUZZ_AVAILABLE)
    return release_shaper(SkShaper::MakeShaperDrivenWrapper(font_mgr_or_null(font_mgr)));
#else
    (void)font_mgr;
    return nullptr;
#endif
}

reskia_shaper_t *SkShaper_MakeShapeThenWrap(sk_font_mgr_t font_mgr) {
#if defined(SK_SHAPER_HARFBUZZ_AVAILABLE)
    return release_shaper(SkShaper::MakeShapeThenWrap(font_mgr_or_null(font_mgr)));
#else
    (void)font_mgr;
    return nullptr;
#endif
}

reskia_shaper_t *SkShaper_MakeShapeDontWrapOrReorder(reskia_unicode_t *unicode, sk_font_mgr_t font_mgr) {
#if defined(SK_SHAPER_HARFBUZZ_AVAILABLE)
    if (unicode == nullptr) {
        return nullptr;
    }
    return release_shaper(SkShaper::MakeShapeDontWrapOrReorder(
            std::unique_ptr<SkUnicode>(as_unicode(unicode)),
            font_mgr_or_null(font_mgr)));
#else
    (void)unicode;
    (void)font_mgr;
    return nullptr;
#endif
}

reskia_shaper_t *SkShaper_MakeCoreText(void) {
#if defined(SK_SHAPER_CORETEXT_AVAILABLE)
    return release_shaper(SkShaper::MakeCoreText());
#else
    return nullptr;
#endif
}

void SkShaper_delete(reskia_shaper_t *shaper) {
    delete as_shaper(shaper);
}

void SkShaper_PurgeCaches(void) {
    SkShaper::PurgeCaches();
}

void SkShaper_PurgeHarfBuzzCache(void) {
#if defined(SK_SHAPER_HARFBUZZ_AVAILABLE)
    SkShaper::PurgeHarfBuzzCache();
#endif
}

reskia_shaper_font_run_iterator_t *SkShaper_MakeFontMgrRunIterator(const char *utf8, size_t utf8_bytes, const reskia_font_t *font, sk_font_mgr_t fallback) {
    if (!valid_text(utf8, utf8_bytes) || font == nullptr) {
        return nullptr;
    }
    sk_sp<SkFontMgr> fallback_manager = font_mgr_or_default(fallback);
    if (!fallback_manager) {
        return nullptr;
    }
    return release_font_iterator(SkShaper::MakeFontMgrRunIterator(utf8 == nullptr ? "" : utf8, utf8_bytes, *as_font(font), std::move(fallback_manager)));
}

reskia_shaper_font_run_iterator_t *SkShaper_MakeFontMgrRunIteratorWithRequest(const char *utf8, size_t utf8_bytes, const reskia_font_t *font, sk_font_mgr_t fallback, const char *request_name, int32_t request_weight, int32_t request_width, int32_t request_slant, const reskia_shaper_language_run_iterator_t *language_iterator) {
    if (!valid_text(utf8, utf8_bytes) || font == nullptr) {
        return nullptr;
    }
    return release_font_iterator(SkShaper::MakeFontMgrRunIterator(
            utf8 == nullptr ? "" : utf8,
            utf8_bytes,
            *as_font(font),
            font_mgr_or_default(fallback),
            request_name,
            SkFontStyle(request_weight, request_width, static_cast<SkFontStyle::Slant>(request_slant)),
            as_language_iterator(language_iterator)));
}

reskia_shaper_bidi_run_iterator_t *SkShaper_MakeBiDiRunIterator(const char *utf8, size_t utf8_bytes, uint8_t bidi_level) {
    if (!valid_text(utf8, utf8_bytes)) {
        return nullptr;
    }
    return release_bidi_iterator(SkShaper::MakeBiDiRunIterator(utf8 == nullptr ? "" : utf8, utf8_bytes, bidi_level));
}

reskia_shaper_bidi_run_iterator_t *SkShaper_MakeSkUnicodeBidiRunIterator(reskia_unicode_t *unicode, const char *utf8, size_t utf8_bytes, uint8_t bidi_level) {
#if defined(SK_SHAPER_UNICODE_AVAILABLE)
    if (unicode == nullptr || !valid_text(utf8, utf8_bytes)) {
        return nullptr;
    }
    return release_bidi_iterator(SkShaper::MakeSkUnicodeBidiRunIterator(as_unicode(unicode), utf8 == nullptr ? "" : utf8, utf8_bytes, bidi_level));
#else
    (void)unicode;
    (void)utf8;
    (void)utf8_bytes;
    (void)bidi_level;
    return nullptr;
#endif
}

reskia_shaper_bidi_run_iterator_t *SkShaper_MakeIcuBiDiRunIterator(const char *utf8, size_t utf8_bytes, uint8_t bidi_level) {
#if defined(SK_SHAPER_UNICODE_AVAILABLE)
    if (!valid_text(utf8, utf8_bytes)) {
        return nullptr;
    }
    return release_bidi_iterator(SkShaper::MakeIcuBiDiRunIterator(utf8 == nullptr ? "" : utf8, utf8_bytes, bidi_level));
#else
    (void)utf8;
    (void)utf8_bytes;
    (void)bidi_level;
    return nullptr;
#endif
}

reskia_shaper_script_run_iterator_t *SkShaper_MakeScriptRunIterator(const char *utf8, size_t utf8_bytes, reskia_four_byte_tag_t script) {
    if (!valid_text(utf8, utf8_bytes)) {
        return nullptr;
    }
    return release_script_iterator(SkShaper::MakeScriptRunIterator(utf8 == nullptr ? "" : utf8, utf8_bytes, static_cast<SkFourByteTag>(script)));
}

reskia_shaper_script_run_iterator_t *SkShaper_MakeSkUnicodeHbScriptRunIterator(const char *utf8, size_t utf8_bytes) {
#if defined(SK_SHAPER_HARFBUZZ_AVAILABLE)
    if (!valid_text(utf8, utf8_bytes)) {
        return nullptr;
    }
    return release_script_iterator(SkShaper::MakeSkUnicodeHbScriptRunIterator(utf8 == nullptr ? "" : utf8, utf8_bytes));
#else
    (void)utf8;
    (void)utf8_bytes;
    return nullptr;
#endif
}

reskia_shaper_script_run_iterator_t *SkShaper_MakeSkUnicodeHbScriptRunIteratorWithScript(const char *utf8, size_t utf8_bytes, reskia_four_byte_tag_t script) {
#if defined(SK_SHAPER_HARFBUZZ_AVAILABLE)
    if (!valid_text(utf8, utf8_bytes)) {
        return nullptr;
    }
    return release_script_iterator(SkShaper::MakeSkUnicodeHbScriptRunIterator(utf8 == nullptr ? "" : utf8, utf8_bytes, static_cast<SkFourByteTag>(script)));
#else
    (void)utf8;
    (void)utf8_bytes;
    (void)script;
    return nullptr;
#endif
}

reskia_shaper_script_run_iterator_t *SkShaper_MakeHbIcuScriptRunIterator(const char *utf8, size_t utf8_bytes) {
#if defined(SK_SHAPER_HARFBUZZ_AVAILABLE)
    if (!valid_text(utf8, utf8_bytes)) {
        return nullptr;
    }
    return release_script_iterator(SkShaper::MakeHbIcuScriptRunIterator(utf8 == nullptr ? "" : utf8, utf8_bytes));
#else
    (void)utf8;
    (void)utf8_bytes;
    return nullptr;
#endif
}

reskia_shaper_language_run_iterator_t *SkShaper_MakeStdLanguageRunIterator(const char *utf8, size_t utf8_bytes) {
    if (!valid_text(utf8, utf8_bytes)) {
        return nullptr;
    }
    return release_language_iterator(SkShaper::MakeStdLanguageRunIterator(utf8 == nullptr ? "" : utf8, utf8_bytes));
}

void SkShaper_FontRunIterator_delete(reskia_shaper_font_run_iterator_t *iterator) {
    delete as_font_iterator(iterator);
}

void SkShaper_BiDiRunIterator_delete(reskia_shaper_bidi_run_iterator_t *iterator) {
    delete as_bidi_iterator(iterator);
}

void SkShaper_ScriptRunIterator_delete(reskia_shaper_script_run_iterator_t *iterator) {
    delete as_script_iterator(iterator);
}

void SkShaper_LanguageRunIterator_delete(reskia_shaper_language_run_iterator_t *iterator) {
    delete as_language_iterator(iterator);
}

bool SkShaper_FontRunIterator_consume(reskia_shaper_font_run_iterator_t *iterator) {
    return consume_iterator(as_font_iterator(iterator));
}

bool SkShaper_BiDiRunIterator_consume(reskia_shaper_bidi_run_iterator_t *iterator) {
    return consume_iterator(as_bidi_iterator(iterator));
}

bool SkShaper_ScriptRunIterator_consume(reskia_shaper_script_run_iterator_t *iterator) {
    return consume_iterator(as_script_iterator(iterator));
}

bool SkShaper_LanguageRunIterator_consume(reskia_shaper_language_run_iterator_t *iterator) {
    return consume_iterator(as_language_iterator(iterator));
}

size_t SkShaper_FontRunIterator_endOfCurrentRun(reskia_shaper_font_run_iterator_t *iterator) {
    return end_of_current_run(as_font_iterator(iterator));
}

size_t SkShaper_BiDiRunIterator_endOfCurrentRun(reskia_shaper_bidi_run_iterator_t *iterator) {
    return end_of_current_run(as_bidi_iterator(iterator));
}

size_t SkShaper_ScriptRunIterator_endOfCurrentRun(reskia_shaper_script_run_iterator_t *iterator) {
    return end_of_current_run(as_script_iterator(iterator));
}

size_t SkShaper_LanguageRunIterator_endOfCurrentRun(reskia_shaper_language_run_iterator_t *iterator) {
    return end_of_current_run(as_language_iterator(iterator));
}

bool SkShaper_FontRunIterator_atEnd(reskia_shaper_font_run_iterator_t *iterator) {
    return iterator_at_end(as_font_iterator(iterator));
}

bool SkShaper_BiDiRunIterator_atEnd(reskia_shaper_bidi_run_iterator_t *iterator) {
    return iterator_at_end(as_bidi_iterator(iterator));
}

bool SkShaper_ScriptRunIterator_atEnd(reskia_shaper_script_run_iterator_t *iterator) {
    return iterator_at_end(as_script_iterator(iterator));
}

bool SkShaper_LanguageRunIterator_atEnd(reskia_shaper_language_run_iterator_t *iterator) {
    return iterator_at_end(as_language_iterator(iterator));
}

uint8_t SkShaper_BiDiRunIterator_currentLevel(reskia_shaper_bidi_run_iterator_t *iterator) {
    return iterator == nullptr ? 0 : as_bidi_iterator(iterator)->currentLevel();
}

reskia_four_byte_tag_t SkShaper_ScriptRunIterator_currentScript(reskia_shaper_script_run_iterator_t *iterator) {
    return iterator == nullptr ? 0 : static_cast<reskia_four_byte_tag_t>(as_script_iterator(iterator)->currentScript());
}

const char *SkShaper_LanguageRunIterator_currentLanguage(reskia_shaper_language_run_iterator_t *iterator) {
    return iterator == nullptr ? nullptr : as_language_iterator(iterator)->currentLanguage();
}

bool SkShaper_shape(reskia_shaper_t *shaper, const char *utf8, size_t utf8_bytes, const reskia_font_t *font, bool left_to_right, float width, SkTextBlobBuilderRunHandler *handler) {
    if (shaper == nullptr || !valid_text(utf8, utf8_bytes) || font == nullptr || handler == nullptr || width < 0.0f) {
        return false;
    }
    as_shaper(shaper)->shape(utf8 == nullptr ? "" : utf8, utf8_bytes, *as_font(font), left_to_right, width, handler);
    return true;
}

bool SkShaper_shapeWithIterators(reskia_shaper_t *shaper, const char *utf8, size_t utf8_bytes, reskia_shaper_font_run_iterator_t *font, reskia_shaper_bidi_run_iterator_t *bidi, reskia_shaper_script_run_iterator_t *script, reskia_shaper_language_run_iterator_t *language, float width, SkTextBlobBuilderRunHandler *handler) {
    if (shaper == nullptr || !valid_text(utf8, utf8_bytes) || font == nullptr || bidi == nullptr || script == nullptr || language == nullptr || handler == nullptr || width < 0.0f) {
        return false;
    }
    as_shaper(shaper)->shape(utf8 == nullptr ? "" : utf8, utf8_bytes, *as_font_iterator(font), *as_bidi_iterator(bidi), *as_script_iterator(script), *as_language_iterator(language), width, handler);
    return true;
}

bool SkShaper_shapeWithFeatures(reskia_shaper_t *shaper, const char *utf8, size_t utf8_bytes, reskia_shaper_font_run_iterator_t *font, reskia_shaper_bidi_run_iterator_t *bidi, reskia_shaper_script_run_iterator_t *script, reskia_shaper_language_run_iterator_t *language, const reskia_shaper_feature_t *features, size_t features_count, float width, SkTextBlobBuilderRunHandler *handler) {
    if (shaper == nullptr || !valid_text(utf8, utf8_bytes) || font == nullptr || bidi == nullptr || script == nullptr || language == nullptr || handler == nullptr || (features == nullptr && features_count != 0) || width < 0.0f) {
        return false;
    }
    const std::vector<SkShaper::Feature> feature_values = make_features(features, features_count);
    as_shaper(shaper)->shape(utf8 == nullptr ? "" : utf8, utf8_bytes, *as_font_iterator(font), *as_bidi_iterator(bidi), *as_script_iterator(script), *as_language_iterator(language), feature_values.data(), feature_values.size(), width, handler);
    return true;
}

} // extern "C"
