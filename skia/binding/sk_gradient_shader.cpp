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

void SkGradientShader_delete(void * gradientShader) {
    delete static_cast<SkGradientShader *>(gradientShader);
}

// static

sk_shader_t SkGradientShader_MakeLinear(const void * pts, const void * colors, const void * pos, int count, int mode, uint32_t flags, const void *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeLinear(static_cast<const SkPoint *>(pts), static_cast<const SkColor *>(colors), static_cast<const SkScalar *>(pos), count, static_cast<SkTileMode>(mode), flags, static_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeLinear_2(const void * pts, const void * colors, sk_color_space_t color_space, const void * pos, int count, int mode, const void *interpolation, const void *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeLinear(static_cast<const SkPoint *>(pts), static_cast<const SkColor4f *>(colors), static_sk_color_space_move(color_space), static_cast<const SkScalar *>(pos), count, static_cast<SkTileMode>(mode), * static_cast<const SkGradientShader::Interpolation *>(interpolation), static_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeLinear_3(const void * pts, const void * colors, sk_color_space_t color_space, const void * pos, int count, int mode, uint32_t flags, const void *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeLinear(static_cast<const SkPoint *>(pts), static_cast<const SkColor4f *>(colors), static_sk_color_space_move(color_space), static_cast<const SkScalar *>(pos), count, static_cast<SkTileMode>(mode), flags, static_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeRadial(const void *center, float radius, const void * colors, const void * pos, int count, int mode, uint32_t flags, const void *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeRadial(* static_cast<const SkPoint *>(center), radius, static_cast<const SkColor *>(colors), static_cast<const SkScalar *>(pos), count, static_cast<SkTileMode>(mode), flags, static_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeRadial_2(const void *center, float radius, const void * colors, sk_color_space_t color_space, const void * pos, int count, int mode, const void *interpolation, const void *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeRadial(* static_cast<const SkPoint *>(center), radius, static_cast<const SkColor4f *>(colors), static_sk_color_space_move(color_space), static_cast<const SkScalar *>(pos), count, static_cast<SkTileMode>(mode), * static_cast<const SkGradientShader::Interpolation *>(interpolation), static_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeRadial_3(const void *center, float radius, const void * colors, sk_color_space_t color_space, const void * pos, int count, int mode, uint32_t flags, const void *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeRadial(* static_cast<const SkPoint *>(center), radius, static_cast<const SkColor4f *>(colors), static_sk_color_space_move(color_space), static_cast<const SkScalar *>(pos), count, static_cast<SkTileMode>(mode), flags, static_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeTwoPointConical(const void *start, float startRadius, const void *end, float endRadius, const void * colors, const void * pos, int count, int mode, uint32_t flags, const void *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeTwoPointConical(* static_cast<const SkPoint *>(start), startRadius, * static_cast<const SkPoint *>(end), endRadius, static_cast<const SkColor *>(colors), static_cast<const SkScalar *>(pos), count, static_cast<SkTileMode>(mode), flags, static_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeTwoPointConical_2(const void *start, float startRadius, const void *end, float endRadius, const void * colors, sk_color_space_t color_space, const void * pos, int count, int mode, const void *interpolation, const void *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeTwoPointConical(* static_cast<const SkPoint *>(start), startRadius, * static_cast<const SkPoint *>(end), endRadius, static_cast<const SkColor4f *>(colors), static_sk_color_space_move(color_space), static_cast<const SkScalar *>(pos), count, static_cast<SkTileMode>(mode), * static_cast<const SkGradientShader::Interpolation *>(interpolation), static_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeTwoPointConical_3(const void *start, float startRadius, const void *end, float endRadius, const void * colors, sk_color_space_t color_space, const void * pos, int count, int mode, uint32_t flags, const void *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeTwoPointConical(* static_cast<const SkPoint *>(start), startRadius, * static_cast<const SkPoint *>(end), endRadius, static_cast<const SkColor4f *>(colors), static_sk_color_space_move(color_space), static_cast<const SkScalar *>(pos), count, static_cast<SkTileMode>(mode), flags, static_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeSweep(float cx, float cy, const void * colors, const void * pos, int count, int mode, float startAngle, float endAngle, uint32_t flags, const void *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeSweep(cx, cy, static_cast<const SkColor *>(colors), static_cast<const SkScalar *>(pos), count, static_cast<SkTileMode>(mode), startAngle, endAngle, flags, static_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeSweep_2(float cx, float cy, const void * colors, const void * pos, int count, uint32_t flags, const void *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeSweep(cx, cy, static_cast<const SkColor *>(colors), static_cast<const SkScalar *>(pos), count, flags, static_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeSweep_3(float cx, float cy, const void * colors, sk_color_space_t color_space, const void * pos, int count, int mode, float startAngle, float endAngle, const void *interpolation, const void *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeSweep(cx, cy, static_cast<const SkColor4f *>(colors), static_sk_color_space_move(color_space), static_cast<const SkScalar *>(pos), count, static_cast<SkTileMode>(mode), startAngle, endAngle, * static_cast<const SkGradientShader::Interpolation *>(interpolation), static_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeSweep_4(float cx, float cy, const void * colors, sk_color_space_t color_space, const void * pos, int count, int mode, float startAngle, float endAngle, uint32_t flags, const void *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeSweep(cx, cy, static_cast<const SkColor4f *>(colors), static_sk_color_space_move(color_space), static_cast<const SkScalar *>(pos), count, static_cast<SkTileMode>(mode), startAngle, endAngle, flags, static_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkGradientShader_MakeSweep_5(float cx, float cy, const void * colors, sk_color_space_t color_space, const void * pos, int count, uint32_t flags, const void *localMatrix) {
    return static_sk_shader_make(SkGradientShader::MakeSweep(cx, cy, static_cast<const SkColor4f *>(colors), static_sk_color_space_move(color_space), static_cast<const SkScalar *>(pos), count, flags, static_cast<const SkMatrix *>(localMatrix)));
}

}
