cmake_minimum_required(VERSION 3.26.4)
project(reskia)

set(RESKIA_ROOT_DIR "${PROJECT_SOURCE_DIR}/..")
include("${RESKIA_ROOT_DIR}/cmake/deps/ReskiaDeps.cmake")
reskia_resolve_third_party("${RESKIA_ROOT_DIR}" RESKIA_DEP_LINK_DIRS RESKIA_DEP_LIBS)
string(TOLOWER "${RESKIA_DEPS_MODE}" RESKIA_DEPS_MODE_LOWER)

if(RESKIA_DEPS_MODE_LOWER STREQUAL "source")
    if(NOT TARGET skcms)
        add_subdirectory("${RESKIA_ROOT_DIR}/skcms" "${CMAKE_BINARY_DIR}/_deps/skcms")
    endif()
    if(APPLE)
        if(NOT TARGET skresources)
            add_subdirectory("${RESKIA_ROOT_DIR}/skresources" "${CMAKE_BINARY_DIR}/_deps/skresources")
        endif()
        if(NOT TARGET svg)
            add_subdirectory("${RESKIA_ROOT_DIR}/svg" "${CMAKE_BINARY_DIR}/_deps/svg")
        endif()
    endif()
endif()

set(RESKIA_INTERNAL_LIBS skcms)
if(APPLE)
    list(APPEND RESKIA_INTERNAL_LIBS skresources svg)
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
                "${RESKIA_ROOT_DIR}/skia/lib"
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
        message(FATAL_ERROR "RESKIA_ENABLE_SKOTTIE=ON は現在 APPLE のみ対応です。")
    endif()
    if(RESKIA_DEPS_MODE_LOWER STREQUAL "source")
        if((NOT TARGET skresources) OR (NOT TARGET svg))
            message(FATAL_ERROR
                    "RESKIA_ENABLE_SKOTTIE=ON には skresources と svg の source モード解決が必要です。"
            )
        endif()
    endif()
endif()

if(RESKIA_ENABLE_SKPARAGRAPH)
    if(NOT APPLE)
        message(FATAL_ERROR "RESKIA_ENABLE_SKPARAGRAPH=ON は現在 APPLE のみ対応です。")
    endif()
    if(NOT RESKIA_DEPS_MODE_LOWER STREQUAL "source")
        message(FATAL_ERROR "RESKIA_ENABLE_SKPARAGRAPH=ON は現在 RESKIA_DEPS_MODE=source のみ対応です。")
    endif()
    if(NOT TARGET skshaper OR NOT TARGET skunicode)
        message(FATAL_ERROR
                "RESKIA_ENABLE_SKPARAGRAPH=ON には skshaper/skunicode の source モード解決が必要です。"
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
                "RESKIA_ENABLE_SKPARAGRAPH=ON ですが hb.h が見つかりません。HarfBuzz を導入してください。"
        )
    endif()
    find_library(RESKIA_SKPARAGRAPH_HARFBUZZ_LIBRARY
            NAMES harfbuzz libharfbuzz
            HINTS ${RESKIA_SKPARAGRAPH_HARFBUZZ_HINTS}
            PATH_SUFFIXES lib lib64
    )
    if(NOT RESKIA_SKPARAGRAPH_HARFBUZZ_LIBRARY)
        message(FATAL_ERROR
                "RESKIA_ENABLE_SKPARAGRAPH=ON ですが libharfbuzz が見つかりません。HarfBuzz を導入してください。"
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
                "RESKIA_ENABLE_GPU_VULKAN/METAL/DAWN を有効化する場合は "
                "RESKIA_ENABLE_GPU_GANESH または RESKIA_ENABLE_GPU_GRAPHITE も有効化してください。")
    endif()
endif()

if(RESKIA_ENABLE_GPU_DAWN AND NOT RESKIA_ENABLE_GPU_GRAPHITE)
    message(FATAL_ERROR "RESKIA_ENABLE_GPU_DAWN=ON は現在 RESKIA_ENABLE_GPU_GRAPHITE=ON が必須です。")
endif()

if(RESKIA_ENABLE_GPU_METAL AND NOT APPLE)
    message(FATAL_ERROR "RESKIA_ENABLE_GPU_METAL=ON は現在 APPLE のみ対応です。")
endif()

