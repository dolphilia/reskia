//
// Created by dolphilia on 2024/01/05.
//

#include "sk_bitmap.h"

#include "include/core/SkBitmap.h"

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

void * SkBitmap_new(void) {
    return new SkBitmap();
}

void * SkBitmap_new_2(const void * src) {
    return new SkBitmap(*static_cast<const SkBitmap *>(src));
}

void SkBitmap_delete(void * bitmap) {
    delete static_cast<SkBitmap *>(bitmap);
}

void SkBitmap_allocN32Pixels(void * bitmap, int width, int height, bool isOpaque) {
    static_cast<SkBitmap *>(bitmap)->allocN32Pixels(width, height, isOpaque);
}

void SkBitmap_allocPixels(void * bitmap) {
    static_cast<SkBitmap *>(bitmap)->allocPixels();
}

void SkBitmap_allocPixels_2(void * bitmap, void * allocator) {
    static_cast<SkBitmap *>(bitmap)->allocPixels(static_cast<SkBitmap::Allocator *>(allocator));
}

void SkBitmap_allocPixels_3(void * bitmap, const void * info) {
    static_cast<SkBitmap *>(bitmap)->allocPixels(* static_cast<const SkImageInfo *>(info));
}

void SkBitmap_allocPixels_4(void *bitmap, const void *info, size_t rowBytes) {
    static_cast<SkBitmap *>(bitmap)->allocPixels(* static_cast<const SkImageInfo *>(info), rowBytes);
}

void SkBitmap_allocPixelsFlags(void *bitmap, const void *info, uint32_t flags) {
    static_cast<SkBitmap *>(bitmap)->allocPixelsFlags(* static_cast<const SkImageInfo *>(info), flags);
}

int SkBitmap_alphaType(void *bitmap) { // inline
    return static_cast<SkBitmap *>(bitmap)->alphaType();
}

sk_image_t SkBitmap_asImage(void *bitmap) {
    return static_sk_image_make(static_cast<SkBitmap *>(bitmap)->asImage());
}

sk_i_rect_t SkBitmap_bounds(void *bitmap) { // inline
    return static_sk_i_rect_make(static_cast<SkBitmap *>(bitmap)->bounds());
}

int SkBitmap_bytesPerPixel(void *bitmap) { // inline
    return static_cast<SkBitmap *>(bitmap)->bytesPerPixel();
}

void * SkBitmap_colorSpace(void *bitmap) {
    return static_cast<SkBitmap *>(bitmap)->colorSpace();
}

int SkBitmap_colorType(void *bitmap) { // inline
    return static_cast<SkBitmap *>(bitmap)->colorType();
}

size_t SkBitmap_computeByteSize(void *bitmap) { // inline
    return static_cast<SkBitmap *>(bitmap)->computeByteSize();
}

sk_i_size_t SkBitmap_dimensions(void *bitmap) { // inline
    return static_sk_i_size_make(static_cast<SkBitmap *>(bitmap)->dimensions());
}

bool SkBitmap_drawsNothing(void *bitmap) { // inline
    return static_cast<SkBitmap *>(bitmap)->drawsNothing();
}

bool SkBitmap_empty(void *bitmap) { // inline
    return static_cast<SkBitmap *>(bitmap)->empty();
}

void SkBitmap_erase(void *bitmap, unsigned int c, const void *area) {
    static_cast<SkBitmap *>(bitmap)->erase(c, * static_cast<const SkIRect *>(area));
}

void SkBitmap_erase_2(void *bitmap, sk_color_4f_t c, const void *area) {
    static_cast<SkBitmap *>(bitmap)->erase(static_sk_color_4f_get(c), * static_cast<const SkIRect *>(area));
}

void SkBitmap_eraseArea(void *bitmap, const void *area, unsigned int c) { // inline
    static_cast<SkBitmap *>(bitmap)->eraseArea(* static_cast<const SkIRect *>(area), c);
}

void SkBitmap_eraseARGB(void *bitmap, unsigned int a, unsigned int r, unsigned int g, unsigned int b) { // inline
    static_cast<SkBitmap *>(bitmap)->eraseARGB(a, r, g, b);
}

