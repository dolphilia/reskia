//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_CORNER_PATH_EFFECT_H
#define RAIA_SKIA_SK_CORNER_PATH_EFFECT_H

#include "../handles/static_sk_path_effect.h"

#ifdef __cplusplus
extern "C" {
#endif

void SkCornerPathEffect_delete(void * cornerPathEffect); // owned: No-op for NULL input. (SkCornerPathEffect * cornerPathEffect)

// static

sk_path_effect_t SkCornerPathEffect_Make(float radius); // Returns 0 on failure. (SkScalar radius) -> sk_path_effect_t
void SkCornerPathEffect_RegisterFlattenables(); // ()

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_CORNER_PATH_EFFECT_H
