//
// Created by dolphilia on 2024/01/05.
//

#include "sk_bitmap.h"

#include "include/core/SkBitmap.h"

#include "../static/static_sk_color_4f.h"
#include "../static/static_sk_color_space.h"
#include "../static/static_sk_i_point.h"
#include "../static/static_sk_i_rect.h"
#include "../static/static_sk_i_size.h"
#include "../static/static_sk_image_info.h"
#include "../static/static_sk_image.h"
#include "../static/static_sk_pixel_ref.h"
#include "../static/static_sk_pixmap.h"
#include "../static/static_sk_shader.h"

#include "../static/static_sk_image-internal.h"
#include "../static/static_sk_image_info-internal.h"
#include "../static/static_sk_i_point-internal.h"
#include "../static/static_sk_i_rect-internal.h"
#include "../static/static_sk_i_size-internal.h"
#include "../static/static_sk_pixel_ref-internal.h"
#include "../static/static_sk_pixmap-internal.h"
#include "../static/static_sk_shader-internal.h"
#include "../static/static_sk_color_space-internal.h"
#include "../static/static_sk_color_4f-internal.h"

#ifdef __cplusplus
extern "C" {
#endif

reskia_bitmap_t *SkBitmap_new(void) {
    return reinterpret_cast<reskia_bitmap_t *>(new SkBitmap());
}

reskia_bitmap_t *SkBitmap_new_2(const reskia_bitmap_t *src) {
    return reinterpret_cast<reskia_bitmap_t *>(new SkBitmap(*reinterpret_cast<const SkBitmap *>(src)));
}

void SkBitmap_delete(reskia_bitmap_t *bitmap) {
    delete reinterpret_cast<SkBitmap *>(bitmap);
}

void SkBitmap_allocN32Pixels(reskia_bitmap_t *bitmap, int width, int height, bool isOpaque) {
    reinterpret_cast<SkBitmap *>(bitmap)->allocN32Pixels(width, height, isOpaque);
}

void SkBitmap_allocPixels(reskia_bitmap_t *bitmap) {
    reinterpret_cast<SkBitmap *>(bitmap)->allocPixels();
}

void SkBitmap_allocPixels_2(reskia_bitmap_t *bitmap, reskia_bitmap_allocator_t *allocator) {
    reinterpret_cast<SkBitmap *>(bitmap)->allocPixels(reinterpret_cast<SkBitmap::Allocator *>(allocator));
}

void SkBitmap_allocPixels_3(reskia_bitmap_t *bitmap, const reskia_image_info_t *info) {
    reinterpret_cast<SkBitmap *>(bitmap)->allocPixels(* reinterpret_cast<const SkImageInfo *>(info));
}

void SkBitmap_allocPixels_4(reskia_bitmap_t *bitmap, const reskia_image_info_t *info, size_t rowBytes) {
    reinterpret_cast<SkBitmap *>(bitmap)->allocPixels(* reinterpret_cast<const SkImageInfo *>(info), rowBytes);
}

void SkBitmap_allocPixelsFlags(reskia_bitmap_t *bitmap, const reskia_image_info_t *info, uint32_t flags) {
    reinterpret_cast<SkBitmap *>(bitmap)->allocPixelsFlags(* reinterpret_cast<const SkImageInfo *>(info), flags);
}

int SkBitmap_alphaType(reskia_bitmap_t *bitmap) { // inline
    return reinterpret_cast<SkBitmap *>(bitmap)->alphaType();
}

sk_image_t SkBitmap_asImage(reskia_bitmap_t *bitmap) {
    return static_sk_image_make(reinterpret_cast<SkBitmap *>(bitmap)->asImage());
}

sk_i_rect_t SkBitmap_bounds(reskia_bitmap_t *bitmap) { // inline
    return static_sk_i_rect_make(reinterpret_cast<SkBitmap *>(bitmap)->bounds());
}

int SkBitmap_bytesPerPixel(reskia_bitmap_t *bitmap) { // inline
    return reinterpret_cast<SkBitmap *>(bitmap)->bytesPerPixel();
}

reskia_color_space_t *SkBitmap_colorSpace(reskia_bitmap_t *bitmap) {
    return reinterpret_cast<reskia_color_space_t *>(reinterpret_cast<SkBitmap *>(bitmap)->colorSpace());
}

int SkBitmap_colorType(reskia_bitmap_t *bitmap) { // inline
    return reinterpret_cast<SkBitmap *>(bitmap)->colorType();
}

size_t SkBitmap_computeByteSize(reskia_bitmap_t *bitmap) { // inline
    return reinterpret_cast<SkBitmap *>(bitmap)->computeByteSize();
}

sk_i_size_t SkBitmap_dimensions(reskia_bitmap_t *bitmap) { // inline
    return static_sk_i_size_make(reinterpret_cast<SkBitmap *>(bitmap)->dimensions());
}

bool SkBitmap_drawsNothing(reskia_bitmap_t *bitmap) { // inline
    return reinterpret_cast<SkBitmap *>(bitmap)->drawsNothing();
}

bool SkBitmap_empty(reskia_bitmap_t *bitmap) { // inline
    return reinterpret_cast<SkBitmap *>(bitmap)->empty();
}

void SkBitmap_erase(reskia_bitmap_t *bitmap, uint32_t c, const reskia_i_rect_t *area) {
    reinterpret_cast<SkBitmap *>(bitmap)->erase(c, * reinterpret_cast<const SkIRect *>(area));
}

void SkBitmap_erase_2(reskia_bitmap_t *bitmap, sk_color_4f_t c, const reskia_i_rect_t *area) {
    reinterpret_cast<SkBitmap *>(bitmap)->erase(static_sk_color_4f_get_entity(c), * reinterpret_cast<const SkIRect *>(area));
}

void SkBitmap_eraseArea(reskia_bitmap_t *bitmap, const reskia_i_rect_t *area, uint32_t c) { // inline
    reinterpret_cast<SkBitmap *>(bitmap)->eraseArea(* reinterpret_cast<const SkIRect *>(area), c);
}

void SkBitmap_eraseARGB(reskia_bitmap_t *bitmap, uint32_t a, uint32_t r, uint32_t g, uint32_t b) { // inline
    reinterpret_cast<SkBitmap *>(bitmap)->eraseARGB(a, r, g, b);
}

void SkBitmap_eraseColor(reskia_bitmap_t *bitmap, uint32_t c) {
    reinterpret_cast<SkBitmap *>(bitmap)->eraseColor(c);
}

void SkBitmap_eraseColor_2(reskia_bitmap_t *bitmap, sk_color_4f_t c) {
    reinterpret_cast<SkBitmap *>(bitmap)->eraseColor(static_sk_color_4f_get_entity(c));
}

bool SkBitmap_extractAlpha(reskia_bitmap_t *bitmap, reskia_bitmap_t *dst) { // inline
    return reinterpret_cast<SkBitmap *>(bitmap)->extractAlpha(reinterpret_cast<SkBitmap *>(dst));
}

bool SkBitmap_extractAlpha_2(reskia_bitmap_t *bitmap, reskia_bitmap_t *dst, const reskia_paint_t *paint, reskia_bitmap_allocator_t *allocator, reskia_i_point_t *offset) {
    return reinterpret_cast<SkBitmap *>(bitmap)->extractAlpha(reinterpret_cast<SkBitmap *>(dst), reinterpret_cast<const SkPaint *>(paint), reinterpret_cast<SkBitmap::Allocator *>(allocator), reinterpret_cast<SkIPoint *>(offset));
}

bool SkBitmap_extractAlpha_3(reskia_bitmap_t *bitmap, reskia_bitmap_t *dst, const reskia_paint_t *paint, reskia_i_point_t *offset) { // inline
    return reinterpret_cast<SkBitmap *>(bitmap)->extractAlpha(reinterpret_cast<SkBitmap *>(dst), reinterpret_cast<const SkPaint *>(paint), reinterpret_cast<SkIPoint *>(offset));
}

bool SkBitmap_extractSubset(reskia_bitmap_t *bitmap, reskia_bitmap_t *dst, const reskia_i_rect_t *subset) {
    return reinterpret_cast<SkBitmap *>(bitmap)->extractSubset(reinterpret_cast<SkBitmap *>(dst), * reinterpret_cast<const SkIRect *>(subset));
}

void *SkBitmap_getAddr(reskia_bitmap_t *bitmap, int x, int y) {
    return reinterpret_cast<SkBitmap *>(bitmap)->getAddr(x, y);
}

uint16_t *SkBitmap_getAddr16(reskia_bitmap_t *bitmap, int x, int y) { // inline
    return reinterpret_cast<SkBitmap *>(bitmap)->getAddr16(x, y);
}

uint32_t *SkBitmap_getAddr32(reskia_bitmap_t *bitmap, int x, int y) { // inline
    return reinterpret_cast<SkBitmap *>(bitmap)->getAddr32(x, y);
}

uint8_t *SkBitmap_getAddr8(reskia_bitmap_t *bitmap, int x, int y) { // inline
    return reinterpret_cast<SkBitmap *>(bitmap)->getAddr8(x, y);
}

float SkBitmap_getAlphaf(reskia_bitmap_t *bitmap, int x, int y) { // inline
    return reinterpret_cast<SkBitmap *>(bitmap)->getAlphaf(x, y);
}

void SkBitmap_getBounds(reskia_bitmap_t *bitmap, reskia_i_rect_t *bounds) {
    reinterpret_cast<SkBitmap *>(bitmap)->getBounds(reinterpret_cast<SkIRect *>(bounds));
}

void SkBitmap_getBounds2(reskia_bitmap_t *bitmap, reskia_rect_t *bounds) {
    reinterpret_cast<SkBitmap *>(bitmap)->getBounds(reinterpret_cast<SkRect *>(bounds));
}

uint32_t SkBitmap_getColor(reskia_bitmap_t *bitmap, int x, int y) { // inline
    return reinterpret_cast<SkBitmap *>(bitmap)->getColor(x, y);
}

sk_color_4f_t SkBitmap_getColor4f(reskia_bitmap_t *bitmap, int x, int y) { // inline
    return static_sk_color_4f_make(reinterpret_cast<SkBitmap *>(bitmap)->getColor4f(x, y));
}

uint32_t SkBitmap_getGenerationID(reskia_bitmap_t *bitmap) {
    return reinterpret_cast<SkBitmap *>(bitmap)->getGenerationID();
}

void *SkBitmap_getPixels(reskia_bitmap_t *bitmap) { // inline
    return reinterpret_cast<SkBitmap *>(bitmap)->getPixels();
}

sk_i_rect_t SkBitmap_getSubset(reskia_bitmap_t *bitmap) { // inline
    return static_sk_i_rect_make(reinterpret_cast<SkBitmap *>(bitmap)->getSubset());
}

int SkBitmap_height(reskia_bitmap_t *bitmap) { // inline
    return reinterpret_cast<SkBitmap *>(bitmap)->height();
}

sk_image_info_t SkBitmap_info(reskia_bitmap_t *bitmap) { // inline
    return static_sk_image_info_make(reinterpret_cast<SkBitmap *>(bitmap)->info());
}

bool SkBitmap_installMaskPixels(reskia_bitmap_t *bitmap, reskia_mask_builder_t *mask) { // Deprecated
    return reinterpret_cast<SkBitmap *>(bitmap)->installMaskPixels(* reinterpret_cast<SkMaskBuilder *>(mask));
}

bool SkBitmap_installPixels(reskia_bitmap_t *bitmap, const reskia_image_info_t *info, void *pixels, size_t rowBytes) { // inline
    return reinterpret_cast<SkBitmap *>(bitmap)->installPixels(* reinterpret_cast<const SkImageInfo *>(info), pixels, rowBytes);
}

bool SkBitmap_installPixels_2(reskia_bitmap_t *bitmap, const reskia_image_info_t *info, void *pixels, size_t rowBytes, void(*releaseProc)(void *addr, void *context), void *context) {
    return reinterpret_cast<SkBitmap *>(bitmap)->installPixels(* reinterpret_cast<const SkImageInfo *>(info), pixels, rowBytes, releaseProc, context);
}

bool SkBitmap_installPixels_3(reskia_bitmap_t *bitmap, const reskia_pixmap_t *pixmap) {
    return reinterpret_cast<SkBitmap *>(bitmap)->installPixels(* reinterpret_cast<const SkPixmap *>(pixmap));
}

bool SkBitmap_isImmutable(reskia_bitmap_t *bitmap) {
    return reinterpret_cast<SkBitmap *>(bitmap)->isImmutable();
}

bool SkBitmap_isNull(reskia_bitmap_t *bitmap) {
    return reinterpret_cast<SkBitmap *>(bitmap)->isNull();
}

bool SkBitmap_isOpaque(reskia_bitmap_t *bitmap) {
    return reinterpret_cast<SkBitmap *>(bitmap)->isOpaque();
}

sk_shader_t SkBitmap_makeShader(reskia_bitmap_t *bitmap, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm) {
    return static_sk_shader_make(reinterpret_cast<SkBitmap *>(bitmap)->makeShader(* reinterpret_cast<const SkSamplingOptions *>(sampling), * reinterpret_cast<const SkMatrix *>(lm)));
}

sk_shader_t SkBitmap_makeShader_2(reskia_bitmap_t *bitmap, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm) {
    return static_sk_shader_make(reinterpret_cast<SkBitmap *>(bitmap)->makeShader(* reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkMatrix *>(lm)));
}

sk_shader_t SkBitmap_makeShader_3(reskia_bitmap_t *bitmap, int tmx, int tmy, const reskia_sampling_options_t *sampling, const reskia_matrix_t *localMatrix) {
    return static_sk_shader_make(reinterpret_cast<SkBitmap *>(bitmap)->makeShader(static_cast<SkTileMode>(tmx), static_cast<SkTileMode>(tmy), * reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkBitmap_makeShader_4(reskia_bitmap_t *bitmap, int tmx, int tmy, const reskia_sampling_options_t *sampling, const reskia_matrix_t *lm) {
    return static_sk_shader_make(reinterpret_cast<SkBitmap *>(bitmap)->makeShader(static_cast<SkTileMode>(tmx), static_cast<SkTileMode>(tmy), * reinterpret_cast<const SkSamplingOptions *>(sampling), * reinterpret_cast<const SkMatrix *>(lm)));
}

void SkBitmap_notifyPixelsChanged(reskia_bitmap_t *bitmap) {
    reinterpret_cast<SkBitmap *>(bitmap)->notifyPixelsChanged();
}

bool SkBitmap_peekPixels(reskia_bitmap_t *bitmap, reskia_pixmap_t *pixmap) {
    return reinterpret_cast<SkBitmap *>(bitmap)->peekPixels(reinterpret_cast<SkPixmap *>(pixmap));
}

reskia_pixel_ref_t *SkBitmap_pixelRef(reskia_bitmap_t *bitmap) { // inline
    return reinterpret_cast<reskia_pixel_ref_t *>(reinterpret_cast<SkBitmap *>(bitmap)->pixelRef());
}

sk_i_point_t SkBitmap_pixelRefOrigin(reskia_bitmap_t *bitmap) {
    return static_sk_i_point_make(reinterpret_cast<SkBitmap *>(bitmap)->pixelRefOrigin());
}

int SkBitmap_pixmap(reskia_bitmap_t *bitmap) { // inline
    return static_sk_pixmap_make(reinterpret_cast<SkBitmap *>(bitmap)->pixmap());
}

bool SkBitmap_readPixels(reskia_bitmap_t *bitmap, const reskia_image_info_t *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY) {
    return reinterpret_cast<SkBitmap *>(bitmap)->readPixels(* reinterpret_cast<const SkImageInfo *>(dstInfo), dstPixels, dstRowBytes, srcX, srcY);
}

bool SkBitmap_readPixels_2(reskia_bitmap_t *bitmap, const reskia_pixmap_t *dst) { // inline
    return reinterpret_cast<SkBitmap *>(bitmap)->readPixels(* reinterpret_cast<const SkPixmap *>(dst));
}

bool SkBitmap_readPixels_3(reskia_bitmap_t *bitmap, const reskia_pixmap_t *dst, int srcX, int srcY) {
    return reinterpret_cast<SkBitmap *>(bitmap)->readPixels(* reinterpret_cast<const SkPixmap *>(dst), srcX, srcY);
}

bool SkBitmap_readyToDraw(reskia_bitmap_t *bitmap) { // inline
    return reinterpret_cast<SkBitmap *>(bitmap)->readyToDraw();
}

sk_color_space_t SkBitmap_refColorSpace(reskia_bitmap_t *bitmap) {
    return static_sk_color_space_make(reinterpret_cast<SkBitmap *>(bitmap)->refColorSpace());
}

void SkBitmap_reset(reskia_bitmap_t *bitmap) {
    reinterpret_cast<SkBitmap *>(bitmap)->reset();
}

size_t SkBitmap_rowBytes(reskia_bitmap_t *bitmap) { // inline
    return reinterpret_cast<SkBitmap *>(bitmap)->rowBytes();
}

int SkBitmap_rowBytesAsPixels(reskia_bitmap_t *bitmap) { // inline
    return reinterpret_cast<SkBitmap *>(bitmap)->rowBytesAsPixels();
}

bool SkBitmap_setAlphaType(reskia_bitmap_t *bitmap, int alphaType) {
    return reinterpret_cast<SkBitmap *>(bitmap)->setAlphaType(static_cast<SkAlphaType>(alphaType));
}

void SkBitmap_setImmutable(reskia_bitmap_t *bitmap) {
    reinterpret_cast<SkBitmap *>(bitmap)->setImmutable();
}

bool SkBitmap_setInfo(reskia_bitmap_t *bitmap, const reskia_image_info_t *imageInfo, size_t rowBytes) {
    return reinterpret_cast<SkBitmap *>(bitmap)->setInfo(* reinterpret_cast<const SkImageInfo *>(imageInfo), rowBytes);
}

void SkBitmap_setPixelRef(reskia_bitmap_t *bitmap, sk_pixel_ref_t pixelRef, int dx, int dy) {
    reinterpret_cast<SkBitmap *>(bitmap)->setPixelRef(static_sk_pixel_ref_get_entity(pixelRef), dx, dy);
}

void SkBitmap_setPixels(reskia_bitmap_t *bitmap, void *pixels) {
    reinterpret_cast<SkBitmap *>(bitmap)->setPixels(pixels);
}

int SkBitmap_shiftPerPixel(reskia_bitmap_t *bitmap) {
    return reinterpret_cast<SkBitmap *>(bitmap)->shiftPerPixel();
}

void SkBitmap_swap(reskia_bitmap_t *bitmap, reskia_bitmap_t *other) {
    reinterpret_cast<SkBitmap *>(bitmap)->swap(*reinterpret_cast<SkBitmap *>(other));
}

bool SkBitmap_tryAllocN32Pixels(reskia_bitmap_t *bitmap, int width, int height, bool isOpaque) {
    return reinterpret_cast<SkBitmap *>(bitmap)->tryAllocN32Pixels(width, height, isOpaque);
}

bool SkBitmap_tryAllocPixels(reskia_bitmap_t *bitmap) { // inline
    return reinterpret_cast<SkBitmap *>(bitmap)->tryAllocPixels();
}

bool SkBitmap_tryAllocPixels_2(reskia_bitmap_t *bitmap, reskia_bitmap_allocator_t *allocator) {
    return reinterpret_cast<SkBitmap *>(bitmap)->tryAllocPixels(reinterpret_cast<SkBitmap::Allocator *>(allocator));
}

bool SkBitmap_tryAllocPixels_3(reskia_bitmap_t *bitmap, const reskia_image_info_t *info) { // inline
    return reinterpret_cast<SkBitmap *>(bitmap)->tryAllocPixels(* reinterpret_cast<const SkImageInfo *>(info));
}

bool SkBitmap_tryAllocPixels_4(reskia_bitmap_t *bitmap, const reskia_image_info_t *info, size_t rowBytes) {
    return reinterpret_cast<SkBitmap *>(bitmap)->tryAllocPixels(* reinterpret_cast<const SkImageInfo *>(info), rowBytes);
}

bool SkBitmap_tryAllocPixelsFlags(reskia_bitmap_t *bitmap, const reskia_image_info_t *info, uint32_t flags) {
    return reinterpret_cast<SkBitmap *>(bitmap)->tryAllocPixelsFlags(* reinterpret_cast<const SkImageInfo *>(info), flags);
}

int SkBitmap_width(reskia_bitmap_t *bitmap) {
    return reinterpret_cast<SkBitmap *>(bitmap)->width();
}

bool SkBitmap_writePixels(reskia_bitmap_t *bitmap, const reskia_pixmap_t *src) { // inline
    return reinterpret_cast<SkBitmap *>(bitmap)->writePixels(* reinterpret_cast<const SkPixmap *>(src));
}

bool SkBitmap_writePixels_2(reskia_bitmap_t *bitmap, const reskia_pixmap_t *src, int dstX, int dstY) {
    return reinterpret_cast<SkBitmap *>(bitmap)->writePixels(* reinterpret_cast<const SkPixmap *>(src), dstX, dstY);
}

// static

bool SkBitmap_ComputeIsOpaque(const reskia_bitmap_t *bm) { // inline static
    return SkBitmap::ComputeIsOpaque(*reinterpret_cast<const SkBitmap *>(bm));
}

#ifdef __cplusplus
}
#endif
