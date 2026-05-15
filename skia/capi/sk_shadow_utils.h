#ifndef RAIA_SKIA_SK_SHADOW_UTILS_H
#define RAIA_SKIA_SK_SHADOW_UTILS_H

#include <stdbool.h>
#include <stdint.h>

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_path_t reskia_path_t;
typedef struct reskia_point_3_t reskia_point_3_t;
typedef struct reskia_rect_t reskia_rect_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkShadowUtils_DrawShadow(reskia_canvas_t *canvas, const reskia_path_t *path, const reskia_point_3_t *z_plane_params, const reskia_point_3_t *light_pos, float light_radius, uint32_t ambient_color, uint32_t spot_color, uint32_t flags);
bool SkShadowUtils_GetLocalBounds(const reskia_matrix_t *ctm, const reskia_path_t *path, const reskia_point_3_t *z_plane_params, const reskia_point_3_t *light_pos, float light_radius, uint32_t flags, reskia_rect_t *bounds);
void SkShadowUtils_ComputeTonalColors(uint32_t in_ambient_color, uint32_t in_spot_color, uint32_t *out_ambient_color, uint32_t *out_spot_color);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_SHADOW_UTILS_H
