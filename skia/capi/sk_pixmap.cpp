//
// Created by dolphilia on 2024/01/10.
//

#include "sk_pixmap.h"

#include "include/core/SkPixmap.h"
#include "include/core/SkColorSpace.h"
#include "include/core/SkImageInfo.h"
#include "include/core/SkSamplingOptions.h"
#include "src/core/SkMask.h"

#include <utility>

#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_i_rect.h"
#include "../handles/static_sk_i_size.h"
#include "../handles/static_sk_color_4f.h"

#include "../handles/static_sk_i_rect-internal.h"
#include "../handles/static_sk_i_size-internal.h"
#include "../handles/static_sk_color_space-internal.h"
#include "../handles/static_sk_color_4f-internal.h"

namespace {

SkPixmap *as_pixmap(reskia_pixmap_t *pixmap) {
    return reinterpret_cast<SkPixmap *>(pixmap);
}

const SkPixmap *as_pixmap(const reskia_pixmap_t *pixmap) {
    return reinterpret_cast<const SkPixmap *>(pixmap);
}

const SkImageInfo *as_image_info(const reskia_image_info_t *info) {
    return reinterpret_cast<const SkImageInfo *>(info);
}

const SkMask *as_mask(const reskia_mask_t *mask) {
    return reinterpret_cast<const SkMask *>(mask);
}

const SkIRect *as_irect(const reskia_i_rect_t *rect) {
    return reinterpret_cast<const SkIRect *>(rect);
}

const SkSamplingOptions *as_sampling_options(const reskia_sampling_options_t *options) {
    return reinterpret_cast<const SkSamplingOptions *>(options);
}

const SkColor4f *as_color4f(const reskia_color_4f_t *color) {
    return reinterpret_cast<const SkColor4f *>(color);
}

bool has_pixels(const SkPixmap *pixmap) {
    return pixmap != nullptr && pixmap->addr() != nullptr;
}

bool has_pixel_at(const SkPixmap *pixmap, int x, int y) {
    return has_pixels(pixmap) && x >= 0 && y >= 0 && x < pixmap->width() && y < pixmap->height();
}

bool has_bytes_per_pixel(const SkPixmap *pixmap, int bytes_per_pixel) {
    return has_pixels(pixmap) && pixmap->info().bytesPerPixel() == bytes_per_pixel;
}

bool has_f16_pixels(const SkPixmap *pixmap) {
    if (!has_bytes_per_pixel(pixmap, 8)) {
        return false;
    }
    const SkColorType color_type = pixmap->colorType();
    return color_type == kRGBA_F16_SkColorType || color_type == kRGBA_F16Norm_SkColorType;
}

sk_color_space_t make_color_space_handle(sk_sp<SkColorSpace> color_space) {
    if (!color_space) {
        return 0;
    }
    return static_sk_color_space_make(std::move(color_space));
}

}

