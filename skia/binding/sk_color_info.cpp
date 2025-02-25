//
// Created by dolphilia on 2024/01/08.
//

#include "sk_color_info.h"

#include "include/core/SkImageInfo.h"

#include "../static/static_sk_color_space.h"
#include "../static/static_sk_color_info.h"

#include "../static/static_sk_color_space-internal.h"
#include "../static/static_sk_color_info-internal.h"
#include "../static/static_sk_color_info.h"

extern "C" {

void *SkColorInfo_new() {
    return new SkColorInfo();
}

void *SkColorInfo_new_2(int ct, int at, sk_color_space_t color_space) {
    return new SkColorInfo(static_cast<SkColorType>(ct), static_cast<SkAlphaType>(at), static_sk_color_space_get_entity(color_space));
}

void *SkColorInfo_new_3(const void *color_info) {
    return new SkColorInfo(* static_cast<const SkColorInfo *>(color_info));
}

void SkColorInfo_delete(void *color_info) {
    delete static_cast<SkColorInfo *>(color_info);
}

int SkColorInfo_alphaType(void *color_info) {
    return static_cast<SkColorInfo *>(color_info)->alphaType();
}

int SkColorInfo_bytesPerPixel(void *color_info) {
    return static_cast<SkColorInfo *>(color_info)->bytesPerPixel();
}

void* SkColorInfo_colorSpace(void *color_info) {
    return static_cast<SkColorInfo *>(color_info)->colorSpace();
}

int SkColorInfo_colorType(void *color_info) {
    return static_cast<SkColorInfo *>(color_info)->colorType();
}

bool SkColorInfo_gammaCloseToSRGB(void *color_info) {
    return static_cast<SkColorInfo *>(color_info)->gammaCloseToSRGB();
}

bool SkColorInfo_isOpaque(void *color_info) {
    return static_cast<SkColorInfo *>(color_info)->isOpaque();
}

sk_color_info_t SkColorInfo_makeAlphaType(void *color_info, int newAlphaType) {
    return static_sk_color_info_make(static_cast<SkColorInfo *>(color_info)->makeAlphaType(static_cast<SkAlphaType>(newAlphaType)));
}

sk_color_info_t SkColorInfo_makeColorSpace(void *color_info, sk_color_space_t color_space) {
    return static_sk_color_info_make(static_cast<SkColorInfo *>(color_info)->makeColorSpace(static_sk_color_space_get_entity(color_space)));
}

sk_color_info_t SkColorInfo_makeColorType(void *color_info, int newColorType) {
    return static_sk_color_info_make(static_cast<SkColorInfo *>(color_info)->makeColorType(static_cast<SkColorType>(newColorType)));
}

sk_color_space_t SkColorInfo_refColorSpace(void *color_info) {
    return static_sk_color_space_make(static_cast<SkColorInfo *>(color_info)->refColorSpace());
}

int SkColorInfo_shiftPerPixel(void *color_info) {
    return static_cast<SkColorInfo *>(color_info)->shiftPerPixel();
}

}