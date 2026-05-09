#include "capi/sk_font_arguments.h"
#include "capi/sk_font_metrics.h"
#include "handles/static_sk_font_arguments.h"
#include "handles/static_sk_font_arguments_palette.h"
#include "handles/static_sk_font_arguments_variation_position.h"

#include "include/core/SkFontMetrics.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[font-arguments-metrics-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkFontArguments_delete(nullptr);

    if (!check(SkFontArguments_setCollectionIndex(nullptr, 0) == 0, "SkFontArguments_setCollectionIndex(nullptr)")) {
        return 1;
    }
    if (!check(SkFontArguments_setVariationDesignPosition(nullptr, 0) == 0, "SkFontArguments_setVariationDesignPosition(nullptr)")) {
        return 2;
    }
    if (!check(SkFontArguments_getCollectionIndex(nullptr) == 0, "SkFontArguments_getCollectionIndex(nullptr)")) {
        return 3;
    }
    if (!check(SkFontArguments_getVariationDesignPosition(nullptr) == 0, "SkFontArguments_getVariationDesignPosition(nullptr)")) {
        return 4;
    }
    if (!check(SkFontArguments_setPalette(nullptr, 0) == 0, "SkFontArguments_setPalette(nullptr)")) {
        return 5;
    }
    if (!check(SkFontArguments_getPalette(nullptr) == 0, "SkFontArguments_getPalette(nullptr)")) {
        return 6;
    }

    auto *arguments = SkFontArguments_new();
    if (!check(arguments != nullptr, "SkFontArguments_new()")) {
        return 7;
    }
    if (!check(SkFontArguments_setCollectionIndex(arguments, -1) == 0, "SkFontArguments_setCollectionIndex(negative)")) {
        SkFontArguments_delete(arguments);
        return 8;
    }

    const sk_font_arguments_t arguments_handle = SkFontArguments_setCollectionIndex(arguments, 2);
    if (!check(arguments_handle != 0 && static_sk_font_arguments_get_ptr(arguments_handle) != nullptr, "SkFontArguments_setCollectionIndex(valid)")) {
        SkFontArguments_delete(arguments);
        return 9;
    }
    static_sk_font_arguments_delete(arguments_handle);

    const sk_font_arguments_variation_position_t position_handle = SkFontArguments_getVariationDesignPosition(arguments);
    if (!check(position_handle != 0 && static_sk_font_arguments_variation_position_get_ptr(position_handle) != nullptr, "SkFontArguments_getVariationDesignPosition(valid)")) {
        SkFontArguments_delete(arguments);
        return 10;
    }
    static_sk_font_arguments_variation_position_delete(position_handle);

    const sk_font_arguments_palette_t palette_handle = SkFontArguments_getPalette(arguments);
    if (!check(palette_handle != 0 && static_sk_font_arguments_palette_get_ptr(palette_handle) != nullptr, "SkFontArguments_getPalette(valid)")) {
        SkFontArguments_delete(arguments);
        return 11;
    }
    static_sk_font_arguments_palette_delete(palette_handle);
    SkFontArguments_delete(arguments);

    SkFontMetrics_delete(nullptr);
    float value = 0.0f;
    if (!check(!SkFontMetrics_hasUnderlineThickness(nullptr, &value), "SkFontMetrics_hasUnderlineThickness(nullptr)")) {
        return 12;
    }
    if (!check(!SkFontMetrics_hasUnderlineThickness(reinterpret_cast<reskia_font_metrics_t *>(&value), nullptr), "SkFontMetrics_hasUnderlineThickness(null output)")) {
        return 13;
    }
    if (!check(!SkFontMetrics_hasUnderlinePosition(nullptr, &value), "SkFontMetrics_hasUnderlinePosition(nullptr)")) {
        return 14;
    }
    if (!check(!SkFontMetrics_hasStrikeoutThickness(nullptr, &value), "SkFontMetrics_hasStrikeoutThickness(nullptr)")) {
        return 15;
    }
    if (!check(!SkFontMetrics_hasStrikeoutPosition(nullptr, &value), "SkFontMetrics_hasStrikeoutPosition(nullptr)")) {
        return 16;
    }
    if (!check(!SkFontMetrics_hasBounds(nullptr), "SkFontMetrics_hasBounds(nullptr)")) {
        return 17;
    }

    SkFontMetrics metrics = {};
    auto *reskia_metrics = reinterpret_cast<reskia_font_metrics_t *>(&metrics);
    metrics.fFlags = SkFontMetrics::kUnderlineThicknessIsValid_Flag |
                     SkFontMetrics::kUnderlinePositionIsValid_Flag |
                     SkFontMetrics::kStrikeoutThicknessIsValid_Flag |
                     SkFontMetrics::kStrikeoutPositionIsValid_Flag;
    metrics.fUnderlineThickness = 1.0f;
    metrics.fUnderlinePosition = 2.0f;
    metrics.fStrikeoutThickness = 3.0f;
    metrics.fStrikeoutPosition = 4.0f;

    if (!check(SkFontMetrics_hasUnderlineThickness(reskia_metrics, &value) && value == 1.0f, "SkFontMetrics_hasUnderlineThickness(valid)")) {
        return 18;
    }
    if (!check(SkFontMetrics_hasUnderlinePosition(reskia_metrics, &value) && value == 2.0f, "SkFontMetrics_hasUnderlinePosition(valid)")) {
        return 19;
    }
    if (!check(SkFontMetrics_hasStrikeoutThickness(reskia_metrics, &value) && value == 3.0f, "SkFontMetrics_hasStrikeoutThickness(valid)")) {
        return 20;
    }
    if (!check(SkFontMetrics_hasStrikeoutPosition(reskia_metrics, &value) && value == 4.0f, "SkFontMetrics_hasStrikeoutPosition(valid)")) {
        return 21;
    }
    if (!check(SkFontMetrics_hasBounds(reskia_metrics), "SkFontMetrics_hasBounds(valid)")) {
        return 22;
    }
    return 0;
}
