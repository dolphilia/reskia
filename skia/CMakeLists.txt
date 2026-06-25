cmake_minimum_required(VERSION 3.26.4)
project(reskia)

if(APPLE)
    enable_language(OBJCXX)
endif()

set(RESKIA_ROOT_DIR "${PROJECT_SOURCE_DIR}/..")
include("${RESKIA_ROOT_DIR}/cmake/deps/ReskiaDeps.cmake")
reskia_resolve_third_party("${RESKIA_ROOT_DIR}" RESKIA_DEP_LINK_DIRS RESKIA_DEP_LIBS)
string(TOLOWER "${RESKIA_DEPS_MODE}" RESKIA_DEPS_MODE_LOWER)

if(RESKIA_DEPS_MODE_LOWER STREQUAL "source")
    if(NOT TARGET skcms)
        add_subdirectory("${PROJECT_SOURCE_DIR}/modules/skcms" "${CMAKE_BINARY_DIR}/_deps/skcms")
    endif()
    if(APPLE)
        if(NOT TARGET skresources)
            add_subdirectory("${PROJECT_SOURCE_DIR}/modules/skresources" "${CMAKE_BINARY_DIR}/_deps/skresources")
        endif()
        if(NOT TARGET svg)
            add_subdirectory("${PROJECT_SOURCE_DIR}/modules/svg" "${CMAKE_BINARY_DIR}/_deps/svg")
        endif()
    endif()
endif()

if(APPLE AND NOT RESKIA_DEPS_MODE_LOWER STREQUAL "source")
    if(NOT TARGET skresources)
        add_subdirectory("${PROJECT_SOURCE_DIR}/modules/skresources" "${CMAKE_BINARY_DIR}/_deps/skresources")
    endif()
    set(RESKIA_SVG_SHAPING_INCLUDE_DIRS
            "${PROJECT_SOURCE_DIR}"
            "${PROJECT_SOURCE_DIR}/modules/svg/include"
    )
    if(NOT TARGET skunicode)
        add_library(skunicode
                modules/skunicode/src/SkUnicode.cpp
                modules/skunicode/src/SkUnicode_hardcoded.cpp
        )
        target_compile_features(skunicode PUBLIC cxx_std_20)
        target_include_directories(skunicode PRIVATE ${RESKIA_SVG_SHAPING_INCLUDE_DIRS})
    endif()
    if(NOT TARGET skshaper)
        add_library(skshaper
                modules/skshaper/src/SkShaper.cpp
                modules/skshaper/src/SkShaper_factory.cpp
                modules/skshaper/src/SkShaper_primitive.cpp
                modules/skshaper/src/SkShaper_coretext.cpp
        )
        target_compile_features(skshaper PUBLIC cxx_std_20)
        target_include_directories(skshaper PRIVATE ${RESKIA_SVG_SHAPING_INCLUDE_DIRS})
        target_compile_definitions(skshaper PRIVATE SK_SHAPER_CORETEXT_AVAILABLE SK_BUILD_FOR_MAC)
        target_link_libraries(skshaper PUBLIC skunicode)
    endif()
endif()

set(RESKIA_INTERNAL_LIBS skcms)
if(APPLE)
    list(APPEND RESKIA_INTERNAL_LIBS skresources svg)
    if(TARGET skshaper)
        list(APPEND RESKIA_INTERNAL_LIBS skshaper)
    endif()
    if(TARGET skunicode)
        list(APPEND RESKIA_INTERNAL_LIBS skunicode)
    endif()
endif()

set(RESKIA_RESOLVED_INTERNAL_LIBS "")
foreach(_reskia_internal_lib IN LISTS RESKIA_INTERNAL_LIBS)
    if(TARGET ${_reskia_internal_lib})
        list(APPEND RESKIA_RESOLVED_INTERNAL_LIBS ${_reskia_internal_lib})
    else()
        find_library(_reskia_internal_lib_path
                NAMES ${_reskia_internal_lib} lib${_reskia_internal_lib}
                PATHS
                "${RESKIA_THIRD_PARTY_PREFIX}"
                "${RESKIA_ROOT_DIR}/third_party/install"
                PATH_SUFFIXES lib lib64
        )
        if(NOT _reskia_internal_lib_path)
            message(FATAL_ERROR
                    "Required internal library not found: ${_reskia_internal_lib} "
                    "(RESKIA_DEPS_MODE=${RESKIA_DEPS_MODE}).")
        endif()
        list(APPEND RESKIA_RESOLVED_INTERNAL_LIBS "${_reskia_internal_lib_path}")
    endif()
    unset(_reskia_internal_lib_path CACHE)
