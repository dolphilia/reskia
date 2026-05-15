//
// Created by Codex on 2026/05/15.
//

#ifndef RAIA_SKIA_SK_PARAGRAPH_BUILDER_H
#define RAIA_SKIA_SK_PARAGRAPH_BUILDER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "sk_paragraph_style.h"
#include "sk_paragraph_text_style.h"
#include "../handles/static_sk_font_mgr.h"

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_paragraph_builder_t reskia_paragraph_builder_t;
typedef struct reskia_paragraph_font_collection_t reskia_paragraph_font_collection_t;
typedef struct reskia_paragraph_t reskia_paragraph_t;
typedef struct reskia_unicode_t reskia_unicode_t;
typedef int32_t reskia_paragraph_affinity_t;
typedef int32_t reskia_paragraph_placeholder_alignment_t;
typedef int32_t reskia_paragraph_rect_height_style_t;
typedef int32_t reskia_paragraph_rect_width_style_t;

typedef struct reskia_paragraph_text_box_t {
    float left;
    float top;
    float right;
    float bottom;
    reskia_paragraph_text_direction_t direction;
} reskia_paragraph_text_box_t;

typedef struct reskia_paragraph_position_with_affinity_t {
    int32_t position;
    reskia_paragraph_affinity_t affinity;
} reskia_paragraph_position_with_affinity_t;

typedef struct reskia_paragraph_placeholder_style_t {
    float width;
    float height;
    reskia_paragraph_placeholder_alignment_t alignment;
    reskia_paragraph_text_baseline_t baseline;
    float baseline_offset;
} reskia_paragraph_placeholder_style_t;

typedef struct reskia_paragraph_line_metrics_t {
    size_t start_index;
    size_t end_index;
    size_t end_excluding_whitespaces;
    size_t end_including_newline;
    bool hard_break;
    double ascent;
    double descent;
    double unscaled_ascent;
    double height;
    double width;
    double left;
    double baseline;
    size_t line_number;
    size_t run_metrics_count;
} reskia_paragraph_line_metrics_t;

typedef struct reskia_paragraph_range_t {
    size_t start;
    size_t end;
} reskia_paragraph_range_t;

