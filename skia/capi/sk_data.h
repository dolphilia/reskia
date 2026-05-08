//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_DATA_H
#define RAIA_SKIA_SK_DATA_H

#include <stddef.h>
#include <stdint.h>
#include "../handles/static_sk_data.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_data_t reskia_data_t;
typedef struct reskia_file_t reskia_file_t;
typedef struct reskia_stream_t reskia_stream_t;

void SkData_release(reskia_data_t *sk_data); // owned: caller が保持する参照を release する (SkData *sk_data)
size_t SkData_size(reskia_data_t *sk_data); // (SkData *sk_data) -> size_t
bool SkData_isEmpty(reskia_data_t *sk_data); // (SkData *sk_data) -> bool
const uint8_t * SkData_data(reskia_data_t *sk_data); // borrowed: valid while sk_data remains alive; caller must not free
const uint8_t * SkData_bytes(reskia_data_t *sk_data); // borrowed: valid while sk_data remains alive; caller must not free
uint8_t * SkData_writable_data(reskia_data_t *sk_data); // borrowed mutable pointer; only mutate while SkData is uniquely owned
size_t SkData_copyRange(reskia_data_t *sk_data, size_t offset, size_t length, uint8_t *buffer); // buffer may be null to query clamped copy size
bool SkData_equals(reskia_data_t *sk_data, const reskia_data_t *other); // (SkData *sk_data, const SkData *other) -> bool
bool SkData_unique(reskia_data_t *sk_data); // (SkData *sk_data) -> bool
void SkData_ref(reskia_data_t *sk_data); // retained: 参照カウントを増やす (SkData *sk_data)
void SkData_unref(reskia_data_t *sk_data); // owned: 参照カウントを減らす (SkData *sk_data)
void SkData_deref(reskia_data_t *sk_data); // (SkData *sk_data)
bool SkData_refCntGreaterThan(reskia_data_t *sk_data, int32_t threadIsolatedTestCnt); // (SkData *sk_data, int32_t threadIsolatedTestCnt) -> bool

// static

sk_data_t SkData_MakeWithCopy(const uint8_t *data, size_t length); // data may be null only when length == 0; contents are copied
sk_data_t SkData_MakeUninitialized(size_t length); // (size_t length) -> sk_data_t
sk_data_t SkData_MakeZeroInitialized(size_t length); // (size_t length) -> sk_data_t
sk_data_t SkData_MakeWithCString(const char cstr[]); // cstr may be null; Skia treats it like an empty string
sk_data_t SkData_MakeWithProc(const uint8_t *ptr, size_t length, void(*proc)(const void *ptr, void *context), void *ctx); // ptr may be null only when length == 0; proc may be null
sk_data_t SkData_MakeWithoutCopy(const uint8_t *data, size_t length); // data may be null only when length == 0; caller keeps storage alive
sk_data_t SkData_MakeFromMalloc(const uint8_t *data, size_t length); // data may be null only when length == 0; SkData takes malloc ownership
sk_data_t SkData_MakeFromFileName(const char path[]); // (const char path[]) -> sk_data_t
sk_data_t SkData_MakeFromFILE(reskia_file_t *f); // (FILE *f) -> sk_data_t
sk_data_t SkData_MakeFromFD(int fd); // (int fd) -> sk_data_t
sk_data_t SkData_MakeFromStream(reskia_stream_t *stream, size_t size); // stream may be null only when size == 0
sk_data_t SkData_MakeSubset(const reskia_data_t *src, size_t offset, size_t length); // (const SkData *src, size_t offset, size_t length) -> sk_data_t
sk_data_t SkData_MakeEmpty(); // () -> sk_data_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_DATA_H
