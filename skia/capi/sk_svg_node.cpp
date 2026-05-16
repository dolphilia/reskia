//
// Created by Codex on 2026/05/14.
//

#include "sk_svg_node.h"

#include <utility>

#include "include/core/SkColor.h"
#include "include/core/SkString.h"
#include "modules/svg/include/SkSVGAttribute.h"
#include "modules/svg/include/SkSVGNode.h"
#include "modules/svg/include/SkSVGTypes.h"
#include "modules/svg/include/SkSVGValue.h"

namespace {

enum class ReskiaSVGValueKind {
    kColor,
    kLength,
    kNumber,
    kString,
};

struct ReskiaSVGValue {
    explicit ReskiaSVGValue(SkColor color_in)
        : kind(ReskiaSVGValueKind::kColor)
        , color(color_in) {}

    explicit ReskiaSVGValue(SkSVGLength length_in)
        : kind(ReskiaSVGValueKind::kLength)
        , length(length_in) {}

    explicit ReskiaSVGValue(SkScalar number_in)
        : kind(ReskiaSVGValueKind::kNumber)
        , number(number_in) {}

    explicit ReskiaSVGValue(SkString string_in)
        : kind(ReskiaSVGValueKind::kString)
        , string(std::move(string_in)) {}

    ReskiaSVGValueKind kind;
    SkColor color = SK_ColorBLACK;
    SkSVGLength length;
    SkScalar number = 0.0f;
    SkString string;
};

SkSVGLength::Unit svg_length_unit(int32_t unit) {
    if (unit < static_cast<int32_t>(SkSVGLength::Unit::kUnknown) ||
        unit > static_cast<int32_t>(SkSVGLength::Unit::kPC)) {
        return SkSVGLength::Unit::kUnknown;
    }
    return static_cast<SkSVGLength::Unit>(unit);
}

SkSVGAttribute svg_attribute(int32_t attribute) {
    if (attribute < static_cast<int32_t>(SkSVGAttribute::kClipRule) ||
        attribute >= static_cast<int32_t>(SkSVGAttribute::kUnknown)) {
        return SkSVGAttribute::kUnknown;
    }
    return static_cast<SkSVGAttribute>(attribute);
}

const ReskiaSVGValue *as_svg_value(const reskia_svg_value_t *value) {
    return reinterpret_cast<const ReskiaSVGValue *>(value);
}

}  // namespace

extern "C" {

int32_t SkSVGNode_tag(reskia_svg_node_t *node) {
    if (node == nullptr) {
        return -1;
    }
    return static_cast<int32_t>(reinterpret_cast<SkSVGNode *>(node)->tag());
}

reskia_svg_value_t *SkSVGValue_newColor(uint32_t color) {
    return reinterpret_cast<reskia_svg_value_t *>(new ReskiaSVGValue(static_cast<SkColor>(color)));
}

reskia_svg_value_t *SkSVGValue_newLength(float value, int32_t unit) {
    return reinterpret_cast<reskia_svg_value_t *>(new ReskiaSVGValue(SkSVGLength(value, svg_length_unit(unit))));
}

reskia_svg_value_t *SkSVGValue_newNumber(float value) {
    return reinterpret_cast<reskia_svg_value_t *>(new ReskiaSVGValue(value));
}

reskia_svg_value_t *SkSVGValue_newString(const char *value) {
    return value != nullptr ? reinterpret_cast<reskia_svg_value_t *>(new ReskiaSVGValue(SkString(value))) : nullptr;
}

void SkSVGValue_delete(reskia_svg_value_t *value) {
    delete reinterpret_cast<ReskiaSVGValue *>(value);
}

int32_t SkSVGValue_type(const reskia_svg_value_t *value) {
    if (value == nullptr) {
        return -1;
    }
    switch (as_svg_value(value)->kind) {
        case ReskiaSVGValueKind::kColor:
            return static_cast<int32_t>(SkSVGValue::Type::kColor);
        case ReskiaSVGValueKind::kLength:
            return static_cast<int32_t>(SkSVGValue::Type::kLength);
        case ReskiaSVGValueKind::kNumber:
            return static_cast<int32_t>(SkSVGValue::Type::kNumber);
        case ReskiaSVGValueKind::kString:
            return static_cast<int32_t>(SkSVGValue::Type::kString);
    }
    return -1;
}

bool SkSVGNode_setAttribute(reskia_svg_node_t *node, int32_t attribute, const reskia_svg_value_t *value) {
    SkSVGAttribute attr = svg_attribute(attribute);
    if (node == nullptr || value == nullptr || attr == SkSVGAttribute::kUnknown) {
        return false;
    }
    auto *svg_node = reinterpret_cast<SkSVGNode *>(node);
    const ReskiaSVGValue *svg_value = as_svg_value(value);
    switch (svg_value->kind) {
        case ReskiaSVGValueKind::kColor: {
            SkSVGColorValue wrapped(svg_value->color);
            svg_node->setAttribute(attr, wrapped);
            return true;
        }
        case ReskiaSVGValueKind::kLength: {
            SkSVGLengthValue wrapped(svg_value->length);
            svg_node->setAttribute(attr, wrapped);
            return true;
        }
        case ReskiaSVGValueKind::kNumber: {
            SkSVGNumberValue wrapped(svg_value->number);
            svg_node->setAttribute(attr, wrapped);
            return true;
        }
        case ReskiaSVGValueKind::kString: {
            SkSVGStringValue wrapped(svg_value->string);
            svg_node->setAttribute(attr, wrapped);
            return true;
        }
    }
    return false;
}

bool SkSVGNode_setAttributeString(reskia_svg_node_t *node, const char *attribute_name, const char *attribute_value) {
    if (node == nullptr || attribute_name == nullptr || attribute_value == nullptr) {
        return false;
    }
    return reinterpret_cast<SkSVGNode *>(node)->setAttribute(attribute_name, attribute_value);
}

}
