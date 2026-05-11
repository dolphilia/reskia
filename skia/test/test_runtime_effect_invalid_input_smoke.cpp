#include "capi/sk_runtime_blend_builder.h"
#include "capi/sk_runtime_color_filter_builder.h"
#include "capi/sk_runtime_effect.h"
#include "capi/sk_runtime_effect_builder.h"
#include "capi/sk_runtime_shader_builder.h"
#include "capi/sk_i_point.h"
#include "capi/sk_r_rect.h"
#include "handles/static_sk_i_point.h"
#include "handles/static_sk_r_rect.h"
#include "handles/static_sk_blender.h"
#include "handles/static_sk_color_filter.h"
#include "handles/static_sk_runtime_effect_result.h"
#include "handles/static_sk_runtime_effect.h"
#include "handles/static_sk_runtime_effect-internal.h"
#include "handles/static_sk_runtime_effect_child.h"
#include "handles/static_sk_runtime_effect_uniform.h"
#include "handles/static_sk_shader.h"
#include "handles/static_sk_string.h"
#include "handles/static_sk_string-internal.h"
#include "handles/static_std_string_view.h"
#include "handles/static_std_string_view-internal.h"
#include "include/core/SkString.h"
#include "include/effects/SkRuntimeEffect.h"

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
    ok &= check(SkRuntimeEffect_makeShader(nullptr, 999999, nullptr, 0, nullptr) == 0, "makeShader null effect and invalid data");
    ok &= check(SkRuntimeEffect_makeShader(nullptr, 0, nullptr, 1, nullptr) == 0, "makeShader null effect and invalid children");
    ok &= check(SkRuntimeEffect_makeShaderWithChildPtr(nullptr, 0, 0, nullptr) == 0, "makeShaderWithChildPtr null effect");
    ok &= check(SkRuntimeEffect_makeShaderWithChildPtr(nullptr, 999999, 999999, nullptr) == 0, "makeShaderWithChildPtr null effect invalid data child ptr");
    ok &= check(SkRuntimeEffect_makeColorFilter(nullptr, 0) == 0, "makeColorFilter null effect");
    ok &= check(SkRuntimeEffect_makeColorFilter(nullptr, 999999) == 0, "makeColorFilter null effect invalid data");
    ok &= check(SkRuntimeEffect_makeColorFilterWithChildren(nullptr, 0, nullptr, 0) == 0, "makeColorFilterWithChildren null effect");
    ok &= check(SkRuntimeEffect_makeColorFilterWithChildren(nullptr, 999999, nullptr, 0) == 0, "makeColorFilterWithChildren null effect invalid data");
    ok &= check(SkRuntimeEffect_makeColorFilterWithChildren(nullptr, 0, nullptr, 1) == 0, "makeColorFilterWithChildren null effect and invalid children");
    ok &= check(SkRuntimeEffect_makeColorFilterWithChildPtr(nullptr, 0, 0) == 0, "makeColorFilterWithChildPtr null effect");
    ok &= check(SkRuntimeEffect_makeColorFilterWithChildPtr(nullptr, 999999, 999999) == 0, "makeColorFilterWithChildPtr null effect invalid data child ptr");
    ok &= check(SkRuntimeEffect_makeBlender(nullptr, 0, 0) == 0, "makeBlender null effect");
    ok &= check(SkRuntimeEffect_makeBlender(nullptr, 999999, 999999) == 0, "makeBlender null effect invalid data child ptr");
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
    const auto *c_options = reinterpret_cast<const reskia_runtime_effect_options_t *>(1);
    ok &= check(SkRuntimeEffect_MakeForColorFilter(0, c_options) == 0, "MakeForColorFilter zero source handle");
    ok &= check(SkRuntimeEffect_MakeForColorFilter(999999, c_options) == 0, "MakeForColorFilter invalid source handle");
    ok &= check(SkRuntimeEffect_MakeForColorFilterDefault(0) == 0, "MakeForColorFilterDefault zero source handle");
    ok &= check(SkRuntimeEffect_MakeForColorFilterDefault(999999) == 0, "MakeForColorFilterDefault invalid source handle");
    ok &= check(SkRuntimeEffect_MakeForShader(0, c_options) == 0, "MakeForShader zero source handle");
    ok &= check(SkRuntimeEffect_MakeForShader(999999, c_options) == 0, "MakeForShader invalid source handle");
    ok &= check(SkRuntimeEffect_MakeForShaderDefault(0) == 0, "MakeForShaderDefault zero source handle");
    ok &= check(SkRuntimeEffect_MakeForShaderDefault(999999) == 0, "MakeForShaderDefault invalid source handle");
    ok &= check(SkRuntimeEffect_MakeForBlender(0, c_options) == 0, "MakeForBlender zero source handle");
    ok &= check(SkRuntimeEffect_MakeForBlender(999999, c_options) == 0, "MakeForBlender invalid source handle");
    ok &= check(SkRuntimeEffect_MakeForBlenderDefault(0) == 0, "MakeForBlenderDefault zero source handle");
    ok &= check(SkRuntimeEffect_MakeForBlenderDefault(999999) == 0, "MakeForBlenderDefault invalid source handle");
    const sk_r_rect_t empty_rrect_handle = SkRRect_MakeEmpty();
    auto *empty_rrect = static_cast<reskia_r_rect_t *>(static_sk_r_rect_get_ptr(empty_rrect_handle));
    ok &= check(empty_rrect != nullptr, "empty rrect allocation for result source");
    const sk_string_t source_handle = empty_rrect != nullptr ? SkRRect_dumpToString(empty_rrect, false) : 0;
    ok &= check(source_handle != 0 && static_sk_string_get_ptr(source_handle) != nullptr, "string handle for result source");
    const sk_runtime_effect_result_t shader_result = SkRuntimeEffect_MakeForShaderDefault(source_handle);
    ok &= check(shader_result != 0 && static_sk_runtime_effect_result_get_ptr(shader_result) != nullptr, "MakeForShaderDefault result handle ownership");
    if (shader_result != 0) {
        static_sk_runtime_effect_result_delete(shader_result);
    }
    if (source_handle != 0) {
        static_sk_string_delete(source_handle);
    }
    if (empty_rrect_handle != 0) {
        static_sk_r_rect_delete(empty_rrect_handle);
    }
    const sk_string_t shader_source = static_sk_string_make(SkString("half4 main(float2 p) { return half4(1); }"));
    ok &= check(shader_source != 0 && static_sk_string_get_ptr(shader_source) != nullptr, "string handle for shader source");
    const sk_runtime_effect_result_t generated_shader_result = SkRuntimeEffect_MakeForShaderDefault(shader_source);
    auto *shader_result_entity = static_cast<SkRuntimeEffect::Result *>(static_sk_runtime_effect_result_get_ptr(generated_shader_result));
    ok &= check(shader_result_entity != nullptr && shader_result_entity->effect != nullptr, "MakeForShaderDefault valid effect");
    if (shader_result_entity != nullptr && shader_result_entity->effect != nullptr) {
        const sk_shader_t generated_shader = SkRuntimeEffect_makeShader(
                reinterpret_cast<reskia_runtime_effect_t *>(shader_result_entity->effect.get()),
                0,
                nullptr,
                0,
                nullptr);
        ok &= check(generated_shader != 0 && static_sk_shader_get_ptr(generated_shader) != nullptr, "SkRuntimeEffect_makeShader generated handle ownership");
        if (generated_shader != 0) {
            static_sk_shader_delete(generated_shader);
        }
    }
    if (generated_shader_result != 0) {
        static_sk_runtime_effect_result_delete(generated_shader_result);
    }
    if (shader_source != 0) {
        static_sk_string_delete(shader_source);
    }
    const sk_string_t color_filter_source = static_sk_string_make(SkString("half4 main(half4 c) { return c; }"));
    ok &= check(color_filter_source != 0 && static_sk_string_get_ptr(color_filter_source) != nullptr, "string handle for color filter source");
    const sk_runtime_effect_result_t generated_color_filter_result = SkRuntimeEffect_MakeForColorFilterDefault(color_filter_source);
    auto *color_filter_result_entity = static_cast<SkRuntimeEffect::Result *>(static_sk_runtime_effect_result_get_ptr(generated_color_filter_result));
    ok &= check(color_filter_result_entity != nullptr && color_filter_result_entity->effect != nullptr, "MakeForColorFilterDefault valid effect");
    if (color_filter_result_entity != nullptr && color_filter_result_entity->effect != nullptr) {
        const sk_color_filter_t generated_color_filter = SkRuntimeEffect_makeColorFilter(
                reinterpret_cast<reskia_runtime_effect_t *>(color_filter_result_entity->effect.get()),
                0);
        ok &= check(generated_color_filter != 0 && static_sk_color_filter_get_ptr(generated_color_filter) != nullptr, "SkRuntimeEffect_makeColorFilter generated handle ownership");
        if (generated_color_filter != 0) {
            static_sk_color_filter_delete(generated_color_filter);
        }
    }
    if (generated_color_filter_result != 0) {
        static_sk_runtime_effect_result_delete(generated_color_filter_result);
    }
    if (color_filter_source != 0) {
        static_sk_string_delete(color_filter_source);
    }
    const sk_string_t blender_source = static_sk_string_make(SkString("half4 main(half4 src, half4 dst) { return src; }"));
    ok &= check(blender_source != 0 && static_sk_string_get_ptr(blender_source) != nullptr, "string handle for blender source");
    const sk_runtime_effect_result_t generated_blender_result = SkRuntimeEffect_MakeForBlenderDefault(blender_source);
    auto *blender_result_entity = static_cast<SkRuntimeEffect::Result *>(static_sk_runtime_effect_result_get_ptr(generated_blender_result));
    ok &= check(blender_result_entity != nullptr && blender_result_entity->effect != nullptr, "MakeForBlenderDefault valid effect");
    if (blender_result_entity != nullptr && blender_result_entity->effect != nullptr) {
        const sk_blender_t generated_blender = SkRuntimeEffect_makeBlender(
                reinterpret_cast<reskia_runtime_effect_t *>(blender_result_entity->effect.get()),
                0,
                0);
        ok &= check(generated_blender != 0 && static_sk_blender_get_ptr(generated_blender) != nullptr, "SkRuntimeEffect_makeBlender generated handle ownership");
        if (generated_blender != 0) {
            static_sk_blender_delete(generated_blender);
        }
    }
    if (generated_blender_result != 0) {
        static_sk_runtime_effect_result_delete(generated_blender_result);
    }
    if (blender_source != 0) {
        static_sk_string_delete(blender_source);
    }
    const sk_string_t builder_shader_source = static_sk_string_make(SkString("half4 main(float2 p) { return half4(1); }"));
    ok &= check(builder_shader_source != 0 && static_sk_string_get_ptr(builder_shader_source) != nullptr, "string handle for shader builder source");
    const sk_runtime_effect_result_t builder_shader_result = SkRuntimeEffect_MakeForShaderDefault(builder_shader_source);
    auto *builder_shader_result_entity = static_cast<SkRuntimeEffect::Result *>(static_sk_runtime_effect_result_get_ptr(builder_shader_result));
    ok &= check(builder_shader_result_entity != nullptr && builder_shader_result_entity->effect != nullptr, "MakeForShaderDefault builder valid effect");
    if (builder_shader_result_entity != nullptr && builder_shader_result_entity->effect != nullptr) {
        const sk_runtime_effect_t effect_handle = static_sk_runtime_effect_make(builder_shader_result_entity->effect);
        ok &= check(effect_handle != 0 && static_sk_runtime_effect_get_ptr(effect_handle) != nullptr, "runtime effect handle for shader builder");
        reskia_runtime_shader_builder_t *builder = SkRuntimeShaderBuilder_new(effect_handle);
        ok &= check(builder != nullptr, "SkRuntimeShaderBuilder_new valid effect");
        if (builder != nullptr) {
            const sk_shader_t shader = SkRuntimeShaderBuilder_makeShader(builder, nullptr);
            ok &= check(shader != 0 && static_sk_shader_get_ptr(shader) != nullptr, "SkRuntimeShaderBuilder_makeShader generated handle ownership");
            if (shader != 0) {
                static_sk_shader_delete(shader);
            }
            SkRuntimeShaderBuilder_delete(builder);
        }
        static_sk_runtime_effect_delete(effect_handle);
    }
    if (builder_shader_result != 0) {
        static_sk_runtime_effect_result_delete(builder_shader_result);
    }
    if (builder_shader_source != 0) {
        static_sk_string_delete(builder_shader_source);
    }
    const sk_string_t builder_color_filter_source = static_sk_string_make(SkString("half4 main(half4 c) { return c; }"));
    ok &= check(builder_color_filter_source != 0 && static_sk_string_get_ptr(builder_color_filter_source) != nullptr, "string handle for color filter builder source");
    const sk_runtime_effect_result_t builder_color_filter_result = SkRuntimeEffect_MakeForColorFilterDefault(builder_color_filter_source);
    auto *builder_color_filter_result_entity = static_cast<SkRuntimeEffect::Result *>(static_sk_runtime_effect_result_get_ptr(builder_color_filter_result));
    ok &= check(builder_color_filter_result_entity != nullptr && builder_color_filter_result_entity->effect != nullptr, "MakeForColorFilterDefault builder valid effect");
    if (builder_color_filter_result_entity != nullptr && builder_color_filter_result_entity->effect != nullptr) {
        const sk_runtime_effect_t effect_handle = static_sk_runtime_effect_make(builder_color_filter_result_entity->effect);
        ok &= check(effect_handle != 0 && static_sk_runtime_effect_get_ptr(effect_handle) != nullptr, "runtime effect handle for color filter builder");
        reskia_runtime_color_filter_builder_t *builder = SkRuntimeColorFilterBuilder_new(effect_handle);
        ok &= check(builder != nullptr, "SkRuntimeColorFilterBuilder_new valid effect");
        if (builder != nullptr) {
            const sk_color_filter_t color_filter = SkRuntimeColorFilterBuilder_makeColorFilter(builder);
            ok &= check(color_filter != 0 && static_sk_color_filter_get_ptr(color_filter) != nullptr, "SkRuntimeColorFilterBuilder_makeColorFilter generated handle ownership");
            if (color_filter != 0) {
                static_sk_color_filter_delete(color_filter);
            }
            SkRuntimeColorFilterBuilder_delete(builder);
        }
        static_sk_runtime_effect_delete(effect_handle);
    }
    if (builder_color_filter_result != 0) {
        static_sk_runtime_effect_result_delete(builder_color_filter_result);
    }
    if (builder_color_filter_source != 0) {
        static_sk_string_delete(builder_color_filter_source);
    }
    const sk_string_t builder_blender_source = static_sk_string_make(SkString("half4 main(half4 src, half4 dst) { return src; }"));
    ok &= check(builder_blender_source != 0 && static_sk_string_get_ptr(builder_blender_source) != nullptr, "string handle for blend builder source");
    const sk_runtime_effect_result_t builder_blender_result = SkRuntimeEffect_MakeForBlenderDefault(builder_blender_source);
    auto *builder_blender_result_entity = static_cast<SkRuntimeEffect::Result *>(static_sk_runtime_effect_result_get_ptr(builder_blender_result));
    ok &= check(builder_blender_result_entity != nullptr && builder_blender_result_entity->effect != nullptr, "MakeForBlenderDefault builder valid effect");
    if (builder_blender_result_entity != nullptr && builder_blender_result_entity->effect != nullptr) {
        const sk_runtime_effect_t effect_handle = static_sk_runtime_effect_make(builder_blender_result_entity->effect);
        ok &= check(effect_handle != 0 && static_sk_runtime_effect_get_ptr(effect_handle) != nullptr, "runtime effect handle for blend builder");
        reskia_runtime_blend_builder_t *builder = SkRuntimeBlendBuilder_new(effect_handle);
        ok &= check(builder != nullptr, "SkRuntimeBlendBuilder_new valid effect");
        if (builder != nullptr) {
            const sk_blender_t blender = SkRuntimeBlendBuilder_makeBlender(builder);
            ok &= check(blender != 0 && static_sk_blender_get_ptr(blender) != nullptr, "SkRuntimeBlendBuilder_makeBlender generated handle ownership");
            if (blender != 0) {
                static_sk_blender_delete(blender);
            }
            SkRuntimeBlendBuilder_delete(builder);
        }
        static_sk_runtime_effect_delete(effect_handle);
    }
    if (builder_blender_result != 0) {
        static_sk_runtime_effect_result_delete(builder_blender_result);
    }
    if (builder_blender_source != 0) {
        static_sk_string_delete(builder_blender_source);
    }
    const sk_string_t uniform_source = static_sk_string_make(SkString("uniform float u; half4 main(float2 p) { return half4(u); }"));
    ok &= check(uniform_source != 0 && static_sk_string_get_ptr(uniform_source) != nullptr, "string handle for uniform source");
    const sk_runtime_effect_result_t uniform_result = SkRuntimeEffect_MakeForShaderDefault(uniform_source);
    auto *uniform_result_entity = static_cast<SkRuntimeEffect::Result *>(static_sk_runtime_effect_result_get_ptr(uniform_result));
    ok &= check(uniform_result_entity != nullptr && uniform_result_entity->effect != nullptr, "MakeForShaderDefault uniform valid effect");
    if (uniform_result_entity != nullptr && uniform_result_entity->effect != nullptr) {
        const_sk_runtime_effect_uniform_t uniforms = SkRuntimeEffect_uniforms(reinterpret_cast<reskia_runtime_effect_t *>(uniform_result_entity->effect.get()));
        ok &= check(uniforms != 0 && static_const_sk_runtime_effect_uniform_get_ptr(uniforms, 0) != nullptr, "SkRuntimeEffect_uniforms returned handle ownership");
        if (uniforms != 0) {
            static_const_sk_runtime_effect_uniform_delete(uniforms);
        }
        ok &= check(SkRuntimeEffect_findUniform(reinterpret_cast<reskia_runtime_effect_t *>(uniform_result_entity->effect.get()), 0) == nullptr, "findUniform zero string_view handle");
        ok &= check(SkRuntimeEffect_findUniform(reinterpret_cast<reskia_runtime_effect_t *>(uniform_result_entity->effect.get()), 999999) == nullptr, "findUniform invalid string_view handle");
        const string_view_t uniform_name = static_string_view_make(std::string_view("u"));
        ok &= check(SkRuntimeEffect_findUniform(reinterpret_cast<reskia_runtime_effect_t *>(uniform_result_entity->effect.get()), uniform_name) != nullptr, "findUniform valid string_view handle");
        static_string_view_delete(uniform_name);
    }
    if (uniform_result != 0) {
        static_sk_runtime_effect_result_delete(uniform_result);
    }
    if (uniform_source != 0) {
        static_sk_string_delete(uniform_source);
    }
    const sk_string_t child_source = static_sk_string_make(SkString("uniform shader child; half4 main(float2 p) { return child.eval(p); }"));
    ok &= check(child_source != 0 && static_sk_string_get_ptr(child_source) != nullptr, "string handle for child source");
    const sk_runtime_effect_result_t child_result = SkRuntimeEffect_MakeForShaderDefault(child_source);
    auto *child_result_entity = static_cast<SkRuntimeEffect::Result *>(static_sk_runtime_effect_result_get_ptr(child_result));
    ok &= check(child_result_entity != nullptr && child_result_entity->effect != nullptr, "MakeForShaderDefault child valid effect");
    if (child_result_entity != nullptr && child_result_entity->effect != nullptr) {
        const_sk_runtime_effect_child_t children = SkRuntimeEffect_children(reinterpret_cast<reskia_runtime_effect_t *>(child_result_entity->effect.get()));
        ok &= check(children != 0 && static_const_sk_runtime_effect_child_get_ptr(children, 0) != nullptr, "SkRuntimeEffect_children returned handle ownership");
        if (children != 0) {
            static_const_sk_runtime_effect_child_delete(children);
        }
        ok &= check(SkRuntimeEffect_findChild(reinterpret_cast<reskia_runtime_effect_t *>(child_result_entity->effect.get()), 0) == nullptr, "findChild zero string_view handle");
        ok &= check(SkRuntimeEffect_findChild(reinterpret_cast<reskia_runtime_effect_t *>(child_result_entity->effect.get()), 999999) == nullptr, "findChild invalid string_view handle");
        const string_view_t child_name = static_string_view_make(std::string_view("child"));
        ok &= check(SkRuntimeEffect_findChild(reinterpret_cast<reskia_runtime_effect_t *>(child_result_entity->effect.get()), child_name) != nullptr, "findChild valid string_view handle");
        static_string_view_delete(child_name);
    }
    if (child_result != 0) {
        static_sk_runtime_effect_result_delete(child_result);
    }
    if (child_source != 0) {
        static_sk_string_delete(child_source);
    }
    ok &= check(SkRuntimeEffect_MakeTraced(0, nullptr) == 0, "MakeTraced null traceCoord");
    const sk_i_point_t trace_coord_handle = SkIPoint_Make(0, 0);
    auto *trace_coord = static_cast<reskia_i_point_t *>(static_sk_i_point_get_ptr(trace_coord_handle));
    ok &= check(trace_coord != nullptr, "traceCoord allocation");
    ok &= check(SkRuntimeEffect_MakeTraced(0, trace_coord) == 0, "MakeTraced zero shader handle");
    ok &= check(SkRuntimeEffect_MakeTraced(999999, trace_coord) == 0, "MakeTraced invalid shader handle");
    static_sk_i_point_delete(trace_coord_handle);

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
