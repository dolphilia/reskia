//
// Created by Codex on 2026/05/16.
//

#ifndef RAIA_SKIA_SK_SVG_TYPES_H
#define RAIA_SKIA_SK_SVG_TYPES_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "sk_string.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_svg_color_t reskia_svg_color_t;
typedef struct reskia_svg_dash_array_t reskia_svg_dash_array_t;
typedef struct reskia_svg_fe_input_type_t reskia_svg_fe_input_type_t;
typedef struct reskia_svg_fe_turbulence_base_frequency_t reskia_svg_fe_turbulence_base_frequency_t;
typedef struct reskia_svg_fill_rule_t reskia_svg_fill_rule_t;
typedef struct reskia_svg_font_family_t reskia_svg_font_family_t;
typedef struct reskia_svg_font_size_t reskia_svg_font_size_t;
typedef struct reskia_svg_font_style_t reskia_svg_font_style_t;
typedef struct reskia_svg_font_weight_t reskia_svg_font_weight_t;
typedef struct reskia_svg_func_iri_t reskia_svg_func_iri_t;
typedef struct reskia_svg_iri_t reskia_svg_iri_t;
typedef struct reskia_svg_length_t reskia_svg_length_t;
typedef struct reskia_svg_length_context_t reskia_svg_length_context_t;
typedef struct reskia_svg_line_join_t reskia_svg_line_join_t;
typedef struct reskia_svg_object_bounding_box_units_t reskia_svg_object_bounding_box_units_t;
typedef struct reskia_svg_paint_t reskia_svg_paint_t;
typedef struct reskia_svg_spread_method_t reskia_svg_spread_method_t;
typedef struct reskia_svg_stop_color_t reskia_svg_stop_color_t;
typedef struct reskia_svg_text_anchor_t reskia_svg_text_anchor_t;
typedef struct reskia_svg_visibility_t reskia_svg_visibility_t;

reskia_svg_length_t *SkSVGLength_new(float value, int32_t unit);
void SkSVGLength_delete(reskia_svg_length_t *length);
float SkSVGLength_value(const reskia_svg_length_t *length);
int32_t SkSVGLength_unit(const reskia_svg_length_t *length);

reskia_svg_length_context_t *SkSVGLengthContext_new(float viewport_width, float viewport_height, float dpi);
void SkSVGLengthContext_delete(reskia_svg_length_context_t *context);
bool SkSVGLengthContext_viewPort(const reskia_svg_length_context_t *context, float *out_width, float *out_height);
void SkSVGLengthContext_setViewPort(reskia_svg_length_context_t *context, float width, float height);
float SkSVGLengthContext_resolve(const reskia_svg_length_context_t *context, const reskia_svg_length_t *length, int32_t length_type);
bool SkSVGLengthContext_resolveRect(const reskia_svg_length_context_t *context, const reskia_svg_length_t *x, const reskia_svg_length_t *y, const reskia_svg_length_t *width, const reskia_svg_length_t *height, float *out_left, float *out_top, float *out_right, float *out_bottom);

reskia_svg_color_t *SkSVGColor_new(uint32_t color);
reskia_svg_color_t *SkSVGColor_newWithType(int32_t type);
void SkSVGColor_delete(reskia_svg_color_t *color);
int32_t SkSVGColor_type(const reskia_svg_color_t *color);
bool SkSVGColor_color(const reskia_svg_color_t *color, uint32_t *out_color);
int32_t SkSVGColor_vars(const reskia_svg_color_t *color);
bool SkSVGColor_equals(const reskia_svg_color_t *color, const reskia_svg_color_t *other);
bool SkSVGColor_notEquals(const reskia_svg_color_t *color, const reskia_svg_color_t *other);

reskia_svg_iri_t *SkSVGIRI_new(int32_t type, const char iri[]);
void SkSVGIRI_delete(reskia_svg_iri_t *iri);
int32_t SkSVGIRI_type(const reskia_svg_iri_t *iri);
reskia_string_t *SkSVGIRI_iri(const reskia_svg_iri_t *iri);