void SkBitmap_eraseColor(void *bitmap, unsigned int c) {
    static_cast<SkBitmap *>(bitmap)->eraseColor(c);
}

void SkBitmap_eraseColor_2(void *bitmap, sk_color_4f_t c) {
    static_cast<SkBitmap *>(bitmap)->eraseColor(static_sk_color_4f_get(c));
}

bool SkBitmap_extractAlpha(void *bitmap, void *dst) { // inline
    return static_cast<SkBitmap *>(bitmap)->extractAlpha(static_cast<SkBitmap *>(dst));
}

bool SkBitmap_extractAlpha_2(void *bitmap, void *dst, const void *paint, void *allocator, void *offset) {
    return static_cast<SkBitmap *>(bitmap)->extractAlpha(static_cast<SkBitmap *>(dst), static_cast<const SkPaint *>(paint), static_cast<SkBitmap::Allocator *>(allocator), static_cast<SkIPoint *>(offset));
}

bool SkBitmap_extractAlpha_3(void *bitmap, void *dst, const void *paint, void *offset) { // inline
    return static_cast<SkBitmap *>(bitmap)->extractAlpha(static_cast<SkBitmap *>(dst), static_cast<const SkPaint *>(paint), static_cast<SkIPoint *>(offset));
}

bool SkBitmap_extractSubset(void *bitmap, void *dst, const void *subset) {
    return static_cast<SkBitmap *>(bitmap)->extractSubset(static_cast<SkBitmap *>(dst), * static_cast<const SkIRect *>(subset));
}

void * SkBitmap_getAddr(void *bitmap, int x, int y) {
    return static_cast<SkBitmap *>(bitmap)->getAddr(x, y);
}

void * SkBitmap_getAddr16(void *bitmap, int x, int y) { // inline
    return static_cast<SkBitmap *>(bitmap)->getAddr16(x, y);
}

void * SkBitmap_getAddr32(void *bitmap, int x, int y) { // inline
    return static_cast<SkBitmap *>(bitmap)->getAddr32(x, y);
}

void * SkBitmap_getAddr8(void *bitmap, int x, int y) { // inline
    return static_cast<SkBitmap *>(bitmap)->getAddr8(x, y);
}

float SkBitmap_getAlphaf(void *bitmap, int x, int y) { // inline
    return static_cast<SkBitmap *>(bitmap)->getAlphaf(x, y);
}

void SkBitmap_getBounds(void *bitmap, void *bounds) {
    static_cast<SkBitmap *>(bitmap)->getBounds(static_cast<SkIRect *>(bounds));
}

void SkBitmap_getBounds2(void *bitmap, void *bounds) {
    static_cast<SkBitmap *>(bitmap)->getBounds(static_cast<SkRect *>(bounds));
}

unsigned int SkBitmap_getColor(void *bitmap, int x, int y) { // inline
    return static_cast<SkBitmap *>(bitmap)->getColor(x, y);
}

sk_color_4f_t SkBitmap_getColor4f(void *bitmap, int x, int y) { // inline
    return static_sk_color_4f_make(static_cast<SkBitmap *>(bitmap)->getColor4f(x, y));
}

uint32_t SkBitmap_getGenerationID(void *bitmap) {
    return static_cast<SkBitmap *>(bitmap)->getGenerationID();
}

void * SkBitmap_getPixels(void *bitmap) { // inline
    return static_cast<SkBitmap *>(bitmap)->getPixels();
}

sk_i_rect_t SkBitmap_getSubset(void *bitmap) { // inline
    return static_sk_i_rect_make(static_cast<SkBitmap *>(bitmap)->getSubset());
}

int SkBitmap_height(void *bitmap) { // inline
    return static_cast<SkBitmap *>(bitmap)->height();
}

int SkBitmap_info(void *bitmap) { // inline
    return static_sk_image_info_make(static_cast<SkBitmap *>(bitmap)->info());
}

bool SkBitmap_installMaskPixels(void *bitmap, void *mask) { // Deprecated
    return static_cast<SkBitmap *>(bitmap)->installMaskPixels(* static_cast<SkMaskBuilder *>(mask));
}

