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

void SkUnPreMultiply_delete(reskia_un_pre_multiply_t *unPreMultiply); // No-op for non-owned static helper pointers.

// static

const reskia_un_pre_multiply_scale_t *SkUnPreMultiply_GetScaleTable(); // Returns a borrowed static 256-entry scale table.
reskia_un_pre_multiply_scale_t SkUnPreMultiply_GetScale(uint32_t alpha); // alpha must be <= 255; invalid alpha returns 0.
uint32_t SkUnPreMultiply_ApplyScale(reskia_un_pre_multiply_scale_t scale, uint32_t component); // component must be <= 255; invalid component returns 0.
reskia_color_t SkUnPreMultiply_PMColorToColor(reskia_pmcolor_t c); // Converts a packed premultiplied color value.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_UN_PRE_MULTIPLY_H
