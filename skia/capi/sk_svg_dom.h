//
// Created by Codex on 2026/05/14.
//

#ifndef RAIA_SKIA_SK_SVG_DOM_H
#define RAIA_SKIA_SK_SVG_DOM_H

#include <stdbool.h>

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_stream_t reskia_stream_t;
typedef struct reskia_svg_dom_t reskia_svg_dom_t;
typedef struct reskia_svg_node_t reskia_svg_node_t;
typedef struct reskia_svg_presentation_context_t reskia_svg_presentation_context_t;
typedef struct reskia_svg_svg_t reskia_svg_svg_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_svg_dom_t *SkSVGDOM_MakeFromStream(reskia_stream_t *stream); // owned: caller releases with SkSVGDOM_release; NULL stream returns NULL
reskia_svg_presentation_context_t *SkSVGPresentationContext_new(void); // owned; delete with SkSVGPresentationContext_delete
reskia_svg_presentation_context_t *SkSVGPresentationContext_copy(const reskia_svg_presentation_context_t *context); // owned; NULL input returns NULL
void SkSVGPresentationContext_delete(reskia_svg_presentation_context_t *context); // NULL input is no-op
void SkSVGDOM_ref(reskia_svg_dom_t *dom); // retained: NULL input is no-op
void SkSVGDOM_unref(reskia_svg_dom_t *dom); // owned: NULL input is no-op
void SkSVGDOM_release(reskia_svg_dom_t *dom); // alias of SkSVGDOM_unref
reskia_svg_svg_t *SkSVGDOM_getRoot(reskia_svg_dom_t *dom); // borrowed: NULL input returns NULL
void SkSVGDOM_setContainerSize(reskia_svg_dom_t *dom, float width, float height); // NULL input is no-op
bool SkSVGDOM_containerSize(reskia_svg_dom_t *dom, float *width, float *height); // NULL input returns false; out params optional
reskia_svg_node_t *SkSVGDOM_findNodeById(reskia_svg_dom_t *dom, const char *id); // borrowed: NULL input or missing id returns NULL
void SkSVGDOM_render(reskia_svg_dom_t *dom, reskia_canvas_t *canvas); // NULL input is no-op
void SkSVGDOM_renderNode(reskia_svg_dom_t *dom, reskia_canvas_t *canvas, reskia_svg_presentation_context_t *context, const char *id); // NULL input is no-op
void SkSVGDOM_renderNodeById(reskia_svg_dom_t *dom, reskia_canvas_t *canvas, const char *id); // NULL input is no-op

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_SVG_DOM_H
