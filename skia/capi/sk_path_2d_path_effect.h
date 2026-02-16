//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_PATH_2D_PATH_EFFECT_H
#define RAIA_SKIA_SK_PATH_2D_PATH_EFFECT_H

typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_path_t reskia_path_t;
typedef struct reskia_path_2d_path_effect_t reskia_path_2d_path_effect_t;

#include "../handles/static_sk_path_effect.h"

#ifdef __cplusplus
extern "C" {
#endif

void SkPath2DPathEffect_delete(reskia_path_2d_path_effect_t *path2DPathEffect); // (SkPath2DPathEffect *path2DPathEffect)

// static

sk_path_effect_t SkPath2DPathEffect_Make(const reskia_matrix_t *matrix, const reskia_path_t *path); // (const SkMatrix *matrix, const SkPath *path) -> sk_path_effect_t
void SkPath2DPathEffect_RegisterFlattenables(); // ()

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PATH_2D_PATH_EFFECT_H
