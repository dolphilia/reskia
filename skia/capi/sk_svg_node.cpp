//
// Created by Codex on 2026/05/14.
//

#include "sk_svg_node.h"

#include <utility>

#include "include/core/SkColor.h"
#include "include/core/SkImage.h"
#include "include/core/SkMatrix.h"
#include "include/core/SkString.h"
#include "modules/svg/include/SkSVGAttribute.h"
#include "modules/svg/include/SkSVGCircle.h"
#include "modules/svg/include/SkSVGClipPath.h"
#include "modules/svg/include/SkSVGDefs.h"
#include "modules/svg/include/SkSVGEllipse.h"
#include "modules/svg/include/SkSVGFeBlend.h"
#include "modules/svg/include/SkSVGFeColorMatrix.h"
#include "modules/svg/include/SkSVGFeComposite.h"
#include "modules/svg/include/SkSVGFeDisplacementMap.h"
#include "modules/svg/include/SkSVGFe.h"
#include "modules/svg/include/SkSVGFeFlood.h"
#include "modules/svg/include/SkSVGFeGaussianBlur.h"
#include "modules/svg/include/SkSVGFeImage.h"
#include "modules/svg/include/SkSVGFeLightSource.h"
#include "modules/svg/include/SkSVGFeLighting.h"
#include "modules/svg/include/SkSVGFeMorphology.h"
#include "modules/svg/include/SkSVGFeOffset.h"
#include "modules/svg/include/SkSVGFeTurbulence.h"
#include "modules/svg/include/SkSVGFilter.h"
#include "modules/svg/include/SkSVGG.h"
#include "modules/svg/include/SkSVGImage.h"
#include "modules/svg/include/SkSVGLine.h"
#include "modules/svg/include/SkSVGLinearGradient.h"
#include "modules/svg/include/SkSVGMask.h"
#include "modules/svg/include/SkSVGNode.h"
#include "modules/svg/include/SkSVGPath.h"
#include "modules/svg/include/SkSVGPattern.h"
#include "modules/svg/include/SkSVGPoly.h"
#include "modules/svg/include/SkSVGRadialGradient.h"
#include "modules/svg/include/SkSVGRect.h"
#include "modules/svg/include/SkSVGSVG.h"
#include "modules/svg/include/SkSVGStop.h"
#include "modules/svg/include/SkSVGText.h"
#include "modules/svg/include/SkSVGTypes.h"
#include "modules/svg/include/SkSVGUse.h"
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

template <typename T>
reskia_svg_node_t *to_svg_node(sk_sp<T> node) {
    return reinterpret_cast<reskia_svg_node_t *>(static_cast<SkSVGNode *>(node.release()));
}

SkSVGSVG::Type svg_svg_type(int32_t type) {
    if (type < static_cast<int32_t>(SkSVGSVG::Type::kRoot) ||
        type > static_cast<int32_t>(SkSVGSVG::Type::kInner)) {
        return SkSVGSVG::Type::kInner;
    }
    return static_cast<SkSVGSVG::Type>(type);
}

}  // namespace

