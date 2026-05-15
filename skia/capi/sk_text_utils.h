#ifndef RAIA_SKIA_SK_TEXT_UTILS_H
#define RAIA_SKIA_SK_TEXT_UTILS_H

#include <stddef.h>
#include <stdint.h>

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_font_t reskia_font_t;
typedef struct reskia_paint_t reskia_paint_t;
typedef struct reskia_path_t reskia_path_t;
typedef int32_t reskia_text_utils_align_t;
typedef int32_t reskia_text_utils_text_encoding_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkTextUtils_Draw(reskia_canvas_t *canvas, const void *text, size_t size, reskia_text_utils_text_encoding_t encoding, float x, float y, const reskia_font_t *font, const reskia_paint_t *paint, reskia_text_utils_align_t align);
void SkTextUtils_DrawString(reskia_canvas_t *canvas, const char text[], float x, float y, const reskia_font_t *font, const reskia_paint_t *paint, reskia_text_utils_align_t align);
void SkTextUtils_GetPath(const void *text, size_t length, reskia_text_utils_text_encoding_t encoding, float x, float y, const reskia_font_t *font, reskia_path_t *path);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_TEXT_UTILS_H
