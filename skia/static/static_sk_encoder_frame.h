//
// Created by dolphilia on 2024/02/01.
//

#ifndef RAIA_SKIA_STATIC_SK_ENCODER_FRAME_H
#define RAIA_SKIA_STATIC_SK_ENCODER_FRAME_H

#include <set>
#include <string>
#include <map>
#include "include/private/base/SkSpan_impl.h"
#include "include/encode/SkEncoder.h"
#include "export_api.h"

typedef int const_sk_encoder_frame_t;

extern "C" {
RAIA_API void static_const_sk_encoder_frame_delete(int key);
RAIA_API const SkEncoder::Frame * static_const_sk_encoder_frame_get_ptr(int key, int index);
}

int static_const_sk_encoder_frame_make(SkSpan<const SkEncoder::Frame> value);
SkSpan<const SkEncoder::Frame> static_const_sk_encoder_frame_get(int key);
void static_const_encoder_frame_set(int key, SkSpan<const SkEncoder::Frame> value);

#endif //RAIA_SKIA_STATIC_SK_ENCODER_FRAME_H
