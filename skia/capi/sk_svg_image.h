//
// Created by Codex on 2026/05/21.
//

#ifndef RAIA_SKIA_SK_SVG_IMAGE_H
#define RAIA_SKIA_SK_SVG_IMAGE_H

#include <stdbool.h>

#include "../handles/static_sk_image.h"
#include "../handles/static_sk_rect.h"
#include "sk_rect.h"
#include "sk_resources.h"
#include "sk_svg_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_svg_image_info_t {
    sk_image_t image;
    sk_rect_t dst;
} reskia_svg_image_info_t;

bool SkSVGImage_LoadImage(reskia_skresources_resource_provider_t *resource_provider, const reskia_svg_iri_t *iri, const reskia_rect_t *view_port, const reskia_svg_preserve_aspect_ratio_t *preserve_aspect_ratio, reskia_svg_image_info_t *out_info);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_SVG_IMAGE_H
