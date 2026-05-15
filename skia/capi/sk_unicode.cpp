//
// Created by Codex on 2026/05/15.
//

#include "sk_unicode.h"

#include "include/core/SkString.h"
#include "include/private/base/SkTArray.h"
#include "modules/skunicode/include/SkUnicode.h"

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

namespace {

SkUnicode *as_unicode(reskia_unicode_t *unicode) {
    return reinterpret_cast<SkUnicode *>(unicode);
}

const SkString *as_string(const reskia_string_t *string) {
    return reinterpret_cast<const SkString *>(string);
}

SkUnicode::CodeUnitFlags as_flags(reskia_unicode_code_unit_flags_t flags) {
    return static_cast<SkUnicode::CodeUnitFlags>(flags);
}

SkBidiIterator *as_bidi_iterator(reskia_bidi_iterator_t *iterator) {
    return reinterpret_cast<SkBidiIterator *>(iterator);
}

SkBreakIterator *as_break_iterator(reskia_break_iterator_t *iterator) {
    return reinterpret_cast<SkBreakIterator *>(iterator);
}

bool valid_direction(reskia_unicode_bidi_direction_t direction) {
    return direction == RESKIA_UNICODE_BIDI_DIRECTION_LTR ||
           direction == RESKIA_UNICODE_BIDI_DIRECTION_RTL;
}

SkBidiIterator::Direction as_direction(reskia_unicode_bidi_direction_t direction) {
    return direction == RESKIA_UNICODE_BIDI_DIRECTION_RTL ? SkBidiIterator::kRTL : SkBidiIterator::kLTR;
}

bool valid_break_type(reskia_unicode_break_type_t type) {
    return type >= RESKIA_UNICODE_BREAK_TYPE_WORDS &&
           type <= RESKIA_UNICODE_BREAK_TYPE_SENTENCES;
}

SkUnicode::BreakType as_break_type(reskia_unicode_break_type_t type) {
    switch (type) {
        case RESKIA_UNICODE_BREAK_TYPE_WORDS:
            return SkUnicode::BreakType::kWords;
        case RESKIA_UNICODE_BREAK_TYPE_GRAPHEMES:
            return SkUnicode::BreakType::kGraphemes;
        case RESKIA_UNICODE_BREAK_TYPE_LINES:
            return SkUnicode::BreakType::kLines;
        case RESKIA_UNICODE_BREAK_TYPE_SENTENCES:
            return SkUnicode::BreakType::kSentences;
        default:
            return SkUnicode::BreakType::kGraphemes;
    }
}

reskia_unicode_t *release_unicode(std::unique_ptr<SkUnicode> unicode) {
    return reinterpret_cast<reskia_unicode_t *>(unicode.release());
}

reskia_bidi_iterator_t *release_bidi_iterator(std::unique_ptr<SkBidiIterator> iterator) {
    return reinterpret_cast<reskia_bidi_iterator_t *>(iterator.release());
}

reskia_break_iterator_t *release_break_iterator(std::unique_ptr<SkBreakIterator> iterator) {
    return reinterpret_cast<reskia_break_iterator_t *>(iterator.release());
}

std::vector<SkUnicode::Position> make_positions(const size_t *positions, int32_t count) {
    std::vector<SkUnicode::Position> out;
    out.reserve(static_cast<size_t>(count));
    for (int32_t i = 0; i < count; ++i) {
        out.push_back(positions[i]);
    }
    return out;
}

std::vector<SkUnicode::LineBreakBefore> make_line_breaks(const size_t *positions, int32_t count) {
    std::vector<SkUnicode::LineBreakBefore> out;
    out.reserve(static_cast<size_t>(count));
    for (int32_t i = 0; i < count; ++i) {
        out.emplace_back(positions[i], SkUnicode::LineBreakType::kSoftLineBreak);
    }
    return out;
}

}  // namespace

