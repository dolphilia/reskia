//
// Created by dolphilia on 2024/02/01.
//

#ifndef RAIA_SKIA_SK_ICC_H
#define RAIA_SKIA_SK_ICC_H

#include <stdint.h>
#include "../handles/static_sk_data.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_transfer_function_t reskia_transfer_function_t;
typedef struct reskia_matrix3x3_t reskia_matrix3x3_t;
typedef struct reskia_icc_profile_t reskia_icc_profile_t;

sk_data_t SkICC_SkWriteICCProfile(const reskia_transfer_function_t *transferFunction, const reskia_matrix3x3_t *toXYZD50); // required inputs; invalid/failure returns 0.
int SkICC_SkWriteICCProfileFromICCProfile(const reskia_icc_profile_t *iccProfile, const char *description); // iccProfile required; description may be NULL; invalid/failure returns 0.
void SkICC_SkICCFloatXYZD50ToGrid16Lab(const float *float_xyz, uint8_t *grid16_lab); // required input/output; invalid input is no-op.
void SkICC_SkICCFloatToTable16(float f, uint8_t *table_16); // table_16 required; invalid input is no-op.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_ICC_H
