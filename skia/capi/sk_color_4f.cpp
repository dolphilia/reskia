//
// Created by dolphilia on 25/01/30.
//

#include "sk_color_4f.h"

#include "include/core/SkColor.h"
#include "include/core/SkUnPreMultiply.h"

#include "../handles/static_sk_color_4f.h"

#include "../handles/static_sk_color_4f-internal.h"

extern "C" {

void SkColor4f_delete(reskia_color_4f_t *color) {
    delete reinterpret_cast<SkColor4f *>(color);
}

// Public Attributes

float SkColor4f_fR(reskia_color_4f_t *color) {
    return reinterpret_cast<SkColor4f *>(color)->fR;
}

float SkColor4f_fG(reskia_color_4f_t *color) {
    return reinterpret_cast<SkColor4f *>(color)->fG;
}

float SkColor4f_fB(reskia_color_4f_t *color) {
    return reinterpret_cast<SkColor4f *>(color)->fB;
}

float SkColor4f_fA(reskia_color_4f_t *color) {
    return reinterpret_cast<SkColor4f *>(color)->fA;
}

// Public Member Functions

//bool 	operator== (const SkRGBA4f &other);
//bool 	operator!= (const SkRGBA4f &other);
//SkRGBA4f 	operator* (float scale);
//SkRGBA4f 	operator* (const SkRGBA4f &scale);
//float 	operator[] (SkColor4f *color, int index);
//float & 	operator[] (SkColor4f *color, int index);

const float *SkColor4f_vec(reskia_color_4f_t *color) {
    return reinterpret_cast<SkColor4f *>(color)->vec();
}

float *SkColor4f_vecMutable(reskia_color_4f_t *color) {
    return reinterpret_cast<SkColor4f *>(color)->vec();
}

// TODO
// std::array< float, 4 > SkColor4f_array (void *color) {
//     return static_cast<SkColor4f *>(color)->array();
// }

bool SkColor4f_isOpaque(reskia_color_4f_t *color) {
    return reinterpret_cast<SkColor4f *>(color)->isOpaque();
}

bool SkColor4f_fitsInBytes(reskia_color_4f_t *color) {
    return reinterpret_cast<SkColor4f *>(color)->fitsInBytes();
}

reskia_color_t SkColor4f_toSkColor(reskia_color_4f_t *color) {
    return static_cast<reskia_color_t>(reinterpret_cast<SkColor4f *>(color)->toSkColor());
}

// TODO
//SkRGBA4f< kPremul_SkAlphaType > premul (SkColor4f *color);
//SkRGBA4f< kUnpremul_SkAlphaType > unpremul (SkColor4f *color);

reskia_u32_t SkColor4f_toBytes_RGBA(reskia_color_4f_t *color) {
    return static_cast<reskia_u32_t>(reinterpret_cast<SkColor4f *>(color)->toBytes_RGBA());
}

sk_color_4f_t SkColor4f_makeOpaque(reskia_color_4f_t *color) {
    return static_sk_color_4f_make(reinterpret_cast<SkColor4f *>(color)->makeOpaque());
}

// static

int SkColor4f_FromColor(reskia_color_t color) {
    return static_sk_color_4f_make(SkColor4f::FromColor(static_cast<SkColor>(color)));
}

int SkColor4f_FromPMColor(reskia_pmcolor_t color) {
    return static_sk_color_4f_make(SkColor4f::FromColor(SkUnPreMultiply::PMColorToColor(static_cast<SkPMColor>(color))));
}

int SkColor4f_FromBytes_RGBA(reskia_u32_t color) {
    return static_sk_color_4f_make(SkColor4f::FromBytes_RGBA(color));
}

}
