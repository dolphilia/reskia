//
// Created by Codex on 2026/05/14.
//

#include "sk_svg_canvas.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkRect.h"
#include "include/core/SkStream.h"
#include "include/svg/SkSVGCanvas.h"

extern "C" {

reskia_canvas_t *SkSVGCanvas_Make(float left, float top, float right, float bottom, reskia_w_stream_t *stream, uint32_t flags) {
    if (stream == nullptr) {
        return nullptr;
    }
    auto canvas = SkSVGCanvas::Make(SkRect::MakeLTRB(left, top, right, bottom), reinterpret_cast<SkWStream *>(stream), flags);
    return reinterpret_cast<reskia_canvas_t *>(canvas.release());
}

}
