//
// Created by dolphilia on 2024/02/02.
//

#ifndef RAIA_SKIA_STATIC_SK_CODECS_DECODER_H
#define RAIA_SKIA_STATIC_SK_CODECS_DECODER_H

#include <set>
#include <map>
#include "include/codec/SkCodec.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_codecs_decoder_t;
void static_sk_codecs_decoder_delete(int key);
SkCodecs::Decoder * static_sk_codecs_decoder_get_ptr(int key);
#ifdef __cplusplus
}
#endif

int static_sk_codecs_decoder_make(SkCodecs::Decoder value);
SkCodecs::Decoder static_sk_codecs_decoder_get(int key);
void static_sk_codecs_decoder_set(int key, SkCodecs::Decoder value);

#endif //RAIA_SKIA_STATIC_SK_CODECS_DECODER_H
