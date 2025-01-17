//
// Created by dolphilia on 2024/01/08.
//

#include "sk_color_priv.h"

#include "include/core/SkColorPriv.h"

extern "C" {

// static

unsigned SkColorPriv_SkAlpha255To256(unsigned int alpha) {
    return SkAlpha255To256(alpha);
}

uint32_t SkColorPriv_SkAlphaMulQ(uint32_t c, unsigned scale) {
    return SkAlphaMulQ(c, scale);
}

unsigned int SkColorPriv_SkPackARGB32(unsigned int a, unsigned int r, unsigned int g, unsigned int b) {
    return SkPackARGB32(a, r, g, b);
}

unsigned int SkColorPriv_SkPackARGB32NoCheck(unsigned int a, unsigned int r, unsigned int g, unsigned int b) {
    return SkPackARGB32NoCheck(a, r, g, b);
}

unsigned int SkColorPriv_SkPMSrcOver(unsigned int src, unsigned int dst) {
    return SkPMSrcOver(src, dst);
}

unsigned int SkColorPriv_SkPremultiplyARGBInline(unsigned int a, unsigned int r, unsigned int g, unsigned int b) {
    return SkPremultiplyARGBInline(a, r, g, b);
}

unsigned int SkColorPriv_SkUnitScalarClampToByte(float x) {
    return SkUnitScalarClampToByte(x);
}

}