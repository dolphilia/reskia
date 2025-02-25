//
// Created by dolphilia on 2024/01/08.
//

#include "sk_cubic_map.h"

#include "include/core/SkCubicMap.h"

#include "../static/static_sk_point.h"

#include "../static/static_sk_point-internal.h"

extern "C" {

void *SkCubicMap_new(sk_point_t p1, sk_point_t p2) {
    return new SkCubicMap(static_sk_point_get_entity(p1), static_sk_point_get_entity(p2));
}

void SkCubicMap_delete(void * cubic_map) {
    delete static_cast<SkCubicMap *>(cubic_map);
}

float SkCubicMap_computeYFromX(void * cubic_map, float x) {
    return static_cast<SkCubicMap *>(cubic_map)->computeYFromX(x);
}

sk_point_t SkCubicMap_computeFromT(void * cubic_map, float t) {
    return static_sk_point_make(static_cast<SkCubicMap *>(cubic_map)->computeFromT(t));
}

// static

bool SkCubicMap_IsLinear(sk_point_t p1, sk_point_t p2) {
    return SkCubicMap::IsLinear(static_sk_point_get_entity(p1), static_sk_point_get_entity(p2));
}

}
