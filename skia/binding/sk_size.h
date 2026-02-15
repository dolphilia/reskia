//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_SIZE_H
#define RAIA_SKIA_SK_SIZE_H

#include "../static/static_sk_i_size.h"
#include "../static/static_sk_size_t.h"

typedef struct reskia_i_size_t reskia_i_size_t;
typedef struct reskia_size_t reskia_size_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkSize_delete(reskia_size_t *size); // (SkSize *size)
void SkSize_set(reskia_size_t *size, float w, float h); // (SkSize *size, SkScalar w, SkScalar h)
bool SkSize_isZero(reskia_size_t *size); // (SkSize *size) -> bool
bool SkSize_isEmpty(reskia_size_t *size); // (SkSize *size) -> bool
void SkSize_setEmpty(reskia_size_t *size); // (SkSize *size)
float SkSize_width(reskia_size_t *size); // (SkSize *size) -> SkScalar
float SkSize_height(reskia_size_t *size); // (SkSize *size) -> SkScalar
bool SkSize_equals(reskia_size_t *size, float w, float h); // (SkSize *size, SkScalar w, SkScalar h) -> bool
sk_i_size_t SkSize_toRound(reskia_size_t *size); // (SkSize *size) -> sk_i_size_t
sk_i_size_t SkSize_toCeil(reskia_size_t *size); // (SkSize *size) -> sk_i_size_t
sk_i_size_t SkSize_toFloor(reskia_size_t *size); // (SkSize *size) -> sk_i_size_t

// static

sk_size_t SkSize_Make(float w, float h); // (SkScalar w, SkScalar h) -> sk_size_t
sk_size_t SkSize_Make_2(const reskia_i_size_t *src); // (const SkISize *src) -> sk_size_t
sk_size_t SkSize_MakeEmpty(); // () -> sk_size_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_SIZE_H
