//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_COLOR_INFO_H
#define RAIA_SKIA_SK_COLOR_INFO_H

#include <stdint.h>
#include "sk_alpha_type.h"
#include "../handles/static_sk_color_info.h"
#include "../handles/static_sk_color_space.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_color_info_t reskia_color_info_t;
typedef struct reskia_color_space_t reskia_color_space_t;
typedef int32_t reskia_color_info_color_type_t;

reskia_color_info_t *SkColorInfo_new(); // () -> SkColorInfo *
reskia_color_info_t *SkColorInfo_newWithColorTypeAlphaTypeColorSpace(int ct, int at, sk_color_space_t color_space); // (SkColorType ct, SkAlphaType at, sk_color_space_t color_space) -> SkColorInfo *
reskia_color_info_t *SkColorInfo_newCopy(const reskia_color_info_t *color_info); // (const SkColorInfo *color_info) -> SkColorInfo *
void SkColorInfo_delete(reskia_color_info_t *color_info); // (SkColorInfo *color_info)
reskia_alpha_type_t SkColorInfo_alphaType(reskia_color_info_t *color_info); // (SkColorInfo *color_info) -> SkAlphaType
int SkColorInfo_bytesPerPixel(reskia_color_info_t *color_info); // (SkColorInfo *color_info) -> int
reskia_color_space_t *SkColorInfo_colorSpace(reskia_color_info_t *color_info); // (SkColorInfo *color_info) -> SkColorSpace*
reskia_color_info_color_type_t SkColorInfo_colorType(reskia_color_info_t *color_info); // (SkColorInfo *color_info) -> SkColorType
bool SkColorInfo_gammaCloseToSRGB(reskia_color_info_t *color_info); // (SkColorInfo *color_info) -> bool
bool SkColorInfo_isOpaque(reskia_color_info_t *color_info); // (SkColorInfo *color_info) -> bool
sk_color_info_t SkColorInfo_makeAlphaType(reskia_color_info_t *color_info, reskia_alpha_type_t newAlphaType); // (SkColorInfo *color_info, SkAlphaType newAlphaType) -> sk_color_info_t
sk_color_info_t SkColorInfo_makeColorSpace(reskia_color_info_t *color_info, sk_color_space_t color_space); // (SkColorInfo *color_info, sk_color_space_t color_space) -> sk_color_info_t
sk_color_info_t SkColorInfo_makeColorType(reskia_color_info_t *color_info, reskia_color_info_color_type_t newColorType); // (SkColorInfo *color_info, SkColorType newColorType) -> sk_color_info_t
sk_color_space_t SkColorInfo_refColorSpace(reskia_color_info_t *color_info); // (SkColorInfo *color_info) -> sk_color_space_t
int SkColorInfo_shiftPerPixel(reskia_color_info_t *color_info); // (SkColorInfo *color_info) -> int

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_COLOR_INFO_H
