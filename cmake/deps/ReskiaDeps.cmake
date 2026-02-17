include_guard(GLOBAL)

set(RESKIA_DEPS_MODE "prebuilt" CACHE STRING "Dependency mode: prebuilt, source, or system")
set_property(CACHE RESKIA_DEPS_MODE PROPERTY STRINGS prebuilt source system)
option(RESKIA_ENABLE_AVIF "Link AVIF dependency if available" OFF)
option(RESKIA_ENABLE_JPEGXL "Link JPEGXL dependency if available" OFF)
option(RESKIA_ENABLE_RAW "Enable RAW codec integration (requires dng_sdk/piex sources)" OFF)
option(RESKIA_ENABLE_GIF "Enable GIF codec integration (requires Wuffs source)" OFF)
option(RESKIA_ENABLE_JPEG_ENCODER "Enable JPEG encoder integration" OFF)
option(RESKIA_ENABLE_WEBP_ENCODER "Enable WebP encoder integration" OFF)
option(RESKIA_ENABLE_PDF "Enable PDF backend integration" OFF)
option(RESKIA_ENABLE_SKSG "Enable sksg (Scene Graph) integration" OFF)
option(RESKIA_ENABLE_SKOTTIE "Enable skottie (Lottie) integration" OFF)
option(RESKIA_ENABLE_SKPARAGRAPH "Enable skparagraph integration" OFF)
option(RESKIA_ENABLE_JPEG_GAINMAP "Enable JPEG gainmap metadata decode path" OFF)
option(RESKIA_ENABLE_FONTCONFIG_CAPI "Enable FontConfig-specific C API bridge (requires upstream fontconfig port source)" OFF)
option(RESKIA_ENABLE_GPU_GANESH "Enable Skia Ganesh GPU backend integration" OFF)
option(RESKIA_ENABLE_GPU_GRAPHITE "Enable Skia Graphite GPU backend integration" OFF)
option(RESKIA_ENABLE_GPU_VULKAN "Enable Vulkan GPU backend integration" OFF)
option(RESKIA_ENABLE_GPU_METAL "Enable Metal GPU backend integration" OFF)
option(RESKIA_ENABLE_GPU_DAWN "Enable Dawn GPU backend integration (experimental)" OFF)

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
    # | Platform | Link Dirs | Libraries                                      |
    # |----------|-----------|------------------------------------------------|
    # | WIN32    | (none)    | third_party/install から find_library で解決 |
    # | APPLE    | (none)    | third_party/install から find_library で解決 |
    # | UNIX     | (none)    | third_party/install から find_library で解決 |
    set(_link_dirs "")
    set(_libs "")

    if(WIN32)
        _reskia_find_required_library(_lib_zlib "prebuilt" "${root_dir}" NAMES z zlib zlibstatic)
        _reskia_find_required_library(_lib_png "prebuilt" "${root_dir}" NAMES png png16 png18 libpng libpng16 libpng18)
        _reskia_find_required_library(_lib_jpeg "prebuilt" "${root_dir}" NAMES jpeg libjpeg turbojpeg turbojpeg-static)
        _reskia_find_required_library(_lib_webp "prebuilt" "${root_dir}" NAMES webp libwebp)
        _reskia_find_required_library(_lib_webpdemux "prebuilt" "${root_dir}" NAMES webpdemux libwebpdemux)
        _reskia_find_required_library(_lib_webpmux "prebuilt" "${root_dir}" NAMES webpmux libwebpmux)
        list(APPEND _libs
                "${_lib_zlib}"
                "${_lib_png}"
                "${_lib_jpeg}"
                "${_lib_webp}"
                "${_lib_webpdemux}"
                "${_lib_webpmux}"
        )
        if(RESKIA_ENABLE_AVIF)
            _reskia_find_required_library(_lib_avif "prebuilt" "${root_dir}" NAMES avif libavif)
            list(APPEND _libs "${_lib_avif}")
        endif()
        if(RESKIA_ENABLE_JPEGXL)
            _reskia_find_required_library(_lib_jxl "prebuilt" "${root_dir}" NAMES jxl libjxl)
            _reskia_find_required_library(_lib_jxl_threads "prebuilt" "${root_dir}" NAMES jxl_threads libjxl_threads)
            _reskia_find_required_library(_lib_jxl_cms "prebuilt" "${root_dir}" NAMES jxl_cms libjxl_cms)
            list(APPEND _libs "${_lib_jxl}" "${_lib_jxl_threads}" "${_lib_jxl_cms}")
        endif()
    elseif(APPLE)
        _reskia_find_required_library(_lib_expat "prebuilt" "${root_dir}" NAMES expat libexpat)
        _reskia_find_required_library(_lib_png "prebuilt" "${root_dir}" NAMES png png16 png18 libpng libpng16 libpng18)
        _reskia_find_required_library(_lib_jpeg "prebuilt" "${root_dir}" NAMES jpeg libjpeg turbojpeg)
        _reskia_find_required_library(_lib_webp "prebuilt" "${root_dir}" NAMES webp libwebp)
        _reskia_find_required_library(_lib_webpdecoder "prebuilt" "${root_dir}" NAMES webpdecoder libwebpdecoder)
        _reskia_find_required_library(_lib_webpdemux "prebuilt" "${root_dir}" NAMES webpdemux libwebpdemux)
        _reskia_find_required_library(_lib_webpmux "prebuilt" "${root_dir}" NAMES webpmux libwebpmux)
        list(APPEND _libs
                "${_lib_expat}"
                "${_lib_png}"
                "${_lib_jpeg}"
                "${_lib_webp}"
                "${_lib_webpdecoder}"
                "${_lib_webpdemux}"
                "${_lib_webpmux}"
        )
        if(RESKIA_ENABLE_RAW OR RESKIA_ENABLE_PDF)
            _reskia_find_required_library(_lib_zlib "prebuilt" "${root_dir}" NAMES z zlib)
            list(APPEND _libs "${_lib_zlib}")
        endif()
        if(RESKIA_ENABLE_AVIF)
            _reskia_find_required_library(_lib_avif "prebuilt" "${root_dir}" NAMES avif libavif)
            list(APPEND _libs "${_lib_avif}")
        endif()
        if(RESKIA_ENABLE_JPEGXL)
            _reskia_find_required_library(_lib_jxl "prebuilt" "${root_dir}" NAMES jxl libjxl)
            _reskia_find_required_library(_lib_jxl_threads "prebuilt" "${root_dir}" NAMES jxl_threads libjxl_threads)
            _reskia_find_required_library(_lib_jxl_cms "prebuilt" "${root_dir}" NAMES jxl_cms libjxl_cms)
            list(APPEND _libs "${_lib_jxl}" "${_lib_jxl_threads}" "${_lib_jxl_cms}")
        endif()
    elseif(UNIX)
        if(RESKIA_ENABLE_PDF)
            _reskia_find_required_library(_lib_zlib "prebuilt" "${root_dir}" NAMES z zlib)
            set(_libs "${_lib_zlib}")
        else()
            set(_libs "")
        endif()
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
        _reskia_find_required_library(_lib_sharpyuv "source" "${root_dir}" NAMES sharpyuv libsharpyuv)

        if(RESKIA_ENABLE_AVIF)
            _reskia_find_required_library(_lib_avif "source" "${root_dir}" NAMES avif)
            list(APPEND _libs "${_lib_avif}")
        endif()
        if(RESKIA_ENABLE_RAW OR RESKIA_ENABLE_PDF)
            _reskia_find_required_library(_lib_zlib "source" "${root_dir}" NAMES z zlib)
            list(APPEND _libs "${_lib_zlib}")
        endif()
        if(RESKIA_ENABLE_JPEGXL)
            _reskia_find_required_library(_lib_jxl "source" "${root_dir}" NAMES jxl libjxl)
            _reskia_find_required_library(_lib_jxl_threads "source" "${root_dir}" NAMES jxl_threads libjxl_threads)
            _reskia_find_required_library(_lib_jxl_cms "source" "${root_dir}" NAMES jxl_cms libjxl_cms)
            list(APPEND _libs
                    "${_lib_jxl}"
                    "${_lib_jxl_threads}"
                    "${_lib_jxl_cms}"
            )
        endif()

        list(APPEND _libs
                "${_lib_webp}"
                "${_lib_webpdecoder}"
                "${_lib_webpdemux}"
                "${_lib_webpmux}"
                "${_lib_sharpyuv}"
        )
    elseif(WIN32)
        message(FATAL_ERROR "RESKIA_DEPS_MODE=source on WIN32 is not implemented yet.")
    elseif(UNIX)
        if(RESKIA_ENABLE_PDF)
            _reskia_find_required_library(_lib_zlib "source" "${root_dir}" NAMES z zlib)
            list(APPEND _libs "${_lib_zlib}")
        endif()
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
        if(RESKIA_ENABLE_RAW OR RESKIA_ENABLE_PDF)
            find_package(ZLIB REQUIRED)
            list(APPEND _libs ZLIB::ZLIB)
        endif()

        _reskia_find_required_library(_lib_webp "system" "${root_dir}" NAMES webp libwebp)
        _reskia_find_required_library(_lib_webpdecoder "system" "${root_dir}" NAMES webpdecoder libwebpdecoder)
        _reskia_find_required_library(_lib_webpdemux "system" "${root_dir}" NAMES webpdemux libwebpdemux)
        _reskia_find_required_library(_lib_webpmux "system" "${root_dir}" NAMES webpmux libwebpmux)
        _reskia_find_required_library(_lib_sharpyuv "system" "${root_dir}" NAMES sharpyuv libsharpyuv)

        if(RESKIA_ENABLE_AVIF)
            _reskia_find_required_library(_lib_avif "system" "${root_dir}" NAMES avif)
            list(APPEND _libs "${_lib_avif}")
        endif()
        if(RESKIA_ENABLE_JPEGXL)
            _reskia_find_required_library(_lib_jxl "system" "${root_dir}" NAMES jxl libjxl)
            _reskia_find_required_library(_lib_jxl_threads "system" "${root_dir}" NAMES jxl_threads libjxl_threads)
            _reskia_find_required_library(_lib_jxl_cms "system" "${root_dir}" NAMES jxl_cms libjxl_cms)
            list(APPEND _libs
                    "${_lib_jxl}"
                    "${_lib_jxl_threads}"
                    "${_lib_jxl_cms}"
            )
        endif()

        list(APPEND _libs
                "${_lib_webp}"
                "${_lib_webpdecoder}"
                "${_lib_webpdemux}"
                "${_lib_webpmux}"
                "${_lib_sharpyuv}"
        )
    elseif(WIN32)
        # 互換維持: prebuilt と同名ライブラリ指定を許容（削除期限: 2026-06-30）。
        # 期限までに imported target ベースへ移行する。
        set(_link_dirs "${root_dir}/skia/lib")
        set(_libs zlib libpng turbojpeg-static libwebp libwebpdemux libwebpmux)
        if(RESKIA_ENABLE_AVIF)
            list(APPEND _libs avif)
        endif()
        if(RESKIA_ENABLE_JPEGXL)
            list(APPEND _libs jxl jxl_threads jxl_cms)
        endif()
    elseif(UNIX)
        if(RESKIA_ENABLE_PDF)
            find_package(ZLIB REQUIRED)
            list(APPEND _libs ZLIB::ZLIB)
        endif()
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
