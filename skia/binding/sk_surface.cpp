//
// Created by dolphilia on 2024/01/11.
//

#include "sk_surface.h"

#include "include/core/SkSurface.h"
#include "include/core/SkColorSpace.h"

#include "../static/static_sk_image_info.h"
#include "../static/static_sk_capabilities.h"
#include "../static/static_sk_surface.h"
#include "../static/static_sk_image.h"
#include "../static/static_sk_color_space.h"

#include "../static/static_sk_image-internal.h"
#include "../static/static_sk_image_info-internal.h"
#include "../static/static_sk_surface-internal.h"
#include "../static/static_sk_color_space-internal.h"
#include "../static/static_sk_color_space.h"
#include "../static/static_sk_capabilities-internal.h"

extern "C" {

void SkSurface_delete(reskia_surface_t *surface) {
    reinterpret_cast<SkSurface *>(surface)->unref();
}

bool SkSurface_isCompatible(reskia_surface_t *surface, const reskia_surface_characterization_t *characterization) {
    return reinterpret_cast<SkSurface *>(surface)->isCompatible(* reinterpret_cast<const GrSurfaceCharacterization *>(characterization));
}

int SkSurface_width(reskia_surface_t *surface) {
    return reinterpret_cast<SkSurface *>(surface)->width();
}

int SkSurface_height(reskia_surface_t *surface) {
    return reinterpret_cast<SkSurface *>(surface)->height();
}

sk_image_info_t SkSurface_imageInfo(reskia_surface_t *surface) {
    return static_sk_image_info_make(reinterpret_cast<SkSurface *>(surface)->imageInfo());
}

uint32_t SkSurface_generationID(reskia_surface_t *surface) {
    return reinterpret_cast<SkSurface *>(surface)->generationID();
}

void SkSurface_notifyContentWillChange(reskia_surface_t *surface, reskia_surface_content_change_mode_t mode) {
    reinterpret_cast<SkSurface *>(surface)->notifyContentWillChange(static_cast<SkSurface::ContentChangeMode>(mode));
}

reskia_recording_context_t *SkSurface_recordingContext(reskia_surface_t *surface) {
    return reinterpret_cast<reskia_recording_context_t *>(reinterpret_cast<SkSurface *>(surface)->recordingContext());
}

reskia_graphite_recorder_t *SkSurface_recorder(reskia_surface_t *surface) {
    return reinterpret_cast<reskia_graphite_recorder_t *>(reinterpret_cast<SkSurface *>(surface)->recorder());
}

bool SkSurface_replaceBackendTexture(reskia_surface_t *surface, const reskia_backend_texture_t *backendTexture, int origin, reskia_surface_content_change_mode_t mode, void(* proc)(void *), void * context) {
    return reinterpret_cast<SkSurface *>(surface)->replaceBackendTexture(* reinterpret_cast<const GrBackendTexture *>(backendTexture), static_cast<GrSurfaceOrigin>(origin), static_cast<SkSurface::ContentChangeMode>(mode), proc, context);
}

reskia_canvas_t *SkSurface_getCanvas(reskia_surface_t *surface) {
    return reinterpret_cast<reskia_canvas_t *>(reinterpret_cast<SkSurface *>(surface)->getCanvas());
}

const_sk_capabilities_t SkSurface_capabilities(reskia_surface_t *surface) {
    return static_const_sk_capabilities_make(reinterpret_cast<SkSurface *>(surface)->capabilities());
}

sk_surface_t SkSurface_makeSurface(reskia_surface_t *surface, const reskia_image_info_t *imageInfo) {
    return static_sk_surface_make(reinterpret_cast<SkSurface *>(surface)->makeSurface(* reinterpret_cast<const SkImageInfo *>(imageInfo)));
}

sk_surface_t SkSurface_makeSurface_2(reskia_surface_t *surface, int width, int height) {
    return static_sk_surface_make(reinterpret_cast<SkSurface *>(surface)->makeSurface(width, height));
}

sk_image_t SkSurface_makeImageSnapshot(reskia_surface_t *surface) {
    return static_sk_image_make(reinterpret_cast<SkSurface *>(surface)->makeImageSnapshot());
}

sk_image_t SkSurface_makeImageSnapshot_2(reskia_surface_t *surface, const reskia_i_rect_t *bounds) {
    return static_sk_image_make(reinterpret_cast<SkSurface *>(surface)->makeImageSnapshot(* reinterpret_cast<const SkIRect *>(bounds)));
}

void SkSurface_draw(reskia_surface_t *surface, reskia_canvas_t *canvas, float x, float y, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint) {
    reinterpret_cast<SkSurface *>(surface)->draw(reinterpret_cast<SkCanvas *>(canvas), x, y, * reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkPaint *>(paint));
}

void SkSurface_draw_2(reskia_surface_t *surface, reskia_canvas_t *canvas, float x, float y, const reskia_paint_t *paint) {
    reinterpret_cast<SkSurface *>(surface)->draw(reinterpret_cast<SkCanvas *>(canvas), x, y, reinterpret_cast<const SkPaint *>(paint));
}

bool SkSurface_peekPixels(reskia_surface_t *surface, reskia_pixmap_t *pixmap) {
    return reinterpret_cast<SkSurface *>(surface)->peekPixels(reinterpret_cast<SkPixmap *>(pixmap));
}

bool SkSurface_readPixels(reskia_surface_t *surface, const reskia_pixmap_t *dst, int srcX, int srcY) {
    return reinterpret_cast<SkSurface *>(surface)->readPixels(* reinterpret_cast<const SkPixmap *>(dst), srcX, srcY);
}

bool SkSurface_readPixels_2(reskia_surface_t *surface, const reskia_image_info_t *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY) {
    return reinterpret_cast<SkSurface *>(surface)->readPixels(* reinterpret_cast<const SkImageInfo *>(dstInfo), dstPixels, dstRowBytes, srcX, srcY);
}

bool SkSurface_readPixels_3(reskia_surface_t *surface, const reskia_bitmap_t *dst, int srcX, int srcY) {
    return reinterpret_cast<SkSurface *>(surface)->readPixels(* reinterpret_cast<const SkBitmap *>(dst), srcX, srcY);
}

void SkSurface_asyncRescaleAndReadPixels(void *surface, const void *info, const void *srcRect, int rescaleGamma, int rescaleMode, SkSurface::ReadPixelsCallback callback, void * context) {
    reinterpret_cast<SkSurface *>(surface)->asyncRescaleAndReadPixels(* static_cast<const SkImageInfo *>(info), * static_cast<const SkIRect *>(srcRect), static_cast<SkSurface::RescaleGamma>(rescaleGamma), static_cast<SkSurface::RescaleMode>(rescaleMode), callback, context);
}

void SkSurface_asyncRescaleAndReadPixelsYUV420(void *surface, sk_color_space_t dstColorSpace, int yuvColorSpace, const void *srcRect, const void *dstSize, int rescaleGamma, int rescaleMode, SkSurface::ReadPixelsCallback callback, void * context) {
    reinterpret_cast<SkSurface *>(surface)->asyncRescaleAndReadPixelsYUV420(static_cast<SkYUVColorSpace>(yuvColorSpace), static_sk_color_space_get_entity(dstColorSpace), * static_cast<const SkIRect *>(srcRect), * static_cast<const SkISize *>(dstSize), static_cast<SkSurface::RescaleGamma>(rescaleGamma), static_cast<SkSurface::RescaleMode>(rescaleMode), callback, context);
}

void SkSurface_asyncRescaleAndReadPixelsYUVA420(void *surface, sk_color_space_t dstColorSpace, int yuvColorSpace, const void *srcRect, const void *dstSize, int rescaleGamma, int rescaleMode, SkSurface::ReadPixelsCallback callback, void * context) {
    reinterpret_cast<SkSurface *>(surface)->asyncRescaleAndReadPixelsYUVA420(static_cast<SkYUVColorSpace>(yuvColorSpace), static_sk_color_space_get_entity(dstColorSpace), * static_cast<const SkIRect *>(srcRect), * static_cast<const SkISize *>(dstSize), static_cast<SkSurface::RescaleGamma>(rescaleGamma), static_cast<SkSurface::RescaleMode>(rescaleMode), callback, context);
}

void SkSurface_writePixels(reskia_surface_t *surface, const reskia_pixmap_t *src, int dstX, int dstY) {
    reinterpret_cast<SkSurface *>(surface)->writePixels(* reinterpret_cast<const SkPixmap *>(src), dstX, dstY);
}

void SkSurface_writePixels_2(reskia_surface_t *surface, const reskia_bitmap_t *src, int dstX, int dstY) {
    reinterpret_cast<SkSurface *>(surface)->writePixels(* reinterpret_cast<const SkBitmap *>(src), dstX, dstY);
}

const reskia_surface_props_t *SkSurface_props(reskia_surface_t *surface) {
    return reinterpret_cast<const reskia_surface_props_t *>(&reinterpret_cast<SkSurface *>(surface)->props());
}

bool SkSurface_wait(reskia_surface_t *surface, int numSemaphores, const reskia_backend_semaphore_t *waitSemaphores, bool deleteSemaphoresAfterWait) {
    return reinterpret_cast<SkSurface *>(surface)->wait(numSemaphores, reinterpret_cast<const GrBackendSemaphore *>(waitSemaphores), deleteSemaphoresAfterWait);
}

bool SkSurface_characterize(reskia_surface_t *surface, reskia_surface_characterization_t *characterization) {
    return reinterpret_cast<SkSurface *>(surface)->characterize(reinterpret_cast<GrSurfaceCharacterization *>(characterization));
}

bool SkSurface_unique(reskia_surface_t *surface) {
    return reinterpret_cast<SkSurface *>(surface)->unique();
}

void SkSurface_ref(reskia_surface_t *surface) {
    reinterpret_cast<SkSurface *>(surface)->ref();
}

void SkSurface_unref(reskia_surface_t *surface) {
    reinterpret_cast<SkSurface *>(surface)->unref();
}

}
