//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_I_SIZE_H
#define RAIA_SKIA_SK_I_SIZE_H

#include <stdint.h>
#include "../handles/static_sk_i_size.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_i_size_t reskia_i_size_t;

void SkISize_delete(reskia_i_size_t *i_size); // (SkISize *i_size)
void SkISize_set(reskia_i_size_t *i_size, int w, int h); // NULL i_size is no-op.
bool SkISize_isZero(reskia_i_size_t *i_size); // NULL i_size returns true.
bool SkISize_isEmpty(reskia_i_size_t *i_size); // NULL i_size returns true.
void SkISize_setEmpty(reskia_i_size_t *i_size); // NULL i_size is no-op.
int SkISize_width(reskia_i_size_t *i_size); // NULL i_size returns 0.
int SkISize_height(reskia_i_size_t *i_size); // NULL i_size returns 0.
int64_t SkISize_area(reskia_i_size_t *i_size); // NULL i_size returns 0.
bool SkISize_equals(reskia_i_size_t *i_size, int w, int h); // NULL i_size returns false.

// static

sk_i_size_t SkISize_Make(int w, int h); // (int32_t w, int32_t h) -> sk_i_size_t
sk_i_size_t SkISize_MakeEmpty(); // () -> sk_i_size_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_I_SIZE_H
