//
// Created by dolphilia on 24/06/20.
//

#ifndef RESKIA_STATIC_SK_POINT_TWO_H
#define RESKIA_STATIC_SK_POINT_TWO_H

#include <set>
#include <map>
#include "include/core/SkRect.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_point_two_t;
int static_sk_point_two_make_float(float fx1, float fy1, float fx2, float fy2);
void static_sk_point_two_delete(int key);
void * static_sk_point_two_get_ptr(int key); // -> SkPoint *
#ifdef __cplusplus
}
#endif

int static_sk_point_two_make(SkPoint value1, SkPoint value2);
void static_sk_point_two_set(int key, SkPoint value1, SkPoint value2);
//SkPoint static_sk_point_two_get(int key);

#endif //RESKIA_STATIC_SK_POINT_TWO_H
