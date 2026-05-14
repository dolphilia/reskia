//
// Created by dolphilia on 2024/01/11.
//

#include "sk_v3.h"

#include "include/core/SkM44.h"
#include "../handles/static_sk_v3.h"

#include "../handles/static_sk_v3-internal.h"

bool SkV3_Equal(const SkV3 &v1, const SkV3 &v2) {
    return v1 == v2;
}

bool SkV3_NotEqual(const SkV3 &v1, const SkV3 &v2) {
    return  v1 != v2;
}

SkV3 SkV3_Minus(const SkV3 &v1, const SkV3 &v2) {
    return v1 - v2;
}

SkV3 SkV3_Plus(const SkV3 &v1, const SkV3 &v2) {
    return v1 + v2;
}

SkV3 SkV3_Star(const SkV3 &v1, const SkV3 &v2) {
    return v1 * v2;
}

void SkV3_PlusAssign(SkV3 &v1, const SkV3 &v2) {
    v1 += v2;
}

void SkV3_MinusAssign(SkV3 &v1, const SkV3 &v2) {
    v1 -= v2;
}

void SkV3_StarAssign(SkV3 &v1, const SkV3 &v2) {
    v1 *= v2;
}

extern "C" {

bool SkV3_equals(reskia_v3_t *v3, const reskia_v3_t *v) {
    if (v3 == nullptr || v == nullptr) {
        return false;
    }
    return *reinterpret_cast<SkV3 *>(v3) == *reinterpret_cast<const SkV3 *>(v);
}

bool SkV3_notEquals(reskia_v3_t *v3, const reskia_v3_t *v) {
    if (v3 == nullptr || v == nullptr) {
        return false;
    }
    return *reinterpret_cast<SkV3 *>(v3) != *reinterpret_cast<const SkV3 *>(v);
}

sk_v3_t SkV3_negate(reskia_v3_t *v3) {
    if (v3 == nullptr) {
        return static_sk_v3_make({});
    }
    return static_sk_v3_make(-*reinterpret_cast<SkV3 *>(v3));
}

sk_v3_t SkV3_add(reskia_v3_t *v3, const reskia_v3_t *v) {
    if (v3 == nullptr || v == nullptr) {
        return static_sk_v3_make({});
    }
    return static_sk_v3_make(*reinterpret_cast<SkV3 *>(v3) + *reinterpret_cast<const SkV3 *>(v));
}

sk_v3_t SkV3_subtract(reskia_v3_t *v3, const reskia_v3_t *v) {
    if (v3 == nullptr || v == nullptr) {
        return static_sk_v3_make({});
    }
    return static_sk_v3_make(*reinterpret_cast<SkV3 *>(v3) - *reinterpret_cast<const SkV3 *>(v));
}

sk_v3_t SkV3_multiply(reskia_v3_t *v3, const reskia_v3_t *v) {
    if (v3 == nullptr || v == nullptr) {
        return static_sk_v3_make({});
    }
    return static_sk_v3_make(*reinterpret_cast<SkV3 *>(v3) * *reinterpret_cast<const SkV3 *>(v));
}

void SkV3_addAssign(reskia_v3_t *v3, const reskia_v3_t *v) {
    if (v3 == nullptr || v == nullptr) {
        return;
    }
    *reinterpret_cast<SkV3 *>(v3) += *reinterpret_cast<const SkV3 *>(v);
}

void SkV3_subtractAssign(reskia_v3_t *v3, const reskia_v3_t *v) {
    if (v3 == nullptr || v == nullptr) {
        return;
    }
    *reinterpret_cast<SkV3 *>(v3) -= *reinterpret_cast<const SkV3 *>(v);
}

void SkV3_multiplyAssign(reskia_v3_t *v3, const reskia_v3_t *v) {
    if (v3 == nullptr || v == nullptr) {
        return;
    }
    *reinterpret_cast<SkV3 *>(v3) *= *reinterpret_cast<const SkV3 *>(v);
}

void SkV3_multiplyScalarAssign(reskia_v3_t *v3, float s) {
    if (v3 == nullptr) {
        return;
    }
    *reinterpret_cast<SkV3 *>(v3) *= s;
}

void SkV3_delete(reskia_v3_t *v3) {
    if (v3 == nullptr) {
        return;
    }
    delete reinterpret_cast<SkV3 *>(v3);
}

float SkV3_lengthSquared(reskia_v3_t *v3) {
    if (v3 == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkV3 *>(v3)->lengthSquared();
}

float SkV3_length(reskia_v3_t *v3) {
    if (v3 == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkV3 *>(v3)->length();
}

float SkV3_dot(reskia_v3_t *v3, const reskia_v3_t *v) {
    if (v3 == nullptr || v == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkV3 *>(v3)->dot(* reinterpret_cast<const SkV3 *>(v));
}

sk_v3_t SkV3_cross(reskia_v3_t *v3, const reskia_v3_t *v) {
    if (v3 == nullptr || v == nullptr) {
        return static_sk_v3_make({});
    }
    return static_sk_v3_make(reinterpret_cast<SkV3 *>(v3)->cross(* reinterpret_cast<const SkV3 *>(v)));
}

sk_v3_t SkV3_normalize(reskia_v3_t *v3) {
    if (v3 == nullptr) {
        return static_sk_v3_make({});
    }
    return static_sk_v3_make(reinterpret_cast<SkV3 *>(v3)->normalize());
}

const float *SkV3_ptr(reskia_v3_t *v3) {
    if (v3 == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<SkV3 *>(v3)->ptr();
}

float *SkV3_ptrMutable(reskia_v3_t *v3) {
    if (v3 == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<SkV3 *>(v3)->ptr();
}

// static

float SkV3_Dot(const reskia_v3_t *a, const reskia_v3_t *b) {
    if (a == nullptr || b == nullptr) {
        return 0.0f;
    }
    return SkV3::Dot(* reinterpret_cast<const SkV3 *>(a), * reinterpret_cast<const SkV3 *>(b));
}

sk_v3_t SkV3_Cross(const reskia_v3_t *a, const reskia_v3_t *b) {
    if (a == nullptr || b == nullptr) {
        return static_sk_v3_make({});
    }
    return static_sk_v3_make(SkV3::Cross(* reinterpret_cast<const SkV3 *>(a), * reinterpret_cast<const SkV3 *>(b)));
}

sk_v3_t SkV3_Normalize(const reskia_v3_t *v) {
    if (v == nullptr) {
        return static_sk_v3_make({});
    }
    return static_sk_v3_make(SkV3::Normalize(* reinterpret_cast<const SkV3 *>(v)));
}

}
