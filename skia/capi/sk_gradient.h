//
// Created by Codex on 2026/06/01.
//

#ifndef RESKIA_SK_GRADIENT_H
#define RESKIA_SK_GRADIENT_H

#include <stddef.h>
#include <stdint.h>

#include "../handles/static_sk_color_space.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_color_4f_t reskia_color_4f_t;
typedef struct reskia_gradient_t reskia_gradient_t;
typedef struct reskia_gradient_colors_t reskia_gradient_colors_t;
typedef struct reskia_gradient_interpolation_t reskia_gradient_interpolation_t;
typedef int32_t reskia_gradient_tile_mode_t;
typedef int32_t reskia_gradient_in_premul_t;
typedef int32_t reskia_gradient_color_space_t;
typedef int32_t reskia_gradient_hue_method_t;

reskia_gradient_colors_t *SkGradient_Colors_new(void);
reskia_gradient_colors_t *SkGradient_Colors_newWithColorsPositionsModeColorSpace(const reskia_color_4f_t *colors, size_t color_count, const float *positions, size_t position_count, reskia_gradient_tile_mode_t mode, sk_color_space_t color_space);
void SkGradient_Colors_delete(reskia_gradient_colors_t *colors);
size_t SkGradient_Colors_colorCount(const reskia_gradient_colors_t *colors);
const reskia_color_4f_t *SkGradient_Colors_colors(const reskia_gradient_colors_t *colors);
size_t SkGradient_Colors_positionCount(const reskia_gradient_colors_t *colors);
const float *SkGradient_Colors_positions(const reskia_gradient_colors_t *colors);
sk_color_space_t SkGradient_Colors_colorSpace(const reskia_gradient_colors_t *colors);
reskia_gradient_tile_mode_t SkGradient_Colors_tileMode(const reskia_gradient_colors_t *colors);

reskia_gradient_interpolation_t *SkGradient_Interpolation_new(void);
reskia_gradient_interpolation_t *SkGradient_Interpolation_newWithValues(reskia_gradient_in_premul_t in_premul, reskia_gradient_color_space_t color_space, reskia_gradient_hue_method_t hue_method);
reskia_gradient_interpolation_t *SkGradient_Interpolation_FromFlags(uint32_t flags);
void SkGradient_Interpolation_delete(reskia_gradient_interpolation_t *interpolation);
reskia_gradient_in_premul_t SkGradient_Interpolation_inPremul(const reskia_gradient_interpolation_t *interpolation);
reskia_gradient_color_space_t SkGradient_Interpolation_colorSpace(const reskia_gradient_interpolation_t *interpolation);
reskia_gradient_hue_method_t SkGradient_Interpolation_hueMethod(const reskia_gradient_interpolation_t *interpolation);

reskia_gradient_t *SkGradient_new(void);
reskia_gradient_t *SkGradient_newWithColorsAndInterpolation(const reskia_gradient_colors_t *colors, const reskia_gradient_interpolation_t *interpolation);
void SkGradient_delete(reskia_gradient_t *gradient);
const reskia_gradient_colors_t *SkGradient_colors(const reskia_gradient_t *gradient);
const reskia_gradient_interpolation_t *SkGradient_interpolation(const reskia_gradient_t *gradient);

#ifdef __cplusplus
}
#endif

#endif // RESKIA_SK_GRADIENT_H