endforeach()

if(RESKIA_ENABLE_SKOTTIE)
    if(NOT APPLE)
        message(FATAL_ERROR "RESKIA_ENABLE_SKOTTIE=ON is currently supported only on Apple platforms.")
    endif()
    if(RESKIA_DEPS_MODE_LOWER STREQUAL "source")
        if((NOT TARGET skresources) OR (NOT TARGET svg))
            message(FATAL_ERROR
                    "RESKIA_ENABLE_SKOTTIE=ON requires skresources and svg to be resolved in source mode."
            )
        endif()
    endif()
endif()

if(RESKIA_ENABLE_SKPARAGRAPH)
    if(NOT APPLE)
        message(FATAL_ERROR "RESKIA_ENABLE_SKPARAGRAPH=ON is currently supported only on Apple platforms.")
    endif()
    if(NOT RESKIA_DEPS_MODE_LOWER STREQUAL "source")
        message(FATAL_ERROR "RESKIA_ENABLE_SKPARAGRAPH=ON currently requires RESKIA_DEPS_MODE=source.")
    endif()
    if(NOT TARGET skshaper OR NOT TARGET skunicode)
        message(FATAL_ERROR
                "RESKIA_ENABLE_SKPARAGRAPH=ON requires skshaper/skunicode to be resolved in source mode."
        )
    endif()

    set(RESKIA_SKPARAGRAPH_HARFBUZZ_HINTS
            "${RESKIA_THIRD_PARTY_PREFIX}"
            "${RESKIA_ROOT_DIR}/third_party/install"
    )
    find_path(RESKIA_SKPARAGRAPH_HARFBUZZ_INCLUDE_DIR
            NAMES hb.h
            HINTS ${RESKIA_SKPARAGRAPH_HARFBUZZ_HINTS}
            PATH_SUFFIXES include include/harfbuzz
    )
    if(NOT RESKIA_SKPARAGRAPH_HARFBUZZ_INCLUDE_DIR)
        message(FATAL_ERROR
                "RESKIA_ENABLE_SKPARAGRAPH=ON requires hb.h. Install HarfBuzz or provide its include path."
        )
    endif()
    find_library(RESKIA_SKPARAGRAPH_HARFBUZZ_LIBRARY
            NAMES harfbuzz libharfbuzz
            HINTS ${RESKIA_SKPARAGRAPH_HARFBUZZ_HINTS}
            PATH_SUFFIXES lib lib64
    )
    if(NOT RESKIA_SKPARAGRAPH_HARFBUZZ_LIBRARY)
        message(FATAL_ERROR
                "RESKIA_ENABLE_SKPARAGRAPH=ON requires libharfbuzz. Install HarfBuzz or provide its library path."
        )
    endif()

    find_path(RESKIA_SKPARAGRAPH_ICU_UBIDI_INCLUDE_DIR
            NAMES unicode/ubidi.h
            HINTS ${RESKIA_SKPARAGRAPH_HARFBUZZ_HINTS}
            PATH_SUFFIXES include
    )
endif()

if(RESKIA_ENABLE_GPU_VULKAN OR RESKIA_ENABLE_GPU_METAL OR RESKIA_ENABLE_GPU_DAWN)
    if(NOT (RESKIA_ENABLE_GPU_GANESH OR RESKIA_ENABLE_GPU_GRAPHITE))
        message(FATAL_ERROR
                "RESKIA_ENABLE_GPU_VULKAN/METAL/DAWN requires "
                "RESKIA_ENABLE_GPU_GANESH or RESKIA_ENABLE_GPU_GRAPHITE to be enabled.")
    endif()
endif()

