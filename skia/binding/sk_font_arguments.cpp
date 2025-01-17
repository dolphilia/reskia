//
// Created by dolphilia on 2024/01/08.
//

#include "sk_font_arguments.h"

#include "include/core/SkFontArguments.h"

#include "../static/static_sk_font_arguments.h"
#include "../static/static_sk_font_arguments_variation_position.h"
#include "../static/static_sk_font_arguments_palette.h"

#include "static/static_sk_font_arguments-internal.h"
#include "static/static_sk_font_arguments_palette-internal.h"
#include "static/static_sk_font_arguments_variation_position-internal.h"

extern "C" {

void *SkFontArguments_new() {
    return new SkFontArguments();
}

void SkFontArguments_delete(void *font_arguments) {
    delete static_cast<SkFontArguments *>(font_arguments);
}

sk_font_arguments_t SkFontArguments_setCollectionIndex(void *font_argments, int collectionIndex) {
    return static_sk_font_arguments_make(static_cast<SkFontArguments *>(font_argments)->setCollectionIndex(collectionIndex));
}

sk_font_arguments_t SkFontArguments_setVariationDesignPosition(void *font_argments, sk_font_arguments_variation_position_t position) {
    return static_sk_font_arguments_make(static_cast<SkFontArguments *>(font_argments)->setVariationDesignPosition(static_sk_font_arguments_variation_position_get(position)));
}

int SkFontArguments_getCollectionIndex(void *font_argments) {
    return static_cast<SkFontArguments *>(font_argments)->getCollectionIndex();
}

sk_font_arguments_variation_position_t SkFontArguments_getVariationDesignPosition(void *font_argments) {
    return static_sk_font_arguments_variation_position_make(static_cast<SkFontArguments *>(font_argments)->getVariationDesignPosition());
}

sk_font_arguments_t SkFontArguments_setPalette(void *font_argments, sk_font_arguments_palette_t palette) {
    return static_sk_font_arguments_make(static_cast<SkFontArguments *>(font_argments)->setPalette(static_sk_font_arguments_palette_get(palette)));
}

sk_font_arguments_palette_t SkFontArguments_getPalette(void *font_argments) {
    return static_sk_font_arguments_palette_make(static_cast<SkFontArguments *>(font_argments)->getPalette());
}

}
