#include "capi/sk_color_matrix_filter.h"
#include "handles/static_sk_color_filter.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[color-matrix-filter-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkColorMatrixFilter_release(nullptr);
    SkColorMatrixFilter_ref(nullptr);
    SkColorMatrixFilter_unref(nullptr);

    reskia_color_t color = 0;
    int mode = 0;
    if (!check(!SkColorMatrixFilter_asAColorMode(nullptr, &color, &mode), "SkColorMatrixFilter_asAColorMode(nullptr)")) {
        return 1;
    }
    if (!check(!SkColorMatrixFilter_asAColorMatrix(nullptr, nullptr), "SkColorMatrixFilter_asAColorMatrix(nullptr)")) {
        return 2;
    }
    if (!check(!SkColorMatrixFilter_isAlphaUnchanged(nullptr), "SkColorMatrixFilter_isAlphaUnchanged(nullptr)")) {
        return 3;
    }
    if (!check(SkColorMatrixFilter_filterColor4f(nullptr, nullptr, nullptr, nullptr) == 0, "SkColorMatrixFilter_filterColor4f(nullptr)")) {
        return 5;
    }
    if (!check(SkColorMatrixFilter_makeComposed(nullptr, 0) == 0, "SkColorMatrixFilter_makeComposed(nullptr)")) {
        return 6;
    }
    if (!check(SkColorMatrixFilter_makeWithWorkingColorSpace(nullptr, 0) == 0, "SkColorMatrixFilter_makeWithWorkingColorSpace(nullptr)")) {
        return 7;
    }
    if (!check(SkColorMatrixFilter_getFactory(nullptr) == 0, "SkColorMatrixFilter_getFactory(nullptr)")) {
        return 8;
    }
    if (!check(SkColorMatrixFilter_getTypeName(nullptr) == nullptr, "SkColorMatrixFilter_getTypeName(nullptr)")) {
        return 9;
    }
    SkColorMatrixFilter_flatten(nullptr, nullptr);
    if (!check(SkColorMatrixFilter_getFlattenableType(nullptr) == 0, "SkColorMatrixFilter_getFlattenableType(nullptr)")) {
        return 10;
    }
    if (!check(SkColorMatrixFilter_serialize(nullptr, nullptr) == 0, "SkColorMatrixFilter_serialize(nullptr)")) {
        return 11;
    }
    if (!check(SkColorMatrixFilter_serializeToMemory(nullptr, nullptr, 0, nullptr) == 0, "SkColorMatrixFilter_serializeToMemory(nullptr)")) {
        return 12;
    }
    if (!check(!SkColorMatrixFilter_unique(nullptr), "SkColorMatrixFilter_unique(nullptr)")) {
        return 13;
    }
    if (!check(SkColorMatrixFilter_Deserialize(nullptr, 0, nullptr) == 0, "SkColorMatrixFilter_Deserialize(nullptr)")) {
        return 14;
    }
    if (!check(SkColorMatrixFilter_NameToFactory(nullptr) == 0, "SkColorMatrixFilter_NameToFactory(nullptr)")) {
        return 15;
    }
    if (!check(SkColorMatrixFilter_FactoryToName(0) == nullptr, "SkColorMatrixFilter_FactoryToName(0)")) {
        return 16;
    }
    SkColorMatrixFilter_Register(nullptr, 0);

    const sk_color_filter_t lighting = SkColorMatrixFilter_MakeLightingFilter(0xffffffff, 0xff000000);
    if (!check(static_sk_color_filter_get_ptr(lighting) != nullptr, "SkColorMatrixFilter_MakeLightingFilter(valid)")) {
        return 17;
    }

    static_sk_color_filter_delete(lighting);
    return 0;
}
