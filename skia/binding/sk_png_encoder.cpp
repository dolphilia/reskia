//
// Created by dolphilia on 2024/02/01.
//

#include "sk_png_encoder.h"

#include "include/encode/SkPngEncoder.h"

#include "../static/static_sk_data.h"
#include "../static/static_sk_encoder.h"

#include "../static/static_sk_encoder-internal.h"
#include "../static/static_sk_data-internal.h"

extern "C" {

bool SkPngEncoder_Encode(void * dst, const void * src, const void * options) {
    return SkPngEncoder::Encode(static_cast<SkWStream *>(dst), * static_cast<const SkPixmap *>(src), * static_cast<const SkPngEncoder::Options *>(options));
}

sk_data_t SkPngEncoder_Encode_2(void * ctx, const void * img, const void * options) {
    return static_sk_data_make(SkPngEncoder::Encode(static_cast<GrDirectContext *>(ctx), static_cast<const SkImage *>(img), * static_cast<const SkPngEncoder::Options *>(options)));
}

sk_encoder_t SkPngEncoder_Make(void * dst, const void * src, const void * options) {
    return static_sk_encoder_make(SkPngEncoder::Make(static_cast<SkWStream *>(dst), * static_cast<const SkPixmap *>(src), * static_cast<const SkPngEncoder::Options *>(options)));
}

}
