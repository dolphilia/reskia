#include "capi/sk_mask_filter.h"
#include "capi/sk_shader_mask_filter.h"
#include "capi/sk_table_mask_filter.h"
#include "handles/static_sk_mask_filter.h"

#include <cstdint>
#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[mask-filter-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkMaskFilter_release(nullptr);
    SkMaskFilter_ref(nullptr);
    SkMaskFilter_unref(nullptr);
    SkMaskFilter_flatten(nullptr, nullptr);
    SkMaskFilter_Register(nullptr, 0);
    SkTableMaskFilter_delete(nullptr);
    SkTableMaskFilter_MakeGammaTable(nullptr, 1.0f);
    SkTableMaskFilter_MakeClipTable(nullptr, 0, 255);
    SkShaderMaskFilter_delete(nullptr);

    if (!check(SkMaskFilter_getFactory(nullptr) == 0, "SkMaskFilter_getFactory(nullptr)")) {
        return 2;
    }
    if (!check(SkMaskFilter_getTypeName(nullptr) == nullptr, "SkMaskFilter_getTypeName(nullptr)")) {
        return 3;
    }
    if (!check(SkMaskFilter_getFlattenableType(nullptr) == -1, "SkMaskFilter_getFlattenableType(nullptr)")) {
        return 4;
    }
    if (!check(SkMaskFilter_serialize(nullptr, nullptr) == 0, "SkMaskFilter_serialize(nullptr)")) {
        return 5;
    }
    if (!check(SkMaskFilter_serializeToMemory(nullptr, nullptr, 0, nullptr) == 0, "SkMaskFilter_serializeToMemory(nullptr)")) {
        return 6;
    }
    if (!check(SkMaskFilter_serializeToMemory(nullptr, nullptr, 8, nullptr) == 0, "SkMaskFilter_serializeToMemory(nullptr memory)")) {
        return 7;
    }
    if (!check(!SkMaskFilter_unique(nullptr), "SkMaskFilter_unique(nullptr)")) {
        return 8;
    }
    if (!check(SkMaskFilter_Deserialize(nullptr, 8, nullptr) == 0, "SkMaskFilter_Deserialize(nullptr)")) {
        return 9;
    }
    if (!check(SkMaskFilter_Deserialize("x", 0, nullptr) == 0, "SkMaskFilter_Deserialize(empty)")) {
        return 10;
    }
    if (!check(SkMaskFilter_NameToFactory(nullptr) == 0, "SkMaskFilter_NameToFactory(nullptr)")) {
        return 11;
    }
    if (!check(SkMaskFilter_FactoryToName(0) == nullptr, "SkMaskFilter_FactoryToName(0)")) {
        return 12;
    }
    if (!check(SkShaderMaskFilter_Make(0) == 0, "SkShaderMaskFilter_Make(0)")) {
        return 13;
    }
    if (!check(SkTableMaskFilter_Create(nullptr) == nullptr, "SkTableMaskFilter_Create(nullptr)")) {
        return 14;
    }

    uint8_t table[256] = {};
    SkTableMaskFilter_MakeClipTable(table, 64, 192);
    if (!check(table[0] == 0 && table[63] == 0 && table[192] == 255 && table[255] == 255, "SkTableMaskFilter_MakeClipTable(valid)")) {
        return 15;
    }
    SkTableMaskFilter_MakeGammaTable(table, 1.0f);
    if (!check(table[0] == 0 && table[255] == 255, "SkTableMaskFilter_MakeGammaTable(valid)")) {
        return 16;
    }

    reskia_mask_filter_t *table_filter = SkTableMaskFilter_Create(table);
    if (!check(table_filter != nullptr, "SkTableMaskFilter_Create(valid)")) {
        return 17;
    }
    if (!check(SkMaskFilter_getTypeName(table_filter) != nullptr, "SkMaskFilter_getTypeName(valid)")) {
        SkMaskFilter_release(table_filter);
        return 18;
    }
    SkMaskFilter_release(table_filter);

    const sk_mask_filter_t blur = SkMaskFilter_MakeBlur(0, 1.0f, true);
    if (!check(blur != 0 && static_sk_mask_filter_get_ptr(blur) != nullptr, "SkMaskFilter_MakeBlur(valid)")) {
        return 19;
    }
    static_sk_mask_filter_delete(blur);

    return 0;
}
