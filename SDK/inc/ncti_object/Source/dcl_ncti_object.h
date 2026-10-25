#ifndef dcl_ncti_object_H
#define dcl_ncti_object_H

#ifndef DECL_NCTI_OBJECT
#ifdef NCTI_DLL

#ifdef EXPORT_NCTI_OBJECT
#ifdef _MSC_VER
#define DECL_NCTI_OBJECT __declspec(dllexport)
#else
#define DECL_NCTI_OBJECT __attribute__((visibility("default")))
#endif 
# else 
#ifdef _MSC_VER
#define DECL_NCTI_OBJECT __declspec(dllimport)
#else
#define DECL_NCTI_OBJECT __attribute__((visibility("default")))
#endif 

# endif

#else
# define DECL_NCTI_OBJECT
#endif
#endif
#endif // 