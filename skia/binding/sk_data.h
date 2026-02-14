//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_DATA_H
#define RAIA_SKIA_SK_DATA_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_data_t reskia_data_t;
typedef struct reskia_file_t reskia_file_t;
typedef struct reskia_stream_t reskia_stream_t;

void SkData_delete(reskia_data_t *sk_data); // owned: caller が保持する参照を release する (SkData *sk_data)
size_t SkData_size(reskia_data_t *sk_data); // (SkData *sk_data) -> size_t
bool SkData_isEmpty(reskia_data_t *sk_data); // (SkData *sk_data) -> bool
const uint8_t * SkData_data(reskia_data_t *sk_data); // borrowed: 解放不要の借用ポインタ (SkData *sk_data) -> const void *
const uint8_t * SkData_bytes(reskia_data_t *sk_data); // borrowed: 解放不要の借用ポインタ (SkData *sk_data) -> const uint8_t *
uint8_t * SkData_writable_data(reskia_data_t *sk_data); // borrowed: 解放不要の借用ポインタ (SkData *sk_data) -> void *
size_t SkData_copyRange(reskia_data_t *sk_data, size_t offset, size_t length, uint8_t *buffer); // (SkData *sk_data, size_t offset, size_t length, void *buffer) -> size_t
bool SkData_equals(reskia_data_t *sk_data, const reskia_data_t *other); // (SkData *sk_data, const SkData *other) -> bool
bool SkData_unique(reskia_data_t *sk_data); // (SkData *sk_data) -> bool
void SkData_ref(reskia_data_t *sk_data); // retained: 参照カウントを増やす (SkData *sk_data)
void SkData_unref(reskia_data_t *sk_data); // owned: 参照カウントを減らす (SkData *sk_data)
void SkData_deref(reskia_data_t *sk_data); // (SkData *sk_data)
bool SkData_refCntGreaterThan(reskia_data_t *sk_data, int32_t threadIsolatedTestCnt); // (SkData *sk_data, int32_t threadIsolatedTestCnt) -> bool

// static

int SkData_MakeWithCopy(const uint8_t *data, size_t length); // (const void *data, size_t length) -> sk_data_t
int SkData_MakeUninitialized(size_t length); // (size_t length) -> sk_data_t
int SkData_MakeZeroInitialized(size_t length); // (size_t length) -> sk_data_t
int SkData_MakeWithCString(const char cstr[]); // (const char cstr[]) -> sk_data_t
int SkData_MakeWithProc(const uint8_t *ptr, size_t length, void(*proc)(const void *ptr, void *context), void *ctx); // (const void *ptr, size_t length, SkData::ReleaseProc proc, void *ctx) -> sk_data_t
int SkData_MakeWithoutCopy(const uint8_t *data, size_t length); // (const void *data, size_t length) -> sk_data_t
int SkData_MakeFromMalloc(const uint8_t *data, size_t length); // (const void *data, size_t length) -> sk_data_t
int SkData_MakeFromFileName(const char path[]); // (const char path[]) -> sk_data_t
int SkData_MakeFromFILE(reskia_file_t *f); // (FILE *f) -> sk_data_t
int SkData_MakeFromFD(int fd); // (int fd) -> sk_data_t
int SkData_MakeFromStream(reskia_stream_t *stream, size_t size); // (SkStream *stream, size_t size) -> sk_data_t
int SkData_MakeSubset(const reskia_data_t *src, size_t offset, size_t length); // (const SkData *src, size_t offset, size_t length) -> sk_data_t
int SkData_MakeEmpty(); // () -> sk_data_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_DATA_H
