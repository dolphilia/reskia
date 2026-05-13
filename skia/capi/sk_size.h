//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_SIZE_H
#define RAIA_SKIA_SK_SIZE_H

#include "../handles/static_sk_i_size.h"
#include "../handles/static_sk_size_t.h"

typedef struct reskia_i_size_t reskia_i_size_t;
typedef struct reskia_size_t reskia_size_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkSize_delete(reskia_size_t *size); // (SkSize *size)
void SkSize_set(reskia_size_t *size, float w, float h); // NULL size is no-op.
bool SkSize_isZero(reskia_size_t *size); // NULL size returns true.
bool SkSize_isEmpty(reskia_size_t *size); // NULL size returns true.
void SkSize_setEmpty(reskia_size_t *size); // NULL size is no-op.
float SkSize_width(reskia_size_t *size); // NULL size returns 0.
float SkSize_height(reskia_size_t *size); // NULL size returns 0.
bool SkSize_equals(reskia_size_t *size, float w, float h); // NULL size returns false.
sk_i_size_t SkSize_toRound(reskia_size_t *size); // NULL size returns 0.
sk_i_size_t SkSize_toCeil(reskia_size_t *size); // NULL size returns 0.
sk_i_size_t SkSize_toFloor(reskia_size_t *size); // NULL size returns 0.

// static

sk_size_t SkSize_Make(float w, float h); // (SkScalar w, SkScalar h) -> sk_size_t
sk_size_t SkSize_MakeFromISize(const reskia_i_size_t *src); // src required; invalid input returns 0.
sk_size_t SkSize_MakeEmpty(); // () -> sk_size_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_SIZE_H
