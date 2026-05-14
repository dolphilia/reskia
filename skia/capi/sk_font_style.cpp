//
// Created by dolphilia on 2024/01/08.
//

#include "sk_font_style.h"

#include "include/core/SkFontStyle.h"

extern "C" {

void SkFontStyle_delete(reskia_font_style_t *font_style) {
    if (font_style == nullptr) {
        return;
    }
    delete reinterpret_cast<SkFontStyle *>(font_style);
}

int SkFontStyle_weight(reskia_font_style_t *font_style) {
    if (font_style == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkFontStyle *>(font_style)->weight();
}

int SkFontStyle_width(reskia_font_style_t *font_style) {
    if (font_style == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkFontStyle *>(font_style)->width();
}

reskia_font_style_slant_t SkFontStyle_slant(reskia_font_style_t *font_style) {
    if (font_style == nullptr) {
        return -1;
    }
    return static_cast<reskia_font_style_slant_t>(reinterpret_cast<SkFontStyle *>(font_style)->slant());
}

reskia_font_style_t *SkFontStyle_Normal() {
    return reinterpret_cast<reskia_font_style_t *>(new SkFontStyle(SkFontStyle::Normal()));
}

reskia_font_style_t *SkFontStyle_Bold() {
    return reinterpret_cast<reskia_font_style_t *>(new SkFontStyle(SkFontStyle::Bold()));
}

reskia_font_style_t *SkFontStyle_Italic() {
    return reinterpret_cast<reskia_font_style_t *>(new SkFontStyle(SkFontStyle::Italic()));
}

reskia_font_style_t *SkFontStyle_BoldItalic() {
    return reinterpret_cast<reskia_font_style_t *>(new SkFontStyle(SkFontStyle::BoldItalic()));
}

}
