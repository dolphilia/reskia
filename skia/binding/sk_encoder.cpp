//
// Created by dolphilia on 2024/02/01.
//

#include "sk_encoder.h"

#include "include/encode/SkEncoder.h"

extern "C" {

void SkEncoder_delete(void *encoder) {
    delete static_cast<SkEncoder *>(encoder);
}

bool SkEncoder_encodeRows(void *encoder, int numRows) {
    return static_cast<SkEncoder *>(encoder)->encodeRows(numRows);
}

}