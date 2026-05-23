//
// Created by Codex on 2026/05/23.
//

#ifndef RAIA_SKIA_SK_ARC_H
#define RAIA_SKIA_SK_ARC_H

#include <stdbool.h>
#include <stdint.h>

typedef struct reskia_arc_t reskia_arc_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef int32_t reskia_arc_type_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_arc_t *SkArc_new();
reskia_arc_t *SkArc_newCopy(const reskia_arc_t *arc);
void SkArc_delete(reskia_arc_t *arc);
const reskia_rect_t *SkArc_oval(const reskia_arc_t *arc);
float SkArc_startAngle(const reskia_arc_t *arc);
float SkArc_sweepAngle(const reskia_arc_t *arc);
bool SkArc_isWedge(const reskia_arc_t *arc);
reskia_arc_t *SkArc_Make(const reskia_rect_t *oval, float startAngleDegrees, float sweepAngleDegrees, bool useCenter);
reskia_arc_t *SkArc_MakeWithType(const reskia_rect_t *oval, float startAngleDegrees, float sweepAngleDegrees, reskia_arc_type_t type);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_ARC_H
