#include <cstddef>
#include <cstdio>
#include <cstring>

#include "capi/sk_canvas.h"
#include "capi/sk_memory_stream.h"
#include "capi/sk_stream.h"
#include "capi/sk_svg_dom.h"
#include "capi/sk_svg_node.h"

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[svg-dom-capi-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool smoke_svg_dom() {
    float width = -1.0f;
    float height = -1.0f;
    SkSVGDOM_ref(nullptr);
    SkSVGDOM_unref(nullptr);
    SkSVGDOM_release(nullptr);
    SkSVGDOM_setContainerSize(nullptr, 10.0f, 20.0f);
    SkSVGDOM_render(nullptr, nullptr);
    SkSVGPresentationContext_delete(nullptr);
    if (!check(SkSVGDOM_MakeFromStream(nullptr) == nullptr &&
               SkSVGPresentationContext_copy(nullptr) == nullptr &&
               SkSVGDOM_getRoot(nullptr) == nullptr &&
               SkSVGDOM_findNodeById(nullptr, "rect1") == nullptr &&
               !SkSVGDOM_containerSize(nullptr, &width, &height) &&
               width == 0.0f &&
               height == 0.0f,
               "SkSVGDOM null input helpers")) {
        return false;
    }

    const char svg[] =
            "<svg xmlns='http://www.w3.org/2000/svg' width='64' height='32'>"
            "<rect id='rect1' x='4' y='5' width='12' height='10' fill='red'/>"
            "</svg>";
    reskia_memory_stream_t *stream = SkMemoryStream_newWithDataAndCopyFlag(
            reinterpret_cast<const uint8_t *>(svg), std::strlen(svg), true);
    if (!check(stream != nullptr, "SkMemoryStream_newWithDataAndCopyFlag")) {
        return false;
    }

    reskia_svg_dom_t *dom = SkSVGDOM_MakeFromStream(reinterpret_cast<reskia_stream_t *>(stream));
    SkMemoryStream_delete(stream);
    if (!check(dom != nullptr, "SkSVGDOM_MakeFromStream(valid svg)")) {
        return false;
    }
    if (!check(SkSVGDOM_getRoot(dom) != nullptr, "SkSVGDOM_getRoot(valid svg)") ||
        !check(SkSVGDOM_findNodeById(dom, "rect1") != nullptr, "SkSVGDOM_findNodeById(existing)") ||
        !check(SkSVGDOM_findNodeById(dom, "missing") == nullptr, "SkSVGDOM_findNodeById(missing)")) {
        SkSVGDOM_release(dom);
        return false;
    }
    reskia_svg_node_t *rect = SkSVGDOM_findNodeById(dom, "rect1");
    if (!check(SkSVGNode_tag(nullptr) == -1, "SkSVGNode_tag(null)") ||
        !check(SkSVGNode_tag(rect) >= 0, "SkSVGNode_tag(rect)")) {
        SkSVGDOM_release(dom);
        return false;
    }
    SkSVGValue_delete(nullptr);
    reskia_svg_value_t *width_value = SkSVGValue_newLength(24.0f, 1);
    reskia_svg_value_t *opacity_value = SkSVGValue_newNumber(0.5f);
    reskia_svg_value_t *text_value = SkSVGValue_newString("label");
    reskia_svg_value_t *color_value = SkSVGValue_newColor(0xFF0000FFu);
    if (!check(width_value != nullptr &&
               opacity_value != nullptr &&
               text_value != nullptr &&
               color_value != nullptr &&
               SkSVGValue_newString(nullptr) == nullptr &&
               SkSVGValue_type(nullptr) == -1 &&
               SkSVGValue_type(width_value) == 2 &&
               SkSVGValue_type(opacity_value) == 3 &&
               SkSVGValue_type(text_value) == 7 &&
               SkSVGValue_type(color_value) == 0,
               "SkSVGValue lifecycle")) {
        SkSVGValue_delete(color_value);
        SkSVGValue_delete(text_value);
        SkSVGValue_delete(opacity_value);
        SkSVGValue_delete(width_value);
        SkSVGDOM_release(dom);
        return false;
    }
    if (!check(!SkSVGNode_setAttribute(nullptr, 41, width_value), "SkSVGNode_setAttribute(null node)") ||
        !check(!SkSVGNode_setAttribute(rect, -1, width_value), "SkSVGNode_setAttribute(invalid attr)") ||
        !check(!SkSVGNode_setAttribute(rect, 41, nullptr), "SkSVGNode_setAttribute(null value)") ||
        !check(SkSVGNode_setAttribute(rect, 41, width_value), "SkSVGNode_setAttribute(width length)") ||
        !check(SkSVGNode_setAttribute(rect, 21, opacity_value), "SkSVGNode_setAttribute(opacity number)") ||
        !check(SkSVGNode_setAttribute(rect, 20, text_value), "SkSVGNode_setAttribute(href string)") ||
        !check(SkSVGNode_setAttribute(rect, 1, color_value), "SkSVGNode_setAttribute(color value)")) {
        SkSVGValue_delete(color_value);
        SkSVGValue_delete(text_value);
        SkSVGValue_delete(opacity_value);
        SkSVGValue_delete(width_value);
        SkSVGDOM_release(dom);
        return false;
    }
    SkSVGValue_delete(color_value);
    SkSVGValue_delete(text_value);
    SkSVGValue_delete(opacity_value);
    SkSVGValue_delete(width_value);
    if (!check(!SkSVGNode_setAttributeString(nullptr, "fill", "blue"), "SkSVGNode_setAttributeString(null node)") ||
        !check(!SkSVGNode_setAttributeString(rect, nullptr, "blue"), "SkSVGNode_setAttributeString(null name)") ||
        !check(!SkSVGNode_setAttributeString(rect, "fill", nullptr), "SkSVGNode_setAttributeString(null value)") ||
        !check(SkSVGNode_setAttributeString(rect, "fill", "blue"), "SkSVGNode_setAttributeString(fill)")) {
        SkSVGDOM_release(dom);
        return false;
    }

    SkSVGDOM_setContainerSize(dom, 128.0f, 64.0f);
    if (!check(SkSVGDOM_containerSize(dom, &width, &height) &&
               width == 128.0f &&
               height == 64.0f,
               "SkSVGDOM_containerSize(after set)")) {
        SkSVGDOM_release(dom);
        return false;
    }

    reskia_canvas_t *canvas = SkCanvas_newWithSizeProps(128, 64, nullptr);
    if (!check(canvas != nullptr, "SkCanvas_newWithSizeProps")) {
        SkSVGDOM_release(dom);
        return false;
    }
    SkSVGDOM_render(dom, canvas);
    reskia_svg_presentation_context_t *presentation_context = SkSVGPresentationContext_new();
    if (!check(presentation_context != nullptr, "SkSVGPresentationContext_new")) {
        SkCanvas_delete(canvas);
        SkSVGDOM_release(dom);
        return false;
    }
    reskia_svg_presentation_context_t *presentation_context_copy = SkSVGPresentationContext_copy(presentation_context);
    if (!check(presentation_context_copy != nullptr, "SkSVGPresentationContext_copy")) {
        SkSVGPresentationContext_delete(presentation_context);
        SkCanvas_delete(canvas);
        SkSVGDOM_release(dom);
        return false;
    }
    SkSVGDOM_renderNode(nullptr, canvas, presentation_context, "rect1");
    SkSVGDOM_renderNode(dom, nullptr, presentation_context, "rect1");
    SkSVGDOM_renderNode(dom, canvas, nullptr, "rect1");
    SkSVGDOM_renderNode(dom, canvas, presentation_context, nullptr);
    SkSVGDOM_renderNode(dom, canvas, presentation_context, "rect1");
    SkSVGDOM_renderNode(dom, canvas, presentation_context, "missing");
    SkSVGPresentationContext_delete(presentation_context_copy);
    SkSVGPresentationContext_delete(presentation_context);
    SkSVGDOM_renderNodeById(nullptr, canvas, "rect1");
    SkSVGDOM_renderNodeById(dom, nullptr, "rect1");
    SkSVGDOM_renderNodeById(dom, canvas, nullptr);
    SkSVGDOM_renderNodeById(dom, canvas, "rect1");
    SkSVGDOM_renderNodeById(dom, canvas, "missing");
    SkCanvas_delete(canvas);
    SkSVGDOM_release(dom);
    return true;
}

}  // namespace

int main() {
    return smoke_svg_dom() ? 0 : 1;
}
