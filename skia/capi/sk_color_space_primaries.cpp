//
// Created by dolphilia on 2024/01/08.
//

#include "sk_color_space_primaries.h"

#include "include/core/SkColorSpace.h"

extern "C" {

void SkColorSpacePrimaries_delete(reskia_color_space_primaries_t *color_pace_primaries) {
    delete reinterpret_cast<SkColorSpacePrimaries *>(color_pace_primaries);
}

void SkColorSpacePrimaries_toXYZD50(reskia_color_space_primaries_t *color_pace_primaries, reskia_matrix3x3_t *toXYZD50) {
    reinterpret_cast<SkColorSpacePrimaries *>(color_pace_primaries)->toXYZD50(reinterpret_cast<skcms_Matrix3x3 *>(toXYZD50));
}

}
