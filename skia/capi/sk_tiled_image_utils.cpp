//
// Created by dolphilia on 2024/01/13.
//

#include "sk_tiled_image_utils.h"

#include "include/core/SkTiledImageUtils.h"

namespace {

SkCanvas *as_canvas(reskia_canvas_t *canvas) {
    return reinterpret_cast<SkCanvas *>(canvas);
}

const SkImage *as_image(const reskia_image_t *image) {
    return reinterpret_cast<const SkImage *>(image);
}

const sk_sp<SkImage> *as_image_sp(const reskia_image_sp_t *image) {
    return reinterpret_cast<const sk_sp<SkImage> *>(image);
}

const SkRect *as_rect(const reskia_rect_t *rect) {
    return reinterpret_cast<const SkRect *>(rect);
}

const SkSamplingOptions *as_sampling(const reskia_sampling_options_t *sampling) {
    return reinterpret_cast<const SkSamplingOptions *>(sampling);
}

const SkPaint *as_paint(const reskia_paint_t *paint) {
    return reinterpret_cast<const SkPaint *>(paint);
}

SkCanvas::SrcRectConstraint as_constraint(reskia_tiled_image_utils_src_rect_constraint_t constraint) {
    return static_cast<SkCanvas::SrcRectConstraint>(constraint);
}

} // namespace

extern "C" {

void SkTiledImageUtils_DrawImageRect(reskia_canvas_t *canvas, const reskia_image_t *image, const reskia_rect_t *src, const reskia_rect_t *dst, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint, reskia_tiled_image_utils_src_rect_constraint_t constraint) {
    SkCanvas *native_canvas = as_canvas(canvas);
    const SkImage *native_image = as_image(image);
    const SkRect *native_src = as_rect(src);
    const SkRect *native_dst = as_rect(dst);
    const SkSamplingOptions *native_sampling = as_sampling(sampling);
    if (native_canvas == nullptr || native_image == nullptr || native_src == nullptr || native_dst == nullptr || native_sampling == nullptr) {
        return;
    }
    SkTiledImageUtils::DrawImageRect(native_canvas, native_image, *native_src, *native_dst, *native_sampling, as_paint(paint), as_constraint(constraint));
}

void SkTiledImageUtils_DrawImageRectWithImageSp(reskia_canvas_t *canvas, const reskia_image_sp_t *image, const reskia_rect_t *src, const reskia_rect_t *dst, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint, reskia_tiled_image_utils_src_rect_constraint_t constraint) {
    SkCanvas *native_canvas = as_canvas(canvas);
    const sk_sp<SkImage> *native_image = as_image_sp(image);
    const SkRect *native_src = as_rect(src);
    const SkRect *native_dst = as_rect(dst);
    const SkSamplingOptions *native_sampling = as_sampling(sampling);
    if (native_canvas == nullptr || native_image == nullptr || native_src == nullptr || native_dst == nullptr || native_sampling == nullptr) {
        return;
    }
    SkTiledImageUtils::DrawImageRect(native_canvas, *native_image, *native_src, *native_dst, *native_sampling, as_paint(paint), as_constraint(constraint));
}

void SkTiledImageUtils_DrawImageRectWithDst(reskia_canvas_t *canvas, const reskia_image_t *image, const reskia_rect_t *dst, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint, reskia_tiled_image_utils_src_rect_constraint_t constraint) {
    SkCanvas *native_canvas = as_canvas(canvas);
    const SkImage *native_image = as_image(image);
    const SkRect *native_dst = as_rect(dst);
    const SkSamplingOptions *native_sampling = as_sampling(sampling);
    if (native_canvas == nullptr || native_image == nullptr || native_dst == nullptr || native_sampling == nullptr) {
        return;
    }
    SkTiledImageUtils::DrawImageRect(native_canvas, native_image, *native_dst, *native_sampling, as_paint(paint), as_constraint(constraint));
}

void SkTiledImageUtils_DrawImageRectWithImageSpAndDst(reskia_canvas_t *canvas, const reskia_image_sp_t *image, const reskia_rect_t *dst, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint, reskia_tiled_image_utils_src_rect_constraint_t constraint) {
    SkCanvas *native_canvas = as_canvas(canvas);
    const sk_sp<SkImage> *native_image = as_image_sp(image);
    const SkRect *native_dst = as_rect(dst);
    const SkSamplingOptions *native_sampling = as_sampling(sampling);
    if (native_canvas == nullptr || native_image == nullptr || native_dst == nullptr || native_sampling == nullptr) {
        return;
    }
    SkTiledImageUtils::DrawImageRect(native_canvas, *native_image, *native_dst, *native_sampling, as_paint(paint), as_constraint(constraint));
}

void SkTiledImageUtils_DrawImage(reskia_canvas_t *canvas, const reskia_image_t *image, float x, float y, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint, reskia_tiled_image_utils_src_rect_constraint_t constraint) {
    SkCanvas *native_canvas = as_canvas(canvas);
    const SkImage *native_image = as_image(image);
    const SkSamplingOptions *native_sampling = as_sampling(sampling);
    if (native_canvas == nullptr || native_image == nullptr || native_sampling == nullptr) {
        return;
    }
    SkTiledImageUtils::DrawImage(native_canvas, native_image, x, y, *native_sampling, as_paint(paint), as_constraint(constraint));
}

void SkTiledImageUtils_DrawImageWithImageSp(reskia_canvas_t *canvas, const reskia_image_sp_t *image, float x, float y, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint, reskia_tiled_image_utils_src_rect_constraint_t constraint) {
    SkCanvas *native_canvas = as_canvas(canvas);
    const sk_sp<SkImage> *native_image = as_image_sp(image);
    const SkSamplingOptions *native_sampling = as_sampling(sampling);
    if (native_canvas == nullptr || native_image == nullptr || native_sampling == nullptr) {
        return;
    }
    SkTiledImageUtils::DrawImage(native_canvas, *native_image, x, y, *native_sampling, as_paint(paint), as_constraint(constraint));
}

void SkTiledImageUtils_GetImageKeyValues(const reskia_image_t *image, uint32_t * keyValues) {
    SkTiledImageUtils::GetImageKeyValues(as_image(image), keyValues);
}

}
