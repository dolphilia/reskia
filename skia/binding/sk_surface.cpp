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

void SkSurface_delete(void *surface) {
    delete static_cast<SkSurface *>(surface);
}

bool SkSurface_isCompatible(void *surface, const void *characterization) {
    return static_cast<SkSurface *>(surface)->isCompatible(* static_cast<const GrSurfaceCharacterization *>(characterization));
}

int SkSurface_width(void *surface) {
    return static_cast<SkSurface *>(surface)->width();
}

int SkSurface_height(void *surface) {
    return static_cast<SkSurface *>(surface)->height();
}

sk_image_info_t SkSurface_imageInfo(void *surface) {
    return static_sk_image_info_make(static_cast<SkSurface *>(surface)->imageInfo());
}

uint32_t SkSurface_generationID(void *surface) {
    return static_cast<SkSurface *>(surface)->generationID();
}

void SkSurface_notifyContentWillChange(void *surface, int mode) {
    static_cast<SkSurface *>(surface)->notifyContentWillChange(static_cast<SkSurface::ContentChangeMode>(mode));
}

void * SkSurface_recordingContext(void *surface) {
    return static_cast<SkSurface *>(surface)->recordingContext();
}

void * SkSurface_recorder(void *surface) {
    return static_cast<SkSurface *>(surface)->recorder();
}

bool SkSurface_replaceBackendTexture(void *surface, const void *backendTexture, int origin, int mode, void(* proc)(void *), void * context) {
    return static_cast<SkSurface *>(surface)->replaceBackendTexture(* static_cast<const GrBackendTexture *>(backendTexture), static_cast<GrSurfaceOrigin>(origin), static_cast<SkSurface::ContentChangeMode>(mode), proc, context);
}

void * SkSurface_getCanvas(void *surface) {
    return static_cast<SkSurface *>(surface)->getCanvas();
}

const_sk_capabilities_t SkSurface_capabilities(void *surface) {
    return static_const_sk_capabilities_make(static_cast<SkSurface *>(surface)->capabilities());
}

sk_surface_t SkSurface_makeSurface(void *surface, const void *imageInfo) {
    return static_sk_surface_make(static_cast<SkSurface *>(surface)->makeSurface(* static_cast<const SkImageInfo *>(imageInfo)));
}

sk_surface_t SkSurface_makeSurface_2(void *surface, int width, int height) {
    return static_sk_surface_make(static_cast<SkSurface *>(surface)->makeSurface(width, height));
}

sk_image_t SkSurface_makeImageSnapshot(void *surface) {
    return static_sk_image_make(static_cast<SkSurface *>(surface)->makeImageSnapshot());
}

sk_image_t SkSurface_makeImageSnapshot_2(void *surface, const void *bounds) {
    return static_sk_image_make(static_cast<SkSurface *>(surface)->makeImageSnapshot(* static_cast<const SkIRect *>(bounds)));
}

void SkSurface_draw(void *surface, void *canvas, float x, float y, const void *sampling, const void *paint) {
    static_cast<SkSurface *>(surface)->draw(static_cast<SkCanvas *>(canvas), x, y, * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkPaint *>(paint));
}

void SkSurface_draw_2(void *surface, void *canvas, float x, float y, const void *paint) {
    static_cast<SkSurface *>(surface)->draw(static_cast<SkCanvas *>(canvas), x, y, static_cast<const SkPaint *>(paint));
}

bool SkSurface_peekPixels(void *surface, void *pixmap) {
    return static_cast<SkSurface *>(surface)->peekPixels(static_cast<SkPixmap *>(pixmap));
}

bool SkSurface_readPixels(void *surface, const void *dst, int srcX, int srcY) {
    return static_cast<SkSurface *>(surface)->readPixels(* static_cast<const SkPixmap *>(dst), srcX, srcY);
}

