//
// Created by dolphilia on 2024/01/10.
//

#include "sk_r_rect.h"

#include "include/core/SkRRect.h"

#include "../static/static_sk_string.h"
#include "../static/static_sk_r_rect.h"
#include "../static/static_sk_point.h"

#include "../static/static_sk_point-internal.h"
#include "../static/static_sk_r_rect-internal.h"
#include "../static/static_sk_string-internal.h"

extern "C" {

//SkRRect & operator=(const SkRRect &rrect)

reskia_r_rect_t *SkRRect_new() {
    return reinterpret_cast<reskia_r_rect_t *>(new SkRRect());
}

reskia_r_rect_t *SkRRect_new_2(const reskia_r_rect_t *rrect) {
    return reinterpret_cast<reskia_r_rect_t *>(new SkRRect(*reinterpret_cast<const SkRRect *>(rrect)));
}

void SkRRect_delete(reskia_r_rect_t *rrect) {
    delete reinterpret_cast<SkRRect *>(rrect);
}

reskia_r_rect_type_t SkRRect_getType(reskia_r_rect_t *rrect) {
    return static_cast<reskia_r_rect_type_t>(reinterpret_cast<SkRRect *>(rrect)->getType());
}

reskia_r_rect_type_t SkRRect_type(reskia_r_rect_t *rrect) {
    return static_cast<reskia_r_rect_type_t>(reinterpret_cast<SkRRect *>(rrect)->type());
}

bool SkRRect_isEmpty(reskia_r_rect_t *rrect) {
    return reinterpret_cast<SkRRect *>(rrect)->isEmpty();
}

bool SkRRect_isRect(reskia_r_rect_t *rrect) {
    return reinterpret_cast<SkRRect *>(rrect)->isRect();
}

bool SkRRect_isOval(reskia_r_rect_t *rrect) {
    return reinterpret_cast<SkRRect *>(rrect)->isOval();
}

bool SkRRect_isSimple(reskia_r_rect_t *rrect) {
    return reinterpret_cast<SkRRect *>(rrect)->isSimple();
}

bool SkRRect_isNinePatch(reskia_r_rect_t *rrect) {
    return reinterpret_cast<SkRRect *>(rrect)->isNinePatch();
}

bool SkRRect_isComplex(reskia_r_rect_t *rrect) {
    return reinterpret_cast<SkRRect *>(rrect)->isComplex();
}

float SkRRect_width(reskia_r_rect_t *rrect) {
    return reinterpret_cast<SkRRect *>(rrect)->width();
}

float SkRRect_height(reskia_r_rect_t *rrect) {
    return reinterpret_cast<SkRRect *>(rrect)->height();
}

sk_point_t SkRRect_getSimpleRadii(reskia_r_rect_t *rrect) {
    return static_sk_point_make(reinterpret_cast<SkRRect *>(rrect)->getSimpleRadii());
}

void SkRRect_setEmpty(reskia_r_rect_t *rrect) {
    reinterpret_cast<SkRRect *>(rrect)->setEmpty();
}

void SkRRect_setRect(reskia_r_rect_t *rrect, const reskia_rect_t *rect) {
    reinterpret_cast<SkRRect *>(rrect)->setRect(* reinterpret_cast<const SkRect *>(rect));
}

void SkRRect_setOval(reskia_r_rect_t *rrect, const reskia_rect_t *oval) {
    reinterpret_cast<SkRRect *>(rrect)->setOval(* reinterpret_cast<const SkRect *>(oval));
}

void SkRRect_setRectXY(reskia_r_rect_t *rrect, const reskia_rect_t *rect, float xRad, float yRad) {
    reinterpret_cast<SkRRect *>(rrect)->setRectXY(* reinterpret_cast<const SkRect *>(rect), xRad, yRad);
}

void SkRRect_setNinePatch(reskia_r_rect_t *rrect, const reskia_rect_t *rect, float leftRad, float topRad, float rightRad, float bottomRad) {
    reinterpret_cast<SkRRect *>(rrect)->setNinePatch(* reinterpret_cast<const SkRect *>(rect), leftRad, topRad, rightRad, bottomRad);
}

void SkRRect_setRectRadii(reskia_r_rect_t *rrect, const reskia_rect_t *rect, const reskia_vector_t *radii) {
    reinterpret_cast<SkRRect *>(rrect)->setRectRadii(* reinterpret_cast<const SkRect *>(rect), reinterpret_cast<const SkVector *>(radii));
}

const reskia_rect_t *SkRRect_rect(reskia_r_rect_t *rrect) {
    return reinterpret_cast<const reskia_rect_t *>(
            &reinterpret_cast<SkRRect *>(rrect)->rect());
}

sk_point_t SkRRect_radii(reskia_r_rect_t *rrect, reskia_r_rect_corner_t corner) {
    return static_sk_point_make(reinterpret_cast<SkRRect *>(rrect)->radii(static_cast<SkRRect::Corner>(corner)));
}

const reskia_rect_t *SkRRect_getBounds(reskia_r_rect_t *rrect) {
    return reinterpret_cast<const reskia_rect_t *>(
            &reinterpret_cast<SkRRect *>(rrect)->getBounds());
}

void SkRRect_inset(reskia_r_rect_t *rrect, float dx, float dy, reskia_r_rect_t *dst) {
    reinterpret_cast<SkRRect *>(rrect)->inset(dx, dy, reinterpret_cast<SkRRect *>(dst));
}

void SkRRect_inset_2(reskia_r_rect_t *rrect, float dx, float dy) {
    reinterpret_cast<SkRRect *>(rrect)->inset(dx, dy);
}

void SkRRect_outset(reskia_r_rect_t *rrect, float dx, float dy, reskia_r_rect_t *dst) {
    reinterpret_cast<SkRRect *>(rrect)->outset(dx, dy, reinterpret_cast<SkRRect *>(dst));
}

void SkRRect_outset_2(reskia_r_rect_t *rrect, float dx, float dy) {
    reinterpret_cast<SkRRect *>(rrect)->outset(dx, dy);
}

void SkRRect_offset(reskia_r_rect_t *rrect, float dx, float dy) {
    reinterpret_cast<SkRRect *>(rrect)->offset(dx, dy);
}

sk_r_rect_t SkRRect_makeOffset(reskia_r_rect_t *rrect, float dx, float dy) {
    return static_sk_r_rect_make(reinterpret_cast<SkRRect *>(rrect)->makeOffset(dx, dy));
}

bool SkRRect_contains(reskia_r_rect_t *rrect, const reskia_rect_t *rect) {
    return reinterpret_cast<SkRRect *>(rrect)->contains(* reinterpret_cast<const SkRect *>(rect));
}

bool SkRRect_isValid(reskia_r_rect_t *rrect) {
    return reinterpret_cast<SkRRect *>(rrect)->isValid();
}

size_t SkRRect_writeToMemory(reskia_r_rect_t *rrect, void *buffer) {
    return reinterpret_cast<SkRRect *>(rrect)->writeToMemory(buffer);
}

size_t SkRRect_readFromMemory(reskia_r_rect_t *rrect, const void *buffer, size_t length) {
    return reinterpret_cast<SkRRect *>(rrect)->readFromMemory(buffer, length);
}

bool SkRRect_transform(reskia_r_rect_t *rrect, const reskia_matrix_t *matrix, reskia_r_rect_t *dst) {
    return reinterpret_cast<SkRRect *>(rrect)->transform(* reinterpret_cast<const SkMatrix *>(matrix), reinterpret_cast<SkRRect *>(dst));
}

void SkRRect_dump(reskia_r_rect_t *rrect, bool asHex) {
    reinterpret_cast<SkRRect *>(rrect)->dump(asHex);
}

sk_string_t SkRRect_dumpToString(reskia_r_rect_t *rrect, bool asHex) {
    return static_sk_string_make(reinterpret_cast<SkRRect *>(rrect)->dumpToString(asHex));
}

void SkRRect_dump_2(reskia_r_rect_t *rrect) {
    reinterpret_cast<SkRRect *>(rrect)->dump();
}

void SkRRect_dumpHex(reskia_r_rect_t *rrect) {
    reinterpret_cast<SkRRect *>(rrect)->dumpHex();
}

// static

sk_r_rect_t SkRRect_MakeEmpty() {
    return static_sk_r_rect_make(SkRRect::MakeEmpty());
}

sk_r_rect_t SkRRect_MakeRect(const reskia_rect_t *r) {
    return static_sk_r_rect_make(SkRRect::MakeRect(* reinterpret_cast<const SkRect *>(r)));
}

sk_r_rect_t SkRRect_MakeOval(const reskia_rect_t *oval) {
    return static_sk_r_rect_make(SkRRect::MakeOval(* reinterpret_cast<const SkRect *>(oval)));
}

sk_r_rect_t SkRRect_MakeRectXY(const reskia_rect_t *rect, float xRad, float yRad) {
    return static_sk_r_rect_make(SkRRect::MakeRectXY(*reinterpret_cast<const SkRect *>(rect), xRad, yRad));
}

}
