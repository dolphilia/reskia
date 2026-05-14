//
// Created by Codex on 2026/05/14.
//

#ifndef RAIA_SKIA_SK_SVG_NODE_H
#define RAIA_SKIA_SK_SVG_NODE_H

#include <stdbool.h>
#include <stdint.h>

typedef struct reskia_svg_node_t reskia_svg_node_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * node: borrowed from SkSVGDOM.
 * Returns -1 for NULL input.
 * Skia: SkSVGNode::tag() const.
 */
int32_t SkSVGNode_tag(reskia_svg_node_t *node);

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
