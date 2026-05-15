#include "sk_nway_canvas.h"

#include "include/core/SkCanvas.h"
#include "include/utils/SkNWayCanvas.h"

extern "C" {

reskia_nway_canvas_t *SkNWayCanvas_new(int width, int height) {
    return reinterpret_cast<reskia_nway_canvas_t *>(new SkNWayCanvas(width, height));
}

void SkNWayCanvas_delete(reskia_nway_canvas_t *canvas) {
    delete reinterpret_cast<SkNWayCanvas *>(canvas);
}

reskia_canvas_t *SkNWayCanvas_asCanvas(reskia_nway_canvas_t *canvas) {
    return reinterpret_cast<reskia_canvas_t *>(canvas);
}

void SkNWayCanvas_addCanvas(reskia_nway_canvas_t *canvas, reskia_canvas_t *target) {
    if (canvas != nullptr && target != nullptr) {
        reinterpret_cast<SkNWayCanvas *>(canvas)->addCanvas(reinterpret_cast<SkCanvas *>(target));
    }
}

void SkNWayCanvas_removeCanvas(reskia_nway_canvas_t *canvas, reskia_canvas_t *target) {
    if (canvas != nullptr && target != nullptr) {
        reinterpret_cast<SkNWayCanvas *>(canvas)->removeCanvas(reinterpret_cast<SkCanvas *>(target));
    }
}

void SkNWayCanvas_removeAll(reskia_nway_canvas_t *canvas) {
    if (canvas != nullptr) {
        reinterpret_cast<SkNWayCanvas *>(canvas)->removeAll();
    }
}

} // extern "C"
