#include "capi/sk_color_4f.h"
#include "capi/sk_color_filter.h"
#include "capi/sk_color_filters.h"
#include "handles/static_sk_color_4f.h"
#include "handles/static_sk_color_filter.h"
#include "handles/static_sk_data.h"

#include <cstdio>
#include <cstdint>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[color-filter-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkColorFilter_release(nullptr);
    SkColorFilter_ref(nullptr);
    SkColorFilter_unref(nullptr);

    reskia_color_t color = 0;
    int mode = 0;
    if (!check(!SkColorFilter_asAColorMode(nullptr, &color, &mode), "SkColorFilter_asAColorMode(nullptr)")) {
        return 1;
    }
    if (!check(!SkColorFilter_asAColorMatrix(nullptr, nullptr), "SkColorFilter_asAColorMatrix(nullptr)")) {
        return 2;
    }
    if (!check(!SkColorFilter_isAlphaUnchanged(nullptr), "SkColorFilter_isAlphaUnchanged(nullptr)")) {
        return 3;
    }
    if (!check(SkColorFilter_filterColor(nullptr, 0x11223344) == 0x11223344, "SkColorFilter_filterColor(nullptr)")) {
        return 4;
    }
    if (!check(SkColorFilter_filterColor4f(nullptr, nullptr, nullptr, nullptr) == 0, "SkColorFilter_filterColor4f(nullptr)")) {
        return 5;
    }
    if (!check(SkColorFilter_makeComposed(nullptr, 0) == 0, "SkColorFilter_makeComposed(nullptr)")) {
        return 6;
    }
    if (!check(SkColorFilter_makeWithWorkingColorSpace(nullptr, 0) == 0, "SkColorFilter_makeWithWorkingColorSpace(nullptr)")) {
        return 7;
    }
    if (!check(SkColorFilter_getFactory(nullptr) == 0, "SkColorFilter_getFactory(nullptr)")) {
        return 8;
    }
    if (!check(SkColorFilter_getTypeName(nullptr) == nullptr, "SkColorFilter_getTypeName(nullptr)")) {
        return 9;
    }
    SkColorFilter_flatten(nullptr, nullptr);
    if (!check(SkColorFilter_getFlattenableType(nullptr) == 0, "SkColorFilter_getFlattenableType(nullptr)")) {
        return 10;
    }
    if (!check(SkColorFilter_serialize(nullptr, nullptr) == 0, "SkColorFilter_serialize(nullptr)")) {
        return 11;
    }
    if (!check(SkColorFilter_serializeToMemory(nullptr, nullptr, 0, nullptr) == 0, "SkColorFilter_serializeToMemory(nullptr)")) {
        return 12;
    }
    if (!check(!SkColorFilter_unique(nullptr), "SkColorFilter_unique(nullptr)")) {
        return 13;
    }
    if (!check(SkColorFilter_Deserialize(nullptr, 0, nullptr) == 0, "SkColorFilter_Deserialize(nullptr)")) {
        return 14;
    }
    if (!check(SkColorFilter_NameToFactory(nullptr) == 0, "SkColorFilter_NameToFactory(nullptr)")) {
        return 15;
    }
    if (!check(SkColorFilter_FactoryToName(0) == nullptr, "SkColorFilter_FactoryToName(0)")) {
        return 16;
    }
    SkColorFilter_Register(nullptr, 0);

    if (!check(SkColorFilters_Blend(nullptr, 0, 3) == 0, "SkColorFilters_Blend(nullptr)")) {
        return 17;
    }
    if (!check(SkColorFilters_Compose(0, 0) == 0, "SkColorFilters_Compose(0, 0)")) {
        return 18;
    }
    if (!check(SkColorFilters_HSLAMatrix(nullptr) == 0, "SkColorFilters_HSLAMatrix(nullptr)")) {
        return 19;
    }
    if (!check(SkColorFilters_HSLAMatrixFromMatrix(nullptr) == 0, "SkColorFilters_HSLAMatrixFromMatrix(nullptr)")) {
        return 20;
    }
    if (!check(SkColorFilters_Lerp(0.5f, 0, 0) == 0, "SkColorFilters_Lerp(0, 0)")) {
        return 21;
    }
    if (!check(SkColorFilters_Matrix(nullptr) == 0, "SkColorFilters_Matrix(nullptr)")) {
        return 22;
    }
    if (!check(SkColorFilters_MatrixFromMatrix(nullptr) == 0, "SkColorFilters_MatrixFromMatrix(nullptr)")) {
        return 23;
    }
    if (!check(SkColorFilters_Table(nullptr) == 0, "SkColorFilters_Table(nullptr)")) {
        return 24;
    }
    if (!check(SkColorFilters_TableFromColorTable(0) == 0, "SkColorFilters_TableFromColorTable(0)")) {
        return 25;
    }

    const sk_color_filter_t blend = SkColorFilters_BlendColor(0xff00ff00, 3);
    auto *blend_filter = static_cast<reskia_color_filter_t *>(static_sk_color_filter_get_ptr(blend));
    if (!check(blend_filter != nullptr, "SkColorFilters_BlendColor(valid)")) {
        return 26;
    }
    const sk_data_t serialized = SkColorFilter_serialize(blend_filter, nullptr);
    if (!check(serialized != 0, "SkColorFilter_serialize(valid)")) {
        static_sk_color_filter_delete(blend);
        return 27;
    }
    static_sk_data_delete(serialized);

    const sk_color_filter_t composed = SkColorFilter_makeComposed(blend_filter, 0);
    if (!check(composed != 0, "SkColorFilter_makeComposed(valid, 0)")) {
        static_sk_color_filter_delete(blend);
        return 28;
    }

    const sk_color_4f_t src_color_handle = SkColor4f_FromColor(0xff112233);
    auto *src_color = static_cast<reskia_color_4f_t *>(static_sk_color_4f_get_ptr(src_color_handle));
    if (!check(src_color != nullptr, "SkColor4f_FromColor")) {
        static_sk_color_filter_delete(composed);
        static_sk_color_filter_delete(blend);
        return 29;
    }
    const sk_color_4f_t filtered = SkColorFilter_filterColor4f(blend_filter, src_color, nullptr, nullptr);
    if (!check(filtered != 0, "SkColorFilter_filterColor4f(valid)")) {
        static_sk_color_4f_delete(src_color_handle);
        static_sk_color_filter_delete(composed);
        static_sk_color_filter_delete(blend);
        return 30;
    }

    float identity[20] = {
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    };
    const sk_color_filter_t matrix = SkColorFilters_Matrix(identity);
    if (!check(matrix != 0, "SkColorFilters_Matrix(valid)")) {
        static_sk_color_4f_delete(filtered);
        static_sk_color_4f_delete(src_color_handle);
        static_sk_color_filter_delete(composed);
        static_sk_color_filter_delete(blend);
        return 31;
    }

    static_sk_color_filter_delete(matrix);
    static_sk_color_4f_delete(filtered);
    static_sk_color_4f_delete(src_color_handle);
    static_sk_color_filter_delete(composed);
    static_sk_color_filter_delete(blend);
    return 0;
}
