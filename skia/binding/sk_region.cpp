//
// Created by dolphilia on 2024/01/10.
//

#include "sk_region.h"

#include "include/core/SkRegion.h"

extern "C" {

//SkRegion & operator=(const SkRegion &region)
//bool operator==(const SkRegion &other)
//bool operator!=(const SkRegion &other)

void *SkRegion_new() {
    return new SkRegion();
}

void *SkRegion_new_2(const void *region) {
    return new SkRegion(* static_cast<const SkRegion *>(region));
}

void *SkRegion_new_3(const void *rect) {
    return new SkRegion(* static_cast<const SkIRect *>(rect));
}

void SkRegion_delete(void *region) {
    delete static_cast<SkRegion *>(region);
}

bool SkRegion_set(void *region, const void *src) {
    return static_cast<SkRegion *>(region)->set(* static_cast<const SkRegion *>(src));
}

void SkRegion_swap(void *region, void *other) {
    return static_cast<SkRegion *>(region)->swap(* static_cast<SkRegion *>(other));
}

bool SkRegion_isEmpty(void *region) {
    return static_cast<SkRegion *>(region)->isEmpty();
}

bool SkRegion_isRect(void *region) {
    return static_cast<SkRegion *>(region)->isRect();
}

bool SkRegion_isComplex(void *region) {
    return static_cast<SkRegion *>(region)->isComplex();
}

const void * SkRegion_getBounds(void *region) {
    return &static_cast<SkRegion *>(region)->getBounds();
}

int SkRegion_computeRegionComplexity(void *region) {
    return static_cast<SkRegion *>(region)->computeRegionComplexity();
}

bool SkRegion_getBoundaryPath(void *region, void *path) {
    return static_cast<SkRegion *>(region)->getBoundaryPath(static_cast<SkPath *>(path));
}

bool SkRegion_setEmpty(void *region) {
    return static_cast<SkRegion *>(region)->setEmpty();
}

bool SkRegion_setRect(void *region, const void *rect) {
    return static_cast<SkRegion *>(region)->setRect(* static_cast<const SkIRect *>(rect));
}

bool SkRegion_setRects(void *region, const void * rects, int count) {
    return static_cast<SkRegion *>(region)->setRects(static_cast<const SkIRect *>(rects), count);
}

bool SkRegion_setRegion(void *region, const void *region_2) {
    return static_cast<SkRegion *>(region)->setRegion(* static_cast<const SkRegion *>(region_2));
}

bool SkRegion_setPath(void *region, const void *path, const void *clip) {
    return static_cast<SkRegion *>(region)->setPath(* static_cast<const SkPath *>(path), * static_cast<const SkRegion *>(clip));
}

bool SkRegion_intersects(void *region, const void *rect) {
    return static_cast<SkRegion *>(region)->intersects(* static_cast<const SkIRect *>(rect));
}

bool SkRegion_intersects_2(void *region, const void *other) {
    return static_cast<SkRegion *>(region)->intersects(* static_cast<const SkRegion *>(other));
}

bool SkRegion_contains(void *region, int32_t x, int32_t y) {
    return static_cast<SkRegion *>(region)->contains(x, y);
}

bool SkRegion_contains_2(void *region, const void *other) {
    return static_cast<SkRegion *>(region)->contains(* static_cast<const SkIRect *>(other));
}

bool SkRegion_contains_3(void *region, const void *other) {
    return static_cast<SkRegion *>(region)->contains(* static_cast<const SkRegion *>(other));
}

bool SkRegion_quickContains(void *region, const void *r) {
    return static_cast<SkRegion *>(region)->quickContains(* static_cast<const SkIRect *>(r));
}

bool SkRegion_quickReject(void *region, const void *rect) {
    return static_cast<SkRegion *>(region)->quickReject(* static_cast<const SkIRect *>(rect));
}

bool SkRegion_quickReject_2(void *region, const void *rgn) {
    return static_cast<SkRegion *>(region)->quickReject(* static_cast<const SkRegion *>(rgn));
}

void SkRegion_translate(void *region, int dx, int dy) {
    static_cast<SkRegion *>(region)->translate(dx, dy);
}

void SkRegion_translate_2(void *region, int dx, int dy, void *dst) {
    static_cast<SkRegion *>(region)->translate(dx, dy, static_cast<SkRegion *>(dst));
}

bool SkRegion_op(void *region, const void *rect, int op) {
    return static_cast<SkRegion *>(region)->op(* static_cast<const SkIRect *>(rect), static_cast<SkRegion::Op>(op));
}

bool SkRegion_op_2(void *region, const void *rgn, int op) {
    return static_cast<SkRegion *>(region)->op(* static_cast<const SkRegion *>(rgn), static_cast<SkRegion::Op>(op));
}

bool SkRegion_op_3(void *region, const void *rect, const void *rgn, int op) {
    return static_cast<SkRegion *>(region)->op(* static_cast<const SkIRect *>(rect), * static_cast<const SkRegion *>(rgn), static_cast<SkRegion::Op>(op));
}

bool SkRegion_op_4(void *region, const void *rgn, const void *rect, int op) {
    return static_cast<SkRegion *>(region)->op(* static_cast<const SkRegion *>(rgn), * static_cast<const SkIRect *>(rect), static_cast<SkRegion::Op>(op));
}

bool SkRegion_op_5(void *region, const void *rgna, const void *rgnb, int op) {
    return static_cast<SkRegion *>(region)->op(* static_cast<const SkRegion *>(rgna), * static_cast<const SkRegion *>(rgnb), static_cast<SkRegion::Op>(op));
}

size_t SkRegion_writeToMemory(void *region, void *buffer) {
    return static_cast<SkRegion *>(region)->writeToMemory(buffer);
}

size_t SkRegion_readFromMemory(void *region, const void *buffer, size_t length) {
    return static_cast<SkRegion *>(region)->readFromMemory(buffer, length);
}

}