//
// Created by Codex on 2026/05/16.
//

#include "sk_svg_types.h"

#include <algorithm>
#include <utility>
#include <vector>

#include "include/core/SkColor.h"
#include "include/core/SkPathTypes.h"
#include "include/core/SkRect.h"
#include "include/core/SkSize.h"
#include "include/core/SkString.h"
#include "modules/svg/include/SkSVGNode.h"
#include "modules/svg/include/SkSVGRenderContext.h"
#include "modules/svg/include/SkSVGTypes.h"

namespace {

template <typename T, typename Opaque>
T *as_type(const Opaque *value) {
    return const_cast<T *>(reinterpret_cast<const T *>(value));
}

template <typename Opaque, typename T>
Opaque *to_opaque(T *value) {
    return reinterpret_cast<Opaque *>(value);
}

SkSVGLength::Unit svg_length_unit(int32_t unit) {
    if (unit < static_cast<int32_t>(SkSVGLength::Unit::kUnknown) ||
        unit > static_cast<int32_t>(SkSVGLength::Unit::kPC)) {
        return SkSVGLength::Unit::kUnknown;
    }
    return static_cast<SkSVGLength::Unit>(unit);
}

SkSVGLengthContext::LengthType svg_length_type(int32_t type) {
    if (type < static_cast<int32_t>(SkSVGLengthContext::LengthType::kHorizontal) ||
        type > static_cast<int32_t>(SkSVGLengthContext::LengthType::kOther)) {
        return SkSVGLengthContext::LengthType::kOther;
    }
    return static_cast<SkSVGLengthContext::LengthType>(type);
}

SkSVGColor::Type svg_color_type(int32_t type) {
    if (type < static_cast<int32_t>(SkSVGColor::Type::kCurrentColor) ||
        type > static_cast<int32_t>(SkSVGColor::Type::kICCColor)) {
        return SkSVGColor::Type::kCurrentColor;
    }
    return static_cast<SkSVGColor::Type>(type);
}

SkSVGDashArray::Type svg_dash_array_type(int32_t type) {
    if (type < static_cast<int32_t>(SkSVGDashArray::Type::kNone) ||
        type > static_cast<int32_t>(SkSVGDashArray::Type::kInherit)) {
        return SkSVGDashArray::Type::kNone;
    }
    return static_cast<SkSVGDashArray::Type>(type);
}

SkSVGFeInputType::Type svg_fe_input_type(int32_t type) {
    if (type < static_cast<int32_t>(SkSVGFeInputType::Type::kSourceGraphic) ||
        type > static_cast<int32_t>(SkSVGFeInputType::Type::kUnspecified)) {
        return SkSVGFeInputType::Type::kUnspecified;
    }
    return static_cast<SkSVGFeInputType::Type>(type);
}

SkSVGFillRule::Type svg_fill_rule_type(int32_t type) {
    if (type < static_cast<int32_t>(SkSVGFillRule::Type::kNonZero) ||
        type > static_cast<int32_t>(SkSVGFillRule::Type::kInherit)) {
        return SkSVGFillRule::Type::kInherit;
    }
    return static_cast<SkSVGFillRule::Type>(type);
}

SkSVGFontStyle::Type svg_font_style_type(int32_t type) {
    if (type < static_cast<int32_t>(SkSVGFontStyle::Type::kNormal) ||
        type > static_cast<int32_t>(SkSVGFontStyle::Type::kInherit)) {
        return SkSVGFontStyle::Type::kInherit;
    }
    return static_cast<SkSVGFontStyle::Type>(type);
}

SkSVGFontWeight::Type svg_font_weight_type(int32_t type) {
    if (type < static_cast<int32_t>(SkSVGFontWeight::Type::k100) ||
        type > static_cast<int32_t>(SkSVGFontWeight::Type::kInherit)) {
        return SkSVGFontWeight::Type::kInherit;
    }
    return static_cast<SkSVGFontWeight::Type>(type);
}

SkSVGFuncIRI::Type svg_func_iri_type(int32_t type) {
    if (type < static_cast<int32_t>(SkSVGFuncIRI::Type::kNone) ||
        type > static_cast<int32_t>(SkSVGFuncIRI::Type::kIRI)) {
        return SkSVGFuncIRI::Type::kNone;
    }
    return static_cast<SkSVGFuncIRI::Type>(type);
}

SkSVGPaint::Type svg_paint_type(int32_t type) {
    if (type < static_cast<int32_t>(SkSVGPaint::Type::kNone) ||
        type > static_cast<int32_t>(SkSVGPaint::Type::kIRI)) {
        return SkSVGPaint::Type::kNone;
    }
    return static_cast<SkSVGPaint::Type>(type);
}

SkSVGIRI::Type svg_iri_type(int32_t type) {
    if (type < static_cast<int32_t>(SkSVGIRI::Type::kLocal) ||
        type > static_cast<int32_t>(SkSVGIRI::Type::kDataURI)) {
        return SkSVGIRI::Type::kLocal;
    }
    return static_cast<SkSVGIRI::Type>(type);
}

SkSVGPreserveAspectRatio::Align svg_preserve_aspect_ratio_align(int32_t align) {
    switch (align) {
        case SkSVGPreserveAspectRatio::kXMinYMin:
        case SkSVGPreserveAspectRatio::kXMidYMin:
        case SkSVGPreserveAspectRatio::kXMaxYMin:
        case SkSVGPreserveAspectRatio::kXMinYMid:
        case SkSVGPreserveAspectRatio::kXMidYMid:
        case SkSVGPreserveAspectRatio::kXMaxYMid:
        case SkSVGPreserveAspectRatio::kXMinYMax:
        case SkSVGPreserveAspectRatio::kXMidYMax:
        case SkSVGPreserveAspectRatio::kXMaxYMax:
        case SkSVGPreserveAspectRatio::kNone:
            return static_cast<SkSVGPreserveAspectRatio::Align>(align);
        default:
            return SkSVGPreserveAspectRatio::kXMidYMid;
    }
}

SkSVGPreserveAspectRatio::Scale svg_preserve_aspect_ratio_scale(int32_t scale) {
    return scale == static_cast<int32_t>(SkSVGPreserveAspectRatio::kSlice) ?
            SkSVGPreserveAspectRatio::kSlice :
            SkSVGPreserveAspectRatio::kMeet;
}

SkSVGLineJoin::Type svg_line_join_type(int32_t type) {
    if (type < static_cast<int32_t>(SkSVGLineJoin::Type::kMiter) ||
        type > static_cast<int32_t>(SkSVGLineJoin::Type::kInherit)) {
        return SkSVGLineJoin::Type::kInherit;
    }
    return static_cast<SkSVGLineJoin::Type>(type);
}

SkSVGSpreadMethod::Type svg_spread_method_type(int32_t type) {
    if (type < static_cast<int32_t>(SkSVGSpreadMethod::Type::kPad) ||
        type > static_cast<int32_t>(SkSVGSpreadMethod::Type::kReflect)) {
        return SkSVGSpreadMethod::Type::kPad;
    }
    return static_cast<SkSVGSpreadMethod::Type>(type);
}

SkSVGVisibility::Type svg_visibility_type(int32_t type) {
    if (type < static_cast<int32_t>(SkSVGVisibility::Type::kVisible) ||
        type > static_cast<int32_t>(SkSVGVisibility::Type::kInherit)) {
        return SkSVGVisibility::Type::kVisible;
    }
    return static_cast<SkSVGVisibility::Type>(type);
}

SkSVGStopColor::Type svg_stop_color_type(int32_t type) {
    if (type < static_cast<int32_t>(SkSVGStopColor::Type::kColor) ||
        type > static_cast<int32_t>(SkSVGStopColor::Type::kInherit)) {
        return SkSVGStopColor::Type::kInherit;
    }
    return static_cast<SkSVGStopColor::Type>(type);
}

SkSVGObjectBoundingBoxUnits::Type svg_object_bounding_box_units_type(int32_t type) {
    if (type < static_cast<int32_t>(SkSVGObjectBoundingBoxUnits::Type::kUserSpaceOnUse) ||
        type > static_cast<int32_t>(SkSVGObjectBoundingBoxUnits::Type::kObjectBoundingBox)) {
        return SkSVGObjectBoundingBoxUnits::Type::kUserSpaceOnUse;
    }
    return static_cast<SkSVGObjectBoundingBoxUnits::Type>(type);
}

SkSVGTextAnchor::Type svg_text_anchor_type(int32_t type) {
    if (type < static_cast<int32_t>(SkSVGTextAnchor::Type::kStart) ||
        type > static_cast<int32_t>(SkSVGTextAnchor::Type::kInherit)) {
        return SkSVGTextAnchor::Type::kInherit;
    }
    return static_cast<SkSVGTextAnchor::Type>(type);
}

reskia_string_t *make_string(const SkString& string) {
    return reinterpret_cast<reskia_string_t *>(new SkString(string));
}

}  // namespace

