//
// Created by dolphilia on 2024/02/01.
//

#ifndef RAIA_SKIA_STATIC_SK_ENCODER_H
#define RAIA_SKIA_STATIC_SK_ENCODER_H

#include <set>
#include <map>
#include "include/encode/SkEncoder.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_encoder_t;
void static_sk_encoder_delete(int key);
SkEncoder *static_sk_encoder_get(int key);
#ifdef __cplusplus
}
#endif

int static_sk_encoder_make(std::unique_ptr<SkEncoder> value);
void static_sk_encoder_set(int key, std::unique_ptr<SkEncoder> value);
std::unique_ptr<SkEncoder> static_sk_encoder_move(int key);

#endif //RAIA_SKIA_STATIC_SK_ENCODER_H
