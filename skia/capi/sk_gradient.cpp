//
// Created by Codex on 2026/06/01.
//

#include "sk_gradient.h"

#include "include/effects/SkGradient.h"

#include "../handles/static_sk_color_space-internal.h"
#include "../handles/static_sk_color_space.h"

#include <utility>
#include <vector>

struct reskia_gradient_colors_t {
    std::vector<SkColor4f> colors;
    std::vector<float> positions;
    sk_sp<SkColorSpace> color_space;
    SkTileMode tile_mode = SkTileMode::kClamp;
    SkGradient::Colors native;

    reskia_gradient_colors_t() { this->rebuild(); }

    void rebuild() {
        native = SkGradient::Colors(
            SkSpan<const SkColor4f>(colors.data(), colors.size()),
            SkSpan<const float>(positions.data(), positions.size()),
            tile_mode,
            color_space);
    }
};

struct reskia_gradient_interpolation_t {
    SkGradient::Interpolation native;
};

struct reskia_gradient_t {
    reskia_gradient_colors_t colors;
    reskia_gradient_interpolation_t interpolation;
    SkGradient native;

    reskia_gradient_t() { this->rebuild(); }

    reskia_gradient_t(const reskia_gradient_colors_t& c, const reskia_gradient_interpolation_t& i)
            : colors(c), interpolation(i) {
        colors.rebuild();
        this->rebuild();
    }

    void rebuild() {
        native = SkGradient(colors.native, interpolation.native);
    }
};

namespace {

bool valid_tile_mode(reskia_gradient_tile_mode_t mode) {
    return mode >= 0 && mode <= static_cast<reskia_gradient_tile_mode_t>(SkTileMode::kLastTileMode);
}

bool valid_in_premul(reskia_gradient_in_premul_t value) {
    return value == static_cast<reskia_gradient_in_premul_t>(SkGradient::Interpolation::InPremul::kNo) ||
           value == static_cast<reskia_gradient_in_premul_t>(SkGradient::Interpolation::InPremul::kYes);
}

bool valid_color_space(reskia_gradient_color_space_t value) {
    return value >= 0 &&
           value < SkGradient::Interpolation::kColorSpaceCount;
}

bool valid_hue_method(reskia_gradient_hue_method_t value) {
    return value >= 0 &&
           value < SkGradient::Interpolation::kHueMethodCount;
}

sk_color_space_t make_color_space_handle(sk_sp<SkColorSpace> color_space) {
    return color_space ? static_sk_color_space_make(std::move(color_space)) : 0;
}

}  // namespace

