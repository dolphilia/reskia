//
// Created by dolphilia on 25/01/30.
//

#ifndef SK_MASK_BUILDER_H
#define SK_MASK_BUILDER_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../handles/static_sk_mask_builder.h"

typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_mask_builder_t reskia_mask_builder_t;
typedef struct reskia_mask_t reskia_mask_t;
typedef int32_t reskia_mask_builder_format_t;
typedef int32_t reskia_mask_builder_alloc_type_t;

reskia_mask_builder_t *SkMaskBuilder_new(); // () -> SkMaskBuilder *
/**
 * img is borrowed mutable storage. bounds must be non-NULL, and format must be valid.
 * Returns NULL for invalid input.
 */
reskia_mask_builder_t *SkMaskBuilder_newWithImageBoundsRowBytesFormat(uint8_t *img, const reskia_i_rect_t *bounds, uint32_t rowBytes, reskia_mask_builder_format_t format);
void SkMaskBuilder_delete(reskia_mask_builder_t *maskBuilder); // No-op for NULL input.
uint8_t *SkMaskBuilder_image(reskia_mask_builder_t *maskBuilder); // Borrowed mutable storage. Returns NULL for NULL input.
reskia_i_rect_t *SkMaskBuilder_bounds(reskia_mask_builder_t *maskBuilder); // Borrowed mutable storage. Returns NULL for NULL input.
uint32_t SkMaskBuilder_rowBytes(reskia_mask_builder_t *maskBuilder); // Returns 0 for NULL input.
reskia_mask_builder_format_t SkMaskBuilder_format(reskia_mask_builder_t *maskBuilder); // Returns -1 for NULL input.
uint8_t *SkMaskBuilder_getAddr1(reskia_mask_builder_t *maskBuilder, int x, int y); // Borrowed mutable storage. Returns NULL when format/bounds/image are inconsistent or input is NULL.
uint8_t *SkMaskBuilder_getAddr8(reskia_mask_builder_t *maskBuilder, int x, int y); // Borrowed mutable storage. Returns NULL when format/bounds/image are inconsistent or input is NULL.
uint16_t *SkMaskBuilder_getAddrLCD16(reskia_mask_builder_t *maskBuilder, int x, int y); // Borrowed mutable storage. Returns NULL when format/bounds/image are inconsistent or input is NULL.
uint32_t *SkMaskBuilder_getAddr32(reskia_mask_builder_t *maskBuilder, int x, int y); // Borrowed mutable storage. Returns NULL when format/bounds/image are inconsistent or input is NULL.
void *SkMaskBuilder_getAddr(reskia_mask_builder_t *maskBuilder, int x, int y); // Borrowed mutable storage. Returns NULL when BW/format/bounds/image are inconsistent or input is NULL.
// static
uint8_t *SkMaskBuilder_AllocImage(size_t bytes, reskia_mask_builder_alloc_type_t alloc); // bytes must be greater than 0. Returns NULL for 0 bytes or allocation failure.
void SkMaskBuilder_FreeImage(void *image); // No-op for NULL input.
sk_mask_builder_t SkMaskBuilder_PrepareDestination(int radiusX, int radiusY, const reskia_mask_t *src); // src must be non-NULL. Returns 0 for NULL input.

#ifdef __cplusplus
}
#endif

#endif //SK_MASK_BUILDER_H
