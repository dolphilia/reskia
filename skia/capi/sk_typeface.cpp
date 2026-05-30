//
// Created by dolphilia on 2024/01/11.
//

#include "sk_typeface.h"

#include "include/core/SkTypeface.h"
#include "include/core/SkFontMgr.h"
#include "include/core/SkStream.h"

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_stream_asset.h"
#include "../handles/static_sk_typeface.h"
#include "../handles/static_sk_font_style.h"
#include "../handles/static_sk_rect.h"
#include "../handles/static_sk_font_mgr.h"

#include "../handles/static_sk_font_mgr-internal.h"
#include "../handles/static_sk_rect-internal.h"
#include "../handles/static_sk_stream_asset-internal.h"
#include "../handles/static_sk_typeface-internal.h"
#include "../handles/static_sk_font_style-internal.h"
#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_font_mgr.h"

#include <memory>
#include <mutex>
#include <utility>

namespace {

SkTypeface *as_typeface(reskia_typeface_t *typeface) {
    return reinterpret_cast<SkTypeface *>(typeface);
}

const SkTypeface *as_typeface(const reskia_typeface_t *typeface) {
    return reinterpret_cast<const SkTypeface *>(typeface);
}

bool is_valid_serialize_behavior(reskia_typeface_serialize_behavior_t behavior) {
    return behavior >= 0 && behavior <= static_cast<reskia_typeface_serialize_behavior_t>(SkTypeface::SerializeBehavior::kIncludeDataIfLocal);
}

bool has_text_input(const void *text, size_t byteLength) {
    return byteLength == 0 || text != nullptr;
}

bool has_glyph_output(const uint16_t *glyphs, int count, const int32_t *adjustments) {
    return count == 0 || (count > 0 && glyphs != nullptr && adjustments != nullptr);
}

sk_data_t make_data_handle(sk_sp<SkData> data) {
    if (!data) {
        return 0;
    }
    return static_sk_data_make(std::move(data));
}

sk_font_style_t make_font_style_handle(SkFontStyle font_style) {
    return static_sk_font_style_make(font_style);
}

sk_rect_t make_rect_handle(const SkRect &rect) {
    return static_sk_rect_make(rect);
}

sk_stream_asset_t make_stream_asset_handle(std::unique_ptr<SkStreamAsset> stream) {
    if (!stream) {
        return 0;
    }
    return static_sk_stream_asset_make(std::move(stream));
}

sk_typeface_t make_typeface_handle(sk_sp<SkTypeface> typeface) {
    if (!typeface) {
        return 0;
    }
    return static_sk_typeface_make(std::move(typeface));
}

struct TypefaceRegistrationContext {
    reskia_typeface_factory_make_proc_t make = nullptr;
    void *user_data = nullptr;
    reskia_callback_release_proc_t release_proc = nullptr;

    ~TypefaceRegistrationContext() {
        if (release_proc != nullptr) {
            release_proc(user_data);
        }
    }
};

std::mutex g_typeface_registration_mutex;
std::shared_ptr<const TypefaceRegistrationContext> g_typeface_registration_context;
SkTypeface::FactoryId g_typeface_registration_id = 0;

sk_sp<SkTypeface> reskia_typeface_make_from_stream(
        std::unique_ptr<SkStreamAsset> stream,
        const SkFontArguments &arguments) {
    std::shared_ptr<const TypefaceRegistrationContext> context;
    {
        std::lock_guard<std::mutex> lock(g_typeface_registration_mutex);
        context = g_typeface_registration_context;
    }
    if (!context || context->make == nullptr || !stream) {
        return nullptr;
    }

    sk_stream_asset_t stream_handle = static_sk_stream_asset_make(std::move(stream));
    sk_typeface_t typeface_handle = context->make(
            stream_handle,
            reinterpret_cast<const reskia_font_arguments_t *>(&arguments),
            context->user_data);
    static_sk_stream_asset_delete(stream_handle);
    return static_sk_typeface_take_entity(typeface_handle);
}

}  // namespace