extern "C" {

reskia_gradient_colors_t *SkGradient_Colors_new(void) {
    return new reskia_gradient_colors_t();
}

reskia_gradient_colors_t *SkGradient_Colors_newWithColorsPositionsModeColorSpace(const reskia_color_4f_t *colors, size_t color_count, const float *positions, size_t position_count, reskia_gradient_tile_mode_t mode, sk_color_space_t color_space) {
    if ((color_count > 0 && colors == nullptr) || (position_count > 0 && positions == nullptr) ||
        (position_count != 0 && position_count != color_count) || !valid_tile_mode(mode)) {
        return nullptr;
    }
    auto *result = new reskia_gradient_colors_t();
    if (color_count > 0) {
        const auto *native_colors = reinterpret_cast<const SkColor4f *>(colors);
        result->colors.assign(native_colors, native_colors + color_count);
    }
    if (position_count > 0) {
        result->positions.assign(positions, positions + position_count);
    }
    result->color_space = static_sk_color_space_get_entity(color_space);
    result->tile_mode = static_cast<SkTileMode>(mode);
    result->rebuild();
    return result;
}

void SkGradient_Colors_delete(reskia_gradient_colors_t *colors) {
    delete colors;
}

size_t SkGradient_Colors_colorCount(const reskia_gradient_colors_t *colors) {
    return colors == nullptr ? 0 : colors->colors.size();
}

const reskia_color_4f_t *SkGradient_Colors_colors(const reskia_gradient_colors_t *colors) {
    return colors == nullptr || colors->colors.empty()
        ? nullptr
        : reinterpret_cast<const reskia_color_4f_t *>(colors->colors.data());
}

size_t SkGradient_Colors_positionCount(const reskia_gradient_colors_t *colors) {
    return colors == nullptr ? 0 : colors->positions.size();
}

const float *SkGradient_Colors_positions(const reskia_gradient_colors_t *colors) {
    return colors == nullptr || colors->positions.empty() ? nullptr : colors->positions.data();
}

sk_color_space_t SkGradient_Colors_colorSpace(const reskia_gradient_colors_t *colors) {
    return colors == nullptr ? 0 : make_color_space_handle(colors->color_space);
}

reskia_gradient_tile_mode_t SkGradient_Colors_tileMode(const reskia_gradient_colors_t *colors) {
    return colors == nullptr ? 0 : static_cast<reskia_gradient_tile_mode_t>(colors->tile_mode);
}

reskia_gradient_interpolation_t *SkGradient_Interpolation_new(void) {
    return new reskia_gradient_interpolation_t();
}

reskia_gradient_interpolation_t *SkGradient_Interpolation_newWithValues(reskia_gradient_in_premul_t in_premul, reskia_gradient_color_space_t color_space, reskia_gradient_hue_method_t hue_method) {
    if (!valid_in_premul(in_premul) || !valid_color_space(color_space) || !valid_hue_method(hue_method)) {
        return nullptr;
    }
    auto *result = new reskia_gradient_interpolation_t();
    result->native.fInPremul = static_cast<SkGradient::Interpolation::InPremul>(in_premul);
    result->native.fColorSpace = static_cast<SkGradient::Interpolation::ColorSpace>(color_space);
    result->native.fHueMethod = static_cast<SkGradient::Interpolation::HueMethod>(hue_method);
    return result;
}

reskia_gradient_interpolation_t *SkGradient_Interpolation_FromFlags(uint32_t flags) {
    auto *result = new reskia_gradient_interpolation_t();
    result->native = SkGradient::Interpolation::FromFlags(flags);
    return result;
}

void SkGradient_Interpolation_delete(reskia_gradient_interpolation_t *interpolation) {
    delete interpolation;
}

reskia_gradient_in_premul_t SkGradient_Interpolation_inPremul(const reskia_gradient_interpolation_t *interpolation) {
    return interpolation == nullptr ? 0 : static_cast<reskia_gradient_in_premul_t>(interpolation->native.fInPremul);
}

reskia_gradient_color_space_t SkGradient_Interpolation_colorSpace(const reskia_gradient_interpolation_t *interpolation) {
    return interpolation == nullptr ? 0 : static_cast<reskia_gradient_color_space_t>(interpolation->native.fColorSpace);
}

reskia_gradient_hue_method_t SkGradient_Interpolation_hueMethod(const reskia_gradient_interpolation_t *interpolation) {
    return interpolation == nullptr ? 0 : static_cast<reskia_gradient_hue_method_t>(interpolation->native.fHueMethod);
}

reskia_gradient_t *SkGradient_new(void) {
    return new reskia_gradient_t();
}

reskia_gradient_t *SkGradient_newWithColorsAndInterpolation(const reskia_gradient_colors_t *colors, const reskia_gradient_interpolation_t *interpolation) {
    if (colors == nullptr || interpolation == nullptr) {
        return nullptr;
    }
    return new reskia_gradient_t(*colors, *interpolation);
}

void SkGradient_delete(reskia_gradient_t *gradient) {
    delete gradient;
}

const reskia_gradient_colors_t *SkGradient_colors(const reskia_gradient_t *gradient) {
    return gradient == nullptr ? nullptr : &gradient->colors;
}

const reskia_gradient_interpolation_t *SkGradient_interpolation(const reskia_gradient_t *gradient) {
    return gradient == nullptr ? nullptr : &gradient->interpolation;
}

}  // extern "C"
