# 指定 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.24)

# 项目配置
project(YHCppSDK-Community
	VERSION 1.0.0
	LANGUAGES CXX
	DESCRIPTION "YHCppSDK Project"    
)

# 自定义的 CMake 函数宏定义
include(cmake/functions.cmake)

# ==============================================================================
# 编译器和语言配置
# ==============================================================================

# 选择编译版本
set(NCTI_SELECT_BUILD_TYPE Debug RelWithDebInfo)
set(NCTI_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Select build type")
set_property(CACHE NCTI_BUILD_TYPE PROPERTY STRINGS "${NCTI_SELECT_BUILD_TYPE}")

#设置 C++ 标准版本为 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # 强制使用指定的 C++ 标准
set(CMAKE_CXX_EXTENSIONS OFF)        # 不使用编译器特定扩展

# 禁用优化
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -Od")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} -Od")

# Windows 平台特定配置
if(WIN32)
    add_definitions(-DNCTI_WIN32 -D_CRT_SECURE_NO_WARNINGS)
endif()

# 全局编译定义
add_definitions(-DNCTI_DLL)

# MSVC 特定配置
if(MSVC)
  # 设置 Microsoft Visual C++ 运行时库类型
  add_compile_options(
    "$<$<CONFIG:Debug>:/MDd>"
    "$<$<CONFIG:Release>:/MD>"
    "$<$<CONFIG:RelWithDebInfo>:/MD>"
  )

  # 设置以 UTF-8 格式编译, 必须位于 add_executable() 之前
  add_compile_options(
    "$<$<C_COMPILER_ID:MSVC>:/utf-8>"
    "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>"
  )

  # 开启并行编译
  add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)
endif()

# ==============================================================================
# Qt库配置
# ==============================================================================
set(NCTI_MIN_QT_VERSION 5.14)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
    set(NCTI_PLATFORM_NAME "x86")
else()
    set(NCTI_PLATFORM_NAME "x64")
endif()

# 获取 Qt 版本和编译器名称
set(QT_VERSION_INFO "Qt${QT_VERSION}_${CMAKE_CXX_COMPILER_ID}_${NCTI_PLATFORM_NAME}")

# ==============================================================================
# 模块和库配置
# ==============================================================================

# 定义项目模块名称
set(NCTI_NCTICAX "NCTICAX")
set(NCTI_OCC "OCC")

# 核心模块名称
set(NCTI "ncti")
set(NCTI_BASE "ncti_base")
set(NCTI_RENDER "ncti_render")
set(NCTI_PLUGINMANAGER "ncti_PluginManager")
set(NCTI_GEOM_ENGINE "ncti_geom_engine")

set(NCTI_OBJECT "ncti_object")
set(NCTI_PLUGIN "ncti_plugin")
set(NCTI_PUBFUN "ncti_pubfun")
set(NCTI_PYTHON "ncti_python")
set(NCTI_SKETCH "ncti_sketch")
set(NCTI_WINDOW "ncti_window")

# OCC 库模块定义
set(NCTI_OCC_KERNEL TKernel)
set(NCTI_OCC_MATH TKMath)
set(NCTI_OCC_G2D TKG2d)
set(NCTI_OCC_G3D TKG3d)
set(NCTI_OCC_GEOMBASE TKGeomBase)
set(NCTI_OCC_BREP TKBRep)
set(NCTI_OCC_GEOMALGO TKGeomAlgo)
set(NCTI_OCC_TOPALGO TKTopAlgo)
set(NCTI_OCC_SHHEALING TKShHealing)
set(NCTI_OCC_MESH TKMesh)
set(NCTI_OCC_PRIM TKPrim)
set(NCTI_OCC_BO TKBO)
set(NCTI_OCC_BOOL TKBool)
set(NCTI_OCC_FEAT TKFeat)
set(NCTI_OCC_FILLET TKFillet)
set(NCTI_OCC_OFFSET TKOffset)
set(NCTI_OCC_XSBASE TKXSBase)
set(NCTI_OCC_IGES TKIGES)
set(NCTI_OCC_STEP TKSTEP)
set(NCTI_OCC_STEPBASE TKSTEPBase)
set(NCTI_OCC_STEPATTR TKSTEPAttr)
set(NCTI_OCC_STEP209 TKSTEP209)

# Python 版本配置
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
set(NCTI_PYTHON_VERSION "${Python3_VERSION_MAJOR}${Python3_VERSION_MINOR}")

set(NCTI_PYTHON_VERSION ${NCTI_PYTHON_VERSION} 
    CACHE STRING "Python version (auto-detected, e.g., 38 for 3.8)")

