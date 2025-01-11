//
// Created by dolphilia on 2024/01/05.
//

#ifndef RAIA_SKIA_STATIC_SK_FILE_STREAM_H
#define RAIA_SKIA_STATIC_SK_FILE_STREAM_H

#include <set>
#include <string>
#include <map>
#include "include/core/SkStream.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_file_stream_t;
void static_sk_file_stream_delete(int key);
SkFILEStream *static_sk_file_stream_get(int key);
#ifdef __cplusplus
}
#endif

int static_sk_file_stream_make(std::unique_ptr<SkFILEStream> value);
void static_sk_file_stream_set(int key, std::unique_ptr<SkFILEStream> value);
std::unique_ptr<SkFILEStream> static_sk_file_stream_move(int key);

#endif //RAIA_SKIA_STATIC_SK_FILE_STREAM_H
