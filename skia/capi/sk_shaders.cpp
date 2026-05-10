//
// Created by dolphilia on 2024/01/13.
//

#include "sk_shaders.h"

#include "include/core/SkBlender.h"
#include "include/core/SkShader.h"

#include <utility>

#include "../handles/static_sk_shader.h"
#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_blender.h"

#include "../handles/static_sk_shader-internal.h"
#include "../handles/static_sk_color_space-internal.h"
#include "../handles/static_sk_blender-internal.h"

namespace {

sk_shader_t make_shader_handle(sk_sp<SkShader> shader) {
    if (!shader) {
        return 0;
    }
    return static_sk_shader_make(std::move(shader));
}

} // namespace

extern "C" {

sk_shader_t SkShaders_Empty() {
    return make_shader_handle(SkShaders::Empty());
}

sk_shader_t SkShaders_Color(reskia_color_t color) {
    return make_shader_handle(SkShaders::Color(color));
}

sk_shader_t SkShaders_ColorWithColor4fAndColorSpace(const reskia_color_4f_t *color4f, sk_color_space_t color_space) {
    if (color4f == nullptr) {
        return 0;
    }
    return make_shader_handle(SkShaders::Color(*reinterpret_cast<const SkColor4f *>(color4f), static_sk_color_space_get_entity(color_space)));
}

sk_shader_t SkShaders_Blend(reskia_shaders_blend_mode_t mode, sk_shader_t dst, sk_shader_t src) {
    return make_shader_handle(SkShaders::Blend(static_cast<SkBlendMode>(mode), static_sk_shader_get_entity(dst), static_sk_shader_get_entity(src)));
}

sk_shader_t SkShaders_BlendWithBlender(reskia_blender_t value, sk_shader_t dst, sk_shader_t src) {
    return make_shader_handle(SkShaders::Blend(static_sk_blender_get_entity(value), static_sk_shader_get_entity(dst), static_sk_shader_get_entity(src)));
}

sk_shader_t SkShaders_CoordClamp(sk_shader_t shader, const reskia_rect_t *subset) {
    if (subset == nullptr) {
        return 0;
    }
    return make_shader_handle(SkShaders::CoordClamp(static_sk_shader_get_entity(shader), *reinterpret_cast<const SkRect *>(subset)));
}

//sk_sp< SkShader > SkShaders_MakeFractalNoise(SkScalar baseFrequencyX, SkScalar baseFrequencyY, int numOctaves, SkScalar seed, const SkISize *tileSize) {
//    return SkShaders::MakeFractalNoise(baseFrequencyX, baseFrequencyY, numOctaves, seed, tileSize);
//}

//sk_sp< SkShader > SkShaders_MakeTurbulence(SkScalar baseFrequencyX, SkScalar baseFrequencyY, int numOctaves, SkScalar seed, const SkISize *tileSize) {
//    return SkShaders::MakeTurbulence(baseFrequencyX, baseFrequencyY, numOctaves, seed, tileSize);
//}

}
