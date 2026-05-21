//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_OPEN_TYPE_SVG_DECODER_H
#define RAIA_SKIA_SK_OPEN_TYPE_SVG_DECODER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "include/core/SkOpenTypeSVGDecoder.h"

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_open_type_svg_decoder_t reskia_open_type_svg_decoder_t;

extern "C" {
void SkOpenTypeSVGDecoder_delete(SkOpenTypeSVGDecoder *open_type_svg_decoder); // NULL open_type_svg_decoder is no-op.
size_t SkOpenTypeSVGDecoder_approximateSize(SkOpenTypeSVGDecoder *open_type_svg_decoder); // NULL open_type_svg_decoder returns 0.
/**
 * open_type_svg_decoder/canvas are required.
 */
bool SkOpenTypeSVGDecoder_render(SkOpenTypeSVGDecoder *open_type_svg_decoder, SkCanvas *canvas, int upem, SkGlyphID glyphId, SkColor foregroundColor, SkColor color);

reskia_open_type_svg_decoder_t *SkSVGOpenTypeSVGDecoder_Make(const uint8_t *svg, size_t svg_length);
void SkSVGOpenTypeSVGDecoder_delete(reskia_open_type_svg_decoder_t *decoder);
size_t SkSVGOpenTypeSVGDecoder_approximateSize(reskia_open_type_svg_decoder_t *decoder);
bool SkSVGOpenTypeSVGDecoder_render(reskia_open_type_svg_decoder_t *decoder, reskia_canvas_t *canvas, int upem, uint16_t glyph_id, uint32_t foreground_color, const uint32_t *palette, int palette_count);
}

#endif //RAIA_SKIA_SK_OPEN_TYPE_SVG_DECODER_H
