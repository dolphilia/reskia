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

function(_reskia_resolve_mode_prebuilt root_dir out_link_dirs out_link_libs)
    # mode=prebuilt
    # | Platform | Link Dirs       | Libraries                              |
    # |----------|-----------------|----------------------------------------|
    # | WIN32    | <root>/skia/lib | zlib, libpng, turbojpeg-static, webp* |
    # | APPLE    | <root>/skia/lib | expat, png/jpeg, webp*                 |
    # | UNIX     | <root>/skia/lib | (none)                                 |
    set(_link_dirs "${root_dir}/skia/lib")
    set(_libs "")

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

    set(${out_link_dirs} "${_link_dirs}" PARENT_SCOPE)
    set(${out_link_libs} "${_libs}" PARENT_SCOPE)
endfunction()

function(_reskia_resolve_mode_source root_dir out_link_dirs out_link_libs)
    # mode=source
    # | Platform | Link Dirs | Libraries                                     |
    # |----------|-----------|-----------------------------------------------|
    # | WIN32    | (none)    | 未実装 (FATAL_ERROR)                          |
    # | APPLE    | (none)    | third_party/install から find_library で解決 |
    # | UNIX     | (none)    | (none)                                        |
    set(_link_dirs "")
    set(_libs "")

    if(APPLE)
        _reskia_find_required_library(_lib_expat "source" "${root_dir}" NAMES expat libexpat)
        _reskia_find_required_library(_lib_png "source" "${root_dir}" NAMES png png16 libpng libpng16)
        _reskia_find_required_library(_lib_jpeg "source" "${root_dir}" NAMES jpeg libjpeg turbojpeg)

        list(APPEND _libs
                "${_lib_expat}"
                "${_lib_png}"
                "${_lib_jpeg}"
        )

        _reskia_find_required_library(_lib_webp "source" "${root_dir}" NAMES webp libwebp)
        _reskia_find_required_library(_lib_webpdecoder "source" "${root_dir}" NAMES webpdecoder libwebpdecoder)
        _reskia_find_required_library(_lib_webpdemux "source" "${root_dir}" NAMES webpdemux libwebpdemux)
        _reskia_find_required_library(_lib_webpmux "source" "${root_dir}" NAMES webpmux libwebpmux)

        if(RESKIA_ENABLE_AVIF)
            _reskia_find_required_library(_lib_avif "source" "${root_dir}" NAMES avif)
            list(APPEND _libs "${_lib_avif}")
        endif()

        list(APPEND _libs
                "${_lib_webp}"
                "${_lib_webpdecoder}"
                "${_lib_webpdemux}"
                "${_lib_webpmux}"
        )
    elseif(WIN32)
        message(FATAL_ERROR "RESKIA_DEPS_MODE=source on WIN32 is not implemented yet.")
    elseif(UNIX)
        # Current UNIX path in skia links only skcms.
        set(_libs "")
    endif()

    set(${out_link_dirs} "${_link_dirs}" PARENT_SCOPE)
    set(${out_link_libs} "${_libs}" PARENT_SCOPE)
endfunction()

function(_reskia_resolve_mode_system root_dir out_link_dirs out_link_libs)
    # mode=system
    # | Platform | Link Dirs       | Libraries                                         |
    # |----------|-----------------|---------------------------------------------------|
    # | WIN32    | <root>/skia/lib | prebuilt 互換名 (zlib, libpng, turbojpeg-static) |
    # | APPLE    | (none)          | EXPAT/PNG/JPEG: find_package + webp*: find_library |
    # | UNIX     | (none)          | (none)                                            |
    set(_link_dirs "")
    set(_libs "")

    if(APPLE)
        find_package(EXPAT REQUIRED)
        find_package(PNG REQUIRED)
        find_package(JPEG REQUIRED)
        list(APPEND _libs EXPAT::EXPAT PNG::PNG JPEG::JPEG)

        _reskia_find_required_library(_lib_webp "system" "${root_dir}" NAMES webp libwebp)
        _reskia_find_required_library(_lib_webpdecoder "system" "${root_dir}" NAMES webpdecoder libwebpdecoder)
        _reskia_find_required_library(_lib_webpdemux "system" "${root_dir}" NAMES webpdemux libwebpdemux)
        _reskia_find_required_library(_lib_webpmux "system" "${root_dir}" NAMES webpmux libwebpmux)

        if(RESKIA_ENABLE_AVIF)
            _reskia_find_required_library(_lib_avif "system" "${root_dir}" NAMES avif)
            list(APPEND _libs "${_lib_avif}")
        endif()

        list(APPEND _libs
                "${_lib_webp}"
                "${_lib_webpdecoder}"
                "${_lib_webpdemux}"
                "${_lib_webpmux}"
        )
    elseif(WIN32)
        # 互換維持: prebuilt と同名ライブラリ指定を許容（削除期限: 2026-06-30）。
        # 期限までに imported target ベースへ移行する。
        set(_link_dirs "${root_dir}/skia/lib")
        set(_libs zlib libpng turbojpeg-static avif libwebp libwebpdemux libwebpmux)
    elseif(UNIX)
        # Current UNIX path in skia links only skcms.
        set(_libs "")
    endif()

    set(${out_link_dirs} "${_link_dirs}" PARENT_SCOPE)
    set(${out_link_libs} "${_libs}" PARENT_SCOPE)
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
        _reskia_resolve_mode_prebuilt("${root_dir}" _link_dirs _libs)
    elseif(_mode STREQUAL "source")
        _reskia_resolve_mode_source("${root_dir}" _link_dirs _libs)
    elseif(_mode STREQUAL "system")
        _reskia_resolve_mode_system("${root_dir}" _link_dirs _libs)
    endif()

    message(STATUS "Reskia dependency mode: ${_mode}")
    if(_link_dirs)
        message(STATUS "Reskia dependency link dirs: ${_link_dirs}")
    endif()

    set(${out_link_dirs} "${_link_dirs}" PARENT_SCOPE)
    set(${out_link_libs} "${_libs}" PARENT_SCOPE)
endfunction()
