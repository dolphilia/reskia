//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_IMAGE_FILTERS_H
#define RAIA_SKIA_SK_IMAGE_FILTERS_H

#include <stdint.h>
#include "../handles/static_sk_blender.h"
#include "../handles/static_sk_color_filter.h"
#include "../handles/static_sk_i_point.h"
#include "../handles/static_sk_i_size.h"
#include "../handles/static_sk_image.h"
#include "../handles/static_sk_image_filter.h"
#include "../handles/static_sk_picture.h"
#include "../handles/static_sk_shader.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int reskia_blender_t;
typedef struct reskia_color_filter_t reskia_color_filter_t;
typedef struct reskia_crop_rect_t reskia_crop_rect_t;
typedef struct reskia_i_point_t reskia_i_point_t;
typedef struct reskia_i_size_t reskia_i_size_t;
typedef struct reskia_image_filter_sp_t reskia_image_filter_sp_t;
typedef struct reskia_image_filters_t reskia_image_filters_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_point3_t reskia_point3_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_runtime_shader_builder_t reskia_runtime_shader_builder_t;
typedef struct reskia_sampling_options_t reskia_sampling_options_t;
typedef int reskia_string_view_t;
typedef uint32_t reskia_color_t;
typedef int32_t reskia_image_filters_blend_mode_t;
typedef int32_t reskia_image_filters_tile_mode_t;
typedef int32_t reskia_image_filters_color_channel_t;
typedef int32_t reskia_image_filters_dither_t;

void SkImageFilters_delete(reskia_image_filters_t *imageFilters); // (SkImageFilters *imageFilters)

// static

