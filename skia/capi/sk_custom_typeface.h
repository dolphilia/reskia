#ifndef RAIA_SKIA_SK_CUSTOM_TYPEFACE_H
#define RAIA_SKIA_SK_CUSTOM_TYPEFACE_H

#include <stdint.h>

#include "../handles/static_sk_drawable.h"
#include "../handles/static_sk_stream_asset.h"
#include "../handles/static_sk_typeface.h"

typedef struct reskia_custom_typeface_builder_t reskia_custom_typeface_builder_t;
typedef struct reskia_font_metrics_t reskia_font_metrics_t;
typedef struct reskia_font_style_t reskia_font_style_t;
typedef struct reskia_font_arguments_t reskia_font_arguments_t;
typedef struct reskia_path_t reskia_path_t;
typedef struct reskia_rect_t reskia_rect_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_custom_typeface_builder_t *SkCustomTypefaceBuilder_new();
void SkCustomTypefaceBuilder_delete(reskia_custom_typeface_builder_t *builder);
void SkCustomTypefaceBuilder_setGlyphPath(reskia_custom_typeface_builder_t *builder, uint16_t glyph_id, float advance, const reskia_path_t *path);
void SkCustomTypefaceBuilder_setGlyphDrawable(reskia_custom_typeface_builder_t *builder, uint16_t glyph_id, float advance, sk_drawable_t drawable, const reskia_rect_t *bounds);
void SkCustomTypefaceBuilder_setMetrics(reskia_custom_typeface_builder_t *builder, const reskia_font_metrics_t *metrics, float scale);
void SkCustomTypefaceBuilder_setFontStyle(reskia_custom_typeface_builder_t *builder, const reskia_font_style_t *font_style);
sk_typeface_t SkCustomTypefaceBuilder_detach(reskia_custom_typeface_builder_t *builder); // returned handle owns a ref; delete with static_sk_typeface_delete.
sk_typeface_t SkCustomTypefaceBuilder_MakeFromStream(sk_stream_asset_t stream_asset, const reskia_font_arguments_t *font_arguments); // stream_asset は consumed。invalid 入力や生成不能では 0

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_CUSTOM_TYPEFACE_H
