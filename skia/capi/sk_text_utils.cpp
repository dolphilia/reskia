#include "sk_text_utils.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkFont.h"
#include "include/core/SkPaint.h"
#include "include/core/SkPath.h"
#include "include/utils/SkTextUtils.h"

namespace {

bool is_valid_text_encoding(reskia_text_utils_text_encoding_t encoding) {
    return encoding >= static_cast<reskia_text_utils_text_encoding_t>(SkTextEncoding::kUTF8) &&
           encoding <= static_cast<reskia_text_utils_text_encoding_t>(SkTextEncoding::kGlyphID);
}

bool is_valid_align(reskia_text_utils_align_t align) {
    return align >= SkTextUtils::kLeft_Align && align <= SkTextUtils::kRight_Align;
}

} // namespace

extern "C" {

void SkTextUtils_Draw(reskia_canvas_t *canvas, const void *text, size_t size, reskia_text_utils_text_encoding_t encoding, float x, float y, const reskia_font_t *font, const reskia_paint_t *paint, reskia_text_utils_align_t align) {
    if (canvas == nullptr || font == nullptr || paint == nullptr ||
        (size > 0 && text == nullptr) || !is_valid_text_encoding(encoding) || !is_valid_align(align)) {
        return;
    }
    SkTextUtils::Draw(
            reinterpret_cast<SkCanvas *>(canvas),
            text,
            size,
            static_cast<SkTextEncoding>(encoding),
            x,
            y,
            *reinterpret_cast<const SkFont *>(font),
            *reinterpret_cast<const SkPaint *>(paint),
            static_cast<SkTextUtils::Align>(align));
}

void SkTextUtils_DrawString(reskia_canvas_t *canvas, const char text[], float x, float y, const reskia_font_t *font, const reskia_paint_t *paint, reskia_text_utils_align_t align) {
    if (canvas == nullptr || text == nullptr || font == nullptr || paint == nullptr || !is_valid_align(align)) {
        return;
    }
    SkTextUtils::DrawString(
            reinterpret_cast<SkCanvas *>(canvas),
            text,
            x,
            y,
            *reinterpret_cast<const SkFont *>(font),
            *reinterpret_cast<const SkPaint *>(paint),
            static_cast<SkTextUtils::Align>(align));
}

void SkTextUtils_GetPath(const void *text, size_t length, reskia_text_utils_text_encoding_t encoding, float x, float y, const reskia_font_t *font, reskia_path_t *path) {
    if (font == nullptr || path == nullptr || (length > 0 && text == nullptr) || !is_valid_text_encoding(encoding)) {
        return;
    }
    SkTextUtils::GetPath(
            text,
            length,
            static_cast<SkTextEncoding>(encoding),
            x,
            y,
            *reinterpret_cast<const SkFont *>(font),
            reinterpret_cast<SkPath *>(path));
}

} // extern "C"
