//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_DASH_PATH_EFFECT_H
#define RAIA_SKIA_SK_DASH_PATH_EFFECT_H

#include "../handles/static_sk_path_effect.h"

#ifdef __cplusplus
extern "C" {
#endif

void SkDashPathEffect_delete(void * dashPathEffect); // (SkDashPathEffect * dashPathEffect)

// static

sk_path_effect_t SkDashPathEffect_Make(const float * intervals, int count, float phase); // (const SkScalar intervals[], int count, SkScalar phase) -> sk_path_effect_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_DASH_PATH_EFFECT_H
