//
// Created by Codex on 2026/05/17.
//

#ifndef RAIA_SKIA_SK_SHAPER_H
#define RAIA_SKIA_SK_SHAPER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "../handles/static_sk_font_mgr.h"

typedef struct reskia_font_t reskia_font_t;
typedef struct reskia_shaper_t reskia_shaper_t;
typedef struct reskia_shaper_font_run_iterator_t reskia_shaper_font_run_iterator_t;
typedef struct reskia_shaper_bidi_run_iterator_t reskia_shaper_bidi_run_iterator_t;
typedef struct reskia_shaper_script_run_iterator_t reskia_shaper_script_run_iterator_t;
typedef struct reskia_shaper_language_run_iterator_t reskia_shaper_language_run_iterator_t;
typedef struct reskia_unicode_t reskia_unicode_t;
typedef uint32_t reskia_four_byte_tag_t;

#ifdef __cplusplus
class SkTextBlobBuilderRunHandler;
#else
typedef struct SkTextBlobBuilderRunHandler SkTextBlobBuilderRunHandler;
#endif

typedef struct reskia_shaper_feature_t {
    reskia_four_byte_tag_t tag;
    uint32_t value;
    size_t start;
    size_t end;
} reskia_shaper_feature_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_shaper_t *SkShaper_Make(void);
reskia_shaper_t *SkShaper_MakeWithFontMgr(sk_font_mgr_t font_mgr);
reskia_shaper_t *SkShaper_MakePrimitive(void);
reskia_shaper_t *SkShaper_MakeShaperDrivenWrapper(sk_font_mgr_t font_mgr);
reskia_shaper_t *SkShaper_MakeShapeThenWrap(sk_font_mgr_t font_mgr);
reskia_shaper_t *SkShaper_MakeShapeDontWrapOrReorder(reskia_unicode_t *unicode, sk_font_mgr_t font_mgr); // consumes unicode on success
reskia_shaper_t *SkShaper_MakeCoreText(void);
void SkShaper_delete(reskia_shaper_t *shaper);
void SkShaper_PurgeCaches(void);
void SkShaper_PurgeHarfBuzzCache(void);

reskia_shaper_font_run_iterator_t *SkShaper_MakeFontMgrRunIterator(const char *utf8, size_t utf8_bytes, const reskia_font_t *font, sk_font_mgr_t fallback);
reskia_shaper_font_run_iterator_t *SkShaper_MakeFontMgrRunIteratorWithRequest(const char *utf8, size_t utf8_bytes, const reskia_font_t *font, sk_font_mgr_t fallback, const char *request_name, int32_t request_weight, int32_t request_width, int32_t request_slant, const reskia_shaper_language_run_iterator_t *language_iterator);
reskia_shaper_bidi_run_iterator_t *SkShaper_MakeBiDiRunIterator(const char *utf8, size_t utf8_bytes, uint8_t bidi_level);
reskia_shaper_bidi_run_iterator_t *SkShaper_MakeSkUnicodeBidiRunIterator(reskia_unicode_t *unicode, const char *utf8, size_t utf8_bytes, uint8_t bidi_level);
reskia_shaper_bidi_run_iterator_t *SkShaper_MakeIcuBiDiRunIterator(const char *utf8, size_t utf8_bytes, uint8_t bidi_level);
reskia_shaper_script_run_iterator_t *SkShaper_MakeScriptRunIterator(const char *utf8, size_t utf8_bytes, reskia_four_byte_tag_t script);
reskia_shaper_script_run_iterator_t *SkShaper_MakeSkUnicodeHbScriptRunIterator(const char *utf8, size_t utf8_bytes);
reskia_shaper_script_run_iterator_t *SkShaper_MakeSkUnicodeHbScriptRunIteratorWithScript(const char *utf8, size_t utf8_bytes, reskia_four_byte_tag_t script);
reskia_shaper_script_run_iterator_t *SkShaper_MakeHbIcuScriptRunIterator(const char *utf8, size_t utf8_bytes);
reskia_shaper_language_run_iterator_t *SkShaper_MakeStdLanguageRunIterator(const char *utf8, size_t utf8_bytes);

void SkShaper_FontRunIterator_delete(reskia_shaper_font_run_iterator_t *iterator);
void SkShaper_BiDiRunIterator_delete(reskia_shaper_bidi_run_iterator_t *iterator);
void SkShaper_ScriptRunIterator_delete(reskia_shaper_script_run_iterator_t *iterator);
void SkShaper_LanguageRunIterator_delete(reskia_shaper_language_run_iterator_t *iterator);

bool SkShaper_FontRunIterator_consume(reskia_shaper_font_run_iterator_t *iterator);
bool SkShaper_BiDiRunIterator_consume(reskia_shaper_bidi_run_iterator_t *iterator);
bool SkShaper_ScriptRunIterator_consume(reskia_shaper_script_run_iterator_t *iterator);
bool SkShaper_LanguageRunIterator_consume(reskia_shaper_language_run_iterator_t *iterator);
size_t SkShaper_FontRunIterator_endOfCurrentRun(reskia_shaper_font_run_iterator_t *iterator);
size_t SkShaper_BiDiRunIterator_endOfCurrentRun(reskia_shaper_bidi_run_iterator_t *iterator);
size_t SkShaper_ScriptRunIterator_endOfCurrentRun(reskia_shaper_script_run_iterator_t *iterator);
size_t SkShaper_LanguageRunIterator_endOfCurrentRun(reskia_shaper_language_run_iterator_t *iterator);
bool SkShaper_FontRunIterator_atEnd(reskia_shaper_font_run_iterator_t *iterator);
bool SkShaper_BiDiRunIterator_atEnd(reskia_shaper_bidi_run_iterator_t *iterator);
bool SkShaper_ScriptRunIterator_atEnd(reskia_shaper_script_run_iterator_t *iterator);
bool SkShaper_LanguageRunIterator_atEnd(reskia_shaper_language_run_iterator_t *iterator);
uint8_t SkShaper_BiDiRunIterator_currentLevel(reskia_shaper_bidi_run_iterator_t *iterator);
reskia_four_byte_tag_t SkShaper_ScriptRunIterator_currentScript(reskia_shaper_script_run_iterator_t *iterator);
const char *SkShaper_LanguageRunIterator_currentLanguage(reskia_shaper_language_run_iterator_t *iterator);

bool SkShaper_shape(reskia_shaper_t *shaper, const char *utf8, size_t utf8_bytes, const reskia_font_t *font, bool left_to_right, float width, SkTextBlobBuilderRunHandler *handler);
bool SkShaper_shapeWithIterators(reskia_shaper_t *shaper, const char *utf8, size_t utf8_bytes, reskia_shaper_font_run_iterator_t *font, reskia_shaper_bidi_run_iterator_t *bidi, reskia_shaper_script_run_iterator_t *script, reskia_shaper_language_run_iterator_t *language, float width, SkTextBlobBuilderRunHandler *handler);
bool SkShaper_shapeWithFeatures(reskia_shaper_t *shaper, const char *utf8, size_t utf8_bytes, reskia_shaper_font_run_iterator_t *font, reskia_shaper_bidi_run_iterator_t *bidi, reskia_shaper_script_run_iterator_t *script, reskia_shaper_language_run_iterator_t *language, const reskia_shaper_feature_t *features, size_t features_count, float width, SkTextBlobBuilderRunHandler *handler);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_SHAPER_H
