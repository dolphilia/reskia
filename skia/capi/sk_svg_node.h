//
// Created by Codex on 2026/05/14.
//

#ifndef RAIA_SKIA_SK_SVG_NODE_H
#define RAIA_SKIA_SK_SVG_NODE_H

#include <stdbool.h>
#include <stdint.h>

typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_svg_node_t reskia_svg_node_t;
typedef struct reskia_svg_presentation_attributes_t reskia_svg_presentation_attributes_t;
typedef struct reskia_svg_value_t reskia_svg_value_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * node: borrowed from SkSVGDOM.
 * Returns -1 for NULL input.
 * Skia: SkSVGNode::tag() const.
 */
int32_t SkSVGNode_tag(reskia_svg_node_t *node);
void SkSVGNode_ref(reskia_svg_node_t *node);
void SkSVGNode_unref(reskia_svg_node_t *node);
void SkSVGNode_release(reskia_svg_node_t *node);
bool SkSVGNode_appendChild(reskia_svg_node_t *parent, const reskia_svg_node_t *child);
bool SkSVGTransformableNode_setTransform(reskia_svg_node_t *node, const reskia_matrix_t *matrix);

reskia_svg_presentation_attributes_t *SkSVGPresentationAttributes_MakeInitial(void);
void SkSVGPresentationAttributes_delete(reskia_svg_presentation_attributes_t *attributes);

reskia_svg_node_t *SkSVGCircle_Make(void);
reskia_svg_node_t *SkSVGClipPath_Make(void);
reskia_svg_node_t *SkSVGDefs_Make(void);
reskia_svg_node_t *SkSVGEllipse_Make(void);
reskia_svg_node_t *SkSVGFeBlend_Make(void);
bool SkSVGFe_IsFilterEffect(const reskia_svg_node_t *node);
reskia_svg_node_t *SkSVGFeColorMatrix_Make(void);
reskia_svg_node_t *SkSVGFeComposite_Make(void);
reskia_svg_node_t *SkSVGFeDiffuseLighting_Make(void);
reskia_svg_node_t *SkSVGFeDisplacementMap_Make(void);
reskia_svg_node_t *SkSVGFeDistantLight_Make(void);
reskia_svg_node_t *SkSVGFeFlood_Make(void);
reskia_svg_node_t *SkSVGFeGaussianBlur_Make(void);
reskia_svg_node_t *SkSVGFeImage_Make(void);
reskia_svg_node_t *SkSVGFeMorphology_Make(void);
reskia_svg_node_t *SkSVGFeOffset_Make(void);
reskia_svg_node_t *SkSVGFePointLight_Make(void);
reskia_svg_node_t *SkSVGFeSpecularLighting_Make(void);
reskia_svg_node_t *SkSVGFeSpotLight_Make(void);
reskia_svg_node_t *SkSVGFeTurbulence_Make(void);
reskia_svg_node_t *SkSVGFilter_Make(void);
reskia_svg_node_t *SkSVGG_Make(void);
reskia_svg_node_t *SkSVGImage_Make(void);
reskia_svg_node_t *SkSVGLine_Make(void);
reskia_svg_node_t *SkSVGLinearGradient_Make(void);
reskia_svg_node_t *SkSVGMask_Make(void);
reskia_svg_node_t *SkSVGPath_Make(void);
reskia_svg_node_t *SkSVGPattern_Make(void);
reskia_svg_node_t *SkSVGPoly_MakePolygon(void);
reskia_svg_node_t *SkSVGPoly_MakePolyline(void);
reskia_svg_node_t *SkSVGRadialGradient_Make(void);
reskia_svg_node_t *SkSVGRect_Make(void);
reskia_svg_node_t *SkSVGSVG_Make(int32_t type);
reskia_svg_node_t *SkSVGStop_Make(void);
reskia_svg_node_t *SkSVGText_Make(void);
reskia_svg_node_t *SkSVGTextLiteral_Make(void);
reskia_svg_node_t *SkSVGTextPath_Make(void);
reskia_svg_node_t *SkSVGTSpan_Make(void);
reskia_svg_node_t *SkSVGUse_Make(void);

reskia_svg_value_t *SkSVGValue_newColor(uint32_t color); // owned; delete with SkSVGValue_delete
reskia_svg_value_t *SkSVGValue_newLength(float value, int32_t unit); // owned; delete with SkSVGValue_delete
reskia_svg_value_t *SkSVGValue_newNumber(float value); // owned; delete with SkSVGValue_delete
reskia_svg_value_t *SkSVGValue_newString(const char *value); // owned; NULL input returns NULL
void SkSVGValue_delete(reskia_svg_value_t *value); // NULL input is no-op
int32_t SkSVGValue_type(const reskia_svg_value_t *value); // NULL input returns -1

/**
 * node: borrowed from SkSVGDOM.
 * attribute: SkSVGAttribute integer value.
 * value: owned/borrowed reskia_svg_value_t; not consumed.
 * Returns false for NULL input or invalid attribute.
 * Skia: SkSVGNode::setAttribute(SkSVGAttribute, const SkSVGValue&).
 */
bool SkSVGNode_setAttribute(reskia_svg_node_t *node, int32_t attribute, const reskia_svg_value_t *value);

/**
 * node: borrowed from SkSVGDOM.
 * attribute_name/attribute_value: non-null C strings.
 * Returns false for NULL input or parse failure.
 * Skia: SkSVGNode::setAttribute(const char*, const char*).
 */
bool SkSVGNode_setAttributeString(reskia_svg_node_t *node, const char *attribute_name, const char *attribute_value);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_SVG_NODE_H
