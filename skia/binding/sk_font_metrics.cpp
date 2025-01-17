//
// Created by dolphilia on 2024/01/08.
//

#include "sk_font_metrics.h"

#include "include/core/SkFontMetrics.h"

extern "C" {

void SkFontMetrics_delete(void *font_metrics) {
    delete static_cast<SkFontMetrics *>(font_metrics);
}

bool SkFontMetrics_hasUnderlineThickness(void *font_metrics, void *thickness) {
    return static_cast<SkFontMetrics *>(font_metrics)->hasUnderlineThickness(static_cast<SkScalar *>(thickness));
}

bool SkFontMetrics_hasUnderlinePosition(void *font_metrics, void *position) {
    return static_cast<SkFontMetrics *>(font_metrics)->hasUnderlinePosition(static_cast<SkScalar *>(position));
}

bool SkFontMetrics_hasStrikeoutThickness(void *font_metrics, void *thickness) {
    return static_cast<SkFontMetrics *>(font_metrics)->hasStrikeoutThickness(static_cast<SkScalar *>(thickness));
}

bool SkFontMetrics_hasStrikeoutPosition(void *font_metrics, void *position) {
    return static_cast<SkFontMetrics *>(font_metrics)->hasStrikeoutPosition(static_cast<SkScalar *>(position));
}

bool SkFontMetrics_hasBounds(void *font_metrics) {
    return static_cast<SkFontMetrics *>(font_metrics)->hasBounds();
}

}