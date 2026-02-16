//
// Created by dolphilia on 25/01/30.
//

#ifndef SK_MASK_H
#define SK_MASK_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../handles/static_sk_i_rect.h"
#include "../handles/static_sk_mask.h"

typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_mask_t reskia_mask_t;
typedef int32_t reskia_mask_format_t;

sk_mask_t SkMask_new(const uint8_t *img, const reskia_i_rect_t *bounds, uint32_t rowBytes, reskia_mask_format_t format); // (const uint8_t* img, const SkIRect * bounds, uint32_t rowBytes, SkMask::Format format) -> sk_mask_t
void SkMask_delete(reskia_mask_t *mask);

// member

const uint8_t *SkMask_fImage(reskia_mask_t *mask); // (SkMask *mask) -> const uint8_t *
sk_i_rect_t SkMask_fBounds(reskia_mask_t *mask); // (SkMask *mask) -> sk_i_rect_t
uint32_t SkMask_fRowBytes(reskia_mask_t *mask); // (SkMask *mask) -> uint32_t
reskia_mask_format_t SkMask_fFormat(reskia_mask_t *mask); // (SkMask *mask) -> SkMask::Format

// Method
bool SkMask_isEmpty(reskia_mask_t *mask); // (SkMask *mask) -> bool
size_t SkMask_computeImageSize(reskia_mask_t *mask); // (SkMask *mask) -> size_t
size_t SkMask_computeTotalImageSize(reskia_mask_t *mask); // (SkMask *mask) -> size_t
const uint8_t *SkMask_getAddr1(reskia_mask_t *mask, int x, int y); // (SkMask *mask, int x, int y) -> const uint8_t*
const uint8_t *SkMask_getAddr8(reskia_mask_t *mask, int x, int y); // (SkMask *mask, int x, int y) -> const uint8_t*
const uint16_t *SkMask_getAddrLCD16(reskia_mask_t *mask, int x, int y); // (SkMask *mask, int x, int y) -> const uint16_t*
const uint32_t *SkMask_getAddr32(reskia_mask_t *mask, int x, int y); // (SkMask *mask, int x, int y) -> const uint32_t*
const void *SkMask_getAddr(reskia_mask_t *mask, int x, int y); // (SkMask *mask, int x, int y) -> const void*

// static
bool SkMask_IsValidFormat(uint8_t format); // (uint8_t format) -> bool

#ifdef __cplusplus
}
#endif

#endif //SK_MASK_H
