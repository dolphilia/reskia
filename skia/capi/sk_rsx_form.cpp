//
// Created by dolphilia on 2024/01/10.
//

#include "sk_rsx_form.h"

#include "include/core/SkRSXform.h"

#include "../handles/static_sk_rsx_form.h"

#include "../handles/static_sk_rsx_form-internal.h"

extern "C" {

void SkRSXform_delete(reskia_rsxform_t *rsx_form) {
    delete reinterpret_cast<SkRSXform *>(rsx_form);
}

bool SkRSXform_rectStaysRect(reskia_rsxform_t *rsx_form) {
    return reinterpret_cast<SkRSXform *>(rsx_form)->rectStaysRect();
}

void SkRSXform_setIdentity(reskia_rsxform_t *rsx_form) {
    reinterpret_cast<SkRSXform *>(rsx_form)->setIdentity();
}

void SkRSXform_set(reskia_rsxform_t *rsx_form, float scos, float ssin, float tx, float ty) {
    reinterpret_cast<SkRSXform *>(rsx_form)->set(scos, ssin, tx, ty);
}

void SkRSXform_toQuad(reskia_rsxform_t *rsx_form, float width, float height, reskia_point_t *quad) {
    reinterpret_cast<SkRSXform *>(rsx_form)->toQuad(width, height, reinterpret_cast<SkPoint *>(quad));
}

void SkRSXform_toQuadWithSize(reskia_rsxform_t *rsx_form, const reskia_size_t *size, reskia_point_t *quad) {
    reinterpret_cast<SkRSXform *>(rsx_form)->toQuad(* reinterpret_cast<const SkSize *>(size), reinterpret_cast<SkPoint *>(quad));
}

void SkRSXform_toTriStrip(reskia_rsxform_t *rsx_form, float width, float height, reskia_point_t *strip) {
    reinterpret_cast<SkRSXform *>(rsx_form)->toTriStrip(width, height, reinterpret_cast<SkPoint *>(strip));
}

// static

sk_rsx_form_t SkRSXform_Make(float scos, float ssin, float tx, float ty) {
    return static_sk_rsx_form_make(SkRSXform::Make(scos, ssin, tx, ty));
}

sk_rsx_form_t SkRSXform_MakeFromRadians(float scale, float radians, float tx, float ty, float ax, float ay) {
    return static_sk_rsx_form_make(SkRSXform::MakeFromRadians(scale, radians, tx, ty, ax, ay));
}

}
