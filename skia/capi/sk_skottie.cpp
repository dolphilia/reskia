#include "sk_skottie.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"
#include "include/core/SkRect.h"
#include "include/core/SkString.h"
#include "modules/skottie/include/Skottie.h"
#include "modules/skottie/include/SkottieProperty.h"
#include "modules/skresources/include/SkResources.h"

#include "../handles/static_sk_size_t-internal.h"
#include "../handles/static_sk_typeface-internal.h"
#include "../handles/static_sk_v2-internal.h"

namespace {

inline skottie::Animation *to_animation(reskia_skottie_animation_t *animation) {
    return reinterpret_cast<skottie::Animation *>(animation);
}

inline const skottie::Animation *to_animation(const reskia_skottie_animation_t *animation) {
    return reinterpret_cast<const skottie::Animation *>(animation);
}

inline skottie::Animation::Builder *to_builder(reskia_skottie_animation_builder_t *builder) {
    return reinterpret_cast<skottie::Animation::Builder *>(builder);
}

inline skottie::SlotManager *to_slot_manager(reskia_skottie_slot_manager_t *manager) {
    return reinterpret_cast<skottie::SlotManager *>(manager);
}

inline const skottie::SlotManager::SlotInfo *to_slot_info(const reskia_skottie_slot_info_t *slot_info) {
    return reinterpret_cast<const skottie::SlotManager::SlotInfo *>(slot_info);
}

inline skottie::TextPropertyValue *to_text_property_value(reskia_skottie_text_property_value_t *value) {
    return reinterpret_cast<skottie::TextPropertyValue *>(value);
}

inline const skottie::TextPropertyValue *to_text_property_value(const reskia_skottie_text_property_value_t *value) {
    return reinterpret_cast<const skottie::TextPropertyValue *>(value);
}

inline skresources::ResourceProvider *to_resource_provider(reskia_skresources_resource_provider_t *provider) {
    return reinterpret_cast<skresources::ResourceProvider *>(provider);
}

inline skresources::ImageAsset *to_image_asset(reskia_skresources_image_asset_t *asset) {
    return reinterpret_cast<skresources::ImageAsset *>(asset);
}

reskia_string_t *copy_slot_id(const skia_private::TArray<SkString> &ids, size_t index) {
    if (index >= ids.size()) {
        return nullptr;
    }
    return reinterpret_cast<reskia_string_t *>(new SkString(ids[static_cast<int>(index)]));
}

} // namespace

