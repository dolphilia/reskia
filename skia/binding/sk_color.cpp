//
// Created by dolphilia on 2024/01/08.
//

#include "sk_color.h"

#include "include/core/SkColor.h"

extern "C" {

// SK_API

reskia_color_t SkColor_SkColorSetA(reskia_color_t c, reskia_u32_t a) {
    return static_cast<reskia_color_t>(SkColorSetA(static_cast<SkColor>(c), static_cast<U8CPU>(a)));
}

reskia_color_t SkColor_SkColorSetARGB(reskia_u32_t a, reskia_u32_t r, reskia_u32_t g, reskia_u32_t b) {
    return static_cast<reskia_color_t>(SkColorSetARGB(static_cast<U8CPU>(a), static_cast<U8CPU>(r), static_cast<U8CPU>(g), static_cast<U8CPU>(b)));
}

void SkColor_SkColorToHSV(reskia_color_t color, float hsv[3]) {
    SkColorToHSV(static_cast<SkColor>(color), hsv);
}

reskia_color_t SkColor_SkHSVToColor(const float hsv[3]) {
    return static_cast<reskia_color_t>(SkHSVToColor(hsv));
}

reskia_color_t SkColor_SkHSVToColor_2(reskia_u32_t alpha, const float hsv[3]) {
    return static_cast<reskia_color_t>(SkHSVToColor(static_cast<U8CPU>(alpha), hsv));
}

reskia_pmcolor_t SkColor_SkPreMultiplyARGB(reskia_u32_t a, reskia_u32_t r, reskia_u32_t g, reskia_u32_t b) {
    return static_cast<reskia_pmcolor_t>(SkPreMultiplyARGB(static_cast<U8CPU>(a), static_cast<U8CPU>(r), static_cast<U8CPU>(g), static_cast<U8CPU>(b)));
}

reskia_pmcolor_t SkColor_SkPreMultiplyColor(reskia_color_t c) {
    return static_cast<reskia_pmcolor_t>(SkPreMultiplyColor(static_cast<SkColor>(c)));
}

void SkColor_SkRGBToHSV(reskia_u32_t red, reskia_u32_t green, reskia_u32_t blue, float hsv[3]) {
    SkRGBToHSV(static_cast<U8CPU>(red), static_cast<U8CPU>(green), static_cast<U8CPU>(blue), hsv);
}

}
