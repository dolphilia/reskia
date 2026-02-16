//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_FONT_METRICS_H
#define RAIA_SKIA_SK_FONT_METRICS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_font_metrics_t reskia_font_metrics_t;

void SkFontMetrics_delete(reskia_font_metrics_t *font_metrics); // (SkFontMetrics *font_metrics)
bool SkFontMetrics_hasUnderlineThickness(reskia_font_metrics_t *font_metrics, float *thickness); // (SkFontMetrics *font_metrics, SkScalar *thickness) -> bool
bool SkFontMetrics_hasUnderlinePosition(reskia_font_metrics_t *font_metrics, float *position); // (SkFontMetrics *font_metrics, SkScalar *position) -> bool
bool SkFontMetrics_hasStrikeoutThickness(reskia_font_metrics_t *font_metrics, float *thickness); // (SkFontMetrics *font_metrics, SkScalar *thickness) -> bool
bool SkFontMetrics_hasStrikeoutPosition(reskia_font_metrics_t *font_metrics, float *position); // (SkFontMetrics *font_metrics, SkScalar *position) -> bool
bool SkFontMetrics_hasBounds(reskia_font_metrics_t *font_metrics); // (SkFontMetrics *font_metrics) -> bool

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_FONT_METRICS_H
