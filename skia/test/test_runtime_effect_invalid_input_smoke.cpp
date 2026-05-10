#include "capi/sk_runtime_blend_builder.h"
#include "capi/sk_runtime_color_filter_builder.h"
#include "capi/sk_runtime_effect.h"
#include "capi/sk_runtime_effect_builder.h"
#include "capi/sk_runtime_shader_builder.h"

#include <cstdio>

namespace {
bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[runtime-effect-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}
} // namespace

int main() {
    bool ok = true;

    SkRuntimeEffect_release(nullptr);
    SkRuntimeEffect_ref(nullptr);
    SkRuntimeEffect_unref(nullptr);
    SkRuntimeEffect_RegisterFlattenables();

    ok &= check(SkRuntimeEffect_makeShader(nullptr, 0, nullptr, 0, nullptr) == 0, "makeShader null effect");
    ok &= check(SkRuntimeEffect_makeShader(nullptr, 0, nullptr, 1, nullptr) == 0, "makeShader null effect and invalid children");
    ok &= check(SkRuntimeEffect_makeShaderWithChildPtr(nullptr, 0, 0, nullptr) == 0, "makeShaderWithChildPtr null effect");
    ok &= check(SkRuntimeEffect_makeColorFilter(nullptr, 0) == 0, "makeColorFilter null effect");
    ok &= check(SkRuntimeEffect_makeColorFilterWithChildren(nullptr, 0, nullptr, 0) == 0, "makeColorFilterWithChildren null effect");
    ok &= check(SkRuntimeEffect_makeColorFilterWithChildren(nullptr, 0, nullptr, 1) == 0, "makeColorFilterWithChildren null effect and invalid children");
    ok &= check(SkRuntimeEffect_makeColorFilterWithChildPtr(nullptr, 0, 0) == 0, "makeColorFilterWithChildPtr null effect");
    ok &= check(SkRuntimeEffect_makeBlender(nullptr, 0, 0) == 0, "makeBlender null effect");
    ok &= check(SkRuntimeEffect_source(nullptr) == nullptr, "source null effect");
    ok &= check(SkRuntimeEffect_uniformSize(nullptr) == 0, "uniformSize null effect");
    ok &= check(SkRuntimeEffect_uniforms(nullptr) == 0, "uniforms null effect");
    ok &= check(SkRuntimeEffect_children(nullptr) == 0, "children null effect");
    ok &= check(SkRuntimeEffect_findUniform(nullptr, 0) == nullptr, "findUniform null effect");
    ok &= check(SkRuntimeEffect_findChild(nullptr, 0) == nullptr, "findChild null effect");
    ok &= check(!SkRuntimeEffect_allowShader(nullptr), "allowShader null effect");
    ok &= check(!SkRuntimeEffect_allowColorFilter(nullptr), "allowColorFilter null effect");
    ok &= check(!SkRuntimeEffect_allowBlender(nullptr), "allowBlender null effect");
    ok &= check(!SkRuntimeEffect_unique(nullptr), "unique null effect");
    ok &= check(SkRuntimeEffect_MakeForColorFilter(0, nullptr) == 0, "MakeForColorFilter null options");
    ok &= check(SkRuntimeEffect_MakeForShader(0, nullptr) == 0, "MakeForShader null options");
    ok &= check(SkRuntimeEffect_MakeForBlender(0, nullptr) == 0, "MakeForBlender null options");
    ok &= check(SkRuntimeEffect_MakeTraced(0, nullptr) == 0, "MakeTraced null traceCoord");

    ok &= check(SkRuntimeShaderBuilder_new(0) == nullptr, "shader builder new invalid effect");
    ok &= check(SkRuntimeShaderBuilder_newCopy(nullptr) == nullptr, "shader builder newCopy null");
    SkRuntimeShaderBuilder_delete(nullptr);
    ok &= check(SkRuntimeShaderBuilder_makeShader(nullptr, nullptr) == 0, "shader builder makeShader null");
    ok &= check(SkRuntimeShaderBuilder_effect(nullptr) == nullptr, "shader builder effect null");
    ok &= check(SkRuntimeShaderBuilder_uniform(nullptr, 0) == 0, "shader builder uniform null");
    ok &= check(SkRuntimeShaderBuilder_child(nullptr, 0) == 0, "shader builder child null");
    ok &= check(SkRuntimeShaderBuilder_uniforms(nullptr) == 0, "shader builder uniforms null");
    ok &= check(SkRuntimeShaderBuilder_children(nullptr) == 0, "shader builder children null");

    ok &= check(SkRuntimeColorFilterBuilder_new(0) == nullptr, "color filter builder new invalid effect");
    SkRuntimeColorFilterBuilder_delete(nullptr);
    ok &= check(SkRuntimeColorFilterBuilder_makeColorFilter(nullptr) == 0, "color filter builder make null");
    ok &= check(SkRuntimeColorFilterBuilder_effect(nullptr) == nullptr, "color filter builder effect null");
    ok &= check(SkRuntimeColorFilterBuilder_uniform(nullptr, 0) == 0, "color filter builder uniform null");
    ok &= check(SkRuntimeColorFilterBuilder_child(nullptr, 0) == 0, "color filter builder child null");
    ok &= check(SkRuntimeColorFilterBuilder_uniforms(nullptr) == 0, "color filter builder uniforms null");
    ok &= check(SkRuntimeColorFilterBuilder_children(nullptr) == 0, "color filter builder children null");

    ok &= check(SkRuntimeBlendBuilder_new(0) == nullptr, "blend builder new invalid effect");
    SkRuntimeBlendBuilder_delete(nullptr);
    ok &= check(SkRuntimeBlendBuilder_makeBlender(nullptr) == 0, "blend builder make null");
    ok &= check(SkRuntimeBlendBuilder_effect(nullptr) == nullptr, "blend builder effect null");
    ok &= check(SkRuntimeBlendBuilder_uniform(nullptr, 0) == 0, "blend builder uniform null");
    ok &= check(SkRuntimeBlendBuilder_child(nullptr, 0) == 0, "blend builder child null");
    ok &= check(SkRuntimeBlendBuilder_uniforms(nullptr) == 0, "blend builder uniforms null");
    ok &= check(SkRuntimeBlendBuilder_children(nullptr) == 0, "blend builder children null");

    SkRuntimeEffectBuilder_delete(nullptr);
    ok &= check(SkRuntimeEffectBuilder_effect(nullptr) == nullptr, "effect builder effect null");
    ok &= check(SkRuntimeEffectBuilder_uniform(nullptr, 0) == 0, "effect builder uniform null");
    ok &= check(SkRuntimeEffectBuilder_child(nullptr, 0) == 0, "effect builder child null");
    ok &= check(SkRuntimeEffectBuilder_uniforms(nullptr) == 0, "effect builder uniforms null");
    ok &= check(SkRuntimeEffectBuilder_children(nullptr) == 0, "effect builder children null");

    return ok ? 0 : 1;
}
