//
// Created by Codex on 2026/05/14.
//

#ifndef RAIA_SKIA_SK_SVG_CANVAS_H
#define RAIA_SKIA_SK_SVG_CANVAS_H

#include <stdint.h>

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_w_stream_t reskia_w_stream_t;

#ifdef __cplusplus
extern "C" {
#endif

enum {
    RESKIA_SVG_CANVAS_CONVERT_TEXT_TO_PATHS_FLAG = 0x01,
    RESKIA_SVG_CANVAS_NO_PRETTY_XML_FLAG = 0x02,
    RESKIA_SVG_CANVAS_RELATIVE_PATH_ENCODING_FLAG = 0x04,
};

/**
 * stream: borrowed; it must remain valid until the returned canvas is deleted.
 * Returns a caller-owned canvas pointer, deleted with SkCanvas_delete.
 * Returns NULL when stream is NULL or Skia cannot create the SVG canvas.
 * Skia: SkSVGCanvas::Make(const SkRect& bounds, SkWStream*, uint32_t flags).
 */
reskia_canvas_t *SkSVGCanvas_Make(float left, float top, float right, float bottom, reskia_w_stream_t *stream, uint32_t flags);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_SVG_CANVAS_H
