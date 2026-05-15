#include <cstdio>
#include <cstring>

#include "capi/sk_canvas.h"
#include "capi/sk_graphics.h"
#include "capi/sk_resources.h"
#include "capi/sk_size.h"
#include "capi/sk_skottie.h"
#include "capi/sk_string.h"
#include "handles/static_sk_size_t.h"
#include "handles/static_sk_v2.h"

namespace {

bool check(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "[skottie-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool smoke_skottie_minimal() {
    static const char* kLottieJson = R"JSON({
  "v": "5.7.4",
  "fr": 30,
  "ip": 0,
  "op": 60,
  "w": 64,
  "h": 64,
  "nm": "reskia-skottie-smoke",
  "ddd": 0,
  "assets": [],
  "layers": []
})JSON";

    reskia_skottie_animation_t* animation =
            Skottie_Animation_Make(kLottieJson, std::strlen(kLottieJson));
    if (!check(animation != nullptr, "Skottie_Animation_Make")) {
        return false;
    }

    const double duration = Skottie_Animation_duration(animation);
    const double fps = Skottie_Animation_fps(animation);
    const double in_point = Skottie_Animation_inPoint(animation);
    const double out_point = Skottie_Animation_outPoint(animation);
    const float width = Skottie_Animation_width(animation);
    const float height = Skottie_Animation_height(animation);

    if (!check(duration > 0.0, "Skottie_Animation_duration > 0")) {
        Skottie_Animation_release(animation);
        return false;
    }
    if (!check(fps > 0.0, "Skottie_Animation_fps > 0")) {
        Skottie_Animation_release(animation);
        return false;
    }
    if (!check(width > 0.0f && height > 0.0f, "Skottie_Animation_size > 0")) {
        Skottie_Animation_release(animation);
        return false;
    }
    if (!check(in_point == 0.0 && out_point == 60.0, "Skottie_Animation in/out points")) {
        Skottie_Animation_release(animation);
        return false;
    }
    reskia_string_t *version = Skottie_Animation_version(animation);
    if (!check(version != nullptr && SkString_equalsText(version, "5.7.4"), "Skottie_Animation_version")) {
        SkString_delete(version);
        Skottie_Animation_release(animation);
        return false;
    }
    SkString_delete(version);
    sk_size_t size_handle = Skottie_Animation_size(animation);
    auto *size = reinterpret_cast<reskia_size_t *>(static_sk_size_get_ptr(size_handle));
    if (!check(size != nullptr && SkSize_width(size) == 64.0f && SkSize_height(size) == 64.0f, "Skottie_Animation_size")) {
        static_sk_size_delete(size_handle);
        Skottie_Animation_release(animation);
        return false;
    }
    static_sk_size_delete(size_handle);

    if (!check(Skottie_Animation_seek(animation, 0.0f), "Skottie_Animation_seek(0.0)")) {
        Skottie_Animation_release(animation);
        return false;
    }
    if (!check(Skottie_Animation_seek(animation, 0.5f), "Skottie_Animation_seek(0.5)")) {
        Skottie_Animation_release(animation);
        return false;
    }
    if (!check(Skottie_Animation_seekFrameTime(animation, duration), "Skottie_Animation_seekFrameTime(duration)")) {
        Skottie_Animation_release(animation);
        return false;
    }

    reskia_canvas_t* canvas = SkCanvas_newWithSizeProps(128, 128, nullptr);
    if (!check(canvas != nullptr, "SkCanvas_newWithSizeProps")) {
        Skottie_Animation_release(animation);
        return false;
    }

    Skottie_Animation_render(animation, canvas, nullptr);
    Skottie_Animation_renderWithFlags(animation, canvas, nullptr, 0);

    SkCanvas_delete(canvas);
    Skottie_Animation_release(animation);
    return true;
}

