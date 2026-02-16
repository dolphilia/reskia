//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_GRADIENT_SHADER_H
#define RAIA_SKIA_SK_GRADIENT_SHADER_H

#include <stdint.h>

#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_shader.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_gradient_shader_t reskia_gradient_shader_t;
typedef struct reskia_gradient_shader_interpolation_t reskia_gradient_shader_interpolation_t;
typedef struct reskia_point_t reskia_point_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_color_4f_t reskia_color_4f_t;
typedef uint32_t reskia_color_t;
typedef int32_t reskia_gradient_shader_tile_mode_t;

void SkGradientShader_delete(reskia_gradient_shader_t *gradientShader); // (SkGradientShader * gradientShader)

// static

sk_shader_t SkGradientShader_MakeLinear(const reskia_point_t *pts, const reskia_color_t *colors, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, uint32_t flags, const reskia_matrix_t *localMatrix); // (const SkPoint pts[2], const SkColor colors[], const SkScalar pos[], int count, SkTileMode mode, uint32_t flags, const SkMatrix *localMatrix) -> sk_shader_t
sk_shader_t SkGradientShader_MakeLinear4fWithInterpolation(const reskia_point_t *pts, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, const reskia_gradient_shader_interpolation_t *interpolation, const reskia_matrix_t *localMatrix); // (const SkPoint pts[2], const SkColor4f colors[], sk_color_space_t color_space, const SkScalar pos[], int count, SkTileMode mode, const SkGradientShader::Interpolation *interpolation, const SkMatrix *localMatrix) -> sk_shader_t
sk_shader_t SkGradientShader_MakeLinear4fWithFlags(const reskia_point_t *pts, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, uint32_t flags, const reskia_matrix_t *localMatrix); // (const SkPoint pts[2], const SkColor4f colors[], sk_color_space_t color_space, const SkScalar pos[], int count, SkTileMode mode, uint32_t flags, const SkMatrix *localMatrix) -> sk_shader_t
sk_shader_t SkGradientShader_MakeRadial(const reskia_point_t *center, float radius, const reskia_color_t *colors, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, uint32_t flags, const reskia_matrix_t *localMatrix); // (const SkPoint *center, SkScalar radius, const SkColor colors[], const SkScalar pos[], int count, SkTileMode mode, uint32_t flags, const SkMatrix *localMatrix) -> sk_shader_t
sk_shader_t SkGradientShader_MakeRadial4fWithInterpolation(const reskia_point_t *center, float radius, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, const reskia_gradient_shader_interpolation_t *interpolation, const reskia_matrix_t *localMatrix); // (const SkPoint *center, SkScalar radius, const SkColor4f colors[], sk_color_space_t color_space, const SkScalar pos[], int count, SkTileMode mode, const SkGradientShader::Interpolation *interpolation, const SkMatrix *localMatrix) -> sk_shader_t
sk_shader_t SkGradientShader_MakeRadial4fWithFlags(const reskia_point_t *center, float radius, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, uint32_t flags, const reskia_matrix_t *localMatrix); // (const SkPoint *center, SkScalar radius, const SkColor4f colors[], sk_color_space_t color_space, const SkScalar pos[], int count, SkTileMode mode, uint32_t flags, const SkMatrix *localMatrix) -> sk_shader_t
sk_shader_t SkGradientShader_MakeTwoPointConical(const reskia_point_t *start, float startRadius, const reskia_point_t *end, float endRadius, const reskia_color_t *colors, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, uint32_t flags, const reskia_matrix_t *localMatrix); // (const SkPoint *start, SkScalar startRadius, const SkPoint *end, SkScalar endRadius, const SkColor colors[], const SkScalar pos[], int count, SkTileMode mode, uint32_t flags, const SkMatrix *localMatrix) -> sk_shader_t
sk_shader_t SkGradientShader_MakeTwoPointConical4fWithInterpolation(const reskia_point_t *start, float startRadius, const reskia_point_t *end, float endRadius, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, const reskia_gradient_shader_interpolation_t *interpolation, const reskia_matrix_t *localMatrix); // (const SkPoint *start, SkScalar startRadius, const SkPoint *end, SkScalar endRadius, const SkColor4f colors[], sk_color_space_t color_space, const SkScalar pos[], int count, SkTileMode mode, const SkGradientShader::Interpolation *interpolation, const SkMatrix *localMatrix) -> sk_shader_t
sk_shader_t SkGradientShader_MakeTwoPointConical4fWithFlags(const reskia_point_t *start, float startRadius, const reskia_point_t *end, float endRadius, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, uint32_t flags, const reskia_matrix_t *localMatrix); // (const SkPoint *start, SkScalar startRadius, const SkPoint *end, SkScalar endRadius, const SkColor4f colors[], sk_color_space_t color_space, const SkScalar pos[], int count, SkTileMode mode, uint32_t flags, const SkMatrix *localMatrix) -> sk_shader_t
sk_shader_t SkGradientShader_MakeSweep(float cx, float cy, const reskia_color_t *colors, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, float startAngle, float endAngle, uint32_t flags, const reskia_matrix_t *localMatrix); // (SkScalar cx, SkScalar cy, const SkColor colors[], const SkScalar pos[], int count, SkTileMode mode, SkScalar startAngle, SkScalar endAngle, uint32_t flags, const SkMatrix *localMatrix) -> sk_shader_t
sk_shader_t SkGradientShader_MakeSweepWithFlagsOnly(float cx, float cy, const reskia_color_t *colors, const float *pos, int count, uint32_t flags, const reskia_matrix_t *localMatrix); // (SkScalar cx, SkScalar cy, const SkColor colors[], const SkScalar pos[], int count, uint32_t flags, const SkMatrix *localMatrix) -> sk_shader_t
sk_shader_t SkGradientShader_MakeSweep4fWithInterpolation(float cx, float cy, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, float startAngle, float endAngle, const reskia_gradient_shader_interpolation_t *interpolation, const reskia_matrix_t *localMatrix); // (SkScalar cx, SkScalar cy, const SkColor4f colors[], sk_color_space_t color_space, const SkScalar pos[], int count, SkTileMode mode, SkScalar startAngle, SkScalar endAngle, const SkGradientShader::Interpolation *interpolation, const SkMatrix *localMatrix) -> sk_shader_t
sk_shader_t SkGradientShader_MakeSweep4fWithFlags(float cx, float cy, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, reskia_gradient_shader_tile_mode_t mode, float startAngle, float endAngle, uint32_t flags, const reskia_matrix_t *localMatrix); // (SkScalar cx, SkScalar cy, const SkColor4f colors[], sk_color_space_t color_space, const SkScalar pos[], int count, SkTileMode mode, SkScalar startAngle, SkScalar endAngle, uint32_t flags, const SkMatrix *localMatrix) -> sk_shader_t
sk_shader_t SkGradientShader_MakeSweep_5(float cx, float cy, const reskia_color_4f_t *colors, sk_color_space_t color_space, const float *pos, int count, uint32_t flags, const reskia_matrix_t *localMatrix); // (SkScalar cx, SkScalar cy, const SkColor4f colors[], sk_color_space_t color_space, const SkScalar pos[], int count, uint32_t flags, const SkMatrix *localMatrix) -> sk_shader_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_GRADIENT_SHADER_H