extern "C" {

reskia_unicode_t *SkUnicode_Make(void) {
    return release_unicode(SkUnicode::Make());
}

reskia_unicode_t *SkUnicode_MakeIcuBasedUnicode(void) {
#if defined(SK_UNICODE_ICU_IMPLEMENTATION)
    return release_unicode(SkUnicode::MakeIcuBasedUnicode());
#else
    return nullptr;
#endif
}

reskia_unicode_t *SkUnicode_MakeClientBasedUnicode(const char *text, int32_t text_units, const size_t *words, int32_t words_count, const size_t *grapheme_breaks, int32_t grapheme_breaks_count, const size_t *line_breaks, int32_t line_breaks_count) {
    if (text_units < 0 || words_count < 0 || grapheme_breaks_count < 0 || line_breaks_count < 0 ||
        (text == nullptr && text_units != 0) ||
        (words == nullptr && words_count != 0) ||
        (grapheme_breaks == nullptr && grapheme_breaks_count != 0) ||
        (line_breaks == nullptr && line_breaks_count != 0)) {
        return nullptr;
    }
#if defined(SK_UNICODE_ICU_IMPLEMENTATION)
    std::string text_copy;
    if (text_units > 0) {
        text_copy.assign(text, static_cast<size_t>(text_units));
    }
    return release_unicode(SkUnicode::MakeClientBasedUnicode(
            SkSpan<char>(text_copy.data(), text_copy.size()),
            make_positions(words, words_count),
            make_positions(grapheme_breaks, grapheme_breaks_count),
            make_line_breaks(line_breaks, line_breaks_count)));
#else
    return nullptr;
#endif
}

reskia_unicode_t *SkUnicode_MakeLibgraphemeBasedUnicode(void) {
#if defined(SK_UNICODE_LIBGRAPHEME_IMPLEMENTATION)
    return release_unicode(SkUnicode::MakeLibgraphemeBasedUnicode());
#else
    return nullptr;
#endif
}

reskia_unicode_t *SkUnicode_MakeIcu4xBasedUnicode(void) {
#if defined(SK_UNICODE_ICU4X_IMPLEMENTATION)
    return release_unicode(SkUnicode::MakeIcu4xBasedUnicode());
#else
    return nullptr;
#endif
}

void SkUnicode_delete(reskia_unicode_t *unicode) {
    delete as_unicode(unicode);
}

reskia_unicode_t *SkUnicode_copy(reskia_unicode_t *unicode) {
    if (unicode == nullptr) {
        return nullptr;
    }
    return release_unicode(as_unicode(unicode)->copy());
}

reskia_string_t *SkUnicode_toUpper(reskia_unicode_t *unicode, const reskia_string_t *text) {
    if (unicode == nullptr || text == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_string_t *>(new SkString(as_unicode(unicode)->toUpper(*as_string(text))));
}

bool SkUnicode_isControl(reskia_unicode_t *unicode, reskia_unichar_t unichar) {
    return unicode != nullptr && as_unicode(unicode)->isControl(unichar);
}

bool SkUnicode_isWhitespace(reskia_unicode_t *unicode, reskia_unichar_t unichar) {
    return unicode != nullptr && as_unicode(unicode)->isWhitespace(unichar);
}

bool SkUnicode_isSpace(reskia_unicode_t *unicode, reskia_unichar_t unichar) {
    return unicode != nullptr && as_unicode(unicode)->isSpace(unichar);
}

bool SkUnicode_isTabulation(reskia_unicode_t *unicode, reskia_unichar_t unichar) {
    return unicode != nullptr && as_unicode(unicode)->isTabulation(unichar);
}

bool SkUnicode_isHardBreak(reskia_unicode_t *unicode, reskia_unichar_t unichar) {
    return unicode != nullptr && as_unicode(unicode)->isHardBreak(unichar);
}

bool SkUnicode_isEmoji(reskia_unicode_t *unicode, reskia_unichar_t unichar) {
    return unicode != nullptr && as_unicode(unicode)->isEmoji(unichar);
}

bool SkUnicode_isIdeographic(reskia_unicode_t *unicode, reskia_unichar_t unichar) {
    return unicode != nullptr && as_unicode(unicode)->isIdeographic(unichar);
}

bool SkUnicode_hasTabulationFlag(reskia_unicode_code_unit_flags_t flags) {
    return SkUnicode::hasTabulationFlag(as_flags(flags));
}

bool SkUnicode_hasHardLineBreakFlag(reskia_unicode_code_unit_flags_t flags) {
    return SkUnicode::hasHardLineBreakFlag(as_flags(flags));
}

bool SkUnicode_hasSoftLineBreakFlag(reskia_unicode_code_unit_flags_t flags) {
    return SkUnicode::hasSoftLineBreakFlag(as_flags(flags));
}

bool SkUnicode_hasGraphemeStartFlag(reskia_unicode_code_unit_flags_t flags) {
    return SkUnicode::hasGraphemeStartFlag(as_flags(flags));
}

bool SkUnicode_hasControlFlag(reskia_unicode_code_unit_flags_t flags) {
    return SkUnicode::hasControlFlag(as_flags(flags));
}

bool SkUnicode_hasPartOfWhiteSpaceBreakFlag(reskia_unicode_code_unit_flags_t flags) {
    return SkUnicode::hasPartOfWhiteSpaceBreakFlag(as_flags(flags));
}

reskia_string_t *SkUnicode_convertUtf16ToUtf8(const uint16_t *utf16, int32_t utf16_units) {
    if (utf16 == nullptr && utf16_units != 0) {
        return nullptr;
    }
    SkString result = SkUnicode::convertUtf16ToUtf8(reinterpret_cast<const char16_t *>(utf16), utf16_units);
    return reinterpret_cast<reskia_string_t *>(new SkString(result));
}

int32_t SkUnicode_convertUtf8ToUtf16(const char *utf8, int32_t utf8_units, uint16_t *dst, int32_t dst_units) {
    if (utf8 == nullptr && utf8_units != 0) {
        return -1;
    }
    std::u16string result = SkUnicode::convertUtf8ToUtf16(utf8, utf8_units);
    if (dst != nullptr && dst_units > 0) {
        const int32_t copy_units = std::min<int32_t>(dst_units, static_cast<int32_t>(result.size()));
        std::copy_n(reinterpret_cast<const uint16_t *>(result.data()), copy_units, dst);
    }
    return static_cast<int32_t>(result.size());
}

reskia_bidi_iterator_t *SkUnicode_makeBidiIteratorUtf8(reskia_unicode_t *unicode, const char *text, int32_t count, reskia_unicode_bidi_direction_t direction) {
    if (unicode == nullptr || (text == nullptr && count != 0) || count < 0 || !valid_direction(direction)) {
        return nullptr;
    }
    return release_bidi_iterator(as_unicode(unicode)->makeBidiIterator(text, count, as_direction(direction)));
}

reskia_bidi_iterator_t *SkUnicode_makeBidiIteratorUtf16(reskia_unicode_t *unicode, const uint16_t *text, int32_t count, reskia_unicode_bidi_direction_t direction) {
    if (unicode == nullptr || (text == nullptr && count != 0) || count < 0 || !valid_direction(direction)) {
        return nullptr;
    }
    return release_bidi_iterator(as_unicode(unicode)->makeBidiIterator(text, count, as_direction(direction)));
}

void SkBidiIterator_delete(reskia_bidi_iterator_t *iterator) {
    delete as_bidi_iterator(iterator);
}

int32_t SkBidiIterator_getLength(reskia_bidi_iterator_t *iterator) {
    if (iterator == nullptr) {
        return -1;
    }
    return as_bidi_iterator(iterator)->getLength();
}

uint8_t SkBidiIterator_getLevelAt(reskia_bidi_iterator_t *iterator, int32_t position) {
    if (iterator == nullptr) {
        return 0;
    }
    return as_bidi_iterator(iterator)->getLevelAt(position);
}

reskia_break_iterator_t *SkUnicode_makeBreakIterator(reskia_unicode_t *unicode, reskia_unicode_break_type_t type) {
    if (unicode == nullptr || !valid_break_type(type)) {
        return nullptr;
    }
    return release_break_iterator(as_unicode(unicode)->makeBreakIterator(as_break_type(type)));
}

reskia_break_iterator_t *SkUnicode_makeBreakIteratorWithLocale(reskia_unicode_t *unicode, const char *locale, reskia_unicode_break_type_t type) {
    if (unicode == nullptr || !valid_break_type(type)) {
        return nullptr;
    }
    if (locale == nullptr) {
        return release_break_iterator(as_unicode(unicode)->makeBreakIterator(as_break_type(type)));
    }
    return release_break_iterator(as_unicode(unicode)->makeBreakIterator(locale, as_break_type(type)));
}

void SkBreakIterator_delete(reskia_break_iterator_t *iterator) {
    delete as_break_iterator(iterator);
}

int32_t SkBreakIterator_first(reskia_break_iterator_t *iterator) {
    if (iterator == nullptr) {
        return -1;
    }
    return as_break_iterator(iterator)->first();
}

int32_t SkBreakIterator_current(reskia_break_iterator_t *iterator) {
    if (iterator == nullptr) {
        return -1;
    }
    return as_break_iterator(iterator)->current();
}

int32_t SkBreakIterator_next(reskia_break_iterator_t *iterator) {
    if (iterator == nullptr) {
        return -1;
    }
    return as_break_iterator(iterator)->next();
}

int32_t SkBreakIterator_status(reskia_break_iterator_t *iterator) {
    if (iterator == nullptr) {
        return -1;
    }
    return as_break_iterator(iterator)->status();
}

bool SkBreakIterator_isDone(reskia_break_iterator_t *iterator) {
    return iterator == nullptr || as_break_iterator(iterator)->isDone();
}

bool SkBreakIterator_setTextUtf8(reskia_break_iterator_t *iterator, const char *text, int32_t units) {
    if (iterator == nullptr || (text == nullptr && units != 0) || units < 0) {
        return false;
    }
    return as_break_iterator(iterator)->setText(text, units);
}

bool SkBreakIterator_setTextUtf16(reskia_break_iterator_t *iterator, const uint16_t *text, int32_t units) {
    if (iterator == nullptr || (text == nullptr && units != 0) || units < 0) {
        return false;
    }
    return as_break_iterator(iterator)->setText(reinterpret_cast<const char16_t *>(text), units);
}

int32_t SkUnicode_getBidiRegions(reskia_unicode_t *unicode, const char *utf8, int32_t utf8_units, reskia_unicode_bidi_direction_t direction, reskia_unicode_bidi_region_t *dst, int32_t dst_count) {
    if (unicode == nullptr || (utf8 == nullptr && utf8_units != 0) || utf8_units < 0 || dst_count < 0 || !valid_direction(direction)) {
        return -1;
    }
    std::vector<SkUnicode::BidiRegion> regions;
    const auto text_direction = direction == RESKIA_UNICODE_BIDI_DIRECTION_RTL ? SkUnicode::TextDirection::kRTL : SkUnicode::TextDirection::kLTR;
    if (!as_unicode(unicode)->getBidiRegions(utf8, utf8_units, text_direction, &regions)) {
        return -1;
    }
    if (dst != nullptr && dst_count > 0) {
        const int32_t copy_count = std::min<int32_t>(dst_count, static_cast<int32_t>(regions.size()));
        for (int32_t i = 0; i < copy_count; ++i) {
            dst[i].start = regions[i].start;
            dst[i].end = regions[i].end;
            dst[i].level = regions[i].level;
        }
    }
    return static_cast<int32_t>(regions.size());
}

int32_t SkUnicode_getWords(reskia_unicode_t *unicode, const char *utf8, int32_t utf8_units, const char *locale, size_t *dst, int32_t dst_count) {
    if (unicode == nullptr || (utf8 == nullptr && utf8_units != 0) || utf8_units < 0 || dst_count < 0) {
        return -1;
    }
    std::vector<SkUnicode::Position> positions;
    if (!as_unicode(unicode)->getWords(utf8, utf8_units, locale, &positions)) {
        return -1;
    }
    if (dst != nullptr && dst_count > 0) {
        const int32_t copy_count = std::min<int32_t>(dst_count, static_cast<int32_t>(positions.size()));
        std::copy_n(positions.data(), copy_count, dst);
    }
    return static_cast<int32_t>(positions.size());
}

int32_t SkUnicode_getUtf8Words(reskia_unicode_t *unicode, const char *utf8, int32_t utf8_units, const char *locale, size_t *dst, int32_t dst_count) {
    if (unicode == nullptr || (utf8 == nullptr && utf8_units != 0) || utf8_units < 0 || dst_count < 0) {
        return -1;
    }
    std::vector<SkUnicode::Position> positions;
    if (!as_unicode(unicode)->getUtf8Words(utf8, utf8_units, locale, &positions)) {
        return -1;
    }
    if (dst != nullptr && dst_count > 0) {
        const int32_t copy_count = std::min<int32_t>(dst_count, static_cast<int32_t>(positions.size()));
        std::copy_n(positions.data(), copy_count, dst);
    }
    return static_cast<int32_t>(positions.size());
}

int32_t SkUnicode_getSentences(reskia_unicode_t *unicode, const char *utf8, int32_t utf8_units, const char *locale, size_t *dst, int32_t dst_count) {
    if (unicode == nullptr || (utf8 == nullptr && utf8_units != 0) || utf8_units < 0 || dst_count < 0) {
        return -1;
    }
    std::vector<SkUnicode::Position> positions;
    if (!as_unicode(unicode)->getSentences(utf8, utf8_units, locale, &positions)) {
        return -1;
    }
    if (dst != nullptr && dst_count > 0) {
        const int32_t copy_count = std::min<int32_t>(dst_count, static_cast<int32_t>(positions.size()));
        std::copy_n(positions.data(), copy_count, dst);
    }
    return static_cast<int32_t>(positions.size());
}

int32_t SkUnicode_computeCodeUnitFlagsUtf8(reskia_unicode_t *unicode, char *utf8, int32_t utf8_units, bool replace_tabs, reskia_unicode_code_unit_flags_t *dst, int32_t dst_count) {
    if (unicode == nullptr || (utf8 == nullptr && utf8_units != 0) || utf8_units < 0 || dst_count < 0) {
        return -1;
    }
    skia_private::TArray<SkUnicode::CodeUnitFlags, true> flags;
    if (!as_unicode(unicode)->computeCodeUnitFlags(utf8, utf8_units, replace_tabs, &flags)) {
        return -1;
    }
    if (dst != nullptr && dst_count > 0) {
        const int32_t copy_count = std::min<int32_t>(dst_count, flags.size());
        for (int32_t i = 0; i < copy_count; ++i) {
            dst[i] = static_cast<reskia_unicode_code_unit_flags_t>(flags[i]);
        }
    }
    return flags.size();
}

int32_t SkUnicode_computeCodeUnitFlagsUtf16(reskia_unicode_t *unicode, uint16_t *utf16, int32_t utf16_units, bool replace_tabs, reskia_unicode_code_unit_flags_t *dst, int32_t dst_count) {
    if (unicode == nullptr || (utf16 == nullptr && utf16_units != 0) || utf16_units < 0 || dst_count < 0) {
        return -1;
    }
    skia_private::TArray<SkUnicode::CodeUnitFlags, true> flags;
    if (!as_unicode(unicode)->computeCodeUnitFlags(reinterpret_cast<char16_t *>(utf16), utf16_units, replace_tabs, &flags)) {
        return -1;
    }
    if (dst != nullptr && dst_count > 0) {
        const int32_t copy_count = std::min<int32_t>(dst_count, flags.size());
        for (int32_t i = 0; i < copy_count; ++i) {
            dst[i] = static_cast<reskia_unicode_code_unit_flags_t>(flags[i]);
        }
    }
    return flags.size();
}

bool SkUnicode_reorderVisual(reskia_unicode_t *unicode, const uint8_t *run_levels, int32_t levels_count, int32_t *logical_from_visual) {
    if (unicode == nullptr || run_levels == nullptr || logical_from_visual == nullptr || levels_count < 0) {
        return false;
    }
    as_unicode(unicode)->reorderVisual(run_levels, levels_count, logical_from_visual);
    return true;
}

}
