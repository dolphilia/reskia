//
// Created by dolphilia on 2024/01/08.
//

#include "sk_gradient_shader.h"

#include "include/effects/SkGradient.h"

#include "../handles/static_sk_shader.h"
#include "../handles/static_sk_color_space.h"

#include "../handles/static_sk_shader-internal.h"
#include "../handles/static_sk_color_space-internal.h"

#include <utility>
#include <vector>

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

SkSpan<const SkScalar> make_position_span(const float *pos, int count) {
    return pos != nullptr ? SkSpan<const SkScalar>(reinterpret_cast<const SkScalar *>(pos), static_cast<size_t>(count))
                          : SkSpan<const SkScalar>();
}

SkGradient make_gradient(const SkColor4f *colors,
                         sk_sp<SkColorSpace> colorSpace,
                         const float *pos,
                         int count,
                         SkTileMode mode,
                         const SkGradient::Interpolation& interpolation) {
    return SkGradient(
            SkGradient::Colors(
                    {colors, static_cast<size_t>(count)},
                    make_position_span(pos, count),
                    mode,
                    std::move(colorSpace)),
            interpolation);
}

SkGradient make_gradient_from_colors(const reskia_color_t *colors,
                                     const float *pos,
                                     int count,
                                     SkTileMode mode,
                                     uint32_t flags,
                                     std::vector<SkColor4f> *storage) {
    storage->clear();
    storage->reserve(static_cast<size_t>(count));
    for (int i = 0; i < count; ++i) {
        storage->push_back(SkColor4f::FromColor(static_cast<SkColor>(colors[i])));
    }
    return make_gradient(
            storage->data(),
            nullptr,
            pos,
            count,
            mode,
            SkGradient::Interpolation::FromFlags(flags));
}

}  // namespace

