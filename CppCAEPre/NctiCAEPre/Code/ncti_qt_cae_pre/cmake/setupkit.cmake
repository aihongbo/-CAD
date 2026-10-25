cmake_minimum_required(VERSION 3.24)

set(SETUP_KIT_DIR ${CMAKE_CURRENT_LIST_DIR})

function(get_version_from_ini VERSION_FILE OUTPUT_VARIABLE)
    if(NOT EXISTS ${VERSION_FILE})
        message(WARNING "未找到 ${VERSION_FILE} 文件，使用默认版本号 0.0.0.0")
        set(${OUTPUT_VARIABLE} "0.0.0.0" PARENT_SCOPE)
        return()
    endif()

    file(STRINGS ${VERSION_FILE} VERSION_CONTENT)

    set(IN_INFO_SECTION FALSE)
    set(VERSION_NUMBER "")

    foreach(LINE IN LISTS VERSION_CONTENT)
        if(LINE MATCHES "^\\[info\\]$")
            set(IN_INFO_SECTION TRUE)
        elseif(LINE MATCHES "^\\[.*\\]$")
            set(IN_INFO_SECTION FALSE)
        elseif(IN_INFO_SECTION AND LINE MATCHES "^version[ \t]*=[ \t]*([0-9.]+)$")
            # 提取 version 的值
            string(REGEX REPLACE "^version[ \t]*=[ \t]*([0-9.]+)$" "\\1" VERSION_NUMBER "${LINE}")
            break()
        endif()
    endforeach()

    if(NOT VERSION_NUMBER)
        message(WARNING "未在 [info] 部分找到 version 的值，使用默认版本号 0.0.0.0")
        set(VERSION_NUMBER "0.0.0.0")
    endif()

    set(${OUTPUT_VARIABLE} ${VERSION_NUMBER} PARENT_SCOPE)
endfunction()      


#[[
    Set value if valid, otherwise use default.
    set_value(<key> <maybe_value...> <default>)
]] #
function(set_value _key)
    set(_args "${ARGN}")
    list(POP_BACK _args _default)

    foreach(_item IN LISTS _args)
        if(${_item})
            set(${_key} ${${_item}} PARENT_SCOPE)
            return()
        endif()
    endforeach()

    set(${_key} ${_default} PARENT_SCOPE)
endfunction()

#[[
    Parse version and create seq vars with specified prefix.
    parse_version(<prefix> <version>)
]] #
function(parse_version _prefix _version)
    string(REPLACE "." ";" _version_list ${_version})
    list(LENGTH _version_list _version_count)
    list(PREPEND _version_list 0) # Add placeholder

    foreach(_i RANGE 1 4)
        if(_i LESS_EQUAL _version_count)
            list(GET _version_list ${_i} _item)
        else()
            set(_item 0)
        endif()

        set(${_prefix}_${_i} ${_item} PARENT_SCOPE)
    endforeach()
endfunction()

#[[
    Get shorter version number.
    crop_version(<VAR> <version> <count>)
]] #
function(crop_version _var _version _count)
    parse_version(FUNC ${_version})

    set(_list)

    foreach(_i RANGE 1 ${_count})
        list(APPEND _list ${FUNC_${_i}})
    endforeach()

    string(JOIN "." _short_version ${_list})
    set(${_var} ${_short_version} PARENT_SCOPE)
endfunction()

#[[
    Attach windows RC file to a target.
    add_win_rc(<target>
        [NAME                name]
        [VERSION           version]
        [DESCRIPTION    desc]
        [COPYRIGHT       copyright]
        [ICON                  ico]
        [OUTPUT_DIR     dir]
    )
]] #

