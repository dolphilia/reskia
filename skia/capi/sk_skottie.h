#ifndef RAIA_SKIA_SK_SKOTTIE_H
#define RAIA_SKIA_SK_SKOTTIE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "../handles/static_sk_size_t.h"
#include "../handles/static_sk_typeface.h"
#include "../handles/static_sk_v2.h"

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_skresources_image_asset_t reskia_skresources_image_asset_t;
typedef struct reskia_skresources_resource_provider_t reskia_skresources_resource_provider_t;
typedef struct reskia_skottie_animation_t reskia_skottie_animation_t;
typedef struct reskia_skottie_animation_builder_t reskia_skottie_animation_builder_t;
typedef struct reskia_skottie_slot_info_t reskia_skottie_slot_info_t;
typedef struct reskia_skottie_slot_manager_t reskia_skottie_slot_manager_t;
typedef struct reskia_skottie_text_property_value_t reskia_skottie_text_property_value_t;
typedef struct reskia_string_t reskia_string_t;

#ifdef __cplusplus
extern "C" {
#endif

enum {
    RESKIA_SKOTTIE_ANIMATION_BUILDER_DEFER_IMAGE_LOADING = 0x01,
    RESKIA_SKOTTIE_ANIMATION_BUILDER_PREFER_EMBEDDED_FONTS = 0x02,
};

reskia_skottie_animation_t *Skottie_Animation_Make(const char *data, size_t length);
reskia_skottie_animation_t *Skottie_Animation_MakeFromFile(const char path[]);

void Skottie_Animation_release(reskia_skottie_animation_t *animation);
void Skottie_Animation_ref(reskia_skottie_animation_t *animation);
void Skottie_Animation_unref(reskia_skottie_animation_t *animation);

bool Skottie_Animation_seek(reskia_skottie_animation_t *animation, float t);
bool Skottie_Animation_seekFrameTime(reskia_skottie_animation_t *animation, double t);
void Skottie_Animation_render(reskia_skottie_animation_t *animation, reskia_canvas_t *canvas, const reskia_rect_t *dst);
void Skottie_Animation_renderWithFlags(reskia_skottie_animation_t *animation, reskia_canvas_t *canvas, const reskia_rect_t *dst, uint32_t flags);

double Skottie_Animation_duration(const reskia_skottie_animation_t *animation);
double Skottie_Animation_fps(const reskia_skottie_animation_t *animation);
double Skottie_Animation_inPoint(const reskia_skottie_animation_t *animation);
double Skottie_Animation_outPoint(const reskia_skottie_animation_t *animation);
reskia_string_t *Skottie_Animation_version(const reskia_skottie_animation_t *animation);
// Returns an owned SkSize handle. Release it with static_sk_size_delete().
sk_size_t Skottie_Animation_size(const reskia_skottie_animation_t *animation);
float Skottie_Animation_width(const reskia_skottie_animation_t *animation);
float Skottie_Animation_height(const reskia_skottie_animation_t *animation);

reskia_skottie_animation_builder_t *Skottie_AnimationBuilder_new(uint32_t flags);
void Skottie_AnimationBuilder_delete(reskia_skottie_animation_builder_t *builder);
bool Skottie_AnimationBuilder_setResourceProvider(reskia_skottie_animation_builder_t *builder, reskia_skresources_resource_provider_t *provider); // provider is borrowed and retained.
reskia_skottie_animation_t *Skottie_AnimationBuilder_make(reskia_skottie_animation_builder_t *builder, const char *data, size_t length);
reskia_skottie_animation_t *Skottie_AnimationBuilder_makeFromFile(reskia_skottie_animation_builder_t *builder, const char path[]);
reskia_skottie_slot_manager_t *Skottie_AnimationBuilder_getSlotManager(reskia_skottie_animation_builder_t *builder); // returned pointer owns a ref; release with SlotManager_release.

reskia_skottie_text_property_value_t *TextPropertyValue_new();
reskia_skottie_text_property_value_t *TextPropertyValue_newCopy(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_delete(reskia_skottie_text_property_value_t *value);
bool TextPropertyValue_equals(const reskia_skottie_text_property_value_t *value, const reskia_skottie_text_property_value_t *other);
bool TextPropertyValue_notEquals(const reskia_skottie_text_property_value_t *value, const reskia_skottie_text_property_value_t *other);
void TextPropertyValue_setTypeface(reskia_skottie_text_property_value_t *value, sk_typeface_t typeface);
sk_typeface_t TextPropertyValue_getTypeface(const reskia_skottie_text_property_value_t *value); // returned handle owns a ref; delete with static_sk_typeface_delete.
void TextPropertyValue_setText(reskia_skottie_text_property_value_t *value, const char text[]);
reskia_string_t *TextPropertyValue_getText(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setTextSize(reskia_skottie_text_property_value_t *value, float text_size);
float TextPropertyValue_getTextSize(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setMinTextSize(reskia_skottie_text_property_value_t *value, float min_text_size);
float TextPropertyValue_getMinTextSize(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setMaxTextSize(reskia_skottie_text_property_value_t *value, float max_text_size);
float TextPropertyValue_getMaxTextSize(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setStrokeWidth(reskia_skottie_text_property_value_t *value, float stroke_width);
float TextPropertyValue_getStrokeWidth(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setLineHeight(reskia_skottie_text_property_value_t *value, float line_height);
float TextPropertyValue_getLineHeight(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setLineShift(reskia_skottie_text_property_value_t *value, float line_shift);
float TextPropertyValue_getLineShift(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setAscent(reskia_skottie_text_property_value_t *value, float ascent);
float TextPropertyValue_getAscent(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setMaxLines(reskia_skottie_text_property_value_t *value, size_t max_lines);
size_t TextPropertyValue_getMaxLines(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setHAlign(reskia_skottie_text_property_value_t *value, int32_t align);
int32_t TextPropertyValue_getHAlign(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setVAlign(reskia_skottie_text_property_value_t *value, int32_t align);
int32_t TextPropertyValue_getVAlign(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setResizePolicy(reskia_skottie_text_property_value_t *value, int32_t policy);
int32_t TextPropertyValue_getResizePolicy(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setLinebreakPolicy(reskia_skottie_text_property_value_t *value, int32_t policy);
int32_t TextPropertyValue_getLinebreakPolicy(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setDirection(reskia_skottie_text_property_value_t *value, int32_t direction);
int32_t TextPropertyValue_getDirection(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setCapitalization(reskia_skottie_text_property_value_t *value, int32_t capitalization);
int32_t TextPropertyValue_getCapitalization(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setBox(reskia_skottie_text_property_value_t *value, const reskia_rect_t *box);
bool TextPropertyValue_getBox(const reskia_skottie_text_property_value_t *value, reskia_rect_t *out_box);
void TextPropertyValue_setFillColor(reskia_skottie_text_property_value_t *value, uint32_t color);
uint32_t TextPropertyValue_getFillColor(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setStrokeColor(reskia_skottie_text_property_value_t *value, uint32_t color);
uint32_t TextPropertyValue_getStrokeColor(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setPaintOrder(reskia_skottie_text_property_value_t *value, int32_t order);
int32_t TextPropertyValue_getPaintOrder(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setStrokeJoin(reskia_skottie_text_property_value_t *value, int32_t join);
int32_t TextPropertyValue_getStrokeJoin(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setHasFill(reskia_skottie_text_property_value_t *value, bool has_fill);
bool TextPropertyValue_hasFill(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setHasStroke(reskia_skottie_text_property_value_t *value, bool has_stroke);
bool TextPropertyValue_hasStroke(const reskia_skottie_text_property_value_t *value);
void TextPropertyValue_setLocale(reskia_skottie_text_property_value_t *value, const char locale[]);
reskia_string_t *TextPropertyValue_getLocale(const reskia_skottie_text_property_value_t *value);

void SlotManager_ref(reskia_skottie_slot_manager_t *manager);
void SlotManager_unref(reskia_skottie_slot_manager_t *manager);
void SlotManager_release(reskia_skottie_slot_manager_t *manager);
bool SlotManager_setColorSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[], uint32_t color);
bool SlotManager_getColorSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[], uint32_t *out_color);
bool SlotManager_setScalarSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[], float scalar);
bool SlotManager_getScalarSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[], float *out_scalar);
bool SlotManager_setVec2Slot(reskia_skottie_slot_manager_t *manager, const char slot_id[], sk_v2_t vec2);
bool SlotManager_getVec2Slot(reskia_skottie_slot_manager_t *manager, const char slot_id[], sk_v2_t *out_vec2); // out handle owns a value; delete with static_sk_v2_delete.
bool SlotManager_setImageSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[], reskia_skresources_image_asset_t *asset); // asset is borrowed and retained.
reskia_skresources_image_asset_t *SlotManager_getImageSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[]); // returned pointer owns a ref; release with ImageAsset_release.
bool SlotManager_setTextSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[], const reskia_skottie_text_property_value_t *value);
reskia_skottie_text_property_value_t *SlotManager_getTextSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[]);
reskia_skottie_slot_info_t *SlotManager_getSlotInfo(reskia_skottie_slot_manager_t *manager);

void SlotInfo_delete(reskia_skottie_slot_info_t *slot_info);
size_t SlotInfo_colorSlotCount(const reskia_skottie_slot_info_t *slot_info);
size_t SlotInfo_scalarSlotCount(const reskia_skottie_slot_info_t *slot_info);
size_t SlotInfo_vec2SlotCount(const reskia_skottie_slot_info_t *slot_info);
size_t SlotInfo_imageSlotCount(const reskia_skottie_slot_info_t *slot_info);
size_t SlotInfo_textSlotCount(const reskia_skottie_slot_info_t *slot_info);
reskia_string_t *SlotInfo_colorSlotId(const reskia_skottie_slot_info_t *slot_info, size_t index);
reskia_string_t *SlotInfo_scalarSlotId(const reskia_skottie_slot_info_t *slot_info, size_t index);
reskia_string_t *SlotInfo_vec2SlotId(const reskia_skottie_slot_info_t *slot_info, size_t index);
reskia_string_t *SlotInfo_imageSlotId(const reskia_skottie_slot_info_t *slot_info, size_t index);
reskia_string_t *SlotInfo_textSlotId(const reskia_skottie_slot_info_t *slot_info, size_t index);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_SKOTTIE_H
