//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_CUBIC_MAP_H
#define RAIA_SKIA_SK_CUBIC_MAP_H

#include "../handles/static_sk_point.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_cubic_map_t reskia_cubic_map_t;

reskia_cubic_map_t *SkCubicMap_new(sk_point_t p1, sk_point_t p2); // p1/p2 は有効な sk_point_t handle。invalid 入力では NULL
void SkCubicMap_delete(reskia_cubic_map_t *cubic_map); // NULL 入力では no-op
float SkCubicMap_computeYFromX(reskia_cubic_map_t *cubic_map, float x); // NULL 入力では 0
sk_point_t SkCubicMap_computeFromT(reskia_cubic_map_t *cubic_map, float t); // NULL 入力では 0

// static

bool SkCubicMap_IsLinear(sk_point_t p1, sk_point_t p2); // p1/p2 は有効な sk_point_t handle。invalid 入力では false

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_CUBIC_MAP_H
