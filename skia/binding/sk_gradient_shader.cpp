//
// Created by dolphilia on 2024/01/08.
//

#include "sk_gradient_shader.h"

#include "include/effects/SkGradientShader.h"

#include "../static/static_sk_shader.h"
#include "../static/static_sk_color_space.h"

#include "../static/static_sk_shader-internal.h"
#include "../static/static_sk_color_space-internal.h"

extern "C" {

void SkGradientShader_delete(reskia_gradient_shader_t *gradientShader) {
    delete reinterpret_cast<SkGradientShader *>(gradientShader);
}

// static

sk_shader_t SkGradientShader_MakeLinear(const reskia_point_t *pts, const reskia_color_t *colors, const float *pos, int count, int mode, uint32_t flags, const reskia_matrix_t *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeLinear(
        reinterpret_cast<const SkPoint *>(pts),
        reinterpret_cast<const SkColor *>(colors),
        reinterpret_cast<const SkScalar *>(pos),
        count,
        static_cast<SkTileMode>(mode),
        flags,
        reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeLinear_2(const reskia_point_t *pts, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, int mode, const reskia_gradient_shader_interpolation_t *interpolation, const reskia_matrix_t *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeLinear(
        reinterpret_cast<const SkPoint *>(pts),
        reinterpret_cast<const SkColor4f *>(colors),
        static_sk_color_space_get_entity(color_space),
        reinterpret_cast<const SkScalar *>(pos),
        count,
        static_cast<SkTileMode>(mode),
        *reinterpret_cast<const SkGradientShader::Interpolation *>(interpolation),
        reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeLinear_3(const reskia_point_t *pts, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, int mode, uint32_t flags, const reskia_matrix_t *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeLinear(
        reinterpret_cast<const SkPoint *>(pts),
        reinterpret_cast<const SkColor4f *>(colors),
        static_sk_color_space_get_entity(color_space),
        reinterpret_cast<const SkScalar *>(pos),
        count,
        static_cast<SkTileMode>(mode),
        flags,
        reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeRadial(const reskia_point_t *center, float radius, const reskia_color_t *colors, const float *pos, int count, int mode, uint32_t flags, const reskia_matrix_t *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeRadial(
        *reinterpret_cast<const SkPoint *>(center),
        radius,
        reinterpret_cast<const SkColor *>(colors),
        reinterpret_cast<const SkScalar *>(pos),
        count,
        static_cast<SkTileMode>(mode),
        flags,
        reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeRadial_2(const reskia_point_t *center, float radius, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, int mode, const reskia_gradient_shader_interpolation_t *interpolation, const reskia_matrix_t *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeRadial(
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

sk_shader_t SkGradientShader_MakeRadial_3(const reskia_point_t *center, float radius, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, int mode, uint32_t flags, const reskia_matrix_t *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeRadial(
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

sk_shader_t SkGradientShader_MakeTwoPointConical(const reskia_point_t *start, float startRadius, const reskia_point_t *end, float endRadius, const reskia_color_t *colors, const float *pos, int count, int mode, uint32_t flags, const reskia_matrix_t *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeTwoPointConical(
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

sk_shader_t SkGradientShader_MakeTwoPointConical_2(const reskia_point_t *start, float startRadius, const reskia_point_t *end, float endRadius, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, int mode, const reskia_gradient_shader_interpolation_t *interpolation, const reskia_matrix_t *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeTwoPointConical(
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

sk_shader_t SkGradientShader_MakeTwoPointConical_3(const reskia_point_t *start, float startRadius, const reskia_point_t *end, float endRadius, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, int mode, uint32_t flags, const reskia_matrix_t *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeTwoPointConical(
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

sk_shader_t SkGradientShader_MakeSweep(float cx, float cy, const reskia_color_t *colors, const float *pos, int count, int mode, float startAngle, float endAngle, uint32_t flags, const reskia_matrix_t *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeSweep(
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

sk_shader_t SkGradientShader_MakeSweep_2(float cx, float cy, const reskia_color_t *colors, const float *pos, int count, uint32_t flags, const reskia_matrix_t *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeSweep(
        cx,
        cy,
        reinterpret_cast<const SkColor *>(colors),
        reinterpret_cast<const SkScalar *>(pos),
        count,
        flags,
        reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeSweep_3(float cx, float cy, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, int mode, float startAngle, float endAngle, const reskia_gradient_shader_interpolation_t *interpolation, const reskia_matrix_t *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeSweep(
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

sk_shader_t SkGradientShader_MakeSweep_4(float cx, float cy, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, int mode, float startAngle, float endAngle, uint32_t flags, const reskia_matrix_t *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeSweep(
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
    return static_sk_shader_make(SkGradientShader::MakeSweep(
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
