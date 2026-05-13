//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_HIGH_CONTRAST_CONFIG_H
#define RAIA_SKIA_SK_HIGH_CONTRAST_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_high_contrast_config_t reskia_high_contrast_config_t;

reskia_high_contrast_config_t *SkHighContrastConfig_new(); // Returns caller-owned default config.
reskia_high_contrast_config_t *SkHighContrastConfig_newWithGrayscaleInvertStyleContrast(bool grayscale, int invertStyle, float contrast); // invalid invertStyle returns NULL; caller owns result.
void SkHighContrastConfig_delete(reskia_high_contrast_config_t *highContrastConfig); // (SkHighContrastConfig * highContrastConfig)
bool isValid(reskia_high_contrast_config_t *high_contrast_config); // NULL config returns false.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_HIGH_CONTRAST_CONFIG_H