if(RESKIA_ENABLE_GPU_DAWN AND NOT RESKIA_ENABLE_GPU_GRAPHITE)
    message(FATAL_ERROR "RESKIA_ENABLE_GPU_DAWN=ON currently requires RESKIA_ENABLE_GPU_GRAPHITE=ON.")
endif()

if(RESKIA_ENABLE_GPU_METAL AND NOT APPLE)
    message(FATAL_ERROR "RESKIA_ENABLE_GPU_METAL=ON is currently supported only on Apple platforms.")
endif()

if(RESKIA_ENABLE_GPU_GRAPHITE AND NOT (RESKIA_ENABLE_GPU_METAL OR RESKIA_ENABLE_GPU_VULKAN OR RESKIA_ENABLE_GPU_DAWN))
    message(FATAL_ERROR
            "RESKIA_ENABLE_GPU_GRAPHITE=ON requires at least one backend "
            "(RESKIA_ENABLE_GPU_METAL / RESKIA_ENABLE_GPU_VULKAN / RESKIA_ENABLE_GPU_DAWN) to be enabled.")
endif()

if(RESKIA_ENABLE_GPU_GRAPHITE)
    set(_reskia_required_graphite_sksl
            "sksl_graphite_frag.minified.sksl"
            "sksl_graphite_vert.minified.sksl")
    set(_reskia_missing_graphite_sksl "")
    foreach(_reskia_sksl_file IN LISTS _reskia_required_graphite_sksl)
        if(NOT EXISTS "${PROJECT_SOURCE_DIR}/src/sksl/generated/${_reskia_sksl_file}")
            list(APPEND _reskia_missing_graphite_sksl "${_reskia_sksl_file}")
        endif()
    endforeach()
    if(_reskia_missing_graphite_sksl)
        string(JOIN ", " _reskia_missing_graphite_sksl_joined ${_reskia_missing_graphite_sksl})
        message(FATAL_ERROR
                "RESKIA_ENABLE_GPU_GRAPHITE=ON requires missing src/sksl/generated files: "
                "${_reskia_missing_graphite_sksl_joined}. "
                "Sync them from vendor/skia-upstream/src/sksl/generated.")
    endif()
endif()

set(RESKIA_VMA_INCLUDE_DIR "" CACHE PATH "Directory containing vk_mem_alloc.h (required when RESKIA_ENABLE_GPU_VULKAN=ON)")
if(RESKIA_ENABLE_GPU_VULKAN)
    find_package(Vulkan REQUIRED)
    if(RESKIA_VMA_INCLUDE_DIR STREQUAL "")
        find_path(RESKIA_VMA_INCLUDE_DIR
                NAMES vk_mem_alloc.h
                HINTS
                "${RESKIA_ROOT_DIR}/third_party/src/vulkanmemoryallocator"
                "${RESKIA_ROOT_DIR}/third_party/install"
                "${RESKIA_THIRD_PARTY_PREFIX}"
                PATH_SUFFIXES include include/vma
        )
    endif()
    if(NOT RESKIA_VMA_INCLUDE_DIR)
        message(FATAL_ERROR
                "RESKIA_ENABLE_GPU_VULKAN=ON requires vk_mem_alloc.h. "
                "Set RESKIA_VMA_INCLUDE_DIR.")
    endif()
endif()

set(RESKIA_DAWN_INCLUDE_DIR "" CACHE PATH "Dawn include directory (required when RESKIA_ENABLE_GPU_DAWN=ON)")
set(RESKIA_DAWN_LIBRARY "" CACHE FILEPATH "Dawn library path (required when RESKIA_ENABLE_GPU_DAWN=ON)")
if(RESKIA_ENABLE_GPU_DAWN)
    if(RESKIA_DAWN_INCLUDE_DIR STREQUAL "")
        find_path(RESKIA_DAWN_INCLUDE_DIR
                NAMES dawn/webgpu.h webgpu/webgpu.h
                HINTS "${RESKIA_THIRD_PARTY_PREFIX}" "${RESKIA_ROOT_DIR}/third_party/install"
                PATH_SUFFIXES include
        )
    endif()
    if(RESKIA_DAWN_LIBRARY STREQUAL "")
        find_library(RESKIA_DAWN_LIBRARY
                NAMES dawn webgpu_dawn dawn_native
                HINTS "${RESKIA_THIRD_PARTY_PREFIX}" "${RESKIA_ROOT_DIR}/third_party/install"
                PATH_SUFFIXES lib lib64
        )
    endif()
    if(NOT RESKIA_DAWN_INCLUDE_DIR OR NOT RESKIA_DAWN_LIBRARY)
        message(FATAL_ERROR
                "RESKIA_ENABLE_GPU_DAWN=ON requires Dawn dependencies. "
                "Set RESKIA_DAWN_INCLUDE_DIR and RESKIA_DAWN_LIBRARY.")
    endif()
