//
// Created by dolphilia on 2024/02/02.
//

#include "sk_encoded_origin.h"

#include "include/codec/SkEncodedOrigin.h"

#include "../handles/static_sk_matrix.h"

#include "../handles/static_sk_matrix-internal.h"

namespace {

bool is_valid_encoded_origin(reskia_encoded_origin_t origin) {
    return origin >= kTopLeft_SkEncodedOrigin && origin <= kLast_SkEncodedOrigin;
}

}  // namespace

extern "C" {

// static

sk_matrix_t SkEncodedOrigin_SkEncodedOriginToMatrix(reskia_encoded_origin_t origin, int w, int h) {
    if (!is_valid_encoded_origin(origin)) {
        return 0;
    }
    return static_sk_matrix_make(SkEncodedOriginToMatrix(static_cast<SkEncodedOrigin>(origin), w, h));
}

bool SkEncodedOrigin_SkEncodedOriginSwapsWidthHeight(reskia_encoded_origin_t origin) {
    if (!is_valid_encoded_origin(origin)) {
        return false;
    }
    return SkEncodedOriginSwapsWidthHeight(static_cast<SkEncodedOrigin>(origin));
}

}
