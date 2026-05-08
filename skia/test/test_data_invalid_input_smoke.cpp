#include "capi/sk_data.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[data-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    if (!check(SkData_size(nullptr) == 0, "SkData_size(nullptr)")) {
        return 1;
    }
    if (!check(SkData_isEmpty(nullptr), "SkData_isEmpty(nullptr)")) {
        return 2;
    }
    if (!check(SkData_data(nullptr) == nullptr, "SkData_data(nullptr)")) {
        return 3;
    }
    if (!check(SkData_writable_data(nullptr) == nullptr, "SkData_writable_data(nullptr)")) {
        return 4;
    }
    if (!check(SkData_copyRange(nullptr, 0, 4, nullptr) == 0, "SkData_copyRange(nullptr)")) {
        return 5;
    }
    if (!check(!SkData_equals(nullptr, nullptr), "SkData_equals(nullptr)")) {
        return 6;
    }
    if (!check(!SkData_unique(nullptr), "SkData_unique(nullptr)")) {
        return 7;
    }
    if (!check(!SkData_refCntGreaterThan(nullptr, 0), "SkData_refCntGreaterThan(nullptr)")) {
        return 8;
    }
    if (!check(SkData_MakeWithCopy(nullptr, 1) == 0, "SkData_MakeWithCopy(nullptr, 1)")) {
        return 9;
    }
    if (!check(SkData_MakeWithProc(nullptr, 1, nullptr, nullptr) == 0, "SkData_MakeWithProc(nullptr, 1)")) {
        return 10;
    }
    if (!check(SkData_MakeWithoutCopy(nullptr, 1) == 0, "SkData_MakeWithoutCopy(nullptr, 1)")) {
        return 11;
    }
    if (!check(SkData_MakeFromMalloc(nullptr, 1) == 0, "SkData_MakeFromMalloc(nullptr, 1)")) {
        return 12;
    }
    if (!check(SkData_MakeFromFileName(nullptr) == 0, "SkData_MakeFromFileName(nullptr)")) {
        return 13;
    }
    if (!check(SkData_MakeFromFILE(nullptr) == 0, "SkData_MakeFromFILE(nullptr)")) {
        return 14;
    }
    if (!check(SkData_MakeFromStream(nullptr, 1) == 0, "SkData_MakeFromStream(nullptr, 1)")) {
        return 15;
    }
    if (!check(SkData_MakeSubset(nullptr, 0, 0) == 0, "SkData_MakeSubset(nullptr)")) {
        return 16;
    }

    SkData_release(nullptr);
    SkData_ref(nullptr);
    SkData_unref(nullptr);
    SkData_deref(nullptr);

    const uint8_t bytes[] = {1, 2, 3, 4};
    const sk_data_t handle = SkData_MakeWithCopy(bytes, sizeof(bytes));
    auto *data = static_cast<reskia_data_t *>(static_sk_data_get_ptr(handle));
    if (!check(data != nullptr, "SkData_MakeWithCopy")) {
        return 17;
    }
    if (!check(SkData_size(data) == sizeof(bytes), "SkData_size(data)")) {
        static_sk_data_delete(handle);
        return 18;
    }
    if (!check(SkData_copyRange(data, 1, 2, nullptr) == 2, "SkData_copyRange(data, null buffer)")) {
        static_sk_data_delete(handle);
        return 19;
    }
    uint8_t copied[2] = {};
    if (!check(SkData_copyRange(data, 1, sizeof(copied), copied) == sizeof(copied), "SkData_copyRange(data, buffer)")) {
        static_sk_data_delete(handle);
        return 20;
    }
    if (!check(copied[0] == 2 && copied[1] == 3, "SkData_copyRange contents")) {
        static_sk_data_delete(handle);
        return 21;
    }
    if (!check(SkData_equals(data, data), "SkData_equals(data, data)")) {
        static_sk_data_delete(handle);
        return 22;
    }

    const sk_data_t empty_from_copy = SkData_MakeWithCopy(nullptr, 0);
    auto *empty = static_cast<reskia_data_t *>(static_sk_data_get_ptr(empty_from_copy));
    if (!check(empty != nullptr && SkData_isEmpty(empty), "SkData_MakeWithCopy(nullptr, 0)")) {
        static_sk_data_delete(empty_from_copy);
        static_sk_data_delete(handle);
        return 23;
    }

    const sk_data_t empty_from_stream = SkData_MakeFromStream(nullptr, 0);
    auto *stream_empty = static_cast<reskia_data_t *>(static_sk_data_get_ptr(empty_from_stream));
    if (!check(stream_empty != nullptr && SkData_isEmpty(stream_empty), "SkData_MakeFromStream(nullptr, 0)")) {
        static_sk_data_delete(empty_from_stream);
        static_sk_data_delete(empty_from_copy);
        static_sk_data_delete(handle);
        return 24;
    }

    static_sk_data_delete(empty_from_stream);
    static_sk_data_delete(empty_from_copy);
    static_sk_data_delete(handle);
    return 0;
}
