//
// Created by dolphilia on 2024/02/02.
//

#ifndef RAIA_SKIA_SK_ENCODED_ORIGIN_H
#define RAIA_SKIA_SK_ENCODED_ORIGIN_H

#include "include/codec/SkEncodedOrigin.h"
#include "../static/static_sk_matrix.h"
#include "export_api.h"

extern "C" {
// static
RAIA_API sk_matrix_t SkEncodedOrigin_SkEncodedOriginToMatrix(SkEncodedOrigin origin, int w, int h);
RAIA_API bool SkEncodedOrigin_SkEncodedOriginSwapsWidthHeight(SkEncodedOrigin origin);
}

#endif //RAIA_SKIA_SK_ENCODED_ORIGIN_H
