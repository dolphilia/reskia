//
// Created by Codex on 2026/05/14.
//

#ifndef RAIA_SKIA_SK_SVG_NODE_H
#define RAIA_SKIA_SK_SVG_NODE_H

#include <stdbool.h>
#include <stdint.h>

typedef struct reskia_svg_node_t reskia_svg_node_t;
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
