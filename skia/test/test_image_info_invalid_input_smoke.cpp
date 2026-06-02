#include "capi/sk_image_info.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[image-info-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    if (!check(!SkImageInfo_equals(nullptr, nullptr), "SkImageInfo_equals(nullptr)")) {
        return 1;
    }
    if (!check(!SkImageInfo_notEquals(nullptr, nullptr), "SkImageInfo_notEquals(nullptr, nullptr)")) {
        return 2;
    }
    if (!check(SkImageInfo_width(nullptr) == 0, "SkImageInfo_width(nullptr)")) {
        return 3;
    }
    if (!check(SkImageInfo_height(nullptr) == 0, "SkImageInfo_height(nullptr)")) {
        return 4;
    }
    if (!check(SkImageInfo_colorSpace(nullptr) == nullptr, "SkImageInfo_colorSpace(nullptr)")) {
        return 5;
    }
    if (!check(SkImageInfo_refColorSpace(nullptr) == 0, "SkImageInfo_refColorSpace(nullptr)")) {
        return 6;
    }
    if (!check(SkImageInfo_isEmpty(nullptr), "SkImageInfo_isEmpty(nullptr)")) {
        return 7;
    }
    if (!check(SkImageInfo_colorInfo(nullptr) == 0, "SkImageInfo_colorInfo(nullptr)")) {
        return 8;
    }
    if (!check(!SkImageInfo_isOpaque(nullptr), "SkImageInfo_isOpaque(nullptr)")) {
        return 9;
    }
    if (!check(SkImageInfo_dimensions(nullptr) == 0, "SkImageInfo_dimensions(nullptr)")) {
        return 10;
    }
    if (!check(SkImageInfo_bounds(nullptr) == 0, "SkImageInfo_bounds(nullptr)")) {
        return 11;
    }
    if (!check(SkImageInfo_makeWH(nullptr, 1, 1) == 0, "SkImageInfo_makeWH(nullptr)")) {
        return 12;
    }
    if (!check(SkImageInfo_bytesPerPixel(nullptr) == 0, "SkImageInfo_bytesPerPixel(nullptr)")) {
        return 13;
    }
    if (!check(SkImageInfo_minRowBytes(nullptr) == 0, "SkImageInfo_minRowBytes(nullptr)")) {
        return 14;
    }
    if (!check(SkImageInfo_computeByteSize(nullptr, 0) == 0, "SkImageInfo_computeByteSize(nullptr)")) {
        return 15;
    }
    if (!check(!SkImageInfo_validRowBytes(nullptr, 0), "SkImageInfo_validRowBytes(nullptr)")) {
        return 16;
    }
    if (!check(SkImageInfo_MakeWithDimensionsAndColorInfo(0, nullptr) == 0, "SkImageInfo_MakeWithDimensionsAndColorInfo(nullptr)")) {
        return 17;
    }

    SkImageInfo_reset(nullptr);

    reskia_image_info_t *image_info = SkImageInfo_new();
    if (!check(image_info != nullptr, "SkImageInfo_new")) {
        return 18;
    }
    if (!check(SkImageInfo_isEmpty(image_info), "new SkImageInfo is empty")) {
        SkImageInfo_delete(image_info);
        return 19;
    }

    const sk_image_info_t handle = SkImageInfo_MakeN32Premul(4, 4);
    auto *made = static_cast<reskia_image_info_t *>(static_sk_image_info_get_ptr(handle));
    if (!check(made != nullptr, "SkImageInfo_MakeN32Premul")) {
        SkImageInfo_delete(image_info);
        return 20;
    }
    if (!check(SkImageInfo_width(made) == 4, "SkImageInfo_width(made)")) {
        static_sk_image_info_delete(handle);
        SkImageInfo_delete(image_info);
        return 21;
    }
    if (!check(SkImageInfo_validRowBytes(made, SkImageInfo_minRowBytes(made)), "SkImageInfo_validRowBytes(made)")) {
        static_sk_image_info_delete(handle);
        SkImageInfo_delete(image_info);
        return 22;
    }

    static_sk_image_info_delete(handle);
    SkImageInfo_delete(image_info);
    return 0;
}
