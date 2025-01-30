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

sk_mask_t SkMask_new(const void * img, const void * bounds, uint32_t rowBytes, int format) {
    return static_sk_mask_make(SkMask(static_cast<const uint8_t *>(img), * static_cast<const SkIRect *>(bounds), rowBytes, static_cast<SkMask::Format>(format)));
}

void SkMask_delete(void *mask) {
    delete static_cast<SkMask *>(mask);
}

// Member

const void * SkMask_fImage(void *mask) {
    return static_cast<SkMask *>(mask)->fImage;
}

sk_i_rect_t SkMask_fBounds(void *mask) {
    return static_sk_i_rect_make(static_cast<SkMask *>(mask)->fBounds);
}

uint32_t SkMask_fRowBytes(void *mask) {
    return static_cast<SkMask *>(mask)->fRowBytes;
}

int SkMask_fFormat(void *mask) {
    return static_cast<SkMask *>(mask)->fFormat;
}

// Method

bool SkMask_isEmpty(void *mask) {
    return static_cast<SkMask *>(mask)->isEmpty();
}

size_t SkMask_computeImageSize(void *mask) {
    return static_cast<SkMask *>(mask)->computeImageSize();
}

size_t SkMask_computeTotalImageSize(void *mask) {
    return static_cast<SkMask *>(mask)->computeTotalImageSize();
}

const void * SkMask_getAddr1(void *mask, int x, int y) {
    return static_cast<SkMask *>(mask)->getAddr1(x, y);
}

const void * SkMask_getAddr8(void *mask, int x, int y) {
    return static_cast<SkMask *>(mask)->getAddr8(x, y);
}

const void * SkMask_getAddrLCD16(void *mask, int x, int y) {
    return static_cast<SkMask *>(mask)->getAddrLCD16(x, y);
}

const void * SkMask_getAddr32(void *mask, int x, int y) {
    return static_cast<SkMask *>(mask)->getAddr32(x, y);
}

const void* SkMask_getAddr(void *mask, int x, int y) {
    return static_cast<SkMask *>(mask)->getAddr(x, y);
}

// static

static bool SkMask_IsValidFormat(uint8_t format) {
    return SkMask::IsValidFormat(format);
}

}