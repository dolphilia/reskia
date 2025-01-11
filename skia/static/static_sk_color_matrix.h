//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_STATIC_SK_COLOR_MATRIX_H
#define RAIA_SKIA_STATIC_SK_COLOR_MATRIX_H

#include <set>
#include <map>
#include "include/effects/SkColorMatrix.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_color_matrix_t;
void static_sk_color_matrix_delete(int key);
void * static_sk_color_matrix_get_ptr(int key); // -> SkColorMatrix *
#ifdef __cplusplus
}
#endif

int static_sk_color_matrix_make(SkColorMatrix value);
SkColorMatrix static_sk_color_matrix_get(int key);
void static_sk_color_matrix_set(int key, SkColorMatrix value);

#endif //RAIA_SKIA_STATIC_SK_COLOR_MATRIX_H