message(STATUS "Python ${Python3_VERSION} detected, NCTI_PYTHON_VERSION=${NCTI_PYTHON_VERSION}")
# ==============================================================================
# GMDE_CppSDK 路径配置
# ==============================================================================
# 提取上一级目录的路径
get_filename_component(NCTI_PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" DIRECTORY)

# 设置SDK路径
set(NCTI_GMDE_CPPSDK_ROOT ${NCTI_PROJECT_DIR}/SDK)

# 标准化路径分隔符
file(TO_CMAKE_PATH ${NCTI_GMDE_CPPSDK_ROOT} NCTI_GMDE_CPPSDK_ROOT)

# 设置 SDK 包含目录和库目录
set(NCTI_GMDE_CPPSDK_BIN ${NCTI_GMDE_CPPSDK_ROOT}/bin CACHE PATH "SDK include path" FORCE)
set(NCTI_GMDE_CPPSDK_INC ${NCTI_GMDE_CPPSDK_ROOT}/inc CACHE PATH "SDK include path" FORCE)
set(NCTI_GMDE_CPPSDK_LIB ${NCTI_GMDE_CPPSDK_ROOT}/lib CACHE PATH "SDK library path" FORCE)
set(NCTI_SDK_OCC_INC ${NCTI_GMDE_CPPSDK_INC}/OCC CACHE PATH "SDK OCC INC PATH" FORCE)

# 设置第三方库的头文件和库的路径
set(NCTI_3RDPARTY_ROOT ${NCTI_PROJECT_DIR}/CppCAEPre/3rdparty CACHE PATH "3rdparty ROOT PATH" FORCE)
set(NCTI_3RDPARTY_INC ${NCTI_3RDPARTY_ROOT}/${NCTI_BUILD_TYPE}/include CACHE PATH "3rdparty Inc PATH" FORCE)
set(NCTI_3RDPARTY_LIB ${NCTI_3RDPARTY_ROOT}/${NCTI_BUILD_TYPE}/lib CACHE PATH "3rdparty Lib PATH" FORCE)

# 设置输出路径宏
macro(SetOutputDirectories target_dir lib_dir exe_dir)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${target_dir}/Debug)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${target_dir}/Release)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${target_dir}/MinSizeRel)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${target_dir}/RelWithDebInfo)  
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${lib_dir})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${lib_dir})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${lib_dir})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${lib_dir})  
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${exe_dir}/Debug)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${exe_dir}/Release)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${exe_dir}/MinSizeRel)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${exe_dir}/RelWithDebInfo)
endmacro()

# 设置Ncti库的头文件和库的路径
set(NCTI_APPLICATION_DIR_NCTICAX_INC ${NCTI_GMDE_CPPSDK_INC} CACHE PATH "INC PATH" FORCE)
set(NCTI_APPLICATION_DIR_NCTICAX_LIB ${NCTI_GMDE_CPPSDK_LIB}/${NCTI_NCTICAX} CACHE PATH "INC PATH" FORCE)
set(NCTI_APPLICATION_DIR_NCTI_TEST_INC ${CMAKE_CURRENT_SOURCE_DIR}/NctiCAEPre/Inc CACHE PATH "CAD INC PATH")

# Python 路径配置
set(INC_PATH_PYTHON ${NCTI_GMDE_CPPSDK_INC}/python${NCTI_PYTHON_VERSION})
set(LIB_PATH_PYTHON ${NCTI_GMDE_CPPSDK_LIB}/python${NCTI_PYTHON_VERSION})

# OCC 路径配置
set(INC_PATH_OCC ${NCTI_GMDE_CPPSDK_INC}/${NCTI_OCC})
set(LIB_PATH_OCC ${NCTI_GMDE_CPPSDK_LIB}/${NCTI_OCC})

set(INC_PATH_NCTI ${NCTI_GMDE_CPPSDK_INC}/${NCTI})
set(LIB_PATH_NCTI ${NCTI_APPLICATION_DIR_NCTICAX_LIB})

# inc
set(INC_PATH_NCTI_BASE ${NCTI_GMDE_CPPSDK_INC}/${NCTI_BASE})
set(INC_PATH_NCTI_OBJECT ${NCTI_GMDE_CPPSDK_INC}/${NCTI_OBJECT})
set(INC_PATH_NCTI_PLUGIN ${NCTI_GMDE_CPPSDK_INC}/${NCTI_PLUGIN})
set(INC_PATH_NCTI_PLUGINMANAGER ${NCTI_GMDE_CPPSDK_INC}/${NCTI_PLUGINMANAGER})
set(INC_PATH_NCTI_PUBFUN ${NCTI_GMDE_CPPSDK_INC}/${NCTI_PUBFUN})
set(INC_PATH_NCTI_RENDER ${NCTI_GMDE_CPPSDK_INC}/${NCTI_RENDER})
include_directories(${NCTI_GMDE_CPPSDK_INC})

