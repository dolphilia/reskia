//
// Created by dolphilia on 2024/01/08.
//

#include "sk_font_arguments.h"

#include "include/core/SkFontArguments.h"

#include "../handles/static_sk_font_arguments.h"
#include "../handles/static_sk_font_arguments_variation_position.h"
#include "../handles/static_sk_font_arguments_palette.h"

#include "handles/static_sk_font_arguments-internal.h"
#include "handles/static_sk_font_arguments_palette-internal.h"
#include "handles/static_sk_font_arguments_variation_position-internal.h"

extern "C" {

reskia_font_arguments_t *SkFontArguments_new() {
    return reinterpret_cast<reskia_font_arguments_t *>(new SkFontArguments());
}

void SkFontArguments_delete(reskia_font_arguments_t *font_arguments) {
    delete reinterpret_cast<SkFontArguments *>(font_arguments);
}

sk_font_arguments_t SkFontArguments_setCollectionIndex(reskia_font_arguments_t *font_arguments, int collectionIndex) {
    return static_sk_font_arguments_make(reinterpret_cast<SkFontArguments *>(font_arguments)->setCollectionIndex(collectionIndex));
}

sk_font_arguments_t SkFontArguments_setVariationDesignPosition(reskia_font_arguments_t *font_arguments, sk_font_arguments_variation_position_t position) {
    return static_sk_font_arguments_make(reinterpret_cast<SkFontArguments *>(font_arguments)->setVariationDesignPosition(static_sk_font_arguments_variation_position_get_entity(position)));
}

int SkFontArguments_getCollectionIndex(reskia_font_arguments_t *font_arguments) {
    return reinterpret_cast<SkFontArguments *>(font_arguments)->getCollectionIndex();
}

sk_font_arguments_variation_position_t SkFontArguments_getVariationDesignPosition(reskia_font_arguments_t *font_arguments) {
    return static_sk_font_arguments_variation_position_make(reinterpret_cast<SkFontArguments *>(font_arguments)->getVariationDesignPosition());
}

sk_font_arguments_t SkFontArguments_setPalette(reskia_font_arguments_t *font_arguments, sk_font_arguments_palette_t palette) {
    return static_sk_font_arguments_make(reinterpret_cast<SkFontArguments *>(font_arguments)->setPalette(static_sk_font_arguments_palette_get_entity(palette)));
}

sk_font_arguments_palette_t SkFontArguments_getPalette(reskia_font_arguments_t *font_arguments) {
    return static_sk_font_arguments_palette_make(reinterpret_cast<SkFontArguments *>(font_arguments)->getPalette());
}

}
