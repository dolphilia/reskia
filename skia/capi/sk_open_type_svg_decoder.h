//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_OPEN_TYPE_SVG_DECODER_H
#define RAIA_SKIA_SK_OPEN_TYPE_SVG_DECODER_H

#include "include/core/SkOpenTypeSVGDecoder.h"

extern "C" {
void SkOpenTypeSVGDecoder_delete(SkOpenTypeSVGDecoder *open_type_svg_decoder); // NULL open_type_svg_decoder is no-op.
size_t SkOpenTypeSVGDecoder_approximateSize(SkOpenTypeSVGDecoder *open_type_svg_decoder); // NULL open_type_svg_decoder returns 0.
/**
 * open_type_svg_decoder/canvas are required.
 */
bool SkOpenTypeSVGDecoder_render(SkOpenTypeSVGDecoder *open_type_svg_decoder, SkCanvas *canvas, int upem, SkGlyphID glyphId, SkColor foregroundColor, SkColor color);
}

#endif //RAIA_SKIA_SK_OPEN_TYPE_SVG_DECODER_H
