#ifndef RAIA_SKIA_SK_SKOTTIE_H
#define RAIA_SKIA_SK_SKOTTIE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "reskia_callback.h"
#include "../handles/static_sk_font_mgr.h"
#include "../handles/static_sk_size_t.h"
#include "../handles/static_sk_typeface.h"
#include "../handles/static_sk_v2.h"

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_skresources_image_asset_t reskia_skresources_image_asset_t;
typedef struct reskia_skresources_resource_provider_t reskia_skresources_resource_provider_t;
typedef struct reskia_skottie_animation_t reskia_skottie_animation_t;
typedef struct reskia_skottie_animation_builder_t reskia_skottie_animation_builder_t;
typedef struct reskia_skottie_array_expression_evaluator_t reskia_skottie_array_expression_evaluator_t;
typedef struct reskia_skottie_expression_manager_t reskia_skottie_expression_manager_t;
typedef struct reskia_skottie_external_layer_t reskia_skottie_external_layer_t;
typedef struct reskia_skottie_glyph_decorator_t reskia_skottie_glyph_decorator_t;
typedef struct reskia_skottie_logger_t reskia_skottie_logger_t;
typedef struct reskia_skottie_marker_observer_t reskia_skottie_marker_observer_t;
typedef struct reskia_skottie_number_expression_evaluator_t reskia_skottie_number_expression_evaluator_t;
typedef struct reskia_skottie_precomp_interceptor_t reskia_skottie_precomp_interceptor_t;
typedef struct reskia_skottie_color_property_handle_t reskia_skottie_color_property_handle_t;
typedef struct reskia_skottie_color_property_lazy_handle_t reskia_skottie_color_property_lazy_handle_t;
typedef struct reskia_skottie_opacity_property_handle_t reskia_skottie_opacity_property_handle_t;
typedef struct reskia_skottie_opacity_property_lazy_handle_t reskia_skottie_opacity_property_lazy_handle_t;
typedef struct reskia_skottie_property_observer_t reskia_skottie_property_observer_t;
typedef struct reskia_size_t reskia_size_t;
typedef struct reskia_skottie_slot_info_t reskia_skottie_slot_info_t;
typedef struct reskia_skottie_slot_manager_t reskia_skottie_slot_manager_t;
typedef struct reskia_skottie_shaper_result_t reskia_skottie_shaper_result_t;
typedef struct reskia_skottie_string_expression_evaluator_t reskia_skottie_string_expression_evaluator_t;
typedef struct reskia_skottie_text_property_value_t reskia_skottie_text_property_value_t;
typedef struct reskia_skottie_text_property_handle_t reskia_skottie_text_property_handle_t;
typedef struct reskia_skottie_text_property_lazy_handle_t reskia_skottie_text_property_lazy_handle_t;
typedef struct reskia_skottie_transform_property_handle_t reskia_skottie_transform_property_handle_t;
typedef struct reskia_skottie_transform_property_lazy_handle_t reskia_skottie_transform_property_lazy_handle_t;
typedef struct reskia_string_t reskia_string_t;

