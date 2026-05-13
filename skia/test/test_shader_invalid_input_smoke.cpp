#include "capi/sk_shader.h"
#include "capi/sk_gradient_shader.h"
#include "capi/sk_perlin_noise_shader.h"
#include "capi/sk_shaders.h"
#include "handles/static_sk_point_two.h"
#include "handles/static_sk_shader.h"

#include <cstdio>

namespace {
bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[shader-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}
}

int main() {
    bool ok = true;

    SkShader_release(nullptr);
    SkShader_ref(nullptr);
    SkShader_unref(nullptr);
    SkShader_flatten(nullptr, nullptr);
    SkShader_Register(nullptr, 0);

    ok &= check(!SkShader_isOpaque(nullptr), "isOpaque null");
    ok &= check(SkShader_isAImage(nullptr, nullptr, nullptr) == nullptr, "isAImage null");
    ok &= check(!SkShader_isAImageWithoutLocalMatrixAndTileModes(nullptr), "isAImage no args null");
    ok &= check(SkShader_makeWithLocalMatrix(nullptr, nullptr) == 0, "makeWithLocalMatrix null");
    ok &= check(SkShader_makeWithColorFilter(nullptr, 0) == 0, "makeWithColorFilter null");
    ok &= check(SkShader_makeWithWorkingColorSpace(nullptr, 0) == 0, "makeWithWorkingColorSpace null");
    ok &= check(SkShader_getFactory(nullptr) == 0, "getFactory null");
    ok &= check(SkShader_getTypeName(nullptr) == nullptr, "getTypeName null");
    ok &= check(SkShader_getFlattenableType(nullptr) == 0, "getFlattenableType null");
    ok &= check(SkShader_serialize(nullptr, nullptr) == 0, "serialize null");
    ok &= check(SkShader_serializeToMemory(nullptr, nullptr, 0, nullptr) == 0, "serializeToMemory null");
    ok &= check(!SkShader_unique(nullptr), "unique null");
    ok &= check(SkShader_NameToFactory(nullptr) == 0, "NameToFactory null");
    ok &= check(SkShader_FactoryToName(0) == nullptr, "FactoryToName null factory");
    ok &= check(SkShader_Deserialize(0, nullptr, 0, nullptr) == 0, "Deserialize null");

    const sk_shader_t empty = SkShaders_Empty();
    ok &= check(empty != 0, "Empty returns handle");
    static_sk_shader_delete(empty);

    const sk_shader_t color = SkShaders_Color(0xff336699u);
    ok &= check(color != 0, "Color returns handle");
    static_sk_shader_delete(color);

    ok &= check(SkShaders_ColorWithColor4fAndColorSpace(nullptr, 0) == 0, "ColorWithColor4fAndColorSpace null color");
    ok &= check(SkShaders_Blend(0, 0, 0) == 0, "Blend null shaders");
    ok &= check(SkShaders_BlendWithBlender(0, 0, 0) == 0, "BlendWithBlender null shaders");
    ok &= check(SkShaders_CoordClamp(0, nullptr) == 0, "CoordClamp null subset");

    reskia_color_t gradient_colors[2] = {0xff336699u, 0xffddaa44u};
    ok &= check(SkGradientShader_MakeLinear(nullptr, gradient_colors, nullptr, 2, 0, 0, nullptr) == 0, "Gradient linear null points");
    ok &= check(SkGradientShader_MakeLinear(reinterpret_cast<const reskia_point_t *>(1), nullptr, nullptr, 2, 0, 0, nullptr) == 0, "Gradient linear null colors");
    ok &= check(SkGradientShader_MakeLinear(reinterpret_cast<const reskia_point_t *>(1), gradient_colors, nullptr, 0, 0, 0, nullptr) == 0, "Gradient linear invalid count");
    ok &= check(SkGradientShader_MakeLinear(reinterpret_cast<const reskia_point_t *>(1), gradient_colors, nullptr, 2, 999999, 0, nullptr) == 0, "Gradient linear invalid tile mode");
    ok &= check(SkGradientShader_MakeRadial(nullptr, 1.0f, gradient_colors, nullptr, 2, 0, 0, nullptr) == 0, "Gradient radial null center");
    ok &= check(SkGradientShader_MakeSweep(0.0f, 0.0f, nullptr, nullptr, 2, 0, 0.0f, 360.0f, 0, nullptr) == 0, "Gradient sweep null colors");
    ok &= check(SkGradientShader_MakeSweep(0.0f, 0.0f, gradient_colors, nullptr, 2, 999999, 0.0f, 360.0f, 0, nullptr) == 0, "Gradient sweep invalid tile mode");

    const int gradient_points = static_sk_point_two_make_float(0.0f, 0.0f, 16.0f, 16.0f);
    const auto *points = static_cast<const reskia_point_t *>(static_sk_point_two_get_ptr(gradient_points));
    const sk_shader_t gradient = SkGradientShader_MakeLinear(points, gradient_colors, nullptr, 2, 0, 0, nullptr);
    ok &= check(gradient != 0 && static_sk_shader_get_ptr(gradient) != nullptr, "Gradient linear valid returned handle");
    static_sk_shader_delete(gradient);
    static_sk_point_two_delete(gradient_points);

    ok &= check(SkPerlinNoiseShader_MakeFractalNoise(0.0f, 0.05f, 4, 0.0f, nullptr) == 0, "Perlin fractal invalid frequency");
    ok &= check(SkPerlinNoiseShader_MakeFractalNoise(0.05f, 0.05f, 0, 0.0f, nullptr) == 0, "Perlin fractal invalid octaves");
    ok &= check(SkPerlinNoiseShader_MakeTurbulence(0.0f, 0.05f, 4, 0.0f, nullptr) == 0, "Perlin turbulence invalid frequency");
    ok &= check(SkPerlinNoiseShader_MakeTurbulence(0.05f, 0.05f, 0, 0.0f, nullptr) == 0, "Perlin turbulence invalid octaves");
    const sk_shader_t perlin = SkPerlinNoiseShader_MakeFractalNoise(0.05f, 0.05f, 4, 0.0f, nullptr);
    ok &= check(perlin != 0 && static_sk_shader_get_ptr(perlin) != nullptr, "Perlin fractal valid returned handle");
    static_sk_shader_delete(perlin);

    return ok ? 0 : 1;
}
