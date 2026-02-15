//
// Created by dolphilia on 2024/01/08.
//

#include "sk_image_filters.h"

#include "include/core/SkBlender.h"
#include "include/effects/SkImageFilters.h"

#include "../static/static_sk_image_filter.h"
#include "../static/static_sk_color_filter.h"
#include "../static/static_sk_image.h"
#include "../static/static_sk_picture.h"
#include "../static/static_sk_shader.h"
#include "../static/static_sk_blender.h"
#include "../static/static_std_string_view.h"


#include "../static/static_sk_image-internal.h"
#include "../static/static_sk_image_filter-internal.h"
#include "../static/static_sk_picture-internal.h"
#include "../static/static_sk_shader-internal.h"
#include "../static/static_std_string_view-internal.h"
#include "../static/static_sk_color_filter-internal.h"
#include "../static/static_sk_blender-internal.h"

extern "C" {

void SkImageFilters_delete(reskia_image_filters_t *imageFilters) {
    delete reinterpret_cast<SkImageFilters *>(imageFilters);
}

// static

sk_image_filter_t SkImageFilters_Arithmetic(float k1, float k2, float k3, float k4, bool enforcePMColor, sk_image_filter_t background, sk_image_filter_t foreground, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Arithmetic(k1, k2, k3, k4, enforcePMColor, static_sk_image_filter_get_entity(background), static_sk_image_filter_get_entity(foreground), * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Blend(reskia_image_filters_blend_mode_t mode, sk_image_filter_t background, sk_image_filter_t foreground, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Blend(static_cast<SkBlendMode>(mode), static_sk_image_filter_get_entity(background), static_sk_image_filter_get_entity(foreground), * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Blend_2(reskia_blender_t blender, sk_image_filter_t background, sk_image_filter_t foreground, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Blend(static_sk_blender_get_entity(blender), static_sk_image_filter_get_entity(background), static_sk_image_filter_get_entity(foreground), * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Blur(float sigmaX, float sigmaY, reskia_image_filters_tile_mode_t tileMode, sk_image_filter_t input, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Blur(sigmaX, sigmaY, static_cast<SkTileMode>(tileMode), static_sk_image_filter_get_entity(input), * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Blur_2(float sigmaX, float sigmaY, sk_image_filter_t input, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Blur(sigmaX, sigmaY, static_sk_image_filter_get_entity(input), * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_ColorFilter(sk_color_filter_t cf, sk_image_filter_t input, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::ColorFilter(static_sk_color_filter_get_entity(cf), static_sk_image_filter_get_entity(input), * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Compose(sk_image_filter_t outer, sk_image_filter_t inner) {
    return static_sk_image_filter_make(SkImageFilters::Compose(static_sk_image_filter_get_entity(outer), static_sk_image_filter_get_entity(inner)));
}

sk_image_filter_t SkImageFilters_Crop(const reskia_rect_t *rect, reskia_image_filters_tile_mode_t tileMode, sk_image_filter_t input) {
    return static_sk_image_filter_make(SkImageFilters::Crop(* reinterpret_cast<const SkRect *>(rect), static_cast<SkTileMode>(tileMode), static_sk_image_filter_get_entity(input)));
}

sk_image_filter_t SkImageFilters_Crop_2(const reskia_rect_t *rect, sk_image_filter_t input) {
    return static_sk_image_filter_make(SkImageFilters::Crop(* reinterpret_cast<const SkRect *>(rect), static_sk_image_filter_get_entity(input)));
}

sk_image_filter_t SkImageFilters_DisplacementMap(reskia_image_filters_color_channel_t xChannelSelector, reskia_image_filters_color_channel_t yChannelSelector, float scale, sk_image_filter_t displacement, sk_image_filter_t color, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::DisplacementMap(static_cast<SkColorChannel>(xChannelSelector), static_cast<SkColorChannel>(yChannelSelector), scale, static_sk_image_filter_get_entity(displacement), static_sk_image_filter_get_entity(color), * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_DropShadow(float dx, float dy, float sigmaX, float sigmaY, reskia_color_t color, sk_image_filter_t input, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::DropShadow(dx, dy, sigmaX, sigmaY, color, static_sk_image_filter_get_entity(input), * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_DropShadowOnly(float dx, float dy, float sigmaX, float sigmaY, reskia_color_t color, sk_image_filter_t input, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::DropShadowOnly(dx, dy, sigmaX, sigmaY, color, static_sk_image_filter_get_entity(input), * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Empty() {
    return static_sk_image_filter_make(SkImageFilters::Empty());
}

sk_image_filter_t SkImageFilters_Image(sk_image_t image, const reskia_rect_t *srcRect, const reskia_rect_t *dstRect, const reskia_sampling_options_t *sampling) {
    return static_sk_image_filter_make(SkImageFilters::Image(static_sk_image_get_entity(image), * reinterpret_cast<const SkRect *>(srcRect), * reinterpret_cast<const SkRect *>(dstRect), * reinterpret_cast<const SkSamplingOptions *>(sampling)));
}

sk_image_filter_t SkImageFilters_Image_2(sk_image_t image, const reskia_sampling_options_t *sampling) {
    return static_sk_image_filter_make(SkImageFilters::Image(static_sk_image_get_entity(image), * reinterpret_cast<const SkSamplingOptions *>(sampling)));
}

sk_image_filter_t SkImageFilters_Magnifier(const reskia_rect_t *lensBounds, float zoomAmount, float inset, const reskia_sampling_options_t *sampling, sk_image_filter_t input, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Magnifier(* reinterpret_cast<const SkRect *>(lensBounds), zoomAmount, inset, * reinterpret_cast<const SkSamplingOptions *>(sampling), static_sk_image_filter_get_entity(input), * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_MatrixConvolution(const reskia_i_size_t *kernelSize, const float *kernel, float gain, float bias, const reskia_i_point_t *kernelOffset, reskia_image_filters_tile_mode_t tileMode, bool convolveAlpha, sk_image_filter_t input, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::MatrixConvolution(* reinterpret_cast<const SkISize *>(kernelSize), static_cast<const float *>(kernel), gain, bias, * reinterpret_cast<const SkIPoint *>(kernelOffset), static_cast<SkTileMode>(tileMode), convolveAlpha, static_sk_image_filter_get_entity(input), * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_MatrixTransform(const reskia_matrix_t *matrix, const reskia_sampling_options_t *sampling, sk_image_filter_t input) {
    return static_sk_image_filter_make(SkImageFilters::MatrixTransform(* reinterpret_cast<const SkMatrix *>(matrix), * reinterpret_cast<const SkSamplingOptions *>(sampling), static_sk_image_filter_get_entity(input)));
}

sk_image_filter_t SkImageFilters_Merge(reskia_image_filter_sp_t *filters, int count, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Merge(reinterpret_cast<sk_sp<SkImageFilter> *>(filters), count, * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Merge_2(sk_image_filter_t first, sk_image_filter_t second, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Merge(static_sk_image_filter_get_entity(first), static_sk_image_filter_get_entity(second), * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Offset(float dx, float dy, sk_image_filter_t input, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Offset(dx, dy, static_sk_image_filter_get_entity(input), * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Picture(sk_picture_t picture, const reskia_rect_t *targetRect) {
    return static_sk_image_filter_make(SkImageFilters::Picture(static_sk_picture_get_entity(picture), * reinterpret_cast<const SkRect *>(targetRect)));
}

sk_image_filter_t SkImageFilters_Picture_2(sk_picture_t picture) {
    return static_sk_image_filter_make(SkImageFilters::Picture(static_sk_picture_get_entity(picture)));
}

sk_image_filter_t SkImageFilters_RuntimeShader(const reskia_runtime_shader_builder_t *builder, reskia_string_view_t childShaderName, sk_image_filter_t input) {
    return static_sk_image_filter_make(SkImageFilters::RuntimeShader(* reinterpret_cast<const SkRuntimeShaderBuilder *>(builder), static_string_view_get_entity(childShaderName), static_sk_image_filter_get_entity(input)));
}

sk_image_filter_t SkImageFilters_RuntimeShader_2(const reskia_runtime_shader_builder_t *builder, float sampleRadius, reskia_string_view_t childShaderName, sk_image_filter_t input) {
    return static_sk_image_filter_make(SkImageFilters::RuntimeShader(* reinterpret_cast<const SkRuntimeShaderBuilder *>(builder), sampleRadius, static_string_view_get_entity(childShaderName), static_sk_image_filter_get_entity(input)));
}

sk_image_filter_t SkImageFilters_RuntimeShader_3(const reskia_runtime_shader_builder_t *builder, reskia_string_view_t *childShaderNames, const reskia_image_filter_sp_t *inputs, int inputCount) {
    return static_sk_image_filter_make(SkImageFilters::RuntimeShader(* reinterpret_cast<const SkRuntimeShaderBuilder *>(builder), reinterpret_cast<std::string_view *>(childShaderNames), reinterpret_cast<const sk_sp<SkImageFilter> *>(inputs), inputCount));
}

sk_image_filter_t SkImageFilters_RuntimeShader_4(const reskia_runtime_shader_builder_t *builder, float maxSampleRadius, reskia_string_view_t *childShaderNames, const reskia_image_filter_sp_t *inputs, int inputCount) {
    return static_sk_image_filter_make(SkImageFilters::RuntimeShader(* reinterpret_cast<const SkRuntimeShaderBuilder *>(builder), maxSampleRadius, reinterpret_cast<std::string_view *>(childShaderNames), reinterpret_cast<const sk_sp<SkImageFilter> *>(inputs), inputCount));
}

sk_image_filter_t SkImageFilters_Shader(sk_shader_t shader, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Shader(static_sk_shader_get_entity(shader), * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Shader_2(sk_shader_t shader, reskia_image_filters_dither_t dither, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Shader(static_sk_shader_get_entity(shader), static_cast<SkImageFilters::Dither>(dither), * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Tile(const reskia_rect_t *src, const reskia_rect_t *dst, sk_image_filter_t input) {
    return static_sk_image_filter_make(SkImageFilters::Tile(* reinterpret_cast<const SkRect *>(src), * reinterpret_cast<const SkRect *>(dst), static_sk_image_filter_get_entity(input)));
}

sk_image_filter_t SkImageFilters_Dilate(float radiusX, float radiusY, sk_image_filter_t input, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Dilate(radiusX, radiusY, static_sk_image_filter_get_entity(input), * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Erode(float radiusX, float radiusY, sk_image_filter_t input, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Erode(radiusX, radiusY, static_sk_image_filter_get_entity(input), * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_DistantLitDiffuse(const reskia_point3_t *direction, reskia_color_t lightColor, float surfaceScale, float kd, sk_image_filter_t input, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::DistantLitDiffuse(* reinterpret_cast<const SkPoint3 *>(direction), lightColor, surfaceScale, kd, static_sk_image_filter_get_entity(input), * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_PointLitDiffuse(const reskia_point3_t *location, reskia_color_t lightColor, float surfaceScale, float kd, sk_image_filter_t input, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::PointLitDiffuse(* reinterpret_cast<const SkPoint3 *>(location), lightColor, surfaceScale, kd, static_sk_image_filter_get_entity(input), * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_SpotLitDiffuse(const reskia_point3_t *location, const reskia_point3_t *target, float falloffExponent, float cutoffAngle, reskia_color_t lightColor, float surfaceScale, float kd, sk_image_filter_t input, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::SpotLitDiffuse(* reinterpret_cast<const SkPoint3 *>(location), * reinterpret_cast<const SkPoint3 *>(target), falloffExponent, cutoffAngle, lightColor, surfaceScale, kd, static_sk_image_filter_get_entity(input), * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_DistantLitSpecular(const reskia_point3_t *direction, reskia_color_t lightColor, float surfaceScale, float ks, float shininess, sk_image_filter_t input, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::DistantLitSpecular(* reinterpret_cast<const SkPoint3 *>(direction), lightColor, surfaceScale, ks, shininess, static_sk_image_filter_get_entity(input), * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_PointLitSpecular(const reskia_point3_t *location, reskia_color_t lightColor, float surfaceScale, float ks, float shininess, sk_image_filter_t input, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::PointLitSpecular(* reinterpret_cast<const SkPoint3 *>(location), lightColor, surfaceScale, ks, shininess, static_sk_image_filter_get_entity(input), * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_SpotLitSpecular(const reskia_point3_t *location, const reskia_point3_t *target, float falloffExponent, float cutoffAngle, reskia_color_t lightColor, float surfaceScale, float ks, float shininess, sk_image_filter_t input, const reskia_crop_rect_t *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::SpotLitSpecular(* reinterpret_cast<const SkPoint3 *>(location), * reinterpret_cast<const SkPoint3 *>(target), falloffExponent, cutoffAngle, lightColor, surfaceScale, ks, shininess, static_sk_image_filter_get_entity(input), * reinterpret_cast<const SkImageFilters::CropRect *>(cropRect)));
}

}
