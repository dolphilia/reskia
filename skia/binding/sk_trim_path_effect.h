//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_TRIM_PATH_EFFECT_H
#define RAIA_SKIA_SK_TRIM_PATH_EFFECT_H

#include "../static/static_sk_path_effect.h"

#ifdef __cplusplus
extern "C" {
#endif

void SkTrimPathEffect_delete(void * trimPathEffect); // (SkTrimPathEffect * trimPathEffect)

// static

sk_path_effect_t SkTrimPathEffect_Make(float startT, float stopT, int mode); // (SkScalar startT, SkScalar stopT, SkTrimPathEffect::Mode mode) -> sk_path_effect_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_TRIM_PATH_EFFECT_H
