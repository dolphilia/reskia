#ifndef RAIA_SKIA_SK_SKOTTIE_H
#define RAIA_SKIA_SK_SKOTTIE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_skottie_animation_t reskia_skottie_animation_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_skottie_animation_t *Skottie_Animation_Make(const char *data, size_t length);
reskia_skottie_animation_t *Skottie_Animation_MakeFromFile(const char path[]);

void Skottie_Animation_release(reskia_skottie_animation_t *animation);
void Skottie_Animation_ref(reskia_skottie_animation_t *animation);
void Skottie_Animation_unref(reskia_skottie_animation_t *animation);

bool Skottie_Animation_seek(reskia_skottie_animation_t *animation, float t);
bool Skottie_Animation_seekFrameTime(reskia_skottie_animation_t *animation, double t);
void Skottie_Animation_render(reskia_skottie_animation_t *animation, reskia_canvas_t *canvas, const reskia_rect_t *dst);
void Skottie_Animation_renderWithFlags(reskia_skottie_animation_t *animation, reskia_canvas_t *canvas, const reskia_rect_t *dst, uint32_t flags);

double Skottie_Animation_duration(const reskia_skottie_animation_t *animation);
double Skottie_Animation_fps(const reskia_skottie_animation_t *animation);
float Skottie_Animation_width(const reskia_skottie_animation_t *animation);
float Skottie_Animation_height(const reskia_skottie_animation_t *animation);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_SKOTTIE_H
