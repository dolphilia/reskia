//
// Created by dolphilia on 2024/01/08.
//

#include "sk_high_contrast_config.h"

#include "include/effects/SkHighContrastFilter.h"

namespace {

bool valid_invert_style(int invertStyle) {
    return invertStyle >= static_cast<int>(SkHighContrastConfig::InvertStyle::kNoInvert) &&
           invertStyle <= static_cast<int>(SkHighContrastConfig::InvertStyle::kLast);
}

}  // namespace

extern "C" {

reskia_high_contrast_config_t *SkHighContrastConfig_new() {
    return reinterpret_cast<reskia_high_contrast_config_t *>(new SkHighContrastConfig());
}

reskia_high_contrast_config_t *SkHighContrastConfig_newWithGrayscaleInvertStyleContrast(bool grayscale, int invertStyle, float contrast) {
    if (!valid_invert_style(invertStyle)) {
        return nullptr;
    }
    return reinterpret_cast<reskia_high_contrast_config_t *>(
        new SkHighContrastConfig(grayscale, static_cast<SkHighContrastConfig::InvertStyle>(invertStyle), contrast));
}

void SkHighContrastConfig_delete(reskia_high_contrast_config_t *highContrastConfig) {
    delete reinterpret_cast<SkHighContrastConfig *>(highContrastConfig);
}

bool isValid(reskia_high_contrast_config_t *high_contrast_config) {
    if (high_contrast_config == nullptr) {
        return false;
    }
    return reinterpret_cast<SkHighContrastConfig *>(high_contrast_config)->isValid();
}

}