reskia_svg_paint_t *SkSVGPaint_newWithType(int32_t type);
reskia_svg_paint_t *SkSVGPaint_newWithColor(const reskia_svg_color_t *color);
reskia_svg_paint_t *SkSVGPaint_newWithIRI(const reskia_svg_iri_t *iri, const reskia_svg_color_t *fallback_color);
void SkSVGPaint_delete(reskia_svg_paint_t *paint);
int32_t SkSVGPaint_type(const reskia_svg_paint_t *paint);
reskia_svg_color_t *SkSVGPaint_color(const reskia_svg_paint_t *paint);
reskia_svg_iri_t *SkSVGPaint_iri(const reskia_svg_paint_t *paint);

reskia_svg_dash_array_t *SkSVGDashArray_newWithType(int32_t type);
reskia_svg_dash_array_t *SkSVGDashArray_new(const reskia_svg_length_t *lengths, int32_t count);
void SkSVGDashArray_delete(reskia_svg_dash_array_t *dash_array);
int32_t SkSVGDashArray_type(const reskia_svg_dash_array_t *dash_array);
int32_t SkSVGDashArray_dashArray(const reskia_svg_dash_array_t *dash_array, reskia_svg_length_t *dst, int32_t dst_count);
bool SkSVGDashArray_equals(const reskia_svg_dash_array_t *dash_array, const reskia_svg_dash_array_t *other);
bool SkSVGDashArray_notEquals(const reskia_svg_dash_array_t *dash_array, const reskia_svg_dash_array_t *other);

reskia_svg_fe_input_type_t *SkSVGFeInputType_newWithType(int32_t type);
reskia_svg_fe_input_type_t *SkSVGFeInputType_newWithId(const char id[]);
void SkSVGFeInputType_delete(reskia_svg_fe_input_type_t *input);
int32_t SkSVGFeInputType_type(const reskia_svg_fe_input_type_t *input);
reskia_string_t *SkSVGFeInputType_id(const reskia_svg_fe_input_type_t *input);
bool SkSVGFeInputType_equals(const reskia_svg_fe_input_type_t *input, const reskia_svg_fe_input_type_t *other);
bool SkSVGFeInputType_notEquals(const reskia_svg_fe_input_type_t *input, const reskia_svg_fe_input_type_t *other);

reskia_svg_fe_turbulence_base_frequency_t *SkSVGFeTurbulenceBaseFrequency_new(float freq_x, float freq_y);
void SkSVGFeTurbulenceBaseFrequency_delete(reskia_svg_fe_turbulence_base_frequency_t *frequency);
float SkSVGFeTurbulenceBaseFrequency_freqX(const reskia_svg_fe_turbulence_base_frequency_t *frequency);
float SkSVGFeTurbulenceBaseFrequency_freqY(const reskia_svg_fe_turbulence_base_frequency_t *frequency);

reskia_svg_fill_rule_t *SkSVGFillRule_new(int32_t type);
void SkSVGFillRule_delete(reskia_svg_fill_rule_t *rule);
int32_t SkSVGFillRule_type(const reskia_svg_fill_rule_t *rule);
int32_t SkSVGFillRule_asFillType(const reskia_svg_fill_rule_t *rule);
bool SkSVGFillRule_equals(const reskia_svg_fill_rule_t *rule, const reskia_svg_fill_rule_t *other);
bool SkSVGFillRule_notEquals(const reskia_svg_fill_rule_t *rule, const reskia_svg_fill_rule_t *other);

reskia_svg_line_join_t *SkSVGLineJoin_new(int32_t type);
void SkSVGLineJoin_delete(reskia_svg_line_join_t *join);
int32_t SkSVGLineJoin_type(const reskia_svg_line_join_t *join);

reskia_svg_spread_method_t *SkSVGSpreadMethod_new(int32_t type);
void SkSVGSpreadMethod_delete(reskia_svg_spread_method_t *method);
int32_t SkSVGSpreadMethod_type(const reskia_svg_spread_method_t *method);

reskia_svg_visibility_t *SkSVGVisibility_new(int32_t type);
void SkSVGVisibility_delete(reskia_svg_visibility_t *visibility);
int32_t SkSVGVisibility_type(const reskia_svg_visibility_t *visibility);

