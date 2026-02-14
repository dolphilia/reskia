//
// Created by dolphilia on 2024/01/08.
//

#include "sk_cubic_map.h"

#include "include/core/SkCubicMap.h"

#include "../static/static_sk_point.h"

#include "../static/static_sk_point-internal.h"

extern "C" {

reskia_cubic_map_t *SkCubicMap_new(sk_point_t p1, sk_point_t p2) {
    return reinterpret_cast<reskia_cubic_map_t *>(new SkCubicMap(static_sk_point_get_entity(p1), static_sk_point_get_entity(p2)));
}

void SkCubicMap_delete(reskia_cubic_map_t *cubic_map) {
    delete reinterpret_cast<SkCubicMap *>(cubic_map);
}

float SkCubicMap_computeYFromX(reskia_cubic_map_t *cubic_map, float x) {
    return reinterpret_cast<SkCubicMap *>(cubic_map)->computeYFromX(x);
}

sk_point_t SkCubicMap_computeFromT(reskia_cubic_map_t *cubic_map, float t) {
    return static_sk_point_make(reinterpret_cast<SkCubicMap *>(cubic_map)->computeFromT(t));
}

// static

bool SkCubicMap_IsLinear(sk_point_t p1, sk_point_t p2) {
    return SkCubicMap::IsLinear(static_sk_point_get_entity(p1), static_sk_point_get_entity(p2));
}

}
