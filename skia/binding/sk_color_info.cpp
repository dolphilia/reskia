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

reskia_color_info_t *SkColorInfo_new() {
    return reinterpret_cast<reskia_color_info_t *>(new SkColorInfo());
}

reskia_color_info_t *SkColorInfo_new_2(int ct, int at, sk_color_space_t color_space) {
    return reinterpret_cast<reskia_color_info_t *>(new SkColorInfo(static_cast<SkColorType>(ct), static_cast<SkAlphaType>(at), static_sk_color_space_get_entity(color_space)));
}

reskia_color_info_t *SkColorInfo_new_3(const reskia_color_info_t *color_info) {
    return reinterpret_cast<reskia_color_info_t *>(new SkColorInfo(*reinterpret_cast<const SkColorInfo *>(color_info)));
}

void SkColorInfo_delete(reskia_color_info_t *color_info) {
    delete reinterpret_cast<SkColorInfo *>(color_info);
}

reskia_alpha_type_t SkColorInfo_alphaType(reskia_color_info_t *color_info) {
    return static_cast<reskia_alpha_type_t>(reinterpret_cast<SkColorInfo *>(color_info)->alphaType());
}

int SkColorInfo_bytesPerPixel(reskia_color_info_t *color_info) {
    return reinterpret_cast<SkColorInfo *>(color_info)->bytesPerPixel();
}

reskia_color_space_t *SkColorInfo_colorSpace(reskia_color_info_t *color_info) {
    return reinterpret_cast<reskia_color_space_t *>(reinterpret_cast<SkColorInfo *>(color_info)->colorSpace());
}

reskia_color_info_color_type_t SkColorInfo_colorType(reskia_color_info_t *color_info) {
    return static_cast<reskia_color_info_color_type_t>(reinterpret_cast<SkColorInfo *>(color_info)->colorType());
}

bool SkColorInfo_gammaCloseToSRGB(reskia_color_info_t *color_info) {
    return reinterpret_cast<SkColorInfo *>(color_info)->gammaCloseToSRGB();
}

bool SkColorInfo_isOpaque(reskia_color_info_t *color_info) {
    return reinterpret_cast<SkColorInfo *>(color_info)->isOpaque();
}

sk_color_info_t SkColorInfo_makeAlphaType(reskia_color_info_t *color_info, reskia_alpha_type_t newAlphaType) {
    return static_sk_color_info_make(reinterpret_cast<SkColorInfo *>(color_info)->makeAlphaType(static_cast<SkAlphaType>(newAlphaType)));
}

sk_color_info_t SkColorInfo_makeColorSpace(reskia_color_info_t *color_info, sk_color_space_t color_space) {
    return static_sk_color_info_make(reinterpret_cast<SkColorInfo *>(color_info)->makeColorSpace(static_sk_color_space_get_entity(color_space)));
}

sk_color_info_t SkColorInfo_makeColorType(reskia_color_info_t *color_info, reskia_color_info_color_type_t newColorType) {
    return static_sk_color_info_make(reinterpret_cast<SkColorInfo *>(color_info)->makeColorType(static_cast<SkColorType>(newColorType)));
}

sk_color_space_t SkColorInfo_refColorSpace(reskia_color_info_t *color_info) {
    return static_sk_color_space_make(reinterpret_cast<SkColorInfo *>(color_info)->refColorSpace());
}

int SkColorInfo_shiftPerPixel(reskia_color_info_t *color_info) {
    return reinterpret_cast<SkColorInfo *>(color_info)->shiftPerPixel();
}

}
