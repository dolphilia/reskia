#include "capi/sk_v2.h"
#include "capi/sk_v3.h"
#include "capi/sk_v4.h"
#include "handles/static_sk_v2.h"
#include "handles/static_sk_v2-internal.h"
#include "handles/static_sk_v3.h"
#include "handles/static_sk_v3-internal.h"
#include "handles/static_sk_v4.h"
#include "handles/static_sk_v4-internal.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[vector-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkV2_delete(nullptr);
    SkV3_delete(nullptr);
    SkV4_delete(nullptr);

    if (!check(SkV2_lengthSquared(nullptr) == 0.0f && SkV2_length(nullptr) == 0.0f, "SkV2 length nullptr")) {
        return 1;
    }
    if (!check(SkV2_dot(nullptr, 0) == 0.0f && SkV2_cross(nullptr, 0) == 0.0f, "SkV2 operations nullptr")) {
        return 2;
    }
    const sk_v2_t v2_null_norm = SkV2_normalize(nullptr);
    if (!check(static_sk_v2_get_ptr(v2_null_norm) != nullptr, "SkV2_normalize(nullptr)")) {
        return 3;
    }
    static_sk_v2_delete(v2_null_norm);
    if (!check(SkV2_ptr(nullptr) == nullptr && SkV2_ptrMutable(nullptr) == nullptr, "SkV2 ptr nullptr")) {
        return 4;
    }

    if (!check(SkV3_lengthSquared(nullptr) == 0.0f && SkV3_length(nullptr) == 0.0f, "SkV3 length nullptr")) {
        return 5;
    }
    if (!check(SkV3_dot(nullptr, nullptr) == 0.0f && SkV3_Dot(nullptr, nullptr) == 0.0f, "SkV3 dot nullptr")) {
        return 6;
    }
    const sk_v3_t v3_null_cross = SkV3_cross(nullptr, nullptr);
    if (!check(static_sk_v3_get_ptr(v3_null_cross) != nullptr, "SkV3_cross(nullptr)")) {
        return 7;
    }
    static_sk_v3_delete(v3_null_cross);
    const sk_v3_t v3_static_null_cross = SkV3_Cross(nullptr, nullptr);
    if (!check(static_sk_v3_get_ptr(v3_static_null_cross) != nullptr, "SkV3_Cross(nullptr)")) {
        return 8;
    }
    static_sk_v3_delete(v3_static_null_cross);
    const sk_v3_t v3_null_norm = SkV3_Normalize(nullptr);
    if (!check(static_sk_v3_get_ptr(v3_null_norm) != nullptr, "SkV3_Normalize(nullptr)")) {
        return 9;
    }
    static_sk_v3_delete(v3_null_norm);
    if (!check(SkV3_ptr(nullptr) == nullptr && SkV3_ptrMutable(nullptr) == nullptr, "SkV3 ptr nullptr")) {
        return 10;
    }

    if (!check(SkV4_lengthSquared(nullptr) == 0.0f && SkV4_length(nullptr) == 0.0f, "SkV4 length nullptr")) {
        return 11;
    }
    if (!check(SkV4_dot(nullptr, nullptr) == 0.0f && SkV4_Dot(nullptr, nullptr) == 0.0f, "SkV4 dot nullptr")) {
        return 12;
    }
    const sk_v4_t v4_null_norm = SkV4_Normalize(nullptr);
    if (!check(static_sk_v4_get_ptr(v4_null_norm) != nullptr, "SkV4_Normalize(nullptr)")) {
        return 13;
    }
    static_sk_v4_delete(v4_null_norm);
    if (!check(SkV4_ptr(nullptr) == nullptr && SkV4_ptrMutable(nullptr) == nullptr, "SkV4 ptr nullptr")) {
        return 14;
    }

    const sk_v2_t v2_handle = static_sk_v2_make({3.0f, 4.0f});
    auto *v2 = static_cast<reskia_v2_t *>(static_sk_v2_get_ptr(v2_handle));
    if (!check(v2 != nullptr && SkV2_length(v2) == 5.0f, "SkV2 length valid")) {
        static_sk_v2_delete(v2_handle);
        return 15;
    }
    const float *v2_ptr = SkV2_ptr(v2);
    if (!check(v2_ptr != nullptr && v2_ptr[0] == 3.0f && v2_ptr[1] == 4.0f, "SkV2 ptr valid")) {
        static_sk_v2_delete(v2_handle);
        return 16;
    }
    float *v2_mut = SkV2_ptrMutable(v2);
    if (!check(v2_mut != nullptr, "SkV2 ptrMutable valid")) {
        static_sk_v2_delete(v2_handle);
        return 17;
    }
    v2_mut[0] = 6.0f;
    if (!check(SkV2_ptr(v2)[0] == 6.0f, "SkV2 ptrMutable write")) {
        static_sk_v2_delete(v2_handle);
        return 18;
    }
    static_sk_v2_delete(v2_handle);

    const sk_v3_t v3_handle = static_sk_v3_make({1.0f, 0.0f, 0.0f});
    const sk_v3_t v3_other_handle = static_sk_v3_make({0.0f, 1.0f, 0.0f});
    auto *v3 = static_cast<reskia_v3_t *>(static_sk_v3_get_ptr(v3_handle));
    auto *v3_other = static_cast<const reskia_v3_t *>(static_sk_v3_get_ptr(v3_other_handle));
    if (!check(v3 != nullptr && v3_other != nullptr && SkV3_dot(v3, v3_other) == 0.0f, "SkV3 dot valid")) {
        static_sk_v3_delete(v3_other_handle);
        static_sk_v3_delete(v3_handle);
        return 19;
    }
    const sk_v3_t cross = SkV3_cross(v3, v3_other);
    if (!check(static_sk_v3_get_ptr(cross) != nullptr, "SkV3 cross valid")) {
        static_sk_v3_delete(cross);
        static_sk_v3_delete(v3_other_handle);
        static_sk_v3_delete(v3_handle);
        return 20;
    }
    static_sk_v3_delete(cross);
    static_sk_v3_delete(v3_other_handle);
    static_sk_v3_delete(v3_handle);

    const sk_v4_t v4_handle = static_sk_v4_make({1.0f, 2.0f, 3.0f, 4.0f});
    auto *v4 = static_cast<reskia_v4_t *>(static_sk_v4_get_ptr(v4_handle));
    if (!check(v4 != nullptr && SkV4_lengthSquared(v4) == 30.0f, "SkV4 length valid")) {
        static_sk_v4_delete(v4_handle);
        return 21;
    }
    const float *v4_ptr = SkV4_ptr(v4);
    if (!check(v4_ptr != nullptr && v4_ptr[3] == 4.0f, "SkV4 ptr valid")) {
        static_sk_v4_delete(v4_handle);
        return 22;
    }
    static_sk_v4_delete(v4_handle);

    return 0;
}
