//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_DASH_PATH_EFFECT_H
#define RAIA_SKIA_SK_DASH_PATH_EFFECT_H

#include "../handles/static_sk_path_effect.h"

#ifdef __cplusplus
extern "C" {
#endif

void SkDashPathEffect_delete(void * dashPathEffect); // owned: No-op for NULL input. (SkDashPathEffect * dashPathEffect)

// static

/**
 * raw input array: intervals must contain at least count elements and be non-NULL.
 * Returns 0 on failure. (const SkScalar intervals[], int count, SkScalar phase) -> sk_path_effect_t
 */
sk_path_effect_t SkDashPathEffect_Make(const float * intervals, int count, float phase);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_DASH_PATH_EFFECT_H
