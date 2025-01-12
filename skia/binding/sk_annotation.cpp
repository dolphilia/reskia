//
// Created by dolphilia on 2024/01/05.
//

#include "sk_annotation.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkAnnotation.h"

#ifdef __cplusplus
extern "C" {
#endif

void SkAnnotation_SkAnnotateLinkToDestination(void * canvas, const void * rect, void * data) {
    SkAnnotateLinkToDestination(static_cast<SkCanvas *>(canvas), * static_cast<const SkRect *>(rect), static_cast<SkData *>(data));
}

void SkAnnotation_SkAnnotateNamedDestination(void * canvas, const void * point, void * data) {
    SkAnnotateNamedDestination(static_cast<SkCanvas *>(canvas), * static_cast<const SkPoint *>(point), static_cast<SkData *>(data));
}

void SkAnnotation_SkAnnotateRectWithURL(void * canvas, const void * rect, void * data) {
    SkAnnotateRectWithURL(static_cast<SkCanvas *>(canvas), * static_cast<const SkRect *>(rect), static_cast<SkData *>(data));
}

#ifdef __cplusplus
}
#endif