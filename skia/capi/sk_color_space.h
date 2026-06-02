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
typedef int32_t reskia_named_primaries_cicp_id_t;
typedef int32_t reskia_named_transfer_fn_cicp_id_t;

void SkColorSpace_release(reskia_color_space_t *color_space); // owned: releases the caller-held reference. (SkColorSpace *color_space)
/**
 * out: profile must be non-NULL. No-op for NULL input.
 * (SkColorSpace *color_space, skcms_ICCProfile *profile)
 */
void SkColorSpace_toProfile(reskia_color_space_t *color_space, reskia_icc_profile_t *profile);
bool SkColorSpace_gammaCloseToSRGB(reskia_color_space_t *color_space); // (SkColorSpace *color_space) -> bool
bool SkColorSpace_gammaIsLinear(reskia_color_space_t *color_space); // (SkColorSpace *color_space) -> bool
/**
 * out: fn must be non-NULL. Returns false for NULL input.
 * (SkColorSpace *color_space, skcms_TransferFunction *fn) -> bool
 */
bool SkColorSpace_isNumericalTransferFn(reskia_color_space_t *color_space, reskia_transfer_function_t *fn);
/**
 * out: toXYZD50 must be non-NULL. Returns false for NULL input.
 * (SkColorSpace *color_space, skcms_Matrix3x3 *toXYZD50) -> bool
 */
bool SkColorSpace_toXYZD50(reskia_color_space_t *color_space, reskia_matrix3x3_t *toXYZD50);
uint32_t SkColorSpace_toXYZD50Hash(reskia_color_space_t *color_space); // (SkColorSpace *color_space) -> uint32_t
sk_color_space_t SkColorSpace_makeLinearGamma(reskia_color_space_t *color_space); // (SkColorSpace *color_space) -> sk_color_space_t
sk_color_space_t SkColorSpace_makeSRGBGamma(reskia_color_space_t *color_space); // (SkColorSpace *color_space) -> sk_color_space_t
sk_color_space_t SkColorSpace_makeColorSpin(reskia_color_space_t *color_space); // (SkColorSpace *color_space) -> sk_color_space_t
bool SkColorSpace_isSRGB(reskia_color_space_t *color_space); // (SkColorSpace *color_space) -> bool
/**
 * retained data handle: caller must release it with static_sk_data_delete.
 * Returns 0 for NULL input. (SkColorSpace *color_space) -> sk_data_t
 */
sk_data_t SkColorSpace_serialize(reskia_color_space_t *color_space);
/**
 * raw output buffer: returns the required size when memory is NULL.
 * Returns 0 when color_space is NULL. (SkColorSpace *color_space, void *memory) -> size_t
 */
size_t SkColorSpace_writeToMemory(reskia_color_space_t *color_space, void *memory);
/**
 * out: gabcdef must contain at least 7 elements and be non-NULL. No-op for NULL input.
 * (SkColorSpace *color_space, float gabcdef[7])
 */
void SkColorSpace_transferFn(reskia_color_space_t *color_space, float gabcdef[7]);
/**
 * out: fn must be non-NULL. No-op for NULL input.
 * (SkColorSpace *color_space, skcms_TransferFunction *fn)
 */
void SkColorSpace_transferFnToStruct(reskia_color_space_t *color_space, reskia_transfer_function_t *fn);
/**
 * out: fn must be non-NULL. No-op for NULL input.
 * (SkColorSpace *color_space, skcms_TransferFunction *fn)
 */
void SkColorSpace_invTransferFn(reskia_color_space_t *color_space, reskia_transfer_function_t *fn);
/**
 * out: src_to_dst must be non-NULL. dst may be NULL. No-op for NULL input.
 * (SkColorSpace *color_space, const SkColorSpace *dst, skcms_Matrix3x3 *src_to_dst)
 */
void SkColorSpace_gamutTransformTo(reskia_color_space_t *color_space, const reskia_color_space_t *dst, reskia_matrix3x3_t *src_to_dst);
uint32_t SkColorSpace_transferFnHash(reskia_color_space_t *color_space); // (SkColorSpace *color_space) -> uint32_t
uint64_t SkColorSpace_hash(reskia_color_space_t *color_space); // (SkColorSpace *color_space) -> uint64_t
bool SkColorSpace_unique(reskia_color_space_t *color_space); // (SkColorSpace *color_space) -> bool
void SkColorSpace_ref(reskia_color_space_t *color_space); // retained: increments the reference count. (SkColorSpace *color_space)
void SkColorSpace_unref(reskia_color_space_t *color_space); // owned: decrements the reference count. (SkColorSpace *color_space)
void SkColorSpace_deref(reskia_color_space_t *color_space); // (SkColorSpace *color_space)
bool SkColorSpace_refCntGreaterThan(reskia_color_space_t *color_space, int32_t threadIsolatedTestCnt); // (SkColorSpace *color_space, int32_t threadIsolatedTestCnt) -> bool

// static

sk_color_space_t SkColorSpace_MakeSRGB(); // () -> sk_color_space_t
sk_color_space_t SkColorSpace_MakeSRGBLinear(); // () -> sk_color_space_t
/**
 * transferFn and toXYZ must be non-NULL. Returns 0 for NULL input.
 * (const skcms_TransferFunction *transferFn, const skcms_Matrix3x3 *toXYZ) -> sk_color_space_t
 */
sk_color_space_t SkColorSpace_MakeRGB(const reskia_transfer_function_t *transferFn, const reskia_matrix3x3_t *toXYZ);
sk_color_space_t SkColorSpace_Make(const reskia_icc_profile_t *profile); // profile must be non-NULL. Returns 0 for NULL input. (const skcms_ICCProfile *profile) -> sk_color_space_t
sk_color_space_t SkColorSpace_MakeCICP(reskia_named_primaries_cicp_id_t color_primaries, reskia_named_transfer_fn_cicp_id_t transfer_characteristics);
/**
 * raw input buffer: data must contain at least length bytes and be non-NULL.
 * Returns 0 for NULL input. (const void *data, size_t length) -> sk_color_space_t
 */
sk_color_space_t SkColorSpace_Deserialize(const void *data, size_t length);
bool SkColorSpace_Equals(reskia_color_space_t *color_space_1, const reskia_color_space_t *color_space_2); // (SkColorSpace *color_space_1, const SkColorSpace *color_space_2) -> bool

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_COLOR_SPACE_H
