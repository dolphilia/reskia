//
// Created by dolphilia on 2024/01/08.
//

#include "sk_color_filters.h"

#include "include/core/SkColorFilter.h"

#include "../static/static_sk_color_filter.h"
#include "../static/static_sk_color_space.h"
#include "../static/static_sk_color_table.h"

#include "../static/static_sk_color_table-internal.h"
#include "../static/static_sk_color_space-internal.h"
#include "../static/static_sk_color_filter-internal.h"

extern "C" {

void SkColorFilters_delete(void *colorFilters) {
    delete static_cast<SkColorFilters *>(colorFilters);
}

// static

sk_color_filter_t SkColorFilters_Blend(const void *c, sk_color_space_t color_space, int mode) {
    return static_sk_color_filter_make(SkColorFilters::Blend(* static_cast<const SkColor4f *>(c), static_sk_color_space_get_entity(color_space), static_cast<SkBlendMode>(mode)));
}

sk_color_filter_t SkColorFilters_Blend_2(unsigned int c, int mode) {
    return static_sk_color_filter_make(SkColorFilters::Blend(c, static_cast<SkBlendMode>(mode)));
}

sk_color_filter_t SkColorFilters_Compose(sk_color_filter_t color_filter1, sk_color_filter_t color_filter2) {
    return static_sk_color_filter_make(SkColorFilters::Compose(static_sk_color_filter_get_entity(color_filter1), static_sk_color_filter_get_entity(color_filter2)));
}

sk_color_filter_t SkColorFilters_HSLAMatrix(const float rowMajor[20]) {
    return static_sk_color_filter_make(SkColorFilters::HSLAMatrix(rowMajor));
}

sk_color_filter_t SkColorFilters_HSLAMatrix_2(const void *matrix) {
    return static_sk_color_filter_make(SkColorFilters::HSLAMatrix(* static_cast<const SkColorMatrix *>(matrix)));
}

sk_color_filter_t SkColorFilters_Lerp(float t, sk_color_filter_t color_filter1, sk_color_filter_t color_filter2) {
    return static_sk_color_filter_make(SkColorFilters::Lerp(t, static_sk_color_filter_get_entity(color_filter1), static_sk_color_filter_get_entity(color_filter2)));
}

sk_color_filter_t SkColorFilters_Lighting(unsigned int mul, unsigned int add) {
    return static_sk_color_filter_make(SkColorFilters::Lighting(mul, add));
}

sk_color_filter_t SkColorFilters_LinearToSRGBGamma() {
    return static_sk_color_filter_make(SkColorFilters::LinearToSRGBGamma());
}

sk_color_filter_t SkColorFilters_Matrix(const float rowMajor[20]) {
    return static_sk_color_filter_make(SkColorFilters::Matrix(rowMajor));
}

sk_color_filter_t SkColorFilters_Matrix_2(const void *matrix) {
    return static_sk_color_filter_make(SkColorFilters::Matrix(* static_cast<const SkColorMatrix *>(matrix)));
}

sk_color_filter_t SkColorFilters_SRGBToLinearGamma() {
    return static_sk_color_filter_make(SkColorFilters::SRGBToLinearGamma());
}

sk_color_filter_t SkColorFilters_Table(const uint8_t table[256]) {
    return static_sk_color_filter_make(SkColorFilters::Table(table));
}

sk_color_filter_t SkColorFilters_Table_2(sk_color_table_t color_table) {
    return static_sk_color_filter_make(SkColorFilters::Table(static_sk_color_table_get_entity(color_table)));
}

sk_color_filter_t SkColorFilters_TableARGB(const uint8_t tableA[256], const uint8_t tableR[256], const uint8_t tableG[256], const uint8_t tableB[256]) {
    return static_sk_color_filter_make(SkColorFilters::TableARGB(tableA, tableR, tableG, tableB));
}

}
