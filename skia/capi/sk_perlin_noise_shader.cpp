//
// Created by dolphilia on 2024/01/29.
//

#include "sk_perlin_noise_shader.h"

#include "include/effects/SkPerlinNoiseShader.h"

#include "../handles/static_sk_shader.h"

#include "../handles/static_sk_shader-internal.h"

extern "C" {

sk_shader_t SkPerlinNoiseShader_MakeFractalNoise(float baseFrequencyX, float baseFrequencyY, int numOctaves, float seed, const reskia_i_size_t *tileSize) {
    return static_sk_shader_make(SkShaders::MakeFractalNoise(
        baseFrequencyX,
        baseFrequencyY,
        numOctaves,
        seed,
        reinterpret_cast<const SkISize *>(tileSize)));
}

sk_shader_t SkPerlinNoiseShader_MakeTurbulence(float baseFrequencyX, float baseFrequencyY, int numOctaves, float seed, const reskia_i_size_t *tileSize) {
    return static_sk_shader_make(SkShaders::MakeTurbulence(
        baseFrequencyX,
        baseFrequencyY,
        numOctaves,
        seed,
        reinterpret_cast<const SkISize *>(tileSize)));
}

}
