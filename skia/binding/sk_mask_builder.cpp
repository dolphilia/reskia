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

void * SkMaskBuilder_new() {
    return new SkMaskBuilder();
}

void * SkMaskBuilder_new_2(void * img, const void * bounds, uint32_t rowBytes, int format) {
    return new SkMaskBuilder(static_cast<uint8_t *>(img), * static_cast<const SkIRect *>(bounds), rowBytes, static_cast<SkMask::Format>(format));
}

void SkMaskBuilder_delete(void * maskBuilder) {
    delete static_cast<SkMaskBuilder *>(maskBuilder);
}

void * SkMaskBuilder_image(void *maskBuilder) {
    return static_cast<SkMaskBuilder *>(maskBuilder)->image();
}

void * SkMaskBuilder_bounds(void *maskBuilder) {
    return &static_cast<SkMaskBuilder *>(maskBuilder)->bounds();
}

uint32_t SkMaskBuilder_rowBytes(void *maskBuilder) {
    return static_cast<SkMaskBuilder *>(maskBuilder)->rowBytes();
}

int SkMaskBuilder_format(void *maskBuilder) {
    return static_cast<SkMaskBuilder *>(maskBuilder)->format();
}

void * SkMaskBuilder_getAddr1(void *maskBuilder, int x, int y) {
    return static_cast<SkMaskBuilder *>(maskBuilder)->getAddr1(x, y);
}

void * SkMaskBuilder_getAddr8(void *maskBuilder, int x, int y) {
    return static_cast<SkMaskBuilder *>(maskBuilder)->getAddr8(x, y);
}

void * SkMaskBuilder_getAddrLCD16(void *maskBuilder, int x, int y) {
    return static_cast<SkMaskBuilder *>(maskBuilder)->getAddrLCD16(x, y);
}

void * SkMaskBuilder_getAddr32(void *maskBuilder, int x, int y) {
    return static_cast<SkMaskBuilder *>(maskBuilder)->getAddr32(x, y);
}

void * SkMaskBuilder_getAddr(void *maskBuilder, int x, int y) {
    return static_cast<SkMaskBuilder *>(maskBuilder)->getAddr(x, y);
}

// static

static void * SkMaskBuilder_AllocImage(size_t bytes, int alloc) {
    return SkMaskBuilder::AllocImage(bytes, static_cast<SkMaskBuilder::AllocType>(alloc));
}

static void SkMaskBuilder_FreeImage(void* image) {
    SkMaskBuilder::FreeImage(image);
}

static int SkMaskBuilder_PrepareDestination(int radiusX, int radiusY, const void * src) {
    return static_sk_mask_builder_make(SkMaskBuilder::PrepareDestination(radiusX, radiusY, * static_cast<const SkMask *>(src)));
}

}