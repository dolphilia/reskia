//
// Created by dolphilia on 25/01/30.
//

#include "sk_color_4f.h"

#include "include/core/SkColor.h"

#include "../static/static_sk_color_4f.h"

#include "../static/static_sk_color_4f-internal.h"

extern "C" {

void SkColor4f_delete(void *color) {
    delete static_cast<SkColor4f *>(color);
}

// Public Attributes

float SkColor4f_fR(void *color) {
    return static_cast<SkColor4f *>(color)->fR;
}

float SkColor4f_fG(void *color) {
    return static_cast<SkColor4f *>(color)->fG;
}

float SkColor4f_fB(void *color) {
    return static_cast<SkColor4f *>(color)->fB;
}

float SkColor4f_fA(void *color) {
    return static_cast<SkColor4f *>(color)->fA;
}

// Public Member Functions

//bool 	operator== (const SkRGBA4f &other);
//bool 	operator!= (const SkRGBA4f &other);
//SkRGBA4f 	operator* (float scale);
//SkRGBA4f 	operator* (const SkRGBA4f &scale);
//float 	operator[] (SkColor4f *color, int index);
//float & 	operator[] (SkColor4f *color, int index);

const float * SkColor4f_vec(void *color) {
    return static_cast<SkColor4f *>(color)->vec();
}

float * SkColor4f_vec_2(void *color) {
    return static_cast<SkColor4f *>(color)->vec();
}

// TODO
// std::array< float, 4 > SkColor4f_array (void *color) {
//     return static_cast<SkColor4f *>(color)->array();
// }

bool SkColor4f_isOpaque (void *color) {
    return static_cast<SkColor4f *>(color)->isOpaque();
}

bool SkColor4f_fitsInBytes (void *color) {
    return static_cast<SkColor4f *>(color)->fitsInBytes();
}

unsigned int SkColor4f_toSkColor (void *color) {
    return static_cast<SkColor4f *>(color)->toSkColor();
}

// TODO
//SkRGBA4f< kPremul_SkAlphaType > premul (SkColor4f *color);
//SkRGBA4f< kUnpremul_SkAlphaType > unpremul (SkColor4f *color);

unsigned int SkColor4f_toBytes_RGBA (void *color) {
    return static_cast<SkColor4f *>(color)->toBytes_RGBA();
}

int SkColor4f_makeOpaque(void *color) {
    return static_sk_color_4f_make(static_cast<SkColor4f *>(color)->makeOpaque());
}

// static

static int SkColor4f_FromColor (unsigned int color) {
    return static_sk_color_4f_make(SkColor4f::FromColor(color));
}

static int SkColor4f_FromPMColor (unsigned int color) {
    return static_sk_color_4f_make(SkColor4f::FromPMColor(color));
}

static int SkColor4f_FromBytes_RGBA (unsigned int color) {
    return static_sk_color_4f_make(SkColor4f::FromBytes_RGBA(color));
}

}