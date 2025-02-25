//
// Created by dolphilia on 2024/01/08.
//

#include "sk_executor.h"

#include "include/core/SkExecutor.h"

#include "../static/static_sk_executor.h"

#include "../static/static_std_function_void_void-internal.h"
#include "../static/static_sk_executor-internal.h"
#include "../static/static_std_function_void_void.h"

extern "C" {

void SkExecutor_delete(void *executor) {
    delete static_cast<SkExecutor *>(executor);
}

void SkExecutor_add(int function_void_void_key_in, void *executor) {
    static_cast<SkExecutor *>(executor)->add(static_function_void_void_get_entity(function_void_void_key_in));
}

void SkExecutor_borrow(void *executor) {
    static_cast<SkExecutor *>(executor)->borrow();
}

// static

sk_executor_t SkExecutor_MakeFIFOThreadPool(int threads, bool allowBorrowing) {
    return static_sk_executor_make(SkExecutor::MakeFIFOThreadPool(threads, allowBorrowing));
}

sk_executor_t SkExecutor_MakeLIFOThreadPool(int threads, bool allowBorrowing) {
    return static_sk_executor_make(SkExecutor::MakeLIFOThreadPool(threads, allowBorrowing));
}

void *SkExecutor_GetDefault() {
    return &SkExecutor::GetDefault();
}

void SkExecutor_SetDefault(void * executor) {
    SkExecutor::SetDefault(static_cast<SkExecutor *>(executor));
}

}