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

reskia_cubic_map_t *SkCubicMap_new(sk_point_t p1, sk_point_t p2); // p1 and p2 must be valid sk_point_t handles. Returns NULL for invalid input.
void SkCubicMap_delete(reskia_cubic_map_t *cubic_map); // No-op for NULL input.
float SkCubicMap_computeYFromX(reskia_cubic_map_t *cubic_map, float x); // Returns 0 for NULL input.
sk_point_t SkCubicMap_computeFromT(reskia_cubic_map_t *cubic_map, float t); // Returns 0 for NULL input.

// static

bool SkCubicMap_IsLinear(sk_point_t p1, sk_point_t p2); // p1 and p2 must be valid sk_point_t handles. Returns false for invalid input.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_CUBIC_MAP_H
