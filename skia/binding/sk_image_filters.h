//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_IMAGE_FILTERS_H
#define RAIA_SKIA_SK_IMAGE_FILTERS_H

#include <stdint.h>

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

void SkImageFilters_delete(reskia_image_filters_t *imageFilters); // (SkImageFilters *imageFilters)

// static

int SkImageFilters_Arithmetic(float k1, float k2, float k3, float k4, bool enforcePMColor, int background, int foreground, const reskia_crop_rect_t *cropRect); // (SkScalar k1, SkScalar k2, SkScalar k3, SkScalar k4, bool enforcePMColor, sk_image_filter_t background, sk_image_filter_t foreground, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
int SkImageFilters_Blend(int mode, int background, int foreground, const reskia_crop_rect_t *cropRect); // (SkBlendMode mode, sk_image_filter_t background, sk_image_filter_t foreground, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
int SkImageFilters_Blend_2(reskia_blender_t blender, int background, int foreground, const reskia_crop_rect_t *cropRect); // (sk_blender_t blender, sk_image_filter_t background, sk_image_filter_t foreground, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
int SkImageFilters_Blur(float sigmaX, float sigmaY, int tileMode, int input, const reskia_crop_rect_t *cropRect); // (SkScalar sigmaX, SkScalar sigmaY, SkTileMode tileMode, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
int SkImageFilters_Blur_2(float sigmaX, float sigmaY, int input, const reskia_crop_rect_t *cropRect); // (SkScalar sigmaX, SkScalar sigmaY, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
int SkImageFilters_ColorFilter(int cf, int input, const reskia_crop_rect_t *cropRect); // (sk_color_filter_t cf, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
int SkImageFilters_Compose(int outer, int inner); // (sk_image_filter_t outer, sk_image_filter_t inner) -> sk_image_filter_t
int SkImageFilters_Crop(const reskia_rect_t *rect, int tileMode, int input); // (const SkRect *rect, SkTileMode tileMode, sk_image_filter_t input) -> sk_image_filter_t
int SkImageFilters_Crop_2(const reskia_rect_t *rect, int input); // (const SkRect *rect, sk_image_filter_t input) -> sk_image_filter_t
int SkImageFilters_DisplacementMap(int xChannelSelector, int yChannelSelector, float scale, int displacement, int color, const reskia_crop_rect_t *cropRect); // (SkColorChannel xChannelSelector, SkColorChannel yChannelSelector, SkScalar scale, sk_image_filter_t displacement, sk_image_filter_t color, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
int SkImageFilters_DropShadow(float dx, float dy, float sigmaX, float sigmaY, reskia_color_t color, int input, const reskia_crop_rect_t *cropRect); // (SkScalar dx, SkScalar dy, SkScalar sigmaX, SkScalar sigmaY, SkColor color, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
int SkImageFilters_DropShadowOnly(float dx, float dy, float sigmaX, float sigmaY, reskia_color_t color, int input, const reskia_crop_rect_t *cropRect); // (SkScalar dx, SkScalar dy, SkScalar sigmaX, SkScalar sigmaY, SkColor color, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
int SkImageFilters_Empty(); // () -> sk_image_filter_t
int SkImageFilters_Image(int image, const reskia_rect_t *srcRect, const reskia_rect_t *dstRect, const reskia_sampling_options_t *sampling); // (sk_image_t image, const SkRect *srcRect, const SkRect *dstRect, const SkSamplingOptions *sampling) -> sk_image_filter_t
int SkImageFilters_Image_2(int image, const reskia_sampling_options_t *sampling); // (sk_image_t image, const SkSamplingOptions *sampling) -> sk_image_filter_t
int SkImageFilters_Magnifier(const reskia_rect_t *lensBounds, float zoomAmount, float inset, const reskia_sampling_options_t *sampling, int input, const reskia_crop_rect_t *cropRect); // (const SkRect *lensBounds, SkScalar zoomAmount, SkScalar inset, const SkSamplingOptions *sampling, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
int SkImageFilters_MatrixConvolution(const reskia_i_size_t *kernelSize, const float *kernel, float gain, float bias, const reskia_i_point_t *kernelOffset, int tileMode, bool convolveAlpha, int input, const reskia_crop_rect_t *cropRect); // (const SkISize *kernelSize, const SkScalar kernel[], SkScalar gain, SkScalar bias, const SkIPoint *kernelOffset, SkTileMode tileMode, bool convolveAlpha, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
int SkImageFilters_MatrixTransform(const reskia_matrix_t *matrix, const reskia_sampling_options_t *sampling, int input); // (const SkMatrix *matrix, const SkSamplingOptions *sampling, sk_image_filter_t input) -> sk_image_filter_t
int SkImageFilters_Merge(reskia_image_filter_sp_t *filters, int count, const reskia_crop_rect_t *cropRect); // (sk_sp<SkImageFilter> *filters, int count, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
int SkImageFilters_Merge_2(int first, int second, const reskia_crop_rect_t *cropRect); // (sk_image_filter_t first, sk_image_filter_t second, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
int SkImageFilters_Offset(float dx, float dy, int input, const reskia_crop_rect_t *cropRect); // (SkScalar dx, SkScalar dy, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
int SkImageFilters_Picture(int picture, const reskia_rect_t *targetRect); // (sk_picture_t picture, const SkRect *targetRect) -> sk_image_filter_t
int SkImageFilters_Picture_2(int picture); // (sk_picture_t picture) -> sk_image_filter_t
int SkImageFilters_RuntimeShader(const reskia_runtime_shader_builder_t *builder, reskia_string_view_t childShaderName, int input); // (const SkRuntimeShaderBuilder *builder, string_view_t childShaderName, sk_image_filter_t input) -> sk_image_filter_t
int SkImageFilters_RuntimeShader_2(const reskia_runtime_shader_builder_t *builder, float sampleRadius, reskia_string_view_t childShaderName, int input); // (const SkRuntimeShaderBuilder *builder, SkScalar sampleRadius, string_view_t childShaderName, sk_image_filter_t input) -> sk_image_filter_t
int SkImageFilters_RuntimeShader_3(const reskia_runtime_shader_builder_t *builder, reskia_string_view_t *childShaderNames, const reskia_image_filter_sp_t *inputs, int inputCount); // (const SkRuntimeShaderBuilder *builder, std::string_view childShaderNames[], const sk_sp<SkImageFilter> *inputs, int inputCount) -> sk_image_filter_t
int SkImageFilters_RuntimeShader_4(const reskia_runtime_shader_builder_t *builder, float maxSampleRadius, reskia_string_view_t *childShaderNames, const reskia_image_filter_sp_t *inputs, int inputCount); // (const SkRuntimeShaderBuilder *builder, SkScalar maxSampleRadius, std::string_view childShaderNames[], const sk_sp<SkImageFilter> *inputs, int inputCount) -> sk_image_filter_t
int SkImageFilters_Shader(int shader, const reskia_crop_rect_t *cropRect); // (sk_shader_t shader, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
int SkImageFilters_Shader_2(int shader, int dither, const reskia_crop_rect_t *cropRect); // (sk_shader_t shader, SkImageFilters::Dither dither, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
int SkImageFilters_Tile(const reskia_rect_t *src, const reskia_rect_t *dst, int input); // (const SkRect *src, const SkRect *dst, sk_image_filter_t input) -> sk_image_filter_t
int SkImageFilters_Dilate(float radiusX, float radiusY, int input, const reskia_crop_rect_t *cropRect); // (SkScalar radiusX, SkScalar radiusY, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
int SkImageFilters_Erode(float radiusX, float radiusY, int input, const reskia_crop_rect_t *cropRect); // (SkScalar radiusX, SkScalar radiusY, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
int SkImageFilters_DistantLitDiffuse(const reskia_point3_t *direction, reskia_color_t lightColor, float surfaceScale, float kd, int input, const reskia_crop_rect_t *cropRect); // (const SkPoint3 *direction, SkColor lightColor, SkScalar surfaceScale, SkScalar kd, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
int SkImageFilters_PointLitDiffuse(const reskia_point3_t *location, reskia_color_t lightColor, float surfaceScale, float kd, int input, const reskia_crop_rect_t *cropRect); // (const SkPoint3 *location, SkColor lightColor, SkScalar surfaceScale, SkScalar kd, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
int SkImageFilters_SpotLitDiffuse(const reskia_point3_t *location, const reskia_point3_t *target, float falloffExponent, float cutoffAngle, reskia_color_t lightColor, float surfaceScale, float kd, int input, const reskia_crop_rect_t *cropRect); // (const SkPoint3 *location, const SkPoint3 *target, SkScalar falloffExponent, SkScalar cutoffAngle, SkColor lightColor, SkScalar surfaceScale, SkScalar kd, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
int SkImageFilters_DistantLitSpecular(const reskia_point3_t *direction, reskia_color_t lightColor, float surfaceScale, float ks, float shininess, int input, const reskia_crop_rect_t *cropRect); // (const SkPoint3 *direction, SkColor lightColor, SkScalar surfaceScale, SkScalar ks, SkScalar shininess, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
int SkImageFilters_PointLitSpecular(const reskia_point3_t *location, reskia_color_t lightColor, float surfaceScale, float ks, float shininess, int input, const reskia_crop_rect_t *cropRect); // (const SkPoint3 *location, SkColor lightColor, SkScalar surfaceScale, SkScalar ks, SkScalar shininess, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t
int SkImageFilters_SpotLitSpecular(const reskia_point3_t *location, const reskia_point3_t *target, float falloffExponent, float cutoffAngle, reskia_color_t lightColor, float surfaceScale, float ks, float shininess, int input, const reskia_crop_rect_t *cropRect); // (const SkPoint3 *location, const SkPoint3 *target, SkScalar falloffExponent, SkScalar cutoffAngle, SkColor lightColor, SkScalar surfaceScale, SkScalar ks, SkScalar shininess, sk_image_filter_t input, const SkImageFilters::CropRect *cropRect) -> sk_image_filter_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_IMAGE_FILTERS_H
