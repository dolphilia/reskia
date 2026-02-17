cmake_minimum_required(VERSION 3.26.4)
project(svg LANGUAGES CXX)

set(SVG_COMMON_INCLUDE_DIRS
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/../skia"
)

add_library(svg
        modules/svg/src/SkSVGAttribute.cpp
        modules/svg/src/SkSVGAttributeParser.cpp
        modules/svg/src/SkSVGCircle.cpp
        modules/svg/src/SkSVGClipPath.cpp
        modules/svg/src/SkSVGContainer.cpp
        modules/svg/src/SkSVGDOM.cpp
        modules/svg/src/SkSVGEllipse.cpp
        modules/svg/src/SkSVGFe.cpp
        modules/svg/src/SkSVGFeBlend.cpp
        modules/svg/src/SkSVGFeColorMatrix.cpp
        modules/svg/src/SkSVGFeComposite.cpp
        modules/svg/src/SkSVGFeDisplacementMap.cpp
        modules/svg/src/SkSVGFeFlood.cpp
        modules/svg/src/SkSVGFeGaussianBlur.cpp
        modules/svg/src/SkSVGFeImage.cpp
        modules/svg/src/SkSVGFeLightSource.cpp
        modules/svg/src/SkSVGFeLighting.cpp
        modules/svg/src/SkSVGFeMorphology.cpp
        modules/svg/src/SkSVGFeOffset.cpp
        modules/svg/src/SkSVGFeTurbulence.cpp
        modules/svg/src/SkSVGFilter.cpp
        modules/svg/src/SkSVGFilterContext.cpp
        modules/svg/src/SkSVGGradient.cpp
        modules/svg/src/SkSVGImage.cpp
        modules/svg/src/SkSVGLine.cpp
        modules/svg/src/SkSVGLinearGradient.cpp
        modules/svg/src/SkSVGMask.cpp
        modules/svg/src/SkSVGNode.cpp
        modules/svg/src/SkSVGOpenTypeSVGDecoder.cpp
        modules/svg/src/SkSVGPath.cpp
        modules/svg/src/SkSVGPattern.cpp
        modules/svg/src/SkSVGPoly.cpp
        modules/svg/src/SkSVGRadialGradient.cpp
        modules/svg/src/SkSVGRect.cpp
        modules/svg/src/SkSVGRenderContext.cpp
        modules/svg/src/SkSVGSVG.cpp
        modules/svg/src/SkSVGShape.cpp
        modules/svg/src/SkSVGStop.cpp
        modules/svg/src/SkSVGText.cpp
        modules/svg/src/SkSVGTextPriv.h
        modules/svg/src/SkSVGTransformableNode.cpp
        modules/svg/src/SkSVGUse.cpp
        modules/svg/src/SkSVGValue.cpp
)
target_compile_features(svg PUBLIC cxx_std_17)
target_include_directories(svg PRIVATE ${SVG_COMMON_INCLUDE_DIRS})

#---

add_library(skshaper
        modules/skshaper/src/SkShaper.cpp
        modules/skshaper/src/SkShaper_primitive.cpp
)
target_compile_features(skshaper PUBLIC cxx_std_17)
target_include_directories(skshaper PRIVATE ${SVG_COMMON_INCLUDE_DIRS})

add_library(skunicode
        modules/skunicode/src/SkUnicode.cpp
        modules/skunicode/src/SkUnicode_hardcoded.cpp
)
target_compile_features(skunicode PUBLIC cxx_std_17)
target_include_directories(skunicode PRIVATE ${SVG_COMMON_INCLUDE_DIRS})

# Ensure text shaping symbols are resolved transitively:
# reskia -> svg -> skshaper -> skunicode
target_link_libraries(svg PUBLIC skshaper)
target_link_libraries(skshaper PUBLIC skunicode)

if(APPLE)
    target_compile_definitions(skshaper PRIVATE SK_SHAPER_CORETEXT_AVAILABLE SK_BUILD_FOR_MAC)
    target_sources(skshaper PRIVATE modules/skshaper/src/SkShaper_coretext.cpp)
endif()

set(SVG_DEP_HINTS
        "${CMAKE_PREFIX_PATH}"
        "${PROJECT_SOURCE_DIR}/../third_party/install"
)
if(DEFINED RESKIA_THIRD_PARTY_PREFIX AND NOT RESKIA_THIRD_PARTY_PREFIX STREQUAL "")
    list(PREPEND SVG_DEP_HINTS "${RESKIA_THIRD_PARTY_PREFIX}")
