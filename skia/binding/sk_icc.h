//
// Created by dolphilia on 2024/02/01.
//

#ifndef RAIA_SKIA_SK_ICC_H
#define RAIA_SKIA_SK_ICC_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_transfer_function_t reskia_transfer_function_t;
typedef struct reskia_matrix3x3_t reskia_matrix3x3_t;
typedef struct reskia_icc_profile_t reskia_icc_profile_t;

int SkICC_SkWriteICCProfile(const reskia_transfer_function_t *transferFunction, const reskia_matrix3x3_t *toXYZD50); // (const skcms_TransferFunction* transferFunction, const skcms_Matrix3x3* toXYZD50) -> sk_data_t
int SkICC_SkWriteICCProfile_2(const reskia_icc_profile_t *iccProfile, const char *description); // (const skcms_ICCProfile* iccProfile, const char* description) -> const_sk_data_t
void SkICC_SkICCFloatXYZD50ToGrid16Lab(const float *float_xyz, uint8_t *grid16_lab); // (const float* float_xyz, uint8_t* grid16_lab)
void SkICC_SkICCFloatToTable16(float f, uint8_t *table_16); // (const float f, uint8_t* table_16)

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_ICC_H
