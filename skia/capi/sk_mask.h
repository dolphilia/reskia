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

/**
 * img is borrowed storage. bounds must be non-NULL, and format must be valid.
 * Returns 0 for invalid input.
 */
sk_mask_t SkMask_new(const uint8_t *img, const reskia_i_rect_t *bounds, uint32_t rowBytes, reskia_mask_format_t format);
void SkMask_delete(reskia_mask_t *mask); // No-op for NULL input.

// member

const uint8_t *SkMask_fImage(reskia_mask_t *mask); // Borrowed; the caller must not free it. Returns NULL for NULL input.
sk_i_rect_t SkMask_fBounds(reskia_mask_t *mask); // Returns an empty rect handle for NULL input.
uint32_t SkMask_fRowBytes(reskia_mask_t *mask); // Returns 0 for NULL input.
reskia_mask_format_t SkMask_fFormat(reskia_mask_t *mask); // Returns -1 for NULL input.

// Method
bool SkMask_isEmpty(reskia_mask_t *mask); // Returns true for NULL input.
size_t SkMask_computeImageSize(reskia_mask_t *mask); // Returns 0 for NULL input.
size_t SkMask_computeTotalImageSize(reskia_mask_t *mask); // Returns 0 for NULL input.
const uint8_t *SkMask_getAddr1(reskia_mask_t *mask, int x, int y); // Borrowed storage. Returns NULL when format/bounds/image are inconsistent or input is NULL.
const uint8_t *SkMask_getAddr8(reskia_mask_t *mask, int x, int y); // Borrowed storage. Returns NULL when format/bounds/image are inconsistent or input is NULL.
const uint16_t *SkMask_getAddrLCD16(reskia_mask_t *mask, int x, int y); // Borrowed storage. Returns NULL when format/bounds/image are inconsistent or input is NULL.
const uint32_t *SkMask_getAddr32(reskia_mask_t *mask, int x, int y); // Borrowed storage. Returns NULL when format/bounds/image are inconsistent or input is NULL.
const void *SkMask_getAddr(reskia_mask_t *mask, int x, int y); // Borrowed storage. Returns NULL when BW/format/bounds/image are inconsistent or input is NULL.

// static
bool SkMask_IsValidFormat(uint8_t format); // (uint8_t format) -> bool

#ifdef __cplusplus
}
#endif

#endif //SK_MASK_H
