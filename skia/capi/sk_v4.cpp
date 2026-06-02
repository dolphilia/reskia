//
// Created by dolphilia on 2024/01/11.
//

#include "sk_v4.h"

#include "include/core/SkM44.h"
#include "../handles/static_sk_v4.h"

#include "../handles/static_sk_v4-internal.h"

extern "C" {

bool SkV4_equals(reskia_v4_t *v4, const reskia_v4_t *v) {
    if (v4 == nullptr || v == nullptr) {
        return false;
    }
    return *reinterpret_cast<SkV4 *>(v4) == *reinterpret_cast<const SkV4 *>(v);
}

bool SkV4_notEquals(reskia_v4_t *v4, const reskia_v4_t *v) {
    if (v4 == nullptr || v == nullptr) {
        return false;
    }
    return *reinterpret_cast<SkV4 *>(v4) != *reinterpret_cast<const SkV4 *>(v);
}

sk_v4_t SkV4_negate(reskia_v4_t *v4) {
    if (v4 == nullptr) {
        return static_sk_v4_make({});
    }
    return static_sk_v4_make(-*reinterpret_cast<SkV4 *>(v4));
}

sk_v4_t SkV4_add(reskia_v4_t *v4, const reskia_v4_t *v) {
    if (v4 == nullptr || v == nullptr) {
        return static_sk_v4_make({});
    }
    return static_sk_v4_make(*reinterpret_cast<SkV4 *>(v4) + *reinterpret_cast<const SkV4 *>(v));
}

sk_v4_t SkV4_subtract(reskia_v4_t *v4, const reskia_v4_t *v) {
    if (v4 == nullptr || v == nullptr) {
        return static_sk_v4_make({});
    }
    return static_sk_v4_make(*reinterpret_cast<SkV4 *>(v4) - *reinterpret_cast<const SkV4 *>(v));
}

sk_v4_t SkV4_multiply(reskia_v4_t *v4, const reskia_v4_t *v) {
    if (v4 == nullptr || v == nullptr) {
        return static_sk_v4_make({});
    }
    return static_sk_v4_make(*reinterpret_cast<SkV4 *>(v4) * *reinterpret_cast<const SkV4 *>(v));
}

void SkV4_delete(reskia_v4_t *v4) {
    if (v4 == nullptr) {
        return;
    }
    delete reinterpret_cast<SkV4 *>(v4);
}

float SkV4_lengthSquared(reskia_v4_t *v4) {
    if (v4 == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkV4 *>(v4)->lengthSquared();
}

float SkV4_length(reskia_v4_t *v4) {
    if (v4 == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkV4 *>(v4)->length();
}

float SkV4_dot(reskia_v4_t *v4, const reskia_v4_t *v) {
    if (v4 == nullptr || v == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkV4 *>(v4)->dot(* reinterpret_cast<const SkV4 *>(v));
}

sk_v4_t SkV4_normalize(reskia_v4_t *v4) {
    if (v4 == nullptr) {
        return static_sk_v4_make({});
    }
    return static_sk_v4_make(reinterpret_cast<SkV4 *>(v4)->normalize());
}

const float *SkV4_ptr(reskia_v4_t *v4) {
    if (v4 == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<SkV4 *>(v4)->ptr();
}

float *SkV4_ptrMutable(reskia_v4_t *v4) {
    if (v4 == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<SkV4 *>(v4)->ptr();
}

// static

float SkV4_Dot(const reskia_v4_t *a, const reskia_v4_t *b) {
    if (a == nullptr || b == nullptr) {
        return 0.0f;
    }
    return SkV4::Dot(* reinterpret_cast<const SkV4 *>(a), * reinterpret_cast<const SkV4 *>(b));
}

sk_v4_t SkV4_Normalize(const reskia_v4_t *v) {
    if (v == nullptr) {
        return static_sk_v4_make({});
    }
    return static_sk_v4_make(SkV4::Normalize(* reinterpret_cast<const SkV4 *>(v)));
}

}
