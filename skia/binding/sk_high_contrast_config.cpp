//
// Created by dolphilia on 2024/01/08.
//

#include "sk_high_contrast_config.h"

#include "include/effects/SkHighContrastFilter.h"

extern "C" {

reskia_high_contrast_config_t *SkHighContrastConfig_new() {
    return reinterpret_cast<reskia_high_contrast_config_t *>(new SkHighContrastConfig());
}

reskia_high_contrast_config_t *SkHighContrastConfig_new_2(bool grayscale, int invertStyle, float contrast) {
    return reinterpret_cast<reskia_high_contrast_config_t *>(
        new SkHighContrastConfig(grayscale, static_cast<SkHighContrastConfig::InvertStyle>(invertStyle), contrast));
}

void SkHighContrastConfig_delete(reskia_high_contrast_config_t *highContrastConfig) {
    delete reinterpret_cast<SkHighContrastConfig *>(highContrastConfig);
}

bool isValid(reskia_high_contrast_config_t *high_contrast_config) {
    return reinterpret_cast<SkHighContrastConfig *>(high_contrast_config)->isValid();
}

}
