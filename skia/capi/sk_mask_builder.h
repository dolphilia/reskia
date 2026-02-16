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
reskia_mask_builder_t *SkMaskBuilder_newWithImageBoundsRowBytesFormat(uint8_t *img, const reskia_i_rect_t *bounds, uint32_t rowBytes, reskia_mask_builder_format_t format); // (uint8_t* img, const SkIRect * bounds, uint32_t rowBytes, SkMask::Format format) -> SkMaskBuilder *
void SkMaskBuilder_delete(reskia_mask_builder_t *maskBuilder); // (SkMaskBuilder* maskBuilder)
uint8_t *SkMaskBuilder_image(reskia_mask_builder_t *maskBuilder); // (SkMaskBuilder *maskBuilder) -> uint8_t*
reskia_i_rect_t *SkMaskBuilder_bounds(reskia_mask_builder_t *maskBuilder); // (SkMaskBuilder *maskBuilder) -> SkIRect *
uint32_t SkMaskBuilder_rowBytes(reskia_mask_builder_t *maskBuilder); // (SkMaskBuilder *maskBuilder) -> uint32_t
reskia_mask_builder_format_t SkMaskBuilder_format(reskia_mask_builder_t *maskBuilder); // (SkMaskBuilder *maskBuilder) -> SkMask::Format
uint8_t *SkMaskBuilder_getAddr1(reskia_mask_builder_t *maskBuilder, int x, int y); // (SkMaskBuilder *maskBuilder, int x, int y) -> uint8_t*
uint8_t *SkMaskBuilder_getAddr8(reskia_mask_builder_t *maskBuilder, int x, int y); // (SkMaskBuilder *maskBuilder, int x, int y) -> uint8_t*
uint16_t *SkMaskBuilder_getAddrLCD16(reskia_mask_builder_t *maskBuilder, int x, int y); // (SkMaskBuilder *maskBuilder, int x, int y) -> uint16_t*
uint32_t *SkMaskBuilder_getAddr32(reskia_mask_builder_t *maskBuilder, int x, int y); // (SkMaskBuilder *maskBuilder, int x, int y) -> uint32_t*
void *SkMaskBuilder_getAddr(reskia_mask_builder_t *maskBuilder, int x, int y); // (SkMaskBuilder *maskBuilder, int x, int y) -> void*
// static
uint8_t *SkMaskBuilder_AllocImage(size_t bytes, reskia_mask_builder_alloc_type_t alloc); // (size_t bytes, SkMaskBuilder::AllocType alloc) -> uint8_t*
void SkMaskBuilder_FreeImage(void *image); // (void* image)
sk_mask_builder_t SkMaskBuilder_PrepareDestination(int radiusX, int radiusY, const reskia_mask_t *src); // (int radiusX, int radiusY, const SkMask * src) -> sk_mask_builder_t

#ifdef __cplusplus
}
#endif

#endif //SK_MASK_BUILDER_H
