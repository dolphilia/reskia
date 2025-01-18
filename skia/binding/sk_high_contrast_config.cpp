//
// Created by dolphilia on 2024/01/08.
//

#include "sk_high_contrast_config.h"

#include "include/effects/SkHighContrastFilter.h"

extern "C" {

void *SkHighContrastConfig_new() {
    return new SkHighContrastConfig();
}

void *SkHighContrastConfig_new_2(bool grayscale, int invertStyle, float contrast) {
    return new SkHighContrastConfig(grayscale, static_cast<SkHighContrastConfig::InvertStyle>(invertStyle), contrast);
}

void SkHighContrastConfig_delete(void * highContrastConfig) {
    delete static_cast<SkHighContrastConfig *>(highContrastConfig);
}

bool isValid(void *high_contrast_config) {
    return static_cast<SkHighContrastConfig *>(high_contrast_config)->isValid();
}

}