//
// Created by Codex on 2026/05/15.
//

#ifndef RAIA_SKIA_SK_UNICODE_H
#define RAIA_SKIA_SK_UNICODE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct reskia_string_t reskia_string_t;
typedef struct reskia_bidi_iterator_t reskia_bidi_iterator_t;
typedef struct reskia_break_iterator_t reskia_break_iterator_t;
typedef struct reskia_unicode_t reskia_unicode_t;
typedef int32_t reskia_unicode_code_unit_flags_t;
typedef int32_t reskia_unichar_t;
typedef int32_t reskia_unicode_bidi_direction_t;
typedef int32_t reskia_unicode_break_type_t;

typedef struct reskia_unicode_bidi_region_t {
    size_t start;
    size_t end;
    uint8_t level;
} reskia_unicode_bidi_region_t;

#ifdef __cplusplus
extern "C" {
#endif

enum {
    RESKIA_UNICODE_NO_CODE_UNIT_FLAG = 0x00,
    RESKIA_UNICODE_PART_OF_WHITE_SPACE_BREAK = 0x01,
    RESKIA_UNICODE_GRAPHEME_START = 0x02,
    RESKIA_UNICODE_SOFT_LINE_BREAK_BEFORE = 0x04,
    RESKIA_UNICODE_HARD_LINE_BREAK_BEFORE = 0x08,
    RESKIA_UNICODE_PART_OF_INTRA_WORD_BREAK = 0x10,
    RESKIA_UNICODE_CONTROL = 0x20,
    RESKIA_UNICODE_TABULATION = 0x40,
    RESKIA_UNICODE_GLYPH_CLUSTER_START = 0x80,
    RESKIA_UNICODE_IDEOGRAPHIC = 0x100,
    RESKIA_UNICODE_EMOJI = 0x200,
    RESKIA_UNICODE_WORD_BREAK = 0x400,
    RESKIA_UNICODE_SENTENCE_BREAK = 0x800,
};

enum {
    RESKIA_UNICODE_BIDI_DIRECTION_LTR = 0,
    RESKIA_UNICODE_BIDI_DIRECTION_RTL = 1,
};

enum {
    RESKIA_UNICODE_BREAK_TYPE_WORDS = 0,
    RESKIA_UNICODE_BREAK_TYPE_GRAPHEMES = 1,
    RESKIA_UNICODE_BREAK_TYPE_LINES = 2,
    RESKIA_UNICODE_BREAK_TYPE_SENTENCES = 3,
};

reskia_unicode_t *SkUnicode_Make(void); // owned: delete with SkUnicode_delete; returns NULL when no backend is available
reskia_unicode_t *SkUnicode_MakeIcuBasedUnicode(void); // owned; returns NULL when ICU backend is unavailable
reskia_unicode_t *SkUnicode_MakeClientBasedUnicode(const char *text, int32_t text_units, const size_t *words, int32_t words_count, const size_t *grapheme_breaks, int32_t grapheme_breaks_count, const size_t *line_breaks, int32_t line_breaks_count); // owned; returns NULL when client backend is unavailable
reskia_unicode_t *SkUnicode_MakeLibgraphemeBasedUnicode(void); // owned; returns NULL when libgrapheme backend is unavailable
reskia_unicode_t *SkUnicode_MakeIcu4xBasedUnicode(void); // owned; returns NULL when ICU4X backend is unavailable
void SkUnicode_delete(reskia_unicode_t *unicode); // NULL input is no-op
reskia_unicode_t *SkUnicode_copy(reskia_unicode_t *unicode); // owned: NULL input returns NULL
reskia_string_t *SkUnicode_toUpper(reskia_unicode_t *unicode, const reskia_string_t *text); // owned SkString; NULL input returns NULL
bool SkUnicode_isControl(reskia_unicode_t *unicode, reskia_unichar_t unichar); // NULL unicode returns false
bool SkUnicode_isWhitespace(reskia_unicode_t *unicode, reskia_unichar_t unichar); // NULL unicode returns false
bool SkUnicode_isSpace(reskia_unicode_t *unicode, reskia_unichar_t unichar); // NULL unicode returns false
bool SkUnicode_isTabulation(reskia_unicode_t *unicode, reskia_unichar_t unichar); // NULL unicode returns false
bool SkUnicode_isHardBreak(reskia_unicode_t *unicode, reskia_unichar_t unichar); // NULL unicode returns false
bool SkUnicode_isEmoji(reskia_unicode_t *unicode, reskia_unichar_t unichar); // NULL unicode returns false
bool SkUnicode_isIdeographic(reskia_unicode_t *unicode, reskia_unichar_t unichar); // NULL unicode returns false

bool SkUnicode_hasTabulationFlag(reskia_unicode_code_unit_flags_t flags);
bool SkUnicode_hasHardLineBreakFlag(reskia_unicode_code_unit_flags_t flags);
bool SkUnicode_hasSoftLineBreakFlag(reskia_unicode_code_unit_flags_t flags);
bool SkUnicode_hasGraphemeStartFlag(reskia_unicode_code_unit_flags_t flags);
bool SkUnicode_hasControlFlag(reskia_unicode_code_unit_flags_t flags);
bool SkUnicode_hasPartOfWhiteSpaceBreakFlag(reskia_unicode_code_unit_flags_t flags);
int32_t SkUnicode_extractBidi(const char *utf8, int32_t utf8_units, reskia_unicode_bidi_direction_t direction, reskia_unicode_bidi_region_t *dst, int32_t dst_count); // static helper; returns required region count; dst may be NULL

reskia_string_t *SkUnicode_convertUtf16ToUtf8(const uint16_t *utf16, int32_t utf16_units); // owned SkString; NULL input with non-zero units returns NULL
int32_t SkUnicode_convertUtf8ToUtf16(const char *utf8, int32_t utf8_units, uint16_t *dst, int32_t dst_units); // returns required UTF-16 units; dst may be NULL

reskia_bidi_iterator_t *SkUnicode_makeBidiIteratorUtf8(reskia_unicode_t *unicode, const char *text, int32_t count, reskia_unicode_bidi_direction_t direction); // owned; NULL input with non-zero count returns NULL
reskia_bidi_iterator_t *SkUnicode_makeBidiIteratorUtf16(reskia_unicode_t *unicode, const uint16_t *text, int32_t count, reskia_unicode_bidi_direction_t direction); // owned; NULL input with non-zero count returns NULL
void SkBidiIterator_delete(reskia_bidi_iterator_t *iterator); // NULL input is no-op
int32_t SkBidiIterator_getLength(reskia_bidi_iterator_t *iterator); // NULL input returns -1
uint8_t SkBidiIterator_getLevelAt(reskia_bidi_iterator_t *iterator, int32_t position); // NULL input returns 0

reskia_break_iterator_t *SkUnicode_makeBreakIterator(reskia_unicode_t *unicode, reskia_unicode_break_type_t type); // owned; NULL input returns NULL
reskia_break_iterator_t *SkUnicode_makeBreakIteratorWithLocale(reskia_unicode_t *unicode, const char *locale, reskia_unicode_break_type_t type); // owned; locale may be NULL
void SkBreakIterator_delete(reskia_break_iterator_t *iterator); // NULL input is no-op
int32_t SkBreakIterator_first(reskia_break_iterator_t *iterator); // NULL input returns -1
int32_t SkBreakIterator_current(reskia_break_iterator_t *iterator); // NULL input returns -1
int32_t SkBreakIterator_next(reskia_break_iterator_t *iterator); // NULL input returns -1
int32_t SkBreakIterator_status(reskia_break_iterator_t *iterator); // NULL input returns -1
bool SkBreakIterator_isDone(reskia_break_iterator_t *iterator); // NULL input returns true
bool SkBreakIterator_setTextUtf8(reskia_break_iterator_t *iterator, const char *text, int32_t units); // NULL text allowed only when units == 0
bool SkBreakIterator_setTextUtf16(reskia_break_iterator_t *iterator, const uint16_t *text, int32_t units); // NULL text allowed only when units == 0

int32_t SkUnicode_getBidiRegions(reskia_unicode_t *unicode, const char *utf8, int32_t utf8_units, reskia_unicode_bidi_direction_t direction, reskia_unicode_bidi_region_t *dst, int32_t dst_count); // returns required region count; dst may be NULL
int32_t SkUnicode_getWords(reskia_unicode_t *unicode, const char *utf8, int32_t utf8_units, const char *locale, size_t *dst, int32_t dst_count); // returns required position count; dst may be NULL
int32_t SkUnicode_getUtf8Words(reskia_unicode_t *unicode, const char *utf8, int32_t utf8_units, const char *locale, size_t *dst, int32_t dst_count); // returns required position count; dst may be NULL
int32_t SkUnicode_getSentences(reskia_unicode_t *unicode, const char *utf8, int32_t utf8_units, const char *locale, size_t *dst, int32_t dst_count); // returns required position count; dst may be NULL
int32_t SkUnicode_computeCodeUnitFlagsUtf8(reskia_unicode_t *unicode, char *utf8, int32_t utf8_units, bool replace_tabs, reskia_unicode_code_unit_flags_t *dst, int32_t dst_count); // returns required flag count; dst may be NULL
int32_t SkUnicode_computeCodeUnitFlagsUtf16(reskia_unicode_t *unicode, uint16_t *utf16, int32_t utf16_units, bool replace_tabs, reskia_unicode_code_unit_flags_t *dst, int32_t dst_count); // returns required flag count; dst may be NULL
bool SkUnicode_reorderVisual(reskia_unicode_t *unicode, const uint8_t *run_levels, int32_t levels_count, int32_t *logical_from_visual); // output array must have levels_count entries

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_UNICODE_H
