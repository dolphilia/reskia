cmake_minimum_required(VERSION 3.26.4)
project(skpath LANGUAGES CXX)

add_library(skpath_skcms
    skcms.cc
)
target_compile_features(skpath_skcms PUBLIC cxx_std_17)
target_include_directories(skpath_skcms PRIVATE
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/../skcms"
)
add_library(skpath::skcms ALIAS skpath_skcms)
if(NOT TARGET skcms)
    add_library(skcms ALIAS skpath_skcms)
endif()

set(SKPATH_SKCMS_TRANSFORM_DIR "${PROJECT_SOURCE_DIR}/src")
if(NOT EXISTS "${SKPATH_SKCMS_TRANSFORM_DIR}/skcms_TransformBaseline.cc")
    set(SKPATH_SKCMS_TRANSFORM_DIR "${PROJECT_SOURCE_DIR}/../skcms/src")
endif()

target_sources(skpath_skcms PRIVATE
        "${SKPATH_SKCMS_TRANSFORM_DIR}/skcms_TransformBaseline.cc"
        "${SKPATH_SKCMS_TRANSFORM_DIR}/skcms_TransformHsw.cc"
        "${SKPATH_SKCMS_TRANSFORM_DIR}/skcms_TransformSkx.cc"
)

# set_target_properties(raia_primitive PROPERTIES PREFIX "")
