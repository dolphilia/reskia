//
// Created by dolphilia on 2024/01/13.
//

#include "sk_tiled_image_utils.h"

#include "include/core/SkTiledImageUtils.h"

extern "C" {

void SkTiledImageUtils_DrawImageRect(void *canvas, const void *image, const void *src, const void *dst, const void *sampling, const void *paint, int constraint) {
    SkTiledImageUtils::DrawImageRect(static_cast<SkCanvas *>(canvas), static_cast<const SkImage *>(image), * static_cast<const SkRect *>(src), * static_cast<const SkRect *>(dst), * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkPaint *>(paint), static_cast<SkCanvas::SrcRectConstraint>(constraint));
}

void SkTiledImageUtils_DrawImageRect_2(void *canvas, const void *image, const void *src, const void *dst, const void *sampling, const void *paint, int constraint) {
    SkTiledImageUtils::DrawImageRect(static_cast<SkCanvas *>(canvas), * static_cast<const sk_sp<SkImage> *>(image), * static_cast<const SkRect *>(src), * static_cast<const SkRect *>(dst), * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkPaint *>(paint), static_cast<SkCanvas::SrcRectConstraint>(constraint));
}

void SkTiledImageUtils_DrawImageRect_3(void *canvas, const void *image, const void *dst, const void *sampling, const void *paint, int constraint) {
    SkTiledImageUtils::DrawImageRect(static_cast<SkCanvas *>(canvas), static_cast<const SkImage *>(image), * static_cast<const SkRect *>(dst), * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkPaint *>(paint), static_cast<SkCanvas::SrcRectConstraint>(constraint));
}

void SkTiledImageUtils_DrawImageRect_4(void *canvas, const void *image, const void *dst, const void *sampling, const void *paint, int constraint) {
    SkTiledImageUtils::DrawImageRect(static_cast<SkCanvas *>(canvas), * static_cast<const sk_sp<SkImage> *>(image), * static_cast<const SkRect *>(dst), * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkPaint *>(paint), static_cast<SkCanvas::SrcRectConstraint>(constraint));
}

void SkTiledImageUtils_DrawImage(void *canvas, const void *image, float x, float y, const void *sampling, const void *paint, int constraint) {
    SkTiledImageUtils::DrawImage(static_cast<SkCanvas *>(canvas), static_cast<const SkImage *>(image), x, y, * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkPaint *>(paint), static_cast<SkCanvas::SrcRectConstraint>(constraint));
}

void SkTiledImageUtils_DrawImage_2(void *canvas, const void *image, float x, float y, const void *sampling, const void *paint, int constraint) {
    SkTiledImageUtils::DrawImage(static_cast<SkCanvas *>(canvas), * static_cast<const sk_sp<SkImage> *>(image), x, y, * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkPaint *>(paint), static_cast<SkCanvas::SrcRectConstraint>(constraint));
}

void SkTiledImageUtils_GetImageKeyValues(const void *image, void * keyValues) {
    SkTiledImageUtils::GetImageKeyValues(static_cast<const SkImage *>(image), static_cast<uint32_t *>(keyValues));
}

}