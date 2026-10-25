cmake_minimum_required(VERSION 3.24)

set(NCTI_PROJECT ${NCTI_QT_SCRIPT_EDIT})

# Qt自动处理
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)

# 查找Qt库
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets Svg REQUIRED)

# 不使用Qt关键字
add_compile_definitions(QT_NO_KEYWORDS)

# 设置编译定义
add_compile_definitions(EXPORT_NCTI_QT_SCRIPT_EDIT)

# 设置MSVC编译选项
if(MSVC)
  add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
  add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

# 查找所有头文件目录
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_APPLICATION_DIR_NCTICAX_INC} ${NCTI})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_APPLICATION_DIR_NCTICAX_INC} ${NCTI_BASE})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_APPLICATION_DIR_NCTICAX_INC} ${NCTI_RENDER})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_APPLICATION_DIR_NCTICAX_INC} ${NCTI_PLUGINMANAGER})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_APPLICATION_DIR_NCTICAX_INC} ${NCTI_WINDOW})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_APPLICATION_DIR_NCTICAX_INC} ${NCTI_OBJECT})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_APPLICATION_DIR_NCTICAX_INC} ${NCTI_PLUGIN})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_APPLICATION_DIR_NCTICAX_INC} ${NCTI_PUBFUN})

# 源码扫描
file(GLOB_RECURSE project_cpps *.cpp *c *cc *.h *.hpp *.json)
set(project_cpps_t ${project_cpps})
source_group_by_dir(project_cpps_t ${CMAKE_CURRENT_SOURCE_DIR})

# 查找头文件目录
FUN_FIND_ALL_HEADFILE_DIR(${CMAKE_CURRENT_SOURCE_DIR}/../../Inc ${NCTI_PROJECT})
include_source_and_head(${CMAKE_CURRENT_SOURCE_DIR}/../../Inc ${NCTI_PROJECT})

# 创建库
add_library(${NCTI_PROJECT} 
	SHARED 
	${all_files_h}
	${all_files_cpp}
	${project_cpps_t}
)

# 包含目录
target_include_directories(${NCTI_PROJECT} PRIVATE 
  ${INC_PATH_NCTI}
  ${INC_PATH_PYTHON}
)

# 库目录
target_link_directories(${NCTI_PROJECT} PRIVATE
	${LIB_PATH_NCTI}
	${LIB_PATH_PYTHON}
)

if(WIN32)
  target_compile_definitions(${NCTI_PROJECT} PRIVATE UNICODE _UNICODE)
endif()

# 包含目录
target_include_directories(${NCTI_PROJECT} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/Source/CodeEditor
  ${CMAKE_CURRENT_SOURCE_DIR}/Source/CodeEditor/QCodeEditor/include
)

target_include_directories(${NCTI_PROJECT} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/../../Inc/${NCTI_PROJECT}/Source
)

# Qt库链接
target_link_libraries(${NCTI_PROJECT} PUBLIC
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Gui
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Svg
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
)