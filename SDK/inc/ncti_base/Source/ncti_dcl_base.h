#ifndef ncti_dcl_base_H
#define ncti_dcl_base_H


#ifndef DECL_NCTI_BASE
#ifdef NCTI_DLL

#ifdef EXPORT_NCTI_BASE
#ifdef _MSC_VER
#define DECL_NCTI_BASE __declspec(dllexport)
#else
#define DECL_NCTI_BASE __attribute__((visibility("default")))
#endif 
# else 
#ifdef _MSC_VER
#define DECL_NCTI_BASE __declspec(dllimport)
#else
#define DECL_NCTI_BASE __attribute__((visibility("default")))
#endif 
# endif

#else
# define DECL_NCTI_BASE
#endif
#endif
#endif // !ncti_dcl_base_H