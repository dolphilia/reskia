//
// Created by dolphilia on 2024/01/08.
//

#include "sk_executor.h"

#include <functional>
#include <utility>

#include "include/core/SkExecutor.h"

#include "../handles/static_sk_executor.h"

#include "../handles/static_std_function_void_void-internal.h"
#include "../handles/static_sk_executor-internal.h"
#include "../handles/static_std_function_void_void.h"

extern "C" {

void SkExecutor_delete(reskia_executor_t *executor) {
    delete reinterpret_cast<SkExecutor *>(executor);
}

reskia_status_t SkExecutor_add(reskia_executor_t *executor, function_void_void_t function_key) {
    if (executor == nullptr) {
        return RESKIA_STATUS_INVALID_ARGUMENT;
    }
    std::function<void(void)> task = static_function_void_void_get_entity(function_key);
    if (!task) {
        return RESKIA_STATUS_NOT_FOUND;
    }
    reinterpret_cast<SkExecutor *>(executor)->add(std::move(task));
    return RESKIA_STATUS_OK;
}

void SkExecutor_borrow(reskia_executor_t *executor) {
    reinterpret_cast<SkExecutor *>(executor)->borrow();
}

// static

sk_executor_t SkExecutor_MakeFIFOThreadPool(int threads, bool allowBorrowing) {
    return static_sk_executor_make(SkExecutor::MakeFIFOThreadPool(threads, allowBorrowing));
}

sk_executor_t SkExecutor_MakeLIFOThreadPool(int threads, bool allowBorrowing) {
    return static_sk_executor_make(SkExecutor::MakeLIFOThreadPool(threads, allowBorrowing));
}

reskia_executor_t *SkExecutor_GetDefault() {
    return reinterpret_cast<reskia_executor_t *>(&SkExecutor::GetDefault());
}

void SkExecutor_SetDefault(reskia_executor_t *executor) {
    SkExecutor::SetDefault(reinterpret_cast<SkExecutor *>(executor));
}

}
