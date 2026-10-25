#ifndef dcL_ncti_gm_model_function_H
#define dcL_ncti_gm_model_function_H

/**
 * @brief 几何模型功能导出宏定义
 * @details 根据编译器和平台定义几何模型功能的导入导出宏
 */
#ifndef DECL_NCTI_GM_MODEL_PUBFUN
#ifdef NCTI_DLL
# ifdef EXPORT_NCTI_GM_MODEL_PUBFUN
#ifdef _MSC_VER
/**
 * @brief Windows平台几何模型功能导出宏
 */
#define DECL_NCTI_GM_MODEL_PUBFUN __declspec(dllexport)
#else
/**
 * @brief 非Windows平台几何模型功能导出宏
 */
#define DECL_NCTI_GM_MODEL_PUBFUN __attribute__((visibility("default")))
#endif 
# else  
#ifdef _MSC_VER
/**
 * @brief Windows平台几何模型功能导入宏
 */
#define DECL_NCTI_GM_MODEL_PUBFUN __declspec(dllimport)
#else
/**
 * @brief 非Windows平台几何模型功能导入宏
 */
#define DECL_NCTI_GM_MODEL_PUBFUN __attribute__((visibility("default")))
#endif 

# endif
#else
/**
 * @brief 非DLL模式几何模型功能宏定义
 */
# define DECL_NCTI_GM_MODEL_PUBFUN
#endif
#endif
#endif