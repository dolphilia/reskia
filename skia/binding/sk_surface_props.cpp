//
// Created by dolphilia on 2024/01/11.
//

#include "sk_surface_props.h"

#include "include/core/SkSurfaceProps.h"

#include "../static/static_sk_surface_props.h"

#include "../static/static_sk_surface_props-internal.h"

extern "C" {

// SkSurfaceProps & operator=(const SkSurfaceProps &)
// bool operator==(const SkSurfaceProps &that)
// bool operator!=(const SkSurfaceProps &that)

reskia_surface_props_t *SkSurfaceProps_new() {
    return reinterpret_cast<reskia_surface_props_t *>(new SkSurfaceProps());
}

reskia_surface_props_t *SkSurfaceProps_new_2(uint32_t flags, int geometry) {
    return reinterpret_cast<reskia_surface_props_t *>(new SkSurfaceProps(flags, static_cast<SkPixelGeometry>(geometry)));
}

reskia_surface_props_t *SkSurfaceProps_new_3(const reskia_surface_props_t *props) {
    return reinterpret_cast<reskia_surface_props_t *>(new SkSurfaceProps(* reinterpret_cast<const SkSurfaceProps *>(props)));
}

void SkSurfaceProps_delete(reskia_surface_props_t *surface_props) {
    delete reinterpret_cast<SkSurfaceProps *>(surface_props);
}

sk_surface_props_t SkSurfaceProps_cloneWithPixelGeometry(reskia_surface_props_t *surface_props, int newPixelGeometry) {
    return static_sk_surface_props_make(reinterpret_cast<SkSurfaceProps *>(surface_props)->cloneWithPixelGeometry(static_cast<SkPixelGeometry>(newPixelGeometry)));
}

uint32_t SkSurfaceProps_flags(reskia_surface_props_t *surface_props) {
    return reinterpret_cast<SkSurfaceProps *>(surface_props)->flags();
}

int SkSurfaceProps_pixelGeometry(reskia_surface_props_t *surface_props) {
    return reinterpret_cast<SkSurfaceProps *>(surface_props)->pixelGeometry();
}

bool SkSurfaceProps_isUseDeviceIndependentFonts(reskia_surface_props_t *surface_props) {
    return reinterpret_cast<SkSurfaceProps *>(surface_props)->isUseDeviceIndependentFonts();
}

bool SkSurfaceProps_isAlwaysDither(reskia_surface_props_t *surface_props) {
    return reinterpret_cast<SkSurfaceProps *>(surface_props)->isAlwaysDither();
}

}
