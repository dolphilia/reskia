//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_EXECUTOR_H
#define RAIA_SKIA_SK_EXECUTOR_H

#include "reskia_status.h"
#include "../handles/static_sk_executor.h"
#include "../handles/static_std_function_void_void.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_executor_t reskia_executor_t;

void SkExecutor_delete(reskia_executor_t *executor); // (SkExecutor *executor)
reskia_status_t SkExecutor_add(reskia_executor_t *executor, function_void_void_t function_key); // executor must be non-NULL, and function_key must be valid.
reskia_status_t SkExecutor_addToWorkList(reskia_executor_t *executor, function_void_void_t function_key, int work_list); // executor must be non-NULL, and function_key must be valid.
int SkExecutor_discardAllPendingWork(reskia_executor_t *executor); // NULL executor returns 0
void SkExecutor_borrow(reskia_executor_t *executor); // (SkExecutor *executor)

// static

sk_executor_t SkExecutor_MakeFIFOThreadPool(int threads, bool allowBorrowing); // (int threads, bool allowBorrowing) -> sk_executor_t
sk_executor_t SkExecutor_MakeLIFOThreadPool(int threads, bool allowBorrowing); // (int threads, bool allowBorrowing) -> sk_executor_t
sk_executor_t SkExecutor_MakeMultiListFIFOThreadPool(int numWorkLists, int threads, bool allowBorrowing); // invalid args return 0
sk_executor_t SkExecutor_MakeMultiListLIFOThreadPool(int numWorkLists, int threads, bool allowBorrowing); // invalid args return 0
reskia_executor_t *SkExecutor_GetDefault(); // () -> SkExecutor *
void SkExecutor_SetDefault(reskia_executor_t *executor); // (SkExecutor *executor)

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_EXECUTOR_H
