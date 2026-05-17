#include <cstdio>
#include <cstring>

#include "capi/sk_canvas.h"
#include "capi/sk_graphics.h"
#include "capi/sk_rect.h"
#include "capi/sk_resources.h"
#include "capi/sk_size.h"
#include "capi/sk_skottie.h"
#include "capi/sk_string.h"
#include "handles/static_sk_rect.h"
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

struct LoggerState {
    int logs = 0;
    int releases = 0;
    int last_level = -1;
    const char *last_message = nullptr;
};

struct MarkerState {
    int markers = 0;
    int releases = 0;
    float last_t0 = 0.0f;
    float last_t1 = 0.0f;
    const char *last_name = nullptr;
};

struct ExternalLayerState {
    int renders = 0;
    int releases = 0;
    double last_t = 0.0;
};

struct PrecompState {
    int loads = 0;
    int releases = 0;
    const char *last_id = nullptr;
    const char *last_name = nullptr;
    float last_width = 0.0f;
    float last_height = 0.0f;
    reskia_skottie_external_layer_t *layer = nullptr;
};

struct PropertyObserverState {
    int enters = 0;
    int leaves = 0;
    int colors = 0;
    int opacities = 0;
    int texts = 0;
    int transforms = 0;
    int releases = 0;
    int last_type = -1;
    const char *last_name = nullptr;
};

struct NumberExpressionState {
    int evaluates = 0;
    int releases = 0;
};

struct StringExpressionState {
    int evaluates = 0;
    int releases = 0;
};

struct ArrayExpressionState {
    int evaluates = 0;
    int releases = 0;
};

struct ExpressionManagerState {
    int number_creates = 0;
    int string_creates = 0;
    int array_creates = 0;
    int releases = 0;
    reskia_skottie_number_expression_evaluator_t *number = nullptr;
    reskia_skottie_string_expression_evaluator_t *string = nullptr;
    reskia_skottie_array_expression_evaluator_t *array = nullptr;
};

struct GlyphDecoratorState {
    int decorates = 0;
    int releases = 0;
    size_t last_count = 0;
    float last_scale = 0.0f;
    float last_advance = 0.0f;
};

void log_callback(reskia_skottie_logger_level_t level, const char message[], const char[], void *user_data) {
    auto *state = static_cast<LoggerState *>(user_data);
    if (state != nullptr) {
        state->logs += 1;
        state->last_level = level;
        state->last_message = message;
    }
}

void release_logger(void *user_data) {
    auto *state = static_cast<LoggerState *>(user_data);
    if (state != nullptr) {
        state->releases += 1;
    }
}

void marker_callback(const char name[], float t0, float t1, void *user_data) {
    auto *state = static_cast<MarkerState *>(user_data);
    if (state != nullptr) {
        state->markers += 1;
        state->last_name = name;
        state->last_t0 = t0;
        state->last_t1 = t1;
    }
}

void release_marker(void *user_data) {
    auto *state = static_cast<MarkerState *>(user_data);
    if (state != nullptr) {
        state->releases += 1;
    }
}

void external_layer_render(reskia_canvas_t *, double t, void *user_data) {
    auto *state = static_cast<ExternalLayerState *>(user_data);
    if (state != nullptr) {
        state->renders += 1;
        state->last_t = t;
    }
}

void release_external_layer(void *user_data) {
    auto *state = static_cast<ExternalLayerState *>(user_data);
    if (state != nullptr) {
        state->releases += 1;
    }
}

reskia_skottie_external_layer_t *precomp_on_load(const char id[], const char name[], const reskia_size_t *size, void *user_data) {
    auto *state = static_cast<PrecompState *>(user_data);
    if (state != nullptr) {
        state->loads += 1;
        state->last_id = id;
        state->last_name = name;
        state->last_width = const_cast<reskia_size_t *>(size) != nullptr ? SkSize_width(const_cast<reskia_size_t *>(size)) : 0.0f;
        state->last_height = const_cast<reskia_size_t *>(size) != nullptr ? SkSize_height(const_cast<reskia_size_t *>(size)) : 0.0f;
        return state->layer;
    }
    return nullptr;
}