bool SkSurface_readPixels_2(void *surface, const void *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY) {
    return static_cast<SkSurface *>(surface)->readPixels(* static_cast<const SkImageInfo *>(dstInfo), dstPixels, dstRowBytes, srcX, srcY);
}

bool SkSurface_readPixels_3(void *surface, const void *dst, int srcX, int srcY) {
    return static_cast<SkSurface *>(surface)->readPixels(* static_cast<const SkBitmap *>(dst), srcX, srcY);
}

void SkSurface_asyncRescaleAndReadPixels(void *surface, const void *info, const void *srcRect, int rescaleGamma, int rescaleMode, SkSurface::ReadPixelsCallback callback, void * context) {
    static_cast<SkSurface *>(surface)->asyncRescaleAndReadPixels(* static_cast<const SkImageInfo *>(info), * static_cast<const SkIRect *>(srcRect), static_cast<SkSurface::RescaleGamma>(rescaleGamma), static_cast<SkSurface::RescaleMode>(rescaleMode), callback, context);
}

void SkSurface_asyncRescaleAndReadPixelsYUV420(void *surface, sk_color_space_t dstColorSpace, int yuvColorSpace, const void *srcRect, const void *dstSize, int rescaleGamma, int rescaleMode, SkSurface::ReadPixelsCallback callback, void * context) {
    static_cast<SkSurface *>(surface)->asyncRescaleAndReadPixelsYUV420(static_cast<SkYUVColorSpace>(yuvColorSpace), static_sk_color_space_get_entity(dstColorSpace), * static_cast<const SkIRect *>(srcRect), * static_cast<const SkISize *>(dstSize), static_cast<SkSurface::RescaleGamma>(rescaleGamma), static_cast<SkSurface::RescaleMode>(rescaleMode), callback, context);
}

void SkSurface_asyncRescaleAndReadPixelsYUVA420(void *surface, sk_color_space_t dstColorSpace, int yuvColorSpace, const void *srcRect, const void *dstSize, int rescaleGamma, int rescaleMode, SkSurface::ReadPixelsCallback callback, void * context) {
    static_cast<SkSurface *>(surface)->asyncRescaleAndReadPixelsYUVA420(static_cast<SkYUVColorSpace>(yuvColorSpace), static_sk_color_space_get_entity(dstColorSpace), * static_cast<const SkIRect *>(srcRect), * static_cast<const SkISize *>(dstSize), static_cast<SkSurface::RescaleGamma>(rescaleGamma), static_cast<SkSurface::RescaleMode>(rescaleMode), callback, context);
}

void SkSurface_writePixels(void *surface, const void *src, int dstX, int dstY) {
    static_cast<SkSurface *>(surface)->writePixels(* static_cast<const SkPixmap *>(src), dstX, dstY);
}

void SkSurface_writePixels_2(void *surface, const void *src, int dstX, int dstY) {
    static_cast<SkSurface *>(surface)->writePixels(* static_cast<const SkBitmap *>(src), dstX, dstY);
}

const void * SkSurface_props(void *surface) {
    return &static_cast<SkSurface *>(surface)->props();
}

bool SkSurface_wait(void *surface, int numSemaphores, const void *waitSemaphores, bool deleteSemaphoresAfterWait) {
    return static_cast<SkSurface *>(surface)->wait(numSemaphores, static_cast<const GrBackendSemaphore *>(waitSemaphores), deleteSemaphoresAfterWait);
}

bool SkSurface_characterize(void *surface, void *characterization) {
    return static_cast<SkSurface *>(surface)->characterize(static_cast<GrSurfaceCharacterization *>(characterization));
}

bool SkSurface_unique(void *surface) {
    return static_cast<SkSurface *>(surface)->unique();
}

void SkSurface_ref(void *surface) {
    static_cast<SkSurface *>(surface)->ref();
}

void SkSurface_unref(void *surface) {
    static_cast<SkSurface *>(surface)->unref();
}

}