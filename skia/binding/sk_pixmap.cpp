//
// Created by dolphilia on 2024/01/10.
//

#include "sk_pixmap.h"

#include "include/core/SkPixmap.h"
#include "include/core/SkColorSpace.h"

#include "../static/static_sk_color_space.h"
#include "../static/static_sk_i_rect.h"
#include "../static/static_sk_i_size.h"
#include "../static/static_sk_color_4f.h"

#include "../static/static_sk_i_rect-internal.h"
#include "../static/static_sk_i_size-internal.h"
#include "../static/static_sk_color_space-internal.h"
#include "../static/static_sk_color_4f-internal.h"

extern "C" {

void *SkPixmap_new() {
    return new SkPixmap();
}

void *SkPixmap_new_2(const void *info, const void *addr, size_t rowBytes) {
    return new SkPixmap(* static_cast<const SkImageInfo *>(info), addr, rowBytes);
}

void SkPixmap_delete(void *pixmap) {
    delete static_cast<SkPixmap *>(pixmap);
}

void SkPixmap_reset(void *pixmap) {
    return static_cast<SkPixmap *>(pixmap)->reset();
}

void SkPixmap_reset_2(void *pixmap, const void *info, const void *addr, size_t rowBytes) {
    return static_cast<SkPixmap *>(pixmap)->reset(* static_cast<const SkImageInfo *>(info), addr, rowBytes);
}

bool SkPixmap_reset_3(void *pixmap, const void *mask) {
    return static_cast<SkPixmap *>(pixmap)->reset(* static_cast<const SkMask *>(mask));
}

void SkPixmap_setColorSpace(void *pixmap, sk_color_space_t color_space) {
    return static_cast<SkPixmap *>(pixmap)->setColorSpace(static_sk_color_space_move(color_space));
}

bool SkPixmap_extractSubset(void *pixmap, void *subset, const void *area) {
    return static_cast<SkPixmap *>(pixmap)->extractSubset(static_cast<SkPixmap *>(subset), * static_cast<const SkIRect *>(area));
}

const void * SkPixmap_info(void *pixmap) {
    return &static_cast<SkPixmap *>(pixmap)->info();
}

size_t SkPixmap_rowBytes(void *pixmap) {
    return static_cast<SkPixmap *>(pixmap)->rowBytes();
}

const void * SkPixmap_addr(void *pixmap) {
    return static_cast<SkPixmap *>(pixmap)->addr();
}

int SkPixmap_width(void *pixmap) {
    return static_cast<SkPixmap *>(pixmap)->width();
}

int SkPixmap_height(void *pixmap) {
    return static_cast<SkPixmap *>(pixmap)->height();
}

sk_i_size_t SkPixmap_dimensions(void *pixmap) {
    return static_sk_i_size_make(static_cast<SkPixmap *>(pixmap)->dimensions());
}

int SkPixmap_colorType(void *pixmap) {
    return static_cast<SkPixmap *>(pixmap)->colorType();
}

int SkPixmap_alphaType(void *pixmap) {
    return static_cast<SkPixmap *>(pixmap)->alphaType();
}

void * SkPixmap_colorSpace(void *pixmap) {
    return static_cast<SkPixmap *>(pixmap)->colorSpace();
}

sk_color_space_t SkPixmap_refColorSpace(void *pixmap) {
    return static_sk_color_space_make(static_cast<SkPixmap *>(pixmap)->refColorSpace());
}

bool SkPixmap_isOpaque(void *pixmap) {
    return static_cast<SkPixmap *>(pixmap)->isOpaque();
}

sk_i_rect_t SkPixmap_bounds(void *pixmap) {
    return static_sk_i_rect_make(static_cast<SkPixmap *>(pixmap)->bounds());
}

int SkPixmap_rowBytesAsPixels(void *pixmap) {
    return static_cast<SkPixmap *>(pixmap)->rowBytesAsPixels();
}

int SkPixmap_shiftPerPixel(void *pixmap) {
    return static_cast<SkPixmap *>(pixmap)->shiftPerPixel();
}

size_t SkPixmap_computeByteSize(void *pixmap) {
    return static_cast<SkPixmap *>(pixmap)->computeByteSize();
}

bool SkPixmap_computeIsOpaque(void *pixmap) {
    return static_cast<SkPixmap *>(pixmap)->computeIsOpaque();
}

SkColor SkPixmap_getColor(void *pixmap, int x, int y) {
    return static_cast<SkPixmap *>(pixmap)->getColor(x, y);
}

sk_color_4f_t SkPixmap_getColor4f(void *pixmap, int x, int y) {
    return static_sk_color_4f_make(static_cast<SkPixmap *>(pixmap)->getColor4f(x, y));
}

float SkPixmap_getAlphaf(void *pixmap, int x, int y) {
    return static_cast<SkPixmap *>(pixmap)->getAlphaf(x, y);
}

const void * SkPixmap_addr_2(void *pixmap, int x, int y) {
    return static_cast<SkPixmap *>(pixmap)->addr(x, y);
}

const void * SkPixmap_addr8(void *pixmap) {
    return static_cast<SkPixmap *>(pixmap)->addr8();
}

const void * SkPixmap_addr16(void *pixmap) {
    return static_cast<SkPixmap *>(pixmap)->addr16();
}

const void * SkPixmap_addr32(void *pixmap) {
    return static_cast<SkPixmap *>(pixmap)->addr32();
}

const void * SkPixmap_addr64(void *pixmap) {
    return static_cast<SkPixmap *>(pixmap)->addr64();
}

const void * SkPixmap_addrF16(void *pixmap) {
    return static_cast<SkPixmap *>(pixmap)->addrF16();
}

const void * SkPixmap_addr8_2(void *pixmap, int x, int y) {
    return static_cast<SkPixmap *>(pixmap)->addr8(x, y);
}

const void * SkPixmap_addr16_2(void *pixmap, int x, int y) {
    return static_cast<SkPixmap *>(pixmap)->addr16(x, y);
}

const void * SkPixmap_addr32_2(void *pixmap, int x, int y) {
    return static_cast<SkPixmap *>(pixmap)->addr32(x, y);
}

const void * SkPixmap_addr64_2(void *pixmap, int x, int y) {
    return static_cast<SkPixmap *>(pixmap)->addr64(x, y);
}

const void * SkPixmap_addrF16_2(void *pixmap, int x, int y) {
    return static_cast<SkPixmap *>(pixmap)->addrF16(x, y);
}

void * SkPixmap_writable_addr(void *pixmap) {
    return static_cast<SkPixmap *>(pixmap)->writable_addr();
}

void * SkPixmap_writable_addr_2(void *pixmap, int x, int y) {
    return static_cast<SkPixmap *>(pixmap)->writable_addr(x, y);
}

void * SkPixmap_writable_addr8(void *pixmap, int x, int y) {
    return static_cast<SkPixmap *>(pixmap)->writable_addr8(x, y);
}

void * SkPixmap_writable_addr16(void *pixmap, int x, int y) {
    return static_cast<SkPixmap *>(pixmap)->writable_addr16(x, y);
}

void * SkPixmap_writable_addr32(void *pixmap, int x, int y) {
    return static_cast<SkPixmap *>(pixmap)->writable_addr32(x, y);
}

void * SkPixmap_writable_addr64(void *pixmap, int x, int y) {
    return static_cast<SkPixmap *>(pixmap)->writable_addr64(x, y);
}

void * SkPixmap_writable_addrF16(void *pixmap, int x, int y) {
    return static_cast<SkPixmap *>(pixmap)->writable_addrF16(x, y);
}

bool SkPixmap_readPixels(void *pixmap, const void *dstInfo, void *dstPixels, size_t dstRowBytes) {
    return static_cast<SkPixmap *>(pixmap)->readPixels(* static_cast<const SkImageInfo *>(dstInfo), dstPixels, dstRowBytes);
}

bool SkPixmap_readPixels_2(void *pixmap, const void *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY) {
    return static_cast<SkPixmap *>(pixmap)->readPixels(* static_cast<const SkImageInfo *>(dstInfo), dstPixels, dstRowBytes, srcX, srcY);
}

bool SkPixmap_readPixels_3(void *pixmap, const void *dst, int srcX, int srcY) {
    return static_cast<SkPixmap *>(pixmap)->readPixels(* static_cast<const SkPixmap *>(dst), srcX, srcY);
}

bool SkPixmap_readPixels_4(void *pixmap, const void *dst) {
    return static_cast<SkPixmap *>(pixmap)->readPixels(* static_cast<const SkPixmap *>(dst));
}

bool SkPixmap_scalePixels(void *pixmap, const void *dst, const void *options) {
    return static_cast<SkPixmap *>(pixmap)->scalePixels(* static_cast<const SkPixmap *>(dst), * static_cast<const SkSamplingOptions *>(options));
}

bool SkPixmap_erase(void *pixmap, unsigned int color, const void *subset) {
    return static_cast<SkPixmap *>(pixmap)->erase(color, * static_cast<const SkIRect *>(subset));
}

bool SkPixmap_erase_2(void *pixmap, unsigned int color) {
    return static_cast<SkPixmap *>(pixmap)->erase(color);
}

bool SkPixmap_erase_3(void *pixmap, const void *color, const void *subset) {
    return static_cast<SkPixmap *>(pixmap)->erase(* static_cast<const SkColor4f *>(color), static_cast<const SkIRect *>(subset));
}

}
