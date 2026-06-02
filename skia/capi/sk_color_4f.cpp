//
// Created by dolphilia on 25/01/30.
//

#include "sk_color_4f.h"

#include "include/core/SkColor.h"
#include "include/core/SkUnPreMultiply.h"

#include "../handles/static_sk_color_4f.h"

#include "../handles/static_sk_color_4f-internal.h"

extern "C" {

void SkColor4f_delete(reskia_color_4f_t *color) {
    delete reinterpret_cast<SkColor4f *>(color);
}

// Public Attributes

float SkColor4f_fR(reskia_color_4f_t *color) {
    if (color == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkColor4f *>(color)->fR;
}

float SkColor4f_fG(reskia_color_4f_t *color) {
    if (color == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkColor4f *>(color)->fG;
}

float SkColor4f_fB(reskia_color_4f_t *color) {
    if (color == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkColor4f *>(color)->fB;
}

float SkColor4f_fA(reskia_color_4f_t *color) {
    if (color == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkColor4f *>(color)->fA;
}

// Public Member Functions

bool SkColor4f_equals(reskia_color_4f_t *color, reskia_color_4f_t *other) {
    if (color == nullptr || other == nullptr) {
        return color == other;
    }
    return *reinterpret_cast<SkColor4f *>(color) == *reinterpret_cast<SkColor4f *>(other);
}

bool SkColor4f_notEquals(reskia_color_4f_t *color, reskia_color_4f_t *other) {
    return !SkColor4f_equals(color, other);
}

sk_color_4f_t SkColor4f_mulScalar(reskia_color_4f_t *color, float scale) {
    if (color == nullptr) {
        return 0;
    }
    return static_sk_color_4f_make(*reinterpret_cast<SkColor4f *>(color) * scale);
}

sk_color_4f_t SkColor4f_mulColor(reskia_color_4f_t *color, reskia_color_4f_t *scale) {
    if (color == nullptr || scale == nullptr) {
        return 0;
    }
    return static_sk_color_4f_make(*reinterpret_cast<SkColor4f *>(color) * *reinterpret_cast<SkColor4f *>(scale));
}

float SkColor4f_get(reskia_color_4f_t *color, int index) {
    if (color == nullptr || index < 0 || index >= 4) {
        return 0.0f;
    }
    return (*reinterpret_cast<SkColor4f *>(color))[index];
}

void SkColor4f_set(reskia_color_4f_t *color, int index, float value) {
    if (color == nullptr || index < 0 || index >= 4) {
        return;
    }
    (*reinterpret_cast<SkColor4f *>(color))[index] = value;
}

const float *SkColor4f_vec(reskia_color_4f_t *color) {
    if (color == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<SkColor4f *>(color)->vec();
}

float *SkColor4f_vecMutable(reskia_color_4f_t *color) {
    if (color == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<SkColor4f *>(color)->vec();
}

bool SkColor4f_toArray(reskia_color_4f_t *color, float out[4]) {
    if (color == nullptr || out == nullptr) {
        return false;
    }
    const std::array<float, 4> values = reinterpret_cast<SkColor4f *>(color)->array();
    for (size_t i = 0; i < values.size(); ++i) {
        out[i] = values[i];
    }
    return true;
}

bool SkColor4f_isOpaque(reskia_color_4f_t *color) {
    if (color == nullptr) {
        return false;
    }
    return reinterpret_cast<SkColor4f *>(color)->isOpaque();
}

bool SkColor4f_fitsInBytes(reskia_color_4f_t *color) {
    if (color == nullptr) {
        return false;
    }
    return reinterpret_cast<SkColor4f *>(color)->fitsInBytes();
}

reskia_color_t SkColor4f_toSkColor(reskia_color_4f_t *color) {
    if (color == nullptr) {
        return 0;
    }
    return static_cast<reskia_color_t>(reinterpret_cast<SkColor4f *>(color)->toSkColor());
}

reskia_u32_t SkColor4f_toBytes_RGBA(reskia_color_4f_t *color) {
    if (color == nullptr) {
        return 0;
    }
    return static_cast<reskia_u32_t>(reinterpret_cast<SkColor4f *>(color)->toBytes_RGBA());
}

sk_color_4f_t SkColor4f_makeOpaque(reskia_color_4f_t *color) {
    if (color == nullptr) {
        return 0;
    }
    return static_sk_color_4f_make(reinterpret_cast<SkColor4f *>(color)->makeOpaque());
}

// static

int SkColor4f_FromColor(reskia_color_t color) {
    return static_sk_color_4f_make(SkColor4f::FromColor(static_cast<SkColor>(color)));
}

int SkColor4f_FromPMColor(reskia_pmcolor_t color) {
    return static_sk_color_4f_make(SkColor4f::FromColor(SkUnPreMultiply::PMColorToColor(static_cast<SkPMColor>(color))));
}

int SkColor4f_FromBytes_RGBA(reskia_u32_t color) {
    return static_sk_color_4f_make(SkColor4f::FromBytes_RGBA(color));
}

}
