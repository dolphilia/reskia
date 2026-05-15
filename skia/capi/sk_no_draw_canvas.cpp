#include "sk_no_draw_canvas.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkRect.h"
#include "include/utils/SkNoDrawCanvas.h"

extern "C" {

reskia_no_draw_canvas_t *SkNoDrawCanvas_new(int width, int height) {
    return reinterpret_cast<reskia_no_draw_canvas_t *>(new SkNoDrawCanvas(width, height));
}

reskia_no_draw_canvas_t *SkNoDrawCanvas_newWithIRect(const reskia_i_rect_t *rect) {
    if (rect == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_no_draw_canvas_t *>(
            new SkNoDrawCanvas(*reinterpret_cast<const SkIRect *>(rect)));
}

void SkNoDrawCanvas_delete(reskia_no_draw_canvas_t *canvas) {
    delete reinterpret_cast<SkNoDrawCanvas *>(canvas);
}

reskia_canvas_t *SkNoDrawCanvas_asCanvas(reskia_no_draw_canvas_t *canvas) {
    return reinterpret_cast<reskia_canvas_t *>(canvas);
}

void SkNoDrawCanvas_resetCanvas(reskia_no_draw_canvas_t *canvas, int width, int height) {
    if (canvas != nullptr) {
        reinterpret_cast<SkNoDrawCanvas *>(canvas)->resetCanvas(width, height);
    }
}

void SkNoDrawCanvas_resetCanvasWithIRect(reskia_no_draw_canvas_t *canvas, const reskia_i_rect_t *rect) {
    if (canvas != nullptr && rect != nullptr) {
        reinterpret_cast<SkNoDrawCanvas *>(canvas)->resetCanvas(*reinterpret_cast<const SkIRect *>(rect));
    }
}

} // extern "C"
