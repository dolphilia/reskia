//
// Created by dolphilia on 25/01/30.
//

#include "sk_mask.h"

#include "src/core/SkMask.h"

#include "../handles/static_sk_mask.h"
#include "../handles/static_sk_i_rect.h"

#include "../handles/static_sk_mask-internal.h"
#include "../handles/static_sk_i_rect-internal.h"

namespace {

bool can_access_mask_addr(const SkMask *mask, int x, int y) {
    return mask != nullptr && mask->fImage != nullptr && mask->fBounds.contains(x, y);
}

}  // namespace

extern "C" {

sk_mask_t SkMask_new(const uint8_t *img, const reskia_i_rect_t *bounds, uint32_t rowBytes, reskia_mask_format_t format) {
    if (bounds == nullptr || !SkMask::IsValidFormat(static_cast<uint8_t>(format))) {
        return 0;
    }
    return static_sk_mask_make(SkMask(img, *reinterpret_cast<const SkIRect *>(bounds), rowBytes, static_cast<SkMask::Format>(format)));
}

void SkMask_delete(reskia_mask_t *mask) {
    if (mask == nullptr) {
        return;
    }
    delete reinterpret_cast<SkMask *>(mask);
}

// Member

const uint8_t *SkMask_fImage(reskia_mask_t *mask) {
    if (mask == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<SkMask *>(mask)->fImage;
}

sk_i_rect_t SkMask_fBounds(reskia_mask_t *mask) {
    if (mask == nullptr) {
        return static_sk_i_rect_make(SkIRect::MakeEmpty());
    }
    return static_sk_i_rect_make(reinterpret_cast<SkMask *>(mask)->fBounds);
}

uint32_t SkMask_fRowBytes(reskia_mask_t *mask) {
    if (mask == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkMask *>(mask)->fRowBytes;
}

reskia_mask_format_t SkMask_fFormat(reskia_mask_t *mask) {
    if (mask == nullptr) {
        return -1;
    }
    return static_cast<reskia_mask_format_t>(reinterpret_cast<SkMask *>(mask)->fFormat);
}

// Method

bool SkMask_isEmpty(reskia_mask_t *mask) {
    if (mask == nullptr) {
        return true;
    }
    return reinterpret_cast<SkMask *>(mask)->isEmpty();
}

size_t SkMask_computeImageSize(reskia_mask_t *mask) {
    if (mask == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkMask *>(mask)->computeImageSize();
}

size_t SkMask_computeTotalImageSize(reskia_mask_t *mask) {
    if (mask == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkMask *>(mask)->computeTotalImageSize();
}

const uint8_t *SkMask_getAddr1(reskia_mask_t *mask, int x, int y) {
    auto *sk_mask = reinterpret_cast<SkMask *>(mask);
    if (!can_access_mask_addr(sk_mask, x, y) || sk_mask->fFormat != SkMask::kBW_Format) {
        return nullptr;
    }
    return sk_mask->getAddr1(x, y);
}

const uint8_t *SkMask_getAddr8(reskia_mask_t *mask, int x, int y) {
    auto *sk_mask = reinterpret_cast<SkMask *>(mask);
    if (!can_access_mask_addr(sk_mask, x, y) || (sk_mask->fFormat != SkMask::kA8_Format && sk_mask->fFormat != SkMask::kSDF_Format)) {
        return nullptr;
    }
    return sk_mask->getAddr8(x, y);
}

const uint16_t *SkMask_getAddrLCD16(reskia_mask_t *mask, int x, int y) {
    auto *sk_mask = reinterpret_cast<SkMask *>(mask);
    if (!can_access_mask_addr(sk_mask, x, y) || sk_mask->fFormat != SkMask::kLCD16_Format) {
        return nullptr;
    }
    return sk_mask->getAddrLCD16(x, y);
}

const uint32_t *SkMask_getAddr32(reskia_mask_t *mask, int x, int y) {
    auto *sk_mask = reinterpret_cast<SkMask *>(mask);
    if (!can_access_mask_addr(sk_mask, x, y) || sk_mask->fFormat != SkMask::kARGB32_Format) {
        return nullptr;
    }
    return sk_mask->getAddr32(x, y);
}

const void *SkMask_getAddr(reskia_mask_t *mask, int x, int y) {
    auto *sk_mask = reinterpret_cast<SkMask *>(mask);
    if (!can_access_mask_addr(sk_mask, x, y) || sk_mask->fFormat == SkMask::kBW_Format || !SkMask::IsValidFormat(sk_mask->fFormat)) {
        return nullptr;
    }
    return sk_mask->getAddr(x, y);
}

// static

bool SkMask_IsValidFormat(uint8_t format) {
    return SkMask::IsValidFormat(format);
}

}
