#include <cstdio>

#include "capi/sk_bitmap.h"
#include "capi/sk_canvas.h"
#include "capi/sk_font_mgr.h"
#include "capi/sk_graphics.h"
#include "capi/sk_paragraph_builder.h"
#include "capi/sk_paragraph_font_collection.h"
#include "capi/sk_paragraph_style.h"
#include "capi/sk_paragraph_text_style.h"
#include "capi/sk_string.h"
#include "handles/static_sk_font_mgr.h"

namespace {

constexpr uint32_t kWhite = 0xffffffff;
constexpr uint32_t kBlack = 0xff000000;

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[paragraph-builder-capi-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool has_non_white_pixel(reskia_bitmap_t *bitmap) {
    const int width = SkBitmap_width(bitmap);
    const int height = SkBitmap_height(bitmap);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (SkBitmap_getColor(bitmap, x, y) != kWhite) {
                return true;
            }
        }
    }
    return false;
}

bool smoke_null_inputs() {
    return check(SkParagraph_ParagraphBuilder_make(nullptr, nullptr) == nullptr, "make null") &&
           check(!SkParagraph_ParagraphBuilder_pushStyle(nullptr, nullptr), "push null") &&
           check(SkParagraph_ParagraphBuilder_peekStyle(nullptr) == nullptr, "peek null") &&
           check(!SkParagraph_ParagraphBuilder_addTextUtf8(nullptr, "x", 1), "add utf8 null") &&
           check(!SkParagraph_ParagraphBuilder_addTextUtf16(nullptr, nullptr, 0), "add utf16 null") &&
           check(!SkParagraph_ParagraphBuilder_addPlaceholder(nullptr, 1, 1, RESKIA_PARAGRAPH_PLACEHOLDER_ALIGNMENT_BASELINE, RESKIA_PARAGRAPH_TEXT_BASELINE_ALPHABETIC, 0), "placeholder null") &&
           check(SkParagraph_ParagraphBuilder_Build(nullptr) == nullptr, "build null") &&
           check(SkParagraph_ParagraphBuilder_getText(nullptr) == nullptr, "get text null") &&
           check(SkParagraph_ParagraphBuilder_getParagraphStyle(nullptr) == nullptr, "get style null") &&
           check(!SkParagraph_ParagraphBuilder_setWordsUtf8(nullptr, nullptr, 0), "set words null") &&
           check(SkParagraph_Paragraph_getHeight(nullptr) == 0.0f, "paragraph height null") &&
           check(!SkParagraph_Paragraph_layout(nullptr, 100), "layout null") &&
           check(!SkParagraph_Paragraph_paint(nullptr, nullptr, 0, 0), "paint null") &&
           check(SkParagraph_Paragraph_getRectsForRange(nullptr, 0, 1, RESKIA_PARAGRAPH_RECT_HEIGHT_STYLE_TIGHT, RESKIA_PARAGRAPH_RECT_WIDTH_STYLE_TIGHT, nullptr, 0) == -1, "rects range null") &&
           check(SkParagraph_Paragraph_getRectsForPlaceholders(nullptr, nullptr, 0) == -1, "rects placeholders null") &&
           check(!SkParagraph_Paragraph_getGlyphPositionAtCoordinate(nullptr, 0, 0, nullptr), "glyph position null") &&
           check(!SkParagraph_Paragraph_getWordBoundary(nullptr, 0, nullptr), "word boundary null") &&
           check(SkParagraph_Paragraph_getLineMetrics(nullptr, nullptr, 0) == -1, "line metrics null") &&
           check(SkParagraph_Paragraph_unresolvedGlyphs(nullptr) == -1, "unresolved null");
}

