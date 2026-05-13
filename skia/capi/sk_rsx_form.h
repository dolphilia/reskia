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

void SkRSXform_delete(reskia_rsxform_t *rsx_form); // NULL rsx_form is no-op.
bool SkRSXform_rectStaysRect(reskia_rsxform_t *rsx_form); // NULL rsx_form returns false.
void SkRSXform_setIdentity(reskia_rsxform_t *rsx_form); // NULL rsx_form is no-op.
void SkRSXform_set(reskia_rsxform_t *rsx_form, float scos, float ssin, float tx, float ty); // NULL rsx_form is no-op.
void SkRSXform_toQuad(reskia_rsxform_t *rsx_form, float width, float height, reskia_point_t *quad); // rsx_form and quad[4] are required; invalid input is no-op.
void SkRSXform_toQuadWithSize(reskia_rsxform_t *rsx_form, const reskia_size_t *size, reskia_point_t *quad); // rsx_form, size, and quad[4] are required; invalid input is no-op.
void SkRSXform_toTriStrip(reskia_rsxform_t *rsx_form, float width, float height, reskia_point_t *strip); // rsx_form and strip[4] are required; invalid input is no-op.

// static

sk_rsx_form_t SkRSXform_Make(float scos, float ssin, float tx, float ty); // Returns a caller-owned SkRSXform handle.
sk_rsx_form_t SkRSXform_MakeFromRadians(float scale, float radians, float tx, float ty, float ax, float ay); // Returns a caller-owned SkRSXform handle.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_RSX_FORM_H
