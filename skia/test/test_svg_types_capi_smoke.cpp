#include <cstdio>

#include "capi/sk_string.h"
#include "capi/sk_svg_types.h"

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[svg-types-capi-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    reskia_svg_length_t *length = SkSVGLength_new(12.5f, 1);
    if (!check(length != nullptr, "SkSVGLength_new")) {
        return 1;
    }
    if (!check(SkSVGLength_value(length) == 12.5f, "SkSVGLength_value")) {
        SkSVGLength_delete(length);
        return 1;
    }

    reskia_svg_length_context_t *length_context = SkSVGLengthContext_new(200.0f, 100.0f, 90.0f);
    float viewport_width = 0.0f;
    float viewport_height = 0.0f;
    if (!check(length_context != nullptr &&
               SkSVGLengthContext_viewPort(length_context, &viewport_width, &viewport_height) &&
               viewport_width == 200.0f &&
               viewport_height == 100.0f &&
               SkSVGLengthContext_resolve(length_context, length, 0) == 12.5f,
               "SkSVGLengthContext accessors")) {
        SkSVGLengthContext_delete(length_context);
        SkSVGLength_delete(length);
        return 1;
    }
    SkSVGLengthContext_setViewPort(length_context, 300.0f, 150.0f);
    float rect_left = 0.0f;
    float rect_top = 0.0f;
    float rect_right = 0.0f;
    float rect_bottom = 0.0f;
    if (!check(SkSVGLengthContext_viewPort(length_context, &viewport_width, &viewport_height) &&
               viewport_width == 300.0f &&
               viewport_height == 150.0f &&
               SkSVGLengthContext_resolveRect(length_context, length, length, length, length,
                                              &rect_left, &rect_top, &rect_right, &rect_bottom) &&
               rect_left == 12.5f &&
               rect_top == 12.5f &&
               rect_right == 25.0f &&
               rect_bottom == 25.0f,
               "SkSVGLengthContext resolveRect")) {
        SkSVGLengthContext_delete(length_context);
        SkSVGLength_delete(length);
        return 1;
    }
    SkSVGLengthContext_delete(length_context);

    reskia_svg_color_t *color = SkSVGColor_new(0xFF336699);
    uint32_t out_color = 0;
    if (!check(color != nullptr && SkSVGColor_type(color) == 1 &&
               SkSVGColor_color(color, &out_color) && out_color == 0xFF336699,
               "SkSVGColor accessors")) {
        SkSVGColor_delete(color);
        SkSVGLength_delete(length);
        return 1;
    }
    if (!check(SkSVGColor_equals(color, color) && !SkSVGColor_notEquals(color, color),
               "SkSVGColor equality")) {
        SkSVGColor_delete(color);
        SkSVGLength_delete(length);
        return 1;
    }
    if (!check(SkSVGColor_vars(color) == 0, "SkSVGColor_vars")) {
        SkSVGColor_delete(color);
        SkSVGLength_delete(length);
        return 1;
    }

    {
        reskia_svg_iri_t *paint_iri = SkSVGIRI_new(0, "gradient0");
        reskia_string_t *paint_iri_text = SkSVGIRI_iri(paint_iri);
        reskia_svg_paint_t *paint = SkSVGPaint_newWithIRI(paint_iri, color);
        reskia_svg_color_t *paint_color = SkSVGPaint_color(paint);
        reskia_svg_iri_t *paint_iri_copy = SkSVGPaint_iri(paint);
        reskia_string_t *paint_iri_copy_text = SkSVGIRI_iri(paint_iri_copy);
        uint32_t paint_color_value = 0;
        const bool svg_value_accessors_ok =
                paint_iri != nullptr && SkSVGIRI_type(paint_iri) == 0 &&
                paint_iri_text != nullptr && SkString_equalsText(paint_iri_text, "gradient0") &&
                paint != nullptr && SkSVGPaint_type(paint) == 2 &&
                paint_color != nullptr && SkSVGColor_color(paint_color, &paint_color_value) &&
                paint_color_value == 0xFF336699 &&
                paint_iri_copy != nullptr && paint_iri_copy_text != nullptr &&
                SkString_equalsText(paint_iri_copy_text, "gradient0");
        SkString_delete(paint_iri_copy_text);
        SkSVGIRI_delete(paint_iri_copy);
        SkSVGColor_delete(paint_color);
        SkSVGPaint_delete(paint);
        SkString_delete(paint_iri_text);
        SkSVGIRI_delete(paint_iri);
        if (!check(svg_value_accessors_ok, "SkSVGIRI/SkSVGPaint accessors")) {
            SkSVGColor_delete(color);
            SkSVGLength_delete(length);
            return 1;
        }

        reskia_svg_line_join_t *line_join = SkSVGLineJoin_new(2);
        reskia_svg_spread_method_t *spread = SkSVGSpreadMethod_new(1);
        reskia_svg_visibility_t *visibility = SkSVGVisibility_new(3);
        reskia_svg_stop_color_t *stop_color = SkSVGStopColor_new(0xFF112233);
        reskia_svg_object_bounding_box_units_t *units = SkSVGObjectBoundingBoxUnits_new(1);
        reskia_svg_text_anchor_t *text_anchor = SkSVGTextAnchor_new(2);
        uint32_t stop_color_value = 0;
        const bool small_value_accessors_ok =
                line_join != nullptr && SkSVGLineJoin_type(line_join) == 2 &&
                spread != nullptr && SkSVGSpreadMethod_type(spread) == 1 &&
                visibility != nullptr && SkSVGVisibility_type(visibility) == 3 &&
                stop_color != nullptr && SkSVGStopColor_type(stop_color) == 0 &&
                SkSVGStopColor_color(stop_color, &stop_color_value) &&
                stop_color_value == 0xFF112233 &&
                units != nullptr && SkSVGObjectBoundingBoxUnits_type(units) == 1 &&
                text_anchor != nullptr && SkSVGTextAnchor_type(text_anchor) == 2;
        SkSVGTextAnchor_delete(text_anchor);
        SkSVGObjectBoundingBoxUnits_delete(units);
        SkSVGStopColor_delete(stop_color);
        SkSVGVisibility_delete(visibility);
        SkSVGSpreadMethod_delete(spread);
        SkSVGLineJoin_delete(line_join);
        if (!check(small_value_accessors_ok, "SVG small value accessors")) {
            SkSVGColor_delete(color);
            SkSVGLength_delete(length);
            return 1;
        }
    }

    reskia_svg_dash_array_t *dash_none = SkSVGDashArray_newWithType(0);
    if (!check(dash_none != nullptr && SkSVGDashArray_type(dash_none) == 0 &&
               SkSVGDashArray_dashArray(dash_none, nullptr, 0) == 0,
               "SkSVGDashArray accessors")) {
        SkSVGDashArray_delete(dash_none);
        SkSVGColor_delete(color);
        SkSVGLength_delete(length);
        return 1;
    }
    if (!check(SkSVGDashArray_equals(dash_none, dash_none) &&
               !SkSVGDashArray_notEquals(dash_none, dash_none),
               "SkSVGDashArray equality")) {
        SkSVGDashArray_delete(dash_none);
        SkSVGColor_delete(color);
        SkSVGLength_delete(length);
        return 1;
    }

    reskia_svg_fe_input_type_t *input = SkSVGFeInputType_newWithId("SourceGraphicRef");
    reskia_string_t *input_id = SkSVGFeInputType_id(input);
    if (!check(input != nullptr && SkSVGFeInputType_type(input) == 6 &&
               input_id != nullptr && SkString_equalsText(input_id, "SourceGraphicRef"),
               "SkSVGFeInputType accessors")) {
        SkString_delete(input_id);
        SkSVGFeInputType_delete(input);
        SkSVGDashArray_delete(dash_none);
        SkSVGColor_delete(color);
        SkSVGLength_delete(length);
        return 1;
    }
    SkString_delete(input_id);
    if (!check(SkSVGFeInputType_equals(input, input) &&
               !SkSVGFeInputType_notEquals(input, input),
               "SkSVGFeInputType equality")) {
        SkSVGFeInputType_delete(input);
        SkSVGDashArray_delete(dash_none);
        SkSVGColor_delete(color);
        SkSVGLength_delete(length);
        return 1;
    }

    reskia_svg_fe_turbulence_base_frequency_t *frequency =
            SkSVGFeTurbulenceBaseFrequency_new(0.25f, 0.5f);
    if (!check(frequency != nullptr &&
               SkSVGFeTurbulenceBaseFrequency_freqX(frequency) == 0.25f &&
               SkSVGFeTurbulenceBaseFrequency_freqY(frequency) == 0.5f,
               "SkSVGFeTurbulenceBaseFrequency accessors")) {
        SkSVGFeTurbulenceBaseFrequency_delete(frequency);
        SkSVGFeInputType_delete(input);
        SkSVGDashArray_delete(dash_none);
        SkSVGColor_delete(color);
        SkSVGLength_delete(length);
        return 1;
    }

    reskia_svg_fill_rule_t *fill_rule = SkSVGFillRule_new(1);
    if (!check(fill_rule != nullptr && SkSVGFillRule_type(fill_rule) == 1 &&
               SkSVGFillRule_asFillType(fill_rule) == 1,
               "SkSVGFillRule accessors")) {
        SkSVGFillRule_delete(fill_rule);
        SkSVGFeTurbulenceBaseFrequency_delete(frequency);
        SkSVGFeInputType_delete(input);
        SkSVGDashArray_delete(dash_none);
        SkSVGColor_delete(color);
        SkSVGLength_delete(length);
        return 1;
    }
    if (!check(SkSVGFillRule_equals(fill_rule, fill_rule) &&
               !SkSVGFillRule_notEquals(fill_rule, fill_rule),
               "SkSVGFillRule equality")) {
        SkSVGFillRule_delete(fill_rule);
        SkSVGFeTurbulenceBaseFrequency_delete(frequency);
        SkSVGFeInputType_delete(input);
        SkSVGDashArray_delete(dash_none);
        SkSVGColor_delete(color);
        SkSVGLength_delete(length);
        return 1;
    }

    reskia_svg_font_family_t *family = SkSVGFontFamily_new("Inter");
    reskia_string_t *family_name = SkSVGFontFamily_family(family);
    if (!check(family != nullptr && SkSVGFontFamily_type(family) == 0 &&
               family_name != nullptr && SkString_equalsText(family_name, "Inter"),
               "SkSVGFontFamily accessors")) {
        SkString_delete(family_name);
        SkSVGFontFamily_delete(family);
        SkSVGFillRule_delete(fill_rule);
        SkSVGFeTurbulenceBaseFrequency_delete(frequency);
        SkSVGFeInputType_delete(input);
        SkSVGDashArray_delete(dash_none);
        SkSVGColor_delete(color);
        SkSVGLength_delete(length);
        return 1;
    }
    SkString_delete(family_name);
    if (!check(SkSVGFontFamily_equals(family, family) &&
               !SkSVGFontFamily_notEquals(family, family),
               "SkSVGFontFamily equality")) {
        SkSVGFontFamily_delete(family);
        SkSVGFillRule_delete(fill_rule);
        SkSVGFeTurbulenceBaseFrequency_delete(frequency);
        SkSVGFeInputType_delete(input);
        SkSVGDashArray_delete(dash_none);
        SkSVGColor_delete(color);
        SkSVGLength_delete(length);
        return 1;
    }

    reskia_svg_font_size_t *font_size = SkSVGFontSize_new(length);
    reskia_svg_length_t *font_size_length = SkSVGFontSize_size(font_size);
    if (!check(font_size != nullptr && SkSVGFontSize_type(font_size) == 0 &&
               font_size_length != nullptr && SkSVGLength_value(font_size_length) == 12.5f,
               "SkSVGFontSize accessors")) {
        SkSVGLength_delete(font_size_length);
        SkSVGFontSize_delete(font_size);
        SkSVGFontFamily_delete(family);
        SkSVGFillRule_delete(fill_rule);
        SkSVGFeTurbulenceBaseFrequency_delete(frequency);
        SkSVGFeInputType_delete(input);
        SkSVGDashArray_delete(dash_none);
        SkSVGColor_delete(color);
        SkSVGLength_delete(length);
        return 1;
    }
    SkSVGLength_delete(font_size_length);
    if (!check(SkSVGFontSize_equals(font_size, font_size) &&
               !SkSVGFontSize_notEquals(font_size, font_size),
               "SkSVGFontSize equality")) {
        SkSVGFontSize_delete(font_size);
        SkSVGFontFamily_delete(family);
        SkSVGFillRule_delete(fill_rule);
        SkSVGFeTurbulenceBaseFrequency_delete(frequency);
        SkSVGFeInputType_delete(input);
        SkSVGDashArray_delete(dash_none);
        SkSVGColor_delete(color);
        SkSVGLength_delete(length);
        return 1;
    }

    reskia_svg_font_style_t *font_style = SkSVGFontStyle_new(1);
    reskia_svg_font_weight_t *font_weight = SkSVGFontWeight_new(10);
    if (!check(font_style != nullptr && SkSVGFontStyle_type(font_style) == 1 &&
               font_weight != nullptr && SkSVGFontWeight_type(font_weight) == 10,
               "SkSVGFontStyle/Weight accessors")) {
        SkSVGFontWeight_delete(font_weight);
        SkSVGFontStyle_delete(font_style);
        SkSVGFontSize_delete(font_size);
        SkSVGFontFamily_delete(family);
        SkSVGFillRule_delete(fill_rule);
        SkSVGFeTurbulenceBaseFrequency_delete(frequency);
        SkSVGFeInputType_delete(input);
        SkSVGDashArray_delete(dash_none);
        SkSVGColor_delete(color);
        SkSVGLength_delete(length);
        return 1;
    }
    if (!check(SkSVGFontStyle_equals(font_style, font_style) &&
               !SkSVGFontStyle_notEquals(font_style, font_style) &&
               SkSVGFontWeight_equals(font_weight, font_weight) &&
               !SkSVGFontWeight_notEquals(font_weight, font_weight),
               "SkSVGFontStyle/Weight equality")) {
        SkSVGFontWeight_delete(font_weight);
        SkSVGFontStyle_delete(font_style);
        SkSVGFontSize_delete(font_size);
        SkSVGFontFamily_delete(family);
        SkSVGFillRule_delete(fill_rule);
        SkSVGFeTurbulenceBaseFrequency_delete(frequency);
        SkSVGFeInputType_delete(input);
        SkSVGDashArray_delete(dash_none);
        SkSVGColor_delete(color);
        SkSVGLength_delete(length);
        return 1;
    }

    reskia_svg_func_iri_t *func_iri = SkSVGFuncIRI_newWithIRI(0, "paint0");
    reskia_string_t *iri = SkSVGFuncIRI_iri(func_iri);
    if (!check(func_iri != nullptr && SkSVGFuncIRI_type(func_iri) == 1 &&
               iri != nullptr && SkString_equalsText(iri, "paint0"),
               "SkSVGFuncIRI accessors")) {
        SkString_delete(iri);
        SkSVGFuncIRI_delete(func_iri);
        SkSVGFontWeight_delete(font_weight);
        SkSVGFontStyle_delete(font_style);
        SkSVGFontSize_delete(font_size);
        SkSVGFontFamily_delete(family);
        SkSVGFillRule_delete(fill_rule);
        SkSVGFeTurbulenceBaseFrequency_delete(frequency);
        SkSVGFeInputType_delete(input);
        SkSVGDashArray_delete(dash_none);
        SkSVGColor_delete(color);
        SkSVGLength_delete(length);
        return 1;
    }
    SkString_delete(iri);
    if (!check(SkSVGFuncIRI_equals(func_iri, func_iri) &&
               !SkSVGFuncIRI_notEquals(func_iri, func_iri),
               "SkSVGFuncIRI equality")) {
        SkSVGFuncIRI_delete(func_iri);
        SkSVGFontWeight_delete(font_weight);
        SkSVGFontStyle_delete(font_style);
        SkSVGFontSize_delete(font_size);
        SkSVGFontFamily_delete(family);
        SkSVGFillRule_delete(fill_rule);
        SkSVGFeTurbulenceBaseFrequency_delete(frequency);
        SkSVGFeInputType_delete(input);
        SkSVGDashArray_delete(dash_none);
        SkSVGColor_delete(color);
        SkSVGLength_delete(length);
        return 1;
    }

    SkSVGFuncIRI_delete(func_iri);
    SkSVGFontWeight_delete(font_weight);
    SkSVGFontStyle_delete(font_style);
    SkSVGFontSize_delete(font_size);
    SkSVGFontFamily_delete(family);
    SkSVGFillRule_delete(fill_rule);
    SkSVGFeTurbulenceBaseFrequency_delete(frequency);
    SkSVGFeInputType_delete(input);
    SkSVGDashArray_delete(dash_none);
    SkSVGColor_delete(color);
    SkSVGLength_delete(length);
    std::fprintf(stdout, "[svg-types-capi-smoke] PASS\n");
    return 0;
}
