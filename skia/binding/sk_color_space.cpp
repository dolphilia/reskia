//
// Created by dolphilia on 2024/01/08.
//

#include "sk_color_space.h"

#include "include/core/SkColorSpace.h"

#include "../static/static_sk_color_space.h"
#include "../static/static_sk_data.h"

#include "../static/static_sk_data-internal.h"
#include "../static/static_sk_color_space-internal.h"

extern "C" {

void SkColorSpace_delete(void *color_space) {
    delete static_cast<SkColorSpace *>(color_space);
}

void SkColorSpace_toProfile(void *color_space, void *profile) {
    static_cast<SkColorSpace *>(color_space)->toProfile(static_cast<skcms_ICCProfile *>(profile));
}

bool SkColorSpace_gammaCloseToSRGB(void *color_space) {
    return static_cast<SkColorSpace *>(color_space)->gammaCloseToSRGB();
}

bool SkColorSpace_gammaIsLinear(void *color_space) {
    return static_cast<SkColorSpace *>(color_space)->gammaIsLinear();
}

bool SkColorSpace_isNumericalTransferFn(void *color_space, void *fn) {
    return static_cast<SkColorSpace *>(color_space)->isNumericalTransferFn(static_cast<skcms_TransferFunction *>(fn));
}

bool SkColorSpace_toXYZD50(void *color_space, void *toXYZD50) {
    return static_cast<SkColorSpace *>(color_space)->toXYZD50(static_cast<skcms_Matrix3x3 *>(toXYZD50));
}

uint32_t SkColorSpace_toXYZD50Hash(void *color_space) {
    return static_cast<SkColorSpace *>(color_space)->toXYZD50Hash();
}

sk_color_space_t SkColorSpace_makeLinearGamma(void *color_space) {
    return static_sk_color_space_make(static_cast<SkColorSpace *>(color_space)->makeLinearGamma());
}

sk_color_space_t SkColorSpace_makeSRGBGamma(void *color_space) {
    return static_sk_color_space_make(static_cast<SkColorSpace *>(color_space)->makeSRGBGamma());
}

sk_color_space_t SkColorSpace_makeColorSpin(void *color_space) {
    return static_sk_color_space_make(static_cast<SkColorSpace *>(color_space)->makeColorSpin());
}

bool SkColorSpace_isSRGB(void *color_space) {
    return static_cast<SkColorSpace *>(color_space)->isSRGB();
}

sk_data_t SkColorSpace_serialize(void *color_space) {
    return static_sk_data_make(static_cast<SkColorSpace *>(color_space)->serialize());
}

size_t SkColorSpace_writeToMemory(void *color_space, void *memory) {
    return static_cast<SkColorSpace *>(color_space)->writeToMemory(memory);
}

void SkColorSpace_transferFn(void *color_space, float gabcdef[7]) {
    static_cast<SkColorSpace *>(color_space)->transferFn(gabcdef);
}

void SkColorSpace_transferFn_2(void *color_space, void *fn) {
    static_cast<SkColorSpace *>(color_space)->transferFn(static_cast<skcms_TransferFunction *>(fn));
}

void SkColorSpace_invTransferFn(void *color_space, void *fn) {
    static_cast<SkColorSpace *>(color_space)->invTransferFn(static_cast<skcms_TransferFunction *>(fn));
}

void SkColorSpace_gamutTransformTo(void *color_space, const void *dst, void *src_to_dst) {
    static_cast<SkColorSpace *>(color_space)->gamutTransformTo(static_cast<const SkColorSpace *>(dst), static_cast<skcms_Matrix3x3 *>(src_to_dst));
}

uint32_t SkColorSpace_transferFnHash(void *color_space) {
    return static_cast<SkColorSpace *>(color_space)->transferFnHash();
}

uint64_t SkColorSpace_hash(void *color_space) {
    return static_cast<SkColorSpace *>(color_space)->hash();
}

bool SkColorSpace_unique(void *color_space) {
    return static_cast<SkColorSpace *>(color_space)->unique();
}

void SkColorSpace_ref(void *color_space) {
    static_cast<SkColorSpace *>(color_space)->ref();
}

void SkColorSpace_unref(void *color_space) {
    static_cast<SkColorSpace *>(color_space)->unref();
}

void SkColorSpace_deref(void *color_space) {
    static_cast<SkColorSpace *>(color_space)->deref();
}

bool SkColorSpace_refCntGreaterThan(void *color_space, int32_t threadIsolatedTestCnt) {
    return static_cast<SkColorSpace *>(color_space)->refCntGreaterThan(threadIsolatedTestCnt);
}

// static

sk_color_space_t SkColorSpace_MakeSRGB() {
    return static_sk_color_space_make(SkColorSpace::MakeSRGB());
}

sk_color_space_t SkColorSpace_MakeSRGBLinear() {
    return static_sk_color_space_make(SkColorSpace::MakeSRGBLinear());
}

sk_color_space_t SkColorSpace_MakeRGB(const void *transferFn, const void *toXYZ) {
    return static_sk_color_space_make(SkColorSpace::MakeRGB(* static_cast<const skcms_TransferFunction *>(transferFn), * static_cast<const skcms_Matrix3x3 *>(toXYZ)));
}

sk_color_space_t SkColorSpace_Make(const void * profile) {
    return static_sk_color_space_make(SkColorSpace::Make(* static_cast<const skcms_ICCProfile *>(profile)));
}

sk_color_space_t SkColorSpace_Deserialize(const void *data, size_t length) {
    return static_sk_color_space_make(SkColorSpace::Deserialize(data, length));
}

bool SkColorSpace_Equals(void *color_space_1, const void *color_space_2) {
    return SkColorSpace::Equals(static_cast<SkColorSpace *>(color_space_1), static_cast<const SkColorSpace *>(color_space_2));
}

}