reskia_svg_stop_color_t *SkSVGStopColor_new(uint32_t color);
reskia_svg_stop_color_t *SkSVGStopColor_newWithType(int32_t type);
void SkSVGStopColor_delete(reskia_svg_stop_color_t *color);
int32_t SkSVGStopColor_type(const reskia_svg_stop_color_t *color);
bool SkSVGStopColor_color(const reskia_svg_stop_color_t *color, uint32_t *out_color);

reskia_svg_object_bounding_box_units_t *SkSVGObjectBoundingBoxUnits_new(int32_t type);
void SkSVGObjectBoundingBoxUnits_delete(reskia_svg_object_bounding_box_units_t *units);
int32_t SkSVGObjectBoundingBoxUnits_type(const reskia_svg_object_bounding_box_units_t *units);

reskia_svg_font_family_t *SkSVGFontFamily_new(const char family[]);
reskia_svg_font_family_t *SkSVGFontFamily_newInherit(void);
void SkSVGFontFamily_delete(reskia_svg_font_family_t *family);
int32_t SkSVGFontFamily_type(const reskia_svg_font_family_t *family);
reskia_string_t *SkSVGFontFamily_family(const reskia_svg_font_family_t *family);
bool SkSVGFontFamily_equals(const reskia_svg_font_family_t *family, const reskia_svg_font_family_t *other);
bool SkSVGFontFamily_notEquals(const reskia_svg_font_family_t *family, const reskia_svg_font_family_t *other);

reskia_svg_font_size_t *SkSVGFontSize_new(const reskia_svg_length_t *length);
reskia_svg_font_size_t *SkSVGFontSize_newInherit(void);
void SkSVGFontSize_delete(reskia_svg_font_size_t *size);
int32_t SkSVGFontSize_type(const reskia_svg_font_size_t *size);
reskia_svg_length_t *SkSVGFontSize_size(const reskia_svg_font_size_t *size);
bool SkSVGFontSize_equals(const reskia_svg_font_size_t *size, const reskia_svg_font_size_t *other);
bool SkSVGFontSize_notEquals(const reskia_svg_font_size_t *size, const reskia_svg_font_size_t *other);

reskia_svg_font_style_t *SkSVGFontStyle_new(int32_t type);
void SkSVGFontStyle_delete(reskia_svg_font_style_t *style);
int32_t SkSVGFontStyle_type(const reskia_svg_font_style_t *style);
bool SkSVGFontStyle_equals(const reskia_svg_font_style_t *style, const reskia_svg_font_style_t *other);
bool SkSVGFontStyle_notEquals(const reskia_svg_font_style_t *style, const reskia_svg_font_style_t *other);

reskia_svg_font_weight_t *SkSVGFontWeight_new(int32_t type);
void SkSVGFontWeight_delete(reskia_svg_font_weight_t *weight);
int32_t SkSVGFontWeight_type(const reskia_svg_font_weight_t *weight);
bool SkSVGFontWeight_equals(const reskia_svg_font_weight_t *weight, const reskia_svg_font_weight_t *other);
bool SkSVGFontWeight_notEquals(const reskia_svg_font_weight_t *weight, const reskia_svg_font_weight_t *other);

reskia_svg_func_iri_t *SkSVGFuncIRI_newWithType(int32_t type);
reskia_svg_func_iri_t *SkSVGFuncIRI_newWithIRI(int32_t iri_type, const char iri[]);
void SkSVGFuncIRI_delete(reskia_svg_func_iri_t *func_iri);
int32_t SkSVGFuncIRI_type(const reskia_svg_func_iri_t *func_iri);
reskia_string_t *SkSVGFuncIRI_iri(const reskia_svg_func_iri_t *func_iri);
bool SkSVGFuncIRI_equals(const reskia_svg_func_iri_t *func_iri, const reskia_svg_func_iri_t *other);
bool SkSVGFuncIRI_notEquals(const reskia_svg_func_iri_t *func_iri, const reskia_svg_func_iri_t *other);

reskia_svg_text_anchor_t *SkSVGTextAnchor_new(int32_t type);
void SkSVGTextAnchor_delete(reskia_svg_text_anchor_t *anchor);
int32_t SkSVGTextAnchor_type(const reskia_svg_text_anchor_t *anchor);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_SVG_TYPES_H
