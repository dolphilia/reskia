//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_SURFACE_PROPS_H
#define RAIA_SKIA_SK_SURFACE_PROPS_H

#include <stdint.h>

#include "../handles/static_sk_surface_props.h"

typedef struct reskia_surface_props_t reskia_surface_props_t;
typedef int32_t reskia_surface_props_pixel_geometry_t;

#ifdef __cplusplus
extern "C" {
#endif

// SkSurfaceProps & operator=(const SkSurfaceProps &)
// bool operator==(const SkSurfaceProps &that)
// bool operator!=(const SkSurfaceProps &that)

reskia_surface_props_t *SkSurfaceProps_new(); // () -> SkSurfaceProps *
reskia_surface_props_t *SkSurfaceProps_newWithFlagsAndGeometry(uint32_t flags, reskia_surface_props_pixel_geometry_t geometry); // (uint32_t flags, SkPixelGeometry geometry) -> SkSurfaceProps *
reskia_surface_props_t *SkSurfaceProps_newCopy(const reskia_surface_props_t *props); // (const SkSurfaceProps *props) -> SkSurfaceProps *
void SkSurfaceProps_delete(reskia_surface_props_t *surface_props); // (SkSurfaceProps *surface_props)
sk_surface_props_t SkSurfaceProps_cloneWithPixelGeometry(reskia_surface_props_t *surface_props, reskia_surface_props_pixel_geometry_t newPixelGeometry); // (SkSurfaceProps *surface_props, SkPixelGeometry newPixelGeometry) -> sk_surface_props_t
uint32_t SkSurfaceProps_flags(reskia_surface_props_t *surface_props); // (SkSurfaceProps *surface_props) -> uint32_t
reskia_surface_props_pixel_geometry_t SkSurfaceProps_pixelGeometry(reskia_surface_props_t *surface_props); // (SkSurfaceProps *surface_props) -> SkPixelGeometry
bool SkSurfaceProps_isUseDeviceIndependentFonts(reskia_surface_props_t *surface_props); // (SkSurfaceProps *surface_props) -> bool
bool SkSurfaceProps_isAlwaysDither(reskia_surface_props_t *surface_props); // (SkSurfaceProps *surface_props) -> bool

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_SURFACE_PROPS_H