if(RESKIA_ENABLE_GPU_GRAPHITE AND NOT (RESKIA_ENABLE_GPU_METAL OR RESKIA_ENABLE_GPU_VULKAN OR RESKIA_ENABLE_GPU_DAWN))
    message(FATAL_ERROR
            "RESKIA_ENABLE_GPU_GRAPHITE=ON の場合は少なくとも 1 つの backend "
            "(RESKIA_ENABLE_GPU_METAL / RESKIA_ENABLE_GPU_VULKAN / RESKIA_ENABLE_GPU_DAWN) を有効化してください。")
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
                "RESKIA_ENABLE_GPU_GRAPHITE=ON ですが src/sksl/generated の同期が不足しています: "
                "${_reskia_missing_graphite_sksl_joined}。"
                "vendor/skia-upstream/src/sksl/generated から同期してください。")
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
                "RESKIA_ENABLE_GPU_VULKAN=ON ですが vk_mem_alloc.h が見つかりません。"
                "RESKIA_VMA_INCLUDE_DIR を指定してください。")
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
                "RESKIA_ENABLE_GPU_DAWN=ON ですが Dawn 依存が見つかりません。"
                "RESKIA_DAWN_INCLUDE_DIR と RESKIA_DAWN_LIBRARY を指定してください。")
    endif()
endif()

set(SOURCE_FILES)

include("${RESKIA_ROOT_DIR}/cmake/reskia/sources-core.cmake")
include("${RESKIA_ROOT_DIR}/cmake/reskia/sources-capi.cmake")
include("${RESKIA_ROOT_DIR}/cmake/reskia/sources-handles.cmake")

if (WIN32)
    list(APPEND SOURCE_FILES
            src/fonts/SkFontMgr_indirect.cpp
            src/fonts/SkRemotableFontMgr.cpp
            src/ports/SkDebug_win.cpp
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
            src/ports/SkFontMgr_win_dw_factory.cpp
    )
elseif (APPLE)
    list(APPEND SOURCE_FILES
            src/ports/SkFontMgr_mac_ct.cpp
            src/ports/SkFontMgr_mac_ct_factory.cpp
            src/sfnt/SkOTTable_name.cpp
            src/sfnt/SkOTUtils.cpp
            src/ports/SkScalerContext_mac_ct.cpp
            src/ports/SkTypeface_mac_ct.cpp
            src/ports/SkOSFile_posix.cpp
            capi/sk_typeface_mac.cpp
            src/utils/mac/SkCTFont.cpp
    )
elseif (UNIX)
    list(APPEND SOURCE_FILES
            src/ports/SkFontMgr_empty_factory.cpp
            src/ports/SkOSFile_posix.cpp
    )
endif()

add_library(reskia SHARED ${SOURCE_FILES})
if(APPLE AND RESKIA_ENABLE_GPU_METAL)
    set(_reskia_gpu_mtl_sources "")
    foreach(_reskia_src IN LISTS SOURCE_FILES)
        if(_reskia_src MATCHES "^src/gpu/.+\\.mm$")
            list(APPEND _reskia_gpu_mtl_sources "${PROJECT_SOURCE_DIR}/${_reskia_src}")
        endif()
    endforeach()
    if(_reskia_gpu_mtl_sources)
        set_source_files_properties(${_reskia_gpu_mtl_sources}
                PROPERTIES COMPILE_OPTIONS "-fno-objc-arc")
    endif()
endif()
target_compile_features(reskia PRIVATE cxx_std_17)
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
if(RESKIA_ENABLE_SKOTTIE OR RESKIA_ENABLE_SKPARAGRAPH)
    target_include_directories(reskia PRIVATE "${RESKIA_ROOT_DIR}/svg")
endif()
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
        message(WARNING "RESKIA_ENABLE_AVIF=ON ですが src/codec/SkAvifCodec.cpp が SOURCE_FILES に未登録のため decoder マクロは未定義です。")
    endif()
endif()
if(RESKIA_ENABLE_JPEGXL)
    if("src/codec/SkJpegxlCodec.cpp" IN_LIST SOURCE_FILES)
        target_compile_definitions(reskia PRIVATE SK_CODEC_DECODES_JPEGXL)
    else()
        message(WARNING "RESKIA_ENABLE_JPEGXL=ON ですが src/codec/SkJpegxlCodec.cpp が SOURCE_FILES に未登録のため decoder マクロは未定義です。")
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
        message(WARNING "RESKIA_ENABLE_RAW=ON ですが src/codec/SkRawCodec.cpp が SOURCE_FILES に未登録のため decoder マクロは未定義です。")
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
        message(WARNING "RESKIA_ENABLE_GIF=ON ですが src/codec/SkWuffsCodec.cpp が SOURCE_FILES に未登録のため decoder マクロは未定義です。")
    endif()
endif()
if(RESKIA_ENABLE_PDF)
    if("src/pdf/SkPDFDocument.cpp" IN_LIST SOURCE_FILES)
        target_compile_definitions(reskia PRIVATE SK_SUPPORT_PDF)
    else()
        message(WARNING "RESKIA_ENABLE_PDF=ON ですが src/pdf/SkPDFDocument.cpp が SOURCE_FILES に未登録のため PDF マクロは未定義です。")
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
