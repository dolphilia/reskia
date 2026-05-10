#include "capi/sk_image.h"
#include "capi/sk_image_info.h"
#include "capi/sk_i_rect.h"
#include "capi/sk_i_size.h"
#include "capi/sk_surface.h"
#include "capi/sk_surfaces.h"
#include "handles/static_sk_i_rect.h"
#include "handles/static_sk_i_size.h"
#include "handles/static_sk_image.h"
#include "handles/static_sk_image_info.h"
#include "handles/static_sk_surface.h"

#include <cstdio>
#include <cstdint>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[image-surface-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

struct AsyncFailState {
    int calls = 0;
};

void async_fail_callback(void *context, const reskia_async_read_result_t *result) {
    auto *state = static_cast<AsyncFailState *>(context);
    if (state != nullptr && result == nullptr) {
        ++state->calls;
    }
}

}  // namespace

int main() {
    if (!check(SkImage_width(nullptr) == 0, "SkImage_width(nullptr)")) {
        return 1;
    }
    if (!check(SkImage_height(nullptr) == 0, "SkImage_height(nullptr)")) {
        return 2;
    }
    if (!check(!SkImage_peekPixels(nullptr, nullptr), "SkImage_peekPixels(nullptr)")) {
        return 3;
    }
    if (!check(SkImage_colorSpace(nullptr) == nullptr, "SkImage_colorSpace(nullptr)")) {
        return 4;
    }
    if (!check(SkImage_refEncodedData(nullptr) == 0, "SkImage_refEncodedData(nullptr)")) {
        return 5;
    }

    SkImage_ref(nullptr);
    SkImage_unref(nullptr);
    SkImage_release(nullptr);

    if (!check(SkSurface_width(nullptr) == 0, "SkSurface_width(nullptr)")) {
        return 6;
    }
    if (!check(SkSurface_height(nullptr) == 0, "SkSurface_height(nullptr)")) {
        return 7;
    }
    if (!check(SkSurface_getCanvas(nullptr) == nullptr, "SkSurface_getCanvas(nullptr)")) {
        return 8;
    }
    if (!check(SkSurface_makeImageSnapshot(nullptr) == 0, "SkSurface_makeImageSnapshot(nullptr)")) {
        return 9;
    }
    if (!check(!SkSurface_peekPixels(nullptr, nullptr), "SkSurface_peekPixels(nullptr)")) {
        return 10;
    }
    if (!check(!SkSurface_readPixels(nullptr, nullptr, 0, 0), "SkSurface_readPixels(nullptr)")) {
        return 10;
    }
    if (!check(!SkSurface_readPixelsWithImageInfoAndPixels(nullptr, nullptr, nullptr, 0, 0, 0), "SkSurface_readPixelsWithImageInfoAndPixels(nullptr)")) {
        return 10;
    }
    AsyncFailState async_fail_state;
    SkSurface_asyncRescaleAndReadPixels(nullptr, nullptr, nullptr, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 1, "SkSurface_asyncRescaleAndReadPixels invalid fail callback")) {
        return 10;
    }
    SkSurface_asyncRescaleAndReadPixelsYUV420(nullptr, 0, 0, nullptr, 0, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 2, "SkSurface_asyncRescaleAndReadPixelsYUV420 invalid fail callback")) {
        return 10;
    }
    SkSurface_asyncRescaleAndReadPixelsYUVA420(nullptr, 0, 0, nullptr, 0, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 3, "SkSurface_asyncRescaleAndReadPixelsYUVA420 invalid fail callback")) {
        return 10;
    }

    SkSurface_notifyContentWillChange(nullptr, 0);
    SkSurface_writePixels(nullptr, nullptr, 0, 0);
    SkSurface_writePixelsWithBitmap(nullptr, nullptr, 0, 0);
    SkSurface_ref(nullptr);
    SkSurface_unref(nullptr);
    SkSurface_release(nullptr);

    const sk_image_info_t info_handle = SkImageInfo_MakeN32Premul(2, 2);
    auto *info = static_cast<reskia_image_info_t *>(static_sk_image_info_get_ptr(info_handle));
    if (!check(info != nullptr, "SkImageInfo_MakeN32Premul")) {
        return 11;
    }
    const sk_surface_t surface_handle = SkSurfaces_RasterWithoutRowBytes(info, nullptr);
    auto *surface = static_cast<reskia_surface_t *>(static_sk_surface_get_ptr(surface_handle));
    if (!check(surface != nullptr, "SkSurfaces_RasterWithoutRowBytes")) {
        static_sk_image_info_delete(info_handle);
        return 12;
    }
    uint32_t pixels[4] = {};
    if (!check(!SkSurface_readPixels(surface, nullptr, 0, 0), "SkSurface_readPixels null pixmap")) {
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 13;
    }
    if (!check(!SkSurface_readPixelsWithImageInfoAndPixels(surface, nullptr, pixels, 8, 0, 0), "SkSurface_readPixelsWithImageInfoAndPixels null info")) {
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 14;
    }
    if (!check(!SkSurface_readPixelsWithImageInfoAndPixels(surface, info, nullptr, SkImageInfo_minRowBytes(info), 0, 0), "SkSurface_readPixelsWithImageInfoAndPixels null pixels")) {
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 15;
    }
    if (!check(!SkSurface_readPixelsWithImageInfoAndPixels(surface, info, pixels, 1, 0, 0), "SkSurface_readPixelsWithImageInfoAndPixels invalid rowBytes")) {
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 16;
    }
    const sk_i_rect_t src_rect_handle = SkIRect_MakeXYWH(0, 0, 1, 1);
    auto *src_rect = static_cast<reskia_i_rect_t *>(static_sk_i_rect_get_ptr(src_rect_handle));
    if (!check(src_rect != nullptr, "SkIRect_MakeXYWH for surface async")) {
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 17;
    }
    SkSurface_asyncRescaleAndReadPixels(surface, nullptr, src_rect, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 4, "SkSurface_asyncRescaleAndReadPixels null info fail callback")) {
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 18;
    }
    SkSurface_asyncRescaleAndReadPixels(surface, info, nullptr, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 5, "SkSurface_asyncRescaleAndReadPixels null srcRect fail callback")) {
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 19;
    }
    SkSurface_asyncRescaleAndReadPixelsYUV420(surface, 0, 0, src_rect, 0, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 6, "SkSurface_asyncRescaleAndReadPixelsYUV420 invalid dstSize fail callback")) {
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 20;
    }
    SkSurface_asyncRescaleAndReadPixelsYUVA420(surface, 0, 0, src_rect, 999999, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 7, "SkSurface_asyncRescaleAndReadPixelsYUVA420 invalid dstSize fail callback")) {
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 21;
    }
    const sk_image_t image_handle = SkSurface_makeImageSnapshot(surface);
    auto *image = static_cast<reskia_image_t *>(static_sk_image_get_ptr(image_handle));
    if (!check(image != nullptr, "SkSurface_makeImageSnapshot for image async")) {
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 22;
    }
    SkImage_asyncRescaleAndReadPixels(nullptr, info, src_rect, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 8, "SkImage_asyncRescaleAndReadPixels null image fail callback")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 23;
    }
    SkImage_asyncRescaleAndReadPixels(image, nullptr, src_rect, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 9, "SkImage_asyncRescaleAndReadPixels null info fail callback")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 24;
    }
    SkImage_asyncRescaleAndReadPixels(image, info, nullptr, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 10, "SkImage_asyncRescaleAndReadPixels null srcRect fail callback")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 25;
    }
    SkImage_asyncRescaleAndReadPixelsYUV420(image, 0, 0, src_rect, 0, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 11, "SkImage_asyncRescaleAndReadPixelsYUV420 invalid dstSize fail callback")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 26;
    }
    SkImage_asyncRescaleAndReadPixelsYUVA420(image, 0, 0, src_rect, 999999, 0, 0, async_fail_callback, &async_fail_state);
    if (!check(async_fail_state.calls == 12, "SkImage_asyncRescaleAndReadPixelsYUVA420 invalid dstSize fail callback")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 27;
    }
    const sk_i_size_t valid_dst_size = SkISize_Make(1, 1);
    if (!check(static_sk_i_size_get_ptr(valid_dst_size) != nullptr, "SkISize_Make for image async")) {
        static_sk_image_delete(image_handle);
        static_sk_i_rect_delete(src_rect_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(info_handle);
        return 28;
    }
    static_sk_i_size_delete(valid_dst_size);
    static_sk_image_delete(image_handle);
    static_sk_i_rect_delete(src_rect_handle);
    SkSurface_writePixels(surface, nullptr, 0, 0);
    SkSurface_writePixelsWithBitmap(surface, nullptr, 0, 0);

    static_sk_surface_delete(surface_handle);
    static_sk_image_info_delete(info_handle);

    return 0;
}
