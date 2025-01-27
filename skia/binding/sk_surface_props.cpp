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

void *SkSurfaceProps_new() {
    return new SkSurfaceProps();
}

void *SkSurfaceProps_new_2(uint32_t flags, int geometry) {
    return new SkSurfaceProps(flags, static_cast<SkPixelGeometry>(geometry));
}

void *SkSurfaceProps_new_3(const void *props) {
    return new SkSurfaceProps(* static_cast<const SkSurfaceProps *>(props));
}

void SkSurfaceProps_delete(void *surface_props) {
    delete static_cast<SkSurfaceProps *>(surface_props);
}

sk_surface_props_t SkSurfaceProps_cloneWithPixelGeometry(void *surface_props, int newPixelGeometry) {
    return static_sk_surface_props_make(static_cast<SkSurfaceProps *>(surface_props)->cloneWithPixelGeometry(static_cast<SkPixelGeometry>(newPixelGeometry)));
}

uint32_t SkSurfaceProps_flags(void *surface_props) {
    return static_cast<SkSurfaceProps *>(surface_props)->flags();
}

int SkSurfaceProps_pixelGeometry(void *surface_props) {
    return static_cast<SkSurfaceProps *>(surface_props)->pixelGeometry();
}

bool SkSurfaceProps_isUseDeviceIndependentFonts(void *surface_props) {
    return static_cast<SkSurfaceProps *>(surface_props)->isUseDeviceIndependentFonts();
}

bool SkSurfaceProps_isAlwaysDither(void *surface_props) {
    return static_cast<SkSurfaceProps *>(surface_props)->isAlwaysDither();
}

}