bool smoke_skottie_builder_and_slots() {
    static const char* kLottieJson = R"JSON({
  "v": "5.7.4",
  "fr": 30,
  "ip": 0,
  "op": 60,
  "w": 64,
  "h": 64,
  "nm": "reskia-skottie-builder-smoke",
  "ddd": 0,
  "assets": [],
  "layers": []
})JSON";

    reskia_skottie_animation_builder_t *builder = Skottie_AnimationBuilder_new(0);
    if (!check(builder != nullptr, "Skottie_AnimationBuilder_new")) {
        return false;
    }
    if (!check(!Skottie_AnimationBuilder_setResourceProvider(builder, nullptr), "Skottie_AnimationBuilder_setResourceProvider null")) {
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    reskia_skottie_animation_t *animation =
            Skottie_AnimationBuilder_make(builder, kLottieJson, std::strlen(kLottieJson));
    if (!check(animation != nullptr, "Skottie_AnimationBuilder_make")) {
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }

    reskia_skottie_slot_manager_t *manager = Skottie_AnimationBuilder_getSlotManager(builder);
    if (!check(manager != nullptr, "Skottie_AnimationBuilder_getSlotManager")) {
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }

    reskia_skottie_slot_info_t *slot_info = SlotManager_getSlotInfo(manager);
    if (!check(slot_info != nullptr, "SlotManager_getSlotInfo")) {
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    if (!check(SlotInfo_colorSlotCount(slot_info) == 0 &&
               SlotInfo_scalarSlotCount(slot_info) == 0 &&
               SlotInfo_vec2SlotCount(slot_info) == 0 &&
               SlotInfo_imageSlotCount(slot_info) == 0 &&
               SlotInfo_textSlotCount(slot_info) == 0,
               "SlotInfo empty counts")) {
        SlotInfo_delete(slot_info);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    if (!check(SlotInfo_colorSlotId(slot_info, 0) == nullptr, "SlotInfo out-of-range id")) {
        SlotInfo_delete(slot_info);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    SlotInfo_delete(slot_info);

    uint32_t color = 0;
    float scalar = 0.0f;
    sk_v2_t vec2 = 0;
    reskia_skottie_text_property_value_t *text_value = TextPropertyValue_new();
    if (!check(text_value != nullptr, "TextPropertyValue_new")) {
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    TextPropertyValue_setText(text_value, "reskia text");
    TextPropertyValue_setTextSize(text_value, 24.0f);
    TextPropertyValue_setMinTextSize(text_value, 12.0f);
    TextPropertyValue_setMaxTextSize(text_value, 48.0f);
    TextPropertyValue_setLineHeight(text_value, 28.0f);
    TextPropertyValue_setLineShift(text_value, 2.0f);
    TextPropertyValue_setAscent(text_value, 18.0f);
    TextPropertyValue_setMaxLines(text_value, 3);
    TextPropertyValue_setFillColor(text_value, 0xff112233);
    TextPropertyValue_setStrokeColor(text_value, 0xff445566);
    TextPropertyValue_setHasFill(text_value, true);
    TextPropertyValue_setHasStroke(text_value, true);
    TextPropertyValue_setLocale(text_value, "ja-JP");
    reskia_string_t *text = TextPropertyValue_getText(text_value);
    reskia_string_t *locale = TextPropertyValue_getLocale(text_value);
    if (!check(text != nullptr && SkString_equalsText(text, "reskia text"), "TextPropertyValue_getText")) {
        SkString_delete(text);
        SkString_delete(locale);
        TextPropertyValue_delete(text_value);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    if (!check(locale != nullptr && SkString_equalsText(locale, "ja-JP"), "TextPropertyValue_getLocale")) {
        SkString_delete(text);
        SkString_delete(locale);
        TextPropertyValue_delete(text_value);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    SkString_delete(text);
    SkString_delete(locale);
    if (!check(TextPropertyValue_getTextSize(text_value) == 24.0f &&
               TextPropertyValue_getMinTextSize(text_value) == 12.0f &&
               TextPropertyValue_getMaxTextSize(text_value) == 48.0f &&
               TextPropertyValue_getLineHeight(text_value) == 28.0f &&
               TextPropertyValue_getLineShift(text_value) == 2.0f &&
               TextPropertyValue_getAscent(text_value) == 18.0f &&
               TextPropertyValue_getMaxLines(text_value) == 3 &&
               TextPropertyValue_getFillColor(text_value) == 0xff112233 &&
               TextPropertyValue_getStrokeColor(text_value) == 0xff445566 &&
               TextPropertyValue_hasFill(text_value) &&
               TextPropertyValue_hasStroke(text_value),
               "TextPropertyValue scalar/color fields")) {
        TextPropertyValue_delete(text_value);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    reskia_skottie_text_property_value_t *text_copy = TextPropertyValue_newCopy(text_value);
    if (!check(text_copy != nullptr && TextPropertyValue_equals(text_value, text_copy), "TextPropertyValue_newCopy/equals")) {
        TextPropertyValue_delete(text_copy);
        TextPropertyValue_delete(text_value);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    TextPropertyValue_setText(text_copy, "changed");
    if (!check(TextPropertyValue_notEquals(text_value, text_copy), "TextPropertyValue_notEquals")) {
        TextPropertyValue_delete(text_copy);
        TextPropertyValue_delete(text_value);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    TextPropertyValue_delete(text_copy);
    if (!check(!SlotManager_setColorSlot(manager, "missing", 0xff00ff00), "SlotManager_setColorSlot missing")) {
        TextPropertyValue_delete(text_value);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    if (!check(!SlotManager_getColorSlot(manager, "missing", &color), "SlotManager_getColorSlot missing")) {
        TextPropertyValue_delete(text_value);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    if (!check(!SlotManager_setScalarSlot(manager, "missing", 1.0f), "SlotManager_setScalarSlot missing")) {
        TextPropertyValue_delete(text_value);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    if (!check(!SlotManager_getScalarSlot(manager, "missing", &scalar), "SlotManager_getScalarSlot missing")) {
        TextPropertyValue_delete(text_value);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    if (!check(!SlotManager_getVec2Slot(manager, "missing", &vec2) && vec2 == 0, "SlotManager_getVec2Slot missing")) {
        TextPropertyValue_delete(text_value);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    if (!check(SlotManager_getImageSlot(manager, "missing") == nullptr, "SlotManager_getImageSlot missing")) {
        TextPropertyValue_delete(text_value);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    if (!check(!SlotManager_setTextSlot(manager, "missing", text_value), "SlotManager_setTextSlot missing")) {
        TextPropertyValue_delete(text_value);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    if (!check(SlotManager_getTextSlot(manager, "missing") == nullptr, "SlotManager_getTextSlot missing")) {
        TextPropertyValue_delete(text_value);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    TextPropertyValue_delete(text_value);

    SlotManager_release(manager);
    Skottie_Animation_release(animation);
    Skottie_AnimationBuilder_delete(builder);
    return true;
}

bool smoke_skottie_text_slot() {
    static const char* kLottieJson = R"JSON({
  "v": "5.7.4",
  "fr": 30,
  "ip": 0,
  "op": 60,
  "w": 128,
  "h": 64,
  "nm": "reskia-skottie-text-slot-smoke",
  "ddd": 0,
  "assets": [],
  "fonts": {
    "list": [{
      "fFamily": "Arial",
      "fName": "Arial",
      "fStyle": "Regular"
    }]
  },
  "layers": [{
    "ty": 5,
    "nm": "text_layer",
    "ip": 0,
    "op": 60,
    "ks": {
      "p": { "a": 0, "k": [0, 0] }
    },
    "t": {
      "d": {
        "sid": "body",
        "k": [{
          "t": 0,
          "s": {
            "f": "Arial",
            "t": "initial text",
            "s": 24,
            "fc": [1, 1, 1, 1],
            "lh": 28,
            "ls": 0,
            "ps": [0, 0],
            "sz": [128, 64]
          }
        }]
      }
    }
  }]
})JSON";

    reskia_skottie_animation_builder_t *builder = Skottie_AnimationBuilder_new(0);
    if (!check(builder != nullptr, "text slot AnimationBuilder_new")) {
        return false;
    }
    reskia_skottie_animation_t *animation =
            Skottie_AnimationBuilder_make(builder, kLottieJson, std::strlen(kLottieJson));
    if (!check(animation != nullptr, "text slot AnimationBuilder_make")) {
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    reskia_skottie_slot_manager_t *manager = Skottie_AnimationBuilder_getSlotManager(builder);
    if (!check(manager != nullptr, "text slot getSlotManager")) {
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    reskia_skottie_slot_info_t *slot_info = SlotManager_getSlotInfo(manager);
    if (!check(slot_info != nullptr && SlotInfo_textSlotCount(slot_info) == 1, "text slot SlotInfo_textSlotCount")) {
        SlotInfo_delete(slot_info);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    reskia_string_t *slot_id = SlotInfo_textSlotId(slot_info, 0);
    if (!check(slot_id != nullptr && SkString_equalsText(slot_id, "body"), "text slot SlotInfo_textSlotId")) {
        SkString_delete(slot_id);
        SlotInfo_delete(slot_info);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    SkString_delete(slot_id);
    SlotInfo_delete(slot_info);

    reskia_skottie_text_property_value_t *initial = SlotManager_getTextSlot(manager, "body");
    if (!check(initial != nullptr, "SlotManager_getTextSlot body")) {
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    reskia_string_t *initial_text = TextPropertyValue_getText(initial);
    if (!check(initial_text != nullptr && SkString_equalsText(initial_text, "initial text"), "SlotManager_getTextSlot text")) {
        SkString_delete(initial_text);
        TextPropertyValue_delete(initial);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    SkString_delete(initial_text);
    TextPropertyValue_setText(initial, "updated text");
    TextPropertyValue_setTextSize(initial, 18.0f);
    if (!check(SlotManager_setTextSlot(manager, "body", initial), "SlotManager_setTextSlot body")) {
        TextPropertyValue_delete(initial);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    reskia_skottie_text_property_value_t *updated = SlotManager_getTextSlot(manager, "body");
    if (!check(updated != nullptr, "SlotManager_getTextSlot updated")) {
        TextPropertyValue_delete(initial);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    reskia_string_t *updated_text = TextPropertyValue_getText(updated);
    if (!check(updated_text != nullptr &&
               SkString_equalsText(updated_text, "updated text") &&
               TextPropertyValue_getTextSize(updated) == 18.0f,
               "SlotManager_set/getTextSlot updated")) {
        SkString_delete(updated_text);
        TextPropertyValue_delete(updated);
        TextPropertyValue_delete(initial);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    SkString_delete(updated_text);
    TextPropertyValue_delete(updated);
    TextPropertyValue_delete(initial);
    SlotManager_release(manager);
    Skottie_Animation_release(animation);
    Skottie_AnimationBuilder_delete(builder);
    return true;
}

}  // namespace

int main() {
    SkGraphics_Init();

    if (!smoke_skottie_minimal()) {
        return 1;
    }
    if (!smoke_skottie_builder_and_slots()) {
        return 1;
    }
    if (!smoke_skottie_text_slot()) {
        return 1;
    }

    std::fprintf(stdout, "[skottie-smoke] PASS\n");
    return 0;
}
