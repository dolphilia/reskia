//
// Created by dolphilia on 2024/02/01.
//

#include "sk_icc.h"

#include "include/encode/SkICC.h"

#include "../handles/static_sk_data.h"

#include "../handles/static_sk_data-internal.h"

#include <algorithm>
#include <cmath>

namespace {

void write_u16_be(uint16_t value, uint8_t *dst) {
    dst[0] = static_cast<uint8_t>((value >> 8) & 0xff);
    dst[1] = static_cast<uint8_t>(value & 0xff);
}

uint16_t float_to_u16(float value) {
    value = std::clamp(value, 0.0f, 1.0f);
    return static_cast<uint16_t>(std::lround(value * 65535.0f));
}

}  // namespace

extern "C" {

sk_data_t SkICC_SkWriteICCProfile(const reskia_transfer_function_t *transferFunction, const reskia_matrix3x3_t *toXYZD50) {
    if (transferFunction == nullptr || toXYZD50 == nullptr) {
        return 0;
    }
    return static_sk_data_make(SkWriteICCProfile(
        *reinterpret_cast<const skcms_TransferFunction *>(transferFunction),
        *reinterpret_cast<const skcms_Matrix3x3 *>(toXYZD50)));
}

const_sk_data_t SkICC_SkWriteICCProfileFromICCProfile(const reskia_icc_profile_t *iccProfile, const char *description) {
    if (iccProfile == nullptr) {
        return 0;
    }
    return static_const_sk_data_make(SkWriteICCProfile(
        reinterpret_cast<const skcms_ICCProfile *>(iccProfile), description));
}

void SkICC_SkICCFloatXYZD50ToGrid16Lab(const float *float_xyz, uint8_t *grid16_lab) {
    if (float_xyz == nullptr || grid16_lab == nullptr) {
        return;
    }
    write_u16_be(float_to_u16(float_xyz[0]), &grid16_lab[0]);
    write_u16_be(float_to_u16(float_xyz[1]), &grid16_lab[2]);
    write_u16_be(float_to_u16(float_xyz[2]), &grid16_lab[4]);
}

void SkICC_SkICCFloatToTable16(float f, uint8_t *table_16) {
    if (table_16 == nullptr) {
        return;
    }
    write_u16_be(float_to_u16(f), table_16);
}

}
