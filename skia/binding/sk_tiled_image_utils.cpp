//
// Created by dolphilia on 2024/01/13.
//

#include "sk_tiled_image_utils.h"

#include "include/core/SkTiledImageUtils.h"

extern "C" {

void SkTiledImageUtils_DrawImageRect(reskia_canvas_t *canvas, const reskia_image_t *image, const reskia_rect_t *src, const reskia_rect_t *dst, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint, int constraint) {
    SkTiledImageUtils::DrawImageRect(reinterpret_cast<SkCanvas *>(canvas), reinterpret_cast<const SkImage *>(image), * reinterpret_cast<const SkRect *>(src), * reinterpret_cast<const SkRect *>(dst), * reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkPaint *>(paint), static_cast<SkCanvas::SrcRectConstraint>(constraint));
}

void SkTiledImageUtils_DrawImageRect_2(reskia_canvas_t *canvas, const reskia_image_sp_t *image, const reskia_rect_t *src, const reskia_rect_t *dst, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint, int constraint) {
    SkTiledImageUtils::DrawImageRect(reinterpret_cast<SkCanvas *>(canvas), * reinterpret_cast<const sk_sp<SkImage> *>(image), * reinterpret_cast<const SkRect *>(src), * reinterpret_cast<const SkRect *>(dst), * reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkPaint *>(paint), static_cast<SkCanvas::SrcRectConstraint>(constraint));
}

void SkTiledImageUtils_DrawImageRect_3(reskia_canvas_t *canvas, const reskia_image_t *image, const reskia_rect_t *dst, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint, int constraint) {
    SkTiledImageUtils::DrawImageRect(reinterpret_cast<SkCanvas *>(canvas), reinterpret_cast<const SkImage *>(image), * reinterpret_cast<const SkRect *>(dst), * reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkPaint *>(paint), static_cast<SkCanvas::SrcRectConstraint>(constraint));
}

void SkTiledImageUtils_DrawImageRect_4(reskia_canvas_t *canvas, const reskia_image_sp_t *image, const reskia_rect_t *dst, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint, int constraint) {
    SkTiledImageUtils::DrawImageRect(reinterpret_cast<SkCanvas *>(canvas), * reinterpret_cast<const sk_sp<SkImage> *>(image), * reinterpret_cast<const SkRect *>(dst), * reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkPaint *>(paint), static_cast<SkCanvas::SrcRectConstraint>(constraint));
}

void SkTiledImageUtils_DrawImage(reskia_canvas_t *canvas, const reskia_image_t *image, float x, float y, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint, int constraint) {
    SkTiledImageUtils::DrawImage(reinterpret_cast<SkCanvas *>(canvas), reinterpret_cast<const SkImage *>(image), x, y, * reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkPaint *>(paint), static_cast<SkCanvas::SrcRectConstraint>(constraint));
}

void SkTiledImageUtils_DrawImage_2(reskia_canvas_t *canvas, const reskia_image_sp_t *image, float x, float y, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint, int constraint) {
    SkTiledImageUtils::DrawImage(reinterpret_cast<SkCanvas *>(canvas), * reinterpret_cast<const sk_sp<SkImage> *>(image), x, y, * reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkPaint *>(paint), static_cast<SkCanvas::SrcRectConstraint>(constraint));
}

void SkTiledImageUtils_GetImageKeyValues(const reskia_image_t *image, uint32_t * keyValues) {
    SkTiledImageUtils::GetImageKeyValues(reinterpret_cast<const SkImage *>(image), keyValues);
}

}
