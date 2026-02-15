//
// Created by dolphilia on 2024/01/05.
//

#ifndef RAIA_SKIA_SK_BITMAP_H
#define RAIA_SKIA_SK_BITMAP_H

#include <stddef.h>
#include <stdint.h>
#include "../static/static_sk_color_4f.h"
#include "../static/static_sk_color_space.h"
#include "../static/static_sk_i_point.h"
#include "../static/static_sk_i_rect.h"
#include "../static/static_sk_i_size.h"
#include "../static/static_sk_image.h"
#include "../static/static_sk_image_info.h"
#include "../static/static_sk_pixel_ref.h"
#include "../static/static_sk_shader.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_bitmap_t reskia_bitmap_t;
typedef struct reskia_bitmap_allocator_t reskia_bitmap_allocator_t;
typedef struct reskia_color_space_t reskia_color_space_t;
typedef struct reskia_i_point_t reskia_i_point_t;
typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_image_info_t reskia_image_info_t;
typedef struct reskia_mask_builder_t reskia_mask_builder_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_paint_t reskia_paint_t;
typedef struct reskia_pixel_ref_t reskia_pixel_ref_t;
typedef struct reskia_pixmap_t reskia_pixmap_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_sampling_options_t reskia_sampling_options_t;

reskia_bitmap_t *SkBitmap_new(void); // () -> SkBitmap *
reskia_bitmap_t *SkBitmap_new_2(const reskia_bitmap_t *src); // (const SkBitmap *src) -> SkBitmap *
void SkBitmap_delete(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap)
void SkBitmap_allocN32Pixels(reskia_bitmap_t *bitmap, int width, int height, bool isOpaque); // (SkBitmap *bitmap, int width, int height, bool isOpaque)
void SkBitmap_allocPixels(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap)
void SkBitmap_allocPixels_2(reskia_bitmap_t *bitmap, reskia_bitmap_allocator_t *allocator); // (SkBitmap *bitmap, SkBitmap::Allocator *allocator)
void SkBitmap_allocPixels_3(reskia_bitmap_t *bitmap, const reskia_image_info_t *info); // (SkBitmap *bitmap, const SkImageInfo *info)
void SkBitmap_allocPixels_4(reskia_bitmap_t *bitmap, const reskia_image_info_t *info, size_t rowBytes); // (SkBitmap *bitmap, const SkImageInfo *info, size_t rowBytes)
void SkBitmap_allocPixelsFlags(reskia_bitmap_t *bitmap, const reskia_image_info_t *info, uint32_t flags); // (SkBitmap *bitmap, const SkImageInfo *info, uint32_t flags)
int SkBitmap_alphaType(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> SkAlphaType
sk_image_t SkBitmap_asImage(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> sk_image_t
sk_i_rect_t SkBitmap_bounds(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> sk_i_rect_t
int SkBitmap_bytesPerPixel(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> int
reskia_color_space_t *SkBitmap_colorSpace(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> SkColorSpace *
int SkBitmap_colorType(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> SkColorType
size_t SkBitmap_computeByteSize(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> size_t
sk_i_size_t SkBitmap_dimensions(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> sk_i_size_t
bool SkBitmap_drawsNothing(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> bool
bool SkBitmap_empty(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> bool
void SkBitmap_erase(reskia_bitmap_t *bitmap, uint32_t c, const reskia_i_rect_t *area); // (SkBitmap *bitmap, SkColor c, const SkIRect *area)
void SkBitmap_erase_2(reskia_bitmap_t *bitmap, sk_color_4f_t c, const reskia_i_rect_t *area); // (SkBitmap *bitmap, sk_color_4f_t c, const SkIRect *area)
void SkBitmap_eraseArea(reskia_bitmap_t *bitmap, const reskia_i_rect_t *area, uint32_t c); // (SkBitmap *bitmap, const SkIRect *area, SkColor c)
void SkBitmap_eraseARGB(reskia_bitmap_t *bitmap, uint32_t a, uint32_t r, uint32_t g, uint32_t b); // (SkBitmap *bitmap, U8CPU a, U8CPU r, U8CPU g, U8CPU b)
void SkBitmap_eraseColor(reskia_bitmap_t *bitmap, uint32_t c); // (SkBitmap *bitmap, SkColor c)
void SkBitmap_eraseColor_2(reskia_bitmap_t *bitmap, sk_color_4f_t c); // (SkBitmap *bitmap, sk_color_4f_t c)
bool SkBitmap_extractAlpha(reskia_bitmap_t *bitmap, reskia_bitmap_t *dst); // (SkBitmap *bitmap, SkBitmap *dst) -> bool
bool SkBitmap_extractAlpha_2(reskia_bitmap_t *bitmap, reskia_bitmap_t *dst, const reskia_paint_t *paint, reskia_bitmap_allocator_t *allocator, reskia_i_point_t *offset); // (SkBitmap *bitmap, SkBitmap *dst, const SkPaint *paint, SkBitmap::Allocator *allocator, SkIPoint *offset) -> bool
bool SkBitmap_extractAlpha_3(reskia_bitmap_t *bitmap, reskia_bitmap_t *dst, const reskia_paint_t *paint, reskia_i_point_t *offset); // (SkBitmap *bitmap, SkBitmap *dst, const SkPaint *paint, SkIPoint *offset) -> bool
bool SkBitmap_extractSubset(reskia_bitmap_t *bitmap, reskia_bitmap_t *dst, const reskia_i_rect_t *subset); // (SkBitmap *bitmap, SkBitmap *dst, const SkIRect *subset) -> bool
void *SkBitmap_getAddr(reskia_bitmap_t *bitmap, int x, int y); // (SkBitmap *bitmap, int x, int y) -> void *
uint16_t *SkBitmap_getAddr16(reskia_bitmap_t *bitmap, int x, int y); // (SkBitmap *bitmap, int x, int y) -> uint16_t *
uint32_t *SkBitmap_getAddr32(reskia_bitmap_t *bitmap, int x, int y); // (SkBitmap *bitmap, int x, int y) -> uint32_t *
uint8_t *SkBitmap_getAddr8(reskia_bitmap_t *bitmap, int x, int y); // (SkBitmap *bitmap, int x, int y) -> uint8_t *
float SkBitmap_getAlphaf(reskia_bitmap_t *bitmap, int x, int y); // (SkBitmap *bitmap, int x, int y) -> float
void SkBitmap_getBounds(reskia_bitmap_t *bitmap, reskia_i_rect_t *bounds); // (SkBitmap *bitmap, SkIRect *bounds)
void SkBitmap_getBounds2(reskia_bitmap_t *bitmap, reskia_rect_t *bounds); // (SkBitmap *bitmap, SkRect *bounds)
uint32_t SkBitmap_getColor(reskia_bitmap_t *bitmap, int x, int y); // (SkBitmap *bitmap, int x, int y) -> SkColor
sk_color_4f_t SkBitmap_getColor4f(reskia_bitmap_t *bitmap, int x, int y); // (SkBitmap *bitmap, int x, int y) -> sk_color_4f_t
uint32_t SkBitmap_getGenerationID(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> uint32_t
void *SkBitmap_getPixels(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> void *
sk_i_rect_t SkBitmap_getSubset(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> sk_i_rect_t
int SkBitmap_height(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> int
sk_image_info_t SkBitmap_info(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> sk_image_info_t
bool SkBitmap_installMaskPixels(reskia_bitmap_t *bitmap, reskia_mask_builder_t *mask); // (SkBitmap *bitmap, SkMaskBuilder *mask) -> bool
bool SkBitmap_installPixels(reskia_bitmap_t *bitmap, const reskia_image_info_t *info, void *pixels, size_t rowBytes); // (SkBitmap *bitmap, const SkImageInfo *info, void *pixels, size_t rowBytes) -> bool
bool SkBitmap_installPixels_2(reskia_bitmap_t *bitmap, const reskia_image_info_t *info, void *pixels, size_t rowBytes, void(*releaseProc)(void *addr, void *context), void *context); // (SkBitmap *bitmap, const SkImageInfo *info, void *pixels, size_t rowBytes, void(*releaseProc)(void *addr, void *context), void *context) -> bool
bool SkBitmap_installPixels_3(reskia_bitmap_t *bitmap, const reskia_pixmap_t *pixmap); // (SkBitmap *bitmap, const SkPixmap *pixmap) -> bool
bool SkBitmap_isImmutable(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> bool
bool SkBitmap_isNull(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> bool
bool SkBitmap_isOpaque(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> bool
sk_shader_t SkBitmap_makeShader(reskia_bitmap_t *bitmap, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm); // (SkBitmap *bitmap, const SkSamplingOptions *sampling, const SkMatrix *lm) -> sk_shader_t
sk_shader_t SkBitmap_makeShader_2(reskia_bitmap_t *bitmap, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm); // (SkBitmap *bitmap, const SkSamplingOptions *sampling, const SkMatrix *lm) -> sk_shader_t
sk_shader_t SkBitmap_makeShader_3(reskia_bitmap_t *bitmap, int tmx, int tmy, const reskia_sampling_options_t *sampling, const reskia_matrix_t *localMatrix); // (SkBitmap *bitmap, SkTileMode tmx, SkTileMode tmy, const SkSamplingOptions *sampling, const SkMatrix *localMatrix) -> sk_shader_t
sk_shader_t SkBitmap_makeShader_4(reskia_bitmap_t *bitmap, int tmx, int tmy, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm); // (SkBitmap *bitmap, SkTileMode tmx, SkTileMode tmy, const SkSamplingOptions *sampling, const SkMatrix *lm) -> sk_shader_t
void SkBitmap_notifyPixelsChanged(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap)
bool SkBitmap_peekPixels(reskia_bitmap_t *bitmap, reskia_pixmap_t *pixmap); // (SkBitmap *bitmap, SkPixmap *pixmap) -> bool
reskia_pixel_ref_t *SkBitmap_pixelRef(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> SkPixelRef *
sk_i_point_t SkBitmap_pixelRefOrigin(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> sk_i_point_t
int SkBitmap_pixmap(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> int
bool SkBitmap_readPixels(reskia_bitmap_t *bitmap, const reskia_image_info_t *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY); // (SkBitmap *bitmap, const SkImageInfo *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY) -> bool
bool SkBitmap_readPixels_2(reskia_bitmap_t *bitmap, const reskia_pixmap_t *dst); // (SkBitmap *bitmap, const SkPixmap *dst) -> bool
bool SkBitmap_readPixels_3(reskia_bitmap_t *bitmap, const reskia_pixmap_t *dst, int srcX, int srcY); // (SkBitmap *bitmap, const SkPixmap *dst, int srcX, int srcY) -> bool
bool SkBitmap_readyToDraw(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> bool
sk_color_space_t SkBitmap_refColorSpace(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> sk_color_space_t
void SkBitmap_reset(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap)
size_t SkBitmap_rowBytes(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> size_t
int SkBitmap_rowBytesAsPixels(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> int
bool SkBitmap_setAlphaType(reskia_bitmap_t *bitmap, int alphaType); // (SkBitmap *bitmap, SkAlphaType alphaType) -> bool
void SkBitmap_setImmutable(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap)
bool SkBitmap_setInfo(reskia_bitmap_t *bitmap, const reskia_image_info_t *imageInfo, size_t rowBytes); // (SkBitmap *bitmap, const SkImageInfo *imageInfo, size_t rowBytes) -> bool
void SkBitmap_setPixelRef(reskia_bitmap_t *bitmap, sk_pixel_ref_t pixelRef, int dx, int dy); // (SkBitmap *bitmap, sk_pixel_ref_t pixelRef, int dx, int dy)
void SkBitmap_setPixels(reskia_bitmap_t *bitmap, void *pixels); // (SkBitmap *bitmap, void *pixels)
int SkBitmap_shiftPerPixel(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> int
void SkBitmap_swap(reskia_bitmap_t *bitmap, reskia_bitmap_t *other); // (SkBitmap *bitmap, SkBitmap *other)
bool SkBitmap_tryAllocN32Pixels(reskia_bitmap_t *bitmap, int width, int height, bool isOpaque); // (SkBitmap *bitmap, int width, int height, bool isOpaque) -> bool
bool SkBitmap_tryAllocPixels(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> bool
bool SkBitmap_tryAllocPixels_2(reskia_bitmap_t *bitmap, reskia_bitmap_allocator_t *allocator); // (SkBitmap *bitmap, SkBitmap::Allocator *allocator) -> bool
bool SkBitmap_tryAllocPixels_3(reskia_bitmap_t *bitmap, const reskia_image_info_t *info); // (SkBitmap *bitmap, const SkImageInfo *info) -> bool
bool SkBitmap_tryAllocPixels_4(reskia_bitmap_t *bitmap, const reskia_image_info_t *info, size_t rowBytes); // (SkBitmap *bitmap, const SkImageInfo *info, size_t rowBytes) -> bool
bool SkBitmap_tryAllocPixelsFlags(reskia_bitmap_t *bitmap, const reskia_image_info_t *info, uint32_t flags); // (SkBitmap *bitmap, const SkImageInfo *info, uint32_t flags) -> bool
int SkBitmap_width(reskia_bitmap_t *bitmap); // (SkBitmap *bitmap) -> int
bool SkBitmap_writePixels(reskia_bitmap_t *bitmap, const reskia_pixmap_t *src); // (SkBitmap *bitmap, const SkPixmap *src) -> bool
bool SkBitmap_writePixels_2(reskia_bitmap_t *bitmap, const reskia_pixmap_t *src, int dstX, int dstY); // (SkBitmap *bitmap, const SkPixmap *src, int dstX, int dstY) -> bool
// static
bool SkBitmap_ComputeIsOpaque(const reskia_bitmap_t *bm); // (const SkBitmap *bm) -> bool

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_BITMAP_H
