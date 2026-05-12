//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_PATH_1D_PATH_EFFECT_H
#define RAIA_SKIA_SK_PATH_1D_PATH_EFFECT_H

#include <stdint.h>

typedef struct reskia_path_1d_path_effect_t reskia_path_1d_path_effect_t;
typedef struct reskia_path_t reskia_path_t;
typedef int32_t reskia_path_1d_path_effect_style_t;

#include "../handles/static_sk_path_effect.h"

#ifdef __cplusplus
extern "C" {
#endif

void SkPath1DPathEffect_delete(reskia_path_1d_path_effect_t *path1DPathEffect); // (SkPath1DPathEffect *path1DPathEffect)

// static

/**
 * path は非 NULL。生成不能なら 0 (const SkPath *path, SkScalar advance, SkScalar phase, SkPath1DPathEffect::Style style) -> sk_path_effect_t
 */
sk_path_effect_t SkPath1DPathEffect_Make(const reskia_path_t *path, float advance, float phase, reskia_path_1d_path_effect_style_t style);
void SkPath1DPathEffect_RegisterFlattenables(); // ()

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PATH_1D_PATH_EFFECT_H
