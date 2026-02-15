//
// Created by dolphilia on 2024/01/13.
//

#ifndef RAIA_SKIA_SK_SHADERS_H
#define RAIA_SKIA_SK_SHADERS_H

#include <stdint.h>

#include "../static/static_sk_blender.h"
#include "../static/static_sk_color_space.h"
#include "../static/static_sk_shader.h"

typedef int reskia_blender_t;
typedef struct reskia_color_4f_t reskia_color_4f_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef uint32_t reskia_color_t;
typedef int32_t reskia_shaders_blend_mode_t;

#ifdef __cplusplus
extern "C" {
#endif

sk_shader_t SkShaders_Empty(); // () -> sk_shader_t
sk_shader_t SkShaders_Color(reskia_color_t color); // (SkColor color) -> sk_shader_t
sk_shader_t SkShaders_Color_2(const reskia_color_4f_t *color4f, sk_color_space_t color_space); // (const SkColor4f *color4f, sk_color_space_t color_space) -> sk_shader_t
sk_shader_t SkShaders_Blend(reskia_shaders_blend_mode_t mode, sk_shader_t dst, sk_shader_t src); // (SkBlendMode mode, sk_shader_t dst, sk_shader_t src) -> sk_shader_t
sk_shader_t SkShaders_Blend_2(reskia_blender_t value, sk_shader_t dst, sk_shader_t src); // (sk_blender_t value, sk_shader_t dst, sk_shader_t src) -> sk_shader_t
sk_shader_t SkShaders_CoordClamp(sk_shader_t shader, const reskia_rect_t *subset); // (sk_shader_t shader, const SkRect *subset) -> sk_shader_t

//sk_sp< SkShader > SkShaders_MakeFractalNoise(SkScalar baseFrequencyX, SkScalar baseFrequencyY, int numOctaves, SkScalar seed, const SkISize *tileSize);
//sk_sp< SkShader > SkShaders_MakeTurbulence(SkScalar baseFrequencyX, SkScalar baseFrequencyY, int numOctaves, SkScalar seed, const SkISize *tileSize);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_SHADERS_H