# 设置全局输出路径
set(NCTI_BIN_OUTPUT_PATH ${QT_VERSION_INFO})
SetOutputDirectories(${NCTI_GMDE_CPPSDK_BIN}/${NCTI_BIN_OUTPUT_PATH} ${NCTI_APPLICATION_DIR_NCTICAX_LIB} ${NCTI_GMDE_CPPSDK_BIN}/${NCTI_BIN_OUTPUT_PATH})

# ==============================================================================
# NctiCAEPre 子目录配置
# ==============================================================================

# 前处理模块定义
set(NCTI_QT_CAE_PRE "ncti_qt_cae_pre")
set(NCTI_QT_LAUNCHER "ncti_qt_launcher")
set(NCTI_QT_SCRIPT_EDIT "ncti_qt_script_edit")
set(NCTI_QT_PUBFUN "ncti_qt_pubfun")
set(NCTI_QT_UIOPTION "ncti_qt_uioption")
set(NCTI_QT_RIBBONBAR "ncti_qt_ribbonbar")

# 启用文件夹分组（仅对支持的生成器有效，如 Visual Studio）
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 添加 NctiCAEPre 项目相关子目录
add_subdirectory(NctiCAEPre/Code/${NCTI_QT_CAE_PRE})
set_target_properties(${NCTI_QT_CAE_PRE} PROPERTIES FOLDER "NctiCAEPreProject")

add_subdirectory(NctiCAEPre/Code/${NCTI_QT_LAUNCHER})
set_target_properties(${NCTI_QT_LAUNCHER} PROPERTIES FOLDER "NctiCAEPreProject")

add_subdirectory(NctiCAEPre/Code/${NCTI_QT_SCRIPT_EDIT})
set_target_properties(${NCTI_QT_SCRIPT_EDIT} PROPERTIES FOLDER "NctiCAEPreProject")

add_subdirectory(NctiCAEPre/Code/${NCTI_QT_PUBFUN})
set_target_properties(${NCTI_QT_PUBFUN} PROPERTIES FOLDER "NctiCAEPreProject")

add_subdirectory(NctiCAEPre/Code/${NCTI_QT_UIOPTION})
set_target_properties(${NCTI_QT_UIOPTION} PROPERTIES FOLDER "NctiCAEPreProject")

########################################################
# 第三方库参数设置
########################################################

# 添加第三方库相关子目录
function(SetupThirdPartyTarget target_name)
    if(TARGET ${target_name})
        set_target_properties(${target_name} PROPERTIES 
            FOLDER "Ncti3rdParty"
            ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${NCTI_3RDPARTY_LIB}
            ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${NCTI_3RDPARTY_LIB}
            ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${NCTI_3RDPARTY_LIB}
            LIBRARY_OUTPUT_DIRECTORY_DEBUG ${NCTI_3RDPARTY_LIB}
            LIBRARY_OUTPUT_DIRECTORY_RELEASE ${NCTI_3RDPARTY_LIB}
            LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${NCTI_3RDPARTY_LIB}
            PDB_OUTPUT_DIRECTORY_DEBUG ${NCTI_3RDPARTY_LIB}
            PDB_OUTPUT_DIRECTORY_RELEASE ${NCTI_3RDPARTY_LIB}
            PDB_OUTPUT_DIRECTORY_RELWITHDEBINFO ${NCTI_3RDPARTY_LIB}
        )
    endif()
endfunction()

#SARibbonBar
add_subdirectory(3rdParty/Source/SARibbonBar)
SetupThirdPartyTarget(${NCTI_QT_RIBBONBAR})

#QtPropertyBrowser
add_subdirectory(3rdParty/Source/QtPropertyBrowser)
SetupThirdPartyTarget(QtPropertyBrowser)

# ORM库
add_subdirectory(3rdParty/Source/ormpp)

#qBreakpad
add_subdirectory(3rdParty/Source/qBreakpad)
SetupThirdPartyTarget(qBreakpad)

# ==============================================================================
# Demo 项目定义
# ==============================================================================
set(NCTI_CMD_DEMO "ncti_cmd_demo")
set(NCTI_PLUGIN_DEMO "ncti_plugin_demo")
set(NCTI_OCC_PLUGIN_DEMO "ncti_occ_plugin_demo")
set(NCTI_PYTHON_DEMO "ncti_python_demo")

