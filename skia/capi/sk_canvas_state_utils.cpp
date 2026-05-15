#include "sk_canvas_state_utils.h"

#include "include/core/SkCanvas.h"
#include "include/utils/SkCanvasStateUtils.h"

extern "C" {

reskia_canvas_state_t *SkCanvasStateUtils_CaptureCanvasState(reskia_canvas_t *canvas) {
    if (canvas == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_canvas_state_t *>(
            SkCanvasStateUtils::CaptureCanvasState(reinterpret_cast<SkCanvas *>(canvas)));
}

reskia_canvas_t *SkCanvasStateUtils_MakeFromCanvasState(const reskia_canvas_state_t *state) {
    if (state == nullptr) {
        return nullptr;
    }
    std::unique_ptr<SkCanvas> canvas = SkCanvasStateUtils::MakeFromCanvasState(
            reinterpret_cast<const SkCanvasState *>(state));
    return reinterpret_cast<reskia_canvas_t *>(canvas.release());
}

void SkCanvasStateUtils_ReleaseCanvasState(reskia_canvas_state_t *state) {
    SkCanvasStateUtils::ReleaseCanvasState(reinterpret_cast<SkCanvasState *>(state));
}

} // extern "C"
