//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_EXECUTOR_H
#define RAIA_SKIA_SK_EXECUTOR_H

#include "../static/static_sk_executor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_executor_t reskia_executor_t;

void SkExecutor_delete(reskia_executor_t *executor); // (SkExecutor *executor)
void SkExecutor_add(int function_void_void_key_in, reskia_executor_t *executor); // (int function_void_void_key_in, SkExecutor *executor)
void SkExecutor_borrow(reskia_executor_t *executor); // (SkExecutor *executor)

// static

sk_executor_t SkExecutor_MakeFIFOThreadPool(int threads, bool allowBorrowing); // (int threads, bool allowBorrowing) -> sk_executor_t
sk_executor_t SkExecutor_MakeLIFOThreadPool(int threads, bool allowBorrowing); // (int threads, bool allowBorrowing) -> sk_executor_t
reskia_executor_t *SkExecutor_GetDefault(); // () -> SkExecutor *
void SkExecutor_SetDefault(reskia_executor_t *executor); // (SkExecutor *executor)

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_EXECUTOR_H
