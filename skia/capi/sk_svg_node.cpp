//
// Created by Codex on 2026/05/14.
//

#include "sk_svg_node.h"

#include "modules/svg/include/SkSVGNode.h"

extern "C" {

int32_t SkSVGNode_tag(reskia_svg_node_t *node) {
    if (node == nullptr) {
        return -1;
    }
    return static_cast<int32_t>(reinterpret_cast<SkSVGNode *>(node)->tag());
}

bool SkSVGNode_setAttributeString(reskia_svg_node_t *node, const char *attribute_name, const char *attribute_value) {
    if (node == nullptr || attribute_name == nullptr || attribute_value == nullptr) {
        return false;
    }
    return reinterpret_cast<SkSVGNode *>(node)->setAttribute(attribute_name, attribute_value);
}

}
