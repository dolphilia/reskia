//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_FONT_METRICS_H
#define RAIA_SKIA_SK_FONT_METRICS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_font_metrics_t reskia_font_metrics_t;

void SkFontMetrics_delete(reskia_font_metrics_t *font_metrics); // No-op for NULL input.
bool SkFontMetrics_equals(reskia_font_metrics_t *font_metrics, const reskia_font_metrics_t *other); // NULL input returns false.
bool SkFontMetrics_hasUnderlineThickness(reskia_font_metrics_t *font_metrics, float *thickness); // thickness must be non-NULL. Returns false for invalid input.
bool SkFontMetrics_hasUnderlinePosition(reskia_font_metrics_t *font_metrics, float *position); // position must be non-NULL. Returns false for invalid input.
bool SkFontMetrics_hasStrikeoutThickness(reskia_font_metrics_t *font_metrics, float *thickness); // thickness must be non-NULL. Returns false for invalid input.
bool SkFontMetrics_hasStrikeoutPosition(reskia_font_metrics_t *font_metrics, float *position); // position must be non-NULL. Returns false for invalid input.
bool SkFontMetrics_hasBounds(reskia_font_metrics_t *font_metrics); // Returns false for NULL input.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_FONT_METRICS_H
