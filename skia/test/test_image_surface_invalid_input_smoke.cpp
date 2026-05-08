#include "capi/sk_image.h"
#include "capi/sk_surface.h"

#include <cstdio>

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

    SkSurface_notifyContentWillChange(nullptr, 0);
    SkSurface_writePixels(nullptr, nullptr, 0, 0);
    SkSurface_writePixelsWithBitmap(nullptr, nullptr, 0, 0);
    SkSurface_ref(nullptr);
    SkSurface_unref(nullptr);
    SkSurface_release(nullptr);

    return 0;
}
