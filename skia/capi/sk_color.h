//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_COLOR_H
#define RAIA_SKIA_SK_COLOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t reskia_u32_t;
typedef uint32_t reskia_color_t;
typedef uint32_t reskia_pmcolor_t;

reskia_color_t SkColor_SkColorSetA(reskia_color_t c, reskia_u32_t a); // (SkColor c, U8CPU a) -> SkColor
reskia_color_t SkColor_SkColorSetARGB(reskia_u32_t a, reskia_u32_t r, reskia_u32_t g, reskia_u32_t b); // (U8CPU a, U8CPU r, U8CPU g, U8CPU b) -> SkColor
void SkColor_SkColorToHSV(reskia_color_t color, float hsv[3]); // (SkColor color, SkScalar hsv[3])
reskia_color_t SkColor_SkHSVToColor(const float hsv[3]); // (const SkScalar hsv[3]) -> SkColor
reskia_color_t SkColor_SkHSVToColor_2(reskia_u32_t alpha, const float hsv[3]); // (U8CPU alpha, const SkScalar hsv[3]) -> SkColor
reskia_pmcolor_t SkColor_SkPreMultiplyARGB(reskia_u32_t a, reskia_u32_t r, reskia_u32_t g, reskia_u32_t b); // (U8CPU a, U8CPU r, U8CPU g, U8CPU b) -> SkPMColor
reskia_pmcolor_t SkColor_SkPreMultiplyColor(reskia_color_t c); // (SkColor c) -> SkPMColor
void SkColor_SkRGBToHSV(reskia_u32_t red, reskia_u32_t green, reskia_u32_t blue, float hsv[3]); // (U8CPU red, U8CPU green, U8CPU blue, SkScalar hsv[3])

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_COLOR_H
