//
// Created by dolphilia on 2024/01/29.
//

#ifndef RAIA_SKIA_SK_PERLIN_NOISE_SHADER_H
#define RAIA_SKIA_SK_PERLIN_NOISE_SHADER_H

#include "../static/static_sk_shader.h"

typedef struct reskia_i_size_t reskia_i_size_t;

#ifdef __cplusplus
extern "C" {
#endif

// static

sk_shader_t SkPerlinNoiseShader_MakeFractalNoise(float baseFrequencyX, float baseFrequencyY, int numOctaves, float seed, const reskia_i_size_t *tileSize); // (SkScalar baseFrequencyX, SkScalar baseFrequencyY, int numOctaves, SkScalar seed, const SkISize *tileSize) -> sk_shader_t
sk_shader_t SkPerlinNoiseShader_MakeTurbulence(float baseFrequencyX, float baseFrequencyY, int numOctaves, float seed, const reskia_i_size_t *tileSize); // (SkScalar baseFrequencyX, SkScalar baseFrequencyY, int numOctaves, SkScalar seed, const SkISize *tileSize) -> sk_shader_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PERLIN_NOISE_SHADER_H
