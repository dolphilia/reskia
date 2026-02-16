//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_DISCRETE_PATH_EFFECT_H
#define RAIA_SKIA_SK_DISCRETE_PATH_EFFECT_H

#include <stdint.h>
#include "../handles/static_sk_path_effect.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_discrete_path_effect_t reskia_discrete_path_effect_t;

void SkDiscretePathEffect_delete(reskia_discrete_path_effect_t *discretePathEffect); // (SkDiscretePathEffect * discretePathEffect)

// static

sk_path_effect_t SkDiscretePathEffect_Make(float segLength, float dev, uint32_t seedAssist); // (SkScalar segLength, SkScalar dev, uint32_t seedAssist) -> sk_path_effect_t
void SkDiscretePathEffect_RegisterFlattenables(); // ()

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_DISCRETE_PATH_EFFECT_H
