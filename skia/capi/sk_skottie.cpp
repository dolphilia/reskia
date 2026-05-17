#include "sk_skottie.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkFontMgr.h"
#include "include/core/SkPaint.h"
#include "include/core/SkRect.h"
#include "include/core/SkString.h"
#include "modules/skottie/include/Skottie.h"
#include "modules/skottie/include/SkottieProperty.h"
#include "modules/skottie/include/TextShaper.h"
#include "modules/skresources/include/SkResources.h"

#include <vector>

#include "../handles/static_sk_size_t-internal.h"
#include "../handles/static_sk_font_mgr-internal.h"
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

inline skottie::Shaper::Result *to_shaper_result(reskia_skottie_shaper_result_t *result) {
    return reinterpret_cast<skottie::Shaper::Result *>(result);
}

inline const skottie::Shaper::Result *to_shaper_result(const reskia_skottie_shaper_result_t *result) {
    return reinterpret_cast<const skottie::Shaper::Result *>(result);
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

inline skottie::Logger *to_logger(reskia_skottie_logger_t *logger) {
    return reinterpret_cast<skottie::Logger *>(logger);
}

inline skottie::MarkerObserver *to_marker_observer(reskia_skottie_marker_observer_t *observer) {
    return reinterpret_cast<skottie::MarkerObserver *>(observer);
}

inline skottie::ExternalLayer *to_external_layer(reskia_skottie_external_layer_t *layer) {
    return reinterpret_cast<skottie::ExternalLayer *>(layer);
}

inline skottie::PrecompInterceptor *to_precomp_interceptor(reskia_skottie_precomp_interceptor_t *interceptor) {
    return reinterpret_cast<skottie::PrecompInterceptor *>(interceptor);
}

inline skottie::PropertyObserver *to_property_observer(reskia_skottie_property_observer_t *observer) {
    return reinterpret_cast<skottie::PropertyObserver *>(observer);
}

inline skottie::ColorPropertyHandle *to_color_property_handle(reskia_skottie_color_property_handle_t *handle) {
    return reinterpret_cast<skottie::ColorPropertyHandle *>(handle);
}

inline const skottie::ColorPropertyHandle *to_color_property_handle(const reskia_skottie_color_property_handle_t *handle) {
    return reinterpret_cast<const skottie::ColorPropertyHandle *>(handle);
}

inline skottie::OpacityPropertyHandle *to_opacity_property_handle(reskia_skottie_opacity_property_handle_t *handle) {
    return reinterpret_cast<skottie::OpacityPropertyHandle *>(handle);
}

inline const skottie::OpacityPropertyHandle *to_opacity_property_handle(const reskia_skottie_opacity_property_handle_t *handle) {
    return reinterpret_cast<const skottie::OpacityPropertyHandle *>(handle);
}

inline skottie::TextPropertyHandle *to_text_property_handle(reskia_skottie_text_property_handle_t *handle) {
    return reinterpret_cast<skottie::TextPropertyHandle *>(handle);
}

inline const skottie::TextPropertyHandle *to_text_property_handle(const reskia_skottie_text_property_handle_t *handle) {
    return reinterpret_cast<const skottie::TextPropertyHandle *>(handle);
}

inline skottie::TransformPropertyHandle *to_transform_property_handle(reskia_skottie_transform_property_handle_t *handle) {
    return reinterpret_cast<skottie::TransformPropertyHandle *>(handle);
}

inline const skottie::TransformPropertyHandle *to_transform_property_handle(const reskia_skottie_transform_property_handle_t *handle) {
    return reinterpret_cast<const skottie::TransformPropertyHandle *>(handle);
}

inline skottie::ExpressionEvaluator<float> *to_number_expression_evaluator(reskia_skottie_number_expression_evaluator_t *evaluator) {
    return reinterpret_cast<skottie::ExpressionEvaluator<float> *>(evaluator);
}

inline skottie::ExpressionEvaluator<SkString> *to_string_expression_evaluator(reskia_skottie_string_expression_evaluator_t *evaluator) {
    return reinterpret_cast<skottie::ExpressionEvaluator<SkString> *>(evaluator);
}

inline skottie::ExpressionEvaluator<std::vector<float>> *to_array_expression_evaluator(reskia_skottie_array_expression_evaluator_t *evaluator) {
    return reinterpret_cast<skottie::ExpressionEvaluator<std::vector<float>> *>(evaluator);
}

inline skottie::ExpressionManager *to_expression_manager(reskia_skottie_expression_manager_t *manager) {
    return reinterpret_cast<skottie::ExpressionManager *>(manager);
}

inline skottie::GlyphDecorator *to_glyph_decorator(reskia_skottie_glyph_decorator_t *decorator) {
    return reinterpret_cast<skottie::GlyphDecorator *>(decorator);
}

skottie::Logger::Level logger_level_or_warning(reskia_skottie_logger_level_t level) {
    switch (level) {
        case RESKIA_SKOTTIE_LOGGER_LEVEL_ERROR:
            return skottie::Logger::Level::kError;
        case RESKIA_SKOTTIE_LOGGER_LEVEL_WARNING:
        default:
            return skottie::Logger::Level::kWarning;
    }
}

skottie::PropertyObserver::NodeType property_node_type_or_other(reskia_skottie_property_observer_node_type_t node_type) {
    switch (node_type) {
        case RESKIA_SKOTTIE_PROPERTY_OBSERVER_NODE_TYPE_COMPOSITION:
            return skottie::PropertyObserver::NodeType::COMPOSITION;
        case RESKIA_SKOTTIE_PROPERTY_OBSERVER_NODE_TYPE_LAYER:
            return skottie::PropertyObserver::NodeType::LAYER;
        case RESKIA_SKOTTIE_PROPERTY_OBSERVER_NODE_TYPE_EFFECT:
            return skottie::PropertyObserver::NodeType::EFFECT;
        case RESKIA_SKOTTIE_PROPERTY_OBSERVER_NODE_TYPE_OTHER:
        default:
            return skottie::PropertyObserver::NodeType::OTHER;
    }
}

reskia_skottie_property_observer_node_type_t to_c_property_node_type(skottie::PropertyObserver::NodeType node_type) {
    switch (node_type) {
        case skottie::PropertyObserver::NodeType::COMPOSITION:
            return RESKIA_SKOTTIE_PROPERTY_OBSERVER_NODE_TYPE_COMPOSITION;
        case skottie::PropertyObserver::NodeType::LAYER:
            return RESKIA_SKOTTIE_PROPERTY_OBSERVER_NODE_TYPE_LAYER;
        case skottie::PropertyObserver::NodeType::EFFECT:
            return RESKIA_SKOTTIE_PROPERTY_OBSERVER_NODE_TYPE_EFFECT;
        case skottie::PropertyObserver::NodeType::OTHER:
        default:
            return RESKIA_SKOTTIE_PROPERTY_OBSERVER_NODE_TYPE_OTHER;
    }
}

reskia_string_t *copy_slot_id(const skia_private::TArray<SkString> &ids, size_t index) {
    if (index >= ids.size()) {
        return nullptr;
    }
    return reinterpret_cast<reskia_string_t *>(new SkString(ids[static_cast<int>(index)]));
}

template <typename HandleT>
struct ReskiaSkottiePropertyLazyHandle {
    const skottie::PropertyObserver::LazyHandle<HandleT> *lazy_handle;
};

using ReskiaSkottieColorPropertyLazyHandle = ReskiaSkottiePropertyLazyHandle<skottie::ColorPropertyHandle>;
using ReskiaSkottieOpacityPropertyLazyHandle = ReskiaSkottiePropertyLazyHandle<skottie::OpacityPropertyHandle>;
using ReskiaSkottieTextPropertyLazyHandle = ReskiaSkottiePropertyLazyHandle<skottie::TextPropertyHandle>;
using ReskiaSkottieTransformPropertyLazyHandle = ReskiaSkottiePropertyLazyHandle<skottie::TransformPropertyHandle>;

template <typename HandleT, typename LazyHandleT, typename CHandleT>
CHandleT *materialize_property_handle(LazyHandleT *lazy_handle) {
    auto *lazy = reinterpret_cast<ReskiaSkottiePropertyLazyHandle<HandleT> *>(lazy_handle);
    if (lazy == nullptr || lazy->lazy_handle == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<CHandleT *>((*lazy->lazy_handle)().release());
}

skottie::TransformPropertyValue transform_property_value_or_default(const reskia_skottie_transform_property_value_t *value) {
    if (value == nullptr) {
        return {
                SkPoint::Make(0.0f, 0.0f),
                SkPoint::Make(0.0f, 0.0f),
                SkVector::Make(0.0f, 0.0f),
                0.0f,
                0.0f,
                0.0f,
        };
    }
    return {
            SkPoint::Make(value->anchor_x, value->anchor_y),
            SkPoint::Make(value->position_x, value->position_y),
            SkVector::Make(value->scale_x, value->scale_y),
            value->rotation,
            value->skew,
            value->skew_axis,
    };
}

sk_sp<SkFontMgr> font_mgr_or_default(sk_font_mgr_t font_mgr) {
    return font_mgr != 0 ? static_sk_font_mgr_get_entity(font_mgr) : SkFontMgr::RefDefault();
}

skottie::Shaper::TextDesc make_shaper_text_desc(
        const reskia_skottie_text_property_value_t *desc,
        const sk_sp<SkTypeface> &typeface) {
    skottie::Shaper::TextDesc out{typeface};
    if (desc == nullptr) {
        return out;
    }
    const auto *value = to_text_property_value(desc);
    out.fTextSize = value->fTextSize;
    out.fMinTextSize = value->fMinTextSize;
    out.fMaxTextSize = value->fMaxTextSize;
    out.fLineHeight = value->fLineHeight;
    out.fLineShift = value->fLineShift;
    out.fAscent = value->fAscent;
    out.fHAlign = value->fHAlign;
    out.fVAlign = value->fVAlign;
    out.fResize = value->fResize;
    out.fLinebreak = value->fLineBreak;
    out.fDirection = value->fDirection;
    out.fCapitalization = value->fCapitalization;
    out.fMaxLines = value->fMaxLines;
    out.fLocale = value->fLocale.c_str();
    return out;
}

void to_c_transform_property_value(
        const skottie::TransformPropertyValue &value,
        reskia_skottie_transform_property_value_t *out_value) {
    out_value->anchor_x = value.fAnchorPoint.x();
    out_value->anchor_y = value.fAnchorPoint.y();
    out_value->position_x = value.fPosition.x();
    out_value->position_y = value.fPosition.y();
    out_value->scale_x = value.fScale.x();
    out_value->scale_y = value.fScale.y();
    out_value->rotation = value.fRotation;
    out_value->skew = value.fSkew;
    out_value->skew_axis = value.fSkewAxis;
}

class ReskiaSkottieLogger final : public skottie::Logger {
public:
    ReskiaSkottieLogger(
            reskia_skottie_logger_log_proc_t log,
            void *user_data,
            reskia_callback_release_proc_t release_proc)
        : log_(log)
        , user_data_(user_data)
        , release_proc_(release_proc) {}

    ~ReskiaSkottieLogger() override {
        if (release_proc_ != nullptr) {
            release_proc_(user_data_);
        }
    }

    void log(Level level, const char message[], const char *json) override {
        if (log_ != nullptr) {
            log_(static_cast<reskia_skottie_logger_level_t>(level), message, json, user_data_);
        }
    }

private:
    reskia_skottie_logger_log_proc_t log_;
    void *user_data_;
    reskia_callback_release_proc_t release_proc_;
};

class ReskiaSkottieMarkerObserver final : public skottie::MarkerObserver {
public:
    ReskiaSkottieMarkerObserver(
            reskia_skottie_marker_observer_on_marker_proc_t on_marker,
            void *user_data,
            reskia_callback_release_proc_t release_proc)
        : on_marker_(on_marker)
        , user_data_(user_data)
        , release_proc_(release_proc) {}

    ~ReskiaSkottieMarkerObserver() override {
        if (release_proc_ != nullptr) {
            release_proc_(user_data_);
        }
    }

    void onMarker(const char name[], float t0, float t1) override {
        if (on_marker_ != nullptr) {
            on_marker_(name, t0, t1, user_data_);
        }
    }

private:
    reskia_skottie_marker_observer_on_marker_proc_t on_marker_;
    void *user_data_;
    reskia_callback_release_proc_t release_proc_;
};

class ReskiaSkottieExternalLayer final : public skottie::ExternalLayer {
public:
    ReskiaSkottieExternalLayer(
            reskia_skottie_external_layer_render_proc_t render,
            void *user_data,
            reskia_callback_release_proc_t release_proc)
        : render_(render)
        , user_data_(user_data)
        , release_proc_(release_proc) {}

    ~ReskiaSkottieExternalLayer() override {
        if (release_proc_ != nullptr) {
            release_proc_(user_data_);
        }
    }

    void render(SkCanvas *canvas, double t) override {
        if (render_ != nullptr) {
            render_(reinterpret_cast<reskia_canvas_t *>(canvas), t, user_data_);
        }
    }

private:
    reskia_skottie_external_layer_render_proc_t render_;
    void *user_data_;
    reskia_callback_release_proc_t release_proc_;
};

class ReskiaSkottiePrecompInterceptor final : public skottie::PrecompInterceptor {
public:
    ReskiaSkottiePrecompInterceptor(
            reskia_skottie_precomp_interceptor_on_load_precomp_proc_t on_load_precomp,
            void *user_data,
            reskia_callback_release_proc_t release_proc)
        : on_load_precomp_(on_load_precomp)
        , user_data_(user_data)
        , release_proc_(release_proc) {}

    ~ReskiaSkottiePrecompInterceptor() override {
        if (release_proc_ != nullptr) {
            release_proc_(user_data_);
        }
    }

    sk_sp<skottie::ExternalLayer> onLoadPrecomp(const char id[], const char name[], const SkSize &size) override {
        if (on_load_precomp_ == nullptr) {
            return nullptr;
        }
        auto *layer = on_load_precomp_(
                id,
                name,
                reinterpret_cast<const reskia_size_t *>(&size),
                user_data_);
        return layer != nullptr ? sk_ref_sp(to_external_layer(layer)) : nullptr;
    }

private:
    reskia_skottie_precomp_interceptor_on_load_precomp_proc_t on_load_precomp_;
    void *user_data_;
    reskia_callback_release_proc_t release_proc_;
};

class ReskiaSkottiePropertyObserver final : public skottie::PropertyObserver {
public:
    ReskiaSkottiePropertyObserver(
            reskia_skottie_property_observer_node_proc_t on_enter_node,
            reskia_skottie_property_observer_node_proc_t on_leaving_node,
            void *user_data,
            reskia_callback_release_proc_t release_proc)
        : on_enter_node_(on_enter_node)
        , on_leaving_node_(on_leaving_node)
        , on_color_property_(nullptr)
        , on_opacity_property_(nullptr)
        , on_text_property_(nullptr)
        , on_transform_property_(nullptr)
        , user_data_(user_data)
        , release_proc_(release_proc) {}

    ReskiaSkottiePropertyObserver(
            reskia_skottie_property_observer_node_proc_t on_enter_node,
            reskia_skottie_property_observer_node_proc_t on_leaving_node,
            reskia_skottie_property_observer_color_proc_t on_color_property,
            reskia_skottie_property_observer_opacity_proc_t on_opacity_property,
            reskia_skottie_property_observer_text_proc_t on_text_property,
            reskia_skottie_property_observer_transform_proc_t on_transform_property,
            void *user_data,
            reskia_callback_release_proc_t release_proc)
        : on_enter_node_(on_enter_node)
        , on_leaving_node_(on_leaving_node)
        , on_color_property_(on_color_property)
        , on_opacity_property_(on_opacity_property)
        , on_text_property_(on_text_property)
        , on_transform_property_(on_transform_property)
        , user_data_(user_data)
        , release_proc_(release_proc) {}

    ~ReskiaSkottiePropertyObserver() override {
        if (release_proc_ != nullptr) {
            release_proc_(user_data_);
        }
    }

    void onEnterNode(const char node_name[], NodeType node_type) override {
        if (on_enter_node_ != nullptr) {
            on_enter_node_(node_name, to_c_property_node_type(node_type), user_data_);
        }
    }

    void onLeavingNode(const char node_name[], NodeType node_type) override {
        if (on_leaving_node_ != nullptr) {
            on_leaving_node_(node_name, to_c_property_node_type(node_type), user_data_);
        }
    }

    void onColorProperty(const char node_name[], const LazyHandle<skottie::ColorPropertyHandle> &lazy_handle) override {
        if (on_color_property_ != nullptr) {
            ReskiaSkottieColorPropertyLazyHandle lazy{&lazy_handle};
            on_color_property_(node_name, reinterpret_cast<reskia_skottie_color_property_lazy_handle_t *>(&lazy), user_data_);
        }
    }

    void onOpacityProperty(const char node_name[], const LazyHandle<skottie::OpacityPropertyHandle> &lazy_handle) override {
        if (on_opacity_property_ != nullptr) {
            ReskiaSkottieOpacityPropertyLazyHandle lazy{&lazy_handle};
            on_opacity_property_(node_name, reinterpret_cast<reskia_skottie_opacity_property_lazy_handle_t *>(&lazy), user_data_);
        }
    }

    void onTextProperty(const char node_name[], const LazyHandle<skottie::TextPropertyHandle> &lazy_handle) override {
        if (on_text_property_ != nullptr) {
            ReskiaSkottieTextPropertyLazyHandle lazy{&lazy_handle};
            on_text_property_(node_name, reinterpret_cast<reskia_skottie_text_property_lazy_handle_t *>(&lazy), user_data_);
        }
    }

    void onTransformProperty(const char node_name[], const LazyHandle<skottie::TransformPropertyHandle> &lazy_handle) override {
        if (on_transform_property_ != nullptr) {
            ReskiaSkottieTransformPropertyLazyHandle lazy{&lazy_handle};
            on_transform_property_(node_name, reinterpret_cast<reskia_skottie_transform_property_lazy_handle_t *>(&lazy), user_data_);
        }
    }

private:
    reskia_skottie_property_observer_node_proc_t on_enter_node_;
    reskia_skottie_property_observer_node_proc_t on_leaving_node_;
    reskia_skottie_property_observer_color_proc_t on_color_property_;
    reskia_skottie_property_observer_opacity_proc_t on_opacity_property_;
    reskia_skottie_property_observer_text_proc_t on_text_property_;
    reskia_skottie_property_observer_transform_proc_t on_transform_property_;
    void *user_data_;
    reskia_callback_release_proc_t release_proc_;
};

class ReskiaSkottieNumberExpressionEvaluator final : public skottie::ExpressionEvaluator<float> {
public:
    ReskiaSkottieNumberExpressionEvaluator(reskia_skottie_number_expression_evaluate_proc_t evaluate, void *user_data, reskia_callback_release_proc_t release_proc)
        : evaluate_(evaluate), user_data_(user_data), release_proc_(release_proc) {}

    ~ReskiaSkottieNumberExpressionEvaluator() override {
        if (release_proc_ != nullptr) {
            release_proc_(user_data_);
        }
    }

    float evaluate(float t) override {
        return evaluate_ != nullptr ? evaluate_(t, user_data_) : 0.0f;
    }

private:
    reskia_skottie_number_expression_evaluate_proc_t evaluate_;
    void *user_data_;
    reskia_callback_release_proc_t release_proc_;
};

class ReskiaSkottieStringExpressionEvaluator final : public skottie::ExpressionEvaluator<SkString> {
public:
    ReskiaSkottieStringExpressionEvaluator(reskia_skottie_string_expression_evaluate_proc_t evaluate, void *user_data, reskia_callback_release_proc_t release_proc)
        : evaluate_(evaluate), user_data_(user_data), release_proc_(release_proc) {}

    ~ReskiaSkottieStringExpressionEvaluator() override {
        if (release_proc_ != nullptr) {
            release_proc_(user_data_);
        }
    }

    SkString evaluate(float t) override {
        if (evaluate_ == nullptr) {
            return SkString();
        }
        const char *value = evaluate_(t, user_data_);
        return value != nullptr ? SkString(value) : SkString();
    }

private:
    reskia_skottie_string_expression_evaluate_proc_t evaluate_;
    void *user_data_;
    reskia_callback_release_proc_t release_proc_;
};

class ReskiaSkottieArrayExpressionEvaluator final : public skottie::ExpressionEvaluator<std::vector<float>> {
public:
    ReskiaSkottieArrayExpressionEvaluator(reskia_skottie_array_expression_evaluate_proc_t evaluate, void *user_data, reskia_callback_release_proc_t release_proc)
        : evaluate_(evaluate), user_data_(user_data), release_proc_(release_proc) {}

    ~ReskiaSkottieArrayExpressionEvaluator() override {
        if (release_proc_ != nullptr) {
            release_proc_(user_data_);
        }
    }

    std::vector<float> evaluate(float t) override {
        if (evaluate_ == nullptr) {
            return {};
        }
        const size_t count = evaluate_(t, nullptr, 0, user_data_);
        std::vector<float> values(count);
        if (count > 0) {
            const size_t written = evaluate_(t, values.data(), values.size(), user_data_);
            values.resize(written <= values.size() ? written : values.size());
        }
        return values;
    }

private:
    reskia_skottie_array_expression_evaluate_proc_t evaluate_;
    void *user_data_;
    reskia_callback_release_proc_t release_proc_;
};

class ReskiaSkottieExpressionManager final : public skottie::ExpressionManager {
public:
    ReskiaSkottieExpressionManager(
            reskia_skottie_expression_manager_create_number_proc_t create_number,
            reskia_skottie_expression_manager_create_string_proc_t create_string,
            reskia_skottie_expression_manager_create_array_proc_t create_array,
            void *user_data,
            reskia_callback_release_proc_t release_proc)
        : create_number_(create_number)
        , create_string_(create_string)
        , create_array_(create_array)
        , user_data_(user_data)
        , release_proc_(release_proc) {}

    ~ReskiaSkottieExpressionManager() override {
        if (release_proc_ != nullptr) {
            release_proc_(user_data_);
        }
    }

    sk_sp<skottie::ExpressionEvaluator<float>> createNumberExpressionEvaluator(const char expression[]) override {
        if (create_number_ == nullptr) {
            return nullptr;
        }
        auto *evaluator = create_number_(expression, user_data_);
        return evaluator != nullptr ? sk_ref_sp(to_number_expression_evaluator(evaluator)) : nullptr;
    }

    sk_sp<skottie::ExpressionEvaluator<SkString>> createStringExpressionEvaluator(const char expression[]) override {
        if (create_string_ == nullptr) {
            return nullptr;
        }
        auto *evaluator = create_string_(expression, user_data_);
        return evaluator != nullptr ? sk_ref_sp(to_string_expression_evaluator(evaluator)) : nullptr;
    }

    sk_sp<skottie::ExpressionEvaluator<std::vector<float>>> createArrayExpressionEvaluator(const char expression[]) override {
        if (create_array_ == nullptr) {
            return nullptr;
        }
        auto *evaluator = create_array_(expression, user_data_);
        return evaluator != nullptr ? sk_ref_sp(to_array_expression_evaluator(evaluator)) : nullptr;
    }

private:
    reskia_skottie_expression_manager_create_number_proc_t create_number_;
    reskia_skottie_expression_manager_create_string_proc_t create_string_;
    reskia_skottie_expression_manager_create_array_proc_t create_array_;
    void *user_data_;
    reskia_callback_release_proc_t release_proc_;
};

class ReskiaSkottieGlyphDecorator final : public skottie::GlyphDecorator {
public:
    ReskiaSkottieGlyphDecorator(
            reskia_skottie_glyph_decorator_on_decorate_proc_t on_decorate,
            void *user_data,
            reskia_callback_release_proc_t release_proc)
        : on_decorate_(on_decorate)
        , user_data_(user_data)
        , release_proc_(release_proc) {}

    ~ReskiaSkottieGlyphDecorator() override {
        if (release_proc_ != nullptr) {
            release_proc_(user_data_);
        }
    }

    void onDecorate(SkCanvas *canvas, const TextInfo &text_info) override {
        if (on_decorate_ == nullptr) {
            return;
        }
        std::vector<reskia_skottie_glyph_info_t> glyphs(text_info.fGlyphs.size());
        for (size_t i = 0; i < glyphs.size(); ++i) {
            const GlyphInfo &src = text_info.fGlyphs[i];
            glyphs[i].bounds_left = src.fBounds.left();
            glyphs[i].bounds_top = src.fBounds.top();
            glyphs[i].bounds_right = src.fBounds.right();
            glyphs[i].bounds_bottom = src.fBounds.bottom();
            src.fMatrix.get9(glyphs[i].matrix);
            glyphs[i].cluster = src.fCluster;
            glyphs[i].advance = src.fAdvance;
        }
        on_decorate_(
                reinterpret_cast<reskia_canvas_t *>(canvas),
                glyphs.empty() ? nullptr : glyphs.data(),
                glyphs.size(),
                text_info.fScale,
                user_data_);
    }

private:
    reskia_skottie_glyph_decorator_on_decorate_proc_t on_decorate_;
    void *user_data_;
    reskia_callback_release_proc_t release_proc_;
};

} // namespace

extern "C" {

reskia_skottie_logger_t *Skottie_Logger_new(
        reskia_skottie_logger_log_proc_t log,
        void *user_data,
        reskia_callback_release_proc_t release_proc) {
    return reinterpret_cast<reskia_skottie_logger_t *>(
            new ReskiaSkottieLogger(log, user_data, release_proc));
}

void Skottie_Logger_ref(reskia_skottie_logger_t *logger) {
    if (logger != nullptr) {
        to_logger(logger)->ref();
    }
}

void Skottie_Logger_unref(reskia_skottie_logger_t *logger) {
    if (logger != nullptr) {
        to_logger(logger)->unref();
    }
}

void Skottie_Logger_release(reskia_skottie_logger_t *logger) {
    Skottie_Logger_unref(logger);
}

void Skottie_Logger_log(reskia_skottie_logger_t *logger, reskia_skottie_logger_level_t level, const char message[], const char json[]) {
    if (logger != nullptr) {
        to_logger(logger)->log(logger_level_or_warning(level), message, json);
    }
}

reskia_skottie_marker_observer_t *Skottie_MarkerObserver_new(
        reskia_skottie_marker_observer_on_marker_proc_t on_marker,
        void *user_data,
        reskia_callback_release_proc_t release_proc) {
    return reinterpret_cast<reskia_skottie_marker_observer_t *>(
            new ReskiaSkottieMarkerObserver(on_marker, user_data, release_proc));
}

void Skottie_MarkerObserver_ref(reskia_skottie_marker_observer_t *observer) {
    if (observer != nullptr) {
        to_marker_observer(observer)->ref();
    }
}

void Skottie_MarkerObserver_unref(reskia_skottie_marker_observer_t *observer) {
    if (observer != nullptr) {
        to_marker_observer(observer)->unref();
    }
}

void Skottie_MarkerObserver_release(reskia_skottie_marker_observer_t *observer) {
    Skottie_MarkerObserver_unref(observer);
}

void Skottie_MarkerObserver_onMarker(reskia_skottie_marker_observer_t *observer, const char name[], float t0, float t1) {
    if (observer != nullptr) {
        to_marker_observer(observer)->onMarker(name, t0, t1);
    }
}

reskia_skottie_external_layer_t *Skottie_ExternalLayer_new(
        reskia_skottie_external_layer_render_proc_t render,
        void *user_data,
        reskia_callback_release_proc_t release_proc) {
    return reinterpret_cast<reskia_skottie_external_layer_t *>(
            new ReskiaSkottieExternalLayer(render, user_data, release_proc));
}

void Skottie_ExternalLayer_ref(reskia_skottie_external_layer_t *layer) {
    if (layer != nullptr) {
        to_external_layer(layer)->ref();
    }
}

void Skottie_ExternalLayer_unref(reskia_skottie_external_layer_t *layer) {
    if (layer != nullptr) {
        to_external_layer(layer)->unref();
    }
}

void Skottie_ExternalLayer_release(reskia_skottie_external_layer_t *layer) {
    Skottie_ExternalLayer_unref(layer);
}

void Skottie_ExternalLayer_render(reskia_skottie_external_layer_t *layer, reskia_canvas_t *canvas, double t) {
    if (layer != nullptr) {
        to_external_layer(layer)->render(reinterpret_cast<SkCanvas *>(canvas), t);
    }
}

reskia_skottie_precomp_interceptor_t *Skottie_PrecompInterceptor_new(
        reskia_skottie_precomp_interceptor_on_load_precomp_proc_t on_load_precomp,
        void *user_data,
        reskia_callback_release_proc_t release_proc) {
    return reinterpret_cast<reskia_skottie_precomp_interceptor_t *>(
            new ReskiaSkottiePrecompInterceptor(on_load_precomp, user_data, release_proc));
}

void Skottie_PrecompInterceptor_ref(reskia_skottie_precomp_interceptor_t *interceptor) {
    if (interceptor != nullptr) {
        to_precomp_interceptor(interceptor)->ref();
    }
}

void Skottie_PrecompInterceptor_unref(reskia_skottie_precomp_interceptor_t *interceptor) {
    if (interceptor != nullptr) {
        to_precomp_interceptor(interceptor)->unref();
    }
}

void Skottie_PrecompInterceptor_release(reskia_skottie_precomp_interceptor_t *interceptor) {
    Skottie_PrecompInterceptor_unref(interceptor);
}

reskia_skottie_external_layer_t *Skottie_PrecompInterceptor_onLoadPrecomp(
        reskia_skottie_precomp_interceptor_t *interceptor,
        const char id[],
        const char name[],
        const reskia_size_t *size) {
    if (interceptor == nullptr || size == nullptr) {
        return nullptr;
    }
    sk_sp<skottie::ExternalLayer> layer = to_precomp_interceptor(interceptor)->onLoadPrecomp(
            id,
            name,
            *reinterpret_cast<const SkSize *>(size));
    return reinterpret_cast<reskia_skottie_external_layer_t *>(layer.release());
}

reskia_skottie_property_observer_t *Skottie_PropertyObserver_new(
        reskia_skottie_property_observer_node_proc_t on_enter_node,
        reskia_skottie_property_observer_node_proc_t on_leaving_node,
        void *user_data,
        reskia_callback_release_proc_t release_proc) {
    return reinterpret_cast<reskia_skottie_property_observer_t *>(
            new ReskiaSkottiePropertyObserver(on_enter_node, on_leaving_node, user_data, release_proc));
}

reskia_skottie_property_observer_t *Skottie_PropertyObserver_newWithProperties(
        reskia_skottie_property_observer_node_proc_t on_enter_node,
        reskia_skottie_property_observer_node_proc_t on_leaving_node,
        reskia_skottie_property_observer_color_proc_t on_color_property,
        reskia_skottie_property_observer_opacity_proc_t on_opacity_property,
        reskia_skottie_property_observer_text_proc_t on_text_property,
        reskia_skottie_property_observer_transform_proc_t on_transform_property,
        void *user_data,
        reskia_callback_release_proc_t release_proc) {
    return reinterpret_cast<reskia_skottie_property_observer_t *>(
            new ReskiaSkottiePropertyObserver(
                    on_enter_node,
                    on_leaving_node,
                    on_color_property,
                    on_opacity_property,
                    on_text_property,
                    on_transform_property,
                    user_data,
                    release_proc));
}

void Skottie_PropertyObserver_ref(reskia_skottie_property_observer_t *observer) {
    if (observer != nullptr) {
        to_property_observer(observer)->ref();
    }
}

void Skottie_PropertyObserver_unref(reskia_skottie_property_observer_t *observer) {
    if (observer != nullptr) {
        to_property_observer(observer)->unref();
    }
}

void Skottie_PropertyObserver_release(reskia_skottie_property_observer_t *observer) {
    Skottie_PropertyObserver_unref(observer);
}

void Skottie_PropertyObserver_onEnterNode(
        reskia_skottie_property_observer_t *observer,
        const char node_name[],
        reskia_skottie_property_observer_node_type_t node_type) {
    if (observer != nullptr) {
        to_property_observer(observer)->onEnterNode(node_name, property_node_type_or_other(node_type));
    }
}

void Skottie_PropertyObserver_onLeavingNode(
        reskia_skottie_property_observer_t *observer,
        const char node_name[],
        reskia_skottie_property_observer_node_type_t node_type) {
    if (observer != nullptr) {
        to_property_observer(observer)->onLeavingNode(node_name, property_node_type_or_other(node_type));
    }
}

void Skottie_PropertyObserver_onColorProperty(
        reskia_skottie_property_observer_t *observer,
        const char node_name[],
        reskia_skottie_color_property_lazy_handle_t *lazy_handle) {
    if (observer != nullptr) {
        to_property_observer(observer)->onColorProperty(
                node_name,
                [lazy_handle]() {
                    return std::unique_ptr<skottie::ColorPropertyHandle>(
                            to_color_property_handle(Skottie_ColorPropertyLazyHandle_materialize(lazy_handle)));
                });
    }
}

void Skottie_PropertyObserver_onOpacityProperty(
        reskia_skottie_property_observer_t *observer,
        const char node_name[],
        reskia_skottie_opacity_property_lazy_handle_t *lazy_handle) {
    if (observer != nullptr) {
        to_property_observer(observer)->onOpacityProperty(
                node_name,
                [lazy_handle]() {
                    return std::unique_ptr<skottie::OpacityPropertyHandle>(
                            to_opacity_property_handle(Skottie_OpacityPropertyLazyHandle_materialize(lazy_handle)));
                });
    }
}

void Skottie_PropertyObserver_onTextProperty(
        reskia_skottie_property_observer_t *observer,
        const char node_name[],
        reskia_skottie_text_property_lazy_handle_t *lazy_handle) {
    if (observer != nullptr) {
        to_property_observer(observer)->onTextProperty(
                node_name,
                [lazy_handle]() {
                    return std::unique_ptr<skottie::TextPropertyHandle>(
                            to_text_property_handle(Skottie_TextPropertyLazyHandle_materialize(lazy_handle)));
                });
    }
}

void Skottie_PropertyObserver_onTransformProperty(
        reskia_skottie_property_observer_t *observer,
        const char node_name[],
        reskia_skottie_transform_property_lazy_handle_t *lazy_handle) {
    if (observer != nullptr) {
        to_property_observer(observer)->onTransformProperty(
                node_name,
                [lazy_handle]() {
                    return std::unique_ptr<skottie::TransformPropertyHandle>(
                            to_transform_property_handle(Skottie_TransformPropertyLazyHandle_materialize(lazy_handle)));
                });
    }
}

reskia_skottie_color_property_handle_t *Skottie_ColorPropertyLazyHandle_materialize(
        reskia_skottie_color_property_lazy_handle_t *lazy_handle) {
    return materialize_property_handle<
            skottie::ColorPropertyHandle,
            reskia_skottie_color_property_lazy_handle_t,
            reskia_skottie_color_property_handle_t>(lazy_handle);
}

reskia_skottie_opacity_property_handle_t *Skottie_OpacityPropertyLazyHandle_materialize(
        reskia_skottie_opacity_property_lazy_handle_t *lazy_handle) {
    return materialize_property_handle<
            skottie::OpacityPropertyHandle,
            reskia_skottie_opacity_property_lazy_handle_t,
            reskia_skottie_opacity_property_handle_t>(lazy_handle);
}

reskia_skottie_text_property_handle_t *Skottie_TextPropertyLazyHandle_materialize(
        reskia_skottie_text_property_lazy_handle_t *lazy_handle) {
    return materialize_property_handle<
            skottie::TextPropertyHandle,
            reskia_skottie_text_property_lazy_handle_t,
            reskia_skottie_text_property_handle_t>(lazy_handle);
}

reskia_skottie_transform_property_handle_t *Skottie_TransformPropertyLazyHandle_materialize(
        reskia_skottie_transform_property_lazy_handle_t *lazy_handle) {
    return materialize_property_handle<
            skottie::TransformPropertyHandle,
            reskia_skottie_transform_property_lazy_handle_t,
            reskia_skottie_transform_property_handle_t>(lazy_handle);
}

void Skottie_ColorPropertyHandle_delete(reskia_skottie_color_property_handle_t *handle) {
    delete to_color_property_handle(handle);
}

uint32_t Skottie_ColorPropertyHandle_get(const reskia_skottie_color_property_handle_t *handle) {
    return handle != nullptr ? to_color_property_handle(handle)->get() : 0;
}

void Skottie_ColorPropertyHandle_set(reskia_skottie_color_property_handle_t *handle, uint32_t color) {
    if (handle != nullptr) {
        to_color_property_handle(handle)->set(color);
    }
}

void Skottie_OpacityPropertyHandle_delete(reskia_skottie_opacity_property_handle_t *handle) {
    delete to_opacity_property_handle(handle);
}

float Skottie_OpacityPropertyHandle_get(const reskia_skottie_opacity_property_handle_t *handle) {
    return handle != nullptr ? to_opacity_property_handle(handle)->get() : 0.0f;
}

void Skottie_OpacityPropertyHandle_set(reskia_skottie_opacity_property_handle_t *handle, float opacity) {
    if (handle != nullptr) {
        to_opacity_property_handle(handle)->set(opacity);
    }
}

void Skottie_TextPropertyHandle_delete(reskia_skottie_text_property_handle_t *handle) {
    delete to_text_property_handle(handle);
}

reskia_skottie_text_property_value_t *Skottie_TextPropertyHandle_get(const reskia_skottie_text_property_handle_t *handle) {
    if (handle == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_skottie_text_property_value_t *>(
            new skottie::TextPropertyValue(to_text_property_handle(handle)->get()));
}

void Skottie_TextPropertyHandle_set(reskia_skottie_text_property_handle_t *handle, const reskia_skottie_text_property_value_t *value) {
    if (handle != nullptr && value != nullptr) {
        to_text_property_handle(handle)->set(*to_text_property_value(value));
    }
}

void Skottie_TransformPropertyHandle_delete(reskia_skottie_transform_property_handle_t *handle) {
    delete to_transform_property_handle(handle);
}

bool Skottie_TransformPropertyHandle_get(
        const reskia_skottie_transform_property_handle_t *handle,
        reskia_skottie_transform_property_value_t *out_value) {
    if (handle == nullptr || out_value == nullptr) {
        return false;
    }
    to_c_transform_property_value(to_transform_property_handle(handle)->get(), out_value);
    return true;
}

void Skottie_TransformPropertyHandle_set(
        reskia_skottie_transform_property_handle_t *handle,
        const reskia_skottie_transform_property_value_t *value) {
    if (handle != nullptr && value != nullptr) {
        to_transform_property_handle(handle)->set(transform_property_value_or_default(value));
    }
}

reskia_skottie_number_expression_evaluator_t *Skottie_NumberExpressionEvaluator_new(
        reskia_skottie_number_expression_evaluate_proc_t evaluate,
        void *user_data,
        reskia_callback_release_proc_t release_proc) {
    return reinterpret_cast<reskia_skottie_number_expression_evaluator_t *>(
            new ReskiaSkottieNumberExpressionEvaluator(evaluate, user_data, release_proc));
}

void Skottie_NumberExpressionEvaluator_ref(reskia_skottie_number_expression_evaluator_t *evaluator) {
    if (evaluator != nullptr) {
        to_number_expression_evaluator(evaluator)->ref();
    }
}

void Skottie_NumberExpressionEvaluator_unref(reskia_skottie_number_expression_evaluator_t *evaluator) {
    if (evaluator != nullptr) {
        to_number_expression_evaluator(evaluator)->unref();
    }
}

void Skottie_NumberExpressionEvaluator_release(reskia_skottie_number_expression_evaluator_t *evaluator) {
    Skottie_NumberExpressionEvaluator_unref(evaluator);
}

float Skottie_NumberExpressionEvaluator_evaluate(reskia_skottie_number_expression_evaluator_t *evaluator, float t) {
    return evaluator != nullptr ? to_number_expression_evaluator(evaluator)->evaluate(t) : 0.0f;
}

reskia_skottie_string_expression_evaluator_t *Skottie_StringExpressionEvaluator_new(
        reskia_skottie_string_expression_evaluate_proc_t evaluate,
        void *user_data,
        reskia_callback_release_proc_t release_proc) {
    return reinterpret_cast<reskia_skottie_string_expression_evaluator_t *>(
            new ReskiaSkottieStringExpressionEvaluator(evaluate, user_data, release_proc));
}

void Skottie_StringExpressionEvaluator_ref(reskia_skottie_string_expression_evaluator_t *evaluator) {
    if (evaluator != nullptr) {
        to_string_expression_evaluator(evaluator)->ref();
    }
}

void Skottie_StringExpressionEvaluator_unref(reskia_skottie_string_expression_evaluator_t *evaluator) {
    if (evaluator != nullptr) {
        to_string_expression_evaluator(evaluator)->unref();
    }
}

void Skottie_StringExpressionEvaluator_release(reskia_skottie_string_expression_evaluator_t *evaluator) {
    Skottie_StringExpressionEvaluator_unref(evaluator);
}

reskia_string_t *Skottie_StringExpressionEvaluator_evaluate(reskia_skottie_string_expression_evaluator_t *evaluator, float t) {
    if (evaluator == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_string_t *>(new SkString(to_string_expression_evaluator(evaluator)->evaluate(t)));
}

reskia_skottie_array_expression_evaluator_t *Skottie_ArrayExpressionEvaluator_new(
        reskia_skottie_array_expression_evaluate_proc_t evaluate,
        void *user_data,
        reskia_callback_release_proc_t release_proc) {
    return reinterpret_cast<reskia_skottie_array_expression_evaluator_t *>(
            new ReskiaSkottieArrayExpressionEvaluator(evaluate, user_data, release_proc));
}

void Skottie_ArrayExpressionEvaluator_ref(reskia_skottie_array_expression_evaluator_t *evaluator) {
    if (evaluator != nullptr) {
        to_array_expression_evaluator(evaluator)->ref();
    }
}

void Skottie_ArrayExpressionEvaluator_unref(reskia_skottie_array_expression_evaluator_t *evaluator) {
    if (evaluator != nullptr) {
        to_array_expression_evaluator(evaluator)->unref();
    }
}

void Skottie_ArrayExpressionEvaluator_release(reskia_skottie_array_expression_evaluator_t *evaluator) {
    Skottie_ArrayExpressionEvaluator_unref(evaluator);
}

size_t Skottie_ArrayExpressionEvaluator_evaluate(reskia_skottie_array_expression_evaluator_t *evaluator, float t, float out_values[], size_t capacity) {
    if (evaluator == nullptr) {
        return 0;
    }
    std::vector<float> values = to_array_expression_evaluator(evaluator)->evaluate(t);
    const size_t count = values.size();
    if (out_values != nullptr) {
        const size_t copy_count = count < capacity ? count : capacity;
        for (size_t i = 0; i < copy_count; ++i) {
            out_values[i] = values[i];
        }
    }
    return count;
}

reskia_skottie_expression_manager_t *Skottie_ExpressionManager_new(
        reskia_skottie_expression_manager_create_number_proc_t create_number,
        reskia_skottie_expression_manager_create_string_proc_t create_string,
        reskia_skottie_expression_manager_create_array_proc_t create_array,
        void *user_data,
        reskia_callback_release_proc_t release_proc) {
    return reinterpret_cast<reskia_skottie_expression_manager_t *>(
            new ReskiaSkottieExpressionManager(create_number, create_string, create_array, user_data, release_proc));
}

void Skottie_ExpressionManager_ref(reskia_skottie_expression_manager_t *manager) {
    if (manager != nullptr) {
        to_expression_manager(manager)->ref();
    }
}

void Skottie_ExpressionManager_unref(reskia_skottie_expression_manager_t *manager) {
    if (manager != nullptr) {
        to_expression_manager(manager)->unref();
    }
}

void Skottie_ExpressionManager_release(reskia_skottie_expression_manager_t *manager) {
    Skottie_ExpressionManager_unref(manager);
}

reskia_skottie_number_expression_evaluator_t *Skottie_ExpressionManager_createNumberExpressionEvaluator(reskia_skottie_expression_manager_t *manager, const char expression[]) {
    if (manager == nullptr) {
        return nullptr;
    }
    sk_sp<skottie::ExpressionEvaluator<float>> evaluator =
            to_expression_manager(manager)->createNumberExpressionEvaluator(expression);
    return reinterpret_cast<reskia_skottie_number_expression_evaluator_t *>(evaluator.release());
}

reskia_skottie_string_expression_evaluator_t *Skottie_ExpressionManager_createStringExpressionEvaluator(reskia_skottie_expression_manager_t *manager, const char expression[]) {
    if (manager == nullptr) {
        return nullptr;
    }
    sk_sp<skottie::ExpressionEvaluator<SkString>> evaluator =
            to_expression_manager(manager)->createStringExpressionEvaluator(expression);
    return reinterpret_cast<reskia_skottie_string_expression_evaluator_t *>(evaluator.release());
}

reskia_skottie_array_expression_evaluator_t *Skottie_ExpressionManager_createArrayExpressionEvaluator(reskia_skottie_expression_manager_t *manager, const char expression[]) {
    if (manager == nullptr) {
        return nullptr;
    }
    sk_sp<skottie::ExpressionEvaluator<std::vector<float>>> evaluator =
            to_expression_manager(manager)->createArrayExpressionEvaluator(expression);
    return reinterpret_cast<reskia_skottie_array_expression_evaluator_t *>(evaluator.release());
}

reskia_skottie_glyph_decorator_t *Skottie_GlyphDecorator_new(
        reskia_skottie_glyph_decorator_on_decorate_proc_t on_decorate,
        void *user_data,
        reskia_callback_release_proc_t release_proc) {
    return reinterpret_cast<reskia_skottie_glyph_decorator_t *>(
            new ReskiaSkottieGlyphDecorator(on_decorate, user_data, release_proc));
}

void Skottie_GlyphDecorator_ref(reskia_skottie_glyph_decorator_t *decorator) {
    if (decorator != nullptr) {
        to_glyph_decorator(decorator)->ref();
    }
}

void Skottie_GlyphDecorator_unref(reskia_skottie_glyph_decorator_t *decorator) {
    if (decorator != nullptr) {
        to_glyph_decorator(decorator)->unref();
    }
}

void Skottie_GlyphDecorator_release(reskia_skottie_glyph_decorator_t *decorator) {
    Skottie_GlyphDecorator_unref(decorator);
}

void Skottie_GlyphDecorator_onDecorate(
        reskia_skottie_glyph_decorator_t *decorator,
        reskia_canvas_t *canvas,
        const reskia_skottie_glyph_info_t glyphs[],
        size_t glyph_count,
        float scale) {
    if (decorator == nullptr) {
        return;
    }
    if (glyph_count > 0 && glyphs == nullptr) {
        return;
    }
    std::vector<skottie::GlyphDecorator::GlyphInfo> native_glyphs(glyph_count);
    for (size_t i = 0; i < glyph_count; ++i) {
        native_glyphs[i].fBounds = SkRect::MakeLTRB(
                glyphs[i].bounds_left,
                glyphs[i].bounds_top,
                glyphs[i].bounds_right,
                glyphs[i].bounds_bottom);
        native_glyphs[i].fMatrix.set9(glyphs[i].matrix);
        native_glyphs[i].fCluster = glyphs[i].cluster;
        native_glyphs[i].fAdvance = glyphs[i].advance;
    }
    const skottie::GlyphDecorator::TextInfo text_info = {
            SkSpan<const skottie::GlyphDecorator::GlyphInfo>(native_glyphs.data(), native_glyphs.size()),
            scale};
    to_glyph_decorator(decorator)->onDecorate(reinterpret_cast<SkCanvas *>(canvas), text_info);
}

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

bool Skottie_AnimationBuilder_setLogger(reskia_skottie_animation_builder_t *builder, reskia_skottie_logger_t *logger) {
    if (builder == nullptr || logger == nullptr) {
        return false;
    }
    to_builder(builder)->setLogger(sk_ref_sp(to_logger(logger)));
    return true;
}

bool Skottie_AnimationBuilder_setMarkerObserver(reskia_skottie_animation_builder_t *builder, reskia_skottie_marker_observer_t *observer) {
    if (builder == nullptr || observer == nullptr) {
        return false;
    }
    to_builder(builder)->setMarkerObserver(sk_ref_sp(to_marker_observer(observer)));
    return true;
}

bool Skottie_AnimationBuilder_setPrecompInterceptor(reskia_skottie_animation_builder_t *builder, reskia_skottie_precomp_interceptor_t *interceptor) {
    if (builder == nullptr || interceptor == nullptr) {
        return false;
    }
    to_builder(builder)->setPrecompInterceptor(sk_ref_sp(to_precomp_interceptor(interceptor)));
    return true;
}

bool Skottie_AnimationBuilder_setPropertyObserver(reskia_skottie_animation_builder_t *builder, reskia_skottie_property_observer_t *observer) {
    if (builder == nullptr || observer == nullptr) {
        return false;
    }
    to_builder(builder)->setPropertyObserver(sk_ref_sp(to_property_observer(observer)));
    return true;
}

bool Skottie_AnimationBuilder_setExpressionManager(reskia_skottie_animation_builder_t *builder, reskia_skottie_expression_manager_t *manager) {
    if (builder == nullptr || manager == nullptr) {
        return false;
    }
    to_builder(builder)->setExpressionManager(sk_ref_sp(to_expression_manager(manager)));
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

void TextPropertyValue_setDecorator(reskia_skottie_text_property_value_t *value, reskia_skottie_glyph_decorator_t *decorator) {
    if (value != nullptr) {
        to_text_property_value(value)->fDecorator = decorator != nullptr ? sk_ref_sp(to_glyph_decorator(decorator)) : nullptr;
    }
}

reskia_skottie_shaper_result_t *Skottie_Shaper_Shape(
        const char text[],
        const reskia_skottie_text_property_value_t *desc,
        const reskia_rect_t *box,
        bool use_box,
        float x,
        float y,
        sk_font_mgr_t font_mgr) {
    if (text == nullptr || (use_box && box == nullptr)) {
        return nullptr;
    }
    const sk_sp<SkTypeface> typeface = desc != nullptr ? to_text_property_value(desc)->fTypeface : nullptr;
    const skottie::Shaper::TextDesc text_desc = make_shaper_text_desc(desc, typeface);
    skottie::Shaper::Result result = use_box
            ? skottie::Shaper::Shape(
                    SkString(text),
                    text_desc,
                    *reinterpret_cast<const SkRect *>(box),
                    font_mgr_or_default(font_mgr))
            : skottie::Shaper::Shape(
                    SkString(text),
                    text_desc,
                    SkPoint::Make(x, y),
                    font_mgr_or_default(font_mgr));
    return reinterpret_cast<reskia_skottie_shaper_result_t *>(new skottie::Shaper::Result(std::move(result)));
}

reskia_skottie_shaper_result_t *Skottie_Shaper_ShapeAtPoint(
        const char text[],
        const reskia_skottie_text_property_value_t *desc,
        float x,
        float y,
        sk_font_mgr_t font_mgr) {
    return Skottie_Shaper_Shape(text, desc, nullptr, false, x, y, font_mgr);
}

reskia_skottie_shaper_result_t *Skottie_Shaper_ShapeInBox(
        const char text[],
        const reskia_skottie_text_property_value_t *desc,
        const reskia_rect_t *box,
        sk_font_mgr_t font_mgr) {
    return Skottie_Shaper_Shape(text, desc, box, true, 0.0f, 0.0f, font_mgr);
}

void Skottie_Shaper_Result_delete(reskia_skottie_shaper_result_t *result) {
    delete to_shaper_result(result);
}

size_t Skottie_Shaper_Result_fragmentCount(const reskia_skottie_shaper_result_t *result) {
    return result != nullptr ? to_shaper_result(result)->fFragments.size() : 0;
}

size_t Skottie_Shaper_Result_missingGlyphCount(const reskia_skottie_shaper_result_t *result) {
    return result != nullptr ? to_shaper_result(result)->fMissingGlyphCount : 0;
}

float Skottie_Shaper_Result_scale(const reskia_skottie_shaper_result_t *result) {
    return result != nullptr ? to_shaper_result(result)->fScale : 0.0f;
}

bool Skottie_Shaper_Result_computeVisualBounds(
        const reskia_skottie_shaper_result_t *result,
        reskia_rect_t *out_bounds) {
    if (result == nullptr || out_bounds == nullptr) {
        return false;
    }
    *reinterpret_cast<SkRect *>(out_bounds) = to_shaper_result(result)->computeVisualBounds();
    return true;
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