endif()

set(SOURCE_FILES)

include("${RESKIA_ROOT_DIR}/cmake/reskia/sources-core.cmake")
include("${RESKIA_ROOT_DIR}/cmake/reskia/sources-capi.cmake")
include("${RESKIA_ROOT_DIR}/cmake/reskia/sources-handles.cmake")

if (WIN32)
    list(APPEND SOURCE_FILES
            src/ports/SkLog_win.cpp
            src/ports/SkOSFile_win.cpp
            src/ports/SkTypeface_win_dw.cpp
            src/ports/SkScalerContext_win_dw.cpp
            src/sfnt/SkOTTable_name.cpp
            src/sfnt/SkOTUtils.cpp
            src/utils/win/SkAutoCoInitialize.cpp
            src/utils/win/SkDWrite.cpp
            src/utils/win/SkDWriteFontFileStream.cpp
            src/utils/win/SkDWriteGeometrySink.cpp
            src/utils/win/SkHRESULT.cpp
            src/utils/win/SkIStream.cpp
            src/ports/SkFontMgr_win_dw.cpp
    )
elseif (APPLE)
    list(APPEND SOURCE_FILES
            src/ports/SkFontMgr_mac_ct.cpp
            src/sfnt/SkOTTable_name.cpp
            src/sfnt/SkOTUtils.cpp
            src/ports/SkScalerContext_mac_ct.cpp
            src/ports/SkTypeface_mac_ct.cpp
            src/ports/SkOSFile_posix.cpp
            capi/sk_typeface_mac.cpp
            src/utils/mac/SkCTFont.cpp
            src/utils/mac/SkCTFontCreateExactCopy.cpp
    )
elseif (UNIX)
    list(APPEND SOURCE_FILES
            src/ports/SkOSFile_posix.cpp
    )
endif()

add_library(reskia SHARED ${SOURCE_FILES})
if(APPLE AND RESKIA_ENABLE_GPU_METAL)
    set_source_files_properties("${PROJECT_SOURCE_DIR}/capi/sk_gpu_context.cpp"
            PROPERTIES LANGUAGE OBJCXX)
    set(_reskia_gpu_mtl_sources "")
    foreach(_reskia_src IN LISTS SOURCE_FILES)
        if(_reskia_src MATCHES "^src/gpu/.+\\.mm$" AND NOT _reskia_src MATCHES "^src/gpu/graphite/mtl/.+\\.mm$")
            list(APPEND _reskia_gpu_mtl_sources "${PROJECT_SOURCE_DIR}/${_reskia_src}")
        endif()
    endforeach()
    if(_reskia_gpu_mtl_sources)
        set_source_files_properties(${_reskia_gpu_mtl_sources}
                PROPERTIES COMPILE_OPTIONS "-fobjc-arc")
    endif()
endif()
if(RESKIA_ENABLE_GPU_GANESH OR RESKIA_ENABLE_GPU_GRAPHITE OR RESKIA_ENABLE_SKPARAGRAPH)
    target_compile_features(reskia PRIVATE cxx_std_20)
else()
    target_compile_features(reskia PRIVATE cxx_std_17)
endif()
set(_reskia_external_include_root "${RESKIA_THIRD_PARTY_PREFIX}")
if(_reskia_external_include_root STREQUAL "")
    set(_reskia_external_include_root "${RESKIA_ROOT_DIR}/third_party/install")