function(add_win_rc _target)
    if(NOT WIN32)
        return()
    endif()

    _check_target_type_helper(${_target} _ "EXECUTABLE" "SHARED_LIBRARY")

    set(options)
    set(oneValueArgs NAME VERSION DESCRIPTION COPYRIGHT ICON OUTPUT_DIR)
    set(multiValueArgs)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set_value(_name FUNC_NAME ${_target})
    set_value(_version FUNC_VERSION PROJECT_VERSION "0.0.0.0")
    set_value(_desc FUNC_DESCRIPTION PROJECT_DESCRIPTION ${_name})
    set_value(_copyright FUNC_COPYRIGHT ${_name})

    parse_version(_ver ${_version})
    set(RC_VERSION ${_ver_1},${_ver_2},${_ver_3},${_ver_4})

    set(RC_APPLICATION_NAME ${_name})
    set(RC_VERSION_STRING ${_version})
    set(RC_DESCRIPTION ${_desc})
    set(RC_COPYRIGHT ${_copyright})

    if(NOT FUNC_ICON)
        set(RC_ICON_COMMENT "//")
        set(RC_ICON_PATH)
    else()
        get_filename_component(RC_ICON_PATH ${FUNC_ICON} ABSOLUTE)
    endif()

    set_value(_out_dir OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
    set(_out_path "${_out_dir}/${_target}_res.rc")
    configure_file("${SETUP_KIT_DIR}/windows/WinResource.rc.in" ${_out_path} @ONLY)
    target_sources(${_target} PRIVATE ${_out_path})

    if(FUNC_ICON)
        if(${FUNC_ICON} IS_NEWER_THAN ${_out_path})
            file(TOUCH_NOCREATE ${_out_path})
        endif()
    endif()
endfunction()

#[[
    Attach windows manifest file to a target.

    add_win_manifest(<target>
        [NAME                name]
        [VERSION           version]
        [DESCRIPTION    desc]
        [OUTPUT_DIR     dir]
        [UTF8]
        [ADMIN]
    )
]] #

function(add_win_manifest _target)
    if(NOT WIN32)
        return()
    endif()

    _check_target_type_helper(${_target} _ "EXECUTABLE")

    set(options UTF8 ADMIN)
    set(oneValueArgs NAME VERSION DESCRIPTION OUTPUT_DIR)
    set(multiValueArgs)
    cmake_parse_arguments(FUNC "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set_value(_name FUNC_NAME ${_target})
    set_value(_version FUNC_VERSION PROJECT_VERSION "0.0.0.0")
    set_value(_desc FUNC_DESCRIPTION PROJECT_DESCRIPTION ${_name})

    crop_version(_version ${_version} 4)

    set(MANIFEST_IDENTIFIER ${_name})
    set(MANIFEST_VERSION ${_version})
    set(MANIFEST_DESCRIPTION ${_desc})

    set(MANIFEST_UTF8)

    if(FUNC_UTF8)
        set(MANIFEST_UTF8 "<activeCodePage xmlns=\"http://schemas.microsoft.com/SMI/2019/WindowsSettings\">UTF-8</activeCodePage>")
    endif()

    if(FUNC_ADMIN)
        set(MANIFEST_PRIVILEGES "<requestedExecutionLevel level=\"requireAdministrator\" uiAccess=\"false\" />")
    else()
        set(MANIFEST_PRIVILEGES "<requestedExecutionLevel level=\"asInvoker\" uiAccess=\"false\" />")
    endif()

    set_value(_out_dir OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
    set(_out_path "${_out_dir}/${_target}_manifest.exe.manifest")
    configure_file("${SETUP_KIT_DIR}/windows/WinManifest.manifest.in" ${_out_path} @ONLY)

    # https://cmake.org/cmake/help/latest/release/3.4.html#other
    # CMake learned to honor *.manifest source files with MSVC tools. Manifest files named as sources
    # of .exe and .dll targets will be merged with linker-generated manifests and embedded in the binary.
    # NOTE: CMake will automatically generate a default manifest file and embed it into the binary file
    # when we are using MSVC toolchain, so it will conflict with the one we embed in the RC file. So in
    # this case, we just follow the CMake documentation, add the manifest file into the sources and let
    # CMake handle it. What's more, CMake can automatically merge all manifest files so we can actually
    # add multiple manifest files, eg. each manifest file contains a separate section.
    if(MSVC)
        target_sources(${_target} PRIVATE ${_out_path})
    else()
        # For non-MSVC toolchains we can only embed the manifest file into the RC file, sadly we have
        # to merge all manifest files into one by ourself if we have multiple of them, but luckily
        # CMake won't embed a default one so we don't need to worry about resource conflicts.
        set(_manifest_rc ${_out_path}.rc)
        file(WRITE ${_manifest_rc} "#include <windows.h>\n\n1 RT_MANIFEST \"${_out_path}\"")
        target_sources(${_target} PRIVATE ${_manifest_rc})
    endif()
endfunction()

# ----------------------------------
# Private functions
# ----------------------------------
macro(_check_target_type_helper _target _type)
    set(_tmp_target_type_list ${ARGN})
    get_target_property(_tmp_target_type ${_target} TYPE)

    if(NOT "${_tmp_target_type}" IN_LIST _tmp_target_type_list)
        return()
    endif()

    set(${_type} ${_tmp_target_type})
    unset(_tmp_target_type)
    unset(_tmp_target_type_list)
endmacro()