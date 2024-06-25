cmake_minimum_required(VERSION 3.26.4)
project(svg)

include_directories(${PROJECT_SOURCE_DIR}/)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/../skia)
link_directories(${PROJECT_SOURCE_DIR}/)
link_directories(${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_STANDARD 17)

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

#---

project(skshaper)
add_library(skshaper
        modules/skshaper/src/SkShaper.cpp
        modules/skshaper/src/SkShaper_coretext.cpp
        modules/skshaper/src/SkShaper_harfbuzz.cpp
        modules/skshaper/src/SkShaper_primitive.cpp
        modules/skshaper/src/SkShaper_skunicode.cpp
)

project(skunicode)
add_library(skunicode
        modules/skunicode/src/SkUnicode.cpp
        modules/skunicode/src/SkUnicode_client.cpp
        modules/skunicode/src/SkUnicode_hardcoded.cpp
        modules/skunicode/src/SkUnicode_icu.cpp
        modules/skunicode/src/SkUnicode_icu4x.cpp
        modules/skunicode/src/SkUnicode_icu_bidi.cpp
        modules/skunicode/src/SkUnicode_icu_builtin.cpp
        modules/skunicode/src/SkUnicode_icu_runtime.cpp
        modules/skunicode/src/SkUnicode_libgrapheme.cpp
        modules/skunicode/src/SkUnicode_client.cpp
)