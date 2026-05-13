//
// Created by dolphilia on 2024/01/29.
//

#include "sk_perlin_noise_shader.h"

#include "include/effects/SkPerlinNoiseShader.h"

#include "../handles/static_sk_shader.h"

#include "../handles/static_sk_shader-internal.h"

#include <utility>

namespace {

sk_shader_t make_shader_handle(sk_sp<SkShader> shader) {
    return shader ? static_sk_shader_make(std::move(shader)) : 0;
}

bool valid_perlin_inputs(float baseFrequencyX, float baseFrequencyY, int numOctaves) {
    return baseFrequencyX > 0.0f && baseFrequencyY > 0.0f && numOctaves > 0;
}

}  // namespace

extern "C" {

sk_shader_t SkPerlinNoiseShader_MakeFractalNoise(float baseFrequencyX, float baseFrequencyY, int numOctaves, float seed, const reskia_i_size_t *tileSize) {
    if (!valid_perlin_inputs(baseFrequencyX, baseFrequencyY, numOctaves)) {
        return 0;
    }
    return make_shader_handle(SkShaders::MakeFractalNoise(
        baseFrequencyX,
        baseFrequencyY,
        numOctaves,
        seed,
        reinterpret_cast<const SkISize *>(tileSize)));
}

sk_shader_t SkPerlinNoiseShader_MakeTurbulence(float baseFrequencyX, float baseFrequencyY, int numOctaves, float seed, const reskia_i_size_t *tileSize) {
    if (!valid_perlin_inputs(baseFrequencyX, baseFrequencyY, numOctaves)) {
        return 0;
    }
    return make_shader_handle(SkShaders::MakeTurbulence(
        baseFrequencyX,
        baseFrequencyY,
        numOctaves,
        seed,
        reinterpret_cast<const SkISize *>(tileSize)));
}

}