extern "C" {

reskia_skottie_animation_t *Skottie_Animation_Make(const char *data, size_t length) {
    if (data == nullptr || length == 0) {
        return nullptr;
    }
    auto animation = skottie::Animation::Make(data, length);
    return reinterpret_cast<reskia_skottie_animation_t *>(animation.release());
}

reskia_skottie_animation_t *Skottie_Animation_MakeFromFile(const char path[]) {
    if (path == nullptr) {
        return nullptr;
    }
    auto animation = skottie::Animation::MakeFromFile(path);
    return reinterpret_cast<reskia_skottie_animation_t *>(animation.release());
}

void Skottie_Animation_release(reskia_skottie_animation_t *animation) {
    if (animation == nullptr) {
        return;
    }
    to_animation(animation)->unref();
}

void Skottie_Animation_ref(reskia_skottie_animation_t *animation) {
    if (animation == nullptr) {
        return;
    }
    to_animation(animation)->ref();
}

void Skottie_Animation_unref(reskia_skottie_animation_t *animation) {
    if (animation == nullptr) {
        return;
    }
    to_animation(animation)->unref();
}

bool Skottie_Animation_seek(reskia_skottie_animation_t *animation, float t) {
    if (animation == nullptr) {
        return false;
    }
    to_animation(animation)->seek(t);
    return true;
}

bool Skottie_Animation_seekFrameTime(reskia_skottie_animation_t *animation, double t) {
    if (animation == nullptr) {
        return false;
    }
    to_animation(animation)->seekFrameTime(t);
    return true;
}

void Skottie_Animation_render(reskia_skottie_animation_t *animation, reskia_canvas_t *canvas, const reskia_rect_t *dst) {
    if (animation == nullptr || canvas == nullptr) {
        return;
    }
    to_animation(animation)->render(
            reinterpret_cast<SkCanvas *>(canvas),
            reinterpret_cast<const SkRect *>(dst)
    );
}

void Skottie_Animation_renderWithFlags(reskia_skottie_animation_t *animation, reskia_canvas_t *canvas, const reskia_rect_t *dst, uint32_t flags) {
    if (animation == nullptr || canvas == nullptr) {
        return;
    }
    to_animation(animation)->render(
            reinterpret_cast<SkCanvas *>(canvas),
            reinterpret_cast<const SkRect *>(dst),
            flags
    );
}

double Skottie_Animation_duration(const reskia_skottie_animation_t *animation) {
    if (animation == nullptr) {
        return 0.0;
    }
    return to_animation(animation)->duration();
}

double Skottie_Animation_fps(const reskia_skottie_animation_t *animation) {
    if (animation == nullptr) {
        return 0.0;
    }
    return to_animation(animation)->fps();
}

double Skottie_Animation_inPoint(const reskia_skottie_animation_t *animation) {
    if (animation == nullptr) {
        return 0.0;
    }
    return to_animation(animation)->inPoint();
}

double Skottie_Animation_outPoint(const reskia_skottie_animation_t *animation) {
    if (animation == nullptr) {
        return 0.0;
    }
    return to_animation(animation)->outPoint();
}

reskia_string_t *Skottie_Animation_version(const reskia_skottie_animation_t *animation) {
    if (animation == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_string_t *>(new SkString(to_animation(animation)->version()));
}

sk_size_t Skottie_Animation_size(const reskia_skottie_animation_t *animation) {
    if (animation == nullptr) {
        return 0;
    }
    return static_sk_size_make(to_animation(animation)->size());
}

float Skottie_Animation_width(const reskia_skottie_animation_t *animation) {
    if (animation == nullptr) {
        return 0.0f;
    }
    return to_animation(animation)->size().width();
}

float Skottie_Animation_height(const reskia_skottie_animation_t *animation) {
    if (animation == nullptr) {
        return 0.0f;
    }
    return to_animation(animation)->size().height();
}

reskia_skottie_animation_builder_t *Skottie_AnimationBuilder_new(uint32_t flags) {
    return reinterpret_cast<reskia_skottie_animation_builder_t *>(
            new skottie::Animation::Builder(flags));
}

void Skottie_AnimationBuilder_delete(reskia_skottie_animation_builder_t *builder) {
    delete to_builder(builder);
}

bool Skottie_AnimationBuilder_setResourceProvider(reskia_skottie_animation_builder_t *builder, reskia_skresources_resource_provider_t *provider) {
    if (builder == nullptr || provider == nullptr) {
        return false;
    }
    to_builder(builder)->setResourceProvider(sk_ref_sp(to_resource_provider(provider)));
    return true;
}

reskia_skottie_animation_t *Skottie_AnimationBuilder_make(reskia_skottie_animation_builder_t *builder, const char *data, size_t length) {
    if (builder == nullptr || data == nullptr || length == 0) {
        return nullptr;
    }
    auto animation = to_builder(builder)->make(data, length);
    return reinterpret_cast<reskia_skottie_animation_t *>(animation.release());
}

reskia_skottie_animation_t *Skottie_AnimationBuilder_makeFromFile(reskia_skottie_animation_builder_t *builder, const char path[]) {
    if (builder == nullptr || path == nullptr) {
        return nullptr;
    }
    auto animation = to_builder(builder)->makeFromFile(path);
    return reinterpret_cast<reskia_skottie_animation_t *>(animation.release());
}

reskia_skottie_slot_manager_t *Skottie_AnimationBuilder_getSlotManager(reskia_skottie_animation_builder_t *builder) {
    if (builder == nullptr) {
        return nullptr;
    }
    sk_sp<skottie::SlotManager> manager = to_builder(builder)->getSlotManager();
    return reinterpret_cast<reskia_skottie_slot_manager_t *>(manager.release());
}

reskia_skottie_text_property_value_t *TextPropertyValue_new() {
    return reinterpret_cast<reskia_skottie_text_property_value_t *>(new skottie::TextPropertyValue());
}

reskia_skottie_text_property_value_t *TextPropertyValue_newCopy(const reskia_skottie_text_property_value_t *value) {
    if (value == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_skottie_text_property_value_t *>(
            new skottie::TextPropertyValue(*to_text_property_value(value)));
}

void TextPropertyValue_delete(reskia_skottie_text_property_value_t *value) {
    delete to_text_property_value(value);
}

bool TextPropertyValue_equals(const reskia_skottie_text_property_value_t *value, const reskia_skottie_text_property_value_t *other) {
    if (value == nullptr || other == nullptr) {
        return false;
    }
    return *to_text_property_value(value) == *to_text_property_value(other);
}

bool TextPropertyValue_notEquals(const reskia_skottie_text_property_value_t *value, const reskia_skottie_text_property_value_t *other) {
    if (value == nullptr || other == nullptr) {
        return false;
    }
    return *to_text_property_value(value) != *to_text_property_value(other);
}

void TextPropertyValue_setTypeface(reskia_skottie_text_property_value_t *value, sk_typeface_t typeface) {
    if (value == nullptr) {
        return;
    }
    to_text_property_value(value)->fTypeface = typeface != 0 ? static_sk_typeface_get_entity(typeface) : nullptr;
}

sk_typeface_t TextPropertyValue_getTypeface(const reskia_skottie_text_property_value_t *value) {
    if (value == nullptr || to_text_property_value(value)->fTypeface == nullptr) {
        return 0;
    }
    return static_sk_typeface_make(to_text_property_value(value)->fTypeface);
}

void TextPropertyValue_setText(reskia_skottie_text_property_value_t *value, const char text[]) {
    if (value == nullptr || text == nullptr) {
        return;
    }
    to_text_property_value(value)->fText.set(text);
}

reskia_string_t *TextPropertyValue_getText(const reskia_skottie_text_property_value_t *value) {
    if (value == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_string_t *>(new SkString(to_text_property_value(value)->fText));
}

void TextPropertyValue_setTextSize(reskia_skottie_text_property_value_t *value, float text_size) {
    if (value != nullptr) {
        to_text_property_value(value)->fTextSize = text_size;
    }
}

float TextPropertyValue_getTextSize(const reskia_skottie_text_property_value_t *value) {
    return value != nullptr ? to_text_property_value(value)->fTextSize : 0.0f;
}

void TextPropertyValue_setMinTextSize(reskia_skottie_text_property_value_t *value, float min_text_size) {
    if (value != nullptr) {
        to_text_property_value(value)->fMinTextSize = min_text_size;
    }
}

float TextPropertyValue_getMinTextSize(const reskia_skottie_text_property_value_t *value) {
    return value != nullptr ? to_text_property_value(value)->fMinTextSize : 0.0f;
}

void TextPropertyValue_setMaxTextSize(reskia_skottie_text_property_value_t *value, float max_text_size) {
    if (value != nullptr) {
        to_text_property_value(value)->fMaxTextSize = max_text_size;
    }
}

float TextPropertyValue_getMaxTextSize(const reskia_skottie_text_property_value_t *value) {
    return value != nullptr ? to_text_property_value(value)->fMaxTextSize : 0.0f;
}

void TextPropertyValue_setStrokeWidth(reskia_skottie_text_property_value_t *value, float stroke_width) {
    if (value != nullptr) {
        to_text_property_value(value)->fStrokeWidth = stroke_width;
    }
}

float TextPropertyValue_getStrokeWidth(const reskia_skottie_text_property_value_t *value) {
    return value != nullptr ? to_text_property_value(value)->fStrokeWidth : 0.0f;
}

void TextPropertyValue_setLineHeight(reskia_skottie_text_property_value_t *value, float line_height) {
    if (value != nullptr) {
        to_text_property_value(value)->fLineHeight = line_height;
    }
}

float TextPropertyValue_getLineHeight(const reskia_skottie_text_property_value_t *value) {
    return value != nullptr ? to_text_property_value(value)->fLineHeight : 0.0f;
}

void TextPropertyValue_setLineShift(reskia_skottie_text_property_value_t *value, float line_shift) {
    if (value != nullptr) {
        to_text_property_value(value)->fLineShift = line_shift;
    }
}

float TextPropertyValue_getLineShift(const reskia_skottie_text_property_value_t *value) {
    return value != nullptr ? to_text_property_value(value)->fLineShift : 0.0f;
}

void TextPropertyValue_setAscent(reskia_skottie_text_property_value_t *value, float ascent) {
    if (value != nullptr) {
        to_text_property_value(value)->fAscent = ascent;
    }
}

float TextPropertyValue_getAscent(const reskia_skottie_text_property_value_t *value) {
    return value != nullptr ? to_text_property_value(value)->fAscent : 0.0f;
}

void TextPropertyValue_setMaxLines(reskia_skottie_text_property_value_t *value, size_t max_lines) {
    if (value != nullptr) {
        to_text_property_value(value)->fMaxLines = max_lines;
    }
}

size_t TextPropertyValue_getMaxLines(const reskia_skottie_text_property_value_t *value) {
    return value != nullptr ? to_text_property_value(value)->fMaxLines : 0;
}

void TextPropertyValue_setHAlign(reskia_skottie_text_property_value_t *value, int32_t align) {
    if (value != nullptr) {
        to_text_property_value(value)->fHAlign = static_cast<SkTextUtils::Align>(align);
    }
}

int32_t TextPropertyValue_getHAlign(const reskia_skottie_text_property_value_t *value) {
    return value != nullptr ? static_cast<int32_t>(to_text_property_value(value)->fHAlign) : 0;
}

void TextPropertyValue_setVAlign(reskia_skottie_text_property_value_t *value, int32_t align) {
    if (value != nullptr) {
        to_text_property_value(value)->fVAlign = static_cast<skottie::Shaper::VAlign>(align);
    }
}

int32_t TextPropertyValue_getVAlign(const reskia_skottie_text_property_value_t *value) {
    return value != nullptr ? static_cast<int32_t>(to_text_property_value(value)->fVAlign) : 0;
}

void TextPropertyValue_setResizePolicy(reskia_skottie_text_property_value_t *value, int32_t policy) {
    if (value != nullptr) {
        to_text_property_value(value)->fResize = static_cast<skottie::Shaper::ResizePolicy>(policy);
    }
}

int32_t TextPropertyValue_getResizePolicy(const reskia_skottie_text_property_value_t *value) {
    return value != nullptr ? static_cast<int32_t>(to_text_property_value(value)->fResize) : 0;
}

void TextPropertyValue_setLinebreakPolicy(reskia_skottie_text_property_value_t *value, int32_t policy) {
    if (value != nullptr) {
        to_text_property_value(value)->fLineBreak = static_cast<skottie::Shaper::LinebreakPolicy>(policy);
    }
}

int32_t TextPropertyValue_getLinebreakPolicy(const reskia_skottie_text_property_value_t *value) {
    return value != nullptr ? static_cast<int32_t>(to_text_property_value(value)->fLineBreak) : 0;
}

void TextPropertyValue_setDirection(reskia_skottie_text_property_value_t *value, int32_t direction) {
    if (value != nullptr) {
        to_text_property_value(value)->fDirection = static_cast<skottie::Shaper::Direction>(direction);
    }
}

int32_t TextPropertyValue_getDirection(const reskia_skottie_text_property_value_t *value) {
    return value != nullptr ? static_cast<int32_t>(to_text_property_value(value)->fDirection) : 0;
}

void TextPropertyValue_setCapitalization(reskia_skottie_text_property_value_t *value, int32_t capitalization) {
    if (value != nullptr) {
        to_text_property_value(value)->fCapitalization = static_cast<skottie::Shaper::Capitalization>(capitalization);
    }
}

int32_t TextPropertyValue_getCapitalization(const reskia_skottie_text_property_value_t *value) {
    return value != nullptr ? static_cast<int32_t>(to_text_property_value(value)->fCapitalization) : 0;
}

void TextPropertyValue_setBox(reskia_skottie_text_property_value_t *value, const reskia_rect_t *box) {
    if (value != nullptr && box != nullptr) {
        to_text_property_value(value)->fBox = *reinterpret_cast<const SkRect *>(box);
    }
}

bool TextPropertyValue_getBox(const reskia_skottie_text_property_value_t *value, reskia_rect_t *out_box) {
    if (value == nullptr || out_box == nullptr) {
        return false;
    }
    *reinterpret_cast<SkRect *>(out_box) = to_text_property_value(value)->fBox;
    return true;
}

void TextPropertyValue_setFillColor(reskia_skottie_text_property_value_t *value, uint32_t color) {
    if (value != nullptr) {
        to_text_property_value(value)->fFillColor = color;
    }
}

uint32_t TextPropertyValue_getFillColor(const reskia_skottie_text_property_value_t *value) {
    return value != nullptr ? to_text_property_value(value)->fFillColor : 0;
}

void TextPropertyValue_setStrokeColor(reskia_skottie_text_property_value_t *value, uint32_t color) {
    if (value != nullptr) {
        to_text_property_value(value)->fStrokeColor = color;
    }
}

uint32_t TextPropertyValue_getStrokeColor(const reskia_skottie_text_property_value_t *value) {
    return value != nullptr ? to_text_property_value(value)->fStrokeColor : 0;
}

void TextPropertyValue_setPaintOrder(reskia_skottie_text_property_value_t *value, int32_t order) {
    if (value != nullptr) {
        to_text_property_value(value)->fPaintOrder = static_cast<skottie::TextPaintOrder>(order);
    }
}

int32_t TextPropertyValue_getPaintOrder(const reskia_skottie_text_property_value_t *value) {
    return value != nullptr ? static_cast<int32_t>(to_text_property_value(value)->fPaintOrder) : 0;
}

void TextPropertyValue_setStrokeJoin(reskia_skottie_text_property_value_t *value, int32_t join) {
    if (value != nullptr) {
        to_text_property_value(value)->fStrokeJoin = static_cast<SkPaint::Join>(join);
    }
}

int32_t TextPropertyValue_getStrokeJoin(const reskia_skottie_text_property_value_t *value) {
    return value != nullptr ? static_cast<int32_t>(to_text_property_value(value)->fStrokeJoin) : 0;
}

void TextPropertyValue_setHasFill(reskia_skottie_text_property_value_t *value, bool has_fill) {
    if (value != nullptr) {
        to_text_property_value(value)->fHasFill = has_fill;
    }
}

bool TextPropertyValue_hasFill(const reskia_skottie_text_property_value_t *value) {
    return value != nullptr && to_text_property_value(value)->fHasFill;
}

void TextPropertyValue_setHasStroke(reskia_skottie_text_property_value_t *value, bool has_stroke) {
    if (value != nullptr) {
        to_text_property_value(value)->fHasStroke = has_stroke;
    }
}

bool TextPropertyValue_hasStroke(const reskia_skottie_text_property_value_t *value) {
    return value != nullptr && to_text_property_value(value)->fHasStroke;
}

void TextPropertyValue_setLocale(reskia_skottie_text_property_value_t *value, const char locale[]) {
    if (value == nullptr || locale == nullptr) {
        return;
    }
    to_text_property_value(value)->fLocale.set(locale);
}

reskia_string_t *TextPropertyValue_getLocale(const reskia_skottie_text_property_value_t *value) {
    if (value == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_string_t *>(new SkString(to_text_property_value(value)->fLocale));
}

void SlotManager_ref(reskia_skottie_slot_manager_t *manager) {
    if (manager != nullptr) {
        to_slot_manager(manager)->ref();
    }
}

void SlotManager_unref(reskia_skottie_slot_manager_t *manager) {
    if (manager != nullptr) {
        to_slot_manager(manager)->unref();
    }
}

void SlotManager_release(reskia_skottie_slot_manager_t *manager) {
    SlotManager_unref(manager);
}

bool SlotManager_setColorSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[], uint32_t color) {
    if (manager == nullptr || slot_id == nullptr) {
        return false;
    }
    return to_slot_manager(manager)->setColorSlot(SkString(slot_id), color);
}

bool SlotManager_getColorSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[], uint32_t *out_color) {
    if (out_color != nullptr) {
        *out_color = 0;
    }
    if (manager == nullptr || slot_id == nullptr || out_color == nullptr) {
        return false;
    }
    auto value = to_slot_manager(manager)->getColorSlot(SkString(slot_id));
    if (!value.has_value()) {
        return false;
    }
    *out_color = *value;
    return true;
}

bool SlotManager_setScalarSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[], float scalar) {
    if (manager == nullptr || slot_id == nullptr) {
        return false;
    }
    return to_slot_manager(manager)->setScalarSlot(SkString(slot_id), scalar);
}

bool SlotManager_getScalarSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[], float *out_scalar) {
    if (out_scalar != nullptr) {
        *out_scalar = 0.0f;
    }
    if (manager == nullptr || slot_id == nullptr || out_scalar == nullptr) {
        return false;
    }
    auto value = to_slot_manager(manager)->getScalarSlot(SkString(slot_id));
    if (!value.has_value()) {
        return false;
    }
    *out_scalar = *value;
    return true;
}

bool SlotManager_setVec2Slot(reskia_skottie_slot_manager_t *manager, const char slot_id[], sk_v2_t vec2) {
    if (manager == nullptr || slot_id == nullptr || vec2 == 0) {
        return false;
    }
    return to_slot_manager(manager)->setVec2Slot(SkString(slot_id), static_sk_v2_get_entity(vec2));
}

bool SlotManager_getVec2Slot(reskia_skottie_slot_manager_t *manager, const char slot_id[], sk_v2_t *out_vec2) {
    if (out_vec2 != nullptr) {
        *out_vec2 = 0;
    }
    if (manager == nullptr || slot_id == nullptr || out_vec2 == nullptr) {
        return false;
    }
    auto value = to_slot_manager(manager)->getVec2Slot(SkString(slot_id));
    if (!value.has_value()) {
        return false;
    }
    *out_vec2 = static_sk_v2_make(*value);
    return true;
}

bool SlotManager_setImageSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[], reskia_skresources_image_asset_t *asset) {
    if (manager == nullptr || slot_id == nullptr || asset == nullptr) {
        return false;
    }
    return to_slot_manager(manager)->setImageSlot(SkString(slot_id), sk_ref_sp(to_image_asset(asset)));
}