endif()

find_path(HARFBUZZ_INCLUDE_DIR
        NAMES hb.h
        HINTS ${SVG_DEP_HINTS}
        PATH_SUFFIXES include include/harfbuzz
)
find_library(HARFBUZZ_LIBRARY
        NAMES harfbuzz libharfbuzz
        HINTS ${SVG_DEP_HINTS}
        PATH_SUFFIXES lib lib64
)
if(HARFBUZZ_INCLUDE_DIR AND HARFBUZZ_LIBRARY)
    target_include_directories(skshaper PRIVATE "${HARFBUZZ_INCLUDE_DIR}")
    target_compile_definitions(skshaper PRIVATE SK_SHAPER_HARFBUZZ_AVAILABLE)
    target_sources(skshaper PRIVATE modules/skshaper/src/SkShaper_harfbuzz.cpp)
    target_link_libraries(skshaper PUBLIC "${HARFBUZZ_LIBRARY}")
elseif(HARFBUZZ_INCLUDE_DIR AND NOT HARFBUZZ_LIBRARY)
    message(WARNING "hb.h は検出されましたが libharfbuzz が見つからないため HarfBuzz 実装は無効化します。")
endif()

find_path(ICU_UBIDI_INCLUDE_DIR
        NAMES unicode/ubidi.h
        HINTS ${SVG_DEP_HINTS}
        PATH_SUFFIXES include
)
if(ICU_UBIDI_INCLUDE_DIR)
    find_library(ICU_I18N_LIBRARY NAMES icui18n HINTS ${SVG_DEP_HINTS} PATH_SUFFIXES lib lib64)
    find_library(ICU_UC_LIBRARY NAMES icuuc HINTS ${SVG_DEP_HINTS} PATH_SUFFIXES lib lib64)
    find_library(ICU_DATA_LIBRARY NAMES icudata HINTS ${SVG_DEP_HINTS} PATH_SUFFIXES lib lib64)

    target_include_directories(skunicode PRIVATE "${ICU_UBIDI_INCLUDE_DIR}")
    target_compile_definitions(skunicode PRIVATE SK_UNICODE_ICU_IMPLEMENTATION)
    target_sources(skunicode PRIVATE
            modules/skunicode/src/SkUnicode_icu.cpp
            modules/skunicode/src/SkUnicode_icu_bidi.cpp
            modules/skunicode/src/SkUnicode_icu_builtin.cpp
            modules/skunicode/src/SkUnicode_icu_runtime.cpp
            modules/skunicode/src/SkUnicode_client.cpp
    )

    if(ICU_I18N_LIBRARY AND ICU_UC_LIBRARY AND ICU_DATA_LIBRARY)
        target_link_libraries(skunicode PUBLIC
                "${ICU_I18N_LIBRARY}"
                "${ICU_UC_LIBRARY}"
                "${ICU_DATA_LIBRARY}"
        )
    endif()
endif()

find_path(ICU4X_INCLUDE_DIR ICU4XDataProvider.hpp)
if(ICU4X_INCLUDE_DIR)
    target_include_directories(skunicode PRIVATE "${ICU4X_INCLUDE_DIR}")
    target_compile_definitions(skunicode PRIVATE SK_UNICODE_ICU4X_IMPLEMENTATION)
    target_sources(skunicode PRIVATE modules/skunicode/src/SkUnicode_icu4x.cpp)
endif()

find_path(LIBGRAPHEME_INCLUDE_DIR grapheme.h)
if(LIBGRAPHEME_INCLUDE_DIR)
    target_include_directories(skunicode PRIVATE "${LIBGRAPHEME_INCLUDE_DIR}")
    target_compile_definitions(skunicode PRIVATE SK_UNICODE_LIBGRAPHEME_IMPLEMENTATION)
    target_sources(skunicode PRIVATE modules/skunicode/src/SkUnicode_libgrapheme.cpp)
endif()

if(ICU_UBIDI_INCLUDE_DIR)
    target_compile_definitions(skshaper PRIVATE SK_SHAPER_UNICODE_AVAILABLE)
    target_sources(skshaper PRIVATE modules/skshaper/src/SkShaper_skunicode.cpp)
endif()
