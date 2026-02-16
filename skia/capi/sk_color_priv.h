//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_COLOR_PRIV_H
#define RAIA_SKIA_SK_COLOR_PRIV_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t reskia_u32_t;
typedef uint32_t reskia_pmcolor_t;

// static
reskia_u32_t SkColorPriv_SkAlpha255To256(reskia_u32_t alpha); // (U8CPU alpha) -> unsigned
reskia_u32_t SkColorPriv_SkAlphaMulQ(reskia_u32_t c, reskia_u32_t scale); // (uint32_t c, unsigned scale) -> uint32_t
reskia_pmcolor_t SkColorPriv_SkPackARGB32(reskia_u32_t a, reskia_u32_t r, reskia_u32_t g, reskia_u32_t b); // (U8CPU a, U8CPU r, U8CPU g, U8CPU b) -> SkPMColor
reskia_pmcolor_t SkColorPriv_SkPackARGB32NoCheck(reskia_u32_t a, reskia_u32_t r, reskia_u32_t g, reskia_u32_t b); // (U8CPU a, U8CPU r, U8CPU g, U8CPU b) -> SkPMColor
reskia_pmcolor_t SkColorPriv_SkPMSrcOver(reskia_pmcolor_t src, reskia_pmcolor_t dst); // (SkPMColor src, SkPMColor dst) -> SkPMColor
reskia_pmcolor_t SkColorPriv_SkPremultiplyARGBInline(reskia_u32_t a, reskia_u32_t r, reskia_u32_t g, reskia_u32_t b); // (U8CPU a, U8CPU r, U8CPU g, U8CPU b) -> SkPMColor
reskia_u32_t SkColorPriv_SkUnitScalarClampToByte(float x); // (SkScalar x) -> U8CPU

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_COLOR_PRIV_H
