//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_RSX_FORM_H
#define RAIA_SKIA_SK_RSX_FORM_H

#include "../handles/static_sk_rsx_form.h"

typedef struct reskia_point_t reskia_point_t;
typedef struct reskia_rsxform_t reskia_rsxform_t;
typedef struct reskia_size_t reskia_size_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkRSXform_delete(reskia_rsxform_t *rsx_form); // (SkRSXform *rsx_form)
bool SkRSXform_rectStaysRect(reskia_rsxform_t *rsx_form); // (SkRSXform *rsx_form) -> bool
void SkRSXform_setIdentity(reskia_rsxform_t *rsx_form); // (SkRSXform *rsx_form)
void SkRSXform_set(reskia_rsxform_t *rsx_form, float scos, float ssin, float tx, float ty); // (SkRSXform *rsx_form, SkScalar scos, SkScalar ssin, SkScalar tx, SkScalar ty)
void SkRSXform_toQuad(reskia_rsxform_t *rsx_form, float width, float height, reskia_point_t *quad); // (SkRSXform *rsx_form, SkScalar width, SkScalar height, SkPoint quad[4])
void SkRSXform_toQuadWithSize(reskia_rsxform_t *rsx_form, const reskia_size_t *size, reskia_point_t *quad); // (SkRSXform *rsx_form, const SkSize *size, SkPoint quad[4])
void SkRSXform_toTriStrip(reskia_rsxform_t *rsx_form, float width, float height, reskia_point_t *strip); // (SkRSXform *rsx_form, SkScalar width, SkScalar height, SkPoint strip[4])

// static

sk_rsx_form_t SkRSXform_Make(float scos, float ssin, float tx, float ty); // (SkScalar scos, SkScalar ssin, SkScalar tx, SkScalar ty) -> sk_rsx_form_t
sk_rsx_form_t SkRSXform_MakeFromRadians(float scale, float radians, float tx, float ty, float ax, float ay); // (SkScalar scale, SkScalar radians, SkScalar tx, SkScalar ty, SkScalar ax, SkScalar ay) -> sk_rsx_form_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_RSX_FORM_H
