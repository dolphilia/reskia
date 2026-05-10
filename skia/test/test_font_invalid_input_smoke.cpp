#include "capi/sk_font.h"
#include "handles/static_sk_font.h"

#include <cstdio>
#include <cstdint>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[font-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

void glyph_path_counter(const reskia_path_t *, const reskia_matrix_t *, void *ctx) {
    auto *count = static_cast<int *>(ctx);
    if (count != nullptr) {
        ++*count;
    }
}

}  // namespace

int main() {
    SkFont_delete(nullptr);

    if (!check(!SkFont_equals(nullptr, nullptr), "SkFont_equals(nullptr, nullptr)")) {
        return 1;
    }
    if (!check(!SkFont_notEquals(nullptr, nullptr), "SkFont_notEquals(nullptr, nullptr)")) {
        return 2;
    }
    if (!check(!SkFont_isForceAutoHinting(nullptr), "SkFont_isForceAutoHinting(nullptr)")) {
        return 3;
    }
    if (!check(!SkFont_isEmbeddedBitmaps(nullptr), "SkFont_isEmbeddedBitmaps(nullptr)")) {
        return 4;
    }
    if (!check(!SkFont_isSubpixel(nullptr), "SkFont_isSubpixel(nullptr)")) {
        return 5;
    }
    if (!check(!SkFont_isLinearMetrics(nullptr), "SkFont_isLinearMetrics(nullptr)")) {
        return 6;
    }
    if (!check(!SkFont_isEmbolden(nullptr), "SkFont_isEmbolden(nullptr)")) {
        return 7;
    }
    if (!check(!SkFont_isBaselineSnap(nullptr), "SkFont_isBaselineSnap(nullptr)")) {
        return 8;
    }
    if (!check(SkFont_getEdging(nullptr) == -1, "SkFont_getEdging(nullptr)")) {
        return 9;
    }
    if (!check(SkFont_getHinting(nullptr) == -1, "SkFont_getHinting(nullptr)")) {
        return 10;
    }
    if (!check(SkFont_makeWithSize(nullptr, 12.0f) == 0, "SkFont_makeWithSize(nullptr)")) {
        return 11;
    }
    if (!check(SkFont_getTypeface(nullptr) == nullptr, "SkFont_getTypeface(nullptr)")) {
        return 12;
    }
    if (!check(SkFont_refTypeface(nullptr) == 0, "SkFont_refTypeface(nullptr)")) {
        return 13;
    }
    if (!check(SkFont_getSize(nullptr) == 0.0f, "SkFont_getSize(nullptr)")) {
        return 14;
    }
    if (!check(SkFont_getScaleX(nullptr) == 0.0f, "SkFont_getScaleX(nullptr)")) {
        return 15;
    }
    if (!check(SkFont_getSkewX(nullptr) == 0.0f, "SkFont_getSkewX(nullptr)")) {
        return 16;
    }

    SkFont_setForceAutoHinting(nullptr, true);
    SkFont_setEmbeddedBitmaps(nullptr, true);
    SkFont_setSubpixel(nullptr, true);
    SkFont_setLinearMetrics(nullptr, true);
    SkFont_setEmbolden(nullptr, true);
    SkFont_setBaselineSnap(nullptr, true);
    SkFont_setEdging(nullptr, 1);
    SkFont_setHinting(nullptr, 1);
    SkFont_setSize(nullptr, 12.0f);
    SkFont_setScaleX(nullptr, 1.0f);
    SkFont_setSkewX(nullptr, 0.0f);
    SkFont_getPaths(nullptr, nullptr, 0, nullptr, nullptr);
    SkFont_dump(nullptr);

    if (!check(SkFont_textToGlyphs(nullptr, nullptr, 0, 0, nullptr, 0) == 0, "SkFont_textToGlyphs(nullptr)")) {
        return 17;
    }
    if (!check(SkFont_unicharToGlyph(nullptr, 65) == 0, "SkFont_unicharToGlyph(nullptr)")) {
        return 18;
    }
    SkFont_unicharsToGlyphs(nullptr, nullptr, 0, nullptr);
    if (!check(SkFont_countText(nullptr, nullptr, 0, 0) == 0, "SkFont_countText(nullptr)")) {
        return 19;
    }
    if (!check(SkFont_measureText(nullptr, nullptr, 0, 0, nullptr) == 0.0f, "SkFont_measureText(nullptr)")) {
        return 20;
    }
    if (!check(SkFont_measureTextWithPaint(nullptr, nullptr, 0, 0, nullptr, nullptr) == 0.0f, "SkFont_measureTextWithPaint(nullptr)")) {
        return 21;
    }

    uint16_t glyph = 0;
    float scalar = 0.0f;
    SkFont_getWidths(nullptr, &glyph, 1, &scalar, nullptr);
    SkFont_getWidthsWithoutBounds(nullptr, &glyph, 1, &scalar);
    SkFont_getWidthsBounds(nullptr, &glyph, 1, &scalar, nullptr, nullptr);
    SkFont_getBounds(nullptr, &glyph, 1, nullptr, nullptr);
    SkFont_getPos(nullptr, &glyph, 1, nullptr, 0);
    SkFont_getXPos(nullptr, &glyph, 1, &scalar, 0.0f);
    if (!check(SkFont_getIntercepts(nullptr, &glyph, 1, nullptr, 0.0f, 1.0f, nullptr) == 0, "SkFont_getIntercepts(nullptr)")) {
        return 22;
    }
    if (!check(!SkFont_getPath(nullptr, 0, nullptr), "SkFont_getPath(nullptr)")) {
        return 23;
    }
    if (!check(SkFont_getMetrics(nullptr, nullptr) == 0.0f, "SkFont_getMetrics(nullptr)")) {
        return 24;
    }
    if (!check(SkFont_getSpacing(nullptr) == 0.0f, "SkFont_getSpacing(nullptr)")) {
        return 25;
    }

    auto *font = SkFont_new();
    if (!check(font != nullptr, "SkFont_new()")) {
        return 26;
    }
    if (!check(SkFont_equals(font, font), "SkFont_equals(valid self)")) {
        SkFont_delete(font);
        return 27;
    }
    if (!check(SkFont_getSize(font) > 0.0f, "SkFont_getSize(valid)")) {
        SkFont_delete(font);
        return 28;
    }
    SkFont_setSize(font, 18.0f);
    if (!check(SkFont_getSize(font) == 18.0f, "SkFont_setSize(valid)")) {
        SkFont_delete(font);
        return 29;
    }

    const sk_font_t sized_font_handle = SkFont_makeWithSize(font, 24.0f);
    if (!check(sized_font_handle != 0 && static_sk_font_get_ptr(sized_font_handle) != nullptr, "SkFont_makeWithSize(valid)")) {
        SkFont_delete(font);
        return 30;
    }
    static_sk_font_delete(sized_font_handle);

    const uint8_t text[] = {'A'};
    if (!check(SkFont_countText(font, text, sizeof(text), 0) == 1, "SkFont_countText(valid UTF8)")) {
        SkFont_delete(font);
        return 31;
    }
    if (!check(SkFont_textToGlyphs(font, text, sizeof(text), 0, nullptr, 0) == 1, "SkFont_textToGlyphs(count only)")) {
        SkFont_delete(font);
        return 32;
    }
    if (!check(SkFont_measureText(font, text, sizeof(text), 0, nullptr) >= 0.0f, "SkFont_measureText(valid)")) {
        SkFont_delete(font);
        return 33;
    }

    uint16_t glyphs[1] = {SkFont_unicharToGlyph(font, 65)};
    int path_callback_count = 0;
    SkFont_getPaths(font, nullptr, 1, glyph_path_counter, &path_callback_count);
    if (!check(path_callback_count == 0, "SkFont_getPaths(valid font, null glyphIDs)")) {
        SkFont_delete(font);
        return 34;
    }
    SkFont_getPaths(font, glyphs, 0, glyph_path_counter, &path_callback_count);
    if (!check(path_callback_count == 0, "SkFont_getPaths(valid font, zero count)")) {
        SkFont_delete(font);
        return 35;
    }
    SkFont_getPaths(font, glyphs, 1, nullptr, &path_callback_count);
    if (!check(path_callback_count == 0, "SkFont_getPaths(valid font, null callback)")) {
        SkFont_delete(font);
        return 36;
    }

    float widths[1] = {0.0f};
    SkFont_getWidthsWithoutBounds(font, glyphs, 1, widths);
    SkFont_getWidths(font, nullptr, 1, widths, nullptr);
    SkFont_getWidths(font, glyphs, 0, nullptr, nullptr);
    SkFont_getWidths(font, glyphs, -1, nullptr, nullptr);
    SkFont_getWidths(font, glyphs, 1, nullptr, nullptr);
    SkFont_getWidthsWithoutBounds(font, nullptr, 1, widths);
    SkFont_getWidthsWithoutBounds(font, glyphs, 0, nullptr);
    SkFont_getWidthsWithoutBounds(font, glyphs, 1, nullptr);
    SkFont_getWidthsBounds(font, nullptr, 1, widths, nullptr, nullptr);
    SkFont_getWidthsBounds(font, glyphs, 0, nullptr, nullptr, nullptr);
    SkFont_getWidthsBounds(font, glyphs, 1, nullptr, nullptr, nullptr);
    SkFont_getBounds(font, nullptr, 1, nullptr, nullptr);
    SkFont_getBounds(font, glyphs, 0, nullptr, nullptr);
    SkFont_getBounds(font, glyphs, 1, nullptr, nullptr);
    SkFont_delete(font);
    return 0;
}
