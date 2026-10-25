#ifndef ncti_dcl_H
#define ncti_dcl_H

#ifndef DECL_NCTI
#ifdef NCTI_DLL
# ifdef EXPORT_NCTI
#ifdef _MSC_VER
#define DECL_NCTI __declspec(dllexport)
#else
#define DECL_NCTI __attribute__((visibility("default")))
#endif 
# else  
#ifdef _MSC_VER
#define DECL_NCTI __declspec(dllimport)
#else
#define DECL_NCTI __attribute__((visibility("default")))
#endif 

# endif
#else
# define DECL_NCTI
#endif
#endif

#endif // !ncti_dcl_H