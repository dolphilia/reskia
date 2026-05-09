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
reskia_pixmap_t *SkPixmap_newWithImageInfoAddressAndRowBytes(const reskia_image_info_t *info, const void *addr, size_t rowBytes); // info: non-null; addr may be null; returns null on invalid input
void SkPixmap_delete(reskia_pixmap_t *pixmap); // null pixmap is a no-op
void SkPixmap_reset(reskia_pixmap_t *pixmap); // null pixmap is a no-op
void SkPixmap_resetWithImageInfoAddressAndRowBytes(reskia_pixmap_t *pixmap, const reskia_image_info_t *info, const void *addr, size_t rowBytes); // pixmap/info: non-null; addr may be null; invalid input is a no-op
bool SkPixmap_resetFromMask(reskia_pixmap_t *pixmap, const reskia_mask_t *mask); // pixmap/mask: non-null; false on invalid input
void SkPixmap_setColorSpace(reskia_pixmap_t *pixmap, sk_color_space_t color_space); // null pixmap is a no-op; color_space handle 0 clears the color space
bool SkPixmap_extractSubset(reskia_pixmap_t *pixmap, reskia_pixmap_t *subset, const reskia_i_rect_t *area); // pixmap/subset/area: non-null; false on invalid input
const reskia_image_info_t *SkPixmap_info(reskia_pixmap_t *pixmap); // returns null on null pixmap
size_t SkPixmap_rowBytes(reskia_pixmap_t *pixmap); // returns 0 on null pixmap
const void *SkPixmap_addr(reskia_pixmap_t *pixmap); // returns null on null pixmap
int SkPixmap_width(reskia_pixmap_t *pixmap); // returns 0 on null pixmap
int SkPixmap_height(reskia_pixmap_t *pixmap); // returns 0 on null pixmap
sk_i_size_t SkPixmap_dimensions(reskia_pixmap_t *pixmap); // returns handle 0 on null pixmap
reskia_pixmap_color_type_t SkPixmap_colorType(reskia_pixmap_t *pixmap); // returns -1 on null pixmap
reskia_pixmap_alpha_type_t SkPixmap_alphaType(reskia_pixmap_t *pixmap); // returns -1 on null pixmap
reskia_color_space_t *SkPixmap_colorSpace(reskia_pixmap_t *pixmap); // borrowed; returns null on null pixmap or no color space
sk_color_space_t SkPixmap_refColorSpace(reskia_pixmap_t *pixmap); // retained handle; returns 0 on null pixmap or no color space
bool SkPixmap_isOpaque(reskia_pixmap_t *pixmap); // returns false on null pixmap
sk_i_rect_t SkPixmap_bounds(reskia_pixmap_t *pixmap); // returns handle 0 on null pixmap
int SkPixmap_rowBytesAsPixels(reskia_pixmap_t *pixmap); // returns 0 on null pixmap
int SkPixmap_shiftPerPixel(reskia_pixmap_t *pixmap); // returns 0 on null pixmap
size_t SkPixmap_computeByteSize(reskia_pixmap_t *pixmap); // returns 0 on null pixmap
bool SkPixmap_computeIsOpaque(reskia_pixmap_t *pixmap); // returns false on null pixmap
uint32_t SkPixmap_getColor(reskia_pixmap_t *pixmap, int x, int y); // returns 0 when pixmap has no pixels or x/y is out of bounds
sk_color_4f_t SkPixmap_getColor4f(reskia_pixmap_t *pixmap, int x, int y); // returns handle 0 when pixmap has no pixels or x/y is out of bounds
float SkPixmap_getAlphaf(reskia_pixmap_t *pixmap, int x, int y); // returns 0.0 when pixmap has no pixels or x/y is out of bounds
const void *SkPixmap_addrAt(reskia_pixmap_t *pixmap, int x, int y); // returns null when pixmap has no pixels or x/y is out of bounds
const uint8_t *SkPixmap_addr8(reskia_pixmap_t *pixmap); // returns null unless pixmap has pixels and bytesPerPixel() == 1
const uint16_t *SkPixmap_addr16(reskia_pixmap_t *pixmap); // returns null unless pixmap has pixels and bytesPerPixel() == 2
const uint32_t *SkPixmap_addr32(reskia_pixmap_t *pixmap); // returns null unless pixmap has pixels and bytesPerPixel() == 4
const uint64_t *SkPixmap_addr64(reskia_pixmap_t *pixmap); // returns null unless pixmap has pixels and bytesPerPixel() == 8
const uint16_t *SkPixmap_addrF16(reskia_pixmap_t *pixmap); // returns null unless pixmap has F16 pixels
const uint8_t *SkPixmap_addr8At(reskia_pixmap_t *pixmap, int x, int y); // returns null on invalid input, out-of-bounds x/y, or non-8-bit pixels
const uint16_t *SkPixmap_addr16At(reskia_pixmap_t *pixmap, int x, int y); // returns null on invalid input, out-of-bounds x/y, or non-16-bit pixels
const uint32_t *SkPixmap_addr32At(reskia_pixmap_t *pixmap, int x, int y); // returns null on invalid input, out-of-bounds x/y, or non-32-bit pixels
const uint64_t *SkPixmap_addr64At(reskia_pixmap_t *pixmap, int x, int y); // returns null on invalid input, out-of-bounds x/y, or non-64-bit pixels
const uint16_t *SkPixmap_addrF16At(reskia_pixmap_t *pixmap, int x, int y); // returns null on invalid input, out-of-bounds x/y, or non-F16 pixels
void *SkPixmap_writable_addr(reskia_pixmap_t *pixmap); // returns null on null pixmap or missing pixels
void *SkPixmap_writable_addrAt(reskia_pixmap_t *pixmap, int x, int y); // returns null when pixmap has no pixels or x/y is out of bounds
uint8_t *SkPixmap_writable_addr8(reskia_pixmap_t *pixmap, int x, int y); // returns null on invalid input, out-of-bounds x/y, or non-8-bit pixels
uint16_t *SkPixmap_writable_addr16(reskia_pixmap_t *pixmap, int x, int y); // returns null on invalid input, out-of-bounds x/y, or non-16-bit pixels
uint32_t *SkPixmap_writable_addr32(reskia_pixmap_t *pixmap, int x, int y); // returns null on invalid input, out-of-bounds x/y, or non-32-bit pixels
uint64_t *SkPixmap_writable_addr64(reskia_pixmap_t *pixmap, int x, int y); // returns null on invalid input, out-of-bounds x/y, or non-64-bit pixels
uint16_t *SkPixmap_writable_addrF16(reskia_pixmap_t *pixmap, int x, int y); // returns null on invalid input, out-of-bounds x/y, or non-F16 pixels
bool SkPixmap_readPixels(reskia_pixmap_t *pixmap, const reskia_image_info_t *dstInfo, void *dstPixels, size_t dstRowBytes); // pixmap/dstInfo/dstPixels: non-null; false on invalid input
bool SkPixmap_readPixelsWithSourceOffset(reskia_pixmap_t *pixmap, const reskia_image_info_t *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY); // pixmap/dstInfo/dstPixels: non-null; false on invalid input
bool SkPixmap_readPixelsToPixmapWithSourceOffset(reskia_pixmap_t *pixmap, const reskia_pixmap_t *dst, int srcX, int srcY); // pixmap/dst: non-null; false on invalid input
bool SkPixmap_readPixelsToPixmap(reskia_pixmap_t *pixmap, const reskia_pixmap_t *dst); // pixmap/dst: non-null; false on invalid input
bool SkPixmap_scalePixels(reskia_pixmap_t *pixmap, const reskia_pixmap_t *dst, const reskia_sampling_options_t *options); // pixmap/dst/options: non-null; false on invalid input
bool SkPixmap_erase(reskia_pixmap_t *pixmap, uint32_t color, const reskia_i_rect_t *subset); // pixmap/subset: non-null; false on invalid input
bool SkPixmap_eraseColor(reskia_pixmap_t *pixmap, uint32_t color); // returns false on null pixmap
bool SkPixmap_eraseColor4fWithSubset(reskia_pixmap_t *pixmap, const reskia_color_4f_t *color, const reskia_i_rect_t *subset); // pixmap/color: non-null; subset may be null; false on invalid input

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PIXMAP_H
