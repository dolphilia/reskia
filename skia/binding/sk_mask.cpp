//
// Created by dolphilia on 25/01/30.
//

#include "sk_mask.h"

#include "src/core/SkMask.h"

#include "../static/static_sk_mask.h"
#include "../static/static_sk_i_rect.h"

#include "../static/static_sk_mask-internal.h"
#include "../static/static_sk_i_rect-internal.h"

extern "C" {

sk_mask_t SkMask_new(const uint8_t *img, const reskia_i_rect_t *bounds, uint32_t rowBytes, reskia_mask_format_t format) {
    return static_sk_mask_make(SkMask(img, *reinterpret_cast<const SkIRect *>(bounds), rowBytes, static_cast<SkMask::Format>(format)));
}

void SkMask_delete(reskia_mask_t *mask) {
    delete reinterpret_cast<SkMask *>(mask);
}

// Member

const uint8_t *SkMask_fImage(reskia_mask_t *mask) {
    return reinterpret_cast<SkMask *>(mask)->fImage;
}

sk_i_rect_t SkMask_fBounds(reskia_mask_t *mask) {
    return static_sk_i_rect_make(reinterpret_cast<SkMask *>(mask)->fBounds);
}

uint32_t SkMask_fRowBytes(reskia_mask_t *mask) {
    return reinterpret_cast<SkMask *>(mask)->fRowBytes;
}

reskia_mask_format_t SkMask_fFormat(reskia_mask_t *mask) {
    return static_cast<reskia_mask_format_t>(reinterpret_cast<SkMask *>(mask)->fFormat);
}

// Method

bool SkMask_isEmpty(reskia_mask_t *mask) {
    return reinterpret_cast<SkMask *>(mask)->isEmpty();
}

size_t SkMask_computeImageSize(reskia_mask_t *mask) {
    return reinterpret_cast<SkMask *>(mask)->computeImageSize();
}

size_t SkMask_computeTotalImageSize(reskia_mask_t *mask) {
    return reinterpret_cast<SkMask *>(mask)->computeTotalImageSize();
}

const uint8_t *SkMask_getAddr1(reskia_mask_t *mask, int x, int y) {
    return reinterpret_cast<SkMask *>(mask)->getAddr1(x, y);
}

const uint8_t *SkMask_getAddr8(reskia_mask_t *mask, int x, int y) {
    return reinterpret_cast<SkMask *>(mask)->getAddr8(x, y);
}

const uint16_t *SkMask_getAddrLCD16(reskia_mask_t *mask, int x, int y) {
    return reinterpret_cast<SkMask *>(mask)->getAddrLCD16(x, y);
}

const uint32_t *SkMask_getAddr32(reskia_mask_t *mask, int x, int y) {
    return reinterpret_cast<SkMask *>(mask)->getAddr32(x, y);
}

const void *SkMask_getAddr(reskia_mask_t *mask, int x, int y) {
    return reinterpret_cast<SkMask *>(mask)->getAddr(x, y);
}

// static

bool SkMask_IsValidFormat(uint8_t format) {
    return SkMask::IsValidFormat(format);
}

}
