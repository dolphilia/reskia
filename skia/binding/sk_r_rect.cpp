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

void *SkRRect_new() {
    return new SkRRect();
}

void *SkRRect_new_2(const void *rrect) {
    return new SkRRect(* static_cast<const SkRRect *>(rrect));
}

void SkRRect_delete(void *rrect) {
    delete static_cast<SkRRect *>(rrect);
}

int getType(void *rrect) {
    return static_cast<SkRRect *>(rrect)->getType();
}

int type(void *rrect) {
    return static_cast<SkRRect *>(rrect)->type();
}

bool SkRRect_isEmpty(void *rrect) {
    return static_cast<SkRRect *>(rrect)->isEmpty();
}

bool SkRRect_isRect(void *rrect) {
    return static_cast<SkRRect *>(rrect)->isRect();
}

bool SkRRect_isOval(void *rrect) {
    return static_cast<SkRRect *>(rrect)->isOval();
}

bool SkRRect_isSimple(void *rrect) {
    return static_cast<SkRRect *>(rrect)->isSimple();
}

bool SkRRect_isNinePatch(void *rrect) {
    return static_cast<SkRRect *>(rrect)->isNinePatch();
}

bool SkRRect_isComplex(void *rrect) {
    return static_cast<SkRRect *>(rrect)->isComplex();
}

float SkRRect_width(void *rrect) {
    return static_cast<SkRRect *>(rrect)->width();
}

float SkRRect_height(void *rrect) {
    return static_cast<SkRRect *>(rrect)->height();
}

sk_point_t SkRRect_getSimpleRadii(void *rrect) {
    return static_sk_point_make(static_cast<SkRRect *>(rrect)->getSimpleRadii());
}

void SkRRect_setEmpty(void *rrect) {
    static_cast<SkRRect *>(rrect)->setEmpty();
}

void SkRRect_setRect(void *rrect, const void *rect) {
    static_cast<SkRRect *>(rrect)->setRect(* static_cast<const SkRect *>(rect));
}

void SkRRect_setOval(void *rrect, const void *oval) {
    static_cast<SkRRect *>(rrect)->setOval(* static_cast<const SkRect *>(oval));
}

void SkRRect_setRectXY(void *rrect, const void *rect, float xRad, float yRad) {
    static_cast<SkRRect *>(rrect)->setRectXY(* static_cast<const SkRect *>(rect), xRad, yRad);
}

void SkRRect_setNinePatch(void *rrect, const void *rect, float leftRad, float topRad, float rightRad, float bottomRad) {
    static_cast<SkRRect *>(rrect)->setNinePatch(* static_cast<const SkRect *>(rect), leftRad, topRad, rightRad, bottomRad);
}

void SkRRect_setRectRadii(void *rrect, const void *rect, const void * radii) {
    static_cast<SkRRect *>(rrect)->setRectRadii(* static_cast<const SkRect *>(rect), static_cast<const SkVector *>(radii));
}

const void * SkRRect_rect(void *rrect) {
    return &static_cast<SkRRect *>(rrect)->rect();
}

sk_point_t SkRRect_radii(void *rrect, int corner) {
    return static_sk_point_make(static_cast<SkRRect *>(rrect)->radii(static_cast<SkRRect::Corner>(corner)));
}

const void * SkRRect_getBounds(void *rrect) {
    return &static_cast<SkRRect *>(rrect)->getBounds();
}

void SkRRect_inset(void *rrect, float dx, float dy, void *dst) {
    static_cast<SkRRect *>(rrect)->inset(dx, dy, static_cast<SkRRect *>(dst));
}

void SkRRect_inset_2(void *rrect, float dx, float dy) {
    static_cast<SkRRect *>(rrect)->inset(dx, dy);
}

void SkRRect_outset(void *rrect, float dx, float dy, void *dst) {
    static_cast<SkRRect *>(rrect)->outset(dx, dy, static_cast<SkRRect *>(dst));
}

void SkRRect_outset_2(void *rrect, float dx, float dy) {
    static_cast<SkRRect *>(rrect)->outset(dx, dy);
}

void SkRRect_offset(void *rrect, float dx, float dy) {
    static_cast<SkRRect *>(rrect)->offset(dx, dy);
}

sk_r_rect_t SkRRect_makeOffset(void *rrect, float dx, float dy) {
    return static_sk_r_rect_make(static_cast<SkRRect *>(rrect)->makeOffset(dx, dy));
}

bool SkRRect_contains(void *rrect, const void *rect) {
    return static_cast<SkRRect *>(rrect)->contains(* static_cast<const SkRect *>(rect));
}

bool SkRRect_isValid(void *rrect) {
    return static_cast<SkRRect *>(rrect)->isValid();
}

size_t SkRRect_writeToMemory(void *rrect, void *buffer) {
    return static_cast<SkRRect *>(rrect)->writeToMemory(buffer);
}

size_t SkRRect_readFromMemory(void *rrect, const void *buffer, size_t length) {
    return static_cast<SkRRect *>(rrect)->readFromMemory(buffer, length);
}

bool SkRRect_transform(void *rrect, const void *matrix, void *dst) {
    return static_cast<SkRRect *>(rrect)->transform(* static_cast<const SkMatrix *>(matrix), static_cast<SkRRect *>(dst));
}

void SkRRect_dump(void *rrect, bool asHex) {
    static_cast<SkRRect *>(rrect)->dump(asHex);
}

sk_string_t SkRRect_dumpToString(void *rrect, bool asHex) {
    return static_sk_string_make(static_cast<SkRRect *>(rrect)->dumpToString(asHex));
}

void SkRRect_dump_2(void *rrect) {
    static_cast<SkRRect *>(rrect)->dump();
}

void SkRRect_dumpHex(void *rrect) {
    static_cast<SkRRect *>(rrect)->dumpHex();
}

// static

sk_r_rect_t SkRRect_MakeEmpty() {
    return static_sk_r_rect_make(SkRRect::MakeEmpty());
}

sk_r_rect_t SkRRect_MakeRect(const void *r) {
    return static_sk_r_rect_make(SkRRect::MakeRect(* static_cast<const SkRect *>(r)));
}

sk_r_rect_t SkRRect_MakeOval(const void *oval) {
    return static_sk_r_rect_make(SkRRect::MakeOval(* static_cast<const SkRect *>(oval)));
}

sk_r_rect_t SkRRect_MakeRectXY(const void *rect, float xRad, float yRad) {
    return static_sk_r_rect_make(SkRRect::MakeRectXY(* (const SkRect *)rect, xRad, yRad));
}

}
