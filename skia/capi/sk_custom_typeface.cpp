#include "sk_custom_typeface.h"

#include <utility>

#include "include/core/SkFontMetrics.h"
#include "include/core/SkFontStyle.h"
#include "include/core/SkPath.h"
#include "include/core/SkRect.h"
#include "include/core/SkStream.h"
#include "include/utils/SkCustomTypeface.h"

#include "../handles/static_sk_drawable-internal.h"
#include "../handles/static_sk_font_arguments-internal.h"
#include "../handles/static_sk_stream_asset-internal.h"
#include "../handles/static_sk_typeface-internal.h"

extern "C" {

reskia_custom_typeface_builder_t *SkCustomTypefaceBuilder_new() {
    return reinterpret_cast<reskia_custom_typeface_builder_t *>(new SkCustomTypefaceBuilder());
}

void SkCustomTypefaceBuilder_delete(reskia_custom_typeface_builder_t *builder) {
    delete reinterpret_cast<SkCustomTypefaceBuilder *>(builder);
}

void SkCustomTypefaceBuilder_setGlyphPath(reskia_custom_typeface_builder_t *builder, uint16_t glyph_id, float advance, const reskia_path_t *path) {
    if (builder == nullptr || path == nullptr) {
        return;
    }
    reinterpret_cast<SkCustomTypefaceBuilder *>(builder)->setGlyph(
            glyph_id,
            advance,
            *reinterpret_cast<const SkPath *>(path));
}

void SkCustomTypefaceBuilder_setGlyphDrawable(reskia_custom_typeface_builder_t *builder, uint16_t glyph_id, float advance, sk_drawable_t drawable, const reskia_rect_t *bounds) {
    if (builder == nullptr || drawable == 0 || bounds == nullptr) {
        return;
    }
    sk_sp<SkDrawable> native_drawable = static_sk_drawable_borrow_entity(drawable);
    if (!native_drawable) {
        return;
    }
    reinterpret_cast<SkCustomTypefaceBuilder *>(builder)->setGlyph(
            glyph_id,
            advance,
            std::move(native_drawable),
            *reinterpret_cast<const SkRect *>(bounds));
}

void SkCustomTypefaceBuilder_setMetrics(reskia_custom_typeface_builder_t *builder, const reskia_font_metrics_t *metrics, float scale) {
    if (builder == nullptr || metrics == nullptr) {
        return;
    }
    reinterpret_cast<SkCustomTypefaceBuilder *>(builder)->setMetrics(
            *reinterpret_cast<const SkFontMetrics *>(metrics),
            scale);
}

void SkCustomTypefaceBuilder_setFontStyle(reskia_custom_typeface_builder_t *builder, const reskia_font_style_t *font_style) {
    if (builder == nullptr || font_style == nullptr) {
        return;
    }
    reinterpret_cast<SkCustomTypefaceBuilder *>(builder)->setFontStyle(
            *reinterpret_cast<const SkFontStyle *>(font_style));
}

sk_typeface_t SkCustomTypefaceBuilder_detach(reskia_custom_typeface_builder_t *builder) {
    if (builder == nullptr) {
        return 0;
    }
    sk_sp<SkTypeface> typeface = reinterpret_cast<SkCustomTypefaceBuilder *>(builder)->detach();
    return typeface ? static_sk_typeface_make(std::move(typeface)) : 0;
}

sk_typeface_t SkCustomTypefaceBuilder_MakeFromStream(sk_stream_asset_t stream_asset, const reskia_font_arguments_t *font_arguments) {
    if (stream_asset == 0 || font_arguments == nullptr) {
        return 0;
    }
    sk_sp<SkTypeface> typeface = SkCustomTypefaceBuilder::MakeFromStream(
            static_sk_stream_asset_take_entity(stream_asset),
            *reinterpret_cast<const SkFontArguments *>(font_arguments));
    return typeface ? static_sk_typeface_make(std::move(typeface)) : 0;
}

} // extern "C"