extern "C" {

reskia_pixmap_t *SkPixmap_new() {
    return reinterpret_cast<reskia_pixmap_t *>(new SkPixmap());
}

reskia_pixmap_t *SkPixmap_newWithImageInfoAddressAndRowBytes(const reskia_image_info_t *info, const void *addr, size_t rowBytes) {
    const SkImageInfo *image_info = as_image_info(info);
    if (image_info == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_pixmap_t *>(new SkPixmap(*image_info, addr, rowBytes));
}

void SkPixmap_delete(reskia_pixmap_t *pixmap) {
    delete as_pixmap(pixmap);
}

void SkPixmap_reset(reskia_pixmap_t *pixmap) {
    SkPixmap *native = as_pixmap(pixmap);
    if (native == nullptr) {
        return;
    }
    native->reset();
}

void SkPixmap_resetWithImageInfoAddressAndRowBytes(reskia_pixmap_t *pixmap, const reskia_image_info_t *info, const void *addr, size_t rowBytes) {
    SkPixmap *native = as_pixmap(pixmap);
    const SkImageInfo *image_info = as_image_info(info);
    if (native == nullptr || image_info == nullptr) {
        return;
    }
    native->reset(*image_info, addr, rowBytes);
}

bool SkPixmap_resetFromMask(reskia_pixmap_t *pixmap, const reskia_mask_t *mask) {
    SkPixmap *native = as_pixmap(pixmap);
    const SkMask *native_mask = as_mask(mask);
    if (native == nullptr || native_mask == nullptr) {
        return false;
    }
    return native->reset(*native_mask);
}

void SkPixmap_setColorSpace(reskia_pixmap_t *pixmap, sk_color_space_t color_space) {
    SkPixmap *native = as_pixmap(pixmap);
    if (native == nullptr) {
        return;
    }
    native->setColorSpace(static_sk_color_space_get_entity(color_space));
}

bool SkPixmap_extractSubset(reskia_pixmap_t *pixmap, reskia_pixmap_t *subset, const reskia_i_rect_t *area) {
    const SkPixmap *native = as_pixmap(pixmap);
    SkPixmap *native_subset = as_pixmap(subset);
    const SkIRect *native_area = as_irect(area);
    if (native == nullptr || native_subset == nullptr || native_area == nullptr) {
        return false;
    }
    return native->extractSubset(native_subset, *native_area);
}

const reskia_image_info_t *SkPixmap_info(reskia_pixmap_t *pixmap) {
    SkPixmap *native = as_pixmap(pixmap);
    if (native == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_image_info_t *>(&native->info());
}

size_t SkPixmap_rowBytes(reskia_pixmap_t *pixmap) {
    const SkPixmap *native = as_pixmap(pixmap);
    return native != nullptr ? native->rowBytes() : 0;
}

const void *SkPixmap_addr(reskia_pixmap_t *pixmap) {
    const SkPixmap *native = as_pixmap(pixmap);
    return native != nullptr ? native->addr() : nullptr;
}

int SkPixmap_width(reskia_pixmap_t *pixmap) {
    const SkPixmap *native = as_pixmap(pixmap);
    return native != nullptr ? native->width() : 0;
}

int SkPixmap_height(reskia_pixmap_t *pixmap) {
    const SkPixmap *native = as_pixmap(pixmap);
    return native != nullptr ? native->height() : 0;
}

sk_i_size_t SkPixmap_dimensions(reskia_pixmap_t *pixmap) {
    const SkPixmap *native = as_pixmap(pixmap);
    if (native == nullptr) {
        return 0;
    }
    return static_sk_i_size_make(native->dimensions());
}

reskia_pixmap_color_type_t SkPixmap_colorType(reskia_pixmap_t *pixmap) {
    const SkPixmap *native = as_pixmap(pixmap);
    if (native == nullptr) {
        return -1;
    }
    return static_cast<reskia_pixmap_color_type_t>(native->colorType());
}

reskia_pixmap_alpha_type_t SkPixmap_alphaType(reskia_pixmap_t *pixmap) {
    const SkPixmap *native = as_pixmap(pixmap);
    if (native == nullptr) {
        return -1;
    }
    return static_cast<reskia_pixmap_alpha_type_t>(native->alphaType());
}

reskia_color_space_t *SkPixmap_colorSpace(reskia_pixmap_t *pixmap) {
    const SkPixmap *native = as_pixmap(pixmap);
    if (native == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_color_space_t *>(native->colorSpace());
}

sk_color_space_t SkPixmap_refColorSpace(reskia_pixmap_t *pixmap) {
    const SkPixmap *native = as_pixmap(pixmap);
    if (native == nullptr) {
        return 0;
    }
    return make_color_space_handle(native->refColorSpace());
}

bool SkPixmap_isOpaque(reskia_pixmap_t *pixmap) {
    const SkPixmap *native = as_pixmap(pixmap);
    return native != nullptr && native->isOpaque();
}

sk_i_rect_t SkPixmap_bounds(reskia_pixmap_t *pixmap) {
    const SkPixmap *native = as_pixmap(pixmap);
    if (native == nullptr) {
        return 0;
    }
    return static_sk_i_rect_make(native->bounds());
}

int SkPixmap_rowBytesAsPixels(reskia_pixmap_t *pixmap) {
    const SkPixmap *native = as_pixmap(pixmap);
    return native != nullptr ? native->rowBytesAsPixels() : 0;
}

int SkPixmap_shiftPerPixel(reskia_pixmap_t *pixmap) {
    const SkPixmap *native = as_pixmap(pixmap);
    return native != nullptr ? native->shiftPerPixel() : 0;
}

size_t SkPixmap_computeByteSize(reskia_pixmap_t *pixmap) {
    const SkPixmap *native = as_pixmap(pixmap);
    return native != nullptr ? native->computeByteSize() : 0;
}

bool SkPixmap_computeIsOpaque(reskia_pixmap_t *pixmap) {
    const SkPixmap *native = as_pixmap(pixmap);
    return native != nullptr && native->computeIsOpaque();
}

uint32_t SkPixmap_getColor(reskia_pixmap_t *pixmap, int x, int y) {
    const SkPixmap *native = as_pixmap(pixmap);
    if (!has_pixel_at(native, x, y)) {
        return 0;
    }
    return native->getColor(x, y);
}

sk_color_4f_t SkPixmap_getColor4f(reskia_pixmap_t *pixmap, int x, int y) {
    const SkPixmap *native = as_pixmap(pixmap);
    if (!has_pixel_at(native, x, y)) {
        return 0;
    }
    return static_sk_color_4f_make(native->getColor4f(x, y));
}

float SkPixmap_getAlphaf(reskia_pixmap_t *pixmap, int x, int y) {
    const SkPixmap *native = as_pixmap(pixmap);
    if (!has_pixel_at(native, x, y)) {
        return 0.0f;
    }
    return native->getAlphaf(x, y);
}

const void *SkPixmap_addrAt(reskia_pixmap_t *pixmap, int x, int y) {
    const SkPixmap *native = as_pixmap(pixmap);
    if (!has_pixel_at(native, x, y)) {
        return nullptr;
    }
    return native->addr(x, y);
}

const uint8_t *SkPixmap_addr8(reskia_pixmap_t *pixmap) {
    const SkPixmap *native = as_pixmap(pixmap);
    return has_bytes_per_pixel(native, 1) ? native->addr8() : nullptr;
}

const uint16_t *SkPixmap_addr16(reskia_pixmap_t *pixmap) {
    const SkPixmap *native = as_pixmap(pixmap);
    return has_bytes_per_pixel(native, 2) ? native->addr16() : nullptr;
}

const uint32_t *SkPixmap_addr32(reskia_pixmap_t *pixmap) {
    const SkPixmap *native = as_pixmap(pixmap);
    return has_bytes_per_pixel(native, 4) ? native->addr32() : nullptr;
}

const uint64_t *SkPixmap_addr64(reskia_pixmap_t *pixmap) {
    const SkPixmap *native = as_pixmap(pixmap);
    return has_bytes_per_pixel(native, 8) ? native->addr64() : nullptr;
}

const uint16_t *SkPixmap_addrF16(reskia_pixmap_t *pixmap) {
    const SkPixmap *native = as_pixmap(pixmap);
    return has_f16_pixels(native) ? native->addrF16() : nullptr;
}

const uint8_t *SkPixmap_addr8At(reskia_pixmap_t *pixmap, int x, int y) {
    const SkPixmap *native = as_pixmap(pixmap);
    return has_pixel_at(native, x, y) && has_bytes_per_pixel(native, 1) ? native->addr8(x, y) : nullptr;
}

const uint16_t *SkPixmap_addr16At(reskia_pixmap_t *pixmap, int x, int y) {
    const SkPixmap *native = as_pixmap(pixmap);
    return has_pixel_at(native, x, y) && has_bytes_per_pixel(native, 2) ? native->addr16(x, y) : nullptr;
}

const uint32_t *SkPixmap_addr32At(reskia_pixmap_t *pixmap, int x, int y) {
    const SkPixmap *native = as_pixmap(pixmap);
    return has_pixel_at(native, x, y) && has_bytes_per_pixel(native, 4) ? native->addr32(x, y) : nullptr;
}

const uint64_t *SkPixmap_addr64At(reskia_pixmap_t *pixmap, int x, int y) {
    const SkPixmap *native = as_pixmap(pixmap);
    return has_pixel_at(native, x, y) && has_bytes_per_pixel(native, 8) ? native->addr64(x, y) : nullptr;
}

const uint16_t *SkPixmap_addrF16At(reskia_pixmap_t *pixmap, int x, int y) {
    const SkPixmap *native = as_pixmap(pixmap);
    return has_pixel_at(native, x, y) && has_f16_pixels(native) ? native->addrF16(x, y) : nullptr;
}

void *SkPixmap_writable_addr(reskia_pixmap_t *pixmap) {
    SkPixmap *native = as_pixmap(pixmap);
    return has_pixels(native) ? native->writable_addr() : nullptr;
}

void *SkPixmap_writable_addrAt(reskia_pixmap_t *pixmap, int x, int y) {
    SkPixmap *native = as_pixmap(pixmap);
    if (!has_pixel_at(native, x, y)) {
        return nullptr;
    }
    return native->writable_addr(x, y);
}

uint8_t *SkPixmap_writable_addr8(reskia_pixmap_t *pixmap, int x, int y) {
    SkPixmap *native = as_pixmap(pixmap);
    return has_pixel_at(native, x, y) && has_bytes_per_pixel(native, 1) ? native->writable_addr8(x, y) : nullptr;
}

uint16_t *SkPixmap_writable_addr16(reskia_pixmap_t *pixmap, int x, int y) {
    SkPixmap *native = as_pixmap(pixmap);
    return has_pixel_at(native, x, y) && has_bytes_per_pixel(native, 2) ? native->writable_addr16(x, y) : nullptr;
}

uint32_t *SkPixmap_writable_addr32(reskia_pixmap_t *pixmap, int x, int y) {
    SkPixmap *native = as_pixmap(pixmap);
    return has_pixel_at(native, x, y) && has_bytes_per_pixel(native, 4) ? native->writable_addr32(x, y) : nullptr;
}

uint64_t *SkPixmap_writable_addr64(reskia_pixmap_t *pixmap, int x, int y) {
    SkPixmap *native = as_pixmap(pixmap);
    return has_pixel_at(native, x, y) && has_bytes_per_pixel(native, 8) ? native->writable_addr64(x, y) : nullptr;
}

uint16_t *SkPixmap_writable_addrF16(reskia_pixmap_t *pixmap, int x, int y) {
    SkPixmap *native = as_pixmap(pixmap);
    return has_pixel_at(native, x, y) && has_f16_pixels(native) ? native->writable_addrF16(x, y) : nullptr;
}

bool SkPixmap_readPixels(reskia_pixmap_t *pixmap, const reskia_image_info_t *dstInfo, void *dstPixels, size_t dstRowBytes) {
    const SkPixmap *native = as_pixmap(pixmap);
    const SkImageInfo *dst_info = as_image_info(dstInfo);
    if (native == nullptr || dst_info == nullptr || dstPixels == nullptr) {
        return false;
    }
    return native->readPixels(*dst_info, dstPixels, dstRowBytes);
}

bool SkPixmap_readPixelsWithSourceOffset(reskia_pixmap_t *pixmap, const reskia_image_info_t *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY) {
    const SkPixmap *native = as_pixmap(pixmap);
    const SkImageInfo *dst_info = as_image_info(dstInfo);
    if (native == nullptr || dst_info == nullptr || dstPixels == nullptr) {
        return false;
    }
    return native->readPixels(*dst_info, dstPixels, dstRowBytes, srcX, srcY);
}

bool SkPixmap_readPixelsToPixmapWithSourceOffset(reskia_pixmap_t *pixmap, const reskia_pixmap_t *dst, int srcX, int srcY) {
    const SkPixmap *native = as_pixmap(pixmap);
    const SkPixmap *dst_pixmap = as_pixmap(dst);
    if (native == nullptr || dst_pixmap == nullptr) {
        return false;
    }
    return native->readPixels(*dst_pixmap, srcX, srcY);
}

bool SkPixmap_readPixelsToPixmap(reskia_pixmap_t *pixmap, const reskia_pixmap_t *dst) {
    const SkPixmap *native = as_pixmap(pixmap);
    const SkPixmap *dst_pixmap = as_pixmap(dst);
    if (native == nullptr || dst_pixmap == nullptr) {
        return false;
    }
    return native->readPixels(*dst_pixmap);
}

bool SkPixmap_scalePixels(reskia_pixmap_t *pixmap, const reskia_pixmap_t *dst, const reskia_sampling_options_t *options) {
    const SkPixmap *native = as_pixmap(pixmap);
    const SkPixmap *dst_pixmap = as_pixmap(dst);
    const SkSamplingOptions *sampling_options = as_sampling_options(options);
    if (native == nullptr || dst_pixmap == nullptr || sampling_options == nullptr) {
        return false;
    }
    return native->scalePixels(*dst_pixmap, *sampling_options);
}

bool SkPixmap_erase(reskia_pixmap_t *pixmap, uint32_t color, const reskia_i_rect_t *subset) {
    SkPixmap *native = as_pixmap(pixmap);
    const SkIRect *native_subset = as_irect(subset);
    if (native == nullptr || native_subset == nullptr) {
        return false;
    }
    return native->erase(color, *native_subset);
}

bool SkPixmap_eraseColor(reskia_pixmap_t *pixmap, uint32_t color) {
    SkPixmap *native = as_pixmap(pixmap);
    if (native == nullptr) {
        return false;
    }
    return native->erase(color);
}

bool SkPixmap_eraseColor4fWithSubset(reskia_pixmap_t *pixmap, const reskia_color_4f_t *color, const reskia_i_rect_t *subset) {
    SkPixmap *native = as_pixmap(pixmap);
    const SkColor4f *native_color = as_color4f(color);
    if (native == nullptr || native_color == nullptr) {
        return false;
    }
    return native->erase(*native_color, as_irect(subset));
}

}