endif()
set(RESKIA_PUBLIC_INCLUDE_DIRS
        "${PROJECT_SOURCE_DIR}"
        "${_reskia_external_include_root}/include"
)
if(EXISTS "${_reskia_external_include_root}/include/libpng18")
    list(APPEND RESKIA_PUBLIC_INCLUDE_DIRS "${_reskia_external_include_root}/include/libpng18")
endif()
target_include_directories(reskia
    PRIVATE
        ${RESKIA_PUBLIC_INCLUDE_DIRS}
)
if(RESKIA_ENABLE_SKPARAGRAPH)
    target_include_directories(reskia PRIVATE "${RESKIA_SKPARAGRAPH_HARFBUZZ_INCLUDE_DIR}")
endif()
if(RESKIA_ENABLE_GPU_DAWN)
    target_include_directories(reskia PRIVATE "${RESKIA_DAWN_INCLUDE_DIR}")
endif()
if(RESKIA_ENABLE_GPU_VULKAN)
    target_include_directories(reskia PRIVATE "${RESKIA_VMA_INCLUDE_DIR}")
endif()
if(RESKIA_DEP_LINK_DIRS)
    target_link_directories(reskia PRIVATE ${RESKIA_DEP_LINK_DIRS})
endif()
target_compile_definitions(reskia PRIVATE SK_ENABLE_OPTIMIZE_SIZE)
if(RESKIA_ENABLE_SKOTTIE)
    target_compile_definitions(reskia PRIVATE
            SK_ENABLE_SKOTTIE
            SK_ENABLE_SKOTTIE_SKSLEFFECT
    )
endif()
if(RESKIA_ENABLE_SKPARAGRAPH)
    target_compile_definitions(reskia PRIVATE
            SK_ENABLE_PARAGRAPH
            SK_UNICODE_CLIENT_IMPLEMENTATION
            SK_SHAPER_HARFBUZZ_AVAILABLE
    )
    if(RESKIA_SKPARAGRAPH_ICU_UBIDI_INCLUDE_DIR)
        target_compile_definitions(reskia PRIVATE SK_SHAPER_UNICODE_AVAILABLE)
    endif()
endif()
if(RESKIA_ENABLE_AVIF)
    if("src/codec/SkAvifCodec.cpp" IN_LIST SOURCE_FILES)
        target_compile_definitions(reskia PRIVATE SK_CODEC_DECODES_AVIF)
    else()
        message(WARNING "RESKIA_ENABLE_AVIF=ON, but src/codec/SkAvifCodec.cpp is not registered in SOURCE_FILES; the decoder macro will not be defined.")
    endif()
endif()
if(RESKIA_ENABLE_JPEGXL)
    if("src/codec/SkJpegxlCodec.cpp" IN_LIST SOURCE_FILES)
        target_compile_definitions(reskia PRIVATE SK_CODEC_DECODES_JPEGXL)
    else()
        message(WARNING "RESKIA_ENABLE_JPEGXL=ON, but src/codec/SkJpegxlCodec.cpp is not registered in SOURCE_FILES; the decoder macro will not be defined.")
    endif()
endif()
if(RESKIA_ENABLE_JPEG_GAINMAP)
    if("src/codec/SkJpegXmp.cpp" IN_LIST SOURCE_FILES AND "src/codec/SkXmp.cpp" IN_LIST SOURCE_FILES)
        target_compile_definitions(reskia PRIVATE SK_CODEC_DECODES_JPEG_GAINMAPS)
    else()
        message(WARNING
                "RESKIA_ENABLE_JPEG_GAINMAP=ON, but src/codec/SkJpegXmp.cpp or src/codec/SkXmp.cpp is "
                "not registered in SOURCE_FILES; the gainmap macro will not be defined.")
    endif()
