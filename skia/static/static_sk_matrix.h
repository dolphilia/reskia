//
// Created by dolphilia on 2024/01/06.
//

#ifndef RAIA_SKIA_STATIC_SK_MATRIX_H
#define RAIA_SKIA_STATIC_SK_MATRIX_H

#include <set>
#include <map>
#include "include/core/SkMatrix.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_matrix_t;
void static_sk_matrix_delete(int key);
void * static_sk_matrix_get_ptr(int key); // -> SkMatrix *
#ifdef __cplusplus
}
#endif

int static_sk_matrix_make(SkMatrix value);
SkMatrix static_sk_matrix_get(int key);
void static_sk_matrix_set(int key, SkMatrix value);

#endif //RAIA_SKIA_STATIC_SK_MATRIX_H
