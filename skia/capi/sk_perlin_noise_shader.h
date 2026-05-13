//
// Created by dolphilia on 2024/01/29.
//

#ifndef RAIA_SKIA_SK_PERLIN_NOISE_SHADER_H
#define RAIA_SKIA_SK_PERLIN_NOISE_SHADER_H

#include "../handles/static_sk_shader.h"

typedef struct reskia_i_size_t reskia_i_size_t;

#ifdef __cplusplus
extern "C" {
#endif

// static

sk_shader_t SkPerlinNoiseShader_MakeFractalNoise(float baseFrequencyX, float baseFrequencyY, int numOctaves, float seed, const reskia_i_size_t *tileSize); // positive frequencies/octaves required; tileSize may be NULL; failure returns 0.
sk_shader_t SkPerlinNoiseShader_MakeTurbulence(float baseFrequencyX, float baseFrequencyY, int numOctaves, float seed, const reskia_i_size_t *tileSize); // positive frequencies/octaves required; tileSize may be NULL; failure returns 0.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PERLIN_NOISE_SHADER_H
