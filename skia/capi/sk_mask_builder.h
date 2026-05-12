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
 * img は borrowed mutable。bounds 非 NULL、format valid。invalid 入力では NULL
 */
reskia_mask_builder_t *SkMaskBuilder_newWithImageBoundsRowBytesFormat(uint8_t *img, const reskia_i_rect_t *bounds, uint32_t rowBytes, reskia_mask_builder_format_t format);
void SkMaskBuilder_delete(reskia_mask_builder_t *maskBuilder); // NULL 入力では no-op
uint8_t *SkMaskBuilder_image(reskia_mask_builder_t *maskBuilder); // borrowed mutable。NULL 入力では NULL
reskia_i_rect_t *SkMaskBuilder_bounds(reskia_mask_builder_t *maskBuilder); // borrowed mutable。NULL 入力では NULL
uint32_t SkMaskBuilder_rowBytes(reskia_mask_builder_t *maskBuilder); // NULL 入力では 0
reskia_mask_builder_format_t SkMaskBuilder_format(reskia_mask_builder_t *maskBuilder); // NULL 入力では -1
uint8_t *SkMaskBuilder_getAddr1(reskia_mask_builder_t *maskBuilder, int x, int y); // borrowed mutable。format/bounds/image 不一致や NULL 入力では NULL
uint8_t *SkMaskBuilder_getAddr8(reskia_mask_builder_t *maskBuilder, int x, int y); // borrowed mutable。format/bounds/image 不一致や NULL 入力では NULL
uint16_t *SkMaskBuilder_getAddrLCD16(reskia_mask_builder_t *maskBuilder, int x, int y); // borrowed mutable。format/bounds/image 不一致や NULL 入力では NULL
uint32_t *SkMaskBuilder_getAddr32(reskia_mask_builder_t *maskBuilder, int x, int y); // borrowed mutable。format/bounds/image 不一致や NULL 入力では NULL
void *SkMaskBuilder_getAddr(reskia_mask_builder_t *maskBuilder, int x, int y); // borrowed mutable。BW/format/bounds/image 不一致や NULL 入力では NULL
// static
uint8_t *SkMaskBuilder_AllocImage(size_t bytes, reskia_mask_builder_alloc_type_t alloc); // bytes > 0。0 や割当不能では NULL
void SkMaskBuilder_FreeImage(void *image); // NULL 入力では no-op
sk_mask_builder_t SkMaskBuilder_PrepareDestination(int radiusX, int radiusY, const reskia_mask_t *src); // src 非 NULL。NULL 入力では 0

#ifdef __cplusplus
}
#endif

#endif //SK_MASK_BUILDER_H
