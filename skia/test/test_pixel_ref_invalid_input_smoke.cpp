#include "capi/sk_malloc_pixel_ref.h"
#include "capi/sk_pixel_ref.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[pixel-ref-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkPixelRef_release(nullptr);
    SkPixelRef_notifyPixelsChanged(nullptr);
    SkPixelRef_setImmutable(nullptr);
    SkPixelRef_addGenIDChangeListener(nullptr, 0);
    SkPixelRef_notifyAddedToCache(nullptr);
    SkPixelRef_ref(nullptr);
    SkPixelRef_unref(nullptr);

    if (!check(SkPixelRef_new(-1, 1, nullptr, 0) == nullptr, "SkPixelRef_new negative width")) {
        return 1;
    }
    if (!check(SkPixelRef_dimensions(nullptr) == 0, "SkPixelRef_dimensions(nullptr)")) {
        return 2;
    }
    if (!check(SkPixelRef_width(nullptr) == 0, "SkPixelRef_width(nullptr)")) {
        return 3;
    }
    if (!check(SkPixelRef_height(nullptr) == 0, "SkPixelRef_height(nullptr)")) {
        return 4;
    }
    if (!check(SkPixelRef_pixels(nullptr) == nullptr, "SkPixelRef_pixels(nullptr)")) {
        return 5;
    }
    if (!check(SkPixelRef_rowBytes(nullptr) == 0, "SkPixelRef_rowBytes(nullptr)")) {
        return 6;
    }
    if (!check(SkPixelRef_getGenerationID(nullptr) == 0, "SkPixelRef_getGenerationID(nullptr)")) {
        return 7;
    }
    if (!check(!SkPixelRef_isImmutable(nullptr), "SkPixelRef_isImmutable(nullptr)")) {
        return 8;
    }
    if (!check(SkPixelRef_diagnostic_only_getDiscardable(nullptr) == nullptr, "SkPixelRef_diagnostic_only_getDiscardable(nullptr)")) {
        return 9;
    }
    if (!check(!SkPixelRef_unique(nullptr), "SkPixelRef_unique(nullptr)")) {
        return 10;
    }
    if (!check(SkMallocPixelRef_MakeAllocate(nullptr, 0) == 0, "SkMallocPixelRef_MakeAllocate(nullptr)")) {
        return 11;
    }
    if (!check(SkMallocPixelRef_MakeWithData(nullptr, 0, 0) == 0, "SkMallocPixelRef_MakeWithData(nullptr)")) {
        return 12;
    }

    unsigned char pixels[4] = {0, 0, 0, 0};
    reskia_pixel_ref_t *pixelRef = SkPixelRef_new(1, 1, pixels, 4);
    if (!check(pixelRef != nullptr, "SkPixelRef_new valid")) {
        return 13;
    }
    if (!check(SkPixelRef_width(pixelRef) == 1, "SkPixelRef_width valid")) {
        SkPixelRef_release(pixelRef);
        return 14;
    }
    if (!check(SkPixelRef_height(pixelRef) == 1, "SkPixelRef_height valid")) {
        SkPixelRef_release(pixelRef);
        return 15;
    }
    if (!check(SkPixelRef_pixels(pixelRef) == pixels, "SkPixelRef_pixels valid")) {
        SkPixelRef_release(pixelRef);
        return 16;
    }
    if (!check(SkPixelRef_rowBytes(pixelRef) == 4, "SkPixelRef_rowBytes valid")) {
        SkPixelRef_release(pixelRef);
        return 17;
    }
    if (!check(SkPixelRef_getGenerationID(pixelRef) != 0, "SkPixelRef_getGenerationID valid")) {
        SkPixelRef_release(pixelRef);
        return 18;
    }
    const sk_i_size_t dimensions = SkPixelRef_dimensions(pixelRef);
    if (!check(dimensions != 0, "SkPixelRef_dimensions valid")) {
        SkPixelRef_release(pixelRef);
        return 19;
    }
    static_sk_i_size_delete(dimensions);

    SkPixelRef_ref(pixelRef);
    if (!check(!SkPixelRef_unique(pixelRef), "SkPixelRef_unique after ref")) {
        SkPixelRef_unref(pixelRef);
        SkPixelRef_release(pixelRef);
        return 20;
    }
    SkPixelRef_unref(pixelRef);
    SkPixelRef_setImmutable(pixelRef);
    if (!check(SkPixelRef_isImmutable(pixelRef), "SkPixelRef_isImmutable after set")) {
        SkPixelRef_release(pixelRef);
        return 21;
    }
    SkPixelRef_notifyPixelsChanged(pixelRef);
    SkPixelRef_notifyAddedToCache(pixelRef);
    SkPixelRef_addGenIDChangeListener(pixelRef, 0);
    SkPixelRef_release(pixelRef);

    return 0;
}