# 添加Demo相关子目录
add_subdirectory(examples/${NCTI_CMD_DEMO})
set_target_properties(${NCTI_CMD_DEMO} PROPERTIES FOLDER "NctiPluginDemo")

add_subdirectory(examples/${NCTI_PLUGIN_DEMO})
set_target_properties(${NCTI_PLUGIN_DEMO} PROPERTIES FOLDER "NctiPluginDemo")

add_subdirectory(examples/${NCTI_OCC_PLUGIN_DEMO})
set_target_properties(${NCTI_OCC_PLUGIN_DEMO} PROPERTIES FOLDER "NctiPluginDemo")

add_subdirectory(examples/${NCTI_PYTHON_DEMO})
set_target_properties(${NCTI_PYTHON_DEMO} PROPERTIES FOLDER "NctiPluginDemo")

# ==============================================================================
# IDE 特定配置
# ==============================================================================

# 指定 Visual Studio 启动项目
if(MSVC)
  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${NCTI_QT_CAE_PRE})
endif()

# 输出配置信息
message(STATUS "=============================================")
message(STATUS "Cpp SDK Path: ${NCTI_GMDE_CPPSDK_ROOT}")
message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "NCTI Python version: ${NCTI_PYTHON_VERSION}")
message(STATUS "Selected Build type: ${NCTI_BUILD_TYPE}")
message(STATUS "Qt Version Info: ${QT_VERSION_INFO}")
message(STATUS "Qt${QT_VERSION_MAJOR}_DIR: ${Qt${QT_VERSION_MAJOR}_DIR}")
message(STATUS "=============================================")

# ==============================================================================
# 安装配置
# ==============================================================================

# 设置安装路径
set(CMAKE_INSTALL_PREFIX "${NCTI_GMDE_CPPSDK_BIN}/${NCTI_BIN_OUTPUT_PATH}" CACHE PATH "Install path" FORCE)

# 确保安装目录存在
# if(NOT EXISTS "${CMAKE_INSTALL_PREFIX}")
    # file(MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}")
# endif()

# ==============================================================================
# 安装可执行文件和动态库
# ==============================================================================

# 定义需要安装的目标列表
set(INSTALL_TARGETS
    ${NCTI_QT_CAE_PRE}
    ${NCTI_QT_LAUNCHER}
    ${NCTI_QT_PUBFUN}
    ${NCTI_QT_SCRIPT_EDIT}
    ${NCTI_QT_UIOPTION}
    ${NCTI_CMD_DEMO}
    ${NCTI_OCC_PLUGIN_DEMO}
    ${NCTI_PLUGIN_DEMO}
    ${NCTI_PYTHON_DEMO}
    ${NCTI_QT_RIBBONBAR}
    QtPropertyBrowser
)

# 安装目标文件
foreach(TARGET ${INSTALL_TARGETS})
    # 检查目标是否存在
    if(TARGET ${TARGET})
        if(NCTI_BUILD_TYPE MATCHES "Debug" OR NCTI_BUILD_TYPE MATCHES "RelWithDebInfo")
            # 获取目标类型
            get_target_property(TARGET_TYPE ${TARGET} TYPE)

            if(TARGET_TYPE STREQUAL "EXECUTABLE")
                # 安装可执行文件
                install(TARGETS ${TARGET}
                        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
                        COMPONENT Runtime)
            elseif(TARGET_TYPE STREQUAL "SHARED_LIBRARY")
                # 安装动态库
                install(TARGETS ${TARGET}
                        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
                        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}
                        COMPONENT Libraries)
            endif()
        endif()
    endif()
endforeach()

# ==============================================================================
# 使用 windeployqt 部署 Qt 依赖
# ==============================================================================

if(WIN32 AND DEFINED NCTI_QT_CAE_PRE)
    # 查找 windeployqt 工具
    find_program(QT_WINDEPLOYQT_EXECUTABLE
        NAMES windeployqt
        HINTS "${Qt${QT_VERSION_MAJOR}_DIR}/../../../bin"
        NO_DEFAULT_PATH
        NO_CACHE
        DOC "Path to windeployqt executable"
    )

    if(QT_WINDEPLOYQT_EXECUTABLE)
        message(STATUS "Found windeployqt: ${QT_WINDEPLOYQT_EXECUTABLE}")
    else()
        message(WARNING "windeployqt not found. Qt dependencies will not be deployed automatically.")
    endif()
endif()

# 安装完成信息
message(STATUS "Installation prefix: ${CMAKE_INSTALL_PREFIX}")