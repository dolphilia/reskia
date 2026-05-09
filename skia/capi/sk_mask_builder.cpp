//
// Created by dolphilia on 25/01/30.
//

#include "sk_mask_builder.h"

#include "src/core/SkMask.h"

#include "../handles/static_sk_mask_builder.h"

#include "../handles/static_sk_mask_builder-internal.h"

//    SkMaskBuilder(const SkMaskBuilder&)
//    SkMaskBuilder(SkMaskBuilder&&)
//    SkMaskBuilder& operator=(const SkMaskBuilder&)
//    SkMaskBuilder& operator=(SkMaskBuilder&& that)

namespace {

bool can_access_mask_builder_addr(const SkMaskBuilder *mask_builder, int x, int y) {
    return mask_builder != nullptr && mask_builder->fImage != nullptr && mask_builder->fBounds.contains(x, y);
}

}  // namespace

extern "C" {

reskia_mask_builder_t *SkMaskBuilder_new() {
    return reinterpret_cast<reskia_mask_builder_t *>(new SkMaskBuilder());
}

reskia_mask_builder_t *SkMaskBuilder_newWithImageBoundsRowBytesFormat(uint8_t *img, const reskia_i_rect_t *bounds, uint32_t rowBytes, reskia_mask_builder_format_t format) {
    if (bounds == nullptr || !SkMask::IsValidFormat(static_cast<uint8_t>(format))) {
        return nullptr;
    }
    return reinterpret_cast<reskia_mask_builder_t *>(new SkMaskBuilder(img, *reinterpret_cast<const SkIRect *>(bounds), rowBytes, static_cast<SkMask::Format>(format)));
}

void SkMaskBuilder_delete(reskia_mask_builder_t *maskBuilder) {
    if (maskBuilder == nullptr) {
        return;
    }
    delete reinterpret_cast<SkMaskBuilder *>(maskBuilder);
}

uint8_t *SkMaskBuilder_image(reskia_mask_builder_t *maskBuilder) {
    if (maskBuilder == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<SkMaskBuilder *>(maskBuilder)->image();
}

reskia_i_rect_t *SkMaskBuilder_bounds(reskia_mask_builder_t *maskBuilder) {
    if (maskBuilder == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_i_rect_t *>(&reinterpret_cast<SkMaskBuilder *>(maskBuilder)->bounds());
}

uint32_t SkMaskBuilder_rowBytes(reskia_mask_builder_t *maskBuilder) {
    if (maskBuilder == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkMaskBuilder *>(maskBuilder)->rowBytes();
}

reskia_mask_builder_format_t SkMaskBuilder_format(reskia_mask_builder_t *maskBuilder) {
    if (maskBuilder == nullptr) {
        return -1;
    }
    return static_cast<reskia_mask_builder_format_t>(reinterpret_cast<SkMaskBuilder *>(maskBuilder)->format());
}

uint8_t *SkMaskBuilder_getAddr1(reskia_mask_builder_t *maskBuilder, int x, int y) {
    auto *sk_mask_builder = reinterpret_cast<SkMaskBuilder *>(maskBuilder);
    if (!can_access_mask_builder_addr(sk_mask_builder, x, y) || sk_mask_builder->fFormat != SkMask::kBW_Format) {
        return nullptr;
    }
    return sk_mask_builder->getAddr1(x, y);
}

uint8_t *SkMaskBuilder_getAddr8(reskia_mask_builder_t *maskBuilder, int x, int y) {
    auto *sk_mask_builder = reinterpret_cast<SkMaskBuilder *>(maskBuilder);
    if (!can_access_mask_builder_addr(sk_mask_builder, x, y) || (sk_mask_builder->fFormat != SkMask::kA8_Format && sk_mask_builder->fFormat != SkMask::kSDF_Format)) {
        return nullptr;
    }
    return sk_mask_builder->getAddr8(x, y);
}

uint16_t *SkMaskBuilder_getAddrLCD16(reskia_mask_builder_t *maskBuilder, int x, int y) {
    auto *sk_mask_builder = reinterpret_cast<SkMaskBuilder *>(maskBuilder);
    if (!can_access_mask_builder_addr(sk_mask_builder, x, y) || sk_mask_builder->fFormat != SkMask::kLCD16_Format) {
        return nullptr;
    }
    return sk_mask_builder->getAddrLCD16(x, y);
}

uint32_t *SkMaskBuilder_getAddr32(reskia_mask_builder_t *maskBuilder, int x, int y) {
    auto *sk_mask_builder = reinterpret_cast<SkMaskBuilder *>(maskBuilder);
    if (!can_access_mask_builder_addr(sk_mask_builder, x, y) || sk_mask_builder->fFormat != SkMask::kARGB32_Format) {
        return nullptr;
    }
    return sk_mask_builder->getAddr32(x, y);
}

void *SkMaskBuilder_getAddr(reskia_mask_builder_t *maskBuilder, int x, int y) {
    auto *sk_mask_builder = reinterpret_cast<SkMaskBuilder *>(maskBuilder);
    if (!can_access_mask_builder_addr(sk_mask_builder, x, y) || sk_mask_builder->fFormat == SkMask::kBW_Format || !SkMask::IsValidFormat(sk_mask_builder->fFormat)) {
        return nullptr;
    }
    return sk_mask_builder->getAddr(x, y);
}

// static

uint8_t *SkMaskBuilder_AllocImage(size_t bytes, reskia_mask_builder_alloc_type_t alloc) {
    if (bytes == 0) {
        return nullptr;
    }
    return SkMaskBuilder::AllocImage(bytes, static_cast<SkMaskBuilder::AllocType>(alloc));
}

void SkMaskBuilder_FreeImage(void *image) {
    if (image == nullptr) {
        return;
    }
    SkMaskBuilder::FreeImage(image);
}

int SkMaskBuilder_PrepareDestination(int radiusX, int radiusY, const reskia_mask_t *src) {
    if (src == nullptr) {
        return 0;
    }
    return static_sk_mask_builder_make(SkMaskBuilder::PrepareDestination(radiusX, radiusY, *reinterpret_cast<const SkMask *>(src)));
}

}
