#ifndef STATIC_SK_FILE_STREAM_INTERNAL_H
#define STATIC_SK_FILE_STREAM_INTERNAL_H
#include <set>
#include <map>
#include "include/core/SkStream.h"
int static_sk_file_stream_make(std::unique_ptr<SkFILEStream> value);
void static_sk_file_stream_set(int key, std::unique_ptr<SkFILEStream> value);
SkFILEStream* static_sk_file_stream_borrow_entity(int key);
std::unique_ptr<SkFILEStream> static_sk_file_stream_take_entity(int key);
std::unique_ptr<SkFILEStream> static_sk_file_stream_get_entity(int key);
#endif // STATIC_SK_FILE_STREAM_INTERNAL_H
