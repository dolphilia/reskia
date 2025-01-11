//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_STATIC_SK_RUNTIME_EFFECT_RESULT_H
#define RAIA_SKIA_STATIC_SK_RUNTIME_EFFECT_RESULT_H

#include <set>
#include <map>
#include <utility>
#include "include/effects/SkRuntimeEffect.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_runtime_effect_result_t;
void static_sk_runtime_effect_result_delete(int key);
SkRuntimeEffect::Result * static_sk_runtime_effect_result_get_ptr(int key);
#ifdef __cplusplus
}
#endif

// const
int static_sk_runtime_effect_result_make(SkRuntimeEffect::Result value);
SkRuntimeEffect::Result static_sk_runtime_effect_result_get(int key);
void static_sk_runtime_effect_result_set(int key, SkRuntimeEffect::Result value);

#endif //RAIA_SKIA_STATIC_SK_RUNTIME_EFFECT_RESULT_H
