//
// Created by dolphilia on 2024/01/10.
//

#include "sk_region.h"

#include "include/core/SkRegion.h"

extern "C" {

//SkRegion & operator=(const SkRegion &region)
//bool operator==(const SkRegion &other)
//bool operator!=(const SkRegion &other)

reskia_region_t *SkRegion_new() {
    return reinterpret_cast<reskia_region_t *>(new SkRegion());
}

reskia_region_t *SkRegion_new_2(const reskia_region_t *region) {
    return reinterpret_cast<reskia_region_t *>(
            new SkRegion(*reinterpret_cast<const SkRegion *>(region)));
}

reskia_region_t *SkRegion_new_3(const reskia_i_rect_t *rect) {
    return reinterpret_cast<reskia_region_t *>(
            new SkRegion(*reinterpret_cast<const SkIRect *>(rect)));
}

void SkRegion_delete(reskia_region_t *region) {
    delete reinterpret_cast<SkRegion *>(region);
}

bool SkRegion_set(reskia_region_t *region, const reskia_region_t *src) {
    return reinterpret_cast<SkRegion *>(region)->set(* reinterpret_cast<const SkRegion *>(src));
}

void SkRegion_swap(reskia_region_t *region, reskia_region_t *other) {
    return reinterpret_cast<SkRegion *>(region)->swap(* reinterpret_cast<SkRegion *>(other));
}

bool SkRegion_isEmpty(reskia_region_t *region) {
    return reinterpret_cast<SkRegion *>(region)->isEmpty();
}

bool SkRegion_isRect(reskia_region_t *region) {
    return reinterpret_cast<SkRegion *>(region)->isRect();
}

bool SkRegion_isComplex(reskia_region_t *region) {
    return reinterpret_cast<SkRegion *>(region)->isComplex();
}

const reskia_i_rect_t *SkRegion_getBounds(reskia_region_t *region) {
    return reinterpret_cast<const reskia_i_rect_t *>(
            &reinterpret_cast<SkRegion *>(region)->getBounds());
}

int SkRegion_computeRegionComplexity(reskia_region_t *region) {
    return reinterpret_cast<SkRegion *>(region)->computeRegionComplexity();
}

bool SkRegion_getBoundaryPath(reskia_region_t *region, reskia_path_t *path) {
    return reinterpret_cast<SkRegion *>(region)->getBoundaryPath(reinterpret_cast<SkPath *>(path));
}

bool SkRegion_setEmpty(reskia_region_t *region) {
    return reinterpret_cast<SkRegion *>(region)->setEmpty();
}

bool SkRegion_setRect(reskia_region_t *region, const reskia_i_rect_t *rect) {
    return reinterpret_cast<SkRegion *>(region)->setRect(* reinterpret_cast<const SkIRect *>(rect));
}

bool SkRegion_setRects(reskia_region_t *region, const reskia_i_rect_t *rects, int count) {
    return reinterpret_cast<SkRegion *>(region)->setRects(reinterpret_cast<const SkIRect *>(rects), count);
}

bool SkRegion_setRegion(reskia_region_t *region, const reskia_region_t *region_2) {
    return reinterpret_cast<SkRegion *>(region)->setRegion(* reinterpret_cast<const SkRegion *>(region_2));
}

bool SkRegion_setPath(reskia_region_t *region, const reskia_path_t *path, const reskia_region_t *clip) {
    return reinterpret_cast<SkRegion *>(region)->setPath(* reinterpret_cast<const SkPath *>(path), * reinterpret_cast<const SkRegion *>(clip));
}

bool SkRegion_intersects(reskia_region_t *region, const reskia_i_rect_t *rect) {
    return reinterpret_cast<SkRegion *>(region)->intersects(* reinterpret_cast<const SkIRect *>(rect));
}

bool SkRegion_intersects_2(reskia_region_t *region, const reskia_region_t *other) {
    return reinterpret_cast<SkRegion *>(region)->intersects(* reinterpret_cast<const SkRegion *>(other));
}

bool SkRegion_contains(reskia_region_t *region, int32_t x, int32_t y) {
    return reinterpret_cast<SkRegion *>(region)->contains(x, y);
}

bool SkRegion_contains_2(reskia_region_t *region, const reskia_i_rect_t *other) {
    return reinterpret_cast<SkRegion *>(region)->contains(* reinterpret_cast<const SkIRect *>(other));
}

bool SkRegion_contains_3(reskia_region_t *region, const reskia_region_t *other) {
    return reinterpret_cast<SkRegion *>(region)->contains(* reinterpret_cast<const SkRegion *>(other));
}

bool SkRegion_quickContains(reskia_region_t *region, const reskia_i_rect_t *r) {
    return reinterpret_cast<SkRegion *>(region)->quickContains(* reinterpret_cast<const SkIRect *>(r));
}

bool SkRegion_quickReject(reskia_region_t *region, const reskia_i_rect_t *rect) {
    return reinterpret_cast<SkRegion *>(region)->quickReject(* reinterpret_cast<const SkIRect *>(rect));
}

bool SkRegion_quickReject_2(reskia_region_t *region, const reskia_region_t *rgn) {
    return reinterpret_cast<SkRegion *>(region)->quickReject(* reinterpret_cast<const SkRegion *>(rgn));
}

void SkRegion_translate(reskia_region_t *region, int dx, int dy) {
    reinterpret_cast<SkRegion *>(region)->translate(dx, dy);
}

void SkRegion_translate_2(reskia_region_t *region, int dx, int dy, reskia_region_t *dst) {
    reinterpret_cast<SkRegion *>(region)->translate(dx, dy, reinterpret_cast<SkRegion *>(dst));
}

bool SkRegion_op(reskia_region_t *region, const reskia_i_rect_t *rect, int op) {
    return reinterpret_cast<SkRegion *>(region)->op(* reinterpret_cast<const SkIRect *>(rect), static_cast<SkRegion::Op>(op));
}

bool SkRegion_op_2(reskia_region_t *region, const reskia_region_t *rgn, int op) {
    return reinterpret_cast<SkRegion *>(region)->op(* reinterpret_cast<const SkRegion *>(rgn), static_cast<SkRegion::Op>(op));
}

bool SkRegion_op_3(reskia_region_t *region, const reskia_i_rect_t *rect, const reskia_region_t *rgn, int op) {
    return reinterpret_cast<SkRegion *>(region)->op(* reinterpret_cast<const SkIRect *>(rect), * reinterpret_cast<const SkRegion *>(rgn), static_cast<SkRegion::Op>(op));
}

bool SkRegion_op_4(reskia_region_t *region, const reskia_region_t *rgn, const reskia_i_rect_t *rect, int op) {
    return reinterpret_cast<SkRegion *>(region)->op(* reinterpret_cast<const SkRegion *>(rgn), * reinterpret_cast<const SkIRect *>(rect), static_cast<SkRegion::Op>(op));
}

bool SkRegion_op_5(reskia_region_t *region, const reskia_region_t *rgna, const reskia_region_t *rgnb, int op) {
    return reinterpret_cast<SkRegion *>(region)->op(* reinterpret_cast<const SkRegion *>(rgna), * reinterpret_cast<const SkRegion *>(rgnb), static_cast<SkRegion::Op>(op));
}

size_t SkRegion_writeToMemory(reskia_region_t *region, void *buffer) {
    return reinterpret_cast<SkRegion *>(region)->writeToMemory(buffer);
}

size_t SkRegion_readFromMemory(reskia_region_t *region, const void *buffer, size_t length) {
    return reinterpret_cast<SkRegion *>(region)->readFromMemory(buffer, length);
}

}
