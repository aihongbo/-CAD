#ifndef ncti_dcl_render_H
#define ncti_dcl_render_H

#ifndef DECL_NCTI_RENDER
#ifdef NCTI_DLL
# ifdef EXPORT_NCTI_RENDER
#ifdef _MSC_VER
#define DECL_NCTI_RENDER __declspec(dllexport)
#else
#define DECL_NCTI_RENDER __attribute__((visibility("default")))
#endif 
# else  
#ifdef _MSC_VER
#define DECL_NCTI_RENDER __declspec(dllimport)
#else
#define DECL_NCTI_RENDER __attribute__((visibility("default")))
#endif 
# endif
#else
# define DECL_NCTI_RENDER
#endif
#endif

#endif // !ncti_dcl_render_H