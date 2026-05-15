#include <cstdio>

#include "capi/sk_custom_typeface.h"
#include "capi/sk_font.h"
#include "capi/sk_font_style.h"
#include "capi/sk_path.h"
#include "handles/static_sk_typeface.h"

namespace {

bool check(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "[custom-typeface-utils-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    if (!check(SkCustomTypefaceBuilder_detach(nullptr) == 0,
               "SkCustomTypefaceBuilder_detach null")) {
        return 1;
    }
    SkCustomTypefaceBuilder_setGlyphDrawable(nullptr, 1, 10.0f, 0, nullptr);
    if (!check(SkCustomTypefaceBuilder_MakeFromStream(0, nullptr) == 0,
               "SkCustomTypefaceBuilder_MakeFromStream null")) {
        return 1;
    }

    reskia_custom_typeface_builder_t *builder = SkCustomTypefaceBuilder_new();
    reskia_path_t *glyph_path = SkPath_new();
    reskia_font_style_t *style = SkFontStyle_Normal();
    if (!check(builder != nullptr && glyph_path != nullptr && style != nullptr,
               "custom typeface setup")) {
        SkFontStyle_delete(style);
        SkPath_delete(glyph_path);
        SkCustomTypefaceBuilder_delete(builder);
        return 1;
    }

    SkPath_addRectLTRBWithDirection(glyph_path, 0.0f, 0.0f, 10.0f, 10.0f, 0);
    SkCustomTypefaceBuilder_setGlyphPath(builder, 1, 10.0f, glyph_path);
    SkCustomTypefaceBuilder_setFontStyle(builder, style);
    sk_typeface_t typeface = SkCustomTypefaceBuilder_detach(builder);
    if (!check(typeface != 0, "SkCustomTypefaceBuilder_detach")) {
        SkFontStyle_delete(style);
        SkPath_delete(glyph_path);
        SkCustomTypefaceBuilder_delete(builder);
        return 1;
    }

    reskia_font_t *font = SkFont_newWithTypefaceAndSize(typeface, 12.0f);
    reskia_path_t *out_path = SkPath_new();
    if (!check(font != nullptr && out_path != nullptr, "custom typeface font setup")) {
        SkPath_delete(out_path);
        SkFont_delete(font);
        static_sk_typeface_delete(typeface);
        SkFontStyle_delete(style);
        SkPath_delete(glyph_path);
        SkCustomTypefaceBuilder_delete(builder);
        return 1;
    }
    if (!check(SkFont_getPath(font, 1, out_path), "custom typeface glyph path")) {
        SkPath_delete(out_path);
        SkFont_delete(font);
        static_sk_typeface_delete(typeface);
        SkFontStyle_delete(style);
        SkPath_delete(glyph_path);
        SkCustomTypefaceBuilder_delete(builder);
        return 1;
    }

    SkPath_delete(out_path);
    SkFont_delete(font);
    static_sk_typeface_delete(typeface);
    SkFontStyle_delete(style);
    SkPath_delete(glyph_path);
    SkCustomTypefaceBuilder_delete(builder);

    std::fprintf(stdout, "[custom-typeface-utils-smoke] PASS\n");
    return 0;
}
