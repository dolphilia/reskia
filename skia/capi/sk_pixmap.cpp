//
// Created by dolphilia on 2024/01/10.
//

#include "sk_pixmap.h"

#include "include/core/SkPixmap.h"
#include "include/core/SkColorSpace.h"

#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_i_rect.h"
#include "../handles/static_sk_i_size.h"
#include "../handles/static_sk_color_4f.h"

#include "../handles/static_sk_i_rect-internal.h"
#include "../handles/static_sk_i_size-internal.h"
#include "../handles/static_sk_color_space-internal.h"
#include "../handles/static_sk_color_4f-internal.h"

extern "C" {

reskia_pixmap_t *SkPixmap_new() {
    return reinterpret_cast<reskia_pixmap_t *>(new SkPixmap());
}

reskia_pixmap_t *SkPixmap_new_2(const reskia_image_info_t *info, const void *addr, size_t rowBytes) {
    return reinterpret_cast<reskia_pixmap_t *>(
            new SkPixmap(*reinterpret_cast<const SkImageInfo *>(info), addr, rowBytes));
}

void SkPixmap_delete(reskia_pixmap_t *pixmap) {
    delete reinterpret_cast<SkPixmap *>(pixmap);
}

void SkPixmap_reset(reskia_pixmap_t *pixmap) {
    return reinterpret_cast<SkPixmap *>(pixmap)->reset();
}

void SkPixmap_reset_2(reskia_pixmap_t *pixmap, const reskia_image_info_t *info, const void *addr, size_t rowBytes) {
    return reinterpret_cast<SkPixmap *>(pixmap)->reset(* reinterpret_cast<const SkImageInfo *>(info), addr, rowBytes);
}

bool SkPixmap_reset_3(reskia_pixmap_t *pixmap, const reskia_mask_t *mask) {
    return reinterpret_cast<SkPixmap *>(pixmap)->reset(* reinterpret_cast<const SkMask *>(mask));
}

void SkPixmap_setColorSpace(reskia_pixmap_t *pixmap, sk_color_space_t color_space) {
    return reinterpret_cast<SkPixmap *>(pixmap)->setColorSpace(static_sk_color_space_get_entity(color_space));
}

bool SkPixmap_extractSubset(reskia_pixmap_t *pixmap, reskia_pixmap_t *subset, const reskia_i_rect_t *area) {
    return reinterpret_cast<SkPixmap *>(pixmap)->extractSubset(reinterpret_cast<SkPixmap *>(subset), * reinterpret_cast<const SkIRect *>(area));
}

const reskia_image_info_t *SkPixmap_info(reskia_pixmap_t *pixmap) {
    return reinterpret_cast<const reskia_image_info_t *>(
            &reinterpret_cast<SkPixmap *>(pixmap)->info());
}

size_t SkPixmap_rowBytes(reskia_pixmap_t *pixmap) {
    return reinterpret_cast<SkPixmap *>(pixmap)->rowBytes();
}

const void *SkPixmap_addr(reskia_pixmap_t *pixmap) {
    return reinterpret_cast<SkPixmap *>(pixmap)->addr();
}

int SkPixmap_width(reskia_pixmap_t *pixmap) {
    return reinterpret_cast<SkPixmap *>(pixmap)->width();
}

int SkPixmap_height(reskia_pixmap_t *pixmap) {
    return reinterpret_cast<SkPixmap *>(pixmap)->height();
}

sk_i_size_t SkPixmap_dimensions(reskia_pixmap_t *pixmap) {
    return static_sk_i_size_make(reinterpret_cast<SkPixmap *>(pixmap)->dimensions());
}

reskia_pixmap_color_type_t SkPixmap_colorType(reskia_pixmap_t *pixmap) {
    return static_cast<reskia_pixmap_color_type_t>(reinterpret_cast<SkPixmap *>(pixmap)->colorType());
}

reskia_pixmap_alpha_type_t SkPixmap_alphaType(reskia_pixmap_t *pixmap) {
    return static_cast<reskia_pixmap_alpha_type_t>(reinterpret_cast<SkPixmap *>(pixmap)->alphaType());
}

reskia_color_space_t *SkPixmap_colorSpace(reskia_pixmap_t *pixmap) {
    return reinterpret_cast<reskia_color_space_t *>(
            reinterpret_cast<SkPixmap *>(pixmap)->colorSpace());
}

sk_color_space_t SkPixmap_refColorSpace(reskia_pixmap_t *pixmap) {
    return static_sk_color_space_make(reinterpret_cast<SkPixmap *>(pixmap)->refColorSpace());
}

bool SkPixmap_isOpaque(reskia_pixmap_t *pixmap) {
    return reinterpret_cast<SkPixmap *>(pixmap)->isOpaque();
}

sk_i_rect_t SkPixmap_bounds(reskia_pixmap_t *pixmap) {
    return static_sk_i_rect_make(reinterpret_cast<SkPixmap *>(pixmap)->bounds());
}

int SkPixmap_rowBytesAsPixels(reskia_pixmap_t *pixmap) {
    return reinterpret_cast<SkPixmap *>(pixmap)->rowBytesAsPixels();
}

int SkPixmap_shiftPerPixel(reskia_pixmap_t *pixmap) {
    return reinterpret_cast<SkPixmap *>(pixmap)->shiftPerPixel();
}

size_t SkPixmap_computeByteSize(reskia_pixmap_t *pixmap) {
    return reinterpret_cast<SkPixmap *>(pixmap)->computeByteSize();
}

bool SkPixmap_computeIsOpaque(reskia_pixmap_t *pixmap) {
    return reinterpret_cast<SkPixmap *>(pixmap)->computeIsOpaque();
}

uint32_t SkPixmap_getColor(reskia_pixmap_t *pixmap, int x, int y) {
    return reinterpret_cast<SkPixmap *>(pixmap)->getColor(x, y);
}

sk_color_4f_t SkPixmap_getColor4f(reskia_pixmap_t *pixmap, int x, int y) {
    return static_sk_color_4f_make(reinterpret_cast<SkPixmap *>(pixmap)->getColor4f(x, y));
}

float SkPixmap_getAlphaf(reskia_pixmap_t *pixmap, int x, int y) {
    return reinterpret_cast<SkPixmap *>(pixmap)->getAlphaf(x, y);
}

const void *SkPixmap_addr_2(reskia_pixmap_t *pixmap, int x, int y) {
    return reinterpret_cast<SkPixmap *>(pixmap)->addr(x, y);
}

const uint8_t *SkPixmap_addr8(reskia_pixmap_t *pixmap) {
    return reinterpret_cast<SkPixmap *>(pixmap)->addr8();
}

const uint16_t *SkPixmap_addr16(reskia_pixmap_t *pixmap) {
    return reinterpret_cast<SkPixmap *>(pixmap)->addr16();
}

const uint32_t *SkPixmap_addr32(reskia_pixmap_t *pixmap) {
    return reinterpret_cast<SkPixmap *>(pixmap)->addr32();
}

const uint64_t *SkPixmap_addr64(reskia_pixmap_t *pixmap) {
    return reinterpret_cast<SkPixmap *>(pixmap)->addr64();
}

const uint16_t *SkPixmap_addrF16(reskia_pixmap_t *pixmap) {
    return reinterpret_cast<SkPixmap *>(pixmap)->addrF16();
}

const uint8_t *SkPixmap_addr8_2(reskia_pixmap_t *pixmap, int x, int y) {
    return reinterpret_cast<SkPixmap *>(pixmap)->addr8(x, y);
}

const uint16_t *SkPixmap_addr16_2(reskia_pixmap_t *pixmap, int x, int y) {
    return reinterpret_cast<SkPixmap *>(pixmap)->addr16(x, y);
}

const uint32_t *SkPixmap_addr32_2(reskia_pixmap_t *pixmap, int x, int y) {
    return reinterpret_cast<SkPixmap *>(pixmap)->addr32(x, y);
}

const uint64_t *SkPixmap_addr64_2(reskia_pixmap_t *pixmap, int x, int y) {
    return reinterpret_cast<SkPixmap *>(pixmap)->addr64(x, y);
}

const uint16_t *SkPixmap_addrF16_2(reskia_pixmap_t *pixmap, int x, int y) {
    return reinterpret_cast<SkPixmap *>(pixmap)->addrF16(x, y);
}

void *SkPixmap_writable_addr(reskia_pixmap_t *pixmap) {
    return reinterpret_cast<SkPixmap *>(pixmap)->writable_addr();
}

void *SkPixmap_writable_addr_2(reskia_pixmap_t *pixmap, int x, int y) {
    return reinterpret_cast<SkPixmap *>(pixmap)->writable_addr(x, y);
}

uint8_t *SkPixmap_writable_addr8(reskia_pixmap_t *pixmap, int x, int y) {
    return reinterpret_cast<SkPixmap *>(pixmap)->writable_addr8(x, y);
}

uint16_t *SkPixmap_writable_addr16(reskia_pixmap_t *pixmap, int x, int y) {
    return reinterpret_cast<SkPixmap *>(pixmap)->writable_addr16(x, y);
}

uint32_t *SkPixmap_writable_addr32(reskia_pixmap_t *pixmap, int x, int y) {
    return reinterpret_cast<SkPixmap *>(pixmap)->writable_addr32(x, y);
}

uint64_t *SkPixmap_writable_addr64(reskia_pixmap_t *pixmap, int x, int y) {
    return reinterpret_cast<SkPixmap *>(pixmap)->writable_addr64(x, y);
}

uint16_t *SkPixmap_writable_addrF16(reskia_pixmap_t *pixmap, int x, int y) {
    return reinterpret_cast<SkPixmap *>(pixmap)->writable_addrF16(x, y);
}

bool SkPixmap_readPixels(reskia_pixmap_t *pixmap, const reskia_image_info_t *dstInfo, void *dstPixels, size_t dstRowBytes) {
    return reinterpret_cast<SkPixmap *>(pixmap)->readPixels(* reinterpret_cast<const SkImageInfo *>(dstInfo), dstPixels, dstRowBytes);
}

bool SkPixmap_readPixels_2(reskia_pixmap_t *pixmap, const reskia_image_info_t *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY) {
    return reinterpret_cast<SkPixmap *>(pixmap)->readPixels(* reinterpret_cast<const SkImageInfo *>(dstInfo), dstPixels, dstRowBytes, srcX, srcY);
}

bool SkPixmap_readPixels_3(reskia_pixmap_t *pixmap, const reskia_pixmap_t *dst, int srcX, int srcY) {
    return reinterpret_cast<SkPixmap *>(pixmap)->readPixels(* reinterpret_cast<const SkPixmap *>(dst), srcX, srcY);
}

bool SkPixmap_readPixels_4(reskia_pixmap_t *pixmap, const reskia_pixmap_t *dst) {
    return reinterpret_cast<SkPixmap *>(pixmap)->readPixels(* reinterpret_cast<const SkPixmap *>(dst));
}

bool SkPixmap_scalePixels(reskia_pixmap_t *pixmap, const reskia_pixmap_t *dst, const reskia_sampling_options_t *options) {
    return reinterpret_cast<SkPixmap *>(pixmap)->scalePixels(* reinterpret_cast<const SkPixmap *>(dst), * reinterpret_cast<const SkSamplingOptions *>(options));
}

bool SkPixmap_erase(reskia_pixmap_t *pixmap, uint32_t color, const reskia_i_rect_t *subset) {
    return reinterpret_cast<SkPixmap *>(pixmap)->erase(color, * reinterpret_cast<const SkIRect *>(subset));
}

bool SkPixmap_erase_2(reskia_pixmap_t *pixmap, uint32_t color) {
    return reinterpret_cast<SkPixmap *>(pixmap)->erase(color);
}

bool SkPixmap_erase_3(reskia_pixmap_t *pixmap, const reskia_color_4f_t *color, const reskia_i_rect_t *subset) {
    return reinterpret_cast<SkPixmap *>(pixmap)->erase(* reinterpret_cast<const SkColor4f *>(color), reinterpret_cast<const SkIRect *>(subset));
}

}
