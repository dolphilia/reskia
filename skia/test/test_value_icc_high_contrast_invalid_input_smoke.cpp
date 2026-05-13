#include "capi/sk_high_contrast_config.h"
#include "capi/sk_data.h"
#include "capi/sk_i_rect.h"
#include "capi/sk_i_size.h"
#include "capi/sk_icc.h"
#include "capi/sk_point.h"
#include "capi/sk_size.h"
#include "handles/static_sk_data.h"
#include "handles/static_sk_i_rect.h"
#include "handles/static_sk_i_size.h"
#include "handles/static_sk_i_point.h"
#include "handles/static_sk_point.h"
#include "handles/static_sk_size_t.h"
#include "include/core/SkPoint.h"
#include "modules/skcms/skcms.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[value-icc-high-contrast-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    bool ok = true;

    ok &= check(SkHighContrastConfig_new() != nullptr, "HighContrast default config");
    auto *config = SkHighContrastConfig_newWithGrayscaleInvertStyleContrast(false, 0, 0.0f);
    ok &= check(config != nullptr && isValid(config), "HighContrast valid config");
    SkHighContrastConfig_delete(config);
    ok &= check(SkHighContrastConfig_newWithGrayscaleInvertStyleContrast(false, 999999, 0.0f) == nullptr, "HighContrast invalid invertStyle");
    ok &= check(!isValid(nullptr), "HighContrast isValid null");

    SkISize_set(nullptr, 1, 2);
    SkISize_setEmpty(nullptr);
    ok &= check(SkISize_isZero(nullptr), "ISize isZero null");
    ok &= check(SkISize_isEmpty(nullptr), "ISize isEmpty null");
    ok &= check(SkISize_width(nullptr) == 0 && SkISize_height(nullptr) == 0, "ISize dimensions null");
    ok &= check(SkISize_area(nullptr) == 0, "ISize area null");
    ok &= check(!SkISize_equals(nullptr, 0, 0), "ISize equals null");
    const sk_i_size_t isize_handle = SkISize_Make(3, 4);
    auto *isize = static_cast<reskia_i_size_t *>(static_sk_i_size_get_ptr(isize_handle));
    ok &= check(isize != nullptr && SkISize_width(isize) == 3 && SkISize_height(isize) == 4, "ISize valid handle");
    SkISize_set(isize, 5, 6);
    ok &= check(SkISize_width(isize) == 5 && SkISize_height(isize) == 6 && SkISize_area(isize) == 30, "ISize valid mutation");

    SkSize_set(nullptr, 1.0f, 2.0f);
    SkSize_setEmpty(nullptr);
    ok &= check(SkSize_isZero(nullptr), "Size isZero null");
    ok &= check(SkSize_isEmpty(nullptr), "Size isEmpty null");
    ok &= check(SkSize_width(nullptr) == 0.0f && SkSize_height(nullptr) == 0.0f, "Size dimensions null");
    ok &= check(!SkSize_equals(nullptr, 0.0f, 0.0f), "Size equals null");
    ok &= check(SkSize_toRound(nullptr) == 0 && SkSize_toCeil(nullptr) == 0 && SkSize_toFloor(nullptr) == 0, "Size integer conversions null");
    ok &= check(SkSize_MakeFromISize(nullptr) == 0, "Size MakeFromISize null");
    const sk_size_t size_handle = SkSize_MakeFromISize(isize);
    auto *size = static_cast<reskia_size_t *>(static_sk_size_get_ptr(size_handle));
    ok &= check(size != nullptr && SkSize_width(size) == 5.0f && SkSize_height(size) == 6.0f, "Size valid handle");
    SkSize_set(size, 7.0f, 8.0f);
    ok &= check(SkSize_width(size) == 7.0f && SkSize_height(size) == 8.0f, "Size valid mutation");
    const sk_i_size_t rounded_size_handle = SkSize_toRound(size);
    auto *rounded_size = static_cast<reskia_i_size_t *>(static_sk_i_size_get_ptr(rounded_size_handle));
    ok &= check(rounded_size != nullptr && SkISize_width(rounded_size) == 7 && SkISize_height(rounded_size) == 8, "Size toRound valid handle");

    SkIRect_setEmpty(nullptr);
    ok &= check(SkIRect_left(nullptr) == 0, "IRect left null");
    ok &= check(SkIRect_isEmpty(nullptr), "IRect isEmpty null");
    ok &= check(SkIRect_makeOffset(nullptr, 1, 2) == 0, "IRect makeOffset null");
    ok &= check(!SkIRect_containsIRect(nullptr, nullptr), "IRect contains null");
    ok &= check(SkIRect_MakeSize(nullptr) == 0, "IRect MakeSize null");
    ok &= check(!SkIRect_Intersects(nullptr, nullptr), "IRect Intersects null");
    const sk_i_rect_t irect_handle = SkIRect_MakeSize(isize);
    auto *irect = static_cast<reskia_i_rect_t *>(static_sk_i_rect_get_ptr(irect_handle));
    ok &= check(irect != nullptr && SkIRect_left(irect) == 0 && !SkIRect_isEmpty(irect), "IRect valid handle");
    ok &= check(SkIRect_width(irect) == 5 && SkIRect_height(irect) == 6 && SkIRect_width64(irect) == 5 && SkIRect_height64(irect) == 6, "IRect valid dimensions");
    const sk_i_point_t top_left_handle = SkIRect_topLeft(irect);
    auto *top_left = static_cast<reskia_i_point_t *>(static_sk_i_point_get_ptr(top_left_handle));
    const sk_i_size_t irect_size_handle = SkIRect_size(irect);
    ok &= check(top_left != nullptr && irect_size_handle != 0, "IRect topLeft and size handles");
    const sk_i_rect_t offset_handle = SkIRect_makeOffset(irect, 2, 3);
    auto *offset = static_cast<reskia_i_rect_t *>(static_sk_i_rect_get_ptr(offset_handle));
    ok &= check(offset != nullptr && SkIRect_left(offset) == 2 && SkIRect_top(offset) == 3, "IRect makeOffset valid handle");
    ok &= check(SkIRect_contains(irect, 1, 1) && SkIRect_containsIRect(irect, irect), "IRect valid contains");
    ok &= check(SkIRect_Intersects(irect, offset), "IRect static Intersects valid");

    const sk_point_t point_handle = SkPoint_Make(3.0f, 4.0f);
    auto *point = static_cast<reskia_point_t *>(static_sk_point_get_ptr(point_handle));
    ok &= check(point != nullptr && SkPoint_length(point_handle) == 5.0f, "Point valid handle");
    SkPoint dst_point = {};
    SkPoint_scaleTo(point_handle, 2.0f, reinterpret_cast<reskia_point_t *>(&dst_point));
    ok &= check(dst_point.x() == 6.0f && dst_point.y() == 8.0f, "Point scaleTo valid output");
    SkPoint_iset(point_handle, nullptr);
    SkPoint_setAbs(point_handle, nullptr);
    ok &= check(SkPoint_dot(point_handle, nullptr) == 0.0f, "Point dot null vector");
    ok &= check(SkPoint_CrossProduct(nullptr, nullptr) == 0.0f, "Point CrossProduct null");
    ok &= check(SkPoint_DotProduct(nullptr, nullptr) == 0.0f, "Point DotProduct null");
    ok &= check(SkPoint_Distance(nullptr, nullptr) == 0.0f, "Point Distance null");
    SkPoint_Offset(nullptr, 1, 1.0f, 1.0f);
    SkPoint_OffsetByVector(nullptr, 1, nullptr);
    SkPoint points[1] = {{0.0f, 0.0f}};
    SkPoint_Offset(reinterpret_cast<reskia_point_t *>(points), 1, 2.0f, 3.0f);
    ok &= check(points[0].x() == 2.0f && points[0].y() == 3.0f, "Point Offset valid array");

    ok &= check(SkICC_SkWriteICCProfile(nullptr, nullptr) == 0, "ICC WriteICCProfile null");
    ok &= check(SkICC_SkWriteICCProfileFromICCProfile(nullptr, nullptr) == 0, "ICC WriteICCProfileFromProfile null");
    SkICC_SkICCFloatXYZD50ToGrid16Lab(nullptr, nullptr);
    SkICC_SkICCFloatToTable16(0.0f, nullptr);
    float xyz_d50[3] = {0.5f, 0.5f, 0.5f};
    uint8_t grid16_lab[6] = {};
    SkICC_SkICCFloatXYZD50ToGrid16Lab(xyz_d50, grid16_lab);
    ok &= check(grid16_lab[0] != 0 || grid16_lab[1] != 0 || grid16_lab[2] != 0 ||
                grid16_lab[3] != 0 || grid16_lab[4] != 0 || grid16_lab[5] != 0,
                "ICC Grid16Lab valid output");
    uint8_t table16[2] = {};
    SkICC_SkICCFloatToTable16(0.5f, table16);
    ok &= check(table16[0] != 0 || table16[1] != 0, "ICC Table16 valid output");
    const skcms_ICCProfile *srgb_profile = skcms_sRGB_profile();
    const sk_data_t profile_handle = SkICC_SkWriteICCProfile(
            reinterpret_cast<const reskia_transfer_function_t *>(&srgb_profile->trc[0].parametric),
            reinterpret_cast<const reskia_matrix3x3_t *>(&srgb_profile->toXYZD50));
    auto *profile_data = static_cast<reskia_data_t *>(static_sk_data_get_ptr(profile_handle));
    ok &= check(profile_data != nullptr && SkData_size(profile_data) > 0, "ICC WriteICCProfile valid sRGB profile");
    const const_sk_data_t profile_from_icc_handle = SkICC_SkWriteICCProfileFromICCProfile(
            reinterpret_cast<const reskia_icc_profile_t *>(srgb_profile), "sRGB");
    ok &= check(profile_from_icc_handle != 0 && static_const_sk_data_get_ptr(profile_from_icc_handle) != nullptr, "ICC WriteICCProfileFromICCProfile valid sRGB profile");

    static_const_sk_data_delete(profile_from_icc_handle);
    static_sk_data_delete(profile_handle);
    static_sk_i_rect_delete(offset_handle);
    static_sk_i_point_delete(top_left_handle);
    static_sk_i_size_delete(irect_size_handle);
    static_sk_i_size_delete(rounded_size_handle);
    static_sk_point_delete(point_handle);
    static_sk_i_rect_delete(irect_handle);
    static_sk_size_delete(size_handle);
    static_sk_i_size_delete(isize_handle);
    return ok ? 0 : 1;
}
