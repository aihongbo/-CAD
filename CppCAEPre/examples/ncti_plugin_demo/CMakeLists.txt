
#define
add_definitions(-DEXPORT_NCTI_PLUGIN -DUNICODE)
set(NCTI_PROJECT ${NCTI_PLUGIN_DEMO})

FUN_FIND_ALL_HEADFILE_DIR(${NCTI_GMDE_CPPSDK_INC} ${NCTI})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_GMDE_CPPSDK_INC} ${NCTI_BASE})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_GMDE_CPPSDK_INC} ${NCTI_PLUGINMANAGER})
FUN_FIND_ALL_HEADFILE_DIR(${NCTI_GMDE_CPPSDK_INC} ${NCTI_PLUGIN})

file(GLOB_RECURSE project_cpps *.cpp *c *cc *.h *.hpp)
set(all_files_cpp ${project_cpps})
source_group_by_dir(all_files_cpp ${CMAKE_CURRENT_SOURCE_DIR})

link_directories(${LIB_PATH_NCTI})

#DLL library
add_library(${NCTI_PROJECT} SHARED 
  ${all_files_cpp}
)

target_include_directories(${NCTI_PROJECT} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${NCTI_PROJECT}
  ${NCTI_BASE}
  ${NCTI_PLUGIN}
  ${NCTI_PLUGINMANAGER} 
)

