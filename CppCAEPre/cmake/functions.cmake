#-----------------------------------------------------------------------------
# 寻找指定路径下的头文件
# DIR_PATH_INC 目录路径
# DLL_NAME 库名
# 最终将收集的头文件目录添加到编译器的include目录列表中
#-----------------------------------------------------------------------------
macro(FUN_FIND_ALL_HEADFILE_DIR DIR_PATH_INC DLL_NAME)
   set(DIR_PATH ${DIR_PATH_INC}/${DLL_NAME})
   FILE(GLOB_RECURSE ARG_HEADFILE ${DIR_PATH}/*.*)
   set(dirlist "")	
   foreach(child ${ARG_HEADFILE})
        string(REGEX REPLACE "(.*)/.*" "\\1" LIB_NAME ${child})
		if(IS_DIRECTORY ${LIB_NAME})
		   set(PATH_HELP ${LIB_NAME})
		    #message(STATUS "INCLUDE_DIR_LIST = ${LIB_NAME}")
		   while(NOT PATH_HELP STREQUAL ${DIR_PATH})
		        if(NOT PATH_HELP IN_LIST dirlist)
	               list(APPEND dirlist ${PATH_HELP})
			       #message(STATUS "INCLUDE_DIR_LIST = ${PATH_HELP}")
                endif()
			    string(REGEX REPLACE "(.*)/(.*)" "\\1" PROJECT_INIT_PATH  ${PATH_HELP})
			    set(PATH_HELP ${PROJECT_INIT_PATH})
		   endwhile()			
        endif()	
   endforeach()
   include_directories(${dirlist})
endmacro()

#-----------------------------------------------------------------------------
# 将一组源文件按照它们所在的目录结构组织到Visual Studio的项目视图中
# source_files（源文件列表变量的名称)
# sgbd_cur_dir（当前源文件所在的根目录路径）
#-----------------------------------------------------------------------------
macro(source_group_by_dir source_files sgbd_cur_dir)
        foreach(sgbd_file ${${source_files}})
            string(REGEX REPLACE ${sgbd_cur_dir}/\(.*\) \\1 sgbd_fpath ${sgbd_file})
            string(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
            string(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
            string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
			#message(STATUS "INCLUDE_DIR_LIST = ${sgbd_group_name}")
            if(sgbd_nogroup)
                set(sgbd_group_name "\\")
            endif(sgbd_nogroup)
            source_group(${sgbd_group_name} FILES ${sgbd_file})
        endforeach(sgbd_file)
endmacro(source_group_by_dir)

#-----------------------------------------------------------------------------
# 
# DIR_PATH_INC（头文件所在的根目录路径）
# NCTI_PROJECT_DLL（用于定位头文件子目录的标识符或名称）
#-----------------------------------------------------------------------------
macro(include_source_and_head DIR_PATH_INC NCTI_PROJECT_DLL)
   file(GLOB_RECURSE project_headers ${DIR_PATH_INC}/${NCTI_PROJECT_DLL}/*.h)
   set(all_files_h ${project_headers})
   source_group_by_dir(all_files_h ${DIR_PATH_INC}/${NCTI_PROJECT_DLL})

   file(GLOB_RECURSE project_cpps *.cpp *c)
   set(all_files_cpp ${project_cpps})
   source_group_by_dir(all_files_cpp ${CMAKE_CURRENT_SOURCE_DIR})
endmacro(include_source_and_head)

#-----------------------------------------------------------------------------
# 生成DLL
#-----------------------------------------------------------------------------
macro(NCTI_CODE_BUILD)
  FUN_FIND_ALL_HEADFILE_DIR(${CMAKE_CURRENT_SOURCE_DIR}/../../Inc ${NCTI_PROJECT})
  include_source_and_head(${CMAKE_CURRENT_SOURCE_DIR}/../../Inc ${NCTI_PROJECT})
  add_library(${NCTI_PROJECT} 
    SHARED 
    ${all_files_h}
    ${all_files_cpp}
  )
endmacro()