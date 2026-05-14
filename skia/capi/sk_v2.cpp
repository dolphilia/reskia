//
// Created by dolphilia on 2024/01/11.
//

#include "sk_v2.h"

#include "include/core/SkM44.h"

#include "../handles/static_sk_v2.h"

#include "../handles/static_sk_v2-internal.h"

extern "C" {

bool SkV2_equals(reskia_v2_t *v2, sk_v2_t v) {
    if (v2 == nullptr) {
        return false;
    }
    return *reinterpret_cast<SkV2 *>(v2) == static_sk_v2_get_entity(v);
}

bool SkV2_notEquals(reskia_v2_t *v2, sk_v2_t v) {
    if (v2 == nullptr) {
        return false;
    }
    return *reinterpret_cast<SkV2 *>(v2) != static_sk_v2_get_entity(v);
}

sk_v2_t SkV2_negate(reskia_v2_t *v2) {
    if (v2 == nullptr) {
        return static_sk_v2_make({});
    }
    return static_sk_v2_make(-*reinterpret_cast<SkV2 *>(v2));
}

sk_v2_t SkV2_add(reskia_v2_t *v2, sk_v2_t v) {
    if (v2 == nullptr) {
        return static_sk_v2_make({});
    }
    return static_sk_v2_make(*reinterpret_cast<SkV2 *>(v2) + static_sk_v2_get_entity(v));
}

sk_v2_t SkV2_subtract(reskia_v2_t *v2, sk_v2_t v) {
    if (v2 == nullptr) {
        return static_sk_v2_make({});
    }
    return static_sk_v2_make(*reinterpret_cast<SkV2 *>(v2) - static_sk_v2_get_entity(v));
}

sk_v2_t SkV2_multiply(reskia_v2_t *v2, sk_v2_t v) {
    if (v2 == nullptr) {
        return static_sk_v2_make({});
    }
    return static_sk_v2_make(*reinterpret_cast<SkV2 *>(v2) * static_sk_v2_get_entity(v));
}

void SkV2_addAssign(reskia_v2_t *v2, sk_v2_t v) {
    if (v2 == nullptr) {
        return;
    }
    *reinterpret_cast<SkV2 *>(v2) += static_sk_v2_get_entity(v);
}

void SkV2_subtractAssign(reskia_v2_t *v2, sk_v2_t v) {
    if (v2 == nullptr) {
        return;
    }
    *reinterpret_cast<SkV2 *>(v2) -= static_sk_v2_get_entity(v);
}

void SkV2_multiplyAssign(reskia_v2_t *v2, sk_v2_t v) {
    if (v2 == nullptr) {
        return;
    }
    *reinterpret_cast<SkV2 *>(v2) *= static_sk_v2_get_entity(v);
}

void SkV2_multiplyScalarAssign(reskia_v2_t *v2, float s) {
    if (v2 == nullptr) {
        return;
    }
    *reinterpret_cast<SkV2 *>(v2) *= s;
}

void SkV2_divideScalarAssign(reskia_v2_t *v2, float s) {
    if (v2 == nullptr) {
        return;
    }
    *reinterpret_cast<SkV2 *>(v2) /= s;
}

void SkV2_delete(reskia_v2_t *v2) {
    if (v2 == nullptr) {
        return;
    }
    delete reinterpret_cast<SkV2 *>(v2);
}

float SkV2_lengthSquared(reskia_v2_t *v2) {
    if (v2 == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkV2 *>(v2)->lengthSquared();
}

float SkV2_length(reskia_v2_t *v2) {
    if (v2 == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkV2 *>(v2)->length();
}

float SkV2_dot(reskia_v2_t *v2, sk_v2_t v) {
    if (v2 == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkV2 *>(v2)->dot(static_sk_v2_get_entity(v));
}

float SkV2_cross(reskia_v2_t *v2, sk_v2_t v) {
    if (v2 == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkV2 *>(v2)->cross(static_sk_v2_get_entity(v));
}

sk_v2_t SkV2_normalize(reskia_v2_t *v2) {
    if (v2 == nullptr) {
        return static_sk_v2_make({});
    }
    return static_sk_v2_make(reinterpret_cast<SkV2 *>(v2)->normalize());
}

const float *SkV2_ptr(reskia_v2_t *v2) {
    if (v2 == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<SkV2 *>(v2)->ptr();
}

float *SkV2_ptrMutable(reskia_v2_t *v2) {
    if (v2 == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<SkV2 *>(v2)->ptr();
}

// static

float SkV2_Dot(sk_v2_t a, sk_v2_t b) {
    return SkV2::Dot(static_sk_v2_get_entity(a), static_sk_v2_get_entity(b));
}

float SkV2_Cross(sk_v2_t a, sk_v2_t b) {
    return SkV2::Cross(static_sk_v2_get_entity(a), static_sk_v2_get_entity(b));
}

sk_v2_t SkV2_Normalize(sk_v2_t v) {
    return static_sk_v2_make(SkV2::Normalize(static_sk_v2_get_entity(v)));
}

}
