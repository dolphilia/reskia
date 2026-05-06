//
// Created by Codex on 2026/05/06.
//

#include "sk_async_read_result.h"
#include "sk_async_read_result-internal.h"

ReskiaAsyncReadCallbackContext *reskia_async_read_callback_context_new(
        reskia_async_read_pixels_callback_t callback,
        void *context) {
    return new ReskiaAsyncReadCallbackContext{callback, context};
}

void reskia_async_read_pixels_bridge(
        void *context,
        std::unique_ptr<const SkImage::AsyncReadResult> result) {
    std::unique_ptr<ReskiaAsyncReadCallbackContext> callback_context(
            static_cast<ReskiaAsyncReadCallbackContext *>(context));
    if (!callback_context || !callback_context->callback) {
        return;
    }
    if (!result) {
        callback_context->callback(callback_context->context, nullptr);
        return;
    }
    reskia_async_read_result_t wrapped{result.get()};
    callback_context->callback(callback_context->context, &wrapped);
}

void reskia_async_read_pixels_fail(
        reskia_async_read_pixels_callback_t callback,
        void *context) {
    if (callback) {
        callback(context, nullptr);
    }
}

extern "C" {

int Reskia_AsyncReadResult_count(const reskia_async_read_result_t *result) {
    if (!result || !result->result) {
        return 0;
    }
    return result->result->count();
}

const void *Reskia_AsyncReadResult_data(const reskia_async_read_result_t *result, int index) {
    if (!result || !result->result) {
        return nullptr;
    }
    return result->result->data(index);
}

size_t Reskia_AsyncReadResult_rowBytes(const reskia_async_read_result_t *result, int index) {
    if (!result || !result->result) {
        return 0;
    }
    return result->result->rowBytes(index);
}

}
