//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_SURFACE_H
#define RAIA_SKIA_SK_SURFACE_H

#include <stddef.h>
#include <stdint.h>

typedef struct reskia_backend_semaphore_t reskia_backend_semaphore_t;
typedef struct reskia_backend_texture_t reskia_backend_texture_t;
typedef struct reskia_bitmap_t reskia_bitmap_t;
typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_capabilities_t reskia_capabilities_t;
typedef struct reskia_graphite_recorder_t reskia_graphite_recorder_t;
typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_image_info_t reskia_image_info_t;
typedef struct reskia_paint_t reskia_paint_t;
typedef struct reskia_pixmap_t reskia_pixmap_t;
typedef struct reskia_recording_context_t reskia_recording_context_t;
typedef struct reskia_sampling_options_t reskia_sampling_options_t;
typedef struct reskia_surface_characterization_t reskia_surface_characterization_t;
typedef struct reskia_surface_props_t reskia_surface_props_t;
typedef struct reskia_surface_t reskia_surface_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkSurface_delete(reskia_surface_t *surface); // owned: caller が保持する参照を release する (SkSurface *surface)
bool SkSurface_isCompatible(reskia_surface_t *surface, const reskia_surface_characterization_t *characterization); // (SkSurface *surface, const GrSurfaceCharacterization *characterization) -> bool
int SkSurface_width(reskia_surface_t *surface); // (SkSurface *surface) -> int
int SkSurface_height(reskia_surface_t *surface); // (SkSurface *surface) -> int
int SkSurface_imageInfo(reskia_surface_t *surface); // (SkSurface *surface) -> sk_image_info_t
uint32_t SkSurface_generationID(reskia_surface_t *surface); // (SkSurface *surface) -> uint32_t
void SkSurface_notifyContentWillChange(reskia_surface_t *surface, int mode); // (SkSurface *surface, SkSurface::ContentChangeMode mode)
reskia_recording_context_t *SkSurface_recordingContext(reskia_surface_t *surface); // borrowed: 解放不要の借用ポインタ (SkSurface *surface) -> GrRecordingContext *
reskia_graphite_recorder_t *SkSurface_recorder(reskia_surface_t *surface); // borrowed: 解放不要の借用ポインタ (SkSurface *surface) -> skgpu::graphite::Recorder *
bool SkSurface_replaceBackendTexture(reskia_surface_t *surface, const reskia_backend_texture_t *backendTexture, int origin, int mode, void(* proc)(void *), void * context); // (SkSurface *surface, const GrBackendTexture *backendTexture, GrSurfaceOrigin origin, SkSurface::ContentChangeMode mode, SkSurface::TextureReleaseProc proc, SkSurface::ReleaseContext context) -> bool
reskia_canvas_t *SkSurface_getCanvas(reskia_surface_t *surface); // borrowed: 解放不要の借用ポインタ (SkSurface *surface) -> SkCanvas *
int SkSurface_capabilities(reskia_surface_t *surface); // (SkSurface *surface) -> const_sk_capabilities_t
int SkSurface_makeSurface(reskia_surface_t *surface, const reskia_image_info_t *imageInfo); // (SkSurface *surface, const SkImageInfo *imageInfo) -> sk_surface_t
int SkSurface_makeSurface_2(reskia_surface_t *surface, int width, int height); // (SkSurface *surface, int width, int height) -> sk_surface_t
int SkSurface_makeImageSnapshot(reskia_surface_t *surface); // (SkSurface *surface) -> sk_image_t
int SkSurface_makeImageSnapshot_2(reskia_surface_t *surface, const reskia_i_rect_t *bounds); // (SkSurface *surface, const SkIRect *bounds) -> sk_image_t
void SkSurface_draw(reskia_surface_t *surface, reskia_canvas_t *canvas, float x, float y, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint); // (SkSurface *surface, SkCanvas *canvas, SkScalar x, SkScalar y, const SkSamplingOptions *sampling, const SkPaint *paint)
void SkSurface_draw_2(reskia_surface_t *surface, reskia_canvas_t *canvas, float x, float y, const reskia_paint_t *paint); // (SkSurface *surface, SkCanvas *canvas, SkScalar x, SkScalar y, const SkPaint *paint)
bool SkSurface_peekPixels(reskia_surface_t *surface, reskia_pixmap_t *pixmap); // (SkSurface *surface, SkPixmap *pixmap) -> bool
bool SkSurface_readPixels(reskia_surface_t *surface, const reskia_pixmap_t *dst, int srcX, int srcY); // (SkSurface *surface, const SkPixmap *dst, int srcX, int srcY) -> bool
bool SkSurface_readPixels_2(reskia_surface_t *surface, const reskia_image_info_t *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY); // (SkSurface *surface, const SkImageInfo *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY) -> bool
bool SkSurface_readPixels_3(reskia_surface_t *surface, const reskia_bitmap_t *dst, int srcX, int srcY); // (SkSurface *surface, const SkBitmap *dst, int srcX, int srcY) -> bool

