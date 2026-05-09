#include "capi/sk_color_table.h"
#include "handles/static_sk_color_table.h"

#include <cstdio>
#include <cstdint>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[color-table-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkColorTable_release(nullptr);
    SkColorTable_ref(nullptr);
    SkColorTable_unref(nullptr);
    SkColorTable_flatten(nullptr, nullptr);

    if (!check(SkColorTable_alphaTable(nullptr) == nullptr, "SkColorTable_alphaTable(nullptr)")) {
        return 1;
    }
    if (!check(SkColorTable_redTable(nullptr) == nullptr, "SkColorTable_redTable(nullptr)")) {
        return 2;
    }
    if (!check(SkColorTable_greenTable(nullptr) == nullptr, "SkColorTable_greenTable(nullptr)")) {
        return 3;
    }
    if (!check(SkColorTable_blueTable(nullptr) == nullptr, "SkColorTable_blueTable(nullptr)")) {
        return 4;
    }
    if (!check(!SkColorTable_unique(nullptr), "SkColorTable_unique(nullptr)")) {
        return 5;
    }
    if (!check(SkColorTable_Make(nullptr) == 0, "SkColorTable_Make(nullptr)")) {
        return 6;
    }
    if (!check(SkColorTable_Deserialize(nullptr) == 0, "SkColorTable_Deserialize(nullptr)")) {
        return 7;
    }

    uint8_t table[256] = {};
    for (int i = 0; i < 256; ++i) {
        table[i] = static_cast<uint8_t>(255 - i);
    }
    const sk_color_table_t handle = SkColorTable_Make(table);
    auto *color_table = static_cast<reskia_color_table_t *>(static_sk_color_table_get_ptr(handle));
    if (!check(color_table != nullptr, "SkColorTable_Make(valid)")) {
        return 8;
    }
    const uint8_t *alpha = SkColorTable_alphaTable(color_table);
    const uint8_t *red = SkColorTable_redTable(color_table);
    if (!check(alpha != nullptr && red != nullptr, "SkColorTable borrowed tables")) {
        static_sk_color_table_delete(handle);
        return 9;
    }
    if (!check(alpha[0] == 255 && alpha[255] == 0 && red[0] == 255, "SkColorTable table contents")) {
        static_sk_color_table_delete(handle);
        return 10;
    }

    if (!check(SkColorTable_MakeARGBTables(nullptr, nullptr, nullptr, nullptr) == 0, "SkColorTable_MakeARGBTables(nullptrs)")) {
        static_sk_color_table_delete(handle);
        return 11;
    }
    const sk_color_table_t alpha_handle = SkColorTable_MakeARGBTables(table, nullptr, nullptr, nullptr);
    auto *alpha_table = static_cast<reskia_color_table_t *>(static_sk_color_table_get_ptr(alpha_handle));
    if (!check(alpha_table != nullptr, "SkColorTable_MakeARGBTables(alpha)")) {
        static_sk_color_table_delete(handle);
        return 12;
    }
    const uint8_t *argb_alpha = SkColorTable_alphaTable(alpha_table);
    const uint8_t *argb_red = SkColorTable_redTable(alpha_table);
    if (!check(argb_alpha != nullptr && argb_red != nullptr, "SkColorTable ARGB borrowed tables")) {
        static_sk_color_table_delete(alpha_handle);
        static_sk_color_table_delete(handle);
        return 13;
    }
    if (!check(argb_alpha[0] == 255 && argb_alpha[255] == 0 && argb_red[0] == 0 && argb_red[255] == 255, "SkColorTable ARGB table contents")) {
        static_sk_color_table_delete(alpha_handle);
        static_sk_color_table_delete(handle);
        return 14;
    }

    static_sk_color_table_delete(alpha_handle);
    static_sk_color_table_delete(handle);
    return 0;
}
