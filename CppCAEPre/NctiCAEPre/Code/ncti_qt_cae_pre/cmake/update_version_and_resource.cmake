cmake_minimum_required(VERSION 3.24)

function(update_version VERSION_FILE OUTPUT_VARIABLE)
    set(DEFAULT_VERSION "1.0.0.0")

    # 检查版本文件是否存在
    if(NOT EXISTS ${VERSION_FILE})
        message(WARNING "Version file ${VERSION_FILE} not found. Using default version: ${DEFAULT_VERSION}")
        set(${OUTPUT_VARIABLE} ${DEFAULT_VERSION} PARENT_SCOPE)
        return()
    endif()

    file(STRINGS ${VERSION_FILE} VERSION_LINES)

    set(IN_INFO_SECTION FALSE)
    set(OLD_VERSION "")

    foreach(LINE IN LISTS VERSION_LINES)
        string(STRIP "${LINE}" STRIPPED_LINE)

        if(STRIPPED_LINE MATCHES "^\\[info\\]$")
            set(IN_INFO_SECTION TRUE)
            continue()  # 跳过当前行，后续处理段内内容
        endif()

        if(STRIPPED_LINE MATCHES "^\\[.*\\]$" AND IN_INFO_SECTION)
            set(IN_INFO_SECTION FALSE)
            continue()
        endif()

        # 在 [info] 段内提取 version 字段
        if(IN_INFO_SECTION AND STRIPPED_LINE MATCHES "^version[ \t]*=[ \t]*(.+)$")
            string(REGEX REPLACE "^version[ \t]*=[ \t]*(.+)$" "\\1" OLD_VERSION "${STRIPPED_LINE}")
            break()
        endif()
    endforeach()

    if(NOT OLD_VERSION)
        message(WARNING "Failed to find 'version' in [info] section of ${VERSION_FILE}. Using default version: ${DEFAULT_VERSION}")
        set(${OUTPUT_VARIABLE} ${DEFAULT_VERSION} PARENT_SCOPE)
        return()
    endif()

    # 验证版本号格式
    if(NOT OLD_VERSION MATCHES "^[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+$")
        message(WARNING "Invalid version number format in ${VERSION_FILE}. Using default version: ${DEFAULT_VERSION}")
        set(${OUTPUT_VARIABLE} ${DEFAULT_VERSION} PARENT_SCOPE)
        return()
    endif()

    # 将版本号拆分为各个部分
    string(REPLACE "." ";" VERSION_PARTS ${OLD_VERSION})
    list(GET VERSION_PARTS 0 MAJOR)
    list(GET VERSION_PARTS 1 MINOR)
    list(GET VERSION_PARTS 2 PATCH)
    list(GET VERSION_PARTS 3 BUILD)

    # 增加构建号
    math(EXPR NEW_BUILD "${BUILD} + 1")

    # 构建新的版本号
    set(NEW_VERSION "${MAJOR}.${MINOR}.${PATCH}.${NEW_BUILD}")

    # 替换文件中的旧版本号为新版本号
    set(NEW_VERSION_CONTENT "")

    foreach(LINE IN LISTS VERSION_LINES)
        string(STRIP "${LINE}" STRIPPED_LINE)
        
        if(STRIPPED_LINE MATCHES "^version[ \t]*=[ \t]*.*$" AND IN_INFO_SECTION)
            # 构建新的版本行，保留原始行的空格格式
            string(REGEX REPLACE "(^version[ \t]*=[ \t]*).*$" "\\1${NEW_VERSION}" UPDATED_LINE "${LINE}")
            list(APPEND NEW_VERSION_CONTENT "${UPDATED_LINE}\n")
        else()
            list(APPEND NEW_VERSION_CONTENT "${LINE}\n")
        endif()
    endforeach()

    # 将新内容写回 version.ini 文件
    if(NEW_VERSION_CONTENT)
        file(WRITE ${VERSION_FILE} "")
        foreach(LINE IN LISTS NEW_VERSION_CONTENT)
            file(APPEND ${VERSION_FILE} "${LINE}")
        endforeach()
    endif()

    # 验证写入操作是否成功
    if(NOT EXISTS ${VERSION_FILE})
        message(WARNING "Failed to write new version to ${VERSION_FILE}. Using default version: ${DEFAULT_VERSION}")
        set(${OUTPUT_VARIABLE} ${DEFAULT_VERSION} PARENT_SCOPE)
        return()
    endif()

    set(${OUTPUT_VARIABLE} ${NEW_VERSION} PARENT_SCOPE)
    message(STATUS "Version updated from ${OLD_VERSION} to ${NEW_VERSION}")
endfunction()

# 获取版本文件路径
set(VERSION_FILE "${VERSION_DIR}/version.ini")

# 更新版本号
update_version(${VERSION_FILE} NEW_VERSION)

# 设置资源文件变量
set(_rc_path "${WINRESOURCE_DIR}/${NCTI_PROJECT}_res.rc")

if(NOT EXISTS ${_rc_path})
    message(STATUS "Resource file ${_rc_path} not found. Skipping version update.")
    return()
endif()

# 读取现有资源文件内容
file(READ ${_rc_path} RESOURCE_CONTENT)

# 替换 FILEVERSION 和 PRODUCTVERSION 的值
string(REGEX REPLACE "FILEVERSION[ \t]+[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+" 
	"FILEVERSION ${NEW_VERSION}" 
	RESOURCE_CONTENT "${RESOURCE_CONTENT}")
string(REGEX REPLACE "PRODUCTVERSION[ \t]+[0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+" 
	"PRODUCTVERSION ${NEW_VERSION}" 
	RESOURCE_CONTENT "${RESOURCE_CONTENT}")

# 替换 StringFileInfo 中的 FileVersion 和 ProductVersion
string(REGEX REPLACE "(VALUE \"FileVersion\", \")[^\" ]+\"" 
	"\\1${NEW_VERSION}\"" 
	RESOURCE_CONTENT "${RESOURCE_CONTENT}")
string(REGEX REPLACE "(VALUE \"ProductVersion\", \")[^\" ]+\"" 
	"\\1${NEW_VERSION}\"" 
	RESOURCE_CONTENT "${RESOURCE_CONTENT}")

# 写回更新后的资源文件
file(WRITE ${_rc_path} "${RESOURCE_CONTENT}")

message(STATUS "${_rc_path} updated with new version: ${NEW_VERSION}")