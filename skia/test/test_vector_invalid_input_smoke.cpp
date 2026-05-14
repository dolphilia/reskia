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
    bool ok = true;

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
    const sk_v2_t v2_null_negate = SkV2_negate(nullptr);
    if (!check(static_sk_v2_get_ptr(v2_null_negate) != nullptr, "SkV2_negate(nullptr)")) {
        return 4;
    }
    static_sk_v2_delete(v2_null_negate);
    SkV2_addAssign(nullptr, 0);
    SkV2_subtractAssign(nullptr, 0);
    SkV2_multiplyAssign(nullptr, 0);
    SkV2_multiplyScalarAssign(nullptr, 2.0f);
    SkV2_divideScalarAssign(nullptr, 2.0f);

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
    const sk_v3_t v3_null_negate = SkV3_negate(nullptr);
    if (!check(static_sk_v3_get_ptr(v3_null_negate) != nullptr, "SkV3_negate(nullptr)")) {
        return 10;
    }
    static_sk_v3_delete(v3_null_negate);
    SkV3_addAssign(nullptr, nullptr);
    SkV3_subtractAssign(nullptr, nullptr);
    SkV3_multiplyAssign(nullptr, nullptr);
    SkV3_multiplyScalarAssign(nullptr, 2.0f);

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
    const sk_v4_t v4_null_negate = SkV4_negate(nullptr);
    if (!check(static_sk_v4_get_ptr(v4_null_negate) != nullptr, "SkV4_negate(nullptr)")) {
        return 14;
    }
    static_sk_v4_delete(v4_null_negate);

    const sk_v2_t v2_handle = static_sk_v2_make({3.0f, 4.0f});
    const sk_v2_t v2_other_handle = static_sk_v2_make({1.0f, 2.0f});
    auto *v2 = static_cast<reskia_v2_t *>(static_sk_v2_get_ptr(v2_handle));
    auto *v2_other = static_cast<reskia_v2_t *>(static_sk_v2_get_ptr(v2_other_handle));
    if (!check(v2 != nullptr && SkV2_length(v2) == 5.0f, "SkV2 length valid")) {
        static_sk_v2_delete(v2_other_handle);
        static_sk_v2_delete(v2_handle);
        return 15;
    }
    const float *v2_ptr = SkV2_ptr(v2);
    if (!check(v2_ptr != nullptr && v2_ptr[0] == 3.0f && v2_ptr[1] == 4.0f, "SkV2 ptr valid")) {
        static_sk_v2_delete(v2_other_handle);
        static_sk_v2_delete(v2_handle);
        return 16;
    }
    float *v2_mut = SkV2_ptrMutable(v2);
    if (!check(v2_mut != nullptr, "SkV2 ptrMutable valid")) {
        static_sk_v2_delete(v2_other_handle);
        static_sk_v2_delete(v2_handle);
        return 17;
    }
    v2_mut[0] = 6.0f;
    if (!check(SkV2_ptr(v2)[0] == 6.0f, "SkV2 ptrMutable write")) {
        static_sk_v2_delete(v2_other_handle);
        static_sk_v2_delete(v2_handle);
        return 18;
    }
    if (!check(v2_other != nullptr && SkV2_equals(v2_other, v2_other_handle), "SkV2_equals valid")) {
        static_sk_v2_delete(v2_other_handle);
        static_sk_v2_delete(v2_handle);
        return 18;
    }
    const sk_v2_t v2_sum = SkV2_add(v2, v2_other_handle);
    const sk_v2_t v2_diff = SkV2_subtract(v2, v2_other_handle);
    const sk_v2_t v2_product = SkV2_multiply(v2, v2_other_handle);
    const sk_v2_t v2_neg = SkV2_negate(v2_other);
    ok &= check(static_sk_v2_get_ptr(v2_sum) != nullptr && static_sk_v2_get_entity(v2_sum).x == 7.0f, "SkV2_add valid");
    ok &= check(static_sk_v2_get_ptr(v2_diff) != nullptr && static_sk_v2_get_entity(v2_diff).y == 2.0f, "SkV2_subtract valid");
    ok &= check(static_sk_v2_get_ptr(v2_product) != nullptr && static_sk_v2_get_entity(v2_product).x == 6.0f, "SkV2_multiply valid");
    ok &= check(static_sk_v2_get_ptr(v2_neg) != nullptr && static_sk_v2_get_entity(v2_neg).x == -1.0f, "SkV2_negate valid");
    SkV2_addAssign(v2, v2_other_handle);
    SkV2_subtractAssign(v2, v2_other_handle);
    SkV2_multiplyScalarAssign(v2, 2.0f);
    SkV2_divideScalarAssign(v2, 2.0f);
    ok &= check(SkV2_ptr(v2)[0] == 6.0f, "SkV2 assign ops valid");
    static_sk_v2_delete(v2_neg);
    static_sk_v2_delete(v2_product);
    static_sk_v2_delete(v2_diff);
    static_sk_v2_delete(v2_sum);
    static_sk_v2_delete(v2_other_handle);
    static_sk_v2_delete(v2_handle);
    if (!ok) {
        return 18;
    }

    const sk_v3_t v3_handle = static_sk_v3_make({1.0f, 0.0f, 0.0f});
    const sk_v3_t v3_other_handle = static_sk_v3_make({0.0f, 1.0f, 0.0f});
    auto *v3 = static_cast<reskia_v3_t *>(static_sk_v3_get_ptr(v3_handle));
    auto *v3_other = static_cast<const reskia_v3_t *>(static_sk_v3_get_ptr(v3_other_handle));
    if (!check(v3 != nullptr && v3_other != nullptr && SkV3_dot(v3, v3_other) == 0.0f, "SkV3 dot valid")) {
        static_sk_v3_delete(v3_other_handle);
        static_sk_v3_delete(v3_handle);
        return 19;
    }
    if (!check(SkV3_equals(v3, v3) && SkV3_notEquals(v3, v3_other), "SkV3 equality valid")) {
        static_sk_v3_delete(v3_other_handle);
        static_sk_v3_delete(v3_handle);
        return 19;
    }
    const sk_v3_t v3_sum = SkV3_add(v3, v3_other);
    const sk_v3_t v3_diff = SkV3_subtract(v3, v3_other);
    const sk_v3_t v3_product = SkV3_multiply(v3, v3_other);
    const sk_v3_t v3_neg = SkV3_negate(v3);
    ok &= check(static_sk_v3_get_entity(v3_sum).x == 1.0f && static_sk_v3_get_entity(v3_sum).y == 1.0f, "SkV3_add valid");
    ok &= check(static_sk_v3_get_entity(v3_diff).y == -1.0f, "SkV3_subtract valid");
    ok &= check(static_sk_v3_get_entity(v3_product).x == 0.0f, "SkV3_multiply valid");
    ok &= check(static_sk_v3_get_entity(v3_neg).x == -1.0f, "SkV3_negate valid");
    SkV3_addAssign(v3, v3_other);
    SkV3_subtractAssign(v3, v3_other);
    SkV3_multiplyScalarAssign(v3, 2.0f);
    ok &= check(SkV3_ptr(v3)[0] == 2.0f, "SkV3 assign ops valid");
    static_sk_v3_delete(v3_neg);
    static_sk_v3_delete(v3_product);
    static_sk_v3_delete(v3_diff);
    static_sk_v3_delete(v3_sum);
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

    const sk_v4_t v4_a_handle = static_sk_v4_make({1.0f, 2.0f, 3.0f, 4.0f});
    const sk_v4_t v4_b_handle = static_sk_v4_make({2.0f, 3.0f, 4.0f, 5.0f});
    auto *v4_a = static_cast<reskia_v4_t *>(static_sk_v4_get_ptr(v4_a_handle));
    auto *v4_b = static_cast<reskia_v4_t *>(static_sk_v4_get_ptr(v4_b_handle));
    ok &= check(SkV4_equals(v4_a, v4_a) && SkV4_notEquals(v4_a, v4_b), "SkV4 equality valid");
    const sk_v4_t v4_sum = SkV4_add(v4_a, v4_b);
    const sk_v4_t v4_diff = SkV4_subtract(v4_b, v4_a);
    const sk_v4_t v4_product = SkV4_multiply(v4_a, v4_b);
    const sk_v4_t v4_neg = SkV4_negate(v4_a);
    ok &= check(static_sk_v4_get_entity(v4_sum).w == 9.0f, "SkV4_add valid");
    ok &= check(static_sk_v4_get_entity(v4_diff).x == 1.0f, "SkV4_subtract valid");
    ok &= check(static_sk_v4_get_entity(v4_product).z == 12.0f, "SkV4_multiply valid");
    ok &= check(static_sk_v4_get_entity(v4_neg).w == -4.0f, "SkV4_negate valid");
    static_sk_v4_delete(v4_neg);
    static_sk_v4_delete(v4_product);
    static_sk_v4_delete(v4_diff);
    static_sk_v4_delete(v4_sum);
    static_sk_v4_delete(v4_b_handle);
    static_sk_v4_delete(v4_a_handle);
    if (!ok) {
        return 23;
    }

    return 0;
}
