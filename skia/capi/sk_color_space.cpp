//
// Created by dolphilia on 2024/01/08.
//

#include "sk_color_space.h"

#include "include/core/SkColorSpace.h"

#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_data.h"

#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_color_space-internal.h"

#include <utility>

namespace {

sk_color_space_t make_color_space_handle(sk_sp<SkColorSpace> color_space) {
    if (!color_space) {
        return 0;
    }
    return static_sk_color_space_make(std::move(color_space));
}

}  // namespace

extern "C" {

void SkColorSpace_release(reskia_color_space_t *color_space) {
    if (color_space == nullptr) {
        return;
    }
    reinterpret_cast<SkColorSpace *>(color_space)->unref();
}

void SkColorSpace_toProfile(reskia_color_space_t *color_space, reskia_icc_profile_t *profile) {
    if (color_space == nullptr || profile == nullptr) {
        return;
    }
    reinterpret_cast<SkColorSpace *>(color_space)->toProfile(reinterpret_cast<skcms_ICCProfile *>(profile));
}

bool SkColorSpace_gammaCloseToSRGB(reskia_color_space_t *color_space) {
    if (color_space == nullptr) {
        return false;
    }
    return reinterpret_cast<SkColorSpace *>(color_space)->gammaCloseToSRGB();
}

bool SkColorSpace_gammaIsLinear(reskia_color_space_t *color_space) {
    if (color_space == nullptr) {
        return false;
    }
    return reinterpret_cast<SkColorSpace *>(color_space)->gammaIsLinear();
}

bool SkColorSpace_isNumericalTransferFn(reskia_color_space_t *color_space, reskia_transfer_function_t *fn) {
    if (color_space == nullptr || fn == nullptr) {
        return false;
    }
    return reinterpret_cast<SkColorSpace *>(color_space)->isNumericalTransferFn(reinterpret_cast<skcms_TransferFunction *>(fn));
}

bool SkColorSpace_toXYZD50(reskia_color_space_t *color_space, reskia_matrix3x3_t *toXYZD50) {
    if (color_space == nullptr || toXYZD50 == nullptr) {
        return false;
    }
    return reinterpret_cast<SkColorSpace *>(color_space)->toXYZD50(reinterpret_cast<skcms_Matrix3x3 *>(toXYZD50));
}

uint32_t SkColorSpace_toXYZD50Hash(reskia_color_space_t *color_space) {
    if (color_space == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkColorSpace *>(color_space)->toXYZD50Hash();
}

sk_color_space_t SkColorSpace_makeLinearGamma(reskia_color_space_t *color_space) {
    if (color_space == nullptr) {
        return 0;
    }
    return make_color_space_handle(reinterpret_cast<SkColorSpace *>(color_space)->makeLinearGamma());
}

sk_color_space_t SkColorSpace_makeSRGBGamma(reskia_color_space_t *color_space) {
    if (color_space == nullptr) {
        return 0;
    }
    return make_color_space_handle(reinterpret_cast<SkColorSpace *>(color_space)->makeSRGBGamma());
}

sk_color_space_t SkColorSpace_makeColorSpin(reskia_color_space_t *color_space) {
    if (color_space == nullptr) {
        return 0;
    }
    return make_color_space_handle(reinterpret_cast<SkColorSpace *>(color_space)->makeColorSpin());
}

bool SkColorSpace_isSRGB(reskia_color_space_t *color_space) {
    if (color_space == nullptr) {
        return false;
    }
    return reinterpret_cast<SkColorSpace *>(color_space)->isSRGB();
}

sk_data_t SkColorSpace_serialize(reskia_color_space_t *color_space) {
    if (color_space == nullptr) {
        return 0;
    }
    return static_sk_data_make(reinterpret_cast<SkColorSpace *>(color_space)->serialize());
}

size_t SkColorSpace_writeToMemory(reskia_color_space_t *color_space, void *memory) {
    if (color_space == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkColorSpace *>(color_space)->writeToMemory(memory);
}

void SkColorSpace_transferFn(reskia_color_space_t *color_space, float gabcdef[7]) {
    if (color_space == nullptr || gabcdef == nullptr) {
        return;
    }
    reinterpret_cast<SkColorSpace *>(color_space)->transferFn(gabcdef);
}

void SkColorSpace_transferFnToStruct(reskia_color_space_t *color_space, reskia_transfer_function_t *fn) {
    if (color_space == nullptr || fn == nullptr) {
        return;
    }
    reinterpret_cast<SkColorSpace *>(color_space)->transferFn(reinterpret_cast<skcms_TransferFunction *>(fn));
}

void SkColorSpace_invTransferFn(reskia_color_space_t *color_space, reskia_transfer_function_t *fn) {
    if (color_space == nullptr || fn == nullptr) {
        return;
    }
    reinterpret_cast<SkColorSpace *>(color_space)->invTransferFn(reinterpret_cast<skcms_TransferFunction *>(fn));
}

void SkColorSpace_gamutTransformTo(reskia_color_space_t *color_space, const reskia_color_space_t *dst, reskia_matrix3x3_t *src_to_dst) {
    if (color_space == nullptr || src_to_dst == nullptr) {
        return;
    }
    reinterpret_cast<SkColorSpace *>(color_space)->gamutTransformTo(reinterpret_cast<const SkColorSpace *>(dst), reinterpret_cast<skcms_Matrix3x3 *>(src_to_dst));
}

uint32_t SkColorSpace_transferFnHash(reskia_color_space_t *color_space) {
    if (color_space == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkColorSpace *>(color_space)->transferFnHash();
}

uint64_t SkColorSpace_hash(reskia_color_space_t *color_space) {
    if (color_space == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkColorSpace *>(color_space)->hash();
}

bool SkColorSpace_unique(reskia_color_space_t *color_space) {
    if (color_space == nullptr) {
        return false;
    }
    return reinterpret_cast<SkColorSpace *>(color_space)->unique();
}

void SkColorSpace_ref(reskia_color_space_t *color_space) {
    if (color_space == nullptr) {
        return;
    }
    reinterpret_cast<SkColorSpace *>(color_space)->ref();
}

void SkColorSpace_unref(reskia_color_space_t *color_space) {
    if (color_space == nullptr) {
        return;
    }
    reinterpret_cast<SkColorSpace *>(color_space)->unref();
}

void SkColorSpace_deref(reskia_color_space_t *color_space) {
    if (color_space == nullptr) {
        return;
    }
    reinterpret_cast<SkColorSpace *>(color_space)->deref();
}

bool SkColorSpace_refCntGreaterThan(reskia_color_space_t *color_space, int32_t threadIsolatedTestCnt) {
    if (color_space == nullptr) {
        return false;
    }
    return reinterpret_cast<SkColorSpace *>(color_space)->refCntGreaterThan(threadIsolatedTestCnt);
}

// static

sk_color_space_t SkColorSpace_MakeSRGB() {
    return make_color_space_handle(SkColorSpace::MakeSRGB());
}

sk_color_space_t SkColorSpace_MakeSRGBLinear() {
    return make_color_space_handle(SkColorSpace::MakeSRGBLinear());
}

sk_color_space_t SkColorSpace_MakeRGB(const reskia_transfer_function_t *transferFn, const reskia_matrix3x3_t *toXYZ) {
    if (transferFn == nullptr || toXYZ == nullptr) {
        return 0;
    }
    return make_color_space_handle(SkColorSpace::MakeRGB(* reinterpret_cast<const skcms_TransferFunction *>(transferFn), * reinterpret_cast<const skcms_Matrix3x3 *>(toXYZ)));
}

sk_color_space_t SkColorSpace_Make(const reskia_icc_profile_t *profile) {
    if (profile == nullptr) {
        return 0;
    }
    return make_color_space_handle(SkColorSpace::Make(* reinterpret_cast<const skcms_ICCProfile *>(profile)));
}

sk_color_space_t SkColorSpace_Deserialize(const void *data, size_t length) {
    if (data == nullptr) {
        return 0;
    }
    return make_color_space_handle(SkColorSpace::Deserialize(data, length));
}

bool SkColorSpace_Equals(reskia_color_space_t *color_space_1, const reskia_color_space_t *color_space_2) {
    return SkColorSpace::Equals(reinterpret_cast<SkColorSpace *>(color_space_1), reinterpret_cast<const SkColorSpace *>(color_space_2));
}

}
