//
// Created by dolphilia on 2024/02/02.
//

#ifndef RAIA_SKIA_SK_ENCODED_ORIGIN_H
#define RAIA_SKIA_SK_ENCODED_ORIGIN_H

#include <stdint.h>
#include "../static/static_sk_matrix.h"

#ifdef __cplusplus
extern "C" {
#endif

// static
typedef int32_t reskia_encoded_origin_t;

sk_matrix_t SkEncodedOrigin_SkEncodedOriginToMatrix(reskia_encoded_origin_t origin, int w, int h); // (SkEncodedOrigin origin, int w, int h) -> sk_matrix_t
bool SkEncodedOrigin_SkEncodedOriginSwapsWidthHeight(reskia_encoded_origin_t origin); // (SkEncodedOrigin origin) -> bool

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_ENCODED_ORIGIN_H
