//
// Created by Codex on 2026/05/23.
//

#include "sk_arc.h"

#include "include/core/SkArc.h"
#include "include/core/SkRect.h"

extern "C" {

reskia_arc_t *SkArc_new() {
    return reinterpret_cast<reskia_arc_t *>(new SkArc());
}

reskia_arc_t *SkArc_newCopy(const reskia_arc_t *arc) {
    if (arc == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_arc_t *>(new SkArc(*reinterpret_cast<const SkArc *>(arc)));
}

void SkArc_delete(reskia_arc_t *arc) {
    delete reinterpret_cast<SkArc *>(arc);
}

const reskia_rect_t *SkArc_oval(const reskia_arc_t *arc) {
    if (arc == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_rect_t *>(&reinterpret_cast<const SkArc *>(arc)->oval());
}

float SkArc_startAngle(const reskia_arc_t *arc) {
    if (arc == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<const SkArc *>(arc)->startAngle();
}

float SkArc_sweepAngle(const reskia_arc_t *arc) {
    if (arc == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<const SkArc *>(arc)->sweepAngle();
}

bool SkArc_isWedge(const reskia_arc_t *arc) {
    if (arc == nullptr) {
        return false;
    }
    return reinterpret_cast<const SkArc *>(arc)->isWedge();
}

reskia_arc_t *SkArc_Make(const reskia_rect_t *oval, float startAngleDegrees, float sweepAngleDegrees, bool useCenter) {
    if (oval == nullptr) {
        return nullptr;
    }
    SkArc arc = SkArc::Make(
            *reinterpret_cast<const SkRect *>(oval),
            startAngleDegrees,
            sweepAngleDegrees,
            useCenter);
    return reinterpret_cast<reskia_arc_t *>(new SkArc(arc));
}

reskia_arc_t *SkArc_MakeWithType(const reskia_rect_t *oval, float startAngleDegrees, float sweepAngleDegrees, reskia_arc_type_t type) {
    if (oval == nullptr) {
        return nullptr;
    }
    SkArc arc = SkArc::Make(
            *reinterpret_cast<const SkRect *>(oval),
            startAngleDegrees,
            sweepAngleDegrees,
            static_cast<SkArc::Type>(type != 0));
    return reinterpret_cast<reskia_arc_t *>(new SkArc(arc));
}

}
