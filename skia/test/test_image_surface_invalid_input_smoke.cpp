#include "capi/sk_image.h"
#include "capi/sk_image_info.h"
#include "capi/sk_surface.h"
#include "capi/sk_surfaces.h"
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
    SkSurface_writePixels(surface, nullptr, 0, 0);
    SkSurface_writePixelsWithBitmap(surface, nullptr, 0, 0);

    static_sk_surface_delete(surface_handle);
    static_sk_image_info_delete(info_handle);

    return 0;
}
