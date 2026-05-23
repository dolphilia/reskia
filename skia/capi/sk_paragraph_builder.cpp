//
// Created by Codex on 2026/05/15.
//

#include "sk_paragraph_builder.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"
#include "include/core/SkString.h"
#include "modules/skparagraph/include/FontCollection.h"
#include "modules/skparagraph/include/Metrics.h"
#include "modules/skparagraph/include/Paragraph.h"
#include "modules/skparagraph/include/ParagraphBuilder.h"
#include "modules/skparagraph/include/ParagraphStyle.h"
#include "modules/skparagraph/include/TextStyle.h"
#include "modules/skparagraph/src/ParagraphImpl.h"
#include "modules/skunicode/include/SkUnicode.h"

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

namespace {

using skia::textlayout::FontCollection;
using skia::textlayout::Paragraph;
using skia::textlayout::ParagraphBuilder;
using skia::textlayout::ParagraphImpl;
using skia::textlayout::ParagraphStyle;
using skia::textlayout::PlaceholderAlignment;
using skia::textlayout::PlaceholderStyle;
using skia::textlayout::RectHeightStyle;
using skia::textlayout::RectWidthStyle;
using skia::textlayout::TextBaseline;
using skia::textlayout::TextBox;
using skia::textlayout::TextStyle;

ParagraphBuilder *as_builder(reskia_paragraph_builder_t *builder) {
    return reinterpret_cast<ParagraphBuilder *>(builder);
}

Paragraph *as_paragraph(reskia_paragraph_t *paragraph) {
    return reinterpret_cast<Paragraph *>(paragraph);
}

const ParagraphStyle *as_paragraph_style(const reskia_paragraph_style_t *style) {
    return reinterpret_cast<const ParagraphStyle *>(style);
}

const TextStyle *as_text_style(const reskia_paragraph_text_style_t *style) {
    return reinterpret_cast<const TextStyle *>(style);
}

FontCollection *as_font_collection(reskia_paragraph_font_collection_t *collection) {
    return reinterpret_cast<FontCollection *>(collection);
}

SkUnicode *as_unicode(reskia_unicode_t *unicode) {
    return reinterpret_cast<SkUnicode *>(unicode);
}

SkCanvas *as_canvas(reskia_canvas_t *canvas) {
    return reinterpret_cast<SkCanvas *>(canvas);
}

const SkPaint *as_paint(const reskia_paint_t *paint) {
    return reinterpret_cast<const SkPaint *>(paint);
}

ParagraphImpl *as_paragraph_impl(reskia_paragraph_t *paragraph) {
    return dynamic_cast<ParagraphImpl *>(as_paragraph(paragraph));
}

bool valid_placeholder_alignment(reskia_paragraph_placeholder_alignment_t alignment) {
    return alignment >= RESKIA_PARAGRAPH_PLACEHOLDER_ALIGNMENT_BASELINE &&
           alignment <= RESKIA_PARAGRAPH_PLACEHOLDER_ALIGNMENT_MIDDLE;
}

bool valid_text_baseline(reskia_paragraph_text_baseline_t baseline) {
    return baseline == RESKIA_PARAGRAPH_TEXT_BASELINE_ALPHABETIC ||
           baseline == RESKIA_PARAGRAPH_TEXT_BASELINE_IDEOGRAPHIC;
}

bool valid_text_direction(reskia_paragraph_text_direction_t direction) {
    return direction == RESKIA_PARAGRAPH_TEXT_DIRECTION_RTL ||
           direction == RESKIA_PARAGRAPH_TEXT_DIRECTION_LTR;
}

bool valid_text_align(reskia_paragraph_text_align_t align) {
    return align >= RESKIA_PARAGRAPH_TEXT_ALIGN_LEFT && align <= RESKIA_PARAGRAPH_TEXT_ALIGN_END;
}

bool valid_rect_height_style(reskia_paragraph_rect_height_style_t style) {
    return style >= RESKIA_PARAGRAPH_RECT_HEIGHT_STYLE_TIGHT &&
           style <= RESKIA_PARAGRAPH_RECT_HEIGHT_STYLE_STRUT;
}

bool valid_rect_width_style(reskia_paragraph_rect_width_style_t style) {
    return style == RESKIA_PARAGRAPH_RECT_WIDTH_STYLE_TIGHT ||
           style == RESKIA_PARAGRAPH_RECT_WIDTH_STYLE_MAX;
}

reskia_paragraph_text_direction_t from_text_direction(skia::textlayout::TextDirection direction) {
    return static_cast<reskia_paragraph_text_direction_t>(direction);
}

void copy_text_boxes(const std::vector<TextBox>& boxes, reskia_paragraph_text_box_t *dst, int32_t dst_count) {
    if (dst == nullptr || dst_count <= 0) {
        return;
    }
    const int32_t copy_count = std::min<int32_t>(dst_count, static_cast<int32_t>(boxes.size()));
    for (int32_t i = 0; i < copy_count; ++i) {
        dst[i].left = boxes[i].rect.left();
        dst[i].top = boxes[i].rect.top();
        dst[i].right = boxes[i].rect.right();
        dst[i].bottom = boxes[i].rect.bottom();
        dst[i].direction = from_text_direction(boxes[i].direction);
    }
}

void copy_line_metrics(const std::vector<skia::textlayout::LineMetrics>& metrics, reskia_paragraph_line_metrics_t *dst, int32_t dst_count) {
    if (dst == nullptr || dst_count <= 0) {
        return;
    }
    const int32_t copy_count = std::min<int32_t>(dst_count, static_cast<int32_t>(metrics.size()));
    for (int32_t i = 0; i < copy_count; ++i) {
        dst[i].start_index = metrics[i].fStartIndex;
        dst[i].end_index = metrics[i].fEndIndex;
        dst[i].end_excluding_whitespaces = metrics[i].fEndExcludingWhitespaces;
        dst[i].end_including_newline = metrics[i].fEndIncludingNewline;
        dst[i].hard_break = metrics[i].fHardBreak;
        dst[i].ascent = metrics[i].fAscent;
        dst[i].descent = metrics[i].fDescent;
        dst[i].unscaled_ascent = metrics[i].fUnscaledAscent;
        dst[i].height = metrics[i].fHeight;
        dst[i].width = metrics[i].fWidth;
        dst[i].left = metrics[i].fLeft;
        dst[i].baseline = metrics[i].fBaseline;
        dst[i].line_number = metrics[i].fLineNumber;
        dst[i].run_metrics_count = metrics[i].fLineMetrics.size();
    }
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

bool SkParagraph_PositionWithAffinity_Make(int32_t position, reskia_paragraph_affinity_t affinity, reskia_paragraph_position_with_affinity_t *out_position) {
    if (out_position == nullptr ||
        (affinity != RESKIA_PARAGRAPH_AFFINITY_UPSTREAM && affinity != RESKIA_PARAGRAPH_AFFINITY_DOWNSTREAM)) {
        return false;
    }
    out_position->position = position;
    out_position->affinity = affinity;
    return true;
}

bool SkParagraph_TextBox_Make(float left, float top, float right, float bottom, reskia_paragraph_text_direction_t direction, reskia_paragraph_text_box_t *out_box) {
    if (out_box == nullptr || !valid_text_direction(direction)) {
        return false;
    }
    out_box->left = left;
    out_box->top = top;
    out_box->right = right;
    out_box->bottom = bottom;
    out_box->direction = direction;
    return true;
}

bool SkParagraph_PlaceholderStyle_Make(float width, float height, reskia_paragraph_placeholder_alignment_t alignment, reskia_paragraph_text_baseline_t baseline, float baseline_offset, reskia_paragraph_placeholder_style_t *out_style) {
    if (out_style == nullptr || !valid_placeholder_alignment(alignment) || !valid_text_baseline(baseline) || width < 0.0f || height < 0.0f) {
        return false;
    }
    out_style->width = width;
    out_style->height = height;
    out_style->alignment = alignment;
    out_style->baseline = baseline;
    out_style->baseline_offset = baseline_offset;
    return true;
}

bool SkParagraph_PlaceholderStyle_equals(const reskia_paragraph_placeholder_style_t *style, const reskia_paragraph_placeholder_style_t *other) {
    return style != nullptr && other != nullptr &&
           style->width == other->width &&
           style->height == other->height &&
           style->alignment == other->alignment &&
           style->baseline == other->baseline &&
           style->baseline_offset == other->baseline_offset;
}

bool SkParagraph_LineMetrics_Make(size_t start, size_t end, size_t end_excluding_whitespaces, size_t end_including_newline, bool hard_break, reskia_paragraph_line_metrics_t *out_metrics) {
    if (out_metrics == nullptr || end < start || end_excluding_whitespaces < start || end_including_newline < start) {
        return false;
    }
    *out_metrics = {};
    out_metrics->start_index = start;
    out_metrics->end_index = end;
    out_metrics->end_excluding_whitespaces = end_excluding_whitespaces;
    out_metrics->end_including_newline = end_including_newline;
    out_metrics->hard_break = hard_break;
    return true;
}

reskia_paragraph_builder_t *SkParagraph_ParagraphBuilder_make(const reskia_paragraph_style_t *style, reskia_paragraph_font_collection_t *font_collection) {
    if (style == nullptr || font_collection == nullptr) {
        return nullptr;
    }
    auto builder = ParagraphBuilder::make(*as_paragraph_style(style), sk_ref_sp(as_font_collection(font_collection)));
    return reinterpret_cast<reskia_paragraph_builder_t *>(builder.release());
}

reskia_paragraph_builder_t *ParagraphBuilder_make(const reskia_paragraph_style_t *style, reskia_paragraph_font_collection_t *font_collection) {
    return SkParagraph_ParagraphBuilder_make(style, font_collection);
}

void SkParagraph_ParagraphBuilder_delete(reskia_paragraph_builder_t *builder) {
    delete as_builder(builder);
}

bool SkParagraph_ParagraphBuilder_pushStyle(reskia_paragraph_builder_t *builder, const reskia_paragraph_text_style_t *style) {
    if (builder == nullptr || style == nullptr) {
        return false;
    }
    as_builder(builder)->pushStyle(*as_text_style(style));
    return true;
}

void SkParagraph_ParagraphBuilder_pop(reskia_paragraph_builder_t *builder) {
    if (builder != nullptr) {
        as_builder(builder)->pop();
    }
}

reskia_paragraph_text_style_t *SkParagraph_ParagraphBuilder_peekStyle(reskia_paragraph_builder_t *builder) {
    if (builder == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_paragraph_text_style_t *>(new TextStyle(as_builder(builder)->peekStyle()));
}

bool SkParagraph_ParagraphBuilder_addTextUtf8(reskia_paragraph_builder_t *builder, const char *text, int32_t units) {
    if (builder == nullptr || units < 0 || (text == nullptr && units != 0)) {
        return false;
    }
    as_builder(builder)->addText(text == nullptr ? "" : text, static_cast<size_t>(units));
    return true;
}

bool SkParagraph_ParagraphBuilder_addText(reskia_paragraph_builder_t *builder, const char *text, int32_t units) {
    return SkParagraph_ParagraphBuilder_addTextUtf8(builder, text, units);
}

bool SkParagraph_ParagraphBuilder_addTextUtf16(reskia_paragraph_builder_t *builder, const uint16_t *text, int32_t units) {
    if (builder == nullptr || units < 0 || (text == nullptr && units != 0)) {
        return false;
    }
    std::u16string value;
    if (units > 0) {
        value.assign(reinterpret_cast<const char16_t *>(text), static_cast<size_t>(units));
    }
    as_builder(builder)->addText(value);
    return true;
}

bool SkParagraph_ParagraphBuilder_addPlaceholder(reskia_paragraph_builder_t *builder, float width, float height, reskia_paragraph_placeholder_alignment_t alignment, reskia_paragraph_text_baseline_t baseline, float baseline_offset) {
    if (builder == nullptr || !valid_placeholder_alignment(alignment) || !valid_text_baseline(baseline) || width < 0.0f || height < 0.0f) {
        return false;
    }
    PlaceholderStyle placeholder(width, height, static_cast<PlaceholderAlignment>(alignment), static_cast<TextBaseline>(baseline), baseline_offset);
    as_builder(builder)->addPlaceholder(placeholder);
    return true;
}

reskia_paragraph_t *SkParagraph_ParagraphBuilder_Build(reskia_paragraph_builder_t *builder) {
    if (builder == nullptr) {
        return nullptr;
    }
    auto paragraph = as_builder(builder)->Build();
    return reinterpret_cast<reskia_paragraph_t *>(paragraph.release());
}

reskia_string_t *SkParagraph_ParagraphBuilder_getText(reskia_paragraph_builder_t *builder) {
    if (builder == nullptr) {
        return nullptr;
    }
    SkSpan<char> text = as_builder(builder)->getText();
    return reinterpret_cast<reskia_string_t *>(new SkString(text.data(), text.size()));
}

reskia_paragraph_style_t *SkParagraph_ParagraphBuilder_getParagraphStyle(reskia_paragraph_builder_t *builder) {
    if (builder == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_paragraph_style_t *>(new ParagraphStyle(as_builder(builder)->getParagraphStyle()));
}

bool SkParagraph_ParagraphBuilder_setWordsUtf8(reskia_paragraph_builder_t *builder, const size_t *positions, int32_t count) {
    if (builder == nullptr || count < 0 || (positions == nullptr && count != 0)) {
        return false;
    }
    as_builder(builder)->setWordsUtf8(make_positions(positions, count));
    return true;
}

bool SkParagraph_ParagraphBuilder_setWordsUtf16(reskia_paragraph_builder_t *builder, const size_t *positions, int32_t count) {
    if (builder == nullptr || count < 0 || (positions == nullptr && count != 0)) {
        return false;
    }
    as_builder(builder)->setWordsUtf16(make_positions(positions, count));
    return true;
}

bool SkParagraph_ParagraphBuilder_setGraphemeBreaksUtf8(reskia_paragraph_builder_t *builder, const size_t *positions, int32_t count) {
    if (builder == nullptr || count < 0 || (positions == nullptr && count != 0)) {
        return false;
    }
    as_builder(builder)->setGraphemeBreaksUtf8(make_positions(positions, count));
    return true;
}

bool SkParagraph_ParagraphBuilder_setGraphemeBreaksUtf16(reskia_paragraph_builder_t *builder, const size_t *positions, int32_t count) {
    if (builder == nullptr || count < 0 || (positions == nullptr && count != 0)) {
        return false;
    }
    as_builder(builder)->setGraphemeBreaksUtf16(make_positions(positions, count));
    return true;
}

bool SkParagraph_ParagraphBuilder_setLineBreaksUtf8(reskia_paragraph_builder_t *builder, const size_t *positions, int32_t count) {
    if (builder == nullptr || count < 0 || (positions == nullptr && count != 0)) {
        return false;
    }
    as_builder(builder)->setLineBreaksUtf8(make_line_breaks(positions, count));
    return true;
}

bool SkParagraph_ParagraphBuilder_setLineBreaksUtf16(reskia_paragraph_builder_t *builder, const size_t *positions, int32_t count) {
    if (builder == nullptr || count < 0 || (positions == nullptr && count != 0)) {
        return false;
    }
    as_builder(builder)->setLineBreaksUtf16(make_line_breaks(positions, count));
    return true;
}

bool SkParagraph_ParagraphBuilder_SetUnicode(reskia_paragraph_builder_t *builder, reskia_unicode_t *unicode) {
    if (builder == nullptr || unicode == nullptr) {
        return false;
    }
    as_builder(builder)->SetUnicode(sk_sp<SkUnicode>(as_unicode(unicode)));
    return true;
}

void SkParagraph_ParagraphBuilder_Reset(reskia_paragraph_builder_t *builder) {
    if (builder != nullptr) {
        as_builder(builder)->Reset();
    }
}

void SkParagraph_Paragraph_delete(reskia_paragraph_t *paragraph) {
    delete as_paragraph(paragraph);
}

float SkParagraph_Paragraph_getMaxWidth(reskia_paragraph_t *paragraph) {
    return paragraph == nullptr ? 0.0f : as_paragraph(paragraph)->getMaxWidth();
}

float SkParagraph_Paragraph_getHeight(reskia_paragraph_t *paragraph) {
    return paragraph == nullptr ? 0.0f : as_paragraph(paragraph)->getHeight();
}

float SkParagraph_Paragraph_getMinIntrinsicWidth(reskia_paragraph_t *paragraph) {
    return paragraph == nullptr ? 0.0f : as_paragraph(paragraph)->getMinIntrinsicWidth();
}

float SkParagraph_Paragraph_getMaxIntrinsicWidth(reskia_paragraph_t *paragraph) {
    return paragraph == nullptr ? 0.0f : as_paragraph(paragraph)->getMaxIntrinsicWidth();
}

float SkParagraph_Paragraph_getAlphabeticBaseline(reskia_paragraph_t *paragraph) {
    return paragraph == nullptr ? 0.0f : as_paragraph(paragraph)->getAlphabeticBaseline();
}

float SkParagraph_Paragraph_getIdeographicBaseline(reskia_paragraph_t *paragraph) {
    return paragraph == nullptr ? 0.0f : as_paragraph(paragraph)->getIdeographicBaseline();
}

float SkParagraph_Paragraph_getLongestLine(reskia_paragraph_t *paragraph) {
    return paragraph == nullptr ? 0.0f : as_paragraph(paragraph)->getLongestLine();
}

bool SkParagraph_Paragraph_didExceedMaxLines(reskia_paragraph_t *paragraph) {
    return paragraph != nullptr && as_paragraph(paragraph)->didExceedMaxLines();
}

bool SkParagraph_Paragraph_layout(reskia_paragraph_t *paragraph, float width) {
    if (paragraph == nullptr || width < 0.0f) {
        return false;
    }
    as_paragraph(paragraph)->layout(width);
    return true;
}

bool SkParagraph_Paragraph_paint(reskia_paragraph_t *paragraph, reskia_canvas_t *canvas, float x, float y) {
    if (paragraph == nullptr || canvas == nullptr) {
        return false;
    }
    as_paragraph(paragraph)->paint(as_canvas(canvas), x, y);
    return true;
}

int32_t SkParagraph_Paragraph_getRectsForRange(reskia_paragraph_t *paragraph, uint32_t start, uint32_t end, reskia_paragraph_rect_height_style_t height_style, reskia_paragraph_rect_width_style_t width_style, reskia_paragraph_text_box_t *dst, int32_t dst_count) {
    if (paragraph == nullptr || dst_count < 0 || !valid_rect_height_style(height_style) || !valid_rect_width_style(width_style)) {
        return -1;
    }
    auto boxes = as_paragraph(paragraph)->getRectsForRange(start, end, static_cast<RectHeightStyle>(height_style), static_cast<RectWidthStyle>(width_style));
    copy_text_boxes(boxes, dst, dst_count);
    return static_cast<int32_t>(boxes.size());
}

int32_t SkParagraph_Paragraph_getRectsForPlaceholders(reskia_paragraph_t *paragraph, reskia_paragraph_text_box_t *dst, int32_t dst_count) {
    if (paragraph == nullptr || dst_count < 0) {
        return -1;
    }
    auto boxes = as_paragraph(paragraph)->getRectsForPlaceholders();
    copy_text_boxes(boxes, dst, dst_count);
    return static_cast<int32_t>(boxes.size());
}

bool SkParagraph_Paragraph_getGlyphPositionAtCoordinate(reskia_paragraph_t *paragraph, float dx, float dy, reskia_paragraph_position_with_affinity_t *out_position) {
    if (paragraph == nullptr || out_position == nullptr) {
        return false;
    }
    const auto position = as_paragraph(paragraph)->getGlyphPositionAtCoordinate(dx, dy);
    out_position->position = position.position;
    out_position->affinity = static_cast<reskia_paragraph_affinity_t>(position.affinity);
    return true;
}

bool SkParagraph_Paragraph_getWordBoundary(reskia_paragraph_t *paragraph, uint32_t offset, reskia_paragraph_range_t *out_range) {
    if (paragraph == nullptr || out_range == nullptr) {
        return false;
    }
    const auto range = as_paragraph(paragraph)->getWordBoundary(offset);
    out_range->start = range.start;
    out_range->end = range.end;
    return true;
}

int32_t SkParagraph_Paragraph_getLineMetrics(reskia_paragraph_t *paragraph, reskia_paragraph_line_metrics_t *dst, int32_t dst_count) {
    if (paragraph == nullptr || dst_count < 0) {
        return -1;
    }
    std::vector<skia::textlayout::LineMetrics> metrics;
    as_paragraph(paragraph)->getLineMetrics(metrics);
    copy_line_metrics(metrics, dst, dst_count);
    return static_cast<int32_t>(metrics.size());
}

size_t SkParagraph_Paragraph_lineNumber(reskia_paragraph_t *paragraph) {
    return paragraph == nullptr ? 0 : as_paragraph(paragraph)->lineNumber();
}

void SkParagraph_Paragraph_markDirty(reskia_paragraph_t *paragraph) {
    if (paragraph != nullptr) {
        as_paragraph(paragraph)->markDirty();
    }
}

int32_t SkParagraph_Paragraph_unresolvedGlyphs(reskia_paragraph_t *paragraph) {
    return paragraph == nullptr ? -1 : as_paragraph(paragraph)->unresolvedGlyphs();
}

int32_t SkParagraph_Paragraph_unresolvedCodepoints(reskia_paragraph_t *paragraph, int32_t *dst, int32_t dst_count) {
    if (paragraph == nullptr || dst_count < 0) {
        return -1;
    }
    const auto codepoints = as_paragraph(paragraph)->unresolvedCodepoints();
    if (dst != nullptr && dst_count > 0) {
        int32_t index = 0;
        for (SkUnichar codepoint : codepoints) {
            if (index >= dst_count) {
                break;
            }
            dst[index++] = codepoint;
        }
    }
    return static_cast<int32_t>(codepoints.size());
}

bool SkParagraph_Paragraph_updateTextAlign(reskia_paragraph_t *paragraph, reskia_paragraph_text_align_t text_align) {
    if (paragraph == nullptr || !valid_text_align(text_align)) {
        return false;
    }
    as_paragraph(paragraph)->updateTextAlign(static_cast<skia::textlayout::TextAlign>(text_align));
    return true;
}

bool SkParagraph_Paragraph_updateFontSize(reskia_paragraph_t *paragraph, size_t from, size_t to, float font_size) {
    if (paragraph == nullptr || from > to || font_size < 0.0f) {
        return false;
    }
    as_paragraph(paragraph)->updateFontSize(from, to, font_size);
    return true;
}

bool SkParagraph_Paragraph_updateForegroundPaint(reskia_paragraph_t *paragraph, size_t from, size_t to, const reskia_paint_t *paint) {
    if (paragraph == nullptr || paint == nullptr || from > to) {
        return false;
    }
    ParagraphImpl *impl = as_paragraph_impl(paragraph);
    if (impl == nullptr || from != 0 || to != impl->text().size()) {
        return false;
    }
    impl->updateForegroundPaint(from, to, *as_paint(paint));
    return true;
}

bool SkParagraph_Paragraph_updateBackgroundPaint(reskia_paragraph_t *paragraph, size_t from, size_t to, const reskia_paint_t *paint) {
    if (paragraph == nullptr || paint == nullptr || from > to) {
        return false;
    }
    ParagraphImpl *impl = as_paragraph_impl(paragraph);
    if (impl == nullptr || from != 0 || to != impl->text().size()) {
        return false;
    }
    impl->updateBackgroundPaint(from, to, *as_paint(paint));
    return true;
}

} // extern "C"
