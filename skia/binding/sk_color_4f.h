//
// Created by dolphilia on 25/01/30.
//

#ifndef SK_COLOR4F_H
#define SK_COLOR4F_H

#include <stdint.h>
#include "../static/static_sk_color_4f.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_color_4f_t reskia_color_4f_t;
typedef uint32_t reskia_u32_t;
typedef uint32_t reskia_color_t;
typedef uint32_t reskia_pmcolor_t;

void SkColor4f_delete(reskia_color_4f_t *color);

// Public Attributes

float SkColor4f_fR(reskia_color_4f_t *color); // (SkColor4f *color) -> float
float SkColor4f_fG(reskia_color_4f_t *color); // (SkColor4f *color) -> float
float SkColor4f_fB(reskia_color_4f_t *color); // (SkColor4f *color) -> float
float SkColor4f_fA(reskia_color_4f_t *color); // (SkColor4f *color) -> float

// Public Member Functions

//bool operator== (const SkRGBA4f &other);
//bool operator!= (const SkRGBA4f &other);
//SkRGBA4f operator* (float scale);
//SkRGBA4f operator* (const SkRGBA4f &scale);
//float operator[] (SkColor4f *color, int index);
//float & operator[] (SkColor4f *color, int index);

const float * SkColor4f_vec(reskia_color_4f_t *color); // (SkColor4f *color) -> const float *
float * SkColor4f_vec_2(reskia_color_4f_t *color); // (SkColor4f *color) -> float *

// TODO
// std::array< float, 4 > SkColor4f_array (void *color);

bool SkColor4f_isOpaque(reskia_color_4f_t *color); // (SkColor4f *color) -> bool
bool SkColor4f_fitsInBytes(reskia_color_4f_t *color); // (SkColor4f *color) -> bool
reskia_color_t SkColor4f_toSkColor(reskia_color_4f_t *color); // (SkColor4f *color) -> SkColor

// TODO
//SkRGBA4f< kPremul_SkAlphaType > premul (SkColor4f *color);
//SkRGBA4f< kUnpremul_SkAlphaType > unpremul (SkColor4f *color);

reskia_u32_t SkColor4f_toBytes_RGBA(reskia_color_4f_t *color); // (SkColor4f *color) -> uint32_t
sk_color_4f_t SkColor4f_makeOpaque(reskia_color_4f_t *color); //  (SkColor4f *color) -> SkColor4f

// static

int SkColor4f_FromColor(reskia_color_t color); // (SkColor color) -> SkColor4f
int SkColor4f_FromPMColor(reskia_pmcolor_t color); // (SkPMColor color) -> SkColor4f
int SkColor4f_FromBytes_RGBA(reskia_u32_t color); // (uint32_t color) -> SkColor4f

#ifdef __cplusplus
}
#endif

#endif //SK_COLOR4F_H
