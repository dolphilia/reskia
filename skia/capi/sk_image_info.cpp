//
// Created by dolphilia on 2024/01/09.
//

#include "sk_image_info.h"

#include "include/core/SkImageInfo.h"

#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_color_info.h"
#include "../handles/static_sk_i_rect.h"
#include "../handles/static_sk_image_info.h"
#include "../handles/static_sk_i_size.h"

#include "../handles/static_sk_image_info-internal.h"
#include "../handles/static_sk_i_rect-internal.h"
#include "../handles/static_sk_i_size-internal.h"
#include "../handles/static_sk_color_space-internal.h"
#include "../handles/static_sk_color_info-internal.h"

extern "C" {

//bool operator==(const SkImageInfo &other)
//bool operator!=(const SkImageInfo &other)

reskia_image_info_t *SkImageInfo_new() {
    return reinterpret_cast<reskia_image_info_t *>(new SkImageInfo());
}

void SkImageInfo_delete(reskia_image_info_t *image_info) {
    delete reinterpret_cast<SkImageInfo *>(image_info);
}

int SkImageInfo_width(reskia_image_info_t *image_info) {
    return reinterpret_cast<SkImageInfo *>(image_info)->width();
}

int SkImageInfo_height(reskia_image_info_t *image_info) {
    return reinterpret_cast<SkImageInfo *>(image_info)->height();
}

reskia_image_info_color_type_t SkImageInfo_colorType(reskia_image_info_t *image_info) {
    return static_cast<reskia_image_info_color_type_t>(reinterpret_cast<SkImageInfo *>(image_info)->colorType());
}

reskia_image_info_alpha_type_t SkImageInfo_alphaType(reskia_image_info_t *image_info) {
    return static_cast<reskia_image_info_alpha_type_t>(reinterpret_cast<SkImageInfo *>(image_info)->alphaType());
}

reskia_color_space_t *SkImageInfo_colorSpace(reskia_image_info_t *image_info) {
    return reinterpret_cast<reskia_color_space_t *>(reinterpret_cast<SkImageInfo *>(image_info)->colorSpace());
}

sk_color_space_t SkImageInfo_refColorSpace(reskia_image_info_t *image_info) {
    return static_sk_color_space_make(reinterpret_cast<SkImageInfo *>(image_info)->refColorSpace());
}

bool SkImageInfo_isEmpty(reskia_image_info_t *image_info) {
    return reinterpret_cast<SkImageInfo *>(image_info)->isEmpty();
}

sk_color_info_t SkImageInfo_colorInfo(reskia_image_info_t *image_info) {
    return static_sk_color_info_make(reinterpret_cast<SkImageInfo *>(image_info)->colorInfo());
}

bool SkImageInfo_isOpaque(reskia_image_info_t *image_info) {
    return reinterpret_cast<SkImageInfo *>(image_info)->isOpaque();
}

sk_i_size_t SkImageInfo_dimensions(reskia_image_info_t *image_info) {
    return static_sk_i_size_make(reinterpret_cast<SkImageInfo *>(image_info)->dimensions());
}

sk_i_rect_t SkImageInfo_bounds(reskia_image_info_t *image_info) {
    return static_sk_i_rect_make(reinterpret_cast<SkImageInfo *>(image_info)->bounds());
}

bool SkImageInfo_gammaCloseToSRGB(reskia_image_info_t *image_info) {
    return reinterpret_cast<SkImageInfo *>(image_info)->gammaCloseToSRGB();
}

sk_image_info_t SkImageInfo_makeWH(reskia_image_info_t *image_info, int newWidth, int newHeight) {
    return static_sk_image_info_make(reinterpret_cast<SkImageInfo *>(image_info)->makeWH(newWidth, newHeight));
}

sk_image_info_t SkImageInfo_makeDimensions(reskia_image_info_t *image_info, sk_i_size_t newSize) {
    return static_sk_image_info_make(reinterpret_cast<SkImageInfo *>(image_info)->makeDimensions(static_sk_i_size_get_entity(newSize)));
}

sk_image_info_t SkImageInfo_makeAlphaType(reskia_image_info_t *image_info, reskia_image_info_alpha_type_t newAlphaType) {
    return static_sk_image_info_make(reinterpret_cast<SkImageInfo *>(image_info)->makeAlphaType(static_cast<SkAlphaType>(newAlphaType)));
}

sk_image_info_t SkImageInfo_makeColorType(reskia_image_info_t *image_info, reskia_image_info_color_type_t newColorType) {
    return static_sk_image_info_make(reinterpret_cast<SkImageInfo *>(image_info)->makeColorType(static_cast<SkColorType>(newColorType)));
}

sk_image_info_t SkImageInfo_makeColorSpace(reskia_image_info_t *image_info, sk_color_space_t color_space) {
    return static_sk_image_info_make(reinterpret_cast<SkImageInfo *>(image_info)->makeColorSpace(static_sk_color_space_get_entity(color_space)));
}

int SkImageInfo_bytesPerPixel(reskia_image_info_t *image_info) {
    return reinterpret_cast<SkImageInfo *>(image_info)->bytesPerPixel();
}

int SkImageInfo_shiftPerPixel(reskia_image_info_t *image_info) {
    return reinterpret_cast<SkImageInfo *>(image_info)->shiftPerPixel();
}

reskia_u64_t SkImageInfo_minRowBytes64(reskia_image_info_t *image_info) {
    return reinterpret_cast<SkImageInfo *>(image_info)->minRowBytes64();
}

size_t SkImageInfo_minRowBytes(reskia_image_info_t *image_info) {
    return reinterpret_cast<SkImageInfo *>(image_info)->minRowBytes();
}

size_t SkImageInfo_computeOffset(reskia_image_info_t *image_info, int x, int y, size_t rowBytes) {
    return reinterpret_cast<SkImageInfo *>(image_info)->computeOffset(x, y, rowBytes);
}

size_t SkImageInfo_computeByteSize(reskia_image_info_t *image_info, size_t rowBytes) {
    return reinterpret_cast<SkImageInfo *>(image_info)->computeByteSize(rowBytes);
}

size_t SkImageInfo_computeMinByteSize(reskia_image_info_t *image_info) {
    return reinterpret_cast<SkImageInfo *>(image_info)->computeMinByteSize();
}

bool SkImageInfo_validRowBytes(reskia_image_info_t *image_info, size_t rowBytes) {
    return reinterpret_cast<SkImageInfo *>(image_info)->validRowBytes(rowBytes);
}

void SkImageInfo_reset(reskia_image_info_t *image_info) {
    reinterpret_cast<SkImageInfo *>(image_info)->reset();
}

// static

sk_image_info_t SkImageInfo_Make(int width, int height, reskia_image_info_color_type_t ct, reskia_image_info_alpha_type_t at) {
    return static_sk_image_info_make(SkImageInfo::Make(width, height, static_cast<SkColorType>(ct), static_cast<SkAlphaType>(at)));
}

sk_image_info_t SkImageInfo_MakeWithColorSpace(int width, int height, reskia_image_info_color_type_t ct, reskia_image_info_alpha_type_t at, sk_color_space_t color_space) {
    return static_sk_image_info_make(SkImageInfo::Make(width, height, static_cast<SkColorType>(ct), static_cast<SkAlphaType>(at), static_sk_color_space_get_entity(color_space)));
}

sk_image_info_t SkImageInfo_MakeWithDimensions(sk_i_size_t dimensions, reskia_image_info_color_type_t ct, reskia_image_info_alpha_type_t at) {
    return static_sk_image_info_make(SkImageInfo::Make(static_sk_i_size_get_entity(dimensions), static_cast<SkColorType>(ct), static_cast<SkAlphaType>(at)));
}

sk_image_info_t SkImageInfo_MakeWithDimensionsAndColorSpace(sk_i_size_t dimensions, reskia_image_info_color_type_t ct, reskia_image_info_alpha_type_t at, sk_color_space_t color_space) {
    return static_sk_image_info_make(SkImageInfo::Make(static_sk_i_size_get_entity(dimensions), static_cast<SkColorType>(ct), static_cast<SkAlphaType>(at), static_sk_color_space_get_entity(color_space)));
}

sk_image_info_t SkImageInfo_Make_5(sk_i_size_t dimensions, const reskia_color_info_t *colorInfo) {
    return static_sk_image_info_make(SkImageInfo::Make(static_sk_i_size_get_entity(dimensions), * reinterpret_cast<const SkColorInfo *>(colorInfo)));
}


sk_image_info_t SkImageInfo_MakeN32(int width, int height, reskia_image_info_alpha_type_t at) {
    return static_sk_image_info_make(SkImageInfo::MakeN32(width, height, static_cast<SkAlphaType>(at)));
}

sk_image_info_t SkImageInfo_MakeN32WithColorSpace(int width, int height, reskia_image_info_alpha_type_t at, sk_color_space_t color_space) {
    return static_sk_image_info_make(SkImageInfo::MakeN32(width, height, static_cast<SkAlphaType>(at), static_sk_color_space_get_entity(color_space)));
}

sk_image_info_t SkImageInfo_MakeS32(int width, int height, reskia_image_info_alpha_type_t at) {
    return static_sk_image_info_make(SkImageInfo::MakeS32(width, height, static_cast<SkAlphaType>(at)));
}

sk_image_info_t SkImageInfo_MakeN32Premul(int width, int height) {
    return static_sk_image_info_make(SkImageInfo::MakeN32Premul(width, height));
}

sk_image_info_t SkImageInfo_MakeN32PremulWithColorSpace(int width, int height, sk_color_space_t color_space) {
    return static_sk_image_info_make(SkImageInfo::MakeN32Premul(width, height, static_sk_color_space_get_entity(color_space)));
}

sk_image_info_t SkImageInfo_MakeN32PremulWithDimensions(sk_i_size_t dimensions) {
    return static_sk_image_info_make(SkImageInfo::MakeN32Premul(static_sk_i_size_get_entity(dimensions)));
}

sk_image_info_t SkImageInfo_MakeN32PremulWithDimensionsAndColorSpace(sk_i_size_t dimensions, sk_color_space_t color_space) {
    return static_sk_image_info_make(SkImageInfo::MakeN32Premul(static_sk_i_size_get_entity(dimensions), static_sk_color_space_get_entity(color_space)));
}

sk_image_info_t SkImageInfo_MakeA8(int width, int height) {
    return static_sk_image_info_make(SkImageInfo::MakeA8(width, height));
}

sk_image_info_t SkImageInfo_MakeA8WithDimensions(sk_i_size_t dimensions) {
    return static_sk_image_info_make(SkImageInfo::MakeA8(static_sk_i_size_get_entity(dimensions)));
}

sk_image_info_t SkImageInfo_MakeUnknown(int width, int height) {
    return static_sk_image_info_make(SkImageInfo::MakeUnknown(width, height));
}

sk_image_info_t SkImageInfo_MakeUnknownDefault() {
    return static_sk_image_info_make(SkImageInfo::MakeUnknown());
}

bool SkImageInfo_ByteSizeOverflowed(size_t byteSize) {
    return SkImageInfo::ByteSizeOverflowed(byteSize);
}

}