bool SkBitmap_installPixels(void *bitmap, const void *info, void *pixels, size_t rowBytes) { // inline
    return static_cast<SkBitmap *>(bitmap)->installPixels(* static_cast<const SkImageInfo *>(info), pixels, rowBytes);
}

bool SkBitmap_installPixels_2(void *bitmap, const void *info, void *pixels, size_t rowBytes, void(*releaseProc)(void *addr, void *context), void *context) {
    return static_cast<SkBitmap *>(bitmap)->installPixels(* static_cast<const SkImageInfo *>(info), pixels, rowBytes, releaseProc, context);
}

bool SkBitmap_installPixels_3(void *bitmap, const void *pixmap) {
    return static_cast<SkBitmap *>(bitmap)->installPixels(* static_cast<const SkPixmap *>(pixmap));
}

bool SkBitmap_isImmutable(void *bitmap) {
    return static_cast<SkBitmap *>(bitmap)->isImmutable();
}

bool SkBitmap_isNull(void *bitmap) {
    return static_cast<SkBitmap *>(bitmap)->isNull();
}

bool SkBitmap_isOpaque(void *bitmap) {
    return static_cast<SkBitmap *>(bitmap)->isOpaque();
}

sk_shader_t SkBitmap_makeShader(void *bitmap, const void *sampling, const void *lm) {
    return static_sk_shader_make(static_cast<SkBitmap *>(bitmap)->makeShader(* static_cast<const SkSamplingOptions *>(sampling), * static_cast<const SkMatrix *>(lm)));
}

sk_shader_t SkBitmap_makeShader_2(void *bitmap, const void *sampling, const void *lm) {
    return static_sk_shader_make(static_cast<SkBitmap *>(bitmap)->makeShader(* static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkMatrix *>(lm)));
}

