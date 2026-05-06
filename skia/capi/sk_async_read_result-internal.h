#ifndef RAIA_SKIA_SK_ASYNC_READ_RESULT_INTERNAL_H
#define RAIA_SKIA_SK_ASYNC_READ_RESULT_INTERNAL_H

#include "sk_async_read_result.h"

#include "include/core/SkImage.h"

#include <memory>

struct reskia_async_read_result_t {
    const SkImage::AsyncReadResult *result;
};

struct ReskiaAsyncReadCallbackContext {
    reskia_async_read_pixels_callback_t callback;
    void *context;
};

ReskiaAsyncReadCallbackContext *reskia_async_read_callback_context_new(
        reskia_async_read_pixels_callback_t callback,
        void *context);
void reskia_async_read_pixels_bridge(
        void *context,
        std::unique_ptr<const SkImage::AsyncReadResult> result);
void reskia_async_read_pixels_fail(
        reskia_async_read_pixels_callback_t callback,
        void *context);

#endif // RAIA_SKIA_SK_ASYNC_READ_RESULT_INTERNAL_H
