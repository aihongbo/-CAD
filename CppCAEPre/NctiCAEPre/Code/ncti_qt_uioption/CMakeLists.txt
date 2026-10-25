cmake_minimum_required (VERSION 3.24)

set(NCTI_PROJECT ${NCTI_QT_UIOPTION})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Qt自动处理
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 查找Qt库
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets Svg REQUIRED)

# 不使用Qt关键字
add_compile_definitions(QT_NO_KEYWORDS)

# 指定禁用 Qt 6.0.0 之前的已弃用 API
add_compile_definitions(QT_DISABLE_DEPRECATED_BEFORE=0x060000)

# Qt6-specific components
if(QT_VERSION_MAJOR EQUAL 6)
    find_package(Qt6 COMPONENTS SvgWidgets REQUIRED)
endif()

# 包含目录
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_APPLICATION_DIR_NCTI_TEST_INC} ${NCTI_PROJECT})
include_source_and_head(${NCTI_APPLICATION_DIR_NCTI_TEST_INC} ${NCTI_PROJECT})
set(SOURCE_HEADER_FILES ${all_files_h})

# 源码扫描
set(SOURCE_FILES
    Source/NctiFramelessManager.cpp
    Source/NctiBaseDialog.cpp
    Source/NctiMessageDialog.cpp
    Source/CustomActionManager.cpp
    Source/UIOption.cpp
    Source/UIOptionItemDelegate.cpp
    Source/UIOptionItemModel.cpp
    Source/UIOptionTree.cpp
    Source/UIOptionMimeData.cpp
    Source/UIOptionDialog.cpp
    Source/AddUIActionDialog.cpp
    Source/AddCustomActionDialog.cpp
    Source/ConfigCustomActionDialog.cpp
)

file(GLOB UI_FILES "Source/UI/*.ui")
source_group("UI Files" FILES ${UI_FILES})

set(UI_RES
    Source/uires/resource.qrc
)

# 将资源文件分组到"Resource Files"筛选器下
source_group("Resource Files" FILES ${UI_RES})

# 生成目标
add_compile_definitions(EXPORT_NCTI_UIOPTION)
source_group_by_dir(${SOURCE_FILES} ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${NCTI_PROJECT} SHARED
    ${SOURCE_FILES}
    ${UI_FILES}
    ${UI_RES}
    ${SOURCE_HEADER_FILES}
)

# 设置 AUTOUIC 搜索路径
target_include_directories(${NCTI_PROJECT} PRIVATE Source/UI)
set_property(TARGET ${NCTI_PROJECT} PROPERTY AUTOUIC_SEARCH_PATHS Source/UI)

target_compile_definitions(${NCTI_PROJECT} PRIVATE 
	ORMPP_ENABLE_SQLITE3
	#ORMPP_ENABLE_LOG
)
 
if(WIN32)
  target_compile_definitions(${NCTI_PROJECT} PRIVATE UNICODE _UNICODE)
endif()

# 添加第三方头文件目录
target_include_directories(${NCTI_PROJECT} PRIVATE 
  ${NCTI_3RDPARTY_INC}
  ${NCTI_3RDPARTY_INC}/ormpp
  ${NCTI_3RDPARTY_INC}/sqlite3
)

# 添加第三方库目录
target_link_directories(${NCTI_PROJECT} PRIVATE
	${NCTI_3RDPARTY_LIB}
)
	
# Qt库链接
target_link_libraries(${NCTI_PROJECT} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Svg
)

if(QT_VERSION_MAJOR EQUAL 6)
    target_link_libraries(${NCTI_PROJECT} PUBLIC Qt6::SvgWidgets)
endif()

# 依赖库链接
target_link_libraries(${NCTI_PROJECT} PRIVATE
	sqlite3
)