#ifndef dcl_ncti_pubfun_H
#define dcl_ncti_pubfun_H

#ifdef NCTILIBNAME
#undef NCTILIBNAME
#endif

#ifndef DECL_NCTI_PUBFUN
#ifdef NCTI_DLL

#ifdef EXPORT_NCTI_PUBFUN
#ifdef _MSC_VER
#define DECL_NCTI_PUBFUN __declspec(dllexport)
#else
#define DECL_NCTI_PUBFUN __attribute__((visibility("default")))
#endif 
# else 
#ifdef _MSC_VER
#define DECL_NCTI_PUBFUN __declspec(dllimport)
#else
#define DECL_NCTI_PUBFUN __attribute__((visibility("default")))
#endif 
//#  ifdef _MSC_VER
//#    define NCTIGMLIBNAME "nctigm_base.lib"
//#    pragma comment(lib, NCTILIBNAME)
//#  else
//#    define NCTIGMLIBNAME "libnctigm_base.so"
//#    pragma comment(lib, NCTIGMLIBNAME)
//#endif  
# endif

#else
# define DECL_NCTI_PUBFUN
#endif
#endif
#endif // 