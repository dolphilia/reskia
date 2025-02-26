//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_STATIC_SK_RUNTIME_EFFECT_CHILD_PTR_H
#define RAIA_SKIA_STATIC_SK_RUNTIME_EFFECT_CHILD_PTR_H

#ifdef __cplusplus
extern "C" {
#endif
typedef int const_sk_runtime_effect_child_ptr_t;
void static_const_sk_runtime_effect_child_ptr_delete(int key);
const void * static_const_sk_runtime_effect_child_ptr_get_ptr(int key, int index); // -> const SkRuntimeEffect::ChildPtr *
#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_STATIC_SK_RUNTIME_EFFECT_CHILD_PTR_H
