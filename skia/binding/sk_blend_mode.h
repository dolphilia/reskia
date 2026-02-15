//
// Created by dolphilia on 2024/01/06.
//

#ifndef RAIA_SKIA_SK_BLEND_MODE_H
#define RAIA_SKIA_SK_BLEND_MODE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t reskia_blend_mode_t;

bool SkBlendMode_SkBlendMode_AsCoeff(reskia_blend_mode_t mode, void * src, void * dst); // (SkBlendMode mode, SkBlendModeCoeff *src, SkBlendModeCoeff *dst) -> bool
const char * SkBlendMode_SkBlendMode_Name(reskia_blend_mode_t blendMode); // (SkBlendMode blendMode) -> const char *

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_BLEND_MODE_H
