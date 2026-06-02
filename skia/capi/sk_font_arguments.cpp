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

#include <optional>

extern "C" {

reskia_font_arguments_t *SkFontArguments_new() {
    return reinterpret_cast<reskia_font_arguments_t *>(new SkFontArguments());
}

void SkFontArguments_delete(reskia_font_arguments_t *font_arguments) {
    delete reinterpret_cast<SkFontArguments *>(font_arguments);
}

sk_font_arguments_t SkFontArguments_setCollectionIndex(reskia_font_arguments_t *font_arguments, int collectionIndex) {
    if (font_arguments == nullptr || collectionIndex < 0) {
        return 0;
    }
    return static_sk_font_arguments_make(reinterpret_cast<SkFontArguments *>(font_arguments)->setCollectionIndex(collectionIndex));
}

sk_font_arguments_t SkFontArguments_setVariationDesignPosition(reskia_font_arguments_t *font_arguments, sk_font_arguments_variation_position_t position) {
    if (font_arguments == nullptr) {
        return 0;
    }
    return static_sk_font_arguments_make(reinterpret_cast<SkFontArguments *>(font_arguments)->setVariationDesignPosition(static_sk_font_arguments_variation_position_get_entity(position)));
}

int SkFontArguments_getCollectionIndex(reskia_font_arguments_t *font_arguments) {
    if (font_arguments == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkFontArguments *>(font_arguments)->getCollectionIndex();
}

sk_font_arguments_variation_position_t SkFontArguments_getVariationDesignPosition(reskia_font_arguments_t *font_arguments) {
    if (font_arguments == nullptr) {
        return 0;
    }
    return static_sk_font_arguments_variation_position_make(reinterpret_cast<SkFontArguments *>(font_arguments)->getVariationDesignPosition());
}

sk_font_arguments_t SkFontArguments_setPalette(reskia_font_arguments_t *font_arguments, sk_font_arguments_palette_t palette) {
    if (font_arguments == nullptr) {
        return 0;
    }
    return static_sk_font_arguments_make(reinterpret_cast<SkFontArguments *>(font_arguments)->setPalette(static_sk_font_arguments_palette_get_entity(palette)));
}

sk_font_arguments_palette_t SkFontArguments_getPalette(reskia_font_arguments_t *font_arguments) {
    if (font_arguments == nullptr) {
        return 0;
    }
    return static_sk_font_arguments_palette_make(reinterpret_cast<SkFontArguments *>(font_arguments)->getPalette());
}

sk_font_arguments_t SkFontArguments_setSyntheticBold(reskia_font_arguments_t *font_arguments, bool hasValue, bool bold) {
    if (font_arguments == nullptr) {
        return 0;
    }
    return static_sk_font_arguments_make(
            reinterpret_cast<SkFontArguments *>(font_arguments)->setSyntheticBold(
                    hasValue ? std::optional<bool>(bold) : std::nullopt));
}

bool SkFontArguments_getSyntheticBold(reskia_font_arguments_t *font_arguments, bool *bold) {
    if (font_arguments == nullptr || bold == nullptr) {
        return false;
    }
    std::optional<bool> value = reinterpret_cast<SkFontArguments *>(font_arguments)->getSyntheticBold();
    if (!value.has_value()) {
        return false;
    }
    *bold = *value;
    return true;
}

sk_font_arguments_t SkFontArguments_setSyntheticOblique(reskia_font_arguments_t *font_arguments, bool hasValue, bool oblique) {
    if (font_arguments == nullptr) {
        return 0;
    }
    return static_sk_font_arguments_make(
            reinterpret_cast<SkFontArguments *>(font_arguments)->setSyntheticOblique(
                    hasValue ? std::optional<bool>(oblique) : std::nullopt));
}

bool SkFontArguments_getSyntheticOblique(reskia_font_arguments_t *font_arguments, bool *oblique) {
    if (font_arguments == nullptr || oblique == nullptr) {
        return false;
    }
    std::optional<bool> value = reinterpret_cast<SkFontArguments *>(font_arguments)->getSyntheticOblique();
    if (!value.has_value()) {
        return false;
    }
    *oblique = *value;
    return true;
}

}
