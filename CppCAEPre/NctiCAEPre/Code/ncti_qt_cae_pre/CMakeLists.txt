cmake_minimum_required (VERSION 3.24)

set(NCTI_PROJECT ${NCTI_QT_CAE_PRE})

#-----------------------------------------------------------------------------
# 设置C++标准
#-----------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DCONFIG_FILE="config_caepre.json")

# 默认关闭场景树
option(ENABLE_SHOW_SCENE_VIEW "Enable show scene view" OFF)

# 是否在构建时更新版本号
option(ENABLE_VERSION_AUTO_UPDATE "Enable version auto update" OFF)

# 开启本地QSS加载
option(ENABLE_LOCAL_QSS "Enable local qss" OFF)

# 是否编译为DLL库
option(ENABLE_BUILD_AS_SHARED_LIBS "Build as shared library" OFF)

if(NOT DEFINED NCTI_QT_UIOPTION)
  set(NCTI_QT_UIOPTION "ncti_qt_uioption")
endif()

if(NOT DEFINED NCTI_QT_LAUNCHER)
  set(NCTI_QT_LAUNCHER "ncti_qt_launcher")
endif()

if(NOT DEFINED NCTI_QBREAKPAD)
  set(NCTI_QBREAKPAD "qBreakpad")
endif()

# Qt自动处理
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 查找Qt库
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets Network Svg REQUIRED)

# 不使用Qt关键字
add_compile_definitions(QT_NO_KEYWORDS)

# Qt5-specific components
if(WIN32 AND QT_VERSION_MAJOR EQUAL 5)
  find_package(Qt5 COMPONENTS WinExtras REQUIRED)
endif()

# 指定包含当前路径
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 查找所有头文件目录
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_APPLICATION_DIR_NCTICAX_INC} ${NCTI})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_APPLICATION_DIR_NCTICAX_INC} ${NCTI_BASE})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_APPLICATION_DIR_NCTICAX_INC} ${NCTI_RENDER})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_APPLICATION_DIR_NCTICAX_INC} ${NCTI_PLUGINMANAGER})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_APPLICATION_DIR_NCTICAX_INC} ${NCTI_GEOM_ENGINE})

FUN_FIND_ALL_HEADFILE_DIR(${NCTI_APPLICATION_DIR_NCTICAX_INC} ${NCTI_WINDOW})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_APPLICATION_DIR_NCTICAX_INC} ${NCTI_OBJECT})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_APPLICATION_DIR_NCTICAX_INC} ${NCTI_PLUGIN})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_APPLICATION_DIR_NCTICAX_INC} ${NCTI_PUBFUN})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_APPLICATION_DIR_NCTICAX_INC} ${NCTI_SKETCH})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_APPLICATION_DIR_NCTI_TEST_INC} ${NCTI_QT_PUBFUN})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_APPLICATION_DIR_NCTI_TEST_INC} ${NCTI_QT_SCRIPT_EDIT})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_APPLICATION_DIR_NCTI_TEST_INC} ${NCTI_QT_LAUNCHER})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_APPLICATION_DIR_NCTI_TEST_INC} ${NCTI_QT_UIOPTION})
FUN_FIND_ALL_HEADFILE_DIR(${CMAKE_CURRENT_SOURCE_DIR} "")

# 源码扫描
file(GLOB_RECURSE src_files
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui"
    "${CMAKE_CURRENT_SOURCE_DIR}/version.h"
)
set(PROJECT_SOURCES ${src_files})
source_group_by_dir(PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR})

if(MSVC)
  # 设置以UTF8格式编译, 必须位于 add_executable() 之前
  add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
  add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

# 生成目标	
if(ENABLE_BUILD_AS_SHARED_LIBS)
  add_library(${NCTI_PROJECT} SHARED)
  target_compile_definitions(${NCTI_PROJECT} PUBLIC
    NCTI_CAE_PRE_BUILD_DLL
    EXPORT_NCTI_QT_CAE_PRE
  )
  message(STATUS "Building ncti_qt_cae_pre as DLL Project...")
