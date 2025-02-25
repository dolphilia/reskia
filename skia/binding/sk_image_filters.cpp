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

void SkImageFilters_delete(void * imageFilters) {
    delete static_cast<SkImageFilters *>(imageFilters);
}

// static

sk_image_filter_t SkImageFilters_Arithmetic(float k1, float k2, float k3, float k4, bool enforcePMColor, sk_image_filter_t background, sk_image_filter_t foreground, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Arithmetic(k1, k2, k3, k4, enforcePMColor, static_sk_image_filter_get_entity(background), static_sk_image_filter_get_entity(foreground), * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Blend(int mode, sk_image_filter_t background, sk_image_filter_t foreground, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Blend(static_cast<SkBlendMode>(mode), static_sk_image_filter_get_entity(background), static_sk_image_filter_get_entity(foreground), * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Blend_2(sk_blender_t blender, sk_image_filter_t background, sk_image_filter_t foreground, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Blend(static_sk_blender_get_entity(blender), static_sk_image_filter_get_entity(background), static_sk_image_filter_get_entity(foreground), * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Blur(float sigmaX, float sigmaY, int tileMode, sk_image_filter_t input, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Blur(sigmaX, sigmaY, static_cast<SkTileMode>(tileMode), static_sk_image_filter_get_entity(input), * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Blur_2(float sigmaX, float sigmaY, sk_image_filter_t input, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Blur(sigmaX, sigmaY, static_sk_image_filter_get_entity(input), * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_ColorFilter(sk_color_filter_t cf, sk_image_filter_t input, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::ColorFilter(static_sk_color_filter_get_entity(cf), static_sk_image_filter_get_entity(input), * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Compose(sk_image_filter_t outer, sk_image_filter_t inner) {
    return static_sk_image_filter_make(SkImageFilters::Compose(static_sk_image_filter_get_entity(outer), static_sk_image_filter_get_entity(inner)));
}

sk_image_filter_t SkImageFilters_Crop(const void *rect, int tileMode, sk_image_filter_t input) {
    return static_sk_image_filter_make(SkImageFilters::Crop(* static_cast<const SkRect *>(rect), static_cast<SkTileMode>(tileMode), static_sk_image_filter_get_entity(input)));
}

sk_image_filter_t SkImageFilters_Crop_2(const void *rect, sk_image_filter_t input) {
    return static_sk_image_filter_make(SkImageFilters::Crop(* static_cast<const SkRect *>(rect), static_sk_image_filter_get_entity(input)));
}

sk_image_filter_t SkImageFilters_DisplacementMap(int xChannelSelector, int yChannelSelector, float scale, sk_image_filter_t displacement, sk_image_filter_t color, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::DisplacementMap(static_cast<SkColorChannel>(xChannelSelector), static_cast<SkColorChannel>(yChannelSelector), scale, static_sk_image_filter_get_entity(displacement), static_sk_image_filter_get_entity(color), * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_DropShadow(float dx, float dy, float sigmaX, float sigmaY, unsigned int color, sk_image_filter_t input, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::DropShadow(dx, dy, sigmaX, sigmaY, color, static_sk_image_filter_get_entity(input), * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_DropShadowOnly(float dx, float dy, float sigmaX, float sigmaY, unsigned int color, sk_image_filter_t input, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::DropShadowOnly(dx, dy, sigmaX, sigmaY, color, static_sk_image_filter_get_entity(input), * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Empty() {
    return static_sk_image_filter_make(SkImageFilters::Empty());
}

sk_image_filter_t SkImageFilters_Image(sk_image_t image, const void *srcRect, const void *dstRect, const void *sampling) {
    return static_sk_image_filter_make(SkImageFilters::Image(static_sk_image_get_entity(image), * static_cast<const SkRect *>(srcRect), * static_cast<const SkRect *>(dstRect), * static_cast<const SkSamplingOptions *>(sampling)));
}

sk_image_filter_t SkImageFilters_Image_2(sk_image_t image, const void *sampling) {
    return static_sk_image_filter_make(SkImageFilters::Image(static_sk_image_get_entity(image), * static_cast<const SkSamplingOptions *>(sampling)));
}

sk_image_filter_t SkImageFilters_Magnifier(const void *lensBounds, float zoomAmount, float inset, const void *sampling, sk_image_filter_t input, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Magnifier(* static_cast<const SkRect *>(lensBounds), zoomAmount, inset, * static_cast<const SkSamplingOptions *>(sampling), static_sk_image_filter_get_entity(input), * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_MatrixConvolution(const void *kernelSize, const void * kernel, float gain, float bias, const void *kernelOffset, int tileMode, bool convolveAlpha, sk_image_filter_t input, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::MatrixConvolution(* static_cast<const SkISize *>(kernelSize), static_cast<const float *>(kernel), gain, bias, * static_cast<const SkIPoint *>(kernelOffset), static_cast<SkTileMode>(tileMode), convolveAlpha, static_sk_image_filter_get_entity(input), * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_MatrixTransform(const void *matrix, const void *sampling, sk_image_filter_t input) {
    return static_sk_image_filter_make(SkImageFilters::MatrixTransform(* static_cast<const SkMatrix *>(matrix), * static_cast<const SkSamplingOptions *>(sampling), static_sk_image_filter_get_entity(input)));
}

sk_image_filter_t SkImageFilters_Merge(void *filters, int count, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Merge(static_cast<sk_sp<SkImageFilter> *>(filters), count, * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Merge_2(sk_image_filter_t first, sk_image_filter_t second, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Merge(static_sk_image_filter_get_entity(first), static_sk_image_filter_get_entity(second), * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Offset(float dx, float dy, sk_image_filter_t input, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Offset(dx, dy, static_sk_image_filter_get_entity(input), * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Picture(sk_picture_t picture, const void *targetRect) {
    return static_sk_image_filter_make(SkImageFilters::Picture(static_sk_picture_get_entity(picture), * static_cast<const SkRect *>(targetRect)));
}

sk_image_filter_t SkImageFilters_Picture_2(sk_picture_t picture) {
    return static_sk_image_filter_make(SkImageFilters::Picture(static_sk_picture_get_entity(picture)));
}

sk_image_filter_t SkImageFilters_RuntimeShader(const void *builder, string_view_t childShaderName, sk_image_filter_t input) {
    return static_sk_image_filter_make(SkImageFilters::RuntimeShader(* static_cast<const SkRuntimeShaderBuilder *>(builder), static_string_view_get_entity(childShaderName), static_sk_image_filter_get_entity(input)));
}

sk_image_filter_t SkImageFilters_RuntimeShader_2(const void *builder, float sampleRadius, string_view_t childShaderName, sk_image_filter_t input) {
    return static_sk_image_filter_make(SkImageFilters::RuntimeShader(* static_cast<const SkRuntimeShaderBuilder *>(builder), sampleRadius, static_string_view_get_entity(childShaderName), static_sk_image_filter_get_entity(input)));
}

sk_image_filter_t SkImageFilters_RuntimeShader_3(const void *builder, void * childShaderNames, const void *inputs, int inputCount) {
    return static_sk_image_filter_make(SkImageFilters::RuntimeShader(* static_cast<const SkRuntimeShaderBuilder *>(builder), static_cast<std::string_view *>(childShaderNames), static_cast<const sk_sp<SkImageFilter> *>(inputs), inputCount));
}

sk_image_filter_t SkImageFilters_RuntimeShader_4(const void *builder, float maxSampleRadius, void * childShaderNames, const void *inputs, int inputCount) {
    return static_sk_image_filter_make(SkImageFilters::RuntimeShader(* static_cast<const SkRuntimeShaderBuilder *>(builder), maxSampleRadius, static_cast<std::string_view *>(childShaderNames), static_cast<const sk_sp<SkImageFilter> *>(inputs), inputCount));
}

sk_image_filter_t SkImageFilters_Shader(sk_shader_t shader, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Shader(static_sk_shader_get_entity(shader), * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Shader_2(sk_shader_t shader, int dither, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Shader(static_sk_shader_get_entity(shader), static_cast<SkImageFilters::Dither>(dither), * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Tile(const void *src, const void *dst, sk_image_filter_t input) {
    return static_sk_image_filter_make(SkImageFilters::Tile(* static_cast<const SkRect *>(src), * static_cast<const SkRect *>(dst), static_sk_image_filter_get_entity(input)));
}

sk_image_filter_t SkImageFilters_Dilate(float radiusX, float radiusY, sk_image_filter_t input, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Dilate(radiusX, radiusY, static_sk_image_filter_get_entity(input), * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_Erode(float radiusX, float radiusY, sk_image_filter_t input, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::Erode(radiusX, radiusY, static_sk_image_filter_get_entity(input), * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_DistantLitDiffuse(const void *direction, unsigned int lightColor, float surfaceScale, float kd, sk_image_filter_t input, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::DistantLitDiffuse(* static_cast<const SkPoint3 *>(direction), lightColor, surfaceScale, kd, static_sk_image_filter_get_entity(input), * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_PointLitDiffuse(const void *location, unsigned int lightColor, float surfaceScale, float kd, sk_image_filter_t input, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::PointLitDiffuse(* static_cast<const SkPoint3 *>(location), lightColor, surfaceScale, kd, static_sk_image_filter_get_entity(input), * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_SpotLitDiffuse(const void *location, const void *target, float falloffExponent, float cutoffAngle, unsigned int lightColor, float surfaceScale, float kd, sk_image_filter_t input, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::SpotLitDiffuse(* static_cast<const SkPoint3 *>(location), * static_cast<const SkPoint3 *>(target), falloffExponent, cutoffAngle, lightColor, surfaceScale, kd, static_sk_image_filter_get_entity(input), * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_DistantLitSpecular(const void *direction, unsigned int lightColor, float surfaceScale, float ks, float shininess, sk_image_filter_t input, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::DistantLitSpecular(* static_cast<const SkPoint3 *>(direction), lightColor, surfaceScale, ks, shininess, static_sk_image_filter_get_entity(input), * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_PointLitSpecular(const void *location, unsigned int lightColor, float surfaceScale, float ks, float shininess, sk_image_filter_t input, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::PointLitSpecular(* static_cast<const SkPoint3 *>(location), lightColor, surfaceScale, ks, shininess, static_sk_image_filter_get_entity(input), * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

sk_image_filter_t SkImageFilters_SpotLitSpecular(const void *location, const void *target, float falloffExponent, float cutoffAngle, unsigned int lightColor, float surfaceScale, float ks, float shininess, sk_image_filter_t input, const void *cropRect) {
    return static_sk_image_filter_make(SkImageFilters::SpotLitSpecular(* static_cast<const SkPoint3 *>(location), * static_cast<const SkPoint3 *>(target), falloffExponent, cutoffAngle, lightColor, surfaceScale, ks, shininess, static_sk_image_filter_get_entity(input), * static_cast<const SkImageFilters::CropRect *>(cropRect)));
}

}
