//
// Created by dolphilia on 2024/02/02.
//

#ifndef RAIA_SKIA_SK_ENCODED_ORIGIN_H
#define RAIA_SKIA_SK_ENCODED_ORIGIN_H

#include "../static/static_sk_matrix.h"

#ifdef __cplusplus
extern "C" {
#endif

// static
sk_matrix_t SkEncodedOrigin_SkEncodedOriginToMatrix(int origin, int w, int h); // (SkEncodedOrigin origin, int w, int h) -> sk_matrix_t
bool SkEncodedOrigin_SkEncodedOriginSwapsWidthHeight(int origin); // (SkEncodedOrigin origin) -> bool

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_ENCODED_ORIGIN_H
