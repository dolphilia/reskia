#include "capi/sk_color_info.h"
#include "capi/sk_color_space.h"
#include "capi/sk_color_space_primaries.h"
#include "modules/skcms/skcms.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[color-info-space-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    if (!check(SkColorInfo_newCopy(nullptr) == nullptr, "SkColorInfo_newCopy(nullptr)")) {
        return 1;
    }
    if (!check(!SkColorInfo_equals(nullptr, nullptr), "SkColorInfo_equals(nullptr)")) {
        return 2;
    }
    if (!check(!SkColorInfo_notEquals(nullptr, nullptr), "SkColorInfo_notEquals(nullptr)")) {
        return 3;
    }
    if (!check(SkColorInfo_alphaType(nullptr) == 0, "SkColorInfo_alphaType(nullptr)")) {
        return 4;
    }
    if (!check(SkColorInfo_bytesPerPixel(nullptr) == 0, "SkColorInfo_bytesPerPixel(nullptr)")) {
        return 5;
    }
    if (!check(SkColorInfo_colorSpace(nullptr) == nullptr, "SkColorInfo_colorSpace(nullptr)")) {
        return 6;
    }
    if (!check(SkColorInfo_colorType(nullptr) == 0, "SkColorInfo_colorType(nullptr)")) {
        return 7;
    }
    if (!check(!SkColorInfo_gammaCloseToSRGB(nullptr), "SkColorInfo_gammaCloseToSRGB(nullptr)")) {
        return 8;
    }
    if (!check(!SkColorInfo_isOpaque(nullptr), "SkColorInfo_isOpaque(nullptr)")) {
        return 9;
    }
    if (!check(SkColorInfo_makeAlphaType(nullptr, 0) == 0, "SkColorInfo_makeAlphaType(nullptr)")) {
        return 10;
    }
    if (!check(SkColorInfo_makeColorSpace(nullptr, 0) == 0, "SkColorInfo_makeColorSpace(nullptr)")) {
        return 11;
    }
    if (!check(SkColorInfo_makeColorType(nullptr, 0) == 0, "SkColorInfo_makeColorType(nullptr)")) {
        return 12;
    }
    if (!check(SkColorInfo_refColorSpace(nullptr) == 0, "SkColorInfo_refColorSpace(nullptr)")) {
        return 13;
    }
    if (!check(SkColorInfo_shiftPerPixel(nullptr) == 0, "SkColorInfo_shiftPerPixel(nullptr)")) {
        return 14;
    }

    SkColorSpace_release(nullptr);
    SkColorSpace_toProfile(nullptr, nullptr);
    if (!check(!SkColorSpace_gammaCloseToSRGB(nullptr), "SkColorSpace_gammaCloseToSRGB(nullptr)")) {
        return 15;
    }
    if (!check(!SkColorSpace_gammaIsLinear(nullptr), "SkColorSpace_gammaIsLinear(nullptr)")) {
        return 16;
    }
    if (!check(!SkColorSpace_isNumericalTransferFn(nullptr, nullptr), "SkColorSpace_isNumericalTransferFn(nullptr)")) {
        return 17;
    }
    if (!check(!SkColorSpace_toXYZD50(nullptr, nullptr), "SkColorSpace_toXYZD50(nullptr)")) {
        return 18;
    }
    if (!check(SkColorSpace_toXYZD50Hash(nullptr) == 0, "SkColorSpace_toXYZD50Hash(nullptr)")) {
        return 19;
    }
    if (!check(SkColorSpace_makeLinearGamma(nullptr) == 0, "SkColorSpace_makeLinearGamma(nullptr)")) {
        return 20;
    }
    if (!check(SkColorSpace_makeSRGBGamma(nullptr) == 0, "SkColorSpace_makeSRGBGamma(nullptr)")) {
        return 21;
    }
    if (!check(SkColorSpace_makeColorSpin(nullptr) == 0, "SkColorSpace_makeColorSpin(nullptr)")) {
        return 22;
    }
    if (!check(!SkColorSpace_isSRGB(nullptr), "SkColorSpace_isSRGB(nullptr)")) {
        return 23;
    }
    if (!check(SkColorSpace_serialize(nullptr) == 0, "SkColorSpace_serialize(nullptr)")) {
        return 24;
    }
    if (!check(SkColorSpace_writeToMemory(nullptr, nullptr) == 0, "SkColorSpace_writeToMemory(nullptr)")) {
        return 25;
    }
    SkColorSpace_transferFn(nullptr, nullptr);
    SkColorSpace_transferFnToStruct(nullptr, nullptr);
    SkColorSpace_invTransferFn(nullptr, nullptr);
    SkColorSpace_gamutTransformTo(nullptr, nullptr, nullptr);
    if (!check(SkColorSpace_transferFnHash(nullptr) == 0, "SkColorSpace_transferFnHash(nullptr)")) {
        return 26;
    }
    if (!check(SkColorSpace_hash(nullptr) == 0, "SkColorSpace_hash(nullptr)")) {
        return 27;
    }
    if (!check(!SkColorSpace_unique(nullptr), "SkColorSpace_unique(nullptr)")) {
        return 28;
    }
    SkColorSpace_ref(nullptr);
    SkColorSpace_unref(nullptr);
    SkColorSpace_deref(nullptr);
    if (!check(!SkColorSpace_refCntGreaterThan(nullptr, 0), "SkColorSpace_refCntGreaterThan(nullptr)")) {
        return 29;
    }
    if (!check(SkColorSpace_MakeRGB(nullptr, nullptr) == 0, "SkColorSpace_MakeRGB(nullptr)")) {
        return 30;
    }
    if (!check(SkColorSpace_Make(nullptr) == 0, "SkColorSpace_Make(nullptr)")) {
        return 31;
    }
    if (!check(SkColorSpace_Deserialize(nullptr, 0) == 0, "SkColorSpace_Deserialize(nullptr)")) {
        return 32;
    }
    if (!check(SkColorSpace_Equals(nullptr, nullptr), "SkColorSpace_Equals(nullptr, nullptr)")) {
        return 33;
    }

    SkColorSpacePrimaries_toXYZD50(nullptr, nullptr);

    reskia_color_info_t *color_info = SkColorInfo_new();
    if (!check(color_info != nullptr, "SkColorInfo_new")) {
        return 34;
    }
    if (!check(SkColorInfo_bytesPerPixel(color_info) == 0, "default SkColorInfo bytesPerPixel")) {
        SkColorInfo_delete(color_info);
        return 35;
    }
    if (!check(SkColorInfo_refColorSpace(color_info) == 0, "default SkColorInfo_refColorSpace")) {
        SkColorInfo_delete(color_info);
        return 36;
    }
    const sk_color_info_t n32 = SkColorInfo_makeColorType(color_info, 4);
    auto *n32_info = static_cast<reskia_color_info_t *>(static_sk_color_info_get_ptr(n32));
    if (!check(n32_info != nullptr, "SkColorInfo_makeColorType")) {
        SkColorInfo_delete(color_info);
        return 37;
    }

    const sk_color_space_t srgb = SkColorSpace_MakeSRGB();
    auto *srgb_space = static_cast<reskia_color_space_t *>(static_sk_color_space_get_ptr(srgb));
    if (!check(srgb_space != nullptr, "SkColorSpace_MakeSRGB")) {
        static_sk_color_info_delete(n32);
        SkColorInfo_delete(color_info);
        return 38;
    }
    if (!check(SkColorSpace_isSRGB(srgb_space), "SkColorSpace_isSRGB(srgb)")) {
        static_sk_color_space_delete(srgb);
        static_sk_color_info_delete(n32);
        SkColorInfo_delete(color_info);
        return 39;
    }
    if (!check(SkColorSpace_writeToMemory(srgb_space, nullptr) > 0, "SkColorSpace_writeToMemory(srgb, nullptr)")) {
        static_sk_color_space_delete(srgb);
        static_sk_color_info_delete(n32);
        SkColorInfo_delete(color_info);
        return 40;
    }
    float transfer[7] = {};
    SkColorSpace_transferFn(srgb_space, transfer);
    if (!check(transfer[0] != 0.0f, "SkColorSpace_transferFn(srgb)")) {
        static_sk_color_space_delete(srgb);
        static_sk_color_info_delete(n32);
        SkColorInfo_delete(color_info);
        return 41;
    }

    skcms_TransferFunction fn = {2.2f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    skcms_Matrix3x3 to_xyz = {{{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}};
    const sk_color_space_t rgb = SkColorSpace_MakeRGB(
        reinterpret_cast<const reskia_transfer_function_t *>(&fn),
        reinterpret_cast<const reskia_matrix3x3_t *>(&to_xyz));
    auto *rgb_space = static_cast<reskia_color_space_t *>(static_sk_color_space_get_ptr(rgb));
    if (!check(rgb_space != nullptr, "SkColorSpace_MakeRGB")) {
        static_sk_color_space_delete(srgb);
        static_sk_color_info_delete(n32);
        SkColorInfo_delete(color_info);
        return 42;
    }

    static_sk_color_space_delete(rgb);
    static_sk_color_space_delete(srgb);
    static_sk_color_info_delete(n32);
    SkColorInfo_delete(color_info);
    return 0;
}
