cmake_minimum_required(VERSION 3.26.4)
project(skcms LANGUAGES CXX)

add_library(skcms
    skcms.cc
        src/skcms_TransformBaseline.cc
        src/skcms_TransformHsw.cc
        src/skcms_TransformSkx.cc
)
target_compile_features(skcms PUBLIC cxx_std_17)
target_include_directories(skcms PRIVATE
    "${PROJECT_SOURCE_DIR}"
)

# set_target_properties(raia_primitive PROPERTIES PREFIX "")
