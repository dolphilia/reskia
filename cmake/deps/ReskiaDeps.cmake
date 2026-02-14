include_guard(GLOBAL)

set(RESKIA_DEPS_MODE "prebuilt" CACHE STRING "Dependency mode: prebuilt, source, or system")
set_property(CACHE RESKIA_DEPS_MODE PROPERTY STRINGS prebuilt source system)
option(RESKIA_ENABLE_AVIF "Link AVIF dependency if available" OFF)

set(RESKIA_THIRD_PARTY_PREFIX "" CACHE PATH "Install prefix used when RESKIA_DEPS_MODE=source")

function(_reskia_find_required_library out_var mode root_dir)
    set(one_value_args)
    set(multi_value_args NAMES)
    cmake_parse_arguments(R "" "" "NAMES" ${ARGN})

    if(mode STREQUAL "source")
        find_library(${out_var}
                NAMES ${R_NAMES}
                PATHS
                "${RESKIA_THIRD_PARTY_PREFIX}"
                "${root_dir}/third_party/install"
                PATH_SUFFIXES lib lib64
                NO_DEFAULT_PATH
        )
    else()
        find_library(${out_var}
                NAMES ${R_NAMES}
                PATHS
                "${RESKIA_THIRD_PARTY_PREFIX}"
                "${root_dir}/third_party/install"
                PATH_SUFFIXES lib lib64
        )
    endif()

    if(NOT ${out_var})
        message(FATAL_ERROR "Required library not found: ${R_NAMES} (RESKIA_DEPS_MODE=${mode})")
    endif()
    set(${out_var} "${${out_var}}" PARENT_SCOPE)
endfunction()

function(reskia_resolve_third_party root_dir out_link_dirs out_link_libs)
    string(TOLOWER "${RESKIA_DEPS_MODE}" _mode)

    if(NOT (_mode STREQUAL "prebuilt" OR _mode STREQUAL "source" OR _mode STREQUAL "system"))
        message(FATAL_ERROR "Invalid RESKIA_DEPS_MODE=${RESKIA_DEPS_MODE}. Use prebuilt/source/system.")
    endif()

    if(RESKIA_THIRD_PARTY_PREFIX STREQUAL "")
        set(RESKIA_THIRD_PARTY_PREFIX "${root_dir}/third_party/install")
    endif()

    set(_link_dirs "")
    set(_libs "")

    if(_mode STREQUAL "prebuilt")
        set(_link_dirs "${root_dir}/skia/lib")
        if(WIN32)
            set(_libs zlib libpng turbojpeg-static libwebp libwebpdemux libwebpmux)
            if(RESKIA_ENABLE_AVIF)
                list(APPEND _libs avif)
            endif()
        elseif(APPLE)
            set(_libs expat png png16 jpeg webp webpdecoder webpdemux webpmux)
            if(RESKIA_ENABLE_AVIF)
                list(APPEND _libs avif)
            endif()
        elseif(UNIX)
            set(_libs "")
        endif()
    else()
        if(APPLE)
            if(_mode STREQUAL "source")
                _reskia_find_required_library(_lib_expat "${_mode}" "${root_dir}" NAMES expat libexpat)
                _reskia_find_required_library(_lib_png "${_mode}" "${root_dir}" NAMES png png16 libpng libpng16)
                _reskia_find_required_library(_lib_jpeg "${_mode}" "${root_dir}" NAMES jpeg libjpeg turbojpeg)

                list(APPEND _libs
                        "${_lib_expat}"
                        "${_lib_png}"
                        "${_lib_jpeg}"
                )
            else()
                find_package(EXPAT REQUIRED)
                find_package(PNG REQUIRED)
                find_package(JPEG REQUIRED)
                list(APPEND _libs EXPAT::EXPAT PNG::PNG JPEG::JPEG)
            endif()

            _reskia_find_required_library(_lib_webp "${_mode}" "${root_dir}" NAMES webp libwebp)
            _reskia_find_required_library(_lib_webpdecoder "${_mode}" "${root_dir}" NAMES webpdecoder libwebpdecoder)
            _reskia_find_required_library(_lib_webpdemux "${_mode}" "${root_dir}" NAMES webpdemux libwebpdemux)
            _reskia_find_required_library(_lib_webpmux "${_mode}" "${root_dir}" NAMES webpmux libwebpmux)

            if(RESKIA_ENABLE_AVIF)
                _reskia_find_required_library(_lib_avif "${_mode}" "${root_dir}" NAMES avif)
                list(APPEND _libs "${_lib_avif}")
            endif()

            list(APPEND _libs
                    "${_lib_webp}"
                    "${_lib_webpdecoder}"
                    "${_lib_webpdemux}"
                    "${_lib_webpmux}"
            )
        elseif(WIN32)
            if(_mode STREQUAL "source")
                message(FATAL_ERROR "RESKIA_DEPS_MODE=source on WIN32 is not implemented yet.")
            else()
                # Keep compatibility by using the same names as prebuilt.
                set(_link_dirs "${root_dir}/skia/lib")
                set(_libs zlib libpng turbojpeg-static avif libwebp libwebpdemux libwebpmux)
            endif()
        elseif(UNIX)
            # Current UNIX path in skia links only skcms.
            set(_libs "")
        endif()
    endif()

    message(STATUS "Reskia dependency mode: ${_mode}")
    if(_link_dirs)
        message(STATUS "Reskia dependency link dirs: ${_link_dirs}")
    endif()

    set(${out_link_dirs} "${_link_dirs}" PARENT_SCOPE)
    set(${out_link_libs} "${_libs}" PARENT_SCOPE)
endfunction()
