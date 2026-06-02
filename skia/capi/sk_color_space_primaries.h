//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_COLOR_SPACE_PRIMARIES_H
#define RAIA_SKIA_SK_COLOR_SPACE_PRIMARIES_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_color_space_primaries_t reskia_color_space_primaries_t;
typedef struct reskia_matrix3x3_t reskia_matrix3x3_t;

void SkColorSpacePrimaries_delete(reskia_color_space_primaries_t *color_pace_primaries); // (SkColorSpacePrimaries *color_pace_primaries)
/**
 * out: toXYZD50 must be non-NULL. No-op for NULL input.
 * (SkColorSpacePrimaries *color_pace_primaries, skcms_Matrix3x3 *toXYZD50)
 */
void SkColorSpacePrimaries_toXYZD50(reskia_color_space_primaries_t *color_pace_primaries, reskia_matrix3x3_t *toXYZD50);
bool SkColorSpacePrimaries_Equal(const reskia_color_space_primaries_t *a, const reskia_color_space_primaries_t *b); // Returns true when both inputs are NULL, false when only one is NULL.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_COLOR_SPACE_PRIMARIES_H
