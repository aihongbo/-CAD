#ifndef dcl_ncti_plugin_H
#define dcl_ncti_plugin_H

#ifdef NCTILIBNAME
#undef NCTILIBNAME
#endif

#ifndef DECL_NCTI_PLUGIN
#ifdef NCTI_DLL

#ifdef EXPORT_NCTI_PLUGIN
#ifdef _MSC_VER
#define DECL_NCTI_PLUGIN __declspec(dllexport)
#else
#define DECL_NCTI_PLUGIN __attribute__((visibility("default")))
#endif 
# else 
#ifdef _MSC_VER
#define DECL_NCTI_PLUGIN __declspec(dllimport)
#else
#define DECL_NCTI_PLUGIN __attribute__((visibility("default")))
#endif 
//#  ifdef _MSC_VER
//#    define NCTILIBNAME "ncti_base.lib"
//#    pragma comment(lib, NCTILIBNAME)
//#  else
//#    define NCTILIBNAME "libncti_base.so"
//#    pragma comment(lib, NCTILIBNAME)
//#endif  
# endif

#else
# define DECL_NCTI_PLUGIN
#endif
#endif
#endif // 