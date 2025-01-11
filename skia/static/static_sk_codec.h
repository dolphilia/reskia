//
// Created by dolphilia on 2024/02/02.
//

#ifndef RAIA_SKIA_STATIC_SK_CODEC_H
#define RAIA_SKIA_STATIC_SK_CODEC_H

#include <set>
#include <map>
#include "include/codec/SkCodec.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_codec_t;
void static_sk_codec_delete(int key);
SkCodec *static_sk_codec_get(int key);
#ifdef __cplusplus
}
#endif

int static_sk_codec_make(std::unique_ptr<SkCodec> value);
void static_sk_codec_set(int key, std::unique_ptr<SkCodec> value);
std::unique_ptr<SkCodec> static_sk_codec_move(int key);

#endif //RAIA_SKIA_STATIC_SK_CODEC_H
