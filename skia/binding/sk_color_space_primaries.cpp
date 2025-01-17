//
// Created by dolphilia on 2024/01/08.
//

#include "sk_color_space_primaries.h"

#include "include/core/SkColorSpace.h"

extern "C" {

void SkColorSpacePrimaries_delete(void *color_pace_primaries) {
    delete static_cast<SkColorSpacePrimaries *>(color_pace_primaries);
}

void SkColorSpacePrimaries_toXYZD50(void *color_pace_primaries, void *toXYZD50) {
    static_cast<SkColorSpacePrimaries *>(color_pace_primaries)->toXYZD50(static_cast<skcms_Matrix3x3 *>(toXYZD50));
}

}