sk_shader_t SkBitmap_makeShader_3(void *bitmap, int tmx, int tmy, const void *sampling, const void *localMatrix) {
    return static_sk_shader_make(static_cast<SkBitmap *>(bitmap)->makeShader(static_cast<SkTileMode>(tmx), static_cast<SkTileMode>(tmy), * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkBitmap_makeShader_4(void *bitmap, int tmx, int tmy, const void *sampling, const void *lm) {
    return static_sk_shader_make(static_cast<SkBitmap *>(bitmap)->makeShader(static_cast<SkTileMode>(tmx), static_cast<SkTileMode>(tmy), * static_cast<const SkSamplingOptions *>(sampling), * static_cast<const SkMatrix *>(lm)));
}

void SkBitmap_notifyPixelsChanged(void *bitmap) {
    static_cast<SkBitmap *>(bitmap)->notifyPixelsChanged();
}

bool SkBitmap_peekPixels(void *bitmap, void *pixmap) {
    return static_cast<SkBitmap *>(bitmap)->peekPixels(static_cast<SkPixmap *>(pixmap));
}

void * SkBitmap_pixelRef(void *bitmap) { // inline
    return static_cast<SkBitmap *>(bitmap)->pixelRef();
}

sk_i_point_t SkBitmap_pixelRefOrigin(void *bitmap) {
    return static_sk_i_point_make(static_cast<SkBitmap *>(bitmap)->pixelRefOrigin());
}

int SkBitmap_pixmap(void *bitmap) { // inline
    return static_sk_pixmap_make(static_cast<SkBitmap *>(bitmap)->pixmap());
}

bool SkBitmap_readPixels(void *bitmap, const void *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY) {
    return static_cast<SkBitmap *>(bitmap)->readPixels(* static_cast<const SkImageInfo *>(dstInfo), dstPixels, dstRowBytes, srcX, srcY);
}

bool SkBitmap_readPixels_2(void *bitmap, const void *dst) { // inline
    return static_cast<SkBitmap *>(bitmap)->readPixels(* static_cast<const SkPixmap *>(dst));
}

bool SkBitmap_readPixels_3(void *bitmap, const void *dst, int srcX, int srcY) {
    return static_cast<SkBitmap *>(bitmap)->readPixels(* static_cast<const SkPixmap *>(dst), srcX, srcY);
}

bool SkBitmap_readyToDraw(void *bitmap) { // inline
    return static_cast<SkBitmap *>(bitmap)->readyToDraw();
}

sk_color_space_t SkBitmap_refColorSpace(void *bitmap) {
    return static_sk_color_space_make(static_cast<SkBitmap *>(bitmap)->refColorSpace());
}

void SkBitmap_reset(void *bitmap) {
    static_cast<SkBitmap *>(bitmap)->reset();
}

size_t SkBitmap_rowBytes(void *bitmap) { // inline
    return static_cast<SkBitmap *>(bitmap)->rowBytes();
}

int SkBitmap_rowBytesAsPixels(void *bitmap) { // inline
    return static_cast<SkBitmap *>(bitmap)->rowBytesAsPixels();
}

bool SkBitmap_setAlphaType(void *bitmap, int alphaType) {
    return static_cast<SkBitmap *>(bitmap)->setAlphaType(static_cast<SkAlphaType>(alphaType));
}

void SkBitmap_setImmutable(void *bitmap) {
    static_cast<SkBitmap *>(bitmap)->setImmutable();
}

bool SkBitmap_setInfo(void *bitmap, const void *imageInfo, size_t rowBytes) {
    return static_cast<SkBitmap *>(bitmap)->setInfo(* static_cast<const SkImageInfo *>(imageInfo), rowBytes);
}

void SkBitmap_setPixelRef(void *bitmap, sk_pixel_ref_t pixelRef, int dx, int dy) {
    static_cast<SkBitmap *>(bitmap)->setPixelRef(static_sk_pixel_ref_move(pixelRef), dx, dy);
}

void SkBitmap_setPixels(void *bitmap, void *pixels) {
    static_cast<SkBitmap *>(bitmap)->setPixels(pixels);
}

int SkBitmap_shiftPerPixel(void *bitmap) {
    return static_cast<SkBitmap *>(bitmap)->shiftPerPixel();
}

void SkBitmap_swap(void *bitmap, void *other) {
    static_cast<SkBitmap *>(bitmap)->swap(*static_cast<SkBitmap *>(other));
}

bool SkBitmap_tryAllocN32Pixels(void *bitmap, int width, int height, bool isOpaque) {
    return static_cast<SkBitmap *>(bitmap)->tryAllocN32Pixels(width, height, isOpaque);
}

bool SkBitmap_tryAllocPixels(void *bitmap) { // inline
    return static_cast<SkBitmap *>(bitmap)->tryAllocPixels();
}

bool SkBitmap_tryAllocPixels_2(void *bitmap, void *allocator) {
    return static_cast<SkBitmap *>(bitmap)->tryAllocPixels(static_cast<SkBitmap::Allocator *>(allocator));
}

bool SkBitmap_tryAllocPixels_3(void *bitmap, const void *info) { // inline
    return static_cast<SkBitmap *>(bitmap)->tryAllocPixels(* static_cast<const SkImageInfo *>(info));
}

bool SkBitmap_tryAllocPixels_4(void *bitmap, const void *info, size_t rowBytes) {
    return static_cast<SkBitmap *>(bitmap)->tryAllocPixels(* static_cast<const SkImageInfo *>(info), rowBytes);
}

bool SkBitmap_tryAllocPixelsFlags(void *bitmap, const void *info, uint32_t flags) {
    return static_cast<SkBitmap *>(bitmap)->tryAllocPixelsFlags(* static_cast<const SkImageInfo *>(info), flags);
}

int SkBitmap_width(void *bitmap) {
    return static_cast<SkBitmap *>(bitmap)->width();
}

bool SkBitmap_writePixels(void *bitmap, const void *src) { // inline
    return static_cast<SkBitmap *>(bitmap)->writePixels(* static_cast<const SkPixmap *>(src));
}

bool SkBitmap_writePixels_2(void *bitmap, const void *src, int dstX, int dstY) {
    return static_cast<SkBitmap *>(bitmap)->writePixels(* static_cast<const SkPixmap *>(src), dstX, dstY);
}

// static

bool SkBitmap_ComputeIsOpaque(const void *bm) { // inline static
    return SkBitmap::ComputeIsOpaque(*static_cast<const SkBitmap *>(bm));
}

#ifdef __cplusplus
}
#endif