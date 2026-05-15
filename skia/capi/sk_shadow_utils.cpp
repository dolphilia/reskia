#include "sk_shadow_utils.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkMatrix.h"
#include "include/core/SkPath.h"
#include "include/core/SkPoint3.h"
#include "include/core/SkRect.h"
#include "include/utils/SkShadowUtils.h"

extern "C" {

void SkShadowUtils_DrawShadow(reskia_canvas_t *canvas, const reskia_path_t *path, const reskia_point_3_t *z_plane_params, const reskia_point_3_t *light_pos, float light_radius, uint32_t ambient_color, uint32_t spot_color, uint32_t flags) {
    if (canvas == nullptr || path == nullptr || z_plane_params == nullptr || light_pos == nullptr) {
        return;
    }
    SkShadowUtils::DrawShadow(
            reinterpret_cast<SkCanvas *>(canvas),
            *reinterpret_cast<const SkPath *>(path),
            *reinterpret_cast<const SkPoint3 *>(z_plane_params),
            *reinterpret_cast<const SkPoint3 *>(light_pos),
            light_radius,
            ambient_color,
            spot_color,
            flags);
}

bool SkShadowUtils_GetLocalBounds(const reskia_matrix_t *ctm, const reskia_path_t *path, const reskia_point_3_t *z_plane_params, const reskia_point_3_t *light_pos, float light_radius, uint32_t flags, reskia_rect_t *bounds) {
    if (ctm == nullptr || path == nullptr || z_plane_params == nullptr || light_pos == nullptr || bounds == nullptr) {
        return false;
    }
    return SkShadowUtils::GetLocalBounds(
            *reinterpret_cast<const SkMatrix *>(ctm),
            *reinterpret_cast<const SkPath *>(path),
            *reinterpret_cast<const SkPoint3 *>(z_plane_params),
            *reinterpret_cast<const SkPoint3 *>(light_pos),
            light_radius,
            flags,
            reinterpret_cast<SkRect *>(bounds));
}

void SkShadowUtils_ComputeTonalColors(uint32_t in_ambient_color, uint32_t in_spot_color, uint32_t *out_ambient_color, uint32_t *out_spot_color) {
    if (out_ambient_color == nullptr || out_spot_color == nullptr) {
        return;
    }
    SkShadowUtils::ComputeTonalColors(
            in_ambient_color,
            in_spot_color,
            out_ambient_color,
            out_spot_color);
}

} // extern "C"