void release_precomp(void *user_data) {
    auto *state = static_cast<PrecompState *>(user_data);
    if (state != nullptr) {
        state->releases += 1;
    }
}

void property_enter(const char node_name[], reskia_skottie_property_observer_node_type_t node_type, void *user_data) {
    auto *state = static_cast<PropertyObserverState *>(user_data);
    if (state != nullptr) {
        state->enters += 1;
        state->last_type = node_type;
        state->last_name = node_name;
    }
}

void property_leave(const char node_name[], reskia_skottie_property_observer_node_type_t node_type, void *user_data) {
    auto *state = static_cast<PropertyObserverState *>(user_data);
    if (state != nullptr) {
        state->leaves += 1;
        state->last_type = node_type;
        state->last_name = node_name;
    }
}

void property_color(const char node_name[], reskia_skottie_color_property_lazy_handle_t *lazy_handle, void *user_data) {
    auto *state = static_cast<PropertyObserverState *>(user_data);
    if (state != nullptr) {
        state->colors += 1;
        state->last_name = node_name;
    }
    reskia_skottie_color_property_handle_t *handle = Skottie_ColorPropertyLazyHandle_materialize(lazy_handle);
    Skottie_ColorPropertyHandle_delete(handle);
}

void property_opacity(const char node_name[], reskia_skottie_opacity_property_lazy_handle_t *lazy_handle, void *user_data) {
    auto *state = static_cast<PropertyObserverState *>(user_data);
    if (state != nullptr) {
        state->opacities += 1;
        state->last_name = node_name;
    }
    reskia_skottie_opacity_property_handle_t *handle = Skottie_OpacityPropertyLazyHandle_materialize(lazy_handle);
    Skottie_OpacityPropertyHandle_delete(handle);
}

void property_text(const char node_name[], reskia_skottie_text_property_lazy_handle_t *lazy_handle, void *user_data) {
    auto *state = static_cast<PropertyObserverState *>(user_data);
    if (state != nullptr) {
        state->texts += 1;
        state->last_name = node_name;
    }
    reskia_skottie_text_property_handle_t *handle = Skottie_TextPropertyLazyHandle_materialize(lazy_handle);
    Skottie_TextPropertyHandle_delete(handle);
}

void property_transform(const char node_name[], reskia_skottie_transform_property_lazy_handle_t *lazy_handle, void *user_data) {
    auto *state = static_cast<PropertyObserverState *>(user_data);
    if (state != nullptr) {
        state->transforms += 1;
        state->last_name = node_name;
    }
    reskia_skottie_transform_property_handle_t *handle = Skottie_TransformPropertyLazyHandle_materialize(lazy_handle);
    Skottie_TransformPropertyHandle_delete(handle);
}

void release_property_observer(void *user_data) {
    auto *state = static_cast<PropertyObserverState *>(user_data);
    if (state != nullptr) {
        state->releases += 1;
    }
}

float number_expression_eval(float t, void *user_data) {
    auto *state = static_cast<NumberExpressionState *>(user_data);
    if (state != nullptr) {
        state->evaluates += 1;
    }
    return t + 7.0f;
}

void release_number_expression(void *user_data) {
    auto *state = static_cast<NumberExpressionState *>(user_data);
    if (state != nullptr) {
        state->releases += 1;
    }
}

const char *string_expression_eval(float, void *user_data) {
    auto *state = static_cast<StringExpressionState *>(user_data);
    if (state != nullptr) {
        state->evaluates += 1;
    }
    return "expression text";
}

void release_string_expression(void *user_data) {
    auto *state = static_cast<StringExpressionState *>(user_data);
    if (state != nullptr) {
        state->releases += 1;
    }
}

