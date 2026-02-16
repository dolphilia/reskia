//
// Created by dolphilia on 2024/02/01.
//

#include "sk_encoder.h"

#include "include/encode/SkEncoder.h"

extern "C" {

void SkEncoder_delete(reskia_encoder_t *encoder) {
    delete reinterpret_cast<SkEncoder *>(encoder);
}

bool SkEncoder_encodeRows(reskia_encoder_t *encoder, int numRows) {
    return reinterpret_cast<SkEncoder *>(encoder)->encodeRows(numRows);
}

}