#ifdef __cplusplus
extern "C" {
#endif

enum {
    RESKIA_PARAGRAPH_PLACEHOLDER_ALIGNMENT_BASELINE = 0,
    RESKIA_PARAGRAPH_PLACEHOLDER_ALIGNMENT_ABOVE_BASELINE = 1,
    RESKIA_PARAGRAPH_PLACEHOLDER_ALIGNMENT_BELOW_BASELINE = 2,
    RESKIA_PARAGRAPH_PLACEHOLDER_ALIGNMENT_TOP = 3,
    RESKIA_PARAGRAPH_PLACEHOLDER_ALIGNMENT_BOTTOM = 4,
    RESKIA_PARAGRAPH_PLACEHOLDER_ALIGNMENT_MIDDLE = 5,
};

enum {
    RESKIA_PARAGRAPH_AFFINITY_UPSTREAM = 0,
    RESKIA_PARAGRAPH_AFFINITY_DOWNSTREAM = 1,
};

enum {
    RESKIA_PARAGRAPH_RECT_HEIGHT_STYLE_TIGHT = 0,
    RESKIA_PARAGRAPH_RECT_HEIGHT_STYLE_MAX = 1,
    RESKIA_PARAGRAPH_RECT_HEIGHT_STYLE_INCLUDE_LINE_SPACING_MIDDLE = 2,
    RESKIA_PARAGRAPH_RECT_HEIGHT_STYLE_INCLUDE_LINE_SPACING_TOP = 3,
    RESKIA_PARAGRAPH_RECT_HEIGHT_STYLE_INCLUDE_LINE_SPACING_BOTTOM = 4,
    RESKIA_PARAGRAPH_RECT_HEIGHT_STYLE_STRUT = 5,
};

enum {
    RESKIA_PARAGRAPH_RECT_WIDTH_STYLE_TIGHT = 0,
    RESKIA_PARAGRAPH_RECT_WIDTH_STYLE_MAX = 1,
};

bool SkParagraph_PositionWithAffinity_Make(int32_t position, reskia_paragraph_affinity_t affinity, reskia_paragraph_position_with_affinity_t *out_position);
bool SkParagraph_TextBox_Make(float left, float top, float right, float bottom, reskia_paragraph_text_direction_t direction, reskia_paragraph_text_box_t *out_box);
bool SkParagraph_PlaceholderStyle_Make(float width, float height, reskia_paragraph_placeholder_alignment_t alignment, reskia_paragraph_text_baseline_t baseline, float baseline_offset, reskia_paragraph_placeholder_style_t *out_style);
bool SkParagraph_PlaceholderStyle_equals(const reskia_paragraph_placeholder_style_t *style, const reskia_paragraph_placeholder_style_t *other);
bool SkParagraph_LineMetrics_Make(size_t start, size_t end, size_t end_excluding_whitespaces, size_t end_including_newline, bool hard_break, reskia_paragraph_line_metrics_t *out_metrics);

reskia_paragraph_builder_t *SkParagraph_ParagraphBuilder_make(const reskia_paragraph_style_t *style, reskia_paragraph_font_collection_t *font_collection);
reskia_paragraph_builder_t *ParagraphBuilder_make(const reskia_paragraph_style_t *style, reskia_paragraph_font_collection_t *font_collection); // compatibility alias for coverage tooling
void SkParagraph_ParagraphBuilder_delete(reskia_paragraph_builder_t *builder);
bool SkParagraph_ParagraphBuilder_pushStyle(reskia_paragraph_builder_t *builder, const reskia_paragraph_text_style_t *style);
void SkParagraph_ParagraphBuilder_pop(reskia_paragraph_builder_t *builder);
reskia_paragraph_text_style_t *SkParagraph_ParagraphBuilder_peekStyle(reskia_paragraph_builder_t *builder);
bool SkParagraph_ParagraphBuilder_addTextUtf8(reskia_paragraph_builder_t *builder, const char *text, int32_t units);
bool SkParagraph_ParagraphBuilder_addText(reskia_paragraph_builder_t *builder, const char *text, int32_t units);
bool SkParagraph_ParagraphBuilder_addTextUtf16(reskia_paragraph_builder_t *builder, const uint16_t *text, int32_t units);
bool SkParagraph_ParagraphBuilder_addPlaceholder(reskia_paragraph_builder_t *builder, float width, float height, reskia_paragraph_placeholder_alignment_t alignment, reskia_paragraph_text_baseline_t baseline, float baseline_offset);
reskia_paragraph_t *SkParagraph_ParagraphBuilder_Build(reskia_paragraph_builder_t *builder);
reskia_string_t *SkParagraph_ParagraphBuilder_getText(reskia_paragraph_builder_t *builder);
reskia_paragraph_style_t *SkParagraph_ParagraphBuilder_getParagraphStyle(reskia_paragraph_builder_t *builder);
bool SkParagraph_ParagraphBuilder_setWordsUtf8(reskia_paragraph_builder_t *builder, const size_t *positions, int32_t count);
bool SkParagraph_ParagraphBuilder_setWordsUtf16(reskia_paragraph_builder_t *builder, const size_t *positions, int32_t count);
bool SkParagraph_ParagraphBuilder_setGraphemeBreaksUtf8(reskia_paragraph_builder_t *builder, const size_t *positions, int32_t count);
bool SkParagraph_ParagraphBuilder_setGraphemeBreaksUtf16(reskia_paragraph_builder_t *builder, const size_t *positions, int32_t count);
bool SkParagraph_ParagraphBuilder_setLineBreaksUtf8(reskia_paragraph_builder_t *builder, const size_t *positions, int32_t count);
bool SkParagraph_ParagraphBuilder_setLineBreaksUtf16(reskia_paragraph_builder_t *builder, const size_t *positions, int32_t count);
bool SkParagraph_ParagraphBuilder_SetUnicode(reskia_paragraph_builder_t *builder, reskia_unicode_t *unicode); // consumes unicode on success
void SkParagraph_ParagraphBuilder_Reset(reskia_paragraph_builder_t *builder);

void SkParagraph_Paragraph_delete(reskia_paragraph_t *paragraph);
float SkParagraph_Paragraph_getMaxWidth(reskia_paragraph_t *paragraph);
float SkParagraph_Paragraph_getHeight(reskia_paragraph_t *paragraph);
float SkParagraph_Paragraph_getMinIntrinsicWidth(reskia_paragraph_t *paragraph);
float SkParagraph_Paragraph_getMaxIntrinsicWidth(reskia_paragraph_t *paragraph);
float SkParagraph_Paragraph_getAlphabeticBaseline(reskia_paragraph_t *paragraph);
float SkParagraph_Paragraph_getIdeographicBaseline(reskia_paragraph_t *paragraph);
float SkParagraph_Paragraph_getLongestLine(reskia_paragraph_t *paragraph);
bool SkParagraph_Paragraph_didExceedMaxLines(reskia_paragraph_t *paragraph);
bool SkParagraph_Paragraph_layout(reskia_paragraph_t *paragraph, float width);
bool SkParagraph_Paragraph_paint(reskia_paragraph_t *paragraph, reskia_canvas_t *canvas, float x, float y);
int32_t SkParagraph_Paragraph_getRectsForRange(reskia_paragraph_t *paragraph, uint32_t start, uint32_t end, reskia_paragraph_rect_height_style_t height_style, reskia_paragraph_rect_width_style_t width_style, reskia_paragraph_text_box_t *dst, int32_t dst_count);
int32_t SkParagraph_Paragraph_getRectsForPlaceholders(reskia_paragraph_t *paragraph, reskia_paragraph_text_box_t *dst, int32_t dst_count);
bool SkParagraph_Paragraph_getGlyphPositionAtCoordinate(reskia_paragraph_t *paragraph, float dx, float dy, reskia_paragraph_position_with_affinity_t *out_position);
bool SkParagraph_Paragraph_getWordBoundary(reskia_paragraph_t *paragraph, uint32_t offset, reskia_paragraph_range_t *out_range);
int32_t SkParagraph_Paragraph_getLineMetrics(reskia_paragraph_t *paragraph, reskia_paragraph_line_metrics_t *dst, int32_t dst_count);
size_t SkParagraph_Paragraph_lineNumber(reskia_paragraph_t *paragraph);
void SkParagraph_Paragraph_markDirty(reskia_paragraph_t *paragraph);
int32_t SkParagraph_Paragraph_unresolvedGlyphs(reskia_paragraph_t *paragraph);
int32_t SkParagraph_Paragraph_unresolvedCodepoints(reskia_paragraph_t *paragraph, int32_t *dst, int32_t dst_count);
bool SkParagraph_Paragraph_updateTextAlign(reskia_paragraph_t *paragraph, reskia_paragraph_text_align_t text_align);
bool SkParagraph_Paragraph_updateFontSize(reskia_paragraph_t *paragraph, size_t from, size_t to, float font_size);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_PARAGRAPH_BUILDER_H
