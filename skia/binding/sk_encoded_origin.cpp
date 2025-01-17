//
// Created by dolphilia on 2024/02/02.
//

#include "sk_encoded_origin.h"

#include "include/codec/SkEncodedOrigin.h"

#include "../static/static_sk_matrix.h"

#include "../static/static_sk_matrix-internal.h"

extern "C" {

// static

sk_matrix_t SkEncodedOrigin_SkEncodedOriginToMatrix(int origin, int w, int h) {
    return static_sk_matrix_make(SkEncodedOriginToMatrix(static_cast<SkEncodedOrigin>(origin), w, h));
}

bool SkEncodedOrigin_SkEncodedOriginSwapsWidthHeight(int origin) {
    return SkEncodedOriginSwapsWidthHeight(static_cast<SkEncodedOrigin>(origin));
}

}