reskia_skresources_image_asset_t *SlotManager_getImageSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[]) {
    if (manager == nullptr || slot_id == nullptr) {
        return nullptr;
    }
    sk_sp<const skresources::ImageAsset> asset = to_slot_manager(manager)->getImageSlot(SkString(slot_id));
    return reinterpret_cast<reskia_skresources_image_asset_t *>(const_cast<skresources::ImageAsset *>(asset.release()));
}

bool SlotManager_setTextSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[], const reskia_skottie_text_property_value_t *value) {
    if (manager == nullptr || slot_id == nullptr || value == nullptr) {
        return false;
    }
    return to_slot_manager(manager)->setTextSlot(SkString(slot_id), *to_text_property_value(value));
}

reskia_skottie_text_property_value_t *SlotManager_getTextSlot(reskia_skottie_slot_manager_t *manager, const char slot_id[]) {
    if (manager == nullptr || slot_id == nullptr) {
        return nullptr;
    }
    auto value = to_slot_manager(manager)->getTextSlot(SkString(slot_id));
    if (!value.has_value()) {
        return nullptr;
    }
    return reinterpret_cast<reskia_skottie_text_property_value_t *>(
            new skottie::TextPropertyValue(*value));
}

reskia_skottie_slot_info_t *SlotManager_getSlotInfo(reskia_skottie_slot_manager_t *manager) {
    if (manager == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_skottie_slot_info_t *>(
            new skottie::SlotManager::SlotInfo(to_slot_manager(manager)->getSlotInfo()));
}

void SlotInfo_delete(reskia_skottie_slot_info_t *slot_info) {
    delete reinterpret_cast<skottie::SlotManager::SlotInfo *>(slot_info);
}

size_t SlotInfo_colorSlotCount(const reskia_skottie_slot_info_t *slot_info) {
    return slot_info != nullptr ? to_slot_info(slot_info)->fColorSlotIDs.size() : 0;
}

size_t SlotInfo_scalarSlotCount(const reskia_skottie_slot_info_t *slot_info) {
    return slot_info != nullptr ? to_slot_info(slot_info)->fScalarSlotIDs.size() : 0;
}

size_t SlotInfo_vec2SlotCount(const reskia_skottie_slot_info_t *slot_info) {
    return slot_info != nullptr ? to_slot_info(slot_info)->fVec2SlotIDs.size() : 0;
}

size_t SlotInfo_imageSlotCount(const reskia_skottie_slot_info_t *slot_info) {
    return slot_info != nullptr ? to_slot_info(slot_info)->fImageSlotIDs.size() : 0;
}

size_t SlotInfo_textSlotCount(const reskia_skottie_slot_info_t *slot_info) {
    return slot_info != nullptr ? to_slot_info(slot_info)->fTextSlotIDs.size() : 0;
}

reskia_string_t *SlotInfo_colorSlotId(const reskia_skottie_slot_info_t *slot_info, size_t index) {
    return slot_info != nullptr ? copy_slot_id(to_slot_info(slot_info)->fColorSlotIDs, index) : nullptr;
}

reskia_string_t *SlotInfo_scalarSlotId(const reskia_skottie_slot_info_t *slot_info, size_t index) {
    return slot_info != nullptr ? copy_slot_id(to_slot_info(slot_info)->fScalarSlotIDs, index) : nullptr;
}

reskia_string_t *SlotInfo_vec2SlotId(const reskia_skottie_slot_info_t *slot_info, size_t index) {
    return slot_info != nullptr ? copy_slot_id(to_slot_info(slot_info)->fVec2SlotIDs, index) : nullptr;
}

reskia_string_t *SlotInfo_imageSlotId(const reskia_skottie_slot_info_t *slot_info, size_t index) {
    return slot_info != nullptr ? copy_slot_id(to_slot_info(slot_info)->fImageSlotIDs, index) : nullptr;
}

reskia_string_t *SlotInfo_textSlotId(const reskia_skottie_slot_info_t *slot_info, size_t index) {
    return slot_info != nullptr ? copy_slot_id(to_slot_info(slot_info)->fTextSlotIDs, index) : nullptr;
}

} // extern "C"
