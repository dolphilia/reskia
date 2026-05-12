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
 * img は borrowed。bounds 非 NULL、format valid。invalid 入力では 0
 */
sk_mask_t SkMask_new(const uint8_t *img, const reskia_i_rect_t *bounds, uint32_t rowBytes, reskia_mask_format_t format);
void SkMask_delete(reskia_mask_t *mask); // NULL 入力では no-op

// member

const uint8_t *SkMask_fImage(reskia_mask_t *mask); // borrowed: caller は解放しない。NULL 入力では NULL
sk_i_rect_t SkMask_fBounds(reskia_mask_t *mask); // NULL 入力では empty rect handle
uint32_t SkMask_fRowBytes(reskia_mask_t *mask); // NULL 入力では 0
reskia_mask_format_t SkMask_fFormat(reskia_mask_t *mask); // NULL 入力では -1

// Method
bool SkMask_isEmpty(reskia_mask_t *mask); // NULL 入力では true
size_t SkMask_computeImageSize(reskia_mask_t *mask); // NULL 入力では 0
size_t SkMask_computeTotalImageSize(reskia_mask_t *mask); // NULL 入力では 0
const uint8_t *SkMask_getAddr1(reskia_mask_t *mask, int x, int y); // borrowed。format/bounds/image 不一致や NULL 入力では NULL
const uint8_t *SkMask_getAddr8(reskia_mask_t *mask, int x, int y); // borrowed。format/bounds/image 不一致や NULL 入力では NULL
const uint16_t *SkMask_getAddrLCD16(reskia_mask_t *mask, int x, int y); // borrowed。format/bounds/image 不一致や NULL 入力では NULL
const uint32_t *SkMask_getAddr32(reskia_mask_t *mask, int x, int y); // borrowed。format/bounds/image 不一致や NULL 入力では NULL
const void *SkMask_getAddr(reskia_mask_t *mask, int x, int y); // borrowed。BW/format/bounds/image 不一致や NULL 入力では NULL

// static
bool SkMask_IsValidFormat(uint8_t format); // (uint8_t format) -> bool

#ifdef __cplusplus
}
#endif

#endif //SK_MASK_H
