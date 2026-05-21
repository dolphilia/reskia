//
// Created by dolphilia on 2024/01/09.
//

#include "sk_open_type_svg_decoder.h"

#include <vector>

#include "include/core/SkCanvas.h"

#if defined(__APPLE__)
#include "modules/svg/include/SkSVGOpenTypeSVGDecoder.h"
#endif

extern "C" {

void SkOpenTypeSVGDecoder_delete(SkOpenTypeSVGDecoder *open_type_svg_decoder) {
    delete open_type_svg_decoder;
}

size_t SkOpenTypeSVGDecoder_approximateSize(SkOpenTypeSVGDecoder *open_type_svg_decoder) {
    if (open_type_svg_decoder == nullptr) {
        return 0;
    }
    return open_type_svg_decoder->approximateSize();
}

bool SkOpenTypeSVGDecoder_render(SkOpenTypeSVGDecoder *open_type_svg_decoder, SkCanvas *canvas, int upem, SkGlyphID glyphId, SkColor foregroundColor, SkColor color) {
    if (open_type_svg_decoder == nullptr || canvas == nullptr) {
        return false;
    }
    SkColor palette_colors[] = {color};
    return open_type_svg_decoder->render(*canvas, upem, glyphId, foregroundColor, palette_colors);
}

reskia_open_type_svg_decoder_t *SkSVGOpenTypeSVGDecoder_Make(const uint8_t *svg, size_t svg_length) {
#if defined(__APPLE__)
    if (svg == nullptr || svg_length == 0) {
        return nullptr;
    }
    return reinterpret_cast<reskia_open_type_svg_decoder_t *>(
            SkSVGOpenTypeSVGDecoder::Make(svg, svg_length).release());
#else
    (void)svg;
    (void)svg_length;
    return nullptr;
#endif
}

void SkSVGOpenTypeSVGDecoder_delete(reskia_open_type_svg_decoder_t *decoder) {
    delete reinterpret_cast<SkOpenTypeSVGDecoder *>(decoder);
}

size_t SkSVGOpenTypeSVGDecoder_approximateSize(reskia_open_type_svg_decoder_t *decoder) {
    return decoder != nullptr ? reinterpret_cast<SkOpenTypeSVGDecoder *>(decoder)->approximateSize() : 0;
}

bool SkSVGOpenTypeSVGDecoder_render(
        reskia_open_type_svg_decoder_t *decoder,
        reskia_canvas_t *canvas,
        int upem,
        uint16_t glyph_id,
        uint32_t foreground_color,
        const uint32_t *palette,
        int palette_count) {
    if (decoder == nullptr || canvas == nullptr || upem <= 0 || palette_count < 0 ||
        (palette_count > 0 && palette == nullptr)) {
        return false;
    }
    std::vector<SkColor> palette_colors;
    palette_colors.reserve(static_cast<size_t>(palette_count));
    for (int i = 0; i < palette_count; ++i) {
        palette_colors.push_back(static_cast<SkColor>(palette[i]));
    }
    return reinterpret_cast<SkOpenTypeSVGDecoder *>(decoder)->render(
            *reinterpret_cast<SkCanvas *>(canvas),
            upem,
            static_cast<SkGlyphID>(glyph_id),
            static_cast<SkColor>(foreground_color),
            SkSpan<SkColor>(palette_colors));
}

}
