//
// Created by Codex on 2026/05/14.
//

#include "sk_svg_dom.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkStream.h"
#include "modules/svg/include/SkSVGDOM.h"
#include "modules/svg/include/SkSVGNode.h"
#include "modules/svg/include/SkSVGRenderContext.h"

namespace {

SkSVGDOM *as_svg_dom(reskia_svg_dom_t *dom) {
    return reinterpret_cast<SkSVGDOM *>(dom);
}

const SkSVGDOM *as_svg_dom(const reskia_svg_dom_t *dom) {
    return reinterpret_cast<const SkSVGDOM *>(dom);
}

SkStream *as_stream(reskia_stream_t *stream) {
    return reinterpret_cast<SkStream *>(stream);
}

SkCanvas *as_canvas(reskia_canvas_t *canvas) {
    return reinterpret_cast<SkCanvas *>(canvas);
}

SkSVGPresentationContext *as_presentation_context(reskia_svg_presentation_context_t *context) {
    return reinterpret_cast<SkSVGPresentationContext *>(context);
}

const SkSVGPresentationContext *as_presentation_context(const reskia_svg_presentation_context_t *context) {
    return reinterpret_cast<const SkSVGPresentationContext *>(context);
}

}  // namespace

extern "C" {

reskia_svg_dom_t *SkSVGDOM_MakeFromStream(reskia_stream_t *stream) {
    if (stream == nullptr) {
        return nullptr;
    }
    auto dom = SkSVGDOM::MakeFromStream(*as_stream(stream));
    return reinterpret_cast<reskia_svg_dom_t *>(dom.release());
}

reskia_svg_presentation_context_t *SkSVGPresentationContext_new(void) {
    return reinterpret_cast<reskia_svg_presentation_context_t *>(new SkSVGPresentationContext());
}

reskia_svg_presentation_context_t *SkSVGPresentationContext_copy(const reskia_svg_presentation_context_t *context) {
    return context != nullptr ? reinterpret_cast<reskia_svg_presentation_context_t *>(new SkSVGPresentationContext(*as_presentation_context(context))) : nullptr;
}

void SkSVGPresentationContext_delete(reskia_svg_presentation_context_t *context) {
    delete as_presentation_context(context);
}

void SkSVGDOM_ref(reskia_svg_dom_t *dom) {
    if (dom == nullptr) {
        return;
    }
    as_svg_dom(dom)->ref();
}

void SkSVGDOM_unref(reskia_svg_dom_t *dom) {
    if (dom == nullptr) {
        return;
    }
    as_svg_dom(dom)->unref();
}

void SkSVGDOM_release(reskia_svg_dom_t *dom) {
    SkSVGDOM_unref(dom);
}

reskia_svg_svg_t *SkSVGDOM_getRoot(reskia_svg_dom_t *dom) {
    return dom != nullptr ? reinterpret_cast<reskia_svg_svg_t *>(as_svg_dom(dom)->getRoot()) : nullptr;
}

void SkSVGDOM_setContainerSize(reskia_svg_dom_t *dom, float width, float height) {
    if (dom == nullptr) {
        return;
    }
    as_svg_dom(dom)->setContainerSize(SkSize::Make(width, height));
}

bool SkSVGDOM_containerSize(reskia_svg_dom_t *dom, float *width, float *height) {
    if (dom == nullptr) {
        if (width != nullptr) {
            *width = 0.0f;
        }
        if (height != nullptr) {
            *height = 0.0f;
        }
        return false;
    }
    const SkSize &size = as_svg_dom(dom)->containerSize();
    if (width != nullptr) {
        *width = size.width();
    }
    if (height != nullptr) {
        *height = size.height();
    }
    return true;
}

reskia_svg_node_t *SkSVGDOM_findNodeById(reskia_svg_dom_t *dom, const char *id) {
    if (dom == nullptr || id == nullptr) {
        return nullptr;
    }
    sk_sp<SkSVGNode> *node = as_svg_dom(dom)->findNodeById(id);
    return node != nullptr ? reinterpret_cast<reskia_svg_node_t *>(node->get()) : nullptr;
}

void SkSVGDOM_render(reskia_svg_dom_t *dom, reskia_canvas_t *canvas) {
    if (dom == nullptr || canvas == nullptr) {
        return;
    }
    as_svg_dom(dom)->render(as_canvas(canvas));
}

void SkSVGDOM_renderNode(reskia_svg_dom_t *dom, reskia_canvas_t *canvas, reskia_svg_presentation_context_t *context, const char *id) {
    if (dom == nullptr || canvas == nullptr || context == nullptr || id == nullptr) {
        return;
    }
    as_svg_dom(dom)->renderNode(as_canvas(canvas), *as_presentation_context(context), id);
}

void SkSVGDOM_renderNodeById(reskia_svg_dom_t *dom, reskia_canvas_t *canvas, const char *id) {
    if (dom == nullptr || canvas == nullptr || id == nullptr) {
        return;
    }
    SkSVGPresentationContext context;
    as_svg_dom(dom)->renderNode(as_canvas(canvas), context, id);
}

}
