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
    if (!check(SkSVGDOM_MakeFromStream(nullptr) == nullptr &&
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
