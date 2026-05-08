#include "capi/sk_bitmap.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[bitmap-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    if (!check(SkBitmap_new_copy(nullptr) == nullptr, "SkBitmap_new_copy(nullptr)")) {
        return 1;
    }
    if (!check(SkBitmap_width(nullptr) == 0, "SkBitmap_width(nullptr)")) {
        return 2;
    }
    if (!check(SkBitmap_height(nullptr) == 0, "SkBitmap_height(nullptr)")) {
        return 3;
    }
    if (!check(SkBitmap_getPixels(nullptr) == nullptr, "SkBitmap_getPixels(nullptr)")) {
        return 4;
    }
    if (!check(SkBitmap_empty(nullptr), "SkBitmap_empty(nullptr)")) {
        return 5;
    }
    if (!check(SkBitmap_isNull(nullptr), "SkBitmap_isNull(nullptr)")) {
        return 6;
    }
    if (!check(!SkBitmap_peekPixels(nullptr, nullptr), "SkBitmap_peekPixels(nullptr)")) {
        return 7;
    }
    if (!check(!SkBitmap_readPixels(nullptr, nullptr, nullptr, 0, 0, 0), "SkBitmap_readPixels(nullptr)")) {
        return 8;
    }
    if (!check(!SkBitmap_writePixels(nullptr, nullptr), "SkBitmap_writePixels(nullptr)")) {
        return 9;
    }
    if (!check(!SkBitmap_ComputeIsOpaque(nullptr), "SkBitmap_ComputeIsOpaque(nullptr)")) {
        return 10;
    }

    SkBitmap_allocPixels(nullptr);
    SkBitmap_eraseColor(nullptr, 0);
    SkBitmap_notifyPixelsChanged(nullptr);
    SkBitmap_reset(nullptr);
    SkBitmap_setImmutable(nullptr);
    SkBitmap_setPixels(nullptr, nullptr);
    SkBitmap_swap(nullptr, nullptr);

    reskia_bitmap_t *bitmap = SkBitmap_new();
    if (!check(bitmap != nullptr, "SkBitmap_new")) {
        return 11;
    }

    if (!check(!SkBitmap_readPixels(bitmap, nullptr, nullptr, 0, 0, 0), "SkBitmap_readPixels(bitmap, nullptr)")) {
        SkBitmap_delete(bitmap);
        return 12;
    }
    if (!check(!SkBitmap_writePixels(bitmap, nullptr), "SkBitmap_writePixels(bitmap, nullptr)")) {
        SkBitmap_delete(bitmap);
        return 13;
    }
    if (!check(!SkBitmap_peekPixels(bitmap, nullptr), "SkBitmap_peekPixels(bitmap, nullptr)")) {
        SkBitmap_delete(bitmap);
        return 14;
    }

    SkBitmap_delete(bitmap);
    return 0;
}