#ifdef __cplusplus
extern "C" {
#endif

enum {
    RESKIA_SKOTTIE_ANIMATION_BUILDER_DEFER_IMAGE_LOADING = 0x01,
    RESKIA_SKOTTIE_ANIMATION_BUILDER_PREFER_EMBEDDED_FONTS = 0x02,
};

typedef int32_t reskia_skottie_logger_level_t;
typedef int32_t reskia_skottie_property_observer_node_type_t;

typedef struct reskia_skottie_glyph_info_t {
    float bounds_left;
    float bounds_top;
    float bounds_right;
    float bounds_bottom;
    float matrix[9];
    size_t cluster;
    float advance;
} reskia_skottie_glyph_info_t;

typedef struct reskia_skottie_transform_property_value_t {
    float anchor_x;
    float anchor_y;
    float position_x;
    float position_y;
    float scale_x;
    float scale_y;
    float rotation;
    float skew;
    float skew_axis;
} reskia_skottie_transform_property_value_t;

typedef void (*reskia_skottie_logger_log_proc_t)(
        reskia_skottie_logger_level_t level,
        const char message[],
        const char json[],
        void *user_data);
typedef void (*reskia_skottie_marker_observer_on_marker_proc_t)(
        const char name[],
        float t0,
        float t1,
        void *user_data);
typedef void (*reskia_skottie_external_layer_render_proc_t)(
        reskia_canvas_t *canvas,
        double t,
        void *user_data);
typedef reskia_skottie_external_layer_t *(*reskia_skottie_precomp_interceptor_on_load_precomp_proc_t)(
        const char id[],
        const char name[],
        const reskia_size_t *size,
        void *user_data);
typedef void (*reskia_skottie_property_observer_node_proc_t)(
        const char node_name[],
        reskia_skottie_property_observer_node_type_t node_type,
        void *user_data);
typedef void (*reskia_skottie_property_observer_color_proc_t)(
        const char node_name[],
        reskia_skottie_color_property_lazy_handle_t *lazy_handle,
        void *user_data);
typedef void (*reskia_skottie_property_observer_opacity_proc_t)(
        const char node_name[],
        reskia_skottie_opacity_property_lazy_handle_t *lazy_handle,
        void *user_data);
typedef void (*reskia_skottie_property_observer_text_proc_t)(
        const char node_name[],
        reskia_skottie_text_property_lazy_handle_t *lazy_handle,
        void *user_data);
typedef void (*reskia_skottie_property_observer_transform_proc_t)(
        const char node_name[],
        reskia_skottie_transform_property_lazy_handle_t *lazy_handle,
        void *user_data);
typedef float (*reskia_skottie_number_expression_evaluate_proc_t)(float t, void *user_data);
typedef const char *(*reskia_skottie_string_expression_evaluate_proc_t)(float t, void *user_data);
typedef size_t (*reskia_skottie_array_expression_evaluate_proc_t)(float t, float out_values[], size_t capacity, void *user_data);
typedef void (*reskia_skottie_glyph_decorator_on_decorate_proc_t)(
        reskia_canvas_t *canvas,
        const reskia_skottie_glyph_info_t glyphs[],
        size_t glyph_count,
        float scale,
        void *user_data);
typedef reskia_skottie_number_expression_evaluator_t *(*reskia_skottie_expression_manager_create_number_proc_t)(const char expression[], void *user_data);
typedef reskia_skottie_string_expression_evaluator_t *(*reskia_skottie_expression_manager_create_string_proc_t)(const char expression[], void *user_data);
typedef reskia_skottie_array_expression_evaluator_t *(*reskia_skottie_expression_manager_create_array_proc_t)(const char expression[], void *user_data);

enum {
    RESKIA_SKOTTIE_LOGGER_LEVEL_WARNING = 0,
    RESKIA_SKOTTIE_LOGGER_LEVEL_ERROR = 1,
};

enum {
    RESKIA_SKOTTIE_PROPERTY_OBSERVER_NODE_TYPE_COMPOSITION = 0,
    RESKIA_SKOTTIE_PROPERTY_OBSERVER_NODE_TYPE_LAYER = 1,
    RESKIA_SKOTTIE_PROPERTY_OBSERVER_NODE_TYPE_EFFECT = 2,
    RESKIA_SKOTTIE_PROPERTY_OBSERVER_NODE_TYPE_OTHER = 3,
};

reskia_skottie_logger_t *Skottie_Logger_new(reskia_skottie_logger_log_proc_t log, void *user_data, reskia_callback_release_proc_t release_proc);
void Skottie_Logger_ref(reskia_skottie_logger_t *logger);
void Skottie_Logger_unref(reskia_skottie_logger_t *logger);
void Skottie_Logger_release(reskia_skottie_logger_t *logger);
void Skottie_Logger_log(reskia_skottie_logger_t *logger, reskia_skottie_logger_level_t level, const char message[], const char json[]);

reskia_skottie_marker_observer_t *Skottie_MarkerObserver_new(reskia_skottie_marker_observer_on_marker_proc_t on_marker, void *user_data, reskia_callback_release_proc_t release_proc);
void Skottie_MarkerObserver_ref(reskia_skottie_marker_observer_t *observer);
void Skottie_MarkerObserver_unref(reskia_skottie_marker_observer_t *observer);
void Skottie_MarkerObserver_release(reskia_skottie_marker_observer_t *observer);
void Skottie_MarkerObserver_onMarker(reskia_skottie_marker_observer_t *observer, const char name[], float t0, float t1);

reskia_skottie_external_layer_t *Skottie_ExternalLayer_new(reskia_skottie_external_layer_render_proc_t render, void *user_data, reskia_callback_release_proc_t release_proc);
void Skottie_ExternalLayer_ref(reskia_skottie_external_layer_t *layer);
void Skottie_ExternalLayer_unref(reskia_skottie_external_layer_t *layer);
void Skottie_ExternalLayer_release(reskia_skottie_external_layer_t *layer);
void Skottie_ExternalLayer_render(reskia_skottie_external_layer_t *layer, reskia_canvas_t *canvas, double t);

reskia_skottie_precomp_interceptor_t *Skottie_PrecompInterceptor_new(reskia_skottie_precomp_interceptor_on_load_precomp_proc_t on_load_precomp, void *user_data, reskia_callback_release_proc_t release_proc);
void Skottie_PrecompInterceptor_ref(reskia_skottie_precomp_interceptor_t *interceptor);
void Skottie_PrecompInterceptor_unref(reskia_skottie_precomp_interceptor_t *interceptor);
void Skottie_PrecompInterceptor_release(reskia_skottie_precomp_interceptor_t *interceptor);
reskia_skottie_external_layer_t *Skottie_PrecompInterceptor_onLoadPrecomp(reskia_skottie_precomp_interceptor_t *interceptor, const char id[], const char name[], const reskia_size_t *size); // returned pointer owns a ref; release with Skottie_ExternalLayer_release.

reskia_skottie_property_observer_t *Skottie_PropertyObserver_new(reskia_skottie_property_observer_node_proc_t on_enter_node, reskia_skottie_property_observer_node_proc_t on_leaving_node, void *user_data, reskia_callback_release_proc_t release_proc);
reskia_skottie_property_observer_t *Skottie_PropertyObserver_newWithProperties(reskia_skottie_property_observer_node_proc_t on_enter_node, reskia_skottie_property_observer_node_proc_t on_leaving_node, reskia_skottie_property_observer_color_proc_t on_color_property, reskia_skottie_property_observer_opacity_proc_t on_opacity_property, reskia_skottie_property_observer_text_proc_t on_text_property, reskia_skottie_property_observer_transform_proc_t on_transform_property, void *user_data, reskia_callback_release_proc_t release_proc);
void Skottie_PropertyObserver_ref(reskia_skottie_property_observer_t *observer);
void Skottie_PropertyObserver_unref(reskia_skottie_property_observer_t *observer);
void Skottie_PropertyObserver_release(reskia_skottie_property_observer_t *observer);
void Skottie_PropertyObserver_onEnterNode(reskia_skottie_property_observer_t *observer, const char node_name[], reskia_skottie_property_observer_node_type_t node_type);
void Skottie_PropertyObserver_onLeavingNode(reskia_skottie_property_observer_t *observer, const char node_name[], reskia_skottie_property_observer_node_type_t node_type);
void Skottie_PropertyObserver_onColorProperty(reskia_skottie_property_observer_t *observer, const char node_name[], reskia_skottie_color_property_lazy_handle_t *lazy_handle);
void Skottie_PropertyObserver_onOpacityProperty(reskia_skottie_property_observer_t *observer, const char node_name[], reskia_skottie_opacity_property_lazy_handle_t *lazy_handle);
void Skottie_PropertyObserver_onTextProperty(reskia_skottie_property_observer_t *observer, const char node_name[], reskia_skottie_text_property_lazy_handle_t *lazy_handle);
void Skottie_PropertyObserver_onTransformProperty(reskia_skottie_property_observer_t *observer, const char node_name[], reskia_skottie_transform_property_lazy_handle_t *lazy_handle);

reskia_skottie_color_property_handle_t *Skottie_ColorPropertyLazyHandle_materialize(reskia_skottie_color_property_lazy_handle_t *lazy_handle);
reskia_skottie_opacity_property_handle_t *Skottie_OpacityPropertyLazyHandle_materialize(reskia_skottie_opacity_property_lazy_handle_t *lazy_handle);
reskia_skottie_text_property_handle_t *Skottie_TextPropertyLazyHandle_materialize(reskia_skottie_text_property_lazy_handle_t *lazy_handle);
reskia_skottie_transform_property_handle_t *Skottie_TransformPropertyLazyHandle_materialize(reskia_skottie_transform_property_lazy_handle_t *lazy_handle);

void Skottie_ColorPropertyHandle_delete(reskia_skottie_color_property_handle_t *handle);
uint32_t Skottie_ColorPropertyHandle_get(const reskia_skottie_color_property_handle_t *handle);
void Skottie_ColorPropertyHandle_set(reskia_skottie_color_property_handle_t *handle, uint32_t color);
void Skottie_OpacityPropertyHandle_delete(reskia_skottie_opacity_property_handle_t *handle);
float Skottie_OpacityPropertyHandle_get(const reskia_skottie_opacity_property_handle_t *handle);
void Skottie_OpacityPropertyHandle_set(reskia_skottie_opacity_property_handle_t *handle, float opacity);
void Skottie_TextPropertyHandle_delete(reskia_skottie_text_property_handle_t *handle);
reskia_skottie_text_property_value_t *Skottie_TextPropertyHandle_get(const reskia_skottie_text_property_handle_t *handle);
void Skottie_TextPropertyHandle_set(reskia_skottie_text_property_handle_t *handle, const reskia_skottie_text_property_value_t *value);
void Skottie_TransformPropertyHandle_delete(reskia_skottie_transform_property_handle_t *handle);
bool Skottie_TransformPropertyHandle_get(const reskia_skottie_transform_property_handle_t *handle, reskia_skottie_transform_property_value_t *out_value);
void Skottie_TransformPropertyHandle_set(reskia_skottie_transform_property_handle_t *handle, const reskia_skottie_transform_property_value_t *value);

reskia_skottie_number_expression_evaluator_t *Skottie_NumberExpressionEvaluator_new(reskia_skottie_number_expression_evaluate_proc_t evaluate, void *user_data, reskia_callback_release_proc_t release_proc);
void Skottie_NumberExpressionEvaluator_ref(reskia_skottie_number_expression_evaluator_t *evaluator);
void Skottie_NumberExpressionEvaluator_unref(reskia_skottie_number_expression_evaluator_t *evaluator);
void Skottie_NumberExpressionEvaluator_release(reskia_skottie_number_expression_evaluator_t *evaluator);
float Skottie_NumberExpressionEvaluator_evaluate(reskia_skottie_number_expression_evaluator_t *evaluator, float t);

reskia_skottie_string_expression_evaluator_t *Skottie_StringExpressionEvaluator_new(reskia_skottie_string_expression_evaluate_proc_t evaluate, void *user_data, reskia_callback_release_proc_t release_proc);
void Skottie_StringExpressionEvaluator_ref(reskia_skottie_string_expression_evaluator_t *evaluator);
void Skottie_StringExpressionEvaluator_unref(reskia_skottie_string_expression_evaluator_t *evaluator);
void Skottie_StringExpressionEvaluator_release(reskia_skottie_string_expression_evaluator_t *evaluator);
reskia_string_t *Skottie_StringExpressionEvaluator_evaluate(reskia_skottie_string_expression_evaluator_t *evaluator, float t);

reskia_skottie_array_expression_evaluator_t *Skottie_ArrayExpressionEvaluator_new(reskia_skottie_array_expression_evaluate_proc_t evaluate, void *user_data, reskia_callback_release_proc_t release_proc);
void Skottie_ArrayExpressionEvaluator_ref(reskia_skottie_array_expression_evaluator_t *evaluator);
void Skottie_ArrayExpressionEvaluator_unref(reskia_skottie_array_expression_evaluator_t *evaluator);
void Skottie_ArrayExpressionEvaluator_release(reskia_skottie_array_expression_evaluator_t *evaluator);
size_t Skottie_ArrayExpressionEvaluator_evaluate(reskia_skottie_array_expression_evaluator_t *evaluator, float t, float out_values[], size_t capacity);

reskia_skottie_expression_manager_t *Skottie_ExpressionManager_new(reskia_skottie_expression_manager_create_number_proc_t create_number, reskia_skottie_expression_manager_create_string_proc_t create_string, reskia_skottie_expression_manager_create_array_proc_t create_array, void *user_data, reskia_callback_release_proc_t release_proc);
void Skottie_ExpressionManager_ref(reskia_skottie_expression_manager_t *manager);
void Skottie_ExpressionManager_unref(reskia_skottie_expression_manager_t *manager);
void Skottie_ExpressionManager_release(reskia_skottie_expression_manager_t *manager);
reskia_skottie_number_expression_evaluator_t *Skottie_ExpressionManager_createNumberExpressionEvaluator(reskia_skottie_expression_manager_t *manager, const char expression[]); // returned pointer owns a ref; release with Skottie_NumberExpressionEvaluator_release.
reskia_skottie_string_expression_evaluator_t *Skottie_ExpressionManager_createStringExpressionEvaluator(reskia_skottie_expression_manager_t *manager, const char expression[]); // returned pointer owns a ref; release with Skottie_StringExpressionEvaluator_release.
reskia_skottie_array_expression_evaluator_t *Skottie_ExpressionManager_createArrayExpressionEvaluator(reskia_skottie_expression_manager_t *manager, const char expression[]); // returned pointer owns a ref; release with Skottie_ArrayExpressionEvaluator_release.

reskia_skottie_glyph_decorator_t *Skottie_GlyphDecorator_new(reskia_skottie_glyph_decorator_on_decorate_proc_t on_decorate, void *user_data, reskia_callback_release_proc_t release_proc);
void Skottie_GlyphDecorator_ref(reskia_skottie_glyph_decorator_t *decorator);
void Skottie_GlyphDecorator_unref(reskia_skottie_glyph_decorator_t *decorator);
void Skottie_GlyphDecorator_release(reskia_skottie_glyph_decorator_t *decorator);
void Skottie_GlyphDecorator_onDecorate(reskia_skottie_glyph_decorator_t *decorator, reskia_canvas_t *canvas, const reskia_skottie_glyph_info_t glyphs[], size_t glyph_count, float scale);

reskia_skottie_animation_t *Skottie_Animation_Make(const char *data, size_t length);
reskia_skottie_animation_t *Skottie_Animation_MakeFromFile(const char path[]);

void Skottie_Animation_release(reskia_skottie_animation_t *animation);
void Skottie_Animation_ref(reskia_skottie_animation_t *animation);
void Skottie_Animation_unref(reskia_skottie_animation_t *animation);

bool Skottie_Animation_seek(reskia_skottie_animation_t *animation, float t);
bool Skottie_Animation_seekFrameTime(reskia_skottie_animation_t *animation, double t);
void Skottie_Animation_render(reskia_skottie_animation_t *animation, reskia_canvas_t *canvas, const reskia_rect_t *dst);
void Skottie_Animation_renderWithFlags(reskia_skottie_animation_t *animation, reskia_canvas_t *canvas, const reskia_rect_t *dst, uint32_t flags);

double Skottie_Animation_duration(const reskia_skottie_animation_t *animation);
double Skottie_Animation_fps(const reskia_skottie_animation_t *animation);
double Skottie_Animation_inPoint(const reskia_skottie_animation_t *animation);
double Skottie_Animation_outPoint(const reskia_skottie_animation_t *animation);
reskia_string_t *Skottie_Animation_version(const reskia_skottie_animation_t *animation);
// Returns an owned SkSize handle. Release it with static_sk_size_delete().
sk_size_t Skottie_Animation_size(const reskia_skottie_animation_t *animation);
float Skottie_Animation_width(const reskia_skottie_animation_t *animation);
float Skottie_Animation_height(const reskia_skottie_animation_t *animation);

reskia_skottie_animation_builder_t *Skottie_AnimationBuilder_new(uint32_t flags);
void Skottie_AnimationBuilder_delete(reskia_skottie_animation_builder_t *builder);
bool Skottie_AnimationBuilder_setResourceProvider(reskia_skottie_animation_builder_t *builder, reskia_skresources_resource_provider_t *provider); // provider is borrowed and retained.
bool Skottie_AnimationBuilder_setLogger(reskia_skottie_animation_builder_t *builder, reskia_skottie_logger_t *logger); // logger is borrowed and retained.
bool Skottie_AnimationBuilder_setMarkerObserver(reskia_skottie_animation_builder_t *builder, reskia_skottie_marker_observer_t *observer); // observer is borrowed and retained.
bool Skottie_AnimationBuilder_setPrecompInterceptor(reskia_skottie_animation_builder_t *builder, reskia_skottie_precomp_interceptor_t *interceptor); // interceptor is borrowed and retained.
bool Skottie_AnimationBuilder_setPropertyObserver(reskia_skottie_animation_builder_t *builder, reskia_skottie_property_observer_t *observer); // observer is borrowed and retained.
bool Skottie_AnimationBuilder_setExpressionManager(reskia_skottie_animation_builder_t *builder, reskia_skottie_expression_manager_t *manager); // manager is borrowed and retained.
reskia_skottie_animation_t *Skottie_AnimationBuilder_make(reskia_skottie_animation_builder_t *builder, const char *data, size_t length);
reskia_skottie_animation_t *Skottie_AnimationBuilder_makeFromFile(reskia_skottie_animation_builder_t *builder, const char path[]);
reskia_skottie_slot_manager_t *Skottie_AnimationBuilder_getSlotManager(reskia_skottie_animation_builder_t *builder); // returned pointer owns a ref; release with SlotManager_release.

reskia_skottie_text_property_value_t *TextPropertyValue_new();
reskia_skottie_text_property_value_t *TextPropertyValue_newCopy(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_delete(reskia_skottie_text_property_value_t *value);
bool TextPropertyValue_equals(const reskia_skottie_text_property_value_t *value, const reskia_skottie_text_property_value_t *other);
bool TextPropertyValue_notEquals(const reskia_skottie_text_property_value_t *value, const reskia_skottie_text_property_value_t *other);
void TextPropertyValue_setTypeface(reskia_skottie_text_property_value_t *value, sk_typeface_t typeface);
sk_typeface_t TextPropertyValue_getTypeface(const reskia_skottie_text_property_value_t *value); // returned handle owns a ref; delete with static_sk_typeface_delete.
void TextPropertyValue_setText(reskia_skottie_text_property_value_t *value, const char text[]);
reskia_string_t *TextPropertyValue_getText(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setTextSize(reskia_skottie_text_property_value_t *value, float text_size);
float TextPropertyValue_getTextSize(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setMinTextSize(reskia_skottie_text_property_value_t *value, float min_text_size);
float TextPropertyValue_getMinTextSize(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setMaxTextSize(reskia_skottie_text_property_value_t *value, float max_text_size);
float TextPropertyValue_getMaxTextSize(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setStrokeWidth(reskia_skottie_text_property_value_t *value, float stroke_width);
float TextPropertyValue_getStrokeWidth(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setLineHeight(reskia_skottie_text_property_value_t *value, float line_height);
float TextPropertyValue_getLineHeight(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setLineShift(reskia_skottie_text_property_value_t *value, float line_shift);
float TextPropertyValue_getLineShift(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setAscent(reskia_skottie_text_property_value_t *value, float ascent);
float TextPropertyValue_getAscent(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setMaxLines(reskia_skottie_text_property_value_t *value, size_t max_lines);
size_t TextPropertyValue_getMaxLines(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setHAlign(reskia_skottie_text_property_value_t *value, int32_t align);
int32_t TextPropertyValue_getHAlign(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setVAlign(reskia_skottie_text_property_value_t *value, int32_t align);
int32_t TextPropertyValue_getVAlign(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setResizePolicy(reskia_skottie_text_property_value_t *value, int32_t policy);
int32_t TextPropertyValue_getResizePolicy(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setLinebreakPolicy(reskia_skottie_text_property_value_t *value, int32_t policy);
int32_t TextPropertyValue_getLinebreakPolicy(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setDirection(reskia_skottie_text_property_value_t *value, int32_t direction);
int32_t TextPropertyValue_getDirection(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setCapitalization(reskia_skottie_text_property_value_t *value, int32_t capitalization);
int32_t TextPropertyValue_getCapitalization(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setBox(reskia_skottie_text_property_value_t *value, const reskia_rect_t *box);
bool TextPropertyValue_getBox(const reskia_skottie_text_property_value_t *value, reskia_rect_t *out_box);
void TextPropertyValue_setFillColor(reskia_skottie_text_property_value_t *value, uint32_t color);
uint32_t TextPropertyValue_getFillColor(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setStrokeColor(reskia_skottie_text_property_value_t *value, uint32_t color);
uint32_t TextPropertyValue_getStrokeColor(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setPaintOrder(reskia_skottie_text_property_value_t *value, int32_t order);
int32_t TextPropertyValue_getPaintOrder(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setStrokeJoin(reskia_skottie_text_property_value_t *value, int32_t join);
int32_t TextPropertyValue_getStrokeJoin(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setHasFill(reskia_skottie_text_property_value_t *value, bool has_fill);
bool TextPropertyValue_hasFill(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setHasStroke(reskia_skottie_text_property_value_t *value, bool has_stroke);
bool TextPropertyValue_hasStroke(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setLocale(reskia_skottie_text_property_value_t *value, const char locale[]);
reskia_string_t *TextPropertyValue_getLocale(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setDecorator(reskia_skottie_text_property_value_t *value, reskia_skottie_glyph_decorator_t *decorator); // decorator is borrowed and retained.

reskia_skottie_shaper_result_t *Skottie_Shaper_Shape(const char text[], const reskia_skottie_text_property_value_t *desc, const reskia_rect_t *box, bool use_box, float x, float y, sk_font_mgr_t font_mgr);
reskia_skottie_shaper_result_t *Skottie_Shaper_ShapeAtPoint(const char text[], const reskia_skottie_text_property_value_t *desc, float x, float y, sk_font_mgr_t font_mgr);
reskia_skottie_shaper_result_t *Skottie_Shaper_ShapeInBox(const char text[], const reskia_skottie_text_property_value_t *desc, const reskia_rect_t *box, sk_font_mgr_t font_mgr);
void Skottie_Shaper_Result_delete(reskia_skottie_shaper_result_t *result);
size_t Skottie_Shaper_Result_fragmentCount(const reskia_skottie_shaper_result_t *result);
size_t Skottie_Shaper_Result_missingGlyphCount(const reskia_skottie_shaper_result_t *result);
float Skottie_Shaper_Result_scale(const reskia_skottie_shaper_result_t *result);
bool Skottie_Shaper_Result_computeVisualBounds(const reskia_skottie_shaper_result_t *result, reskia_rect_t *out_bounds);

void SlotManager_ref(reskia_skottie_slot_manager_t *manager);
void SlotManager_unref(reskia_skottie_slot_manager_t *manager);
void SlotManager_release(reskia_skottie_slot_manager_t *manager);
bool SlotManager_setColorSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[], uint32_t color);
bool SlotManager_getColorSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[], uint32_t *out_color);
bool SlotManager_setScalarSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[], float scalar);
bool SlotManager_getScalarSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[], float *out_scalar);
bool SlotManager_setVec2Slot(reskia_skottie_slot_manager_t *manager, const char slot_id[], sk_v2_t vec2);
bool SlotManager_getVec2Slot(reskia_skottie_slot_manager_t *manager, const char slot_id[], sk_v2_t *out_vec2); // out handle owns a value; delete with static_sk_v2_delete.
bool SlotManager_setImageSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[], reskia_skresources_image_asset_t *asset); // asset is borrowed and retained.
reskia_skresources_image_asset_t *SlotManager_getImageSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[]); // returned pointer owns a ref; release with ImageAsset_release.
bool SlotManager_setTextSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[], const reskia_skottie_text_property_value_t *value);
reskia_skottie_text_property_value_t *SlotManager_getTextSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[]);
reskia_skottie_slot_info_t *SlotManager_getSlotInfo(reskia_skottie_slot_manager_t *manager);

void SlotInfo_delete(reskia_skottie_slot_info_t *slot_info);
size_t SlotInfo_colorSlotCount(const reskia_skottie_slot_info_t *slot_info);
size_t SlotInfo_scalarSlotCount(const reskia_skottie_slot_info_t *slot_info);
size_t SlotInfo_vec2SlotCount(const reskia_skottie_slot_info_t *slot_info);
size_t SlotInfo_imageSlotCount(const reskia_skottie_slot_info_t *slot_info);
size_t SlotInfo_textSlotCount(const reskia_skottie_slot_info_t *slot_info);
reskia_string_t *SlotInfo_colorSlotId(const reskia_skottie_slot_info_t *slot_info, size_t index);
reskia_string_t *SlotInfo_scalarSlotId(const reskia_skottie_slot_info_t *slot_info, size_t index);
reskia_string_t *SlotInfo_vec2SlotId(const reskia_skottie_slot_info_t *slot_info, size_t index);
reskia_string_t *SlotInfo_imageSlotId(const reskia_skottie_slot_info_t *slot_info, size_t index);
reskia_string_t *SlotInfo_textSlotId(const reskia_skottie_slot_info_t *slot_info, size_t index);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_SKOTTIE_H
