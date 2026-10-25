#define
add_definitions(-DEXPORT_NCTI_PLUGIN -DUNICODE)
set(NCTI_PROJECT ${NCTI_PYTHON_DEMO})

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
  set(CMAKE_SHARED_LIBRARY_SUFFIX ".pyd")
endif()

if(NCTI_CLOSE_VIEW)
  add_definitions(-DNCTI_CLOSE_VIEW)
endif()

#指定的路径添加到编译器的头文件搜索路径中
include_directories(${INC_PATH_PYTHON})

FUN_FIND_ALL_HEADFILE_DIR(${NCTI_GMDE_CPPSDK_INC} ${NCTI_BASE})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_GMDE_CPPSDK_INC} ${NCTI_PLUGINMANAGER})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_GMDE_CPPSDK_INC} ${NCTI_PLUGIN})
FUN_FIND_ALL_HEADFILE_DIR(${CMAKE_CURRENT_SOURCE_DIR}/../ ${NCTI_PLUGIN_DEMO})
FUN_FIND_ALL_HEADFILE_DIR(${CMAKE_CURRENT_SOURCE_DIR} "")

file(GLOB_RECURSE project_cpps *.cpp *c *cc *h)
set(all_files_cpp ${project_cpps})
source_group_by_dir(all_files_cpp ${CMAKE_CURRENT_SOURCE_DIR})


#将指定的路径添加到链接器的库搜索路径中
link_directories(${LIB_PATH_NCTI})
link_directories(${LIB_PATH_PYTHON})

#DLL library  定义库目标，将指定的源文件编译成一个库
add_library(${NCTI_PROJECT} SHARED 
  ${all_files_cpp}
)

#为 ${NCTI_PROJECT} 目标指定一系列需要链接的库
target_link_libraries(${NCTI_PROJECT} 
  ${NCTI} 
  ${NCTI_BASE} 
  ${NCTI_RENDER} 
  ${NCTI_PLUGINMANAGER}
  ${NCTI_OBJECT} 
  ${NCTI_PLUGIN}
  ${NCTI_PUBFUN}
  ${NCTI_DATA_INTEROP}
  ${NCTI_GEOM_ENGINE} 
  python${NCTI_PYTHON_VERSION}
)