bool smoke_layout_and_paint() {
    SkGraphics_Init();

    reskia_paragraph_font_collection_t *collection = SkParagraph_FontCollection_new();
    reskia_paragraph_style_t *paragraph_style = SkParagraph_ParagraphStyle_new();
    reskia_paragraph_text_style_t *text_style = SkParagraph_TextStyle_new();
    if (!check(collection != nullptr, "font collection") ||
        !check(paragraph_style != nullptr, "paragraph style") ||
        !check(text_style != nullptr, "text style")) {
        SkParagraph_TextStyle_delete(text_style);
        SkParagraph_ParagraphStyle_delete(paragraph_style);
        SkParagraph_FontCollection_release(collection);
        return false;
    }

    sk_font_mgr_t font_mgr = SkFontMgr_RefDefault();
    if (font_mgr == 0) {
        font_mgr = SkFontMgr_RefEmpty();
    }
    if (!check(font_mgr != 0, "font manager") ||
        !check(SkParagraph_FontCollection_setDefaultFontManager(collection, font_mgr), "set font manager")) {
        static_sk_font_mgr_delete(font_mgr);
        SkParagraph_TextStyle_delete(text_style);
        SkParagraph_ParagraphStyle_delete(paragraph_style);
        SkParagraph_FontCollection_release(collection);
        return false;
    }

    const char *families[] = {"sans-serif"};
    SkParagraph_TextStyle_setFontSize(text_style, 24.0f);
    SkParagraph_TextStyle_setColor(text_style, kBlack);
    if (!check(SkParagraph_TextStyle_setFontFamilies(text_style, families, 1), "set text families") ||
        !check(SkParagraph_ParagraphStyle_setTextStyle(paragraph_style, text_style), "set paragraph text style") ||
        !check(SkParagraph_ParagraphStyle_setTextDirection(paragraph_style, RESKIA_PARAGRAPH_TEXT_DIRECTION_LTR), "set direction") ||
        !check(SkParagraph_ParagraphStyle_setTextAlign(paragraph_style, RESKIA_PARAGRAPH_TEXT_ALIGN_LEFT), "set align")) {
        static_sk_font_mgr_delete(font_mgr);
        SkParagraph_TextStyle_delete(text_style);
        SkParagraph_ParagraphStyle_delete(paragraph_style);
        SkParagraph_FontCollection_release(collection);
        return false;
    }

    reskia_paragraph_builder_t *builder = SkParagraph_ParagraphBuilder_make(paragraph_style, collection);
    if (!check(builder != nullptr, "builder make")) {
        static_sk_font_mgr_delete(font_mgr);
        SkParagraph_TextStyle_delete(text_style);
        SkParagraph_ParagraphStyle_delete(paragraph_style);
        SkParagraph_FontCollection_release(collection);
        return false;
    }

    if (!check(SkParagraph_ParagraphBuilder_pushStyle(builder, text_style), "push style") ||
        !check(SkParagraph_ParagraphBuilder_addTextUtf8(builder, "Hello paragraph", 15), "add utf8")) {
        SkParagraph_ParagraphBuilder_delete(builder);
        static_sk_font_mgr_delete(font_mgr);
        SkParagraph_TextStyle_delete(text_style);
        SkParagraph_ParagraphStyle_delete(paragraph_style);
        SkParagraph_FontCollection_release(collection);
        return false;
    }
    const uint16_t suffix[] = {' ', 'O', 'K'};
    if (!check(SkParagraph_ParagraphBuilder_addTextUtf16(builder, suffix, 3), "add utf16")) {
        SkParagraph_ParagraphBuilder_delete(builder);
        static_sk_font_mgr_delete(font_mgr);
        SkParagraph_TextStyle_delete(text_style);
        SkParagraph_ParagraphStyle_delete(paragraph_style);
        SkParagraph_FontCollection_release(collection);
        return false;
    }

    reskia_paragraph_text_style_t *peek = SkParagraph_ParagraphBuilder_peekStyle(builder);
    reskia_string_t *text = SkParagraph_ParagraphBuilder_getText(builder);
    reskia_paragraph_style_t *style_copy = SkParagraph_ParagraphBuilder_getParagraphStyle(builder);
    if (!check(peek != nullptr, "peek style") ||
        !check(text != nullptr, "get text") ||
        !check(style_copy != nullptr, "get paragraph style")) {
        SkParagraph_ParagraphStyle_delete(style_copy);
        SkString_delete(text);
        SkParagraph_TextStyle_delete(peek);
        SkParagraph_ParagraphBuilder_delete(builder);
        static_sk_font_mgr_delete(font_mgr);
        SkParagraph_TextStyle_delete(text_style);
        SkParagraph_ParagraphStyle_delete(paragraph_style);
        SkParagraph_FontCollection_release(collection);
        return false;
    }
    SkParagraph_ParagraphStyle_delete(style_copy);
    SkString_delete(text);
    SkParagraph_TextStyle_delete(peek);

    SkParagraph_ParagraphBuilder_pop(builder);
    reskia_paragraph_t *paragraph = SkParagraph_ParagraphBuilder_Build(builder);
    SkParagraph_ParagraphBuilder_delete(builder);
    if (!check(paragraph != nullptr, "build paragraph") ||
        !check(SkParagraph_Paragraph_layout(paragraph, 260.0f), "layout") ||
        !check(SkParagraph_Paragraph_getHeight(paragraph) > 0.0f, "height") ||
        !check(SkParagraph_Paragraph_getMaxWidth(paragraph) == 260.0f, "max width") ||
        !check(SkParagraph_Paragraph_lineNumber(paragraph) >= 1, "line number")) {
        SkParagraph_Paragraph_delete(paragraph);
        static_sk_font_mgr_delete(font_mgr);
        SkParagraph_TextStyle_delete(text_style);
        SkParagraph_ParagraphStyle_delete(paragraph_style);
        SkParagraph_FontCollection_release(collection);
        return false;
    }
    (void)SkParagraph_Paragraph_getMinIntrinsicWidth(paragraph);
    (void)SkParagraph_Paragraph_getMaxIntrinsicWidth(paragraph);
    (void)SkParagraph_Paragraph_getAlphabeticBaseline(paragraph);
    (void)SkParagraph_Paragraph_getIdeographicBaseline(paragraph);
    (void)SkParagraph_Paragraph_getLongestLine(paragraph);
    (void)SkParagraph_Paragraph_didExceedMaxLines(paragraph);
    (void)SkParagraph_Paragraph_unresolvedGlyphs(paragraph);
    int32_t unresolved_codepoints[4] = {};
    if (!check(SkParagraph_Paragraph_unresolvedCodepoints(paragraph, unresolved_codepoints, 4) >= 0, "unresolved codepoints")) {
        SkParagraph_Paragraph_delete(paragraph);
        static_sk_font_mgr_delete(font_mgr);
        SkParagraph_TextStyle_delete(text_style);
        SkParagraph_ParagraphStyle_delete(paragraph_style);
        SkParagraph_FontCollection_release(collection);
        return false;
    }
    reskia_paragraph_line_metrics_t line_metrics[8] = {};
    const int32_t line_metric_count = SkParagraph_Paragraph_getLineMetrics(paragraph, line_metrics, 8);
    if (!check(line_metric_count > 0, "line metrics count") ||
        !check(line_metrics[0].height > 0.0, "line metrics height") ||
        !check(line_metrics[0].end_index >= line_metrics[0].start_index, "line metrics range")) {
        SkParagraph_Paragraph_delete(paragraph);
        static_sk_font_mgr_delete(font_mgr);
        SkParagraph_TextStyle_delete(text_style);
        SkParagraph_ParagraphStyle_delete(paragraph_style);
        SkParagraph_FontCollection_release(collection);
        return false;
    }
    reskia_paragraph_text_box_t boxes[8] = {};
    if (!check(SkParagraph_Paragraph_getRectsForRange(paragraph, 0, 5, RESKIA_PARAGRAPH_RECT_HEIGHT_STYLE_TIGHT, RESKIA_PARAGRAPH_RECT_WIDTH_STYLE_TIGHT, boxes, 8) >= 0, "rects for range") ||
        !check(SkParagraph_Paragraph_getRectsForPlaceholders(paragraph, boxes, 8) >= 0, "rects for placeholders")) {
        SkParagraph_Paragraph_delete(paragraph);
        static_sk_font_mgr_delete(font_mgr);
        SkParagraph_TextStyle_delete(text_style);
        SkParagraph_ParagraphStyle_delete(paragraph_style);
        SkParagraph_FontCollection_release(collection);
        return false;
    }
    reskia_paragraph_position_with_affinity_t position = {};
    reskia_paragraph_range_t range = {};
    if (!check(SkParagraph_Paragraph_getGlyphPositionAtCoordinate(paragraph, 4.0f, 4.0f, &position), "glyph position") ||
        !check(SkParagraph_Paragraph_getWordBoundary(paragraph, 1, &range), "word boundary") ||
        !check(SkParagraph_Paragraph_updateTextAlign(paragraph, RESKIA_PARAGRAPH_TEXT_ALIGN_CENTER), "update align") ||
        !check(SkParagraph_Paragraph_updateFontSize(paragraph, 0, 18, 20.0f), "update font size")) {
        SkParagraph_Paragraph_delete(paragraph);
        static_sk_font_mgr_delete(font_mgr);
        SkParagraph_TextStyle_delete(text_style);
        SkParagraph_ParagraphStyle_delete(paragraph_style);
        SkParagraph_FontCollection_release(collection);
        return false;
    }
    SkParagraph_Paragraph_markDirty(paragraph);
    if (!check(SkParagraph_Paragraph_layout(paragraph, 260.0f), "layout after dirty")) {
        SkParagraph_Paragraph_delete(paragraph);
        static_sk_font_mgr_delete(font_mgr);
        SkParagraph_TextStyle_delete(text_style);
        SkParagraph_ParagraphStyle_delete(paragraph_style);
        SkParagraph_FontCollection_release(collection);
        return false;
    }

    reskia_bitmap_t *bitmap = SkBitmap_new();
    if (!check(bitmap != nullptr, "bitmap new") ||
        !check(SkBitmap_tryAllocN32Pixels(bitmap, 300, 120, false), "bitmap alloc")) {
        SkBitmap_delete(bitmap);
        SkParagraph_Paragraph_delete(paragraph);
        static_sk_font_mgr_delete(font_mgr);
        SkParagraph_TextStyle_delete(text_style);
        SkParagraph_ParagraphStyle_delete(paragraph_style);
        SkParagraph_FontCollection_release(collection);
        return false;
    }
    SkBitmap_eraseColor(bitmap, kWhite);
    reskia_canvas_t *canvas = SkCanvas_newFromBitmap(bitmap);
    if (!check(canvas != nullptr, "canvas from bitmap") ||
        !check(SkParagraph_Paragraph_paint(paragraph, canvas, 8.0f, 8.0f), "paint") ||
        !check(has_non_white_pixel(bitmap), "paint produced pixels")) {
        SkCanvas_delete(canvas);
        SkBitmap_delete(bitmap);
        SkParagraph_Paragraph_delete(paragraph);
        static_sk_font_mgr_delete(font_mgr);
        SkParagraph_TextStyle_delete(text_style);
        SkParagraph_ParagraphStyle_delete(paragraph_style);
        SkParagraph_FontCollection_release(collection);
        return false;
    }

    SkCanvas_delete(canvas);
    SkBitmap_delete(bitmap);
    SkParagraph_Paragraph_delete(paragraph);
    static_sk_font_mgr_delete(font_mgr);
    SkParagraph_TextStyle_delete(text_style);
    SkParagraph_ParagraphStyle_delete(paragraph_style);
    SkParagraph_FontCollection_release(collection);
    return true;
}

}  // namespace

int main() {
    return smoke_null_inputs() && smoke_layout_and_paint() ? 0 : 1;
}
