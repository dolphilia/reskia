//
// Created by dolphilia on 2024/01/08.
//

#include "sk_font_style.h"

#include "include/core/SkFontStyle.h"

extern "C" {

void SkFontStyle_delete(void *font_style) {
    delete static_cast<SkFontStyle *>(font_style);
}

int SkFontStyle_weight(void *font_style) {
    return static_cast<SkFontStyle *>(font_style)->weight();
}

int SkFontStyle_width(void *font_style) {
    return static_cast<SkFontStyle *>(font_style)->width();
}

int SkFontStyle_slant(void *font_style) {
    return static_cast<SkFontStyle *>(font_style)->slant();
}

}