sk_image_filter_t SkImageFilters_Arithmetic(float k1, float k2, float k3, float k4, bool enforcePMColor, sk_image_filter_t background, sk_image_filter_t foreground, const reskia_crop_rect_t *cropRect); // (SkScalar k1, SkScalar k2, SkScalar k3, SkScalar k4, bool enforcePMColor, sk_image_filter_t background, sk_image_filter_t foreground, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_Blend(reskia_image_filters_blend_mode_t mode, sk_image_filter_t background, sk_image_filter_t foreground, const reskia_crop_rect_t *cropRect); // (SkBlendMode mode, sk_image_filter_t background, sk_image_filter_t foreground, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_BlendWithBlender(reskia_blender_t blender, sk_image_filter_t background, sk_image_filter_t foreground, const reskia_crop_rect_t *cropRect); // (sk_blender_t blender, sk_image_filter_t background, sk_image_filter_t foreground, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_Blur(float sigmaX, float sigmaY, reskia_image_filters_tile_mode_t tileMode, sk_image_filter_t input, const reskia_crop_rect_t *cropRect); // (SkScalar sigmaX, SkScalar sigmaY, SkTileMode tileMode, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_BlurWithoutTileMode(float sigmaX, float sigmaY, sk_image_filter_t input, const reskia_crop_rect_t *cropRect); // (SkScalar sigmaX, SkScalar sigmaY, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_ColorFilter(sk_color_filter_t cf, sk_image_filter_t input, const reskia_crop_rect_t *cropRect); // (sk_color_filter_t cf, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_Compose(sk_image_filter_t outer, sk_image_filter_t inner); // (sk_image_filter_t outer, sk_image_filter_t inner) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_Crop(const reskia_rect_t *rect, reskia_image_filters_tile_mode_t tileMode, sk_image_filter_t input); // (const SkRect *rect, SkTileMode tileMode, sk_image_filter_t input) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_CropWithRect(const reskia_rect_t *rect, sk_image_filter_t input); // (const SkRect *rect, sk_image_filter_t input) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_DisplacementMap(reskia_image_filters_color_channel_t xChannelSelector, reskia_image_filters_color_channel_t yChannelSelector, float scale, sk_image_filter_t displacement, sk_image_filter_t color, const reskia_crop_rect_t *cropRect); // (SkColorChannel xChannelSelector, SkColorChannel yChannelSelector, SkScalar scale, sk_image_filter_t displacement, sk_image_filter_t color, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_DropShadow(float dx, float dy, float sigmaX, float sigmaY, reskia_color_t color, sk_image_filter_t input, const reskia_crop_rect_t *cropRect); // (SkScalar dx, SkScalar dy, SkScalar sigmaX, SkScalar sigmaY, SkColor color, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_DropShadowOnly(float dx, float dy, float sigmaX, float sigmaY, reskia_color_t color, sk_image_filter_t input, const reskia_crop_rect_t *cropRect); // (SkScalar dx, SkScalar dy, SkScalar sigmaX, SkScalar sigmaY, SkColor color, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_Empty(); // () -> sk_image_filter_t
sk_image_filter_t SkImageFilters_Image(sk_image_t image, const reskia_rect_t *srcRect, const reskia_rect_t *dstRect, const reskia_sampling_options_t *sampling); // (sk_image_t image, const SkRect *srcRect, const SkRect *dstRect, const SkSamplingOptions *sampling) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_ImageWithSampling(sk_image_t image, const reskia_sampling_options_t *sampling); // (sk_image_t image, const SkSamplingOptions *sampling) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_Magnifier(const reskia_rect_t *lensBounds, float zoomAmount, float inset, const reskia_sampling_options_t *sampling, sk_image_filter_t input, const reskia_crop_rect_t *cropRect); // (const SkRect *lensBounds, SkScalar zoomAmount, SkScalar inset, const SkSamplingOptions *sampling, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_MatrixConvolution(const reskia_i_size_t *kernelSize, const float *kernel, float gain, float bias, const reskia_i_point_t *kernelOffset, reskia_image_filters_tile_mode_t tileMode, bool convolveAlpha, sk_image_filter_t input, const reskia_crop_rect_t *cropRect); // (const SkISize *kernelSize, const SkScalar kernel[], SkScalar gain, SkScalar bias, const SkIPoint *kernelOffset, SkTileMode tileMode, bool convolveAlpha, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_MatrixTransform(const reskia_matrix_t *matrix, const reskia_sampling_options_t *sampling, sk_image_filter_t input); // (const SkMatrix *matrix, const SkSamplingOptions *sampling, sk_image_filter_t input) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_Merge(reskia_image_filter_sp_t *filters, int count, const reskia_crop_rect_t *cropRect); // (sk_sp<SkImageFilter> *filters, int count, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_MergeTwo(sk_image_filter_t first, sk_image_filter_t second, const reskia_crop_rect_t *cropRect); // (sk_image_filter_t first, sk_image_filter_t second, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_Offset(float dx, float dy, sk_image_filter_t input, const reskia_crop_rect_t *cropRect); // (SkScalar dx, SkScalar dy, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_Picture(sk_picture_t picture, const reskia_rect_t *targetRect); // (sk_picture_t picture, const SkRect *targetRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_PictureOnly(sk_picture_t picture); // (sk_picture_t picture) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_RuntimeShader(const reskia_runtime_shader_builder_t *builder, reskia_string_view_t childShaderName, sk_image_filter_t input); // (const SkRuntimeShaderBuilder *builder, string_view_t childShaderName, sk_image_filter_t input) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_RuntimeShaderWithSampleRadius(const reskia_runtime_shader_builder_t *builder, float sampleRadius, reskia_string_view_t childShaderName, sk_image_filter_t input); // (const SkRuntimeShaderBuilder *builder, SkScalar sampleRadius, string_view_t childShaderName, sk_image_filter_t input) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_RuntimeShaderWithChildShaderNames(const reskia_runtime_shader_builder_t *builder, reskia_string_view_t *childShaderNames, const reskia_image_filter_sp_t *inputs, int inputCount); // (const SkRuntimeShaderBuilder *builder, std::string_view childShaderNames[], const sk_sp<SkImageFilter> *inputs, int inputCount) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_RuntimeShaderWithMaxSampleRadius(const reskia_runtime_shader_builder_t *builder, float maxSampleRadius, reskia_string_view_t *childShaderNames, const reskia_image_filter_sp_t *inputs, int inputCount); // (const SkRuntimeShaderBuilder *builder, SkScalar maxSampleRadius, std::string_view childShaderNames[], const sk_sp<SkImageFilter> *inputs, int inputCount) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_Shader(sk_shader_t shader, const reskia_crop_rect_t *cropRect); // (sk_shader_t shader, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_ShaderWithDither(sk_shader_t shader, reskia_image_filters_dither_t dither, const reskia_crop_rect_t *cropRect); // (sk_shader_t shader, SkImageFilters::Dither dither, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_Tile(const reskia_rect_t *src, const reskia_rect_t *dst, sk_image_filter_t input); // (const SkRect *src, const SkRect *dst, sk_image_filter_t input) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_Dilate(float radiusX, float radiusY, sk_image_filter_t input, const reskia_crop_rect_t *cropRect); // (SkScalar radiusX, SkScalar radiusY, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_Erode(float radiusX, float radiusY, sk_image_filter_t input, const reskia_crop_rect_t *cropRect); // (SkScalar radiusX, SkScalar radiusY, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_DistantLitDiffuse(const reskia_point3_t *direction, reskia_color_t lightColor, float surfaceScale, float kd, sk_image_filter_t input, const reskia_crop_rect_t *cropRect); // (const SkPoint3 *direction, SkColor lightColor, SkScalar surfaceScale, SkScalar kd, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_PointLitDiffuse(const reskia_point3_t *location, reskia_color_t lightColor, float surfaceScale, float kd, sk_image_filter_t input, const reskia_crop_rect_t *cropRect); // (const SkPoint3 *location, SkColor lightColor, SkScalar surfaceScale, SkScalar kd, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_SpotLitDiffuse(const reskia_point3_t *location, const reskia_point3_t *target, float falloffExponent, float cutoffAngle, reskia_color_t lightColor, float surfaceScale, float kd, sk_image_filter_t input, const reskia_crop_rect_t *cropRect); // (const SkPoint3 *location, const SkPoint3 *target, SkScalar falloffExponent, SkScalar cutoffAngle, SkColor lightColor, SkScalar surfaceScale, SkScalar kd, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_DistantLitSpecular(const reskia_point3_t *direction, reskia_color_t lightColor, float surfaceScale, float ks, float shininess, sk_image_filter_t input, const reskia_crop_rect_t *cropRect); // (const SkPoint3 *direction, SkColor lightColor, SkScalar surfaceScale, SkScalar ks, SkScalar shininess, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_PointLitSpecular(const reskia_point3_t *location, reskia_color_t lightColor, float surfaceScale, float ks, float shininess, sk_image_filter_t input, const reskia_crop_rect_t *cropRect); // (const SkPoint3 *location, SkColor lightColor, SkScalar surfaceScale, SkScalar ks, SkScalar shininess, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
sk_image_filter_t SkImageFilters_SpotLitSpecular(const reskia_point3_t *location, const reskia_point3_t *target, float falloffExponent, float cutoffAngle, reskia_color_t lightColor, float surfaceScale, float ks, float shininess, sk_image_filter_t input, const reskia_crop_rect_t *cropRect); // (const SkPoint3 *location, const SkPoint3 *target, SkScalar falloffExponent, SkScalar cutoffAngle, SkColor lightColor, SkScalar surfaceScale, SkScalar ks, SkScalar shininess, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_IMAGE_FILTERS_H
