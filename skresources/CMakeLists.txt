cmake_minimum_required(VERSION 3.26.4)
project(skresources LANGUAGES CXX)

add_library(skresources
    src/SkResources.cpp
)
target_compile_features(skresources PUBLIC cxx_std_17)
target_include_directories(skresources PRIVATE
    "${PROJECT_SOURCE_DIR}/../skia"
)

# set_target_properties(raia_primitive PROPERTIES PREFIX "")
