//
// Created by dolphilia on 2024/02/02.
//

#ifndef RAIA_SKIA_SK_ENCODED_ORIGIN_H
#define RAIA_SKIA_SK_ENCODED_ORIGIN_H

#include <stdint.h>
#include "../handles/static_sk_matrix.h"

#ifdef __cplusplus
extern "C" {
#endif

// static
typedef int32_t reskia_encoded_origin_t;

sk_matrix_t SkEncodedOrigin_SkEncodedOriginToMatrix(reskia_encoded_origin_t origin, int w, int h); // origin は SkEncodedOrigin 範囲内。invalid 入力では 0
bool SkEncodedOrigin_SkEncodedOriginSwapsWidthHeight(reskia_encoded_origin_t origin); // origin は SkEncodedOrigin 範囲内。invalid 入力では false

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_ENCODED_ORIGIN_H
