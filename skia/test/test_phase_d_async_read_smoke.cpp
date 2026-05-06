#include "capi/sk_async_read_result.h"
#include "capi/sk_i_rect.h"
#include "capi/sk_image.h"
#include "capi/sk_image_info.h"
#include "capi/sk_surface.h"
#include "capi/sk_surfaces.h"
#include "handles/static_sk_i_rect.h"
#include "handles/static_sk_image.h"
#include "handles/static_sk_image_info.h"
#include "handles/static_sk_surface.h"

#include <stddef.h>

struct AsyncReadState {
    bool called;
    int count;
    const void *data;
    size_t row_bytes;
};

static void async_read_callback(void *context, const reskia_async_read_result_t *result) {
    auto *state = static_cast<AsyncReadState *>(context);
    state->called = true;
    state->count = Reskia_AsyncReadResult_count(result);
    state->data = Reskia_AsyncReadResult_data(result, 0);
    state->row_bytes = Reskia_AsyncReadResult_rowBytes(result, 0);
}

static bool valid_result(const AsyncReadState &state) {
    return state.called && state.count == 1 && state.data != nullptr && state.row_bytes >= 8;
}

int main() {
    sk_image_info_t info = SkImageInfo_MakeN32Premul(2, 2);
    sk_i_rect_t rect = SkIRect_MakeXYWH(0, 0, 2, 2);
    sk_surface_t surface = SkSurfaces_RasterWithoutRowBytes(
            static_cast<const reskia_image_info_t *>(static_sk_image_info_get_ptr(info)),
            nullptr);
    if (!surface) {
        return 1;
    }

    AsyncReadState surface_state{};
    SkSurface_asyncRescaleAndReadPixels(
            static_cast<reskia_surface_t *>(static_sk_surface_get_ptr(surface)),
            static_cast<const reskia_image_info_t *>(static_sk_image_info_get_ptr(info)),
            static_cast<const reskia_i_rect_t *>(static_sk_i_rect_get_ptr(rect)),
            0,
            0,
            async_read_callback,
            &surface_state);
    if (!valid_result(surface_state)) {
        return 2;
    }

    sk_image_t image = SkSurface_makeImageSnapshot(
            static_cast<reskia_surface_t *>(static_sk_surface_get_ptr(surface)));
    if (!image) {
        return 3;
    }

    AsyncReadState image_state{};
    SkImage_asyncRescaleAndReadPixels(
            static_cast<reskia_image_t *>(static_sk_image_get_ptr(image)),
            static_cast<const reskia_image_info_t *>(static_sk_image_info_get_ptr(info)),
            static_cast<const reskia_i_rect_t *>(static_sk_i_rect_get_ptr(rect)),
            0,
            0,
            async_read_callback,
            &image_state);
    if (!valid_result(image_state)) {
        return 4;
    }

    static_sk_image_delete(image);
    static_sk_surface_delete(surface);
    static_sk_i_rect_delete(rect);
    static_sk_image_info_delete(info);
    return 0;
}