endif()
if(RESKIA_ENABLE_RAW)
    if("src/codec/SkRawCodec.cpp" IN_LIST SOURCE_FILES)
        target_include_directories(reskia PRIVATE
                "${RESKIA_ROOT_DIR}/third_party/src/dng_sdk/source"
                "${RESKIA_ROOT_DIR}/third_party/src/piex"
        )
        target_compile_definitions(reskia PRIVATE
                qDNGBigEndian=0
                qDNGReportErrors=0
                qDNGThreadSafe=1
                qDNGUseLibJPEG=1
                qDNGUseXMP=0
                qDNGValidate=0
                qDNGValidateTarget=1
                UNIX_ENV=1
                BREAK_IF_DEBUGGING_AND_OUT_OF_RANGE
        )
        target_compile_definitions(reskia PRIVATE SK_CODEC_DECODES_RAW)
    else()
        message(WARNING "RESKIA_ENABLE_RAW=ON, but src/codec/SkRawCodec.cpp is not registered in SOURCE_FILES; the decoder macro will not be defined.")
    endif()
endif()
if(RESKIA_ENABLE_GIF)
    if("src/codec/SkWuffsCodec.cpp" IN_LIST SOURCE_FILES)
        target_include_directories(reskia PRIVATE "${RESKIA_ROOT_DIR}/third_party/src/wuffs/release/c")
        if("${RESKIA_ROOT_DIR}/third_party/src/wuffs/release/c/wuffs-v0.3.c" IN_LIST SOURCE_FILES)
            set_source_files_properties(
                    "${RESKIA_ROOT_DIR}/third_party/src/wuffs/release/c/wuffs-v0.3.c"
                    PROPERTIES COMPILE_DEFINITIONS
                    "WUFFS_IMPLEMENTATION;WUFFS_CONFIG__MODULES;WUFFS_CONFIG__MODULE__BASE;WUFFS_CONFIG__MODULE__GIF;WUFFS_CONFIG__MODULE__LZW"
            )
        endif()
        target_compile_definitions(reskia PRIVATE SK_HAS_WUFFS_LIBRARY)
    else()
        message(WARNING "RESKIA_ENABLE_GIF=ON, but src/codec/SkWuffsCodec.cpp is not registered in SOURCE_FILES; the decoder macro will not be defined.")
    endif()
endif()
if(RESKIA_ENABLE_PDF)
    if("src/pdf/SkPDFDocument.cpp" IN_LIST SOURCE_FILES)
        target_compile_definitions(reskia PRIVATE SK_SUPPORT_PDF)
    else()
        message(WARNING "RESKIA_ENABLE_PDF=ON, but src/pdf/SkPDFDocument.cpp is not registered in SOURCE_FILES; the PDF macro will not be defined.")
    endif()
