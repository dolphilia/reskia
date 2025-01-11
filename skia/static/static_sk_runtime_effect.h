//
// Created by dolphilia on 2024/01/12.
//

#ifndef RAIA_SKIA_STATIC_SK_RUNTIME_EFFECT_H
#define RAIA_SKIA_STATIC_SK_RUNTIME_EFFECT_H

#include <set>
#include <map>
#include "include/effects/SkRuntimeEffect.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_runtime_effect_t;
void static_sk_runtime_effect_delete(int key);
void *static_sk_runtime_effect_get(int key); // -> SkRuntimeEffect *
#ifdef __cplusplus
}
#endif

int static_sk_runtime_effect_make(sk_sp<SkRuntimeEffect> value);
void static_sk_runtime_effect_set(int key, sk_sp<SkRuntimeEffect> value);
sk_sp<SkRuntimeEffect> static_sk_runtime_effect_move(int key);

#endif //RAIA_SKIA_STATIC_SK_RUNTIME_EFFECT_H