extern "C" {

void SkGradientShader_delete(reskia_gradient_shader_t *gradientShader) {
    (void)gradientShader;
}

// static

sk_shader_t SkGradientShader_MakeLinear(const reskia_point_t *pts, const reskia_color_t *colors, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, uint32_t flags, const reskia_matrix_t *localMatrix) {
    if (pts == nullptr || !valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    std::vector<SkColor4f> colorStorage;
    SkGradient gradient = make_gradient_from_colors(colors, pos, count, static_cast<SkTileMode>(mode), flags, &colorStorage);
    return make_shader_handle(SkShaders::LinearGradient(
            reinterpret_cast<const SkPoint *>(pts),
            gradient,
            reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeLinear4fWithInterpolation(const reskia_point_t *pts, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, const reskia_gradient_shader_interpolation_t *interpolation, const reskia_matrix_t *localMatrix) {
    if (pts == nullptr || interpolation == nullptr || !valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    SkGradient gradient = make_gradient(
            reinterpret_cast<const SkColor4f *>(colors),
            static_sk_color_space_get_entity(color_space),
            pos,
            count,
            static_cast<SkTileMode>(mode),
            *reinterpret_cast<const SkGradient::Interpolation *>(interpolation));
    return make_shader_handle(SkShaders::LinearGradient(
            reinterpret_cast<const SkPoint *>(pts),
            gradient,
            reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeLinear4fWithFlags(const reskia_point_t *pts, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, uint32_t flags, const reskia_matrix_t *localMatrix) {
    if (pts == nullptr || !valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    SkGradient gradient = make_gradient(
            reinterpret_cast<const SkColor4f *>(colors),
            static_sk_color_space_get_entity(color_space),
            pos,
            count,
            static_cast<SkTileMode>(mode),
            SkGradient::Interpolation::FromFlags(flags));
    return make_shader_handle(SkShaders::LinearGradient(
            reinterpret_cast<const SkPoint *>(pts),
            gradient,
            reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeRadial(const reskia_point_t *center, float radius, const reskia_color_t *colors, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, uint32_t flags, const reskia_matrix_t *localMatrix) {
    if (center == nullptr || !valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    std::vector<SkColor4f> colorStorage;
    SkGradient gradient = make_gradient_from_colors(colors, pos, count, static_cast<SkTileMode>(mode), flags, &colorStorage);
    return make_shader_handle(SkShaders::RadialGradient(
            *reinterpret_cast<const SkPoint *>(center),
            radius,
            gradient,
            reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeRadial4fWithInterpolation(const reskia_point_t *center, float radius, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, const reskia_gradient_shader_interpolation_t *interpolation, const reskia_matrix_t *localMatrix) {
    if (center == nullptr || interpolation == nullptr || !valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    SkGradient gradient = make_gradient(
            reinterpret_cast<const SkColor4f *>(colors),
            static_sk_color_space_get_entity(color_space),
            pos,
            count,
            static_cast<SkTileMode>(mode),
            *reinterpret_cast<const SkGradient::Interpolation *>(interpolation));
    return make_shader_handle(SkShaders::RadialGradient(
            *reinterpret_cast<const SkPoint *>(center),
            radius,
            gradient,
            reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeRadial4fWithFlags(const reskia_point_t *center, float radius, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, uint32_t flags, const reskia_matrix_t *localMatrix) {
    if (center == nullptr || !valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    SkGradient gradient = make_gradient(
            reinterpret_cast<const SkColor4f *>(colors),
            static_sk_color_space_get_entity(color_space),
            pos,
            count,
            static_cast<SkTileMode>(mode),
            SkGradient::Interpolation::FromFlags(flags));
    return make_shader_handle(SkShaders::RadialGradient(
            *reinterpret_cast<const SkPoint *>(center),
            radius,
            gradient,
            reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeTwoPointConical(const reskia_point_t *start, float startRadius, const reskia_point_t *end, float endRadius, const reskia_color_t *colors, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, uint32_t flags, const reskia_matrix_t *localMatrix) {
    if (start == nullptr || end == nullptr || !valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    std::vector<SkColor4f> colorStorage;
    SkGradient gradient = make_gradient_from_colors(colors, pos, count, static_cast<SkTileMode>(mode), flags, &colorStorage);
    return make_shader_handle(SkShaders::TwoPointConicalGradient(
            *reinterpret_cast<const SkPoint *>(start),
            startRadius,
            *reinterpret_cast<const SkPoint *>(end),
            endRadius,
            gradient,
            reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeTwoPointConical4fWithInterpolation(const reskia_point_t *start, float startRadius, const reskia_point_t *end, float endRadius, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, const reskia_gradient_shader_interpolation_t *interpolation, const reskia_matrix_t *localMatrix) {
    if (start == nullptr || end == nullptr || interpolation == nullptr || !valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    SkGradient gradient = make_gradient(
            reinterpret_cast<const SkColor4f *>(colors),
            static_sk_color_space_get_entity(color_space),
            pos,
            count,
            static_cast<SkTileMode>(mode),
            *reinterpret_cast<const SkGradient::Interpolation *>(interpolation));
    return make_shader_handle(SkShaders::TwoPointConicalGradient(
            *reinterpret_cast<const SkPoint *>(start),
            startRadius,
            *reinterpret_cast<const SkPoint *>(end),
            endRadius,
            gradient,
            reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeTwoPointConical4fWithFlags(const reskia_point_t *start, float startRadius, const reskia_point_t *end, float endRadius, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, uint32_t flags, const reskia_matrix_t *localMatrix) {
    if (start == nullptr || end == nullptr || !valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    SkGradient gradient = make_gradient(
            reinterpret_cast<const SkColor4f *>(colors),
            static_sk_color_space_get_entity(color_space),
            pos,
            count,
            static_cast<SkTileMode>(mode),
            SkGradient::Interpolation::FromFlags(flags));
    return make_shader_handle(SkShaders::TwoPointConicalGradient(
            *reinterpret_cast<const SkPoint *>(start),
            startRadius,
            *reinterpret_cast<const SkPoint *>(end),
            endRadius,
            gradient,
            reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeSweep(float cx, float cy, const reskia_color_t *colors, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, float startAngle, float endAngle, uint32_t flags, const reskia_matrix_t *localMatrix) {
    if (!valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    std::vector<SkColor4f> colorStorage;
    SkGradient gradient = make_gradient_from_colors(colors, pos, count, static_cast<SkTileMode>(mode), flags, &colorStorage);
    return make_shader_handle(SkShaders::SweepGradient(
            SkPoint::Make(cx, cy),
            startAngle,
            endAngle,
            gradient,
            reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeSweepWithFlagsOnly(float cx, float cy, const reskia_color_t *colors, const float *pos, int count, uint32_t flags, const reskia_matrix_t *localMatrix) {
    if (colors == nullptr || count <= 0) {
        return 0;
    }
    std::vector<SkColor4f> colorStorage;
    SkGradient gradient = make_gradient_from_colors(colors, pos, count, SkTileMode::kClamp, flags, &colorStorage);
    return make_shader_handle(SkShaders::SweepGradient(
            SkPoint::Make(cx, cy),
            gradient,
            reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeSweep4fWithInterpolation(float cx, float cy, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, float startAngle, float endAngle, const reskia_gradient_shader_interpolation_t *interpolation, const reskia_matrix_t *localMatrix) {
    if (interpolation == nullptr || !valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    SkGradient gradient = make_gradient(
            reinterpret_cast<const SkColor4f *>(colors),
            static_sk_color_space_get_entity(color_space),
            pos,
            count,
            static_cast<SkTileMode>(mode),
            *reinterpret_cast<const SkGradient::Interpolation *>(interpolation));
    return make_shader_handle(SkShaders::SweepGradient(
            SkPoint::Make(cx, cy),
            startAngle,
            endAngle,
            gradient,
            reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeSweep4fWithFlags(float cx, float cy, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, float startAngle, float endAngle, uint32_t flags, const reskia_matrix_t *localMatrix) {
    if (!valid_gradient_inputs(colors, count, mode)) {
        return 0;
    }
    SkGradient gradient = make_gradient(
            reinterpret_cast<const SkColor4f *>(colors),
            static_sk_color_space_get_entity(color_space),
            pos,
            count,
            static_cast<SkTileMode>(mode),
            SkGradient::Interpolation::FromFlags(flags));
    return make_shader_handle(SkShaders::SweepGradient(
            SkPoint::Make(cx, cy),
            startAngle,
            endAngle,
            gradient,
            reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeSweep4fWithFlagsOnly(float cx, float cy, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, uint32_t flags, const reskia_matrix_t *localMatrix) {
    if (colors == nullptr || count <= 0) {
        return 0;
    }
    SkGradient gradient = make_gradient(
            reinterpret_cast<const SkColor4f *>(colors),
            static_sk_color_space_get_entity(color_space),
            pos,
            count,
            SkTileMode::kClamp,
            SkGradient::Interpolation::FromFlags(flags));
    return make_shader_handle(SkShaders::SweepGradient(
            SkPoint::Make(cx, cy),
            gradient,
            reinterpret_cast<const SkMatrix *>(localMatrix)));
}

}
