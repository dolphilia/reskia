//
// Created by dolphilia on 2024/01/05.
//

#ifndef RAIA_SKIA_STATIC_SK_DATA_H
#define RAIA_SKIA_STATIC_SK_DATA_H

#include <set>
#include <map>
#include "include/core/SkData.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_data_t;
typedef int const_sk_data_t;
void static_sk_data_delete(int key);
void *static_sk_data_get(int key); // -> SkData *
// const
void static_const_sk_data_delete(int key);
const void *static_const_sk_data_get(int key); // -> const SkData *
#ifdef __cplusplus
}
#endif

int static_sk_data_make(sk_sp<SkData> value);
void static_sk_data_set(int key, sk_sp<SkData> value);
sk_sp<SkData> static_sk_data_move(int key);
// const
int static_const_sk_data_make(sk_sp<const SkData> value);
void static_const_sk_data_set(int key, sk_sp<const SkData> value);
sk_sp<const SkData> static_const_sk_data_move(int key);

#endif //RAIA_SKIA_STATIC_SK_DATA_H
