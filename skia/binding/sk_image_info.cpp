//
// Created by dolphilia on 2024/01/09.
//

#include "sk_image_info.h"

#include "include/core/SkImageInfo.h"

#include "../static/static_sk_color_space.h"
#include "../static/static_sk_color_info.h"
#include "../static/static_sk_i_rect.h"
#include "../static/static_sk_image_info.h"
#include "../static/static_sk_i_size.h"

#include "../static/static_sk_image_info-internal.h"
#include "../static/static_sk_i_rect-internal.h"
#include "../static/static_sk_i_size-internal.h"
#include "../static/static_sk_color_space-internal.h"
#include "../static/static_sk_color_info-internal.h"

extern "C" {

//bool operator==(const SkImageInfo &other)
//bool operator!=(const SkImageInfo &other)

void *SkImageInfo_new() {
    return new SkImageInfo();
}

void SkImageInfo_delete(void *image_info) {
    delete static_cast<SkImageInfo *>(image_info);
}

int SkImageInfo_width(void *image_info) {
    return static_cast<SkImageInfo *>(image_info)->width();
}

int SkImageInfo_height(void *image_info) {
    return static_cast<SkImageInfo *>(image_info)->height();
}

int SkImageInfo_colorType(void *image_info) {
    return static_cast<SkImageInfo *>(image_info)->colorType();
}

int SkImageInfo_alphaType(void *image_info) {
    return static_cast<SkImageInfo *>(image_info)->alphaType();
}

void * SkImageInfo_colorSpace(void *image_info) {
    return static_cast<SkImageInfo *>(image_info)->colorSpace();
}

sk_color_space_t SkImageInfo_refColorSpace(void *image_info) {
    return static_sk_color_space_make(static_cast<SkImageInfo *>(image_info)->refColorSpace());
}

bool SkImageInfo_isEmpty(void *image_info) {
    return static_cast<SkImageInfo *>(image_info)->isEmpty();
}

sk_color_info_t SkImageInfo_colorInfo(void *image_info) {
    return static_sk_color_info_make(static_cast<SkImageInfo *>(image_info)->colorInfo());
}

bool SkImageInfo_isOpaque(void *image_info) {
    return static_cast<SkImageInfo *>(image_info)->isOpaque();
}

sk_i_size_t SkImageInfo_dimensions(void *image_info) {
    return static_sk_i_size_make(static_cast<SkImageInfo *>(image_info)->dimensions());
}

sk_i_rect_t SkImageInfo_bounds(void *image_info) {
    return static_sk_i_rect_make(static_cast<SkImageInfo *>(image_info)->bounds());
}

bool SkImageInfo_gammaCloseToSRGB(void *image_info) {
    return static_cast<SkImageInfo *>(image_info)->gammaCloseToSRGB();
}

sk_image_info_t SkImageInfo_makeWH(void *image_info, int newWidth, int newHeight) {
    return static_sk_image_info_make(static_cast<SkImageInfo *>(image_info)->makeWH(newWidth, newHeight));
}

sk_image_info_t SkImageInfo_makeDimensions(void *image_info, sk_i_size_t newSize) {
    return static_sk_image_info_make(static_cast<SkImageInfo *>(image_info)->makeDimensions(static_sk_i_size_get_entity(newSize)));
}

sk_image_info_t SkImageInfo_makeAlphaType(void *image_info, int newAlphaType) {
    return static_sk_image_info_make(static_cast<SkImageInfo *>(image_info)->makeAlphaType(static_cast<SkAlphaType>(newAlphaType)));
}

sk_image_info_t SkImageInfo_makeColorType(void *image_info, int newColorType) {
    return static_sk_image_info_make(static_cast<SkImageInfo *>(image_info)->makeColorType(static_cast<SkColorType>(newColorType)));
}

sk_image_info_t SkImageInfo_makeColorSpace(void *image_info, sk_color_space_t color_space) {
    return static_sk_image_info_make(static_cast<SkImageInfo *>(image_info)->makeColorSpace(static_sk_color_space_get_entity(color_space)));
}

int SkImageInfo_bytesPerPixel(void *image_info) {
    return static_cast<SkImageInfo *>(image_info)->bytesPerPixel();
}

int SkImageInfo_shiftPerPixel(void *image_info) {
    return static_cast<SkImageInfo *>(image_info)->shiftPerPixel();
}

uint64_t SkImageInfo_minRowBytes64(void *image_info) {
    return static_cast<SkImageInfo *>(image_info)->minRowBytes64();
}

size_t SkImageInfo_minRowBytes(void *image_info) {
    return static_cast<SkImageInfo *>(image_info)->minRowBytes();
}

size_t SkImageInfo_computeOffset(void *image_info, int x, int y, size_t rowBytes) {
    return static_cast<SkImageInfo *>(image_info)->computeOffset(x, y, rowBytes);
}

size_t SkImageInfo_computeByteSize(void *image_info, size_t rowBytes) {
    return static_cast<SkImageInfo *>(image_info)->computeByteSize(rowBytes);
}

size_t SkImageInfo_computeMinByteSize(void *image_info) {
    return static_cast<SkImageInfo *>(image_info)->computeMinByteSize();
}

bool SkImageInfo_validRowBytes(void *image_info, size_t rowBytes) {
    return static_cast<SkImageInfo *>(image_info)->validRowBytes(rowBytes);
}

void SkImageInfo_reset(void *image_info) {
    static_cast<SkImageInfo *>(image_info)->reset();
}

// static

sk_image_info_t SkImageInfo_Make(int width, int height, int ct, int at) {
    return static_sk_image_info_make(SkImageInfo::Make(width, height, static_cast<SkColorType>(ct), static_cast<SkAlphaType>(at)));
}

sk_image_info_t SkImageInfo_Make_2(int width, int height, int ct, int at, sk_color_space_t color_space) {
    return static_sk_image_info_make(SkImageInfo::Make(width, height, static_cast<SkColorType>(ct), static_cast<SkAlphaType>(at), static_sk_color_space_get_entity(color_space)));
}

sk_image_info_t SkImageInfo_Make_3(sk_i_size_t dimensions, int ct, int at) {
    return static_sk_image_info_make(SkImageInfo::Make(static_sk_i_size_get_entity(dimensions), static_cast<SkColorType>(ct), static_cast<SkAlphaType>(at)));
}

sk_image_info_t SkImageInfo_Make_4(sk_i_size_t dimensions, int ct, int at, sk_color_space_t color_space) {
    return static_sk_image_info_make(SkImageInfo::Make(static_sk_i_size_get_entity(dimensions), static_cast<SkColorType>(ct), static_cast<SkAlphaType>(at), static_sk_color_space_get_entity(color_space)));
}

sk_image_info_t SkImageInfo_Make_5(sk_i_size_t dimensions, const void *colorInfo) {
    return static_sk_image_info_make(SkImageInfo::Make(static_sk_i_size_get_entity(dimensions), * static_cast<const SkColorInfo *>(colorInfo)));
}


sk_image_info_t SkImageInfo_MakeN32(int width, int height, int at) {
    return static_sk_image_info_make(SkImageInfo::MakeN32(width, height, static_cast<SkAlphaType>(at)));
}

sk_image_info_t SkImageInfo_MakeN32_2(int width, int height, int at, sk_color_space_t color_space) {
    return static_sk_image_info_make(SkImageInfo::MakeN32(width, height, static_cast<SkAlphaType>(at), static_sk_color_space_get_entity(color_space)));
}

sk_image_info_t SkImageInfo_MakeS32(int width, int height, int at) {
    return static_sk_image_info_make(SkImageInfo::MakeS32(width, height, static_cast<SkAlphaType>(at)));
}

sk_image_info_t SkImageInfo_MakeN32Premul(int width, int height) {
    return static_sk_image_info_make(SkImageInfo::MakeN32Premul(width, height));
}

sk_image_info_t SkImageInfo_MakeN32Premul_2(int width, int height, sk_color_space_t color_space) {
    return static_sk_image_info_make(SkImageInfo::MakeN32Premul(width, height, static_sk_color_space_get_entity(color_space)));
}

sk_image_info_t SkImageInfo_MakeN32Premul_3(sk_i_size_t dimensions) {
    return static_sk_image_info_make(SkImageInfo::MakeN32Premul(static_sk_i_size_get_entity(dimensions)));
}

sk_image_info_t SkImageInfo_MakeN32Premul_4(sk_i_size_t dimensions, sk_color_space_t color_space) {
    return static_sk_image_info_make(SkImageInfo::MakeN32Premul(static_sk_i_size_get_entity(dimensions), static_sk_color_space_get_entity(color_space)));
}

sk_image_info_t SkImageInfo_MakeA8(int width, int height) {
    return static_sk_image_info_make(SkImageInfo::MakeA8(width, height));
}

sk_image_info_t SkImageInfo_MakeA8_2(sk_i_size_t dimensions) {
    return static_sk_image_info_make(SkImageInfo::MakeA8(static_sk_i_size_get_entity(dimensions)));
}

sk_image_info_t SkImageInfo_MakeUnknown(int width, int height) {
    return static_sk_image_info_make(SkImageInfo::MakeUnknown(width, height));
}

sk_image_info_t SkImageInfo_MakeUnknown_2() {
    return static_sk_image_info_make(SkImageInfo::MakeUnknown());
}

bool SkImageInfo_ByteSizeOverflowed(size_t byteSize) {
    return SkImageInfo::ByteSizeOverflowed(byteSize);
}

}
