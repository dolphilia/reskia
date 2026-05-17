//
// Created by Codex on 2026/05/17.
//

#include "sk_paragraph_font_arguments.h"

#include "include/core/SkFontArguments.h"
#include "modules/skparagraph/include/FontArguments.h"

#include "../handles/static_sk_typeface-internal.h"

namespace {

using skia::textlayout::FontArguments;

const SkFontArguments *as_sk_font_arguments(const reskia_font_arguments_t *arguments) {
    return reinterpret_cast<const SkFontArguments *>(arguments);
}

FontArguments *as_paragraph_font_arguments(reskia_paragraph_font_arguments_t *arguments) {
    return reinterpret_cast<FontArguments *>(arguments);
}

const FontArguments *as_paragraph_font_arguments(const reskia_paragraph_font_arguments_t *arguments) {
    return reinterpret_cast<const FontArguments *>(arguments);
}

sk_typeface_t make_typeface_handle(sk_sp<SkTypeface> typeface) {
    if (!typeface) {
        return 0;
    }
    return static_sk_typeface_make(std::move(typeface));
}

} // namespace

extern "C" {

reskia_paragraph_font_arguments_t *SkParagraph_FontArguments_new(const reskia_font_arguments_t *arguments) {
    if (arguments == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_paragraph_font_arguments_t *>(new FontArguments(*as_sk_font_arguments(arguments)));
}

reskia_paragraph_font_arguments_t *SkParagraph_FontArguments_copy(const reskia_paragraph_font_arguments_t *arguments) {
    if (arguments == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_paragraph_font_arguments_t *>(new FontArguments(*as_paragraph_font_arguments(arguments)));
}

void SkParagraph_FontArguments_delete(reskia_paragraph_font_arguments_t *arguments) {
    delete as_paragraph_font_arguments(arguments);
}

sk_typeface_t SkParagraph_FontArguments_CloneTypeface(const reskia_paragraph_font_arguments_t *arguments, sk_typeface_t typeface) {
    if (arguments == nullptr || typeface == 0) {
        return 0;
    }
    sk_sp<SkTypeface> source = static_sk_typeface_get_entity(typeface);
    if (!source) {
        return 0;
    }
    return make_typeface_handle(as_paragraph_font_arguments(arguments)->CloneTypeface(source));
}

} // extern "C"
