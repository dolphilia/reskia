//
// Created by dolphilia on 2024/01/08.
//

#include "sk_color_priv.h"

#include "include/core/SkColorPriv.h"

extern "C" {

// static

reskia_u32_t SkColorPriv_SkAlpha255To256(reskia_u32_t alpha) {
    return static_cast<reskia_u32_t>(SkAlpha255To256(static_cast<U8CPU>(alpha)));
}

reskia_u32_t SkColorPriv_SkAlphaMulQ(reskia_u32_t c, reskia_u32_t scale) {
    return static_cast<reskia_u32_t>(SkAlphaMulQ(c, scale));
}

reskia_pmcolor_t SkColorPriv_SkPackARGB32(reskia_u32_t a, reskia_u32_t r, reskia_u32_t g, reskia_u32_t b) {
    return static_cast<reskia_pmcolor_t>(SkPackARGB32(static_cast<U8CPU>(a), static_cast<U8CPU>(r), static_cast<U8CPU>(g), static_cast<U8CPU>(b)));
}

reskia_pmcolor_t SkColorPriv_SkPackARGB32NoCheck(reskia_u32_t a, reskia_u32_t r, reskia_u32_t g, reskia_u32_t b) {
    return static_cast<reskia_pmcolor_t>(SkPackARGB32NoCheck(static_cast<U8CPU>(a), static_cast<U8CPU>(r), static_cast<U8CPU>(g), static_cast<U8CPU>(b)));
}

reskia_pmcolor_t SkColorPriv_SkPMSrcOver(reskia_pmcolor_t src, reskia_pmcolor_t dst) {
    return static_cast<reskia_pmcolor_t>(SkPMSrcOver(static_cast<SkPMColor>(src), static_cast<SkPMColor>(dst)));
}

reskia_pmcolor_t SkColorPriv_SkPremultiplyARGBInline(reskia_u32_t a, reskia_u32_t r, reskia_u32_t g, reskia_u32_t b) {
    return static_cast<reskia_pmcolor_t>(SkPremultiplyARGBInline(static_cast<U8CPU>(a), static_cast<U8CPU>(r), static_cast<U8CPU>(g), static_cast<U8CPU>(b)));
}

reskia_u32_t SkColorPriv_SkUnitScalarClampToByte(float x) {
    return static_cast<reskia_u32_t>(SkUnitScalarClampToByte(x));
}

}
