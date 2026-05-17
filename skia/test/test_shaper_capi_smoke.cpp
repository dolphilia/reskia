#include <cstdio>
#include <cstring>

#include "capi/sk_font.h"
#include "capi/sk_point.h"
#include "capi/sk_shaper.h"
#include "capi/sk_text_blob_builder_run_handler.h"
#include "capi/sk_unicode.h"
#include "handles/static_sk_point.h"
#include "handles/static_sk_text_blob.h"

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[shaper-capi-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool smoke_null_inputs() {
    return check(SkShaper_MakeFontMgrRunIterator(nullptr, 1, nullptr, 0) == nullptr, "font iterator null") &&
           check(SkShaper_MakeBiDiRunIterator(nullptr, 1, 0) == nullptr, "bidi iterator null text") &&
           check(SkShaper_MakeScriptRunIterator(nullptr, 1, 0) == nullptr, "script iterator null text") &&
           check(SkShaper_MakeStdLanguageRunIterator(nullptr, 1) == nullptr, "language iterator null text") &&
           check(!SkShaper_shape(nullptr, "abc", 3, nullptr, true, 100.0f, nullptr), "shape null") &&
           check(SkShaper_FontRunIterator_atEnd(nullptr), "font iterator null at end") &&
           check(SkShaper_BiDiRunIterator_currentLevel(nullptr) == 0, "bidi current null") &&
           check(SkShaper_ScriptRunIterator_currentScript(nullptr) == 0, "script current null") &&
           check(SkShaper_LanguageRunIterator_currentLanguage(nullptr) == nullptr, "language current null");
}

bool smoke_shape() {
    const char *text = u8"Hello שלום";
    const size_t text_size = std::strlen(text);

    reskia_shaper_t *shaper = SkShaper_Make();
    if (shaper == nullptr) {
        shaper = SkShaper_MakePrimitive();
    }
    if (!check(shaper != nullptr, "make shaper")) {
        return false;
    }

    reskia_shaper_t *primitive = SkShaper_MakePrimitive();
    SkShaper_delete(primitive);
    reskia_shaper_t *core_text = SkShaper_MakeCoreText();
    SkShaper_delete(core_text);
    reskia_shaper_t *shape_then_wrap = SkShaper_MakeShapeThenWrap(0);
    SkShaper_delete(shape_then_wrap);
    SkShaper_PurgeCaches();
    SkShaper_PurgeHarfBuzzCache();

    reskia_font_t *font = SkFont_new();
    sk_point_t offset = SkPoint_Make(0.0f, 24.0f);
    SkTextBlobBuilderRunHandler *handler = SkTextBlobBuilderRunHandler_new(text, offset);
    if (!check(font != nullptr, "font") ||
        !check(offset != 0, "offset") ||
        !check(handler != nullptr, "handler") ||
        !check(SkShaper_shape(shaper, text, text_size, font, true, 220.0f, handler), "shape simple")) {
        SkTextBlobBuilderRunHandler_delete(handler);
        static_sk_point_delete(offset);
        SkFont_delete(font);
        SkShaper_delete(shaper);
        return false;
    }

    sk_text_blob_t blob = SkTextBlobBuilderRunHandler_makeBlob(handler);
    if (!check(blob != 0, "blob")) {
        SkTextBlobBuilderRunHandler_delete(handler);
        static_sk_point_delete(offset);
        SkFont_delete(font);
        SkShaper_delete(shaper);
        return false;
    }
    static_sk_text_blob_delete(blob);
    SkTextBlobBuilderRunHandler_delete(handler);

    reskia_shaper_font_run_iterator_t *font_iterator = SkShaper_MakeFontMgrRunIterator(text, text_size, font, 0);
    reskia_shaper_bidi_run_iterator_t *bidi_iterator = SkShaper_MakeBiDiRunIterator(text, text_size, 0);
    reskia_shaper_script_run_iterator_t *script_iterator = SkShaper_MakeScriptRunIterator(text, text_size, 0x5a797979);
    reskia_shaper_language_run_iterator_t *language_iterator = SkShaper_MakeStdLanguageRunIterator(text, text_size);
    handler = SkTextBlobBuilderRunHandler_new(text, offset);
    if (!check(font_iterator != nullptr, "font iterator") ||
        !check(bidi_iterator != nullptr, "bidi iterator") ||
        !check(script_iterator != nullptr, "script iterator") ||
        !check(language_iterator != nullptr, "language iterator") ||
        !check(!SkShaper_BiDiRunIterator_atEnd(bidi_iterator), "bidi not at end") ||
        !check(SkShaper_BiDiRunIterator_currentLevel(bidi_iterator) == 0, "bidi level") ||
        !check(SkShaper_ScriptRunIterator_currentScript(script_iterator) == 0x5a797979, "script value") ||
        !check(SkShaper_LanguageRunIterator_currentLanguage(language_iterator) != nullptr, "language value") ||
        !check(SkShaper_shapeWithIterators(shaper, text, text_size, font_iterator, bidi_iterator, script_iterator, language_iterator, 220.0f, handler), "shape iterators")) {
        SkTextBlobBuilderRunHandler_delete(handler);
        SkShaper_FontRunIterator_delete(font_iterator);
        SkShaper_BiDiRunIterator_delete(bidi_iterator);
        SkShaper_ScriptRunIterator_delete(script_iterator);
        SkShaper_LanguageRunIterator_delete(language_iterator);
        static_sk_point_delete(offset);
        SkFont_delete(font);
        SkShaper_delete(shaper);
        return false;
    }
    blob = SkTextBlobBuilderRunHandler_makeBlob(handler);
    if (!check(blob != 0, "iterator blob")) {
        SkTextBlobBuilderRunHandler_delete(handler);
        SkShaper_FontRunIterator_delete(font_iterator);
        SkShaper_BiDiRunIterator_delete(bidi_iterator);
        SkShaper_ScriptRunIterator_delete(script_iterator);
        SkShaper_LanguageRunIterator_delete(language_iterator);
        static_sk_point_delete(offset);
        SkFont_delete(font);
        SkShaper_delete(shaper);
        return false;
    }
    static_sk_text_blob_delete(blob);
    SkTextBlobBuilderRunHandler_delete(handler);
    SkShaper_FontRunIterator_delete(font_iterator);
    SkShaper_BiDiRunIterator_delete(bidi_iterator);
    SkShaper_ScriptRunIterator_delete(script_iterator);
    SkShaper_LanguageRunIterator_delete(language_iterator);

    font_iterator = SkShaper_MakeFontMgrRunIterator(text, text_size, font, 0);
    bidi_iterator = SkShaper_MakeBiDiRunIterator(text, text_size, 0);
    script_iterator = SkShaper_MakeScriptRunIterator(text, text_size, 0x5a797979);
    language_iterator = SkShaper_MakeStdLanguageRunIterator(text, text_size);
    handler = SkTextBlobBuilderRunHandler_new(text, offset);
    const reskia_shaper_feature_t feature = {0x6b65726e, 1, 0, text_size};
    (void)SkShaper_shapeWithFeatures(shaper, text, text_size, font_iterator, bidi_iterator, script_iterator, language_iterator, &feature, 1, 220.0f, handler);
    blob = SkTextBlobBuilderRunHandler_makeBlob(handler);
    if (blob != 0) {
        static_sk_text_blob_delete(blob);
    }
    SkTextBlobBuilderRunHandler_delete(handler);
    SkShaper_FontRunIterator_delete(font_iterator);
    SkShaper_BiDiRunIterator_delete(bidi_iterator);
    SkShaper_ScriptRunIterator_delete(script_iterator);
    SkShaper_LanguageRunIterator_delete(language_iterator);

    reskia_shaper_t *dont_wrap = SkShaper_MakeShapeDontWrapOrReorder(nullptr, 0);
    SkShaper_delete(dont_wrap);

    static_sk_point_delete(offset);
    SkFont_delete(font);
    SkShaper_delete(shaper);
    return true;
}

} // namespace

int main() {
    return smoke_null_inputs() && smoke_shape() ? 0 : 1;
}
