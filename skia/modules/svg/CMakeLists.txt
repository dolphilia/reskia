cmake_minimum_required(VERSION 3.26.4)
project(svg LANGUAGES CXX)

if(NOT DEFINED RESKIA_ROOT_DIR OR RESKIA_ROOT_DIR STREQUAL "")
    get_filename_component(RESKIA_ROOT_DIR "${PROJECT_SOURCE_DIR}/../../.." ABSOLUTE)
endif()

set(SVG_COMMON_INCLUDE_DIRS
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/../.."
)

add_library(svg
        src/SkSVGAttribute.cpp
        src/SkSVGAttributeParser.cpp
        src/SkSVGCircle.cpp
        src/SkSVGClipPath.cpp
        src/SkSVGContainer.cpp
        src/SkSVGDOM.cpp
        src/SkSVGEllipse.cpp
        src/SkSVGFe.cpp
        src/SkSVGFeBlend.cpp
        src/SkSVGFeColorMatrix.cpp
        src/SkSVGFeComposite.cpp
        src/SkSVGFeDisplacementMap.cpp
        src/SkSVGFeFlood.cpp
        src/SkSVGFeGaussianBlur.cpp
        src/SkSVGFeImage.cpp
        src/SkSVGFeLightSource.cpp
        src/SkSVGFeLighting.cpp
        src/SkSVGFeMorphology.cpp
        src/SkSVGFeOffset.cpp
        src/SkSVGFeTurbulence.cpp
        src/SkSVGFilter.cpp
        src/SkSVGFilterContext.cpp
        src/SkSVGGradient.cpp
        src/SkSVGImage.cpp
        src/SkSVGLine.cpp
        src/SkSVGLinearGradient.cpp
        src/SkSVGMask.cpp
        src/SkSVGNode.cpp
        src/SkSVGOpenTypeSVGDecoder.cpp
        src/SkSVGPath.cpp
        src/SkSVGPattern.cpp
        src/SkSVGPoly.cpp
        src/SkSVGRadialGradient.cpp
        src/SkSVGRect.cpp
        src/SkSVGRenderContext.cpp
        src/SkSVGSVG.cpp
        src/SkSVGShape.cpp
        src/SkSVGStop.cpp
        src/SkSVGText.cpp
        src/SkSVGTextPriv.h
        src/SkSVGTransformableNode.cpp
        src/SkSVGUse.cpp
        src/SkSVGValue.cpp
)
target_compile_features(svg PUBLIC cxx_std_17)
target_include_directories(svg PRIVATE ${SVG_COMMON_INCLUDE_DIRS})

#---

add_library(skshaper
        ../skshaper/src/SkShaper.cpp
        ../skshaper/src/SkShaper_primitive.cpp
)
target_compile_features(skshaper PUBLIC cxx_std_17)
target_include_directories(skshaper PRIVATE ${SVG_COMMON_INCLUDE_DIRS})

add_library(skunicode
        ../skunicode/src/SkUnicode.cpp
        ../skunicode/src/SkUnicode_hardcoded.cpp
)
target_compile_features(skunicode PUBLIC cxx_std_17)
target_include_directories(skunicode PRIVATE ${SVG_COMMON_INCLUDE_DIRS})

# Ensure text shaping symbols are resolved transitively:
# reskia -> svg -> skshaper -> skunicode
target_link_libraries(svg PUBLIC skshaper)
target_link_libraries(skshaper PUBLIC skunicode)

if(APPLE)
    target_compile_definitions(skshaper PRIVATE SK_SHAPER_CORETEXT_AVAILABLE SK_BUILD_FOR_MAC)
    target_sources(skshaper PRIVATE ../skshaper/src/SkShaper_coretext.cpp)
endif()

set(SVG_DEP_HINTS
        "${CMAKE_PREFIX_PATH}"
        "${RESKIA_ROOT_DIR}/third_party/install"
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
    target_sources(skshaper PRIVATE ../skshaper/src/SkShaper_harfbuzz.cpp)
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
            ../skunicode/src/SkUnicode_icu.cpp
            ../skunicode/src/SkUnicode_icu_bidi.cpp
            ../skunicode/src/SkUnicode_icu_builtin.cpp
            ../skunicode/src/SkUnicode_icu_runtime.cpp
            ../skunicode/src/SkUnicode_client.cpp
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
    target_sources(skunicode PRIVATE ../skunicode/src/SkUnicode_icu4x.cpp)
endif()

find_path(LIBGRAPHEME_INCLUDE_DIR grapheme.h)
if(LIBGRAPHEME_INCLUDE_DIR)
    target_include_directories(skunicode PRIVATE "${LIBGRAPHEME_INCLUDE_DIR}")
    target_compile_definitions(skunicode PRIVATE SK_UNICODE_LIBGRAPHEME_IMPLEMENTATION)
    target_sources(skunicode PRIVATE ../skunicode/src/SkUnicode_libgrapheme.cpp)
endif()

if(ICU_UBIDI_INCLUDE_DIR)
    target_compile_definitions(skshaper PRIVATE SK_SHAPER_UNICODE_AVAILABLE)
    target_sources(skshaper PRIVATE ../skshaper/src/SkShaper_skunicode.cpp)
endif()
