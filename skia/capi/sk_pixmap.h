//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_PIXMAP_H
#define RAIA_SKIA_SK_PIXMAP_H

#include <stddef.h>
#include <stdint.h>

#include "../handles/static_sk_color_4f.h"
#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_i_rect.h"
#include "../handles/static_sk_i_size.h"

typedef struct reskia_color_4f_t reskia_color_4f_t;
typedef struct reskia_color_space_t reskia_color_space_t;
typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_i_size_t reskia_i_size_t;
typedef struct reskia_image_info_t reskia_image_info_t;
typedef struct reskia_mask_t reskia_mask_t;
typedef struct reskia_pixmap_t reskia_pixmap_t;
typedef struct reskia_sampling_options_t reskia_sampling_options_t;
typedef int32_t reskia_pixmap_color_type_t;
typedef int32_t reskia_pixmap_alpha_type_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_pixmap_t *SkPixmap_new(); // () -> SkPixmap *
reskia_pixmap_t *SkPixmap_newWithImageInfoAddressAndRowBytes(const reskia_image_info_t *info, const void *addr, size_t rowBytes); // (const SkImageInfo *info, const void *addr, size_t rowBytes) -> SkPixmap *
void SkPixmap_delete(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap)
void SkPixmap_reset(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap)
void SkPixmap_resetWithImageInfoAddressAndRowBytes(reskia_pixmap_t *pixmap, const reskia_image_info_t *info, const void *addr, size_t rowBytes); // (SkPixmap *pixmap, const SkImageInfo *info, const void *addr, size_t rowBytes)
bool SkPixmap_resetFromMask(reskia_pixmap_t *pixmap, const reskia_mask_t *mask); // (SkPixmap *pixmap, const SkMask *mask) -> bool
void SkPixmap_setColorSpace(reskia_pixmap_t *pixmap, sk_color_space_t color_space); // (SkPixmap *pixmap, sk_color_space_t color_space)
bool SkPixmap_extractSubset(reskia_pixmap_t *pixmap, reskia_pixmap_t *subset, const reskia_i_rect_t *area); // (SkPixmap *pixmap, SkPixmap *subset, const SkIRect *area) -> bool
const reskia_image_info_t *SkPixmap_info(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap) -> const SkImageInfo *
size_t SkPixmap_rowBytes(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap) -> size_t
const void *SkPixmap_addr(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap) -> const void *
int SkPixmap_width(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap) -> int
int SkPixmap_height(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap) -> int
sk_i_size_t SkPixmap_dimensions(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap) -> sk_i_size_t
reskia_pixmap_color_type_t SkPixmap_colorType(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap) -> SkColorType
reskia_pixmap_alpha_type_t SkPixmap_alphaType(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap) -> SkAlphaType
reskia_color_space_t *SkPixmap_colorSpace(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap) -> SkColorSpace *
sk_color_space_t SkPixmap_refColorSpace(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap) -> sk_color_space_t
bool SkPixmap_isOpaque(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap) -> bool
sk_i_rect_t SkPixmap_bounds(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap) -> sk_i_rect_t
int SkPixmap_rowBytesAsPixels(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap) -> int
int SkPixmap_shiftPerPixel(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap) -> int
size_t SkPixmap_computeByteSize(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap) -> size_t
bool SkPixmap_computeIsOpaque(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap) -> bool
uint32_t SkPixmap_getColor(reskia_pixmap_t *pixmap, int x, int y); // (SkPixmap *pixmap, int x, int y) -> SkColor
sk_color_4f_t SkPixmap_getColor4f(reskia_pixmap_t *pixmap, int x, int y); // (SkPixmap *pixmap, int x, int y) -> sk_color_4f_t
float SkPixmap_getAlphaf(reskia_pixmap_t *pixmap, int x, int y); // (SkPixmap *pixmap, int x, int y) -> float
const void *SkPixmap_addrAt(reskia_pixmap_t *pixmap, int x, int y); // (SkPixmap *pixmap, int x, int y) -> const void *
const uint8_t *SkPixmap_addr8(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap) -> const uint8_t *
const uint16_t *SkPixmap_addr16(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap) -> const uint16_t *
const uint32_t *SkPixmap_addr32(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap) -> const uint32_t *
const uint64_t *SkPixmap_addr64(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap) -> const uint64_t *
const uint16_t *SkPixmap_addrF16(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap) -> const uint16_t *
const uint8_t *SkPixmap_addr8At(reskia_pixmap_t *pixmap, int x, int y); // (SkPixmap *pixmap, int x, int y) -> const uint8_t *
const uint16_t *SkPixmap_addr16At(reskia_pixmap_t *pixmap, int x, int y); // (SkPixmap *pixmap, int x, int y) -> const uint16_t *
const uint32_t *SkPixmap_addr32At(reskia_pixmap_t *pixmap, int x, int y); // (SkPixmap *pixmap, int x, int y) -> const uint32_t *
const uint64_t *SkPixmap_addr64At(reskia_pixmap_t *pixmap, int x, int y); // (SkPixmap *pixmap, int x, int y) -> const uint64_t *
const uint16_t *SkPixmap_addrF16At(reskia_pixmap_t *pixmap, int x, int y); // (SkPixmap *pixmap, int x, int y) -> const uint16_t *
void *SkPixmap_writable_addr(reskia_pixmap_t *pixmap); // (SkPixmap *pixmap) -> void *
void *SkPixmap_writable_addrAt(reskia_pixmap_t *pixmap, int x, int y); // (SkPixmap *pixmap, int x, int y) -> void *
uint8_t *SkPixmap_writable_addr8(reskia_pixmap_t *pixmap, int x, int y); // (SkPixmap *pixmap, int x, int y) -> uint8_t *
uint16_t *SkPixmap_writable_addr16(reskia_pixmap_t *pixmap, int x, int y); // (SkPixmap *pixmap, int x, int y) -> uint16_t *
uint32_t *SkPixmap_writable_addr32(reskia_pixmap_t *pixmap, int x, int y); // (SkPixmap *pixmap, int x, int y) -> uint32_t *
uint64_t *SkPixmap_writable_addr64(reskia_pixmap_t *pixmap, int x, int y); // (SkPixmap *pixmap, int x, int y) -> uint64_t *
uint16_t *SkPixmap_writable_addrF16(reskia_pixmap_t *pixmap, int x, int y); // (SkPixmap *pixmap, int x, int y) -> uint16_t *
bool SkPixmap_readPixels(reskia_pixmap_t *pixmap, const reskia_image_info_t *dstInfo, void *dstPixels, size_t dstRowBytes); // (SkPixmap *pixmap, const SkImageInfo *dstInfo, void *dstPixels, size_t dstRowBytes) -> bool
bool SkPixmap_readPixelsWithSourceOffset(reskia_pixmap_t *pixmap, const reskia_image_info_t *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY); // (SkPixmap *pixmap, const SkImageInfo *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY) -> bool
bool SkPixmap_readPixelsToPixmapWithSourceOffset(reskia_pixmap_t *pixmap, const reskia_pixmap_t *dst, int srcX, int srcY); // (SkPixmap *pixmap, const SkPixmap *dst, int srcX, int srcY) -> bool
bool SkPixmap_readPixelsToPixmap(reskia_pixmap_t *pixmap, const reskia_pixmap_t *dst); // (SkPixmap *pixmap, const SkPixmap *dst) -> bool
bool SkPixmap_scalePixels(reskia_pixmap_t *pixmap, const reskia_pixmap_t *dst, const reskia_sampling_options_t *options); // (SkPixmap *pixmap, const SkPixmap *dst, const SkSamplingOptions *options) -> bool
bool SkPixmap_erase(reskia_pixmap_t *pixmap, uint32_t color, const reskia_i_rect_t *subset); // (SkPixmap *pixmap, SkColor color, const SkIRect *subset) -> bool
bool SkPixmap_eraseColor(reskia_pixmap_t *pixmap, uint32_t color); // (SkPixmap *pixmap, SkColor color) -> bool
bool SkPixmap_eraseColor4fWithSubset(reskia_pixmap_t *pixmap, const reskia_color_4f_t *color, const reskia_i_rect_t *subset); // (SkPixmap *pixmap, const SkColor4f *color, const SkIRect *subset) -> bool

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PIXMAP_H