// TODO
// void SkSurface_asyncRescaleAndReadPixels(void *surface, const void *info, const void *srcRect, int rescaleGamma, int rescaleMode, SkSurface::ReadPixelsCallback callback, void * context); // (SkSurface *surface, const SkImageInfo *info, const SkIRect *srcRect, SkSurface::RescaleGamma rescaleGamma, SkSurface::RescaleMode rescaleMode, SkSurface::ReadPixelsCallback callback, SkSurface::ReadPixelsContext context)
// void SkSurface_asyncRescaleAndReadPixelsYUV420(void *surface, sk_color_space_t dstColorSpace, int yuvColorSpace, const void *srcRect, const void *dstSize, int rescaleGamma, int rescaleMode, SkSurface::ReadPixelsCallback callback, void * context); // (SkSurface *surface, sk_color_space_t dstColorSpace, SkYUVColorSpace yuvColorSpace, const SkIRect *srcRect, const SkISize *dstSize, SkSurface::RescaleGamma rescaleGamma, SkSurface::RescaleMode rescaleMode, SkSurface::ReadPixelsCallback callback, SkSurface::ReadPixelsContext context)
// void SkSurface_asyncRescaleAndReadPixelsYUVA420(void *surface, sk_color_space_t dstColorSpace, int yuvColorSpace, const void *srcRect, const void *dstSize, int rescaleGamma, int rescaleMode, SkSurface::ReadPixelsCallback callback, void * context); // (SkSurface *surface, sk_color_space_t dstColorSpace, SkYUVColorSpace yuvColorSpace, const SkIRect *srcRect, const SkISize *dstSize, SkSurface::RescaleGamma rescaleGamma, SkSurface::RescaleMode rescaleMode, SkSurface::ReadPixelsCallback callback, SkSurface::ReadPixelsContext context)

void SkSurface_writePixels(reskia_surface_t *surface, const reskia_pixmap_t *src, int dstX, int dstY); // (SkSurface *surface, const SkPixmap *src, int dstX, int dstY)
void SkSurface_writePixels_2(reskia_surface_t *surface, const reskia_bitmap_t *src, int dstX, int dstY); // (SkSurface *surface, const SkBitmap *src, int dstX, int dstY)
const reskia_surface_props_t *SkSurface_props(reskia_surface_t *surface); // borrowed: 解放不要の借用ポインタ (SkSurface *surface) -> const SkSurfaceProps *
bool SkSurface_wait(reskia_surface_t *surface, int numSemaphores, const reskia_backend_semaphore_t *waitSemaphores, bool deleteSemaphoresAfterWait); // (SkSurface *surface, int numSemaphores, const GrBackendSemaphore *waitSemaphores, bool deleteSemaphoresAfterWait) -> bool
bool SkSurface_characterize(reskia_surface_t *surface, reskia_surface_characterization_t *characterization); // (SkSurface *surface, GrSurfaceCharacterization *characterization) -> bool
bool SkSurface_unique(reskia_surface_t *surface); // (SkSurface *surface) -> bool
void SkSurface_ref(reskia_surface_t *surface); // retained: 参照カウントを増やす (SkSurface *surface)
void SkSurface_unref(reskia_surface_t *surface); // owned: 参照カウントを減らす (SkSurface *surface)

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_SURFACE_H