else()
  add_executable(${NCTI_PROJECT})
  message(STATUS "Building ncti_qt_cae_pre as EXE Project...")
endif()

# 添加源文件到目标
target_sources(${NCTI_PROJECT} PRIVATE 
  ${PROJECT_SOURCES} 
  ${CMAKE_CURRENT_SOURCE_DIR}/resources/resource.qrc
)

# 添加预处理器宏，直接加载本地QSS
if(ENABLE_LOCAL_QSS)
  target_compile_definitions(${NCTI_PROJECT} PUBLIC
      NCTI_QT_CAD_TEST_LOCAL_QSS="${CMAKE_CURRENT_SOURCE_DIR}/resources"
  )
endif()

# 添加预处理器宏，是否显示Scene视图
if(ENABLE_SHOW_SCENE_VIEW)
  target_compile_definitions(${NCTI_PROJECT} PUBLIC
    NCTI_SHOW_SCENE_VIEW
  )
endif()

# NCTI包含目录
target_include_directories(${NCTI_PROJECT} PRIVATE 
  ${INC_PATH_NCTI}
)

# NCTI库目录
target_link_directories(${NCTI_PROJECT} PRIVATE
  ${LIBS_PATH}
  ${LIB_PATH_NCTI}
)

# 添加SARibbon库的引用
set(QT_RIBBONBAR_ROOT "${NCTI_3RDPARTY_ROOT}/Source/SARibbonBar")
target_include_directories(${NCTI_PROJECT} PRIVATE ${QT_RIBBONBAR_ROOT}/src)

# 添加第三方头文件目录
target_include_directories(${NCTI_PROJECT} PRIVATE 
  ${NCTI_3RDPARTY_INC}
  ${NCTI_3RDPARTY_INC}/qBreakpad
  ${NCTI_3RDPARTY_INC}/ormpp
  ${NCTI_3RDPARTY_INC}/sqlite3
)

# 添加第三方库目录
target_link_directories(${NCTI_PROJECT} PRIVATE ${NCTI_3RDPARTY_LIB})



if(WIN32)
  target_compile_definitions(${NCTI_PROJECT} PRIVATE UNICODE _UNICODE)
  add_compile_definitions(WIN32_LEAN_AND_MEAN NOMINMAX)

  # 添加自定义命令来在构建时更新版本号
  if(ENABLE_VERSION_AUTO_UPDATE)
    add_custom_command(
    	TARGET ${NCTI_PROJECT}
    	PRE_BUILD
    	COMMAND "python" ${CMAKE_CURRENT_SOURCE_DIR}/version.py ${CMAKE_CURRENT_SOURCE_DIR}/version.h
    	COMMENT "Updating version number for ${NCTI_PROJECT}"
    	VERBATIM
    ) 
  endif()

  target_sources(${NCTI_PROJECT} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/version.rc
  )
  
  target_link_libraries(${NCTI_PROJECT} PRIVATE 
    version.lib
  )
endif()

# Qt库链接
target_link_libraries(${NCTI_PROJECT} PUBLIC
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Svg
)

# Link Qt5-specific libraries
if(QT_VERSION_MAJOR EQUAL 5)
  target_link_libraries(${NCTI_PROJECT} PUBLIC Qt5::WinExtras)
endif()

# Qt组件库链接
target_link_libraries(${NCTI_PROJECT} PRIVATE 
  ${NCTI_QT_PUBFUN} 
  ${NCTI_QT_SCRIPT_EDIT}
  ${NCTI_QT_UIOPTION}
  ${NCTI_QT_RIBBONBAR}
  ${NCTI_QBREAKPAD}
)

# NCTI核心库链接
target_link_libraries(${NCTI_PROJECT} PRIVATE 
  ${NCTI} 
  ${NCTI_BASE} 
  ${NCTI_RENDER} 
  ${NCTI_WINDOW} 
  ${NCTI_PLUGINMANAGER} 
  ${NCTI_PUBFUN} 
  ${NCTI_PLUGIN} 
  ${NCTI_OBJECT}
  ${NCTI_SKETCH}
  ${NCTI_GEOM_ENGINE}
)