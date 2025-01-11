//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_STATIC_SK_RUNTIME_EFFECT_UNIFORM_H
#define RAIA_SKIA_STATIC_SK_RUNTIME_EFFECT_UNIFORM_H

#include <set>
#include <string>
#include <map>
#include "include/effects/SkRuntimeEffect.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int const_sk_runtime_effect_uniform_t;
void static_const_sk_runtime_effect_uniform_delete(int key);
const SkRuntimeEffect::Uniform * static_const_sk_runtime_effect_uniform_get(int key, int index);
#ifdef __cplusplus
}
#endif

// const
int static_const_sk_runtime_effect_uniform_make(SkSpan<const SkRuntimeEffect::Uniform> value);
SkSpan<const SkRuntimeEffect::Uniform> static_const_sk_runtime_effect_uniform_get(int key);
void static_const_sk_runtime_effect_uniform_set(int key, SkSpan<const SkRuntimeEffect::Uniform> value);

#endif //RAIA_SKIA_STATIC_SK_RUNTIME_EFFECT_UNIFORM_H
