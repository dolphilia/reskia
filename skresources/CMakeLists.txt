#
# 新しいCmakeを使うように
# OpenMPに対応したGCCを使うように
#

cmake_minimum_required(VERSION 3.26.4)
project(skresources)
#set(CMAKE_C_COMPILER "gcc")

include_directories(${PROJECT_SOURCE_DIR}/../skia/)
link_directories(${PROJECT_SOURCE_DIR}/)
#include(${PROJECT_SOURCE_DIR}/src)

set(CMAKE_CXX_STANDARD 17)

#find_package(OpenMP REQUIRED)
#
#if(NOT OpenMP_C_FOUND)
#    message(FATAL_ERROR "OpenMP not found")
#endif()

# CUDAアーキテクチャをターゲットにする場合のフラグを設定
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp-targets=nvptx64-nvidia-cuda")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")
#add_compile_options(-fopenmp)

add_library(skresources
    src/SkResources.cpp
)

# set_target_properties(raia_primitive PROPERTIES PREFIX "")