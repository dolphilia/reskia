//
// Created by dolphilia on 2024/01/10.
//

#include "sk_rsx_form.h"

#include "include/core/SkRSXform.h"

#include "../static/static_sk_rsx_form.h"

#include "../static/static_sk_rsx_form-internal.h"

extern "C" {

void SkRSXform_delete(void *rsx_form) {
    delete static_cast<SkRSXform *>(rsx_form);
}

bool SkRSXform_rectStaysRect(void *rsx_form) {
    return static_cast<SkRSXform *>(rsx_form)->rectStaysRect();
}

void SkRSXform_setIdentity(void *rsx_form) {
    static_cast<SkRSXform *>(rsx_form)->setIdentity();
}

void SkRSXform_set(void *rsx_form, float scos, float ssin, float tx, float ty) {
    static_cast<SkRSXform *>(rsx_form)->set(scos, ssin, tx, ty);
}

void SkRSXform_toQuad(void *rsx_form, float width, float height, void * quad) {
    static_cast<SkRSXform *>(rsx_form)->toQuad(width, height, static_cast<SkPoint *>(quad));
}

void SkRSXform_toQuad_2(void *rsx_form, const void *size, void * quad) {
    static_cast<SkRSXform *>(rsx_form)->toQuad(* static_cast<const SkSize *>(size), static_cast<SkPoint *>(quad));
}

void SkRSXform_toTriStrip(void *rsx_form, float width, float height, void * strip) {
    static_cast<SkRSXform *>(rsx_form)->toTriStrip(width, height, static_cast<SkPoint *>(strip));
}

// static

sk_rsx_form_t SkRSXform_Make(float scos, float ssin, float tx, float ty) {
    return static_sk_rsx_form_make(SkRSXform::Make(scos, ssin, tx, ty));
}

sk_rsx_form_t SkRSXform_MakeFromRadians(float scale, float radians, float tx, float ty, float ax, float ay) {
    return static_sk_rsx_form_make(SkRSXform::MakeFromRadians(scale, radians, tx, ty, ax, ay));
}

}