size_t array_expression_eval(float t, float out_values[], size_t capacity, void *user_data) {
    auto *state = static_cast<ArrayExpressionState *>(user_data);
    if (state != nullptr) {
        state->evaluates += 1;
    }
    if (out_values != nullptr && capacity >= 3) {
        out_values[0] = t;
        out_values[1] = t + 1.0f;
        out_values[2] = t + 2.0f;
    }
    return 3;
}

void release_array_expression(void *user_data) {
    auto *state = static_cast<ArrayExpressionState *>(user_data);
    if (state != nullptr) {
        state->releases += 1;
    }
}

reskia_skottie_number_expression_evaluator_t *create_number_expression(const char expression[], void *user_data) {
    auto *state = static_cast<ExpressionManagerState *>(user_data);
    if (state != nullptr) {
        state->number_creates += expression != nullptr && std::strcmp(expression, "n") == 0 ? 1 : 0;
        return state->number;
    }
    return nullptr;
}

reskia_skottie_string_expression_evaluator_t *create_string_expression(const char expression[], void *user_data) {
    auto *state = static_cast<ExpressionManagerState *>(user_data);
    if (state != nullptr) {
        state->string_creates += expression != nullptr && std::strcmp(expression, "s") == 0 ? 1 : 0;
        return state->string;
    }
    return nullptr;
}

reskia_skottie_array_expression_evaluator_t *create_array_expression(const char expression[], void *user_data) {
    auto *state = static_cast<ExpressionManagerState *>(user_data);
    if (state != nullptr) {
        state->array_creates += expression != nullptr && std::strcmp(expression, "a") == 0 ? 1 : 0;
        return state->array;
    }
    return nullptr;
}

void release_expression_manager(void *user_data) {
    auto *state = static_cast<ExpressionManagerState *>(user_data);
    if (state != nullptr) {
        state->releases += 1;
    }
}

void glyph_decorator_on_decorate(reskia_canvas_t *, const reskia_skottie_glyph_info_t glyphs[], size_t glyph_count, float scale, void *user_data) {
    auto *state = static_cast<GlyphDecoratorState *>(user_data);
    if (state != nullptr) {
        state->decorates += 1;
        state->last_count = glyph_count;
        state->last_scale = scale;
        state->last_advance = glyph_count > 0 && glyphs != nullptr ? glyphs[0].advance : 0.0f;
    }
}