extern "C" {

reskia_svg_length_t *SkSVGLength_new(float value, int32_t unit) {
    return to_opaque<reskia_svg_length_t>(new SkSVGLength(value, svg_length_unit(unit)));
}

void SkSVGLength_delete(reskia_svg_length_t *length) {
    delete as_type<SkSVGLength>(length);
}

float SkSVGLength_value(const reskia_svg_length_t *length) {
    return length != nullptr ? as_type<SkSVGLength>(length)->value() : 0.0f;
}

int32_t SkSVGLength_unit(const reskia_svg_length_t *length) {
    return length != nullptr ? static_cast<int32_t>(as_type<SkSVGLength>(length)->unit()) : 0;
}

reskia_svg_length_context_t *SkSVGLengthContext_new(float viewport_width, float viewport_height, float dpi) {
    return to_opaque<reskia_svg_length_context_t>(
            new SkSVGLengthContext(SkSize::Make(viewport_width, viewport_height), dpi));
}

void SkSVGLengthContext_delete(reskia_svg_length_context_t *context) {
    delete as_type<SkSVGLengthContext>(context);
}

bool SkSVGLengthContext_viewPort(const reskia_svg_length_context_t *context, float *out_width, float *out_height) {
    if (context == nullptr) {
        return false;
    }
    const SkSize& view_port = as_type<SkSVGLengthContext>(context)->viewPort();
    if (out_width != nullptr) {
        *out_width = view_port.width();
    }
    if (out_height != nullptr) {
        *out_height = view_port.height();
    }
    return true;
}

void SkSVGLengthContext_setViewPort(reskia_svg_length_context_t *context, float width, float height) {
    if (context != nullptr) {
        as_type<SkSVGLengthContext>(context)->setViewPort(SkSize::Make(width, height));
    }
}

float SkSVGLengthContext_resolve(const reskia_svg_length_context_t *context, const reskia_svg_length_t *length, int32_t length_type) {
    return context != nullptr && length != nullptr ?
            as_type<SkSVGLengthContext>(context)->resolve(*as_type<SkSVGLength>(length), svg_length_type(length_type)) :
            0.0f;
}

bool SkSVGLengthContext_resolveRect(
        const reskia_svg_length_context_t *context,
        const reskia_svg_length_t *x,
        const reskia_svg_length_t *y,
        const reskia_svg_length_t *width,
        const reskia_svg_length_t *height,
        float *out_left,
        float *out_top,
        float *out_right,
        float *out_bottom) {
    if (context == nullptr || x == nullptr || y == nullptr || width == nullptr || height == nullptr) {
        return false;
    }
    const SkRect rect = as_type<SkSVGLengthContext>(context)->resolveRect(
            *as_type<SkSVGLength>(x), *as_type<SkSVGLength>(y),
            *as_type<SkSVGLength>(width), *as_type<SkSVGLength>(height));
    if (out_left != nullptr) {
        *out_left = rect.left();
    }
    if (out_top != nullptr) {
        *out_top = rect.top();
    }
    if (out_right != nullptr) {
        *out_right = rect.right();
    }
    if (out_bottom != nullptr) {
        *out_bottom = rect.bottom();
    }
    return true;
}

reskia_svg_color_t *SkSVGColor_new(uint32_t color) {
    return to_opaque<reskia_svg_color_t>(new SkSVGColor(static_cast<SkColor>(color)));
}

reskia_svg_color_t *SkSVGColor_newWithType(int32_t type) {
    return to_opaque<reskia_svg_color_t>(new SkSVGColor(svg_color_type(type), SkSVGColor::Vars()));
}

void SkSVGColor_delete(reskia_svg_color_t *color) {
    delete as_type<SkSVGColor>(color);
}

int32_t SkSVGColor_type(const reskia_svg_color_t *color) {
    return color != nullptr ? static_cast<int32_t>(as_type<SkSVGColor>(color)->type()) : -1;
}

bool SkSVGColor_color(const reskia_svg_color_t *color, uint32_t *out_color) {
    if (color == nullptr || out_color == nullptr ||
        as_type<SkSVGColor>(color)->type() != SkSVGColor::Type::kColor) {
        return false;
    }
    *out_color = as_type<SkSVGColor>(color)->color();
    return true;
}

int32_t SkSVGColor_vars(const reskia_svg_color_t *color) {
    return color != nullptr ? static_cast<int32_t>(as_type<SkSVGColor>(color)->vars().size()) : 0;
}

bool SkSVGColor_equals(const reskia_svg_color_t *color, const reskia_svg_color_t *other) {
    return color != nullptr && other != nullptr && *as_type<SkSVGColor>(color) == *as_type<SkSVGColor>(other);
}

bool SkSVGColor_notEquals(const reskia_svg_color_t *color, const reskia_svg_color_t *other) {
    return color == nullptr || other == nullptr || *as_type<SkSVGColor>(color) != *as_type<SkSVGColor>(other);
}

reskia_svg_iri_t *SkSVGIRI_new(int32_t type, const char iri[]) {
    return iri != nullptr ? to_opaque<reskia_svg_iri_t>(new SkSVGIRI(svg_iri_type(type), SkString(iri))) : nullptr;
}

void SkSVGIRI_delete(reskia_svg_iri_t *iri) {
    delete as_type<SkSVGIRI>(iri);
}

int32_t SkSVGIRI_type(const reskia_svg_iri_t *iri) {
    return iri != nullptr ? static_cast<int32_t>(as_type<SkSVGIRI>(iri)->type()) : -1;
}

reskia_string_t *SkSVGIRI_iri(const reskia_svg_iri_t *iri) {
    return iri != nullptr ? make_string(as_type<SkSVGIRI>(iri)->iri()) : nullptr;
}

reskia_svg_preserve_aspect_ratio_t *SkSVGPreserveAspectRatio_new(int32_t align, int32_t scale) {
    auto *preserve_aspect_ratio = new SkSVGPreserveAspectRatio();
    preserve_aspect_ratio->fAlign = svg_preserve_aspect_ratio_align(align);
    preserve_aspect_ratio->fScale = svg_preserve_aspect_ratio_scale(scale);
    return to_opaque<reskia_svg_preserve_aspect_ratio_t>(preserve_aspect_ratio);
}

void SkSVGPreserveAspectRatio_delete(reskia_svg_preserve_aspect_ratio_t *preserve_aspect_ratio) {
    delete as_type<SkSVGPreserveAspectRatio>(preserve_aspect_ratio);
}

int32_t SkSVGPreserveAspectRatio_align(const reskia_svg_preserve_aspect_ratio_t *preserve_aspect_ratio) {
    return preserve_aspect_ratio != nullptr ?
            static_cast<int32_t>(as_type<SkSVGPreserveAspectRatio>(preserve_aspect_ratio)->fAlign) :
            -1;
}

int32_t SkSVGPreserveAspectRatio_scale(const reskia_svg_preserve_aspect_ratio_t *preserve_aspect_ratio) {
    return preserve_aspect_ratio != nullptr ?
            static_cast<int32_t>(as_type<SkSVGPreserveAspectRatio>(preserve_aspect_ratio)->fScale) :
            -1;
}

void SkSVGPreserveAspectRatio_set(
        reskia_svg_preserve_aspect_ratio_t *preserve_aspect_ratio,
        int32_t align,
        int32_t scale) {
    if (preserve_aspect_ratio == nullptr) {
        return;
    }
    auto *typed = as_type<SkSVGPreserveAspectRatio>(preserve_aspect_ratio);
    typed->fAlign = svg_preserve_aspect_ratio_align(align);
    typed->fScale = svg_preserve_aspect_ratio_scale(scale);
}

reskia_svg_paint_t *SkSVGPaint_newWithType(int32_t type) {
    return to_opaque<reskia_svg_paint_t>(new SkSVGPaint(svg_paint_type(type)));
}

reskia_svg_paint_t *SkSVGPaint_newWithColor(const reskia_svg_color_t *color) {
    return color != nullptr ? to_opaque<reskia_svg_paint_t>(new SkSVGPaint(*as_type<SkSVGColor>(color))) : nullptr;
}

reskia_svg_paint_t *SkSVGPaint_newWithIRI(const reskia_svg_iri_t *iri, const reskia_svg_color_t *fallback_color) {
    return iri != nullptr && fallback_color != nullptr ?
            to_opaque<reskia_svg_paint_t>(new SkSVGPaint(*as_type<SkSVGIRI>(iri), *as_type<SkSVGColor>(fallback_color))) :
            nullptr;
}

void SkSVGPaint_delete(reskia_svg_paint_t *paint) {
    delete as_type<SkSVGPaint>(paint);
}

int32_t SkSVGPaint_type(const reskia_svg_paint_t *paint) {
    return paint != nullptr ? static_cast<int32_t>(as_type<SkSVGPaint>(paint)->type()) : -1;
}

reskia_svg_color_t *SkSVGPaint_color(const reskia_svg_paint_t *paint) {
    if (paint == nullptr ||
        (as_type<SkSVGPaint>(paint)->type() != SkSVGPaint::Type::kColor &&
         as_type<SkSVGPaint>(paint)->type() != SkSVGPaint::Type::kIRI)) {
        return nullptr;
    }
    return to_opaque<reskia_svg_color_t>(new SkSVGColor(as_type<SkSVGPaint>(paint)->color()));
}

reskia_svg_iri_t *SkSVGPaint_iri(const reskia_svg_paint_t *paint) {
    if (paint == nullptr || as_type<SkSVGPaint>(paint)->type() != SkSVGPaint::Type::kIRI) {
        return nullptr;
    }
    return to_opaque<reskia_svg_iri_t>(new SkSVGIRI(as_type<SkSVGPaint>(paint)->iri()));
}

reskia_svg_dash_array_t *SkSVGDashArray_newWithType(int32_t type) {
    return to_opaque<reskia_svg_dash_array_t>(new SkSVGDashArray(svg_dash_array_type(type)));
}

reskia_svg_dash_array_t *SkSVGDashArray_new(const reskia_svg_length_t *lengths, int32_t count) {
    if (count < 0 || (count > 0 && lengths == nullptr)) {
        return nullptr;
    }
    std::vector<SkSVGLength> values;
    values.reserve(static_cast<size_t>(count));
    const auto *typed_lengths = reinterpret_cast<const SkSVGLength *>(lengths);
    for (int32_t i = 0; i < count; ++i) {
        values.push_back(typed_lengths[i]);
    }
    return to_opaque<reskia_svg_dash_array_t>(new SkSVGDashArray(std::move(values)));
}

void SkSVGDashArray_delete(reskia_svg_dash_array_t *dash_array) {
    delete as_type<SkSVGDashArray>(dash_array);
}

int32_t SkSVGDashArray_type(const reskia_svg_dash_array_t *dash_array) {
    return dash_array != nullptr ? static_cast<int32_t>(as_type<SkSVGDashArray>(dash_array)->type()) : -1;
}

int32_t SkSVGDashArray_dashArray(const reskia_svg_dash_array_t *dash_array, reskia_svg_length_t *dst, int32_t dst_count) {
    if (dash_array == nullptr || dst_count < 0) {
        return 0;
    }
    const auto& values = as_type<SkSVGDashArray>(dash_array)->dashArray();
    if (dst != nullptr) {
        auto *typed_dst = reinterpret_cast<SkSVGLength *>(dst);
        const int32_t copy_count = std::min<int32_t>(static_cast<int32_t>(values.size()), dst_count);
        for (int32_t i = 0; i < copy_count; ++i) {
            typed_dst[i] = values[static_cast<size_t>(i)];
        }
    }
    return static_cast<int32_t>(values.size());
}

bool SkSVGDashArray_equals(const reskia_svg_dash_array_t *dash_array, const reskia_svg_dash_array_t *other) {
    return dash_array != nullptr && other != nullptr && *as_type<SkSVGDashArray>(dash_array) == *as_type<SkSVGDashArray>(other);
}

bool SkSVGDashArray_notEquals(const reskia_svg_dash_array_t *dash_array, const reskia_svg_dash_array_t *other) {
    return dash_array == nullptr || other == nullptr || *as_type<SkSVGDashArray>(dash_array) != *as_type<SkSVGDashArray>(other);
}

reskia_svg_fe_input_type_t *SkSVGFeInputType_newWithType(int32_t type) {
    return to_opaque<reskia_svg_fe_input_type_t>(new SkSVGFeInputType(svg_fe_input_type(type)));
}

reskia_svg_fe_input_type_t *SkSVGFeInputType_newWithId(const char id[]) {
    return id != nullptr ? to_opaque<reskia_svg_fe_input_type_t>(new SkSVGFeInputType(SkString(id))) : nullptr;
}

void SkSVGFeInputType_delete(reskia_svg_fe_input_type_t *input) {
    delete as_type<SkSVGFeInputType>(input);
}

int32_t SkSVGFeInputType_type(const reskia_svg_fe_input_type_t *input) {
    return input != nullptr ? static_cast<int32_t>(as_type<SkSVGFeInputType>(input)->type()) : -1;
}

reskia_string_t *SkSVGFeInputType_id(const reskia_svg_fe_input_type_t *input) {
    if (input == nullptr || as_type<SkSVGFeInputType>(input)->type() != SkSVGFeInputType::Type::kFilterPrimitiveReference) {
        return nullptr;
    }
    return make_string(as_type<SkSVGFeInputType>(input)->id());
}

bool SkSVGFeInputType_equals(const reskia_svg_fe_input_type_t *input, const reskia_svg_fe_input_type_t *other) {
    return input != nullptr && other != nullptr && *as_type<SkSVGFeInputType>(input) == *as_type<SkSVGFeInputType>(other);
}

bool SkSVGFeInputType_notEquals(const reskia_svg_fe_input_type_t *input, const reskia_svg_fe_input_type_t *other) {
    return input == nullptr || other == nullptr || *as_type<SkSVGFeInputType>(input) != *as_type<SkSVGFeInputType>(other);
}

reskia_svg_fe_turbulence_base_frequency_t *SkSVGFeTurbulenceBaseFrequency_new(float freq_x, float freq_y) {
    return to_opaque<reskia_svg_fe_turbulence_base_frequency_t>(
            new SkSVGFeTurbulenceBaseFrequency(freq_x, freq_y));
}

void SkSVGFeTurbulenceBaseFrequency_delete(reskia_svg_fe_turbulence_base_frequency_t *frequency) {
    delete as_type<SkSVGFeTurbulenceBaseFrequency>(frequency);
}

float SkSVGFeTurbulenceBaseFrequency_freqX(const reskia_svg_fe_turbulence_base_frequency_t *frequency) {
    return frequency != nullptr ? as_type<SkSVGFeTurbulenceBaseFrequency>(frequency)->freqX() : 0.0f;
}

float SkSVGFeTurbulenceBaseFrequency_freqY(const reskia_svg_fe_turbulence_base_frequency_t *frequency) {
    return frequency != nullptr ? as_type<SkSVGFeTurbulenceBaseFrequency>(frequency)->freqY() : 0.0f;
}

reskia_svg_fill_rule_t *SkSVGFillRule_new(int32_t type) {
    return to_opaque<reskia_svg_fill_rule_t>(new SkSVGFillRule(svg_fill_rule_type(type)));
}

void SkSVGFillRule_delete(reskia_svg_fill_rule_t *rule) {
    delete as_type<SkSVGFillRule>(rule);
}

int32_t SkSVGFillRule_type(const reskia_svg_fill_rule_t *rule) {
    return rule != nullptr ? static_cast<int32_t>(as_type<SkSVGFillRule>(rule)->type()) : -1;
}

int32_t SkSVGFillRule_asFillType(const reskia_svg_fill_rule_t *rule) {
    if (rule == nullptr || as_type<SkSVGFillRule>(rule)->type() == SkSVGFillRule::Type::kInherit) {
        return -1;
    }
    return static_cast<int32_t>(as_type<SkSVGFillRule>(rule)->asFillType());
}

bool SkSVGFillRule_equals(const reskia_svg_fill_rule_t *rule, const reskia_svg_fill_rule_t *other) {
    return rule != nullptr && other != nullptr && *as_type<SkSVGFillRule>(rule) == *as_type<SkSVGFillRule>(other);
}

bool SkSVGFillRule_notEquals(const reskia_svg_fill_rule_t *rule, const reskia_svg_fill_rule_t *other) {
    return rule == nullptr || other == nullptr || *as_type<SkSVGFillRule>(rule) != *as_type<SkSVGFillRule>(other);
}

reskia_svg_line_join_t *SkSVGLineJoin_new(int32_t type) {
    return to_opaque<reskia_svg_line_join_t>(new SkSVGLineJoin(svg_line_join_type(type)));
}

void SkSVGLineJoin_delete(reskia_svg_line_join_t *join) {
    delete as_type<SkSVGLineJoin>(join);
}

int32_t SkSVGLineJoin_type(const reskia_svg_line_join_t *join) {
    return join != nullptr ? static_cast<int32_t>(as_type<SkSVGLineJoin>(join)->type()) : -1;
}

reskia_svg_spread_method_t *SkSVGSpreadMethod_new(int32_t type) {
    return to_opaque<reskia_svg_spread_method_t>(new SkSVGSpreadMethod(svg_spread_method_type(type)));
}

void SkSVGSpreadMethod_delete(reskia_svg_spread_method_t *method) {
    delete as_type<SkSVGSpreadMethod>(method);
}

int32_t SkSVGSpreadMethod_type(const reskia_svg_spread_method_t *method) {
    return method != nullptr ? static_cast<int32_t>(as_type<SkSVGSpreadMethod>(method)->type()) : -1;
}

reskia_svg_visibility_t *SkSVGVisibility_new(int32_t type) {
    return to_opaque<reskia_svg_visibility_t>(new SkSVGVisibility(svg_visibility_type(type)));
}

void SkSVGVisibility_delete(reskia_svg_visibility_t *visibility) {
    delete as_type<SkSVGVisibility>(visibility);
}

int32_t SkSVGVisibility_type(const reskia_svg_visibility_t *visibility) {
    return visibility != nullptr ? static_cast<int32_t>(as_type<SkSVGVisibility>(visibility)->type()) : -1;
}

reskia_svg_stop_color_t *SkSVGStopColor_new(uint32_t color) {
    return to_opaque<reskia_svg_stop_color_t>(new SkSVGStopColor(static_cast<SkColor>(color)));
}

reskia_svg_stop_color_t *SkSVGStopColor_newWithType(int32_t type) {
    return to_opaque<reskia_svg_stop_color_t>(new SkSVGStopColor(svg_stop_color_type(type)));
}

void SkSVGStopColor_delete(reskia_svg_stop_color_t *color) {
    delete as_type<SkSVGStopColor>(color);
}

int32_t SkSVGStopColor_type(const reskia_svg_stop_color_t *color) {
    return color != nullptr ? static_cast<int32_t>(as_type<SkSVGStopColor>(color)->type()) : -1;
}

bool SkSVGStopColor_color(const reskia_svg_stop_color_t *color, uint32_t *out_color) {
    if (color == nullptr || out_color == nullptr ||
        as_type<SkSVGStopColor>(color)->type() != SkSVGStopColor::Type::kColor) {
        return false;
    }
    *out_color = as_type<SkSVGStopColor>(color)->color();
    return true;
}

reskia_svg_object_bounding_box_units_t *SkSVGObjectBoundingBoxUnits_new(int32_t type) {
    return to_opaque<reskia_svg_object_bounding_box_units_t>(
            new SkSVGObjectBoundingBoxUnits(svg_object_bounding_box_units_type(type)));
}

void SkSVGObjectBoundingBoxUnits_delete(reskia_svg_object_bounding_box_units_t *units) {
    delete as_type<SkSVGObjectBoundingBoxUnits>(units);
}

int32_t SkSVGObjectBoundingBoxUnits_type(const reskia_svg_object_bounding_box_units_t *units) {
    return units != nullptr ? static_cast<int32_t>(as_type<SkSVGObjectBoundingBoxUnits>(units)->type()) : -1;
}

reskia_svg_font_family_t *SkSVGFontFamily_new(const char family[]) {
    return family != nullptr ? to_opaque<reskia_svg_font_family_t>(new SkSVGFontFamily(family)) : nullptr;
}

reskia_svg_font_family_t *SkSVGFontFamily_newInherit(void) {
    return to_opaque<reskia_svg_font_family_t>(new SkSVGFontFamily());
}

void SkSVGFontFamily_delete(reskia_svg_font_family_t *family) {
    delete as_type<SkSVGFontFamily>(family);
}

int32_t SkSVGFontFamily_type(const reskia_svg_font_family_t *family) {
    return family != nullptr ? static_cast<int32_t>(as_type<SkSVGFontFamily>(family)->type()) : -1;
}

reskia_string_t *SkSVGFontFamily_family(const reskia_svg_font_family_t *family) {
    return family != nullptr ? make_string(as_type<SkSVGFontFamily>(family)->family()) : nullptr;
}

bool SkSVGFontFamily_equals(const reskia_svg_font_family_t *family, const reskia_svg_font_family_t *other) {
    return family != nullptr && other != nullptr && *as_type<SkSVGFontFamily>(family) == *as_type<SkSVGFontFamily>(other);
}

bool SkSVGFontFamily_notEquals(const reskia_svg_font_family_t *family, const reskia_svg_font_family_t *other) {
    return family == nullptr || other == nullptr || *as_type<SkSVGFontFamily>(family) != *as_type<SkSVGFontFamily>(other);
}

reskia_svg_font_size_t *SkSVGFontSize_new(const reskia_svg_length_t *length) {
    return length != nullptr ? to_opaque<reskia_svg_font_size_t>(new SkSVGFontSize(*as_type<SkSVGLength>(length))) : nullptr;
}

reskia_svg_font_size_t *SkSVGFontSize_newInherit(void) {
    return to_opaque<reskia_svg_font_size_t>(new SkSVGFontSize());
}

void SkSVGFontSize_delete(reskia_svg_font_size_t *size) {
    delete as_type<SkSVGFontSize>(size);
}

int32_t SkSVGFontSize_type(const reskia_svg_font_size_t *size) {
    return size != nullptr ? static_cast<int32_t>(as_type<SkSVGFontSize>(size)->type()) : -1;
}

reskia_svg_length_t *SkSVGFontSize_size(const reskia_svg_font_size_t *size) {
    return size != nullptr ? to_opaque<reskia_svg_length_t>(new SkSVGLength(as_type<SkSVGFontSize>(size)->size())) : nullptr;
}

bool SkSVGFontSize_equals(const reskia_svg_font_size_t *size, const reskia_svg_font_size_t *other) {
    return size != nullptr && other != nullptr && *as_type<SkSVGFontSize>(size) == *as_type<SkSVGFontSize>(other);
}

bool SkSVGFontSize_notEquals(const reskia_svg_font_size_t *size, const reskia_svg_font_size_t *other) {
    return size == nullptr || other == nullptr || *as_type<SkSVGFontSize>(size) != *as_type<SkSVGFontSize>(other);
}

reskia_svg_font_style_t *SkSVGFontStyle_new(int32_t type) {
    return to_opaque<reskia_svg_font_style_t>(new SkSVGFontStyle(svg_font_style_type(type)));
}

void SkSVGFontStyle_delete(reskia_svg_font_style_t *style) {
    delete as_type<SkSVGFontStyle>(style);
}

int32_t SkSVGFontStyle_type(const reskia_svg_font_style_t *style) {
    return style != nullptr ? static_cast<int32_t>(as_type<SkSVGFontStyle>(style)->type()) : -1;
}

bool SkSVGFontStyle_equals(const reskia_svg_font_style_t *style, const reskia_svg_font_style_t *other) {
    return style != nullptr && other != nullptr && *as_type<SkSVGFontStyle>(style) == *as_type<SkSVGFontStyle>(other);
}

bool SkSVGFontStyle_notEquals(const reskia_svg_font_style_t *style, const reskia_svg_font_style_t *other) {
    return style == nullptr || other == nullptr || *as_type<SkSVGFontStyle>(style) != *as_type<SkSVGFontStyle>(other);
}

reskia_svg_font_weight_t *SkSVGFontWeight_new(int32_t type) {
    return to_opaque<reskia_svg_font_weight_t>(new SkSVGFontWeight(svg_font_weight_type(type)));
}

void SkSVGFontWeight_delete(reskia_svg_font_weight_t *weight) {
    delete as_type<SkSVGFontWeight>(weight);
}

int32_t SkSVGFontWeight_type(const reskia_svg_font_weight_t *weight) {
    return weight != nullptr ? static_cast<int32_t>(as_type<SkSVGFontWeight>(weight)->type()) : -1;
}

bool SkSVGFontWeight_equals(const reskia_svg_font_weight_t *weight, const reskia_svg_font_weight_t *other) {
    return weight != nullptr && other != nullptr && *as_type<SkSVGFontWeight>(weight) == *as_type<SkSVGFontWeight>(other);
}

bool SkSVGFontWeight_notEquals(const reskia_svg_font_weight_t *weight, const reskia_svg_font_weight_t *other) {
    return weight == nullptr || other == nullptr || *as_type<SkSVGFontWeight>(weight) != *as_type<SkSVGFontWeight>(other);
}

reskia_svg_func_iri_t *SkSVGFuncIRI_newWithType(int32_t type) {
    return to_opaque<reskia_svg_func_iri_t>(new SkSVGFuncIRI(svg_func_iri_type(type)));
}

reskia_svg_func_iri_t *SkSVGFuncIRI_newWithIRI(int32_t iri_type, const char iri[]) {
    return iri != nullptr ? to_opaque<reskia_svg_func_iri_t>(
            new SkSVGFuncIRI(SkSVGIRI(svg_iri_type(iri_type), SkString(iri)))) : nullptr;
}

void SkSVGFuncIRI_delete(reskia_svg_func_iri_t *func_iri) {
    delete as_type<SkSVGFuncIRI>(func_iri);
}

int32_t SkSVGFuncIRI_type(const reskia_svg_func_iri_t *func_iri) {
    return func_iri != nullptr ? static_cast<int32_t>(as_type<SkSVGFuncIRI>(func_iri)->type()) : -1;
}

reskia_string_t *SkSVGFuncIRI_iri(const reskia_svg_func_iri_t *func_iri) {
    if (func_iri == nullptr || as_type<SkSVGFuncIRI>(func_iri)->type() != SkSVGFuncIRI::Type::kIRI) {
        return nullptr;
    }
    return make_string(as_type<SkSVGFuncIRI>(func_iri)->iri().iri());
}

bool SkSVGFuncIRI_equals(const reskia_svg_func_iri_t *func_iri, const reskia_svg_func_iri_t *other) {
    return func_iri != nullptr && other != nullptr && *as_type<SkSVGFuncIRI>(func_iri) == *as_type<SkSVGFuncIRI>(other);
}

bool SkSVGFuncIRI_notEquals(const reskia_svg_func_iri_t *func_iri, const reskia_svg_func_iri_t *other) {
    return func_iri == nullptr || other == nullptr || *as_type<SkSVGFuncIRI>(func_iri) != *as_type<SkSVGFuncIRI>(other);
}

reskia_svg_text_anchor_t *SkSVGTextAnchor_new(int32_t type) {
    return to_opaque<reskia_svg_text_anchor_t>(new SkSVGTextAnchor(svg_text_anchor_type(type)));
}

void SkSVGTextAnchor_delete(reskia_svg_text_anchor_t *anchor) {
    delete as_type<SkSVGTextAnchor>(anchor);
}

int32_t SkSVGTextAnchor_type(const reskia_svg_text_anchor_t *anchor) {
    return anchor != nullptr ? static_cast<int32_t>(as_type<SkSVGTextAnchor>(anchor)->type()) : -1;
}

}
