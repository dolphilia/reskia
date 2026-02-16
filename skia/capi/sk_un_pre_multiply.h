//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_UN_PRE_MULTIPLY_H
#define RAIA_SKIA_SK_UN_PRE_MULTIPLY_H

#include <stdint.h>

typedef struct reskia_un_pre_multiply_t reskia_un_pre_multiply_t;
typedef uint32_t reskia_un_pre_multiply_scale_t;
typedef uint32_t reskia_color_t;
typedef uint32_t reskia_pmcolor_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkUnPreMultiply_delete(reskia_un_pre_multiply_t *unPreMultiply); // (SkUnPreMultiply *unPreMultiply)

// static

const reskia_un_pre_multiply_scale_t *SkUnPreMultiply_GetScaleTable(); // () -> const SkUnPreMultiply::Scale *
reskia_un_pre_multiply_scale_t SkUnPreMultiply_GetScale(uint32_t alpha); // (U8CPU alpha) -> SkUnPreMultiply::Scale
uint32_t SkUnPreMultiply_ApplyScale(reskia_un_pre_multiply_scale_t scale, uint32_t component); // (SkUnPreMultiply::Scale scale, U8CPU component) -> U8CPU
reskia_color_t SkUnPreMultiply_PMColorToColor(reskia_pmcolor_t c); // (SkPMColor c) -> SkColor

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_UN_PRE_MULTIPLY_H
