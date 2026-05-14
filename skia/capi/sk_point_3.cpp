//
// Created by dolphilia on 2024/01/10.
//

#include "sk_point_3.h"

#include "include/core/SkPoint3.h"

#include "../handles/static_sk_point_3.h"

#include "../handles/static_sk_point_3-internal.h"

extern "C" {

sk_point_3_t SkPoint3_negate(reskia_point_3_t *point3) {
    if (point3 == nullptr) {
        return 0;
    }
    return static_sk_point_3_make(-*reinterpret_cast<SkPoint3 *>(point3));
}

void SkPoint3_addAssign(reskia_point_3_t *point3, const reskia_point_3_t *v) {
    if (point3 == nullptr || v == nullptr) {
        return;
    }
    *reinterpret_cast<SkPoint3 *>(point3) += *reinterpret_cast<const SkPoint3 *>(v);
}

void SkPoint3_subtractAssign(reskia_point_3_t *point3, const reskia_point_3_t *v) {
    if (point3 == nullptr || v == nullptr) {
        return;
    }
    *reinterpret_cast<SkPoint3 *>(point3) -= *reinterpret_cast<const SkPoint3 *>(v);
}

void SkPoint3_delete(reskia_point_3_t *point3) {
    delete reinterpret_cast<SkPoint3 *>(point3);
}

float SkPoint3_x(reskia_point_3_t *point3) {
    if (point3 == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkPoint3 *>(point3)->x();
}

float SkPoint3_y(reskia_point_3_t *point3) {
    if (point3 == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkPoint3 *>(point3)->y();
}

float SkPoint3_z(reskia_point_3_t *point3) {
    if (point3 == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkPoint3 *>(point3)->z();
}

void SkPoint3_set(reskia_point_3_t *point3, float x, float y, float z) {
    if (point3 == nullptr) {
        return;
    }
    reinterpret_cast<SkPoint3 *>(point3)->set(x, y, z);
}

float SkPoint3_length(reskia_point_3_t *point3) {
    if (point3 == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkPoint3 *>(point3)->length();
}

bool SkPoint3_normalize(reskia_point_3_t *point3) {
    if (point3 == nullptr) {
        return false;
    }
    return reinterpret_cast<SkPoint3 *>(point3)->normalize();
}

sk_point_3_t SkPoint3_makeScale(reskia_point_3_t *point3, float scale) {
    if (point3 == nullptr) {
        return 0;
    }
    return static_sk_point_3_make(reinterpret_cast<SkPoint3 *>(point3)->makeScale(scale));
}

void SkPoint3_scale(reskia_point_3_t *point3, float value) {
    if (point3 == nullptr) {
        return;
    }
    reinterpret_cast<SkPoint3 *>(point3)->scale(value);
}

bool SkPoint3_isFinite(reskia_point_3_t *point3) {
    if (point3 == nullptr) {
        return false;
    }
    return reinterpret_cast<SkPoint3 *>(point3)->isFinite();
}

float SkPoint3_dot(reskia_point_3_t *point3, const reskia_point_3_t *vec) {
    if (point3 == nullptr || vec == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkPoint3 *>(point3)->dot(* reinterpret_cast<const SkPoint3 *>(vec));
}

sk_point_3_t SkPoint3_cross(reskia_point_3_t *point3, const reskia_point_3_t *vec) {
    if (point3 == nullptr || vec == nullptr) {
        return 0;
    }
    return static_sk_point_3_make(reinterpret_cast<SkPoint3 *>(point3)->cross(* reinterpret_cast<const SkPoint3 *>(vec)));
}

// static

sk_point_3_t SkPoint3_Make(float x, float y, float z) {
    return static_sk_point_3_make(SkPoint3::Make(x, y, z));
}

float SkPoint3_Length(float x, float y, float z) {
    return SkPoint3::Length(x, y, z);
}

float SkPoint3_DotProduct(const reskia_point_3_t *a, const reskia_point_3_t *b) {
    if (a == nullptr || b == nullptr) {
        return 0.0f;
    }
    return SkPoint3::DotProduct(* reinterpret_cast<const SkPoint3 *>(a), * reinterpret_cast<const SkPoint3 *>(b));
}

sk_point_3_t SkPoint3_CrossProduct(const reskia_point_3_t *a, const reskia_point_3_t *b) {
    if (a == nullptr || b == nullptr) {
        return 0;
    }
    return static_sk_point_3_make(SkPoint3::CrossProduct(* reinterpret_cast<const SkPoint3 *>(a), * reinterpret_cast<const SkPoint3 *>(b)));
}

}
