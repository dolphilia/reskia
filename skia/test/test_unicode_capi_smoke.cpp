#include <cstdio>
#include <cstring>

#include "capi/sk_string.h"
#include "capi/sk_unicode.h"

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[unicode-capi-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool smoke_unicode_static_helpers() {
    if (!check(SkUnicode_hasTabulationFlag(RESKIA_UNICODE_TABULATION), "has tabulation flag") ||
        !check(!SkUnicode_hasTabulationFlag(RESKIA_UNICODE_CONTROL), "does not have tabulation flag") ||
        !check(SkUnicode_hasHardLineBreakFlag(RESKIA_UNICODE_HARD_LINE_BREAK_BEFORE), "has hard line break flag") ||
        !check(SkUnicode_hasSoftLineBreakFlag(RESKIA_UNICODE_SOFT_LINE_BREAK_BEFORE), "has soft line break flag") ||
        !check(SkUnicode_hasGraphemeStartFlag(RESKIA_UNICODE_GRAPHEME_START), "has grapheme start flag") ||
        !check(SkUnicode_hasControlFlag(RESKIA_UNICODE_CONTROL), "has control flag") ||
        !check(SkUnicode_hasPartOfWhiteSpaceBreakFlag(RESKIA_UNICODE_PART_OF_WHITE_SPACE_BREAK), "has whitespace break flag")) {
        return false;
    }

    const uint16_t utf16[] = {'H', 'i'};
    reskia_string_t *utf8 = SkUnicode_convertUtf16ToUtf8(utf16, 2);
    if (!check(utf8 != nullptr, "convertUtf16ToUtf8") ||
        !check(SkString_equalsTextWithLength(utf8, "Hi", 2), "convertUtf16ToUtf8 contents")) {
        SkString_delete(utf8);
        return false;
    }
    SkString_delete(utf8);

    uint16_t output[4] = {};
    int32_t required = SkUnicode_convertUtf8ToUtf16("Hi", 2, output, 4);
    reskia_unicode_bidi_region_t regions[4] = {};
    reskia_unicode_t *icu_unicode = SkUnicodes_ICU_Make();
    int32_t bidi_count = SkUnicode_extractBidi("abc", 3, RESKIA_UNICODE_BIDI_DIRECTION_LTR, regions, 4);
    bool ok = check(required == 2, "convertUtf8ToUtf16 required units") &&
              check(output[0] == 'H' && output[1] == 'i', "convertUtf8ToUtf16 contents") &&
              check(SkUnicode_convertUtf16ToUtf8(nullptr, 1) == nullptr, "convertUtf16ToUtf8 null nonzero") &&
              check(SkUnicode_convertUtf8ToUtf16(nullptr, 1, nullptr, 0) == -1, "convertUtf8ToUtf16 null nonzero") &&
              check(icu_unicode != nullptr ? bidi_count >= 0 : bidi_count == -1, "extractBidi backend availability") &&
              check(SkUnicode_extractBidi(nullptr, 1, RESKIA_UNICODE_BIDI_DIRECTION_LTR, nullptr, 0) == -1, "extractBidi null nonzero");
    SkUnicode_delete(icu_unicode);
    return ok;
}

bool smoke_unicode_instance_helpers() {
    if (!check(SkUnicodes_Client_Make(nullptr, 1, nullptr, 0, nullptr, 0, nullptr, 0) == nullptr, "client unicode null text") ||
        !check(SkUnicodes_Client_Make("", 0, nullptr, 1, nullptr, 0, nullptr, 0) == nullptr, "client unicode null words") ||
        !check(SkUnicode_toUpper(nullptr, nullptr) == nullptr, "toUpper null") ||
        !check(SkUnicode_makeBidiIteratorUtf8(nullptr, "abc", 3, RESKIA_UNICODE_BIDI_DIRECTION_LTR) == nullptr, "bidi iterator null unicode") ||
        !check(SkUnicode_makeBidiIteratorUtf8(nullptr, nullptr, 1, RESKIA_UNICODE_BIDI_DIRECTION_LTR) == nullptr, "bidi iterator null text") ||
        !check(SkUnicode_makeBidiIteratorUtf16(nullptr, nullptr, 1, RESKIA_UNICODE_BIDI_DIRECTION_LTR) == nullptr, "bidi iterator utf16 null text") ||
        !check(SkBidiIterator_getLength(nullptr) == -1, "bidi length null") ||
        !check(SkBidiIterator_getLevelAt(nullptr, 0) == 0, "bidi level null") ||
        !check(SkUnicode_makeBreakIterator(nullptr, RESKIA_UNICODE_BREAK_TYPE_WORDS) == nullptr, "break iterator null unicode") ||
        !check(SkBreakIterator_first(nullptr) == -1, "break first null") ||
        !check(SkBreakIterator_current(nullptr) == -1, "break current null") ||
        !check(SkBreakIterator_next(nullptr) == -1, "break next null") ||
        !check(SkBreakIterator_status(nullptr) == -1, "break status null") ||
        !check(SkBreakIterator_isDone(nullptr), "break isDone null") ||
        !check(!SkBreakIterator_setTextUtf8(nullptr, "abc", 3), "break setText utf8 null iterator") ||
        !check(!SkBreakIterator_setTextUtf16(nullptr, nullptr, 1), "break setText utf16 null iterator") ||
        !check(SkUnicode_getBidiRegions(nullptr, "abc", 3, RESKIA_UNICODE_BIDI_DIRECTION_LTR, nullptr, 0) == -1, "getBidiRegions null") ||
        !check(SkUnicode_getWords(nullptr, "abc", 3, nullptr, nullptr, 0) == -1, "getWords null") ||
        !check(SkUnicode_getUtf8Words(nullptr, "abc", 3, nullptr, nullptr, 0) == -1, "getUtf8Words null") ||
        !check(SkUnicode_getSentences(nullptr, "abc", 3, nullptr, nullptr, 0) == -1, "getSentences null") ||
        !check(SkUnicode_computeCodeUnitFlagsUtf8(nullptr, nullptr, 0, false, nullptr, 0) == -1, "compute utf8 flags null") ||
        !check(SkUnicode_computeCodeUnitFlagsUtf16(nullptr, nullptr, 0, false, nullptr, 0) == -1, "compute utf16 flags null") ||
        !check(!SkUnicode_reorderVisual(nullptr, nullptr, 0, nullptr), "reorderVisual null") ||
        !check(!SkUnicode_isControl(nullptr, 0), "isControl null") ||
        !check(!SkUnicode_isWhitespace(nullptr, ' '), "isWhitespace null") ||
        !check(!SkUnicode_isSpace(nullptr, ' '), "isSpace null") ||
        !check(!SkUnicode_isTabulation(nullptr, '\t'), "isTabulation null") ||
        !check(!SkUnicode_isHardBreak(nullptr, '\n'), "isHardBreak null") ||
        !check(!SkUnicode_isEmoji(nullptr, 0x1f600), "isEmoji null") ||
        !check(!SkUnicode_isIdeographic(nullptr, 0x4e00), "isIdeographic null")) {
        return false;
    }

    reskia_unicode_t *unicode = SkUnicodes_ICU_Make();
    reskia_unicode_t *icu_unicode = SkUnicodes_ICU_Make();
    SkUnicode_delete(icu_unicode);
    const size_t words[] = {0, 3};
    const size_t grapheme_breaks[] = {0, 1, 2};
    const size_t line_breaks[] = {3};
    reskia_unicode_t *client_unicode = SkUnicodes_Client_Make("abc", 3, words, 2, grapheme_breaks, 3, line_breaks, 1);
    SkUnicode_delete(client_unicode);
    reskia_unicode_t *libgrapheme_unicode = SkUnicodes_Libgrapheme_Make();
    SkUnicode_delete(libgrapheme_unicode);
    reskia_unicode_t *icu4x_unicode = SkUnicodes_ICU4X_Make();
    SkUnicode_delete(icu4x_unicode);
    if (unicode == nullptr) {
        return true;
    }

    if (!check(SkUnicode_isWhitespace(unicode, ' '), "isWhitespace space") ||
        !check(SkUnicode_isSpace(unicode, ' '), "isSpace space") ||
        !check(SkUnicode_isTabulation(unicode, '\t'), "isTabulation tab") ||
        !check(SkUnicode_isHardBreak(unicode, '\n'), "isHardBreak newline")) {
        SkUnicode_delete(unicode);
        return false;
    }

    reskia_bidi_iterator_t *bidi = SkUnicode_makeBidiIteratorUtf8(unicode, "abc", 3, RESKIA_UNICODE_BIDI_DIRECTION_LTR);
    if (bidi != nullptr) {
        if (!check(SkBidiIterator_getLength(bidi) >= 0, "bidi length")) {
            SkBidiIterator_delete(bidi);
            SkUnicode_delete(unicode);
            return false;
        }
        (void)SkBidiIterator_getLevelAt(bidi, 0);
        SkBidiIterator_delete(bidi);
    }

    const uint16_t utf16[] = {'a', 'b', 'c'};
    bidi = SkUnicode_makeBidiIteratorUtf16(unicode, utf16, 3, RESKIA_UNICODE_BIDI_DIRECTION_LTR);
    if (bidi != nullptr) {
        if (!check(SkBidiIterator_getLength(bidi) >= 0, "bidi utf16 length")) {
            SkBidiIterator_delete(bidi);
            SkUnicode_delete(unicode);
            return false;
        }
        SkBidiIterator_delete(bidi);
    }

    reskia_break_iterator_t *break_iterator = SkUnicode_makeBreakIterator(unicode, RESKIA_UNICODE_BREAK_TYPE_GRAPHEMES);
    if (break_iterator != nullptr) {
        if (!check(SkBreakIterator_setTextUtf8(break_iterator, "abc", 3), "break setText utf8") ||
            !check(SkBreakIterator_first(break_iterator) >= 0, "break first") ||
            !check(SkBreakIterator_current(break_iterator) >= 0, "break current") ||
            !check(SkBreakIterator_status(break_iterator) >= 0, "break status")) {
            SkBreakIterator_delete(break_iterator);
            SkUnicode_delete(unicode);
            return false;
        }
        (void)SkBreakIterator_next(break_iterator);
        (void)SkBreakIterator_isDone(break_iterator);
        SkBreakIterator_delete(break_iterator);
    }

    reskia_unicode_bidi_region_t regions[8] = {};
    int32_t region_count = SkUnicode_getBidiRegions(unicode, "abc", 3, RESKIA_UNICODE_BIDI_DIRECTION_LTR, regions, 8);
    if (!check(region_count >= 0, "getBidiRegions")) {
        SkUnicode_delete(unicode);
        return false;
    }

    size_t positions[16] = {};
    int32_t position_count = SkUnicode_getWords(unicode, "abc def", 7, nullptr, positions, 16);
    if (!check(position_count >= 0, "getWords")) {
        SkUnicode_delete(unicode);
        return false;
    }
    (void)SkUnicode_getUtf8Words(unicode, "abc def", 7, nullptr, positions, 16);
    (void)SkUnicode_getSentences(unicode, "One. Two.", 9, nullptr, positions, 16);

    char flag_text[] = "a\tb";
    reskia_unicode_code_unit_flags_t flags[8] = {};
    int32_t flag_count = SkUnicode_computeCodeUnitFlagsUtf8(unicode, flag_text, 3, false, flags, 8);
    if (!check(flag_count >= 0, "computeCodeUnitFlags utf8")) {
        SkUnicode_delete(unicode);
        return false;
    }

    uint16_t flag_text16[] = {'a', 'b'};
    (void)SkUnicode_computeCodeUnitFlagsUtf16(unicode, flag_text16, 2, false, flags, 8);

    const uint8_t levels[] = {0, 1};
    int32_t logical_from_visual[] = {-1, -1};
    if (!check(SkUnicode_reorderVisual(unicode, levels, 2, logical_from_visual), "reorderVisual")) {
        SkUnicode_delete(unicode);
        return false;
    }

    SkUnicode_delete(unicode);
    return true;
}

}  // namespace

int main() {
    return smoke_unicode_static_helpers() && smoke_unicode_instance_helpers() ? 0 : 1;
}
