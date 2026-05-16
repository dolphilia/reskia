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
