//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_I_SIZE_H
#define RAIA_SKIA_SK_I_SIZE_H

#include <stdint.h>
#include "../static/static_sk_i_size.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_i_size_t reskia_i_size_t;

void SkISize_delete(reskia_i_size_t *i_size); // (SkISize *i_size)
void SkISize_set(reskia_i_size_t *i_size, int w, int h); // (SkISize *i_size, int32_t w, int32_t h)
bool SkISize_isZero(reskia_i_size_t *i_size); // (SkISize *i_size) -> bool
bool SkISize_isEmpty(reskia_i_size_t *i_size); // (SkISize *i_size) -> bool
void SkISize_setEmpty(reskia_i_size_t *i_size); // (SkISize *i_size)
int SkISize_width(reskia_i_size_t *i_size); // (SkISize *i_size) -> int32_t
int SkISize_height(reskia_i_size_t *i_size); // (SkISize *i_size) -> int32_t
int64_t SkISize_area(reskia_i_size_t *i_size); // (SkISize *i_size) -> int64_t
bool SkISize_equals(reskia_i_size_t *i_size, int w, int h); // (SkISize *i_size, int32_t w, int32_t h) -> bool

// static

sk_i_size_t SkISize_Make(int w, int h); // (int32_t w, int32_t h) -> sk_i_size_t
sk_i_size_t SkISize_MakeEmpty(); // () -> sk_i_size_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_I_SIZE_H