void release_glyph_decorator(void *user_data) {
    auto *state = static_cast<GlyphDecoratorState *>(user_data);
    if (state != nullptr) {
        state->releases += 1;
    }
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
    if (!check(!Skottie_AnimationBuilder_setLogger(builder, nullptr), "Skottie_AnimationBuilder_setLogger null")) {
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    if (!check(!Skottie_AnimationBuilder_setMarkerObserver(builder, nullptr), "Skottie_AnimationBuilder_setMarkerObserver null")) {
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    if (!check(!Skottie_AnimationBuilder_setPrecompInterceptor(builder, nullptr), "Skottie_AnimationBuilder_setPrecompInterceptor null")) {
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    if (!check(!Skottie_AnimationBuilder_setPropertyObserver(builder, nullptr), "Skottie_AnimationBuilder_setPropertyObserver null")) {
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    if (!check(!Skottie_AnimationBuilder_setExpressionManager(builder, nullptr), "Skottie_AnimationBuilder_setExpressionManager null")) {
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }

    LoggerState logger_state;
    reskia_skottie_logger_t *logger = Skottie_Logger_new(log_callback, &logger_state, release_logger);
    if (!check(logger != nullptr, "Skottie_Logger_new")) {
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    Skottie_Logger_log(logger, RESKIA_SKOTTIE_LOGGER_LEVEL_ERROR, "manual log", nullptr);
    if (!check(logger_state.logs == 1 && logger_state.last_level == RESKIA_SKOTTIE_LOGGER_LEVEL_ERROR &&
               std::strcmp(logger_state.last_message, "manual log") == 0,
               "Skottie_Logger_log callback")) {
        Skottie_Logger_release(logger);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    if (!check(Skottie_AnimationBuilder_setLogger(builder, logger), "Skottie_AnimationBuilder_setLogger")) {
        Skottie_Logger_release(logger);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    Skottie_Logger_release(logger);
    if (!check(logger_state.releases == 0, "Skottie_Logger retained by builder")) {
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }

    MarkerState marker_state;
    reskia_skottie_marker_observer_t *marker = Skottie_MarkerObserver_new(marker_callback, &marker_state, release_marker);
    if (!check(marker != nullptr, "Skottie_MarkerObserver_new")) {
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    Skottie_MarkerObserver_onMarker(marker, "manual marker", 1.0f, 2.0f);
    if (!check(marker_state.markers == 1 && marker_state.last_t0 == 1.0f && marker_state.last_t1 == 2.0f &&
               std::strcmp(marker_state.last_name, "manual marker") == 0,
               "Skottie_MarkerObserver_onMarker callback")) {
        Skottie_MarkerObserver_release(marker);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    if (!check(Skottie_AnimationBuilder_setMarkerObserver(builder, marker), "Skottie_AnimationBuilder_setMarkerObserver")) {
        Skottie_MarkerObserver_release(marker);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    Skottie_MarkerObserver_release(marker);
    if (!check(marker_state.releases == 0, "Skottie_MarkerObserver retained by builder")) {
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }

    ExternalLayerState external_state;
    reskia_skottie_external_layer_t *external_layer =
            Skottie_ExternalLayer_new(external_layer_render, &external_state, release_external_layer);
    if (!check(external_layer != nullptr, "Skottie_ExternalLayer_new")) {
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    Skottie_ExternalLayer_render(external_layer, nullptr, 3.5);
    if (!check(external_state.renders == 1 && external_state.last_t == 3.5, "Skottie_ExternalLayer_render callback")) {
        Skottie_ExternalLayer_release(external_layer);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    Skottie_ExternalLayer_ref(external_layer);
    Skottie_ExternalLayer_release(external_layer);
    if (!check(external_state.releases == 0, "Skottie_ExternalLayer retained release keeps alive")) {
        Skottie_ExternalLayer_release(external_layer);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }

    PrecompState precomp_state;
    precomp_state.layer = external_layer;
    reskia_skottie_precomp_interceptor_t *precomp =
            Skottie_PrecompInterceptor_new(precomp_on_load, &precomp_state, release_precomp);
    if (!check(precomp != nullptr, "Skottie_PrecompInterceptor_new")) {
        Skottie_ExternalLayer_release(external_layer);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    sk_size_t precomp_size_handle = SkSize_Make(12.0f, 34.0f);
    auto *precomp_size = reinterpret_cast<reskia_size_t *>(static_sk_size_get_ptr(precomp_size_handle));
    reskia_skottie_external_layer_t *loaded_layer =
            Skottie_PrecompInterceptor_onLoadPrecomp(precomp, "comp_0", "precomp", precomp_size);
    static_sk_size_delete(precomp_size_handle);
    if (!check(loaded_layer != nullptr && precomp_state.loads == 1 &&
               std::strcmp(precomp_state.last_id, "comp_0") == 0 &&
               std::strcmp(precomp_state.last_name, "precomp") == 0 &&
               precomp_state.last_width == 12.0f && precomp_state.last_height == 34.0f,
               "Skottie_PrecompInterceptor_onLoadPrecomp callback")) {
        Skottie_ExternalLayer_release(loaded_layer);
        Skottie_PrecompInterceptor_release(precomp);
        Skottie_ExternalLayer_release(external_layer);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    Skottie_ExternalLayer_release(loaded_layer);
    if (!check(Skottie_AnimationBuilder_setPrecompInterceptor(builder, precomp), "Skottie_AnimationBuilder_setPrecompInterceptor")) {
        Skottie_PrecompInterceptor_release(precomp);
        Skottie_ExternalLayer_release(external_layer);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    Skottie_PrecompInterceptor_release(precomp);
    if (!check(precomp_state.releases == 0, "Skottie_PrecompInterceptor retained by builder")) {
        Skottie_ExternalLayer_release(external_layer);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    Skottie_ExternalLayer_release(external_layer);
    if (!check(external_state.releases == 1, "Skottie_ExternalLayer final release")) {
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }

    PropertyObserverState property_state;
    reskia_skottie_property_observer_t *property_observer =
            Skottie_PropertyObserver_newWithProperties(
                    property_enter,
                    property_leave,
                    property_color,
                    property_opacity,
                    property_text,
                    property_transform,
                    &property_state,
                    release_property_observer);
    if (!check(property_observer != nullptr, "Skottie_PropertyObserver_new")) {
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    Skottie_PropertyObserver_onEnterNode(property_observer, "layer", RESKIA_SKOTTIE_PROPERTY_OBSERVER_NODE_TYPE_LAYER);
    if (!check(property_state.enters == 1 &&
               property_state.last_type == RESKIA_SKOTTIE_PROPERTY_OBSERVER_NODE_TYPE_LAYER &&
               std::strcmp(property_state.last_name, "layer") == 0,
               "Skottie_PropertyObserver_onEnterNode callback")) {
        Skottie_PropertyObserver_release(property_observer);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    Skottie_PropertyObserver_onLeavingNode(property_observer, "effect", RESKIA_SKOTTIE_PROPERTY_OBSERVER_NODE_TYPE_EFFECT);
    if (!check(property_state.leaves == 1 &&
               property_state.last_type == RESKIA_SKOTTIE_PROPERTY_OBSERVER_NODE_TYPE_EFFECT &&
               std::strcmp(property_state.last_name, "effect") == 0,
               "Skottie_PropertyObserver_onLeavingNode callback")) {
        Skottie_PropertyObserver_release(property_observer);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    Skottie_PropertyObserver_onColorProperty(property_observer, "color", nullptr);
    Skottie_PropertyObserver_onOpacityProperty(property_observer, "opacity", nullptr);
    Skottie_PropertyObserver_onTextProperty(property_observer, "text", nullptr);
    Skottie_PropertyObserver_onTransformProperty(property_observer, "transform", nullptr);
    if (!check(property_state.colors == 1 && property_state.opacities == 1 &&
               property_state.texts == 1 && property_state.transforms == 1 &&
               std::strcmp(property_state.last_name, "transform") == 0,
               "Skottie_PropertyObserver property callbacks")) {
        Skottie_PropertyObserver_release(property_observer);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    if (!check(Skottie_ColorPropertyLazyHandle_materialize(nullptr) == nullptr &&
               Skottie_OpacityPropertyLazyHandle_materialize(nullptr) == nullptr &&
               Skottie_TextPropertyLazyHandle_materialize(nullptr) == nullptr &&
               Skottie_TransformPropertyLazyHandle_materialize(nullptr) == nullptr,
               "Skottie property lazy handle null materialize")) {
        Skottie_PropertyObserver_release(property_observer);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    reskia_skottie_transform_property_value_t transform_value{};
    if (!check(!Skottie_TransformPropertyHandle_get(nullptr, &transform_value),
               "Skottie_TransformPropertyHandle_get null")) {
        Skottie_PropertyObserver_release(property_observer);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    if (!check(Skottie_AnimationBuilder_setPropertyObserver(builder, property_observer), "Skottie_AnimationBuilder_setPropertyObserver")) {
        Skottie_PropertyObserver_release(property_observer);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    Skottie_PropertyObserver_release(property_observer);
    if (!check(property_state.releases == 0, "Skottie_PropertyObserver retained by builder")) {
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }

    NumberExpressionState number_state;
    StringExpressionState string_state;
    ArrayExpressionState array_state;
    ExpressionManagerState expression_state;
    expression_state.number = Skottie_NumberExpressionEvaluator_new(number_expression_eval, &number_state, release_number_expression);
    expression_state.string = Skottie_StringExpressionEvaluator_new(string_expression_eval, &string_state, release_string_expression);
    expression_state.array = Skottie_ArrayExpressionEvaluator_new(array_expression_eval, &array_state, release_array_expression);
    if (!check(expression_state.number != nullptr && expression_state.string != nullptr && expression_state.array != nullptr,
               "Skottie expression evaluator new")) {
        Skottie_NumberExpressionEvaluator_release(expression_state.number);
        Skottie_StringExpressionEvaluator_release(expression_state.string);
        Skottie_ArrayExpressionEvaluator_release(expression_state.array);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    if (!check(Skottie_NumberExpressionEvaluator_evaluate(expression_state.number, 2.0f) == 9.0f,
               "Skottie_NumberExpressionEvaluator_evaluate")) {
        Skottie_NumberExpressionEvaluator_release(expression_state.number);
        Skottie_StringExpressionEvaluator_release(expression_state.string);
        Skottie_ArrayExpressionEvaluator_release(expression_state.array);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    reskia_string_t *expression_text = Skottie_StringExpressionEvaluator_evaluate(expression_state.string, 0.0f);
    if (!check(expression_text != nullptr && SkString_equalsText(expression_text, "expression text"),
               "Skottie_StringExpressionEvaluator_evaluate")) {
        SkString_delete(expression_text);
        Skottie_NumberExpressionEvaluator_release(expression_state.number);
        Skottie_StringExpressionEvaluator_release(expression_state.string);
        Skottie_ArrayExpressionEvaluator_release(expression_state.array);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    SkString_delete(expression_text);
    float expression_values[3] = {};
    if (!check(Skottie_ArrayExpressionEvaluator_evaluate(expression_state.array, 4.0f, expression_values, 3) == 3 &&
               expression_values[0] == 4.0f && expression_values[1] == 5.0f && expression_values[2] == 6.0f,
               "Skottie_ArrayExpressionEvaluator_evaluate")) {
        Skottie_NumberExpressionEvaluator_release(expression_state.number);
        Skottie_StringExpressionEvaluator_release(expression_state.string);
        Skottie_ArrayExpressionEvaluator_release(expression_state.array);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    reskia_skottie_expression_manager_t *expression_manager = Skottie_ExpressionManager_new(
            create_number_expression,
            create_string_expression,
            create_array_expression,
            &expression_state,
            release_expression_manager);
    if (!check(expression_manager != nullptr, "Skottie_ExpressionManager_new")) {
        Skottie_NumberExpressionEvaluator_release(expression_state.number);
        Skottie_StringExpressionEvaluator_release(expression_state.string);
        Skottie_ArrayExpressionEvaluator_release(expression_state.array);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    reskia_skottie_number_expression_evaluator_t *created_number =
            Skottie_ExpressionManager_createNumberExpressionEvaluator(expression_manager, "n");
    reskia_skottie_string_expression_evaluator_t *created_string =
            Skottie_ExpressionManager_createStringExpressionEvaluator(expression_manager, "s");
    reskia_skottie_array_expression_evaluator_t *created_array =
            Skottie_ExpressionManager_createArrayExpressionEvaluator(expression_manager, "a");
    if (!check(created_number != nullptr && created_string != nullptr && created_array != nullptr &&
               expression_state.number_creates == 1 && expression_state.string_creates == 1 &&
               expression_state.array_creates == 1,
               "Skottie_ExpressionManager create callbacks")) {
        Skottie_NumberExpressionEvaluator_release(created_number);
        Skottie_StringExpressionEvaluator_release(created_string);
        Skottie_ArrayExpressionEvaluator_release(created_array);
        Skottie_ExpressionManager_release(expression_manager);
        Skottie_NumberExpressionEvaluator_release(expression_state.number);
        Skottie_StringExpressionEvaluator_release(expression_state.string);
        Skottie_ArrayExpressionEvaluator_release(expression_state.array);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    Skottie_NumberExpressionEvaluator_release(created_number);
    Skottie_StringExpressionEvaluator_release(created_string);
    Skottie_ArrayExpressionEvaluator_release(created_array);
    if (!check(Skottie_AnimationBuilder_setExpressionManager(builder, expression_manager),
               "Skottie_AnimationBuilder_setExpressionManager")) {
        Skottie_ExpressionManager_release(expression_manager);
        Skottie_NumberExpressionEvaluator_release(expression_state.number);
        Skottie_StringExpressionEvaluator_release(expression_state.string);
        Skottie_ArrayExpressionEvaluator_release(expression_state.array);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    Skottie_ExpressionManager_release(expression_manager);
    if (!check(expression_state.releases == 0, "Skottie_ExpressionManager retained by builder")) {
        Skottie_NumberExpressionEvaluator_release(expression_state.number);
        Skottie_StringExpressionEvaluator_release(expression_state.string);
        Skottie_ArrayExpressionEvaluator_release(expression_state.array);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }

    GlyphDecoratorState glyph_state;
    reskia_skottie_glyph_decorator_t *decorator =
            Skottie_GlyphDecorator_new(glyph_decorator_on_decorate, &glyph_state, release_glyph_decorator);
    if (!check(decorator != nullptr, "Skottie_GlyphDecorator_new")) {
        Skottie_NumberExpressionEvaluator_release(expression_state.number);
        Skottie_StringExpressionEvaluator_release(expression_state.string);
        Skottie_ArrayExpressionEvaluator_release(expression_state.array);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    reskia_skottie_glyph_info_t glyph{};
    glyph.bounds_left = 1.0f;
    glyph.bounds_top = 2.0f;
    glyph.bounds_right = 3.0f;
    glyph.bounds_bottom = 4.0f;
    glyph.matrix[0] = 1.0f;
    glyph.matrix[4] = 1.0f;
    glyph.matrix[8] = 1.0f;
    glyph.cluster = 5;
    glyph.advance = 6.0f;
    Skottie_GlyphDecorator_onDecorate(decorator, nullptr, &glyph, 1, 0.75f);
    if (!check(glyph_state.decorates == 1 && glyph_state.last_count == 1 &&
               glyph_state.last_scale == 0.75f && glyph_state.last_advance == 6.0f,
               "Skottie_GlyphDecorator_onDecorate callback")) {
        Skottie_GlyphDecorator_release(decorator);
        Skottie_NumberExpressionEvaluator_release(expression_state.number);
        Skottie_StringExpressionEvaluator_release(expression_state.string);
        Skottie_ArrayExpressionEvaluator_release(expression_state.array);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    reskia_skottie_text_property_value_t *decorated_text = TextPropertyValue_new();
    if (!check(decorated_text != nullptr, "TextPropertyValue_new for decorator")) {
        Skottie_GlyphDecorator_release(decorator);
        Skottie_NumberExpressionEvaluator_release(expression_state.number);
        Skottie_StringExpressionEvaluator_release(expression_state.string);
        Skottie_ArrayExpressionEvaluator_release(expression_state.array);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    TextPropertyValue_setDecorator(decorated_text, decorator);
    Skottie_GlyphDecorator_release(decorator);
    if (!check(glyph_state.releases == 0, "TextPropertyValue retains glyph decorator")) {
        TextPropertyValue_delete(decorated_text);
        Skottie_NumberExpressionEvaluator_release(expression_state.number);
        Skottie_StringExpressionEvaluator_release(expression_state.string);
        Skottie_ArrayExpressionEvaluator_release(expression_state.array);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    TextPropertyValue_delete(decorated_text);
    if (!check(glyph_state.releases == 1, "TextPropertyValue releases glyph decorator")) {
        Skottie_NumberExpressionEvaluator_release(expression_state.number);
        Skottie_StringExpressionEvaluator_release(expression_state.string);
        Skottie_ArrayExpressionEvaluator_release(expression_state.array);
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
    reskia_skottie_shaper_result_t *point_shape =
            Skottie_Shaper_ShapeAtPoint("shape me", text_value, 0.0f, 0.0f, 0);
    if (!check(point_shape != nullptr &&
               Skottie_Shaper_Result_fragmentCount(point_shape) > 0 &&
               Skottie_Shaper_Result_scale(point_shape) > 0.0f,
               "Skottie_Shaper_ShapeAtPoint result")) {
        Skottie_Shaper_Result_delete(point_shape);
        TextPropertyValue_delete(text_value);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    sk_rect_t box_handle = SkRect_MakeWH(128.0f, 64.0f);
    sk_rect_t bounds_handle = SkRect_MakeEmpty();
    auto *box = reinterpret_cast<reskia_rect_t *>(static_sk_rect_get_ptr(box_handle));
    auto *bounds = reinterpret_cast<reskia_rect_t *>(static_sk_rect_get_ptr(bounds_handle));
    reskia_skottie_shaper_result_t *box_shape =
            Skottie_Shaper_ShapeInBox("shape me", text_value, box, 0);
    if (!check(box_shape != nullptr &&
               Skottie_Shaper_Result_fragmentCount(box_shape) > 0 &&
               Skottie_Shaper_Result_computeVisualBounds(box_shape, bounds),
               "Skottie_Shaper_ShapeInBox result")) {
        Skottie_Shaper_Result_delete(box_shape);
        Skottie_Shaper_Result_delete(point_shape);
        static_sk_rect_delete(bounds_handle);
        static_sk_rect_delete(box_handle);
        TextPropertyValue_delete(text_value);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    if (!check(Skottie_Shaper_Result_missingGlyphCount(nullptr) == 0 &&
               !Skottie_Shaper_Result_computeVisualBounds(nullptr, bounds) &&
               Skottie_Shaper_ShapeAtPoint(nullptr, text_value, 0.0f, 0.0f, 0) == nullptr &&
               Skottie_Shaper_ShapeInBox("shape me", text_value, nullptr, 0) == nullptr,
               "Skottie_Shaper null paths")) {
        Skottie_Shaper_Result_delete(box_shape);
        Skottie_Shaper_Result_delete(point_shape);
        static_sk_rect_delete(bounds_handle);
        static_sk_rect_delete(box_handle);
        TextPropertyValue_delete(text_value);
        SlotManager_release(manager);
        Skottie_Animation_release(animation);
        Skottie_AnimationBuilder_delete(builder);
        return false;
    }
    Skottie_Shaper_Result_delete(box_shape);
    Skottie_Shaper_Result_delete(point_shape);
    static_sk_rect_delete(bounds_handle);
    static_sk_rect_delete(box_handle);
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
    if (!check(logger_state.releases == 1, "Skottie_Logger released with builder")) {
        return false;
    }
    if (!check(marker_state.releases == 1, "Skottie_MarkerObserver released with builder")) {
        return false;
    }
    if (!check(precomp_state.releases == 1, "Skottie_PrecompInterceptor released with builder")) {
        return false;
    }
    if (!check(property_state.releases == 1, "Skottie_PropertyObserver released with builder")) {
        return false;
    }
    if (!check(expression_state.releases == 1, "Skottie_ExpressionManager released with builder")) {
        return false;
    }
    Skottie_NumberExpressionEvaluator_release(expression_state.number);
    Skottie_StringExpressionEvaluator_release(expression_state.string);
    Skottie_ArrayExpressionEvaluator_release(expression_state.array);
    if (!check(number_state.releases == 1 && string_state.releases == 1 && array_state.releases == 1,
               "Skottie expression evaluators final release")) {
        return false;
    }
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
