#include "capi/sk_high_contrast_config.h"
#include "capi/sk_i_rect.h"
#include "capi/sk_i_size.h"
#include "capi/sk_icc.h"
#include "capi/sk_point.h"
#include "capi/sk_size.h"
#include "handles/static_sk_i_rect.h"
#include "handles/static_sk_i_size.h"
#include "handles/static_sk_point.h"
#include "handles/static_sk_size_t.h"
#include "include/core/SkPoint.h"

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
    ok &= check(size != nullptr && SkSize_width(size) == 3.0f && SkSize_height(size) == 4.0f, "Size valid handle");

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

    const sk_point_t point_handle = SkPoint_Make(3.0f, 4.0f);
    auto *point = static_cast<reskia_point_t *>(static_sk_point_get_ptr(point_handle));
    ok &= check(point != nullptr && SkPoint_length(point_handle) == 5.0f, "Point valid handle");
    SkPoint_scaleTo(point_handle, 2.0f, nullptr);
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

    static_sk_point_delete(point_handle);
    static_sk_i_rect_delete(irect_handle);
    static_sk_size_delete(size_handle);
    static_sk_i_size_delete(isize_handle);
    return ok ? 0 : 1;
}
