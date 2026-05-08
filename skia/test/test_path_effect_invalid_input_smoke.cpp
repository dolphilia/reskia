#include "capi/sk_corner_path_effect.h"
#include "capi/sk_dash_path_effect.h"
#include "capi/sk_discrete_path_effect.h"
#include "capi/sk_line_2d_path_effect.h"
#include "capi/sk_path_1d_path_effect.h"
#include "capi/sk_path_2d_path_effect.h"
#include "capi/sk_path_effect.h"
#include "capi/sk_trim_path_effect.h"
#include "handles/static_sk_data.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[path-effect-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkPathEffect_release(nullptr);
    SkPathEffect_ref(nullptr);
    SkPathEffect_unref(nullptr);
    SkDashPathEffect_delete(nullptr);
    SkCornerPathEffect_delete(nullptr);
    SkTrimPathEffect_delete(nullptr);

    if (!check(SkPathEffect_asADash(nullptr, nullptr) == 0, "SkPathEffect_asADash(nullptr)")) {
        return 1;
    }
    if (!check(!SkPathEffect_filterPath(nullptr, nullptr, nullptr, nullptr, nullptr), "SkPathEffect_filterPath(nullptr)")) {
        return 2;
    }
    if (!check(!SkPathEffect_filterPathWithCTM(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr), "SkPathEffect_filterPathWithCTM(nullptr)")) {
        return 3;
    }
    if (!check(!SkPathEffect_needsCTM(nullptr), "SkPathEffect_needsCTM(nullptr)")) {
        return 4;
    }
    if (!check(SkPathEffect_getFactory(nullptr) == 0, "SkPathEffect_getFactory(nullptr)")) {
        return 5;
    }
    if (!check(SkPathEffect_getTypeName(nullptr) == nullptr, "SkPathEffect_getTypeName(nullptr)")) {
        return 6;
    }
    SkPathEffect_flatten(nullptr, nullptr);
    if (!check(SkPathEffect_getFlattenableType(nullptr) == 0, "SkPathEffect_getFlattenableType(nullptr)")) {
        return 7;
    }
    if (!check(SkPathEffect_serialize(nullptr, nullptr) == 0, "SkPathEffect_serialize(nullptr)")) {
        return 8;
    }
    if (!check(SkPathEffect_serializeToMemory(nullptr, nullptr, 0, nullptr) == 0, "SkPathEffect_serializeToMemory(nullptr)")) {
        return 9;
    }
    if (!check(!SkPathEffect_unique(nullptr), "SkPathEffect_unique(nullptr)")) {
        return 10;
    }
    if (!check(SkPathEffect_MakeSum(0, 0) == 0, "SkPathEffect_MakeSum(0, 0)")) {
        return 11;
    }
    if (!check(SkPathEffect_MakeCompose(0, 0) == 0, "SkPathEffect_MakeCompose(0, 0)")) {
        return 12;
    }
    if (!check(SkPathEffect_Deserialize(nullptr, 0, nullptr) == 0, "SkPathEffect_Deserialize(nullptr)")) {
        return 13;
    }
    if (!check(SkPathEffect_NameToFactory(nullptr) == 0, "SkPathEffect_NameToFactory(nullptr)")) {
        return 14;
    }
    if (!check(SkPathEffect_FactoryToName(0) == nullptr, "SkPathEffect_FactoryToName(0)")) {
        return 15;
    }
    SkPathEffect_Register(nullptr, 0);

    if (!check(SkDashPathEffect_Make(nullptr, 2, 0.0f) == 0, "SkDashPathEffect_Make(nullptr)")) {
        return 16;
    }
    if (!check(SkDashPathEffect_Make(nullptr, 0, 0.0f) == 0, "SkDashPathEffect_Make(nullptr, 0)")) {
        return 17;
    }
    if (!check(SkLine2DPathEffect_Make(1.0f, nullptr) == 0, "SkLine2DPathEffect_Make(nullptr)")) {
        return 18;
    }
    if (!check(SkPath1DPathEffect_Make(nullptr, 1.0f, 0.0f, 0) == 0, "SkPath1DPathEffect_Make(nullptr)")) {
        return 19;
    }
    if (!check(SkPath2DPathEffect_Make(nullptr, nullptr) == 0, "SkPath2DPathEffect_Make(nullptr)")) {
        return 20;
    }

    const float intervals[] = {4.0f, 2.0f};
    const sk_path_effect_t dash = SkDashPathEffect_Make(intervals, 2, 0.0f);
    auto *dash_effect = static_cast<reskia_path_effect_t *>(static_sk_path_effect_get_ptr(dash));
    if (!check(dash_effect != nullptr, "SkDashPathEffect_Make(valid)")) {
        return 21;
    }
    const sk_data_t serialized = SkPathEffect_serialize(dash_effect, nullptr);
    if (!check(serialized != 0, "SkPathEffect_serialize(valid)")) {
        static_sk_path_effect_delete(dash);
        return 22;
    }
    static_sk_data_delete(serialized);

    const sk_path_effect_t corner = SkCornerPathEffect_Make(4.0f);
    auto *corner_effect = static_cast<reskia_path_effect_t *>(static_sk_path_effect_get_ptr(corner));
    if (!check(corner_effect != nullptr, "SkCornerPathEffect_Make(valid)")) {
        static_sk_path_effect_delete(dash);
        return 23;
    }
    const sk_path_effect_t sum = SkPathEffect_MakeSum(dash, corner);
    if (!check(sum != 0, "SkPathEffect_MakeSum(valid)")) {
        static_sk_path_effect_delete(corner);
        static_sk_path_effect_delete(dash);
        return 24;
    }
    const sk_path_effect_t composed = SkPathEffect_MakeCompose(corner, dash);
    if (!check(composed != 0, "SkPathEffect_MakeCompose(valid)")) {
        static_sk_path_effect_delete(corner);
        static_sk_path_effect_delete(dash);
        return 25;
    }

    static_sk_path_effect_delete(composed);
    static_sk_path_effect_delete(sum);
    static_sk_path_effect_delete(corner);
    static_sk_path_effect_delete(dash);
    return 0;
}
