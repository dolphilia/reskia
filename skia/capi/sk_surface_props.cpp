//
// Created by dolphilia on 2024/01/11.
//

#include "sk_surface_props.h"

#include "include/core/SkSurfaceProps.h"

#include "../handles/static_sk_surface_props.h"

#include "../handles/static_sk_surface_props-internal.h"

namespace {

SkSurfaceProps *as_props(reskia_surface_props_t *surface_props) {
    return reinterpret_cast<SkSurfaceProps *>(surface_props);
}

const SkSurfaceProps *as_props(const reskia_surface_props_t *surface_props) {
    return reinterpret_cast<const SkSurfaceProps *>(surface_props);
}

} // namespace

extern "C" {

// SkSurfaceProps & operator=(const SkSurfaceProps &)
// bool operator==(const SkSurfaceProps &that)
// bool operator!=(const SkSurfaceProps &that)

reskia_surface_props_t *SkSurfaceProps_new() {
    return reinterpret_cast<reskia_surface_props_t *>(new SkSurfaceProps());
}

reskia_surface_props_t *SkSurfaceProps_newWithFlagsAndGeometry(uint32_t flags, reskia_surface_props_pixel_geometry_t geometry) {
    return reinterpret_cast<reskia_surface_props_t *>(new SkSurfaceProps(flags, static_cast<SkPixelGeometry>(geometry)));
}

reskia_surface_props_t *SkSurfaceProps_newCopy(const reskia_surface_props_t *props) {
    const SkSurfaceProps *native = as_props(props);
    return native != nullptr ? reinterpret_cast<reskia_surface_props_t *>(new SkSurfaceProps(*native)) : nullptr;
}

void SkSurfaceProps_delete(reskia_surface_props_t *surface_props) {
    delete as_props(surface_props);
}

sk_surface_props_t SkSurfaceProps_cloneWithPixelGeometry(reskia_surface_props_t *surface_props, reskia_surface_props_pixel_geometry_t newPixelGeometry) {
    SkSurfaceProps *native = as_props(surface_props);
    return native != nullptr ? static_sk_surface_props_make(native->cloneWithPixelGeometry(static_cast<SkPixelGeometry>(newPixelGeometry))) : 0;
}

uint32_t SkSurfaceProps_flags(reskia_surface_props_t *surface_props) {
    SkSurfaceProps *native = as_props(surface_props);
    return native != nullptr ? native->flags() : 0;
}

reskia_surface_props_pixel_geometry_t SkSurfaceProps_pixelGeometry(reskia_surface_props_t *surface_props) {
    SkSurfaceProps *native = as_props(surface_props);
    return native != nullptr ? static_cast<reskia_surface_props_pixel_geometry_t>(native->pixelGeometry()) : 0;
}

bool SkSurfaceProps_isUseDeviceIndependentFonts(reskia_surface_props_t *surface_props) {
    SkSurfaceProps *native = as_props(surface_props);
    return native != nullptr ? native->isUseDeviceIndependentFonts() : false;
}

bool SkSurfaceProps_isAlwaysDither(reskia_surface_props_t *surface_props) {
    SkSurfaceProps *native = as_props(surface_props);
    return native != nullptr ? native->isAlwaysDither() : false;
}

}
