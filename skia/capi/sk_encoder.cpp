//
// Created by dolphilia on 2024/02/01.
//

#include "sk_encoder.h"

#include "include/encode/SkEncoder.h"

namespace {

SkEncoder *as_encoder(reskia_encoder_t *encoder) {
    return reinterpret_cast<SkEncoder *>(encoder);
}

} // namespace

extern "C" {

void SkEncoder_delete(reskia_encoder_t *encoder) {
    delete as_encoder(encoder);
}

bool SkEncoder_encodeRows(reskia_encoder_t *encoder, int numRows) {
    SkEncoder *native = as_encoder(encoder);
    if (native == nullptr || numRows <= 0) {
        return false;
    }
    return native->encodeRows(numRows);
}

}
