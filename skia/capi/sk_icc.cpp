//
// Created by dolphilia on 2024/02/01.
//

#include "sk_icc.h"

#include "include/encode/SkICC.h"

#include "../handles/static_sk_data.h"

#include "../handles/static_sk_data-internal.h"

extern "C" {

sk_data_t SkICC_SkWriteICCProfile(const reskia_transfer_function_t *transferFunction, const reskia_matrix3x3_t *toXYZD50) {
    return static_sk_data_make(SkWriteICCProfile(
        *reinterpret_cast<const skcms_TransferFunction *>(transferFunction),
        *reinterpret_cast<const skcms_Matrix3x3 *>(toXYZD50)));
}

const_sk_data_t SkICC_SkWriteICCProfileFromICCProfile(const reskia_icc_profile_t *iccProfile, const char *description) {
    return static_const_sk_data_make(SkWriteICCProfile(
        reinterpret_cast<const skcms_ICCProfile *>(iccProfile), description));
}

void SkICC_SkICCFloatXYZD50ToGrid16Lab(const float *float_xyz, uint8_t *grid16_lab) {
    SkICCFloatXYZD50ToGrid16Lab(float_xyz, grid16_lab);
}

void SkICC_SkICCFloatToTable16(float f, uint8_t *table_16) {
    SkICCFloatToTable16(f, table_16);
}

}
