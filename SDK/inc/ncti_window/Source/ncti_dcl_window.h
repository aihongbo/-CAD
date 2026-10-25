#ifndef dcl_ncti_window_H
#define dcl_ncti_window_H

#ifndef DECL_NCTI_WINDOW
#ifdef NCTI_DLL
# ifdef EXPORT_NCTI_WINDOW
#ifdef _MSC_VER
#define DECL_NCTI_WINDOW __declspec(dllexport)
#else
#define DECL_NCTI_WINDOW __attribute__((visibility("default")))
#endif 
# else  
#ifdef _MSC_VER
#define DECL_NCTI_WINDOW __declspec(dllimport)
#else
#define DECL_NCTI_WINDOW __attribute__((visibility("default")))
#endif 

# endif
#else
# define DECL_NCTI_WINDOW
#endif
#endif
#endif
