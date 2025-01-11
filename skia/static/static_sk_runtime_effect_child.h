//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_STATIC_SK_RUNTIME_EFFECT_CHILD_H
#define RAIA_SKIA_STATIC_SK_RUNTIME_EFFECT_CHILD_H

#include <set>
#include <string>
#include <map>
#include "include/effects/SkRuntimeEffect.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int const_sk_runtime_effect_child_t;
void static_const_sk_runtime_effect_child_delete(int key);
const SkRuntimeEffect::Child * static_const_sk_runtime_effect_child_get_ptr(int key, int index);
#ifdef __cplusplus
}
#endif

// const
int static_const_sk_runtime_effect_child_make(SkSpan<const SkRuntimeEffect::Child> value);
SkSpan<const SkRuntimeEffect::Child> static_const_sk_runtime_effect_child_get(int key);
void static_const_sk_runtime_effect_child_set(int key, SkSpan<const SkRuntimeEffect::Child> value);

#endif //RAIA_SKIA_STATIC_SK_RUNTIME_EFFECT_CHILD_H
