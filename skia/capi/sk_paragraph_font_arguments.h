//
// Created by Codex on 2026/05/17.
//

#ifndef RAIA_SKIA_SK_PARAGRAPH_FONT_ARGUMENTS_H
#define RAIA_SKIA_SK_PARAGRAPH_FONT_ARGUMENTS_H

#include <stdbool.h>

#include "../handles/static_sk_typeface.h"

typedef struct reskia_font_arguments_t reskia_font_arguments_t;
typedef struct reskia_paragraph_font_arguments_t reskia_paragraph_font_arguments_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_paragraph_font_arguments_t *SkParagraph_FontArguments_new(const reskia_font_arguments_t *arguments);
reskia_paragraph_font_arguments_t *SkParagraph_FontArguments_copy(const reskia_paragraph_font_arguments_t *arguments);
void SkParagraph_FontArguments_delete(reskia_paragraph_font_arguments_t *arguments);
sk_typeface_t SkParagraph_FontArguments_CloneTypeface(const reskia_paragraph_font_arguments_t *arguments, sk_typeface_t typeface);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_PARAGRAPH_FONT_ARGUMENTS_H
