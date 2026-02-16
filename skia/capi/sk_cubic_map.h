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

reskia_cubic_map_t *SkCubicMap_new(sk_point_t p1, sk_point_t p2); // (sk_point_t p1, sk_point_t p2) -> SkCubicMap *
void SkCubicMap_delete(reskia_cubic_map_t *cubic_map); // (SkCubicMap * cubic_map)
float SkCubicMap_computeYFromX(reskia_cubic_map_t *cubic_map, float x); // (SkCubicMap * cubic_map, float x) -> float
sk_point_t SkCubicMap_computeFromT(reskia_cubic_map_t *cubic_map, float t); // (SkCubicMap * cubic_map, float t) -> sk_point_t

// static

bool SkCubicMap_IsLinear(sk_point_t p1, sk_point_t p2); // (sk_point_t p1, sk_point_t p2) -> bool

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_CUBIC_MAP_H
