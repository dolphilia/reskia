//
// Created by dolphilia on 2024/01/08.
//

#include "sk_gradient_shader.h"

#include "include/effects/SkGradientShader.h"

#include "../handles/static_sk_shader.h"
#include "../handles/static_sk_color_space.h"

#include "../handles/static_sk_shader-internal.h"
#include "../handles/static_sk_color_space-internal.h"

#include <utility>

namespace {

bool valid_tile_mode(reskia_gradient_shader_tile_mode_t mode) {
    return mode >= 0 && mode <= static_cast<reskia_gradient_shader_tile_mode_t>(SkTileMode::kLastTileMode);
}

bool valid_gradient_inputs(const void *colors, int count, reskia_gradient_shader_tile_mode_t mode) {
    return colors != nullptr && count > 0 && valid_tile_mode(mode);
}

sk_shader_t make_shader_handle(sk_sp<SkShader> shader) {
    return shader ? static_sk_shader_make(std::move(shader)) : 0;
}

}  // namespace

extern "C" {

void SkGradientShader_delete(reskia_gradient_shader_t *gradientShader) {
    delete reinterpret_cast<SkGradientShader *>(gradientShader);
}

// static

sk_shader_t SkGradientShader_MakeLinear(const reskia_point_t *pts, const reskia_color_t *colors, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, uint32_t flags, const reskia_matrix_t *localMatrix) {
    if (pts == nullptr || !valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    return make_shader_handle(SkGradientShader::MakeLinear(
        reinterpret_cast<const SkPoint *>(pts),
        reinterpret_cast<const SkColor *>(colors),
        reinterpret_cast<const SkScalar *>(pos),
        count,
        static_cast<SkTileMode>(mode),
        flags,
        reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeLinear4fWithInterpolation(const reskia_point_t *pts, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, const reskia_gradient_shader_interpolation_t *interpolation, const reskia_matrix_t *localMatrix) {
    if (pts == nullptr || interpolation == nullptr || !valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    return make_shader_handle(SkGradientShader::MakeLinear(
        reinterpret_cast<const SkPoint *>(pts),
        reinterpret_cast<const SkColor4f *>(colors),
        static_sk_color_space_get_entity(color_space),
        reinterpret_cast<const SkScalar *>(pos),
        count,
        static_cast<SkTileMode>(mode),
        *reinterpret_cast<const SkGradientShader::Interpolation *>(interpolation),
        reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeLinear4fWithFlags(const reskia_point_t *pts, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, uint32_t flags, const reskia_matrix_t *localMatrix) {
    if (pts == nullptr || !valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    return make_shader_handle(SkGradientShader::MakeLinear(
        reinterpret_cast<const SkPoint *>(pts),
        reinterpret_cast<const SkColor4f *>(colors),
        static_sk_color_space_get_entity(color_space),
        reinterpret_cast<const SkScalar *>(pos),
        count,
        static_cast<SkTileMode>(mode),
        flags,
        reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeRadial(const reskia_point_t *center, float radius, const reskia_color_t *colors, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, uint32_t flags, const reskia_matrix_t *localMatrix) {
    if (center == nullptr || !valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    return make_shader_handle(SkGradientShader::MakeRadial(
        *reinterpret_cast<const SkPoint *>(center),
        radius,
        reinterpret_cast<const SkColor *>(colors),
        reinterpret_cast<const SkScalar *>(pos),
        count,
        static_cast<SkTileMode>(mode),
        flags,
        reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeRadial4fWithInterpolation(const reskia_point_t *center, float radius, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, const reskia_gradient_shader_interpolation_t *interpolation, const reskia_matrix_t *localMatrix) {
    if (center == nullptr || interpolation == nullptr || !valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    return make_shader_handle(SkGradientShader::MakeRadial(
        *reinterpret_cast<const SkPoint *>(center),
        radius,
        reinterpret_cast<const SkColor4f *>(colors),
        static_sk_color_space_get_entity(color_space),
        reinterpret_cast<const SkScalar *>(pos),
        count,
        static_cast<SkTileMode>(mode),
        *reinterpret_cast<const SkGradientShader::Interpolation *>(interpolation),
        reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeRadial4fWithFlags(const reskia_point_t *center, float radius, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, uint32_t flags, const reskia_matrix_t *localMatrix) {
    if (center == nullptr || !valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    return make_shader_handle(SkGradientShader::MakeRadial(
        *reinterpret_cast<const SkPoint *>(center),
        radius,
        reinterpret_cast<const SkColor4f *>(colors),
        static_sk_color_space_get_entity(color_space),
        reinterpret_cast<const SkScalar *>(pos),
        count,
        static_cast<SkTileMode>(mode),
        flags,
        reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeTwoPointConical(const reskia_point_t *start, float startRadius, const reskia_point_t *end, float endRadius, const reskia_color_t *colors, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, uint32_t flags, const reskia_matrix_t *localMatrix) {
    if (start == nullptr || end == nullptr || !valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    return make_shader_handle(SkGradientShader::MakeTwoPointConical(
        *reinterpret_cast<const SkPoint *>(start),
        startRadius,
        *reinterpret_cast<const SkPoint *>(end),
        endRadius,
        reinterpret_cast<const SkColor *>(colors),
        reinterpret_cast<const SkScalar *>(pos),
        count,
        static_cast<SkTileMode>(mode),
        flags,
        reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeTwoPointConical4fWithInterpolation(const reskia_point_t *start, float startRadius, const reskia_point_t *end, float endRadius, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, const reskia_gradient_shader_interpolation_t *interpolation, const reskia_matrix_t *localMatrix) {
    if (start == nullptr || end == nullptr || interpolation == nullptr || !valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    return make_shader_handle(SkGradientShader::MakeTwoPointConical(
        *reinterpret_cast<const SkPoint *>(start),
        startRadius,
        *reinterpret_cast<const SkPoint *>(end),
        endRadius,
        reinterpret_cast<const SkColor4f *>(colors),
        static_sk_color_space_get_entity(color_space),
        reinterpret_cast<const SkScalar *>(pos),
        count,
        static_cast<SkTileMode>(mode),
        *reinterpret_cast<const SkGradientShader::Interpolation *>(interpolation),
        reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeTwoPointConical4fWithFlags(const reskia_point_t *start, float startRadius, const reskia_point_t *end, float endRadius, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, uint32_t flags, const reskia_matrix_t *localMatrix) {
    if (start == nullptr || end == nullptr || !valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    return make_shader_handle(SkGradientShader::MakeTwoPointConical(
        *reinterpret_cast<const SkPoint *>(start),
        startRadius,
        *reinterpret_cast<const SkPoint *>(end),
        endRadius,
        reinterpret_cast<const SkColor4f *>(colors),
        static_sk_color_space_get_entity(color_space),
        reinterpret_cast<const SkScalar *>(pos),
        count,
        static_cast<SkTileMode>(mode),
        flags,
        reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeSweep(float cx, float cy, const reskia_color_t *colors, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, float startAngle, float endAngle, uint32_t flags, const reskia_matrix_t *localMatrix) {
    if (!valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    return make_shader_handle(SkGradientShader::MakeSweep(
        cx,
        cy,
        reinterpret_cast<const SkColor *>(colors),
        reinterpret_cast<const SkScalar *>(pos),
        count,
        static_cast<SkTileMode>(mode),
        startAngle,
        endAngle,
        flags,
        reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeSweepWithFlagsOnly(float cx, float cy, const reskia_color_t *colors, const float *pos, int count, uint32_t flags, const reskia_matrix_t *localMatrix) {
    if (colors == nullptr || count <= 0) {
        return 0;
    }
    return make_shader_handle(SkGradientShader::MakeSweep(
        cx,
        cy,
        reinterpret_cast<const SkColor *>(colors),
        reinterpret_cast<const SkScalar *>(pos),
        count,
        flags,
        reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeSweep4fWithInterpolation(float cx, float cy, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, float startAngle, float endAngle, const reskia_gradient_shader_interpolation_t *interpolation, const reskia_matrix_t *localMatrix) {
    if (interpolation == nullptr || !valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    return make_shader_handle(SkGradientShader::MakeSweep(
        cx,
        cy,
        reinterpret_cast<const SkColor4f *>(colors),
        static_sk_color_space_get_entity(color_space),
        reinterpret_cast<const SkScalar *>(pos),
        count,
        static_cast<SkTileMode>(mode),
        startAngle,
        endAngle,
        *reinterpret_cast<const SkGradientShader::Interpolation *>(interpolation),
        reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeSweep4fWithFlags(float cx, float cy, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, float startAngle, float endAngle, uint32_t flags, const reskia_matrix_t *localMatrix) {
    if (!valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    return make_shader_handle(SkGradientShader::MakeSweep(
        cx,
        cy,
        reinterpret_cast<const SkColor4f *>(colors),
        static_sk_color_space_get_entity(color_space),
        reinterpret_cast<const SkScalar *>(pos),
        count,
        static_cast<SkTileMode>(mode),
        startAngle,
        endAngle,
        flags,
        reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeSweep_5(float cx, float cy, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, uint32_t flags, const reskia_matrix_t *localMatrix) {
    if (colors == nullptr || count <= 0) {
        return 0;
    }
    return make_shader_handle(SkGradientShader::MakeSweep(
        cx,
        cy,
        reinterpret_cast<const SkColor4f *>(colors),
        static_sk_color_space_get_entity(color_space),
        reinterpret_cast<const SkScalar *>(pos),
        count,
        flags,
        reinterpret_cast<const SkMatrix *>(localMatrix)));
}

}