endif()
if(RESKIA_ENABLE_FONTCONFIG_CAPI)
    if(NOT UNIX)
        message(FATAL_ERROR "RESKIA_ENABLE_FONTCONFIG_CAPI=ON is currently supported only on UNIX platforms.")
    endif()
    if("capi/sk_font_mgr_fontconfig.cpp" IN_LIST SOURCE_FILES)
        find_path(RESKIA_FONTCONFIG_INCLUDE_DIR
                NAMES fontconfig/fontconfig.h
                HINTS "${RESKIA_THIRD_PARTY_PREFIX}" "${RESKIA_ROOT_DIR}/third_party/install"
                PATH_SUFFIXES include
        )
        find_library(RESKIA_FONTCONFIG_LIBRARY
                NAMES fontconfig libfontconfig
                HINTS "${RESKIA_THIRD_PARTY_PREFIX}" "${RESKIA_ROOT_DIR}/third_party/install"
                PATH_SUFFIXES lib lib64
        )
        if(NOT RESKIA_FONTCONFIG_INCLUDE_DIR OR NOT RESKIA_FONTCONFIG_LIBRARY)
            message(FATAL_ERROR
                    "RESKIA_ENABLE_FONTCONFIG_CAPI=ON requires fontconfig. "
                    "Install fontconfig/fontconfig.h and libfontconfig, or provide their paths.")
        endif()
        find_package(Freetype QUIET)
        if(Freetype_FOUND)
            set(RESKIA_FREETYPE_INCLUDE_DIRS "${FREETYPE_INCLUDE_DIRS}")
            set(RESKIA_FREETYPE_LIBRARIES "${FREETYPE_LIBRARIES}")
        else()
            find_path(RESKIA_FREETYPE_INCLUDE_DIR
                    NAMES ft2build.h
                    HINTS "${RESKIA_THIRD_PARTY_PREFIX}" "${RESKIA_ROOT_DIR}/third_party/install"
                    PATH_SUFFIXES include include/freetype2
            )
            find_library(RESKIA_FREETYPE_LIBRARY
                    NAMES freetype libfreetype
                    HINTS "${RESKIA_THIRD_PARTY_PREFIX}" "${RESKIA_ROOT_DIR}/third_party/install"
                    PATH_SUFFIXES lib lib64
            )
            if(RESKIA_FREETYPE_INCLUDE_DIR AND RESKIA_FREETYPE_LIBRARY)
                set(RESKIA_FREETYPE_INCLUDE_DIRS "${RESKIA_FREETYPE_INCLUDE_DIR}")
                set(RESKIA_FREETYPE_LIBRARIES "${RESKIA_FREETYPE_LIBRARY}")
            endif()
        endif()
        if(NOT RESKIA_FREETYPE_INCLUDE_DIRS OR NOT RESKIA_FREETYPE_LIBRARIES)
            message(FATAL_ERROR
                    "RESKIA_ENABLE_FONTCONFIG_CAPI=ON requires FreeType. "
                    "Install ft2build.h and libfreetype, or provide their paths.")
        endif()
        target_include_directories(reskia PRIVATE "${RESKIA_FONTCONFIG_INCLUDE_DIR}")
        target_include_directories(reskia PRIVATE ${RESKIA_FREETYPE_INCLUDE_DIRS})
        target_link_libraries(reskia "${RESKIA_FONTCONFIG_LIBRARY}" ${RESKIA_FREETYPE_LIBRARIES})
    else()
        message(WARNING
                "RESKIA_ENABLE_FONTCONFIG_CAPI=ON, but capi/sk_font_mgr_fontconfig.cpp is not registered in SOURCE_FILES.")
    endif()
endif()
if(RESKIA_ENABLE_GPU_GANESH)
    target_compile_definitions(reskia PRIVATE SK_GANESH)
endif()
if(RESKIA_ENABLE_GPU_GRAPHITE)
    target_compile_definitions(reskia PRIVATE SK_GRAPHITE)
endif()
if(RESKIA_ENABLE_GPU_VULKAN)
    target_compile_definitions(reskia PRIVATE SK_VULKAN SK_USE_VMA)
endif()
if(RESKIA_ENABLE_GPU_METAL)
    target_compile_definitions(reskia PRIVATE SK_METAL)
endif()
if(RESKIA_ENABLE_GPU_DAWN)
    target_compile_definitions(reskia PRIVATE SK_DAWN)
endif()
if(TARGET skunicode)
    target_compile_definitions(reskia PRIVATE $<TARGET_PROPERTY:skunicode,COMPILE_DEFINITIONS>)
endif()

if(WIN32)
    target_link_libraries(reskia ${RESKIA_RESOLVED_INTERNAL_LIBS} ${RESKIA_DEP_LIBS})
elseif(APPLE)
    target_link_libraries(reskia ${RESKIA_RESOLVED_INTERNAL_LIBS} ${RESKIA_DEP_LIBS} "-framework Cocoa" "-framework CoreFoundation" "-framework CoreText")
    if(RESKIA_ENABLE_GPU_METAL)
        target_link_libraries(reskia "-framework Metal" "-framework QuartzCore")
    endif()
elseif(UNIX)
    target_link_libraries(reskia ${RESKIA_RESOLVED_INTERNAL_LIBS} ${RESKIA_DEP_LIBS})
endif()

if(RESKIA_ENABLE_GPU_VULKAN)
    target_link_libraries(reskia Vulkan::Vulkan)
endif()
if(RESKIA_ENABLE_GPU_DAWN)
    target_link_libraries(reskia "${RESKIA_DAWN_LIBRARY}")
endif()

if(WIN32)
    set_target_properties(reskia PROPERTIES PREFIX "lib")
endif()

# TEST
include("${RESKIA_ROOT_DIR}/cmake/reskia/tests.cmake")