extern "C" {

int32_t SkSVGNode_tag(reskia_svg_node_t *node) {
    if (node == nullptr) {
        return -1;
    }
    return static_cast<int32_t>(reinterpret_cast<SkSVGNode *>(node)->tag());
}

void SkSVGNode_ref(reskia_svg_node_t *node) {
    if (node != nullptr) {
        reinterpret_cast<SkSVGNode *>(node)->ref();
    }
}

void SkSVGNode_unref(reskia_svg_node_t *node) {
    if (node != nullptr) {
        reinterpret_cast<SkSVGNode *>(node)->unref();
    }
}

void SkSVGNode_release(reskia_svg_node_t *node) {
    SkSVGNode_unref(node);
}

bool SkSVGNode_appendChild(reskia_svg_node_t *parent, const reskia_svg_node_t *child) {
    if (parent == nullptr || child == nullptr) {
        return false;
    }
    reinterpret_cast<SkSVGNode *>(parent)->appendChild(
            sk_ref_sp(const_cast<SkSVGNode *>(reinterpret_cast<const SkSVGNode *>(child))));
    return true;
}

bool SkSVGTransformableNode_setTransform(reskia_svg_node_t *node, const reskia_matrix_t *matrix) {
    if (node == nullptr || matrix == nullptr) {
        return false;
    }
    reinterpret_cast<SkSVGTransformableNode *>(node)->setTransform(*reinterpret_cast<const SkMatrix *>(matrix));
    return true;
}

reskia_svg_presentation_attributes_t *SkSVGPresentationAttributes_MakeInitial(void) {
    return reinterpret_cast<reskia_svg_presentation_attributes_t *>(
            new SkSVGPresentationAttributes(SkSVGPresentationAttributes::MakeInitial()));
}

void SkSVGPresentationAttributes_delete(reskia_svg_presentation_attributes_t *attributes) {
    delete reinterpret_cast<SkSVGPresentationAttributes *>(attributes);
}

reskia_svg_node_t *SkSVGCircle_Make(void) {
    return to_svg_node(SkSVGCircle::Make());
}

reskia_svg_node_t *SkSVGClipPath_Make(void) {
    return to_svg_node(SkSVGClipPath::Make());
}

reskia_svg_node_t *SkSVGDefs_Make(void) {
    return to_svg_node(SkSVGDefs::Make());
}

reskia_svg_node_t *SkSVGEllipse_Make(void) {
    return to_svg_node(SkSVGEllipse::Make());
}

reskia_svg_node_t *SkSVGFeBlend_Make(void) {
    return to_svg_node(SkSVGFeBlend::Make());
}

bool SkSVGFe_IsFilterEffect(const reskia_svg_node_t *node) {
    return node != nullptr && SkSVGFe::IsFilterEffect(sk_ref_sp(const_cast<SkSVGNode *>(reinterpret_cast<const SkSVGNode *>(node))));
}

reskia_svg_node_t *SkSVGFeColorMatrix_Make(void) {
    return to_svg_node(SkSVGFeColorMatrix::Make());
}

reskia_svg_node_t *SkSVGFeComposite_Make(void) {
    return to_svg_node(SkSVGFeComposite::Make());
}

reskia_svg_node_t *SkSVGFeDiffuseLighting_Make(void) {
    return to_svg_node(SkSVGFeDiffuseLighting::Make());
}

reskia_svg_node_t *SkSVGFeDisplacementMap_Make(void) {
    return to_svg_node(SkSVGFeDisplacementMap::Make());
}

reskia_svg_node_t *SkSVGFeDistantLight_Make(void) {
    return to_svg_node(SkSVGFeDistantLight::Make());
}

reskia_svg_node_t *SkSVGFeFlood_Make(void) {
    return to_svg_node(SkSVGFeFlood::Make());
}

reskia_svg_node_t *SkSVGFeGaussianBlur_Make(void) {
    return to_svg_node(SkSVGFeGaussianBlur::Make());
}

reskia_svg_node_t *SkSVGFeImage_Make(void) {
    return to_svg_node(SkSVGFeImage::Make());
}

reskia_svg_node_t *SkSVGFeMorphology_Make(void) {
    return to_svg_node(SkSVGFeMorphology::Make());
}

reskia_svg_node_t *SkSVGFeOffset_Make(void) {
    return to_svg_node(SkSVGFeOffset::Make());
}

reskia_svg_node_t *SkSVGFePointLight_Make(void) {
    return to_svg_node(SkSVGFePointLight::Make());
}

reskia_svg_node_t *SkSVGFeSpecularLighting_Make(void) {
    return to_svg_node(SkSVGFeSpecularLighting::Make());
}

reskia_svg_node_t *SkSVGFeSpotLight_Make(void) {
    return to_svg_node(SkSVGFeSpotLight::Make());
}

reskia_svg_node_t *SkSVGFeTurbulence_Make(void) {
    return to_svg_node(SkSVGFeTurbulence::Make());
}

reskia_svg_node_t *SkSVGFilter_Make(void) {
    return to_svg_node(SkSVGFilter::Make());
}

reskia_svg_node_t *SkSVGG_Make(void) {
    return to_svg_node(SkSVGG::Make());
}

reskia_svg_node_t *SkSVGImage_Make(void) {
    return to_svg_node(SkSVGImage::Make());
}

reskia_svg_node_t *SkSVGLine_Make(void) {
    return to_svg_node(SkSVGLine::Make());
}

reskia_svg_node_t *SkSVGLinearGradient_Make(void) {
    return to_svg_node(SkSVGLinearGradient::Make());
}

reskia_svg_node_t *SkSVGMask_Make(void) {
    return to_svg_node(SkSVGMask::Make());
}

reskia_svg_node_t *SkSVGPath_Make(void) {
    return to_svg_node(SkSVGPath::Make());
}

reskia_svg_node_t *SkSVGPattern_Make(void) {
    return to_svg_node(SkSVGPattern::Make());
}

reskia_svg_node_t *SkSVGPoly_MakePolygon(void) {
    return to_svg_node(SkSVGPoly::MakePolygon());
}

reskia_svg_node_t *SkSVGPoly_MakePolyline(void) {
    return to_svg_node(SkSVGPoly::MakePolyline());
}

reskia_svg_node_t *SkSVGRadialGradient_Make(void) {
    return to_svg_node(SkSVGRadialGradient::Make());
}

reskia_svg_node_t *SkSVGRect_Make(void) {
    return to_svg_node(SkSVGRect::Make());
}

reskia_svg_node_t *SkSVGSVG_Make(int32_t type) {
    return to_svg_node(SkSVGSVG::Make(svg_svg_type(type)));
}

reskia_svg_node_t *SkSVGStop_Make(void) {
    return to_svg_node(SkSVGStop::Make());
}

reskia_svg_node_t *SkSVGText_Make(void) {
    return to_svg_node(SkSVGText::Make());
}

reskia_svg_node_t *SkSVGTextLiteral_Make(void) {
    return to_svg_node(SkSVGTextLiteral::Make());
}

reskia_svg_node_t *SkSVGTextPath_Make(void) {
    return to_svg_node(SkSVGTextPath::Make());
}

reskia_svg_node_t *SkSVGTSpan_Make(void) {
    return to_svg_node(SkSVGTSpan::Make());
}

reskia_svg_node_t *SkSVGUse_Make(void) {
    return to_svg_node(SkSVGUse::Make());
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
