//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_COLOR_SPACE_H
#define RAIA_SKIA_SK_COLOR_SPACE_H

#include <stddef.h>
#include <stdint.h>
#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_data.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_color_space_t reskia_color_space_t;
typedef struct reskia_icc_profile_t reskia_icc_profile_t;
typedef struct reskia_matrix3x3_t reskia_matrix3x3_t;
typedef struct reskia_transfer_function_t reskia_transfer_function_t;

void SkColorSpace_delete(reskia_color_space_t *color_space); // owned: caller が保持する参照を release する (SkColorSpace *color_space)
void SkColorSpace_toProfile(reskia_color_space_t *color_space, reskia_icc_profile_t *profile); // (SkColorSpace *color_space, skcms_ICCProfile *profile)
bool SkColorSpace_gammaCloseToSRGB(reskia_color_space_t *color_space); // (SkColorSpace *color_space) -> bool
bool SkColorSpace_gammaIsLinear(reskia_color_space_t *color_space); // (SkColorSpace *color_space) -> bool
bool SkColorSpace_isNumericalTransferFn(reskia_color_space_t *color_space, reskia_transfer_function_t *fn); // (SkColorSpace *color_space, skcms_TransferFunction *fn) -> bool
bool SkColorSpace_toXYZD50(reskia_color_space_t *color_space, reskia_matrix3x3_t *toXYZD50); // (SkColorSpace *color_space, skcms_Matrix3x3 *toXYZD50) -> bool
uint32_t SkColorSpace_toXYZD50Hash(reskia_color_space_t *color_space); // (SkColorSpace *color_space) -> uint32_t
sk_color_space_t SkColorSpace_makeLinearGamma(reskia_color_space_t *color_space); // (SkColorSpace *color_space) -> sk_color_space_t
sk_color_space_t SkColorSpace_makeSRGBGamma(reskia_color_space_t *color_space); // (SkColorSpace *color_space) -> sk_color_space_t
sk_color_space_t SkColorSpace_makeColorSpin(reskia_color_space_t *color_space); // (SkColorSpace *color_space) -> sk_color_space_t
bool SkColorSpace_isSRGB(reskia_color_space_t *color_space); // (SkColorSpace *color_space) -> bool
sk_data_t SkColorSpace_serialize(reskia_color_space_t *color_space); // (SkColorSpace *color_space) -> sk_data_t
size_t SkColorSpace_writeToMemory(reskia_color_space_t *color_space, void *memory); // (SkColorSpace *color_space, void *memory) -> size_t
void SkColorSpace_transferFn(reskia_color_space_t *color_space, float gabcdef[7]); // (SkColorSpace *color_space, float gabcdef[7])
void SkColorSpace_transferFn_2(reskia_color_space_t *color_space, reskia_transfer_function_t *fn); // (SkColorSpace *color_space, skcms_TransferFunction *fn)
void SkColorSpace_invTransferFn(reskia_color_space_t *color_space, reskia_transfer_function_t *fn); // (SkColorSpace *color_space, skcms_TransferFunction *fn)
void SkColorSpace_gamutTransformTo(reskia_color_space_t *color_space, const reskia_color_space_t *dst, reskia_matrix3x3_t *src_to_dst); // (SkColorSpace *color_space, const SkColorSpace *dst, skcms_Matrix3x3 *src_to_dst)
uint32_t SkColorSpace_transferFnHash(reskia_color_space_t *color_space); // (SkColorSpace *color_space) -> uint32_t
uint64_t SkColorSpace_hash(reskia_color_space_t *color_space); // (SkColorSpace *color_space) -> uint64_t
bool SkColorSpace_unique(reskia_color_space_t *color_space); // (SkColorSpace *color_space) -> bool
void SkColorSpace_ref(reskia_color_space_t *color_space); // retained: 参照カウントを増やす (SkColorSpace *color_space)
void SkColorSpace_unref(reskia_color_space_t *color_space); // owned: 参照カウントを減らす (SkColorSpace *color_space)
void SkColorSpace_deref(reskia_color_space_t *color_space); // (SkColorSpace *color_space)
bool SkColorSpace_refCntGreaterThan(reskia_color_space_t *color_space, int32_t threadIsolatedTestCnt); // (SkColorSpace *color_space, int32_t threadIsolatedTestCnt) -> bool

// static

sk_color_space_t SkColorSpace_MakeSRGB(); // () -> sk_color_space_t
sk_color_space_t SkColorSpace_MakeSRGBLinear(); // () -> sk_color_space_t
sk_color_space_t SkColorSpace_MakeRGB(const reskia_transfer_function_t *transferFn, const reskia_matrix3x3_t *toXYZ); // (const skcms_TransferFunction *transferFn, const skcms_Matrix3x3 *toXYZ) -> sk_color_space_t
sk_color_space_t SkColorSpace_Make(const reskia_icc_profile_t *profile); // (const skcms_ICCProfile *profile) -> sk_color_space_t
sk_color_space_t SkColorSpace_Deserialize(const void *data, size_t length); // (const void *data, size_t length) -> sk_color_space_t
bool SkColorSpace_Equals(reskia_color_space_t *color_space_1, const reskia_color_space_t *color_space_2); // (SkColorSpace *color_space_1, const SkColorSpace *color_space_2) -> bool

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_COLOR_SPACE_H
