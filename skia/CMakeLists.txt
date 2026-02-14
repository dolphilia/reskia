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

set(SOURCE_FILES reskia.cpp)

include("${RESKIA_ROOT_DIR}/cmake/reskia/sources-core.cmake")
include("${RESKIA_ROOT_DIR}/cmake/reskia/sources-binding.cmake")
include("${RESKIA_ROOT_DIR}/cmake/reskia/sources-static.cmake")

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
            #src/utils/win/SkWGL_win.cpp
    )
elseif (APPLE)
    list(APPEND SOURCE_FILES
            src/ports/SkFontMgr_mac_ct.cpp
            src/ports/SkFontMgr_mac_ct_factory.cpp
            #src/ports/SkFontMgr_empty_factory.cpp
            src/sfnt/SkOTTable_name.cpp
            src/sfnt/SkOTUtils.cpp
            src/ports/SkScalerContext_mac_ct.cpp
            src/ports/SkTypeface_mac_ct.cpp
            src/ports/SkOSFile_posix.cpp
            binding/sk_typeface_mac.cpp
            src/utils/mac/SkCTFont.cpp
    )
elseif (UNIX)
    list(APPEND SOURCE_FILES
            src/ports/SkFontMgr_empty_factory.cpp
            src/ports/SkOSFile_posix.cpp
    )
endif()

add_library(reskia SHARED ${SOURCE_FILES})
target_compile_features(reskia PRIVATE cxx_std_17)
target_include_directories(reskia
    PRIVATE
        "${PROJECT_SOURCE_DIR}"
        "${PROJECT_SOURCE_DIR}/_include"
)
if(RESKIA_DEP_LINK_DIRS)
    target_link_directories(reskia PRIVATE ${RESKIA_DEP_LINK_DIRS})
endif()
target_compile_definitions(reskia PRIVATE SK_ENABLE_OPTIMIZE_SIZE)

if(WIN32)
    target_link_libraries(reskia skcms ${RESKIA_DEP_LIBS})
elseif(APPLE)
    target_link_libraries(reskia skcms skresources svg ${RESKIA_DEP_LIBS} "-framework Cocoa" "-framework CoreFoundation" "-framework CoreText")
elseif(UNIX)
    target_link_libraries(reskia skcms ${RESKIA_DEP_LIBS})
endif()

if(WIN32)
    set_target_properties(reskia PROPERTIES PREFIX "lib")
endif()

# TEST
include("${RESKIA_ROOT_DIR}/cmake/reskia/tests.cmake")
