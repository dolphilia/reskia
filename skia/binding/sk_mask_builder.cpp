//
// Created by dolphilia on 25/01/30.
//

#include "sk_mask_builder.h"

#include "src/core/SkMask.h"

#include "../static/static_sk_mask_builder.h"

#include "../static/static_sk_mask_builder-internal.h"

//    SkMaskBuilder(const SkMaskBuilder&)
//    SkMaskBuilder(SkMaskBuilder&&)
//    SkMaskBuilder& operator=(const SkMaskBuilder&)
//    SkMaskBuilder& operator=(SkMaskBuilder&& that)

extern "C" {

reskia_mask_builder_t *SkMaskBuilder_new() {
    return reinterpret_cast<reskia_mask_builder_t *>(new SkMaskBuilder());
}

reskia_mask_builder_t *SkMaskBuilder_new_2(uint8_t *img, const reskia_i_rect_t *bounds, uint32_t rowBytes, int format) {
    return reinterpret_cast<reskia_mask_builder_t *>(new SkMaskBuilder(img, *reinterpret_cast<const SkIRect *>(bounds), rowBytes, static_cast<SkMask::Format>(format)));
}

void SkMaskBuilder_delete(reskia_mask_builder_t *maskBuilder) {
    delete reinterpret_cast<SkMaskBuilder *>(maskBuilder);
}

uint8_t *SkMaskBuilder_image(reskia_mask_builder_t *maskBuilder) {
    return reinterpret_cast<SkMaskBuilder *>(maskBuilder)->image();
}

reskia_i_rect_t *SkMaskBuilder_bounds(reskia_mask_builder_t *maskBuilder) {
    return reinterpret_cast<reskia_i_rect_t *>(&reinterpret_cast<SkMaskBuilder *>(maskBuilder)->bounds());
}

uint32_t SkMaskBuilder_rowBytes(reskia_mask_builder_t *maskBuilder) {
    return reinterpret_cast<SkMaskBuilder *>(maskBuilder)->rowBytes();
}

int SkMaskBuilder_format(reskia_mask_builder_t *maskBuilder) {
    return reinterpret_cast<SkMaskBuilder *>(maskBuilder)->format();
}

uint8_t *SkMaskBuilder_getAddr1(reskia_mask_builder_t *maskBuilder, int x, int y) {
    return reinterpret_cast<SkMaskBuilder *>(maskBuilder)->getAddr1(x, y);
}

uint8_t *SkMaskBuilder_getAddr8(reskia_mask_builder_t *maskBuilder, int x, int y) {
    return reinterpret_cast<SkMaskBuilder *>(maskBuilder)->getAddr8(x, y);
}

uint16_t *SkMaskBuilder_getAddrLCD16(reskia_mask_builder_t *maskBuilder, int x, int y) {
    return reinterpret_cast<SkMaskBuilder *>(maskBuilder)->getAddrLCD16(x, y);
}

uint32_t *SkMaskBuilder_getAddr32(reskia_mask_builder_t *maskBuilder, int x, int y) {
    return reinterpret_cast<SkMaskBuilder *>(maskBuilder)->getAddr32(x, y);
}

void *SkMaskBuilder_getAddr(reskia_mask_builder_t *maskBuilder, int x, int y) {
    return reinterpret_cast<SkMaskBuilder *>(maskBuilder)->getAddr(x, y);
}

// static

uint8_t *SkMaskBuilder_AllocImage(size_t bytes, int alloc) {
    return SkMaskBuilder::AllocImage(bytes, static_cast<SkMaskBuilder::AllocType>(alloc));
}

void SkMaskBuilder_FreeImage(void *image) {
    SkMaskBuilder::FreeImage(image);
}

int SkMaskBuilder_PrepareDestination(int radiusX, int radiusY, const reskia_mask_t *src) {
    return static_sk_mask_builder_make(SkMaskBuilder::PrepareDestination(radiusX, radiusY, *reinterpret_cast<const SkMask *>(src)));
}

}
