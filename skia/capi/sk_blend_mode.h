//
// Created by dolphilia on 2024/01/06.
//

#ifndef RAIA_SKIA_SK_BLEND_MODE_H
#define RAIA_SKIA_SK_BLEND_MODE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t reskia_blend_mode_t;

/**
 * mode must be a valid SkBlendMode.
 * src/dst: non-null out params.
 * Invalid input returns false.
 * Skia: (SkBlendMode mode, SkBlendModeCoeff *src, SkBlendModeCoeff *dst) -> bool.
 */
bool SkBlendMode_SkBlendMode_AsCoeff(reskia_blend_mode_t mode, void *src, void *dst);
/**
 * blendMode must be a valid SkBlendMode.
 * Invalid input returns NULL.
 * Returned pointer is borrowed static storage.
 * Skia: (SkBlendMode blendMode) -> const char *.
 */
const char *SkBlendMode_SkBlendMode_Name(reskia_blend_mode_t blendMode);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_BLEND_MODE_H
