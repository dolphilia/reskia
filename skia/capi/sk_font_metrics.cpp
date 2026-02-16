//
// Created by dolphilia on 2024/01/08.
//

#include "sk_font_metrics.h"

#include "include/core/SkFontMetrics.h"

extern "C" {

void SkFontMetrics_delete(reskia_font_metrics_t *font_metrics) {
    delete reinterpret_cast<SkFontMetrics *>(font_metrics);
}

bool SkFontMetrics_hasUnderlineThickness(reskia_font_metrics_t *font_metrics, float *thickness) {
    return reinterpret_cast<SkFontMetrics *>(font_metrics)->hasUnderlineThickness(thickness);
}

bool SkFontMetrics_hasUnderlinePosition(reskia_font_metrics_t *font_metrics, float *position) {
    return reinterpret_cast<SkFontMetrics *>(font_metrics)->hasUnderlinePosition(position);
}

bool SkFontMetrics_hasStrikeoutThickness(reskia_font_metrics_t *font_metrics, float *thickness) {
    return reinterpret_cast<SkFontMetrics *>(font_metrics)->hasStrikeoutThickness(thickness);
}

bool SkFontMetrics_hasStrikeoutPosition(reskia_font_metrics_t *font_metrics, float *position) {
    return reinterpret_cast<SkFontMetrics *>(font_metrics)->hasStrikeoutPosition(position);
}

bool SkFontMetrics_hasBounds(reskia_font_metrics_t *font_metrics) {
    return reinterpret_cast<SkFontMetrics *>(font_metrics)->hasBounds();
}

}