extern "C" {

void SkTypeface_delete(reskia_typeface_t *typeface) {
    if (typeface == nullptr) {
        return;
    }
    as_typeface(typeface)->unref();
}

sk_font_style_t SkTypeface_fontStyle(reskia_typeface_t *typeface) {
    if (typeface == nullptr) {
        return 0;
    }
    return make_font_style_handle(as_typeface(typeface)->fontStyle());
}

bool SkTypeface_isBold(reskia_typeface_t *typeface) {
    return typeface != nullptr && as_typeface(typeface)->isBold();
}

bool SkTypeface_isItalic(reskia_typeface_t *typeface) {
    return typeface != nullptr && as_typeface(typeface)->isItalic();
}

bool SkTypeface_isFixedPitch(reskia_typeface_t *typeface) {
    return typeface != nullptr && as_typeface(typeface)->isFixedPitch();
}

int SkTypeface_getVariationDesignPosition(reskia_typeface_t *typeface, reskia_font_arguments_variation_position_coordinate_t *coordinates, int coordinateCount) {
    if (typeface == nullptr || coordinateCount < 0) {
        return -1;
    }
    return as_typeface(typeface)->getVariationDesignPosition(reinterpret_cast<SkFontArguments::VariationPosition::Coordinate *>(coordinates), coordinateCount);
}

int SkTypeface_getVariationDesignParameters(reskia_typeface_t *typeface, reskia_font_parameters_variation_axis_t *parameters, int parameterCount) {
    if (typeface == nullptr || parameterCount < 0) {
        return -1;
    }
    return as_typeface(typeface)->getVariationDesignParameters(reinterpret_cast<SkFontParameters::Variation::Axis *>(parameters), parameterCount);
}

uint32_t SkTypeface_uniqueID(reskia_typeface_t *typeface) {
    if (typeface == nullptr) {
        return 0;
    }
    return as_typeface(typeface)->uniqueID();
}

sk_typeface_t SkTypeface_makeClone(reskia_typeface_t *typeface, const reskia_font_arguments_t *arguments) {
    if (typeface == nullptr || arguments == nullptr) {
        return 0;
    }
    return make_typeface_handle(as_typeface(typeface)->makeClone(* reinterpret_cast<const SkFontArguments *>(arguments)));
}

void SkTypeface_serialize(reskia_typeface_t *typeface, reskia_w_stream_t *stream, reskia_typeface_serialize_behavior_t behavior) {
    if (typeface == nullptr || stream == nullptr || !is_valid_serialize_behavior(behavior)) {
        return;
    }
    as_typeface(typeface)->serialize(reinterpret_cast<SkWStream *>(stream), static_cast<SkTypeface::SerializeBehavior>(behavior));
}

sk_data_t SkTypeface_serializeToData(reskia_typeface_t *typeface, reskia_typeface_serialize_behavior_t behavior) {
    if (typeface == nullptr || !is_valid_serialize_behavior(behavior)) {
        return 0;
    }
    return make_data_handle(as_typeface(typeface)->serialize(static_cast<SkTypeface::SerializeBehavior>(behavior)));
}

void SkTypeface_unicharsToGlyphs(reskia_typeface_t *typeface, const int32_t *uni, int count, uint16_t *glyphs) {
    if (typeface == nullptr || count <= 0 || uni == nullptr || glyphs == nullptr) {
        return;
    }
    as_typeface(typeface)->unicharsToGlyphs(reinterpret_cast<const SkUnichar *>(uni), count, reinterpret_cast<SkGlyphID *>(glyphs));
}

int SkTypeface_textToGlyphs(reskia_typeface_t *typeface, const void *text, size_t byteLength, reskia_typeface_text_encoding_t encoding, uint16_t *glyphs, int maxGlyphCount) {
    if (typeface == nullptr || !has_text_input(text, byteLength) || maxGlyphCount < 0) {
        return 0;
    }
    return as_typeface(typeface)->textToGlyphs(text, byteLength, static_cast<SkTextEncoding>(encoding), reinterpret_cast<SkGlyphID *>(glyphs), maxGlyphCount);
}

uint16_t SkTypeface_unicharToGlyph(reskia_typeface_t *typeface, reskia_typeface_unichar_t unichar) {
    if (typeface == nullptr) {
        return 0;
    }
    return as_typeface(typeface)->unicharToGlyph(static_cast<SkUnichar>(unichar));
}

int SkTypeface_countGlyphs(reskia_typeface_t *typeface) {
    if (typeface == nullptr) {
        return 0;
    }
    return as_typeface(typeface)->countGlyphs();
}

int SkTypeface_countTables(reskia_typeface_t *typeface) {
    if (typeface == nullptr) {
        return 0;
    }
    return as_typeface(typeface)->countTables();
}

int SkTypeface_getTableTags(reskia_typeface_t *typeface, uint32_t *tags) {
    if (typeface == nullptr) {
        return 0;
    }
    return as_typeface(typeface)->getTableTags(reinterpret_cast<SkFontTableTag *>(tags));
}

size_t SkTypeface_getTableSize(reskia_typeface_t *typeface, uint32_t tag) {
    if (typeface == nullptr) {
        return 0;
    }
    return as_typeface(typeface)->getTableSize(static_cast<SkFontTableTag>(tag));
}

size_t SkTypeface_getTableData(reskia_typeface_t *typeface, uint32_t tag, size_t offset, size_t length, void *data) {
    if (typeface == nullptr || (length > 0 && data == nullptr)) {
        return 0;
    }
    return as_typeface(typeface)->getTableData(static_cast<SkFontTableTag>(tag), offset, length, data);
}

sk_data_t SkTypeface_copyTableData(reskia_typeface_t *typeface, uint32_t tag) {
    if (typeface == nullptr) {
        return 0;
    }
    return make_data_handle(as_typeface(typeface)->copyTableData(static_cast<SkFontTableTag>(tag)));
}

int SkTypeface_getUnitsPerEm(reskia_typeface_t *typeface) {
    if (typeface == nullptr) {
        return 0;
    }
    return as_typeface(typeface)->getUnitsPerEm();
}

bool SkTypeface_getKerningPairAdjustments(reskia_typeface_t *typeface, const uint16_t *glyphs, int count, int32_t *adjustments) {
    if (typeface == nullptr || count < 0 || !has_glyph_output(glyphs, count, adjustments)) {
        return false;
    }
    return as_typeface(typeface)->getKerningPairAdjustments(reinterpret_cast<const SkGlyphID *>(glyphs), count, adjustments);
}

reskia_typeface_localized_strings_t *SkTypeface_createFamilyNameIterator(reskia_typeface_t *typeface) {
    if (typeface == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_typeface_localized_strings_t *>(as_typeface(typeface)->createFamilyNameIterator());
}

void SkTypeface_getFamilyName(reskia_typeface_t *typeface, reskia_string_t *name) {
    if (typeface == nullptr || name == nullptr) {
        return;
    }
    as_typeface(typeface)->getFamilyName(reinterpret_cast<SkString *>(name));
}

bool SkTypeface_getPostScriptName(reskia_typeface_t *typeface, reskia_string_t *name) {
    if (typeface == nullptr || name == nullptr) {
        return false;
    }
    return as_typeface(typeface)->getPostScriptName(reinterpret_cast<SkString *>(name));
}

int SkTypeface_getResourceName(reskia_typeface_t *typeface, reskia_string_t *resourceName) {
    if (typeface == nullptr || resourceName == nullptr) {
        return -1;
    }
    return as_typeface(typeface)->getResourceName(reinterpret_cast<SkString *>(resourceName));
}

sk_stream_asset_t SkTypeface_openStream(reskia_typeface_t *typeface, int *ttcIndex) {
    if (typeface == nullptr) {
        return 0;
    }
    return make_stream_asset_handle(as_typeface(typeface)->openStream(ttcIndex));
}

sk_stream_asset_t SkTypeface_openExistingStream(reskia_typeface_t *typeface, int *ttcIndex) {
    if (typeface == nullptr) {
        return 0;
    }
    return make_stream_asset_handle(as_typeface(typeface)->openExistingStream(ttcIndex));
}

//@TODO
//std::unique_ptr<SkScalerContext> SkTypeface_createScalerContext(SkTypeface *typeface, const SkScalerContextEffects &effects, const SkDescriptor *descriptor) {
//    return typeface->createScalerContext(effects, descriptor);
//}

sk_rect_t SkTypeface_getBounds(reskia_typeface_t *typeface) {
    if (typeface == nullptr) {
        return 0;
    }
    return make_rect_handle(as_typeface(typeface)->getBounds());
}

void SkTypeface_filterRec(reskia_typeface_t *typeface, reskia_scaler_context_rec_t *rec) {
    if (typeface == nullptr || rec == nullptr) {
        return;
    }
    as_typeface(typeface)->filterRec(reinterpret_cast<SkScalerContextRec *>(rec));
}

void SkTypeface_getFontDescriptor(reskia_typeface_t *typeface, reskia_font_descriptor_t *desc, bool *isLocal) {
    if (typeface == nullptr || desc == nullptr || isLocal == nullptr) {
        return;
    }
    as_typeface(typeface)->getFontDescriptor(reinterpret_cast<SkFontDescriptor *>(desc), isLocal);
}

void *SkTypeface_internal_private_getCTFontRef(reskia_typeface_t *typeface) {
    if (typeface == nullptr) {
        return nullptr;
    }
    return as_typeface(typeface)->internal_private_getCTFontRef();
}

// static

bool SkTypeface_Equal(const reskia_typeface_t *facea, const reskia_typeface_t *faceb) {
    return SkTypeface::Equal(as_typeface(facea), as_typeface(faceb));
}

sk_typeface_t SkTypeface_MakeEmpty() {
    return make_typeface_handle(SkTypeface::MakeEmpty());
}

sk_typeface_t SkTypeface_MakeDeserialize(reskia_stream_t *stream, sk_font_mgr_t font_mgr) {
    if (stream == nullptr) {
        return 0;
    }
    return make_typeface_handle(SkTypeface::MakeDeserialize(reinterpret_cast<SkStream *>(stream), static_sk_font_mgr_get_entity(font_mgr)));
}

bool SkTypeface_Register(
        reskia_typeface_factory_id_t id,
        reskia_typeface_factory_make_proc_t make,
        void *user_data,
        reskia_callback_release_proc_t release_proc) {
    if (id == 0 || make == nullptr) {
        return false;
    }

    auto next_context = std::make_shared<TypefaceRegistrationContext>();
    next_context->make = make;
    next_context->user_data = user_data;
    next_context->release_proc = release_proc;

    std::shared_ptr<const TypefaceRegistrationContext> previous_context;
    bool should_register = false;
    {
        std::lock_guard<std::mutex> lock(g_typeface_registration_mutex);
        if (g_typeface_registration_id != 0 && g_typeface_registration_id != id) {
            return false;
        }
        should_register = g_typeface_registration_id == 0;
        g_typeface_registration_id = id;
        previous_context = std::move(g_typeface_registration_context);
        g_typeface_registration_context = std::move(next_context);
    }

    if (should_register) {
        SkTypeface::Register(id, reskia_typeface_make_from_stream);
    }
    return true;
}

}
