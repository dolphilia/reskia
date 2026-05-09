#include "capi/sk_data_table.h"
#include "handles/static_sk_data_table.h"

#include <cstdio>
#include <cstring>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[data-table-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkDataTable_release(nullptr);
    SkDataTable_ref(nullptr);
    SkDataTable_unref(nullptr);

    if (!check(SkDataTable_isEmpty(nullptr), "SkDataTable_isEmpty(nullptr)")) {
        return 1;
    }
    if (!check(SkDataTable_count(nullptr) == 0, "SkDataTable_count(nullptr)")) {
        return 2;
    }
    if (!check(SkDataTable_atSize(nullptr, 0) == 0, "SkDataTable_atSize(nullptr)")) {
        return 3;
    }
    size_t size = 123;
    if (!check(SkDataTable_at(nullptr, 0, &size) == nullptr && size == 0, "SkDataTable_at(nullptr)")) {
        return 4;
    }
    if (!check(SkDataTable_atStr(nullptr, 0) == nullptr, "SkDataTable_atStr(nullptr)")) {
        return 5;
    }
    if (!check(!SkDataTable_unique(nullptr), "SkDataTable_unique(nullptr)")) {
        return 6;
    }
    if (!check(SkDataTable_MakeCopyArrays(nullptr, nullptr, 1) == 0, "SkDataTable_MakeCopyArrays(nullptr, 1)")) {
        return 7;
    }
    if (!check(SkDataTable_MakeCopyArray(nullptr, 1, 1) == 0, "SkDataTable_MakeCopyArray(nullptr, 1)")) {
        return 8;
    }
    if (!check(SkDataTable_MakeCopyArray(nullptr, 0, 1) == 0, "SkDataTable_MakeCopyArray(nullptr, elem 0)")) {
        return 9;
    }
    if (!check(SkDataTable_MakeArrayProc(nullptr, 1, 1, nullptr, nullptr) == 0, "SkDataTable_MakeArrayProc(nullptr, 1)")) {
        return 10;
    }

    const sk_data_table_t empty_handle = SkDataTable_MakeCopyArray(nullptr, 1, 0);
    auto *empty = static_cast<reskia_data_table_t *>(static_sk_data_table_get_ptr(empty_handle));
    if (!check(empty != nullptr && SkDataTable_isEmpty(empty), "SkDataTable_MakeCopyArray(nullptr, 0)")) {
        static_sk_data_table_delete(empty_handle);
        return 11;
    }

    const uint8_t bytes[] = {1, 2, 3, 4};
    const sk_data_table_t table_handle = SkDataTable_MakeCopyArray(bytes, 2, 2);
    auto *table = static_cast<reskia_data_table_t *>(static_sk_data_table_get_ptr(table_handle));
    if (!check(table != nullptr, "SkDataTable_MakeCopyArray(valid)")) {
        static_sk_data_table_delete(empty_handle);
        return 12;
    }
    if (!check(SkDataTable_count(table) == 2, "SkDataTable_count(valid)")) {
        static_sk_data_table_delete(table_handle);
        static_sk_data_table_delete(empty_handle);
        return 13;
    }
    if (!check(SkDataTable_atSize(table, 1) == 2, "SkDataTable_atSize(valid)")) {
        static_sk_data_table_delete(table_handle);
        static_sk_data_table_delete(empty_handle);
        return 14;
    }
    const uint8_t *entry = SkDataTable_at(table, 1, &size);
    if (!check(entry != nullptr && size == 2 && entry[0] == 3 && entry[1] == 4, "SkDataTable_at(valid)")) {
        static_sk_data_table_delete(table_handle);
        static_sk_data_table_delete(empty_handle);
        return 15;
    }
    size = 123;
    if (!check(SkDataTable_at(table, 2, &size) == nullptr && size == 0, "SkDataTable_at(out of range)")) {
        static_sk_data_table_delete(table_handle);
        static_sk_data_table_delete(empty_handle);
        return 16;
    }

    const uint8_t str0[] = "one";
    const uint8_t str1[] = "two";
    const uint8_t *ptrs[] = {str0, str1};
    const size_t sizes[] = {sizeof(str0), sizeof(str1)};
    const sk_data_table_t strings_handle = SkDataTable_MakeCopyArrays(ptrs, sizes, 2);
    auto *strings = static_cast<reskia_data_table_t *>(static_sk_data_table_get_ptr(strings_handle));
    if (!check(strings != nullptr, "SkDataTable_MakeCopyArrays(valid)")) {
        static_sk_data_table_delete(table_handle);
        static_sk_data_table_delete(empty_handle);
        return 17;
    }
    if (!check(std::strcmp(SkDataTable_atStr(strings, 1), "two") == 0, "SkDataTable_atStr(valid)")) {
        static_sk_data_table_delete(strings_handle);
        static_sk_data_table_delete(table_handle);
        static_sk_data_table_delete(empty_handle);
        return 18;
    }

    static_sk_data_table_delete(strings_handle);
    static_sk_data_table_delete(table_handle);
    static_sk_data_table_delete(empty_handle);
    return 0;
}
