//
// Created by dolphilia on 2024/02/01.
//

#include "sk_icc.h"

#include "include/encode/SkICC.h"

#include "../static/static_sk_data.h"

#include "../static/static_sk_data-internal.h"

extern "C" {

sk_data_t SkICC_SkWriteICCProfile(const void * transferFunction, const void * toXYZD50) {
    return static_sk_data_make(SkWriteICCProfile(* static_cast<const skcms_TransferFunction *>(transferFunction), * static_cast<const skcms_Matrix3x3 *>(toXYZD50)));
}

const_sk_data_t SkICC_SkWriteICCProfile_2(const void * iccProfile, const char * description) {
    return static_const_sk_data_make(SkWriteICCProfile(static_cast<const skcms_ICCProfile *>(iccProfile), description));
}

void SkICC_SkICCFloatXYZD50ToGrid16Lab(const float * float_xyz, void * grid16_lab) {
    SkICCFloatXYZD50ToGrid16Lab(float_xyz, static_cast<uint8_t *>(grid16_lab));
}

void SkICC_SkICCFloatToTable16(const float f, void * table_16) {
    SkICCFloatToTable16(f, static_cast<uint8_t *>(table_16));
}

}
