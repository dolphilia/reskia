//
// Created by dolphilia on 2024/01/05.
//

#include "sk_annotation.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkAnnotation.h"

namespace {

bool has_annotation_inputs(const reskia_canvas_t *canvas, const void *geometry, const reskia_data_t *data) {
    return canvas != nullptr && geometry != nullptr && data != nullptr;
}

}  // namespace

#ifdef __cplusplus
extern "C" {
#endif

void SkAnnotation_SkAnnotateLinkToDestination(reskia_canvas_t *canvas, const reskia_rect_t *rect, reskia_data_t *data) {
    if (!has_annotation_inputs(canvas, rect, data)) {
        return;
    }
    SkAnnotateLinkToDestination(reinterpret_cast<SkCanvas *>(canvas), *reinterpret_cast<const SkRect *>(rect), reinterpret_cast<SkData *>(data));
}

void SkAnnotation_SkAnnotateNamedDestination(reskia_canvas_t *canvas, const reskia_point_t *point, reskia_data_t *data) {
    if (!has_annotation_inputs(canvas, point, data)) {
        return;
    }
    SkAnnotateNamedDestination(reinterpret_cast<SkCanvas *>(canvas), *reinterpret_cast<const SkPoint *>(point), reinterpret_cast<SkData *>(data));
}

void SkAnnotation_SkAnnotateRectWithURL(reskia_canvas_t *canvas, const reskia_rect_t *rect, reskia_data_t *data) {
    if (!has_annotation_inputs(canvas, rect, data)) {
        return;
    }
    SkAnnotateRectWithURL(reinterpret_cast<SkCanvas *>(canvas), *reinterpret_cast<const SkRect *>(rect), reinterpret_cast<SkData *>(data));
}

#ifdef __cplusplus
}
#endif
