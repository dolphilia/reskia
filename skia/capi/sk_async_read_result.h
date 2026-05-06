//
// Created by Codex on 2026/05/06.
//

#ifndef RAIA_SKIA_SK_ASYNC_READ_RESULT_H
#define RAIA_SKIA_SK_ASYNC_READ_RESULT_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_async_read_result_t reskia_async_read_result_t;
typedef void (*reskia_async_read_pixels_callback_t)(void *context, const reskia_async_read_result_t *result);

int Reskia_AsyncReadResult_count(const reskia_async_read_result_t *result);
const void *Reskia_AsyncReadResult_data(const reskia_async_read_result_t *result, int index);
size_t Reskia_AsyncReadResult_rowBytes(const reskia_async_read_result_t *result, int index);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_ASYNC_READ_RESULT